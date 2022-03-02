#include <stdio.h>
#include <string.h>
#include "checkWord.h"

int substring(char* word, char* word2)
{
    changeCase(word, 1);
    changeCase(word2, 1);
    int matches = 0;
    for (int i = strlen(word2); i > -1; i--){
        if (word2[i] == word[0]){
            matches = 1;
            for (int j = i; j < strlen(word2); j++){
                if (word2[j] != word[j-i]) matches = 0;
            }
            if (matches) return 1;
        }
    }

    return 0;
}

int isInDictionaryFunction(char* search){
    changeCase(search, 0);
    FILE* filePointer;
    int wordExist=0;
    int bufferLength = 255;
    char word[100];
    char line[bufferLength];
    filePointer = fopen("dictionary.txt", "r");
    while(fscanf(filePointer, "%s", line) != EOF) {
        if (!strcmp(line, search)) {
            wordExist=1;
            break;
        }
    }
    fclose(filePointer);

    return wordExist;
}