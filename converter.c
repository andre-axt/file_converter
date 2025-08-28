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