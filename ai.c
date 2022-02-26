#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char* a, char* b){
    char tmp[64];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}

char* removeWord(int i, char** words, int* n){
    swap(words[i], words[*n-1]);
    char* temp = words[*n-1];
    *n = *n-1;
    words = realloc(words, sizeof(char*)*(*n));
    return temp;
}

void checkWords(char* word, char** words, int* n){
    for (int i = 0; i < *n; i++){
        if (!strcmp(word, words[i])){
            free(removeWord(i, words, n));
            break;
        }
    }
}

char* getWord(char** words, int* n){
    
    char* temp;
    return temp;
}

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