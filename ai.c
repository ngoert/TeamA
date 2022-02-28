
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** swaps 2 strings */

void swap(char* a, char* b){
    char tmp[64];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}

/** gets possible words from input file */

char** getWords(char* input, int* n){
    char word[256];
    *n = 0;
    char** words;
    FILE* file = fopen(input, "r");
    fscanf(file, "%s", word);
    fscanf(file, "%s", word);
    fscanf(file, "%s", word);
    while(fscanf(file, "%s", word) != EOF) {
        (*n)++;
        words = realloc(words, sizeof(char*)*(*n));
        words[*n-1] = malloc(sizeof(char)*(strlen(word)+1));
        strcpy(words[*n-1], word);
    }
    fclose(file);
    return words;
}
