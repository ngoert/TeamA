// Robby Hallock
// Group A
// robert.hallock@okstate.edu
// 3/2/2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "substring.h"


/** swaps 2 strings */

void swap(char* a, char* b){
    char tmp[64];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}

/** changes case of string */

void changeCase(char* word, int toCapital){
    for (int i = 0; word[i]; i++){ // Loops through each letter
        if (toCapital) word[i] = toupper(word[i]); // Sets each character to upper case if toCapital is 1
        else word[i] = tolower(word[i]); // // Sets each character to lower case if toCapital is 0
    }
}

/** checks if letters in sting are in scramble */

int isPossible(char* word, char* scramble){
    changeCase(word, 1);
    int noMatch = 0;
    int size = strlen(scramble);
    for(int i = 0; i < strlen(word); i++){ // Loops through each letter of the word
        noMatch = 1;
        for (int j = 0; j < size; j++){ // Loops through each letter of scramble
			
			// If match move on
		
            if (word[i] == scramble[j]){
                noMatch = 0;
                break;
            }
        }
        if (noMatch) return 0; // Return false if there is any letter thats not in scramble

    }
    return 1;
}

/** gets scramble from input file */

char* getScramble(char* input){
    FILE* file = fopen(input, "r");
    char* scramble = malloc(256);
    fscanf(file, "%s", scramble);
    fclose(file);
    return scramble;
}

/** checks if a string is in an array */

int inStringArray(char* word, char** wordList, int size){
	
	// Loops through string array
	
    for (int i = 0; i < size; i++){
        if (!strcmp(word, wordList[i])) return 1; // Return true if a matches is found
    }
    return 0;
}

/** returns an array of all possible words from input file */

char** getPossible(char* input, int* totalWords){
    char ** wordList = malloc(0); // Array to return
    *totalWords = 0;
    FILE* file = fopen(input, "r");
    char* temp = malloc(256);
	
	// Clears first 3 lines
	
    fgets(temp, 256, file);
    fgets(temp, 256, file);
    fgets(temp, 256, file);
	
	// Loops through each word and adds to array
	
    while(fscanf(file, "%s", temp) != EOF){
        (*totalWords)++;
        wordList = realloc(wordList, sizeof(char*)*(*totalWords));
        wordList[*totalWords-1] = malloc(strlen(temp)+1);
        strcpy(wordList[*totalWords-1], temp);
    }
    fclose(file);
    free(temp);
    return wordList;
}

/** checks if string is in input file */

int isInInputFunction(char* input, char* word){
	changeCase(word, 1);
    FILE* file = fopen(input, "r");
    char* temp = malloc(256);
	
	// Clear first 3 lines
	
    fgets(temp, 256, file);
    fgets(temp, 256, file);
    fgets(temp, 256, file);
	
	// Scan each word
	
    while(fscanf(file, "%s", temp) != EOF){
        if (!strcmp(word, temp)) { // If match return true
            fclose(file);
            return 1;
        } 
    }
	
	// If no matches return false
	
    fclose(file);
    free(temp);
    return 0;
}


/** creates forked process to check input file for word */

int isInInput(char* input, char* word){
	
	// Make pipe
	
	int inputPipe[2];
    pipe(inputPipe);
	
    int isFound;
    
	// Fork
	
    if(fork()){ // Parent
        close(inputPipe[1]);
        read(inputPipe[0], &isFound, sizeof(isFound)); // Read from pipe result child sends
        close(inputPipe[0]);
        wait(NULL); // wait for child to finish
		return isFound; // returns result
    } else { // Child
        close(inputPipe[0]);
        isFound = isInInputFunction(input, word); // Executes function to check if word is in input file
        write(inputPipe[1], &isFound, sizeof(isFound)); // Writes the word to pipe for parent
        close(inputPipe[1]);
        exit(EXIT_SUCCESS); // Exits
    }
}

/** creates forked process to find word in dictionary */

int isInDictionary(char* word, char* input){
	
    int isFound;
	
	// Creates pipe
	
    int dictPipe[2];
    pipe(dictPipe);
	
	// Fork
    
    if (fork()){ // Parent
        close(dictPipe[1]);
        read(dictPipe[0], &isFound, sizeof(isFound)); // Read result from child
        close(dictPipe[0]);
        wait(NULL); // Waits for child to finish
        return isFound; // Returns the result
    } else { // Child
        close(dictPipe[0]);
        isFound = isInDictionaryFunction(word); // Performs function to find word in dictionary
		
		// Adds word to input file if in dictionary
		
		if (isFound){
			FILE* file = fopen(input, "a");
			fwrite("\n", sizeof(char), 1, file);
            changeCase(word, 1);
            fwrite(word, sizeof(char), strlen(word), file);
			fclose(file);
		}
        write(dictPipe[1], &isFound, sizeof(isFound)); // Write result to pipe for parent
        close(dictPipe[1]);
        exit(EXIT_SUCCESS); // Exit
    }
}

/** gets a random input file */

char* getInput(){
    time_t t;
    srand((unsigned) time(&t));
    int number = rand()%10 + 1;
    char* temp = malloc(13);
    if (number < 10) sprintf(temp, "input_0%d.txt", number);
    else sprintf(temp, "input_%d.txt", number);
    return temp;
}

