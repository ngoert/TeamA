#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/** gets possible words from input file */

char** getWords(char* input, int* n){
    char word[256];
    *n = 0;
    char** words;
    FILE* file = fopen(input, "r");
	
	// Clear first 3 words
	
    fscanf(file, "%s", word);
    fscanf(file, "%s", word);
    fscanf(file, "%s", word);
	
	// Loop through input file and add each word to array
	
    while(fscanf(file, "%s", word) != EOF) {
        (*n)++;
        words = realloc(words, sizeof(char*)*(*n));
        words[*n-1] = malloc(sizeof(char)*(strlen(word)+1));
        strcpy(words[*n-1], word);
    }
    fclose(file);
    return words; // Return array
}
