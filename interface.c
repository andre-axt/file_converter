#include <gtk/gtk.h>
#include "converter.h"
#include <string.h>

static char *input_file_path = NULL;
static GtkWidget *file_label;
static GtkWidget *csv_button;
static GtkWidget *tsv_button;

static void update_file_label(const char *filename) {
    char label_text[256];
    if (filename) {
        char *filename_copy = g_strdup(filename);
        char *last_dot = strrchr(filename_copy, '.');
        if (last_dot != NULL) {
            *last_dot = '\0';
        }
        snprintf(label_text, sizeof(label_text), "Selected file: %s", filename);
        g_free(filename_copy);
    } else {
        strcpy(label_text, "No file selected");
    }
    gtk_label_set_text(GTK_LABEL(file_label), label_text);
    
    gtk_widget_set_sensitive(csv_button, filename != NULL);
    gtk_widget_set_sensitive(tsv_button, filename != NULL);
}

static void on_drag_data_received(GtkWidget *widget, GdkDragContext *context, 
                                 gint x, gint y, GtkSelectionData *data, 
                                 guint info, guint time, gpointer user_data) {
    gchar **uris = gtk_selection_data_get_uris(data);
    if (uris) {
        
        gchar *file_uri = uris[0];
        gchar *file_path = g_filename_from_uri(file_uri, NULL, NULL);
        
        if (file_path) {

            if (input_file_path) {
                g_free(input_file_path);
            }
            
            input_file_path = file_path;
            update_file_label(input_file_path);
        }
        
        g_strfreev(uris);
    }
    
    gtk_drag_finish(context, TRUE, FALSE, time);
}

static void on_csv_conversion(GtkWidget *widget, gpointer data) {
    if (!input_file_path) return;
    
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s.csv", input_file_path);
    
    int result = TXTtoCSV(input_file_path, output_path);
    
    if (result == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "File converted successfully to CSV!\nSaved as: %s",
            output_path);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Error converting file to CSV!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

static void on_tsv_conversion(GtkWidget *widget, gpointer data) {
    if (!input_file_path) return;
    
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s.tsv", input_file_path);
    
    int result = TXTtoTSV(input_file_path, output_path);
    
    if (result == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "File converted successfully to TSV!\nSaved as: %s",
            output_path);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Error converting file to TSV!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *drop_area;
    GtkWidget *instructions;
    GtkWidget *button_box;
    
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "File Converter");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    instructions = gtk_label_new("Drag and drop a text file to convert");
    gtk_box_pack_start(GTK_BOX(vbox), instructions, FALSE, FALSE, 0);
    
    drop_area = gtk_event_box_new();
    gtk_widget_set_size_request(drop_area, 300, 100);
    GtkWidget *drop_label = gtk_label_new("Drop file here");
    gtk_container_add(GTK_CONTAINER(drop_area), drop_label);
    
    GdkRGBA color;
    gdk_rgba_parse(&color, "#E0E0E0");
    gtk_widget_override_background_color(drop_area, GTK_STATE_FLAG_NORMAL, &color);
    
    gtk_drag_dest_set(drop_area, GTK_DEST_DEFAULT_ALL, NULL, 0, GDK_ACTION_COPY);
    gtk_drag_dest_add_uri_targets(drop_area);
    g_signal_connect(drop_area, "drag-data-received", G_CALLBACK(on_drag_data_received), NULL);
    
    gtk_box_pack_start(GTK_BOX(vbox), drop_area, FALSE, FALSE, 0);
    
    file_label = gtk_label_new("No file selected");
    gtk_box_pack_start(GTK_BOX(vbox), file_label, FALSE, FALSE, 0);
    
    button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); 
    gtk_box_set_homogeneous(GTK_BOX(button_box), TRUE); 
    
    csv_button = gtk_button_new_with_label("Convert to CSV");
    tsv_button = gtk_button_new_with_label("Convert to TSV");
    
    gtk_widget_set_sensitive(csv_button, FALSE);
    gtk_widget_set_sensitive(tsv_button, FALSE);
    
    g_signal_connect(csv_button, "clicked", G_CALLBACK(on_csv_conversion), NULL);
    g_signal_connect(tsv_button, "clicked", G_CALLBACK(on_tsv_conversion), NULL);
    
    gtk_container_add(GTK_CONTAINER(button_box), csv_button);
    gtk_container_add(GTK_CONTAINER(button_box), tsv_button);
    
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);
    
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("com.example.fileconverter", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    if (input_file_path) {
        g_free(input_file_path);
    }
    
    return status;
}