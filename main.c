#include <stdio.h>
#include <stdlib.h>

int main()
{
    void cleanBuffer();
    char readFile();
    void writeFile();
    void alterFile();
    char* writeFileName();
    
    printf("Do you want read[1], write[2] or  alter[3] the file csv?");
    int answ;
    scanf("%i", &answ);
    
    switch (answ){
        case 1:
            char *fileName = writeFileName(fileName);
            readFile(fileName);
            free(fileName);
            break;
        case 2: 
            char *fileName = writeFileName();
            writeFile(fileName);
            break;
        case 3:
            char *fileName = writeFileName();
            alterFile(fileName);
            break;
        default:
            printf("invalid command");
            break;
        
    }
    
    return 0;
}

void cleanBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char readFile(char *fileName){
    FILE *fptr = fopen(fileName, "r");
    
    if(fptr == NULL){
        perror("open file error");
        exit(EXIT_FAILURE);
    }
    
    char *file_read[300];
    while(fgets(file_read, sizeof(file_read), fptr) != NULL) {
        printf("%s", file_read);
    }

    return file_read;
}

void writeFile(char *fileName){
    FILE *file = fopen(fileName, "w");
    
    if(file == NULL){
        printf("open file error");
        return 0;
    }
    
    char x[500];
    printf("Write: \n");
    fgets(x, sizeof(x), stdin);


    return 0;
}

void alterFile(){
    
}

char* writeFileName(){

    unsigned int strpspn();

    char *x;
    int size = 30;
    
    x = malloc(size * sizeof(char));
    
    if (x == NULL){
        fprintf(stderr, "memory allocation error");
        exit(EXIT_FAILURE);
    }
    
    printf("Write file name:\n");
    fgets(x, size, stdin);
    x[strpspn(x, "\n")] = '\0';

    
    return x;
}

unsigned int strpspn(const char *x, const char *y){
    unsigned int a, b;

    for(a = 0; x[a] != '\0'; a++){
        for(b = 0; y[b] != '\0'; b++){
            if(x[a] == y[b]){
                return a;
            }
        }
    }
    return a;
}

