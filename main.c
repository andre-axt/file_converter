#include <stdio.h>
#include <stdlib.h>
#include "fileutils.h";

int main()
{
    
}

void cleanBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

