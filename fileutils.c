#include <stdio.h>
#include <stdlib.h>

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

