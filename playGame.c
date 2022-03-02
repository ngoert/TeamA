// Robby Hallock
// Group A
// robert.hallock@okstate.edu
// 3/2/2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "checkWord.h"
#include "substring.h"
#include "scoreBoard.h"

/** Returns a random letter from the input scramble */

char* getRandomLetter(char* scramble){
	time_t t;
	srand((unsigned) time(&t));
	char* letter = malloc(sizeof(char)*2);
	letter[0] = scramble[rand()%strlen(scramble)];
	letter[1] = '\0';
	return letter;
}
   
/** Function to play game with AI where connf is the connection to client and the rest of the input is user details */

int playGame(int connf, char* first, char* last, char* country)
{
	// Variables
	
	time_t t;
	int start, new, isFirst; // booleans
	int words, added, points, numPlayerPasses, numCPUPasses, cpuPoints, numGuessedWords, numPossible, valid, lenOfWord; // ints
	
	// Setting variables
	
	srand((unsigned) time(&t));
	start = 1;
	new = 0;
	isFirst = rand()%2;
	isFirst = 0;
	words = 0;
	added = 0;
	numCPUPasses = 0;
    numPlayerPasses = 0;
    points = 0;
	cpuPoints = 0;
    char buffer[1028];
	char* temp = malloc(256);
    char* input = malloc(256);
	input = getInput();
    char* scramble = getScramble(input);
	char* rdmLetter = getRandomLetter(scramble);
    char** guessedWords = malloc(0);
    numGuessedWords = 0;
    char** wordList = getPossible(input, &numPossible);
    char playerInput[256] = "";
	
	// Main loop

    while(1){
		
		// PLAYER'S TURN
		
		if (isFirst) { // Checks if player is going first
		
			if (!start){ // If not start of game
			
				// Print used/guessed words
				strcpy(buffer, "Used words:\n");
				for(int i = 0; i < numGuessedWords; i++){
					sprintf(temp, "%s\n", guessedWords[i]);
					strcat(buffer, temp);
				}
				
				// If both players have passed once, then set gamestate to new
				
				if (numPlayerPasses > 0 && numCPUPasses > 0){
					new = 1;
					strcat(buffer, "Can start with any letter.\n");
				}
			}else { // If start of game print what the starting letter is
				strcpy(buffer, "Must start with: ");
				strcat(buffer, rdmLetter);
				strcat(buffer, "\n");
			}
			
			// Input loop
			
			while(1){
				
				// Print scramble and points
				
				strcpy(playerInput, "");
				sprintf(temp, "Letters: %s\t\tPoints: %d\t\tOpponent's Points: %d\n", scramble, points, cpuPoints);
				strcat(buffer, temp);
				write(connf, buffer, sizeof(buffer));
				
				// Set current time and connf to nonblocking
				
				t = time(NULL);
				fcntl(connf, F_SETFL, O_NONBLOCK);

				// Gives player 4 minutes to make input
				
				while (time(NULL) - t < 4*60 && !strcmp(playerInput, "")){
					read(connf, &playerInput, sizeof(playerInput));
				}
				
				// Re-enable blocking
				
				fcntl(connf, F_SETFL, fcntl(connf, F_GETFL) & ~O_NONBLOCK);

				playerInput[strlen(playerInput) -1] = '\0'; // fix input
				
				if(!strcmp(playerInput, "")) { // Checks if player passed or ran out of time
					numPlayerPasses++;
					break;
				} else { // If the player gave input
					valid = 0;
					
					// Checks if input is valid
					
					if (start){ // If start of game
						valid = isPossible(playerInput, scramble) && playerInput[0] == rdmLetter[0]; // Checks if letters are in scramble and the first letter matches
					} else { // If not start of game
						valid = isPossible(playerInput, scramble); // Checks if letters are in scramble
						if (valid && !new) valid = substring(playerInput, guessedWords[numGuessedWords-1]); // if not 2 passes, check if beginning matches the end of opponents last word
						if (inStringArray(playerInput, guessedWords, numGuessedWords)) { // If already used word
							points--; // lose 2 points (1 point here and another point for being invalid);
							valid = 0; // set not valid
						}
					}
					
					// Further validity
					
					if (valid){
						valid = 0;
						
						// Checks if English word
						
						if (isInInput(input, playerInput)){ // Checks input file
							valid = 1;
						} else if (isInDictionary(playerInput, input)){ // Checks dictionary
							valid = 1;
							points += 5; // 5 bonus points
							added++; // increase words added to dictionary
						}
						
						// Calculates points
					
						if (valid){
							words++; // found words
							changeCase(playerInput, 1);
							numPlayerPasses = 0;
							
							// adds word to array of guessed/used words
							numGuessedWords++;
							guessedWords = realloc(guessedWords, sizeof(char*)*numGuessedWords);
							guessedWords[numGuessedWords-1] = malloc(strlen(playerInput+1));
							strcpy(guessedWords[numGuessedWords-1], playerInput);
							
							// Calculates points based on length of word
							
							lenOfWord = strlen(playerInput);
							if (lenOfWord >7){
								points += 11;
							} else if (lenOfWord >6) {
								points += 5;
							} else if (lenOfWord >5) {
								points += 3;
							} else if (lenOfWord >4) {
								points += 2;
							} else if (lenOfWord > 2) {
								points++;
							}
							start = 0;
							new = 0;
							break;
						} 
					}
				}
				points--; // -1 point for any invalid word
			}
			if (numPlayerPasses > 1 && numCPUPasses > 1) break; // Ends after 4 connsecutive passes
		}else{
			isFirst = 1;
		}
		
        // CPU'S TURN
		
		if (numPlayerPasses > 0 && numCPUPasses > 0) new = 1; // Checks if 2 passes and sets to new state
        int CPUPasses = 1;
		
		// Loop to find valid word based on input file possible words or pass
		
        for (int i = 0; i < numPossible; i++){
            if (!(inStringArray(wordList[i], guessedWords, numGuessedWords))){ // Makes sure word is not used
				int valid = 0;
				if (start) valid = wordList[i][0] == rdmLetter[0]; // If start of game, make sure first letter matches
				else if (new) valid = 1; // If 2 passes, then any unused word from input file is valid
				else valid = substring(wordList[i], guessedWords[numGuessedWords-1]); // Normally, make sure the beginning of the word matches end of opponents word
				
				// Point calculations
				
				if (valid){
					
					// Add word to used/guessed words
					
					numGuessedWords++;
					guessedWords = realloc(guessedWords, sizeof(char*)*numGuessedWords);
					guessedWords[numGuessedWords-1] = malloc(strlen(wordList[i]+1));
					strcpy(guessedWords[numGuessedWords-1], wordList[i]);
					numCPUPasses = 0;
					CPUPasses = 0;
					start = 0;
					new = 0;
					
					// Calculates points based on length of word
					
					int lenOfWord = strlen(wordList[i]);
					if (lenOfWord >7){
						cpuPoints += 11;
					} else if (lenOfWord >6) {
						cpuPoints += 5;
					} else if (lenOfWord >5) {
						cpuPoints += 3;
					} else if (lenOfWord >4) {
						cpuPoints += 2;
					} else if (lenOfWord > 2) {
						cpuPoints++;
					}
					break;
				}
            }
        }
		
        if (CPUPasses) numCPUPasses++; // Passes if there are no valid words
        
        
        if (numPlayerPasses > 1 && numCPUPasses > 1) break; // Ends game if 4 connsecutive passes
        
    }

	// Writes score to scoreboard if the player wins
	
	if (points > cpuPoints){
		createScoreBoard(0);
		insertSinglePlayer(first, last, country, points, words, added);
	}
}
