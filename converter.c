#include <stdio.h>
#include <stdlib.h>
#include "fileutils.h"

int TXTtoCSV(const char *in, const char *out) {
    FILE* filein = fopen(in, "r");
    FILE* fileout = fopen(out, "w");
    
    if(filein == NULL || fileout == NULL){
        perror("open file error");
        return 1;
    }

    char c;
    while ((c = fgetc(filein)) != EOF) {
        if(c == ' '){
            fputc(',', fileout);
        }else{
            fputc(c, fileout);
        }
    }

    fclose(filein);
    fclose(fileout);
    return 0;

}

int TXTtoTSV(const char *in, const char *out) {
    FILE* filein = fopen(in, "r");
    FILE* fileout = fopen(out, "w");
    
    if(filein == NULL || fileout == NULL){
        perror("open file error");
        return 1;
    }

    char c;
    while ((c = fgetc(filein)) != EOF) {
        if(c == ' '){
            fputc('\t', fileout);
        }else{
            fputc(c, fileout);
        }
    }

    fclose(filein);
    fclose(fileout);
    return 0;

}

int BMPtoTXT(const char *in, const char *out) {
    FILE* filein = fopen(in, "rb");
    FILE* fileout = fopen(out, "w");

    if(filein == NULL || fileout == NULL){
        perror("open file error");
        return 1;
    }

    unsigned char header[54];
    if (fread(header, sizeof(unsigned char), 54, filein) != 54) {
        fprintf(stderr, "Error reading BMP header\n");
        fclose(filein);
        fclose(fileout);
        return 1;
    }
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    short bitDepth = *(short*)&header[28];

    fprintf(fileout, "Width: %d px\n", width);
    fprintf(fileout, "Height: %d px\n", height);
    fprintf(fileout, "Bit Depth: %d\n", bitDepth);

    fclose(filein);
    fclose(fileout);
}