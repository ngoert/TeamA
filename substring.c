// Nicholas Goertemiller
// Group A
// nicholas.goertemiller@okstate.edu
// 3/22/2022

#include <stdio.h>
#include <string.h>
#include "checkWord.h"

int substring(char* word, char* word2)
{
    changeCase(word, 1);
    changeCase(word2, 1);
    int matches = 0;
    for (int i = strlen(word2)-1; i > -1; i--){  // loop backwards over word2 len
        if (word2[i] == word[0]){              // if substrings match, match equals true
            matches = 1;
            for (int j = i; j < strlen(word2); j++){    // loop over previous substrings
                if (word2[j] != word[j-i]) matches = 0; // if substrings are not in word, match equals false
            }
            if (matches) return 1;   // return true
        }
    }

    return 0;  // end of function
}

// read dict.txt file
// search for string
int isInDictionaryFunction(char* search){
    changeCase(search, 0);
    FILE* filePointer;
    int wordExist=0;
    int bufferLength = 255;
    char word[100];
    char line[bufferLength];
    filePointer = fopen("dictionary.txt", "r");
    while(fscanf(filePointer, "%s", line) != EOF) {
        if (!strcmp(line, search)) {            // comapre each line with string; if they don't match go to next,
            wordExist=1;                        // otherwise word is found and return true
            break;
        }
    }
    fclose(filePointer);

    return wordExist;
}
