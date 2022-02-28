#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "checkWord.h"
#include "substring.h"
#include "ai.h"
   
// Driver function
int playGame(int connf)
{
    //int points = 0;
    char buffer[1028];
	char * temp = malloc(256);
    char input[256] = "input_01.txt";
    char* scramble = getScramble(input);
    int points, numPlayerPasses, numCPUPasses;
    numCPUPasses = 0;
    numPlayerPasses = 0;
    points = 0;
    char** guessedWords = malloc(sizeof(char*));
    int numGuessedWords = 1;
    int numPossible;
    char** wordList = getPossible(input, &numPossible);
    char playerInput[256] = "1";
    guessedWords[numGuessedWords-1] = malloc(sizeof(char)+1);
    strcpy(guessedWords[numGuessedWords-1], scramble);
    guessedWords[numGuessedWords-1][1] = '\0';
    //char temp[256];

    while(1){
        strcpy(buffer, "Guessed words:\n");
        //printf("Guessed words:\n");
        for(int i = 0; i < numGuessedWords; i++){
            sprintf(temp, "%s\n", guessedWords[i]);
            strcat(buffer, temp);
        }
        
        while(1){
        // Players turn
        
        sprintf(temp, "Letters: %s\n", scramble);
        strcat(buffer, temp);
	printf("hello");
        write(connf, buffer, sizeof(buffer));
        
        strcpy(playerInput, "1");
        //int fd[2];
        time_t t = time(NULL);
        //pipe(fd);
        fcntl(connf, F_SETFL, O_NONBLOCK);
        //pid_t pid = fork();
        //if (pid){
            //close(fd[1]);
            while (time(NULL) - t < 30 && !strcmp(playerInput, "1")){
                read(connf, &playerInput, sizeof(playerInput));
            }
            //close(fd[0]);
            //kill(pid, SIGTERM);
            //wait(NULL);
        //} else {
            //close(fd[0]);
            //scanf("%s", playerInput);
            //write(fd[1], &playerInput, sizeof(playerInput));
            //close(fd[1]);
            //exit(0);
        //}
        if(!strcmp(playerInput, "1") || !strcmp(playerInput, "0")) {
            numPlayerPasses++;
            break;
        } else {
            if (isPossible(playerInput, scramble) && substring(playerInput, guessedWords[numGuessedWords-1])){
                if (isValid(playerInput, input)){
                    changeCase(playerInput, 1);
                    numPlayerPasses = 0;
                    numGuessedWords++;
                    guessedWords = realloc(guessedWords, sizeof(char*)*numGuessedWords);
                    guessedWords[numGuessedWords-1] = malloc(strlen(playerInput+1));
                    strcpy(guessedWords[numGuessedWords-1], playerInput);
                    break;
                }
            }
        }
        }
            

        // CPU turn
        int CPUPasses = 1;
        for (int i = 0; i < numPossible; i++){
            if (!(inStringArray(wordList[i], guessedWords, numGuessedWords)) && substring(wordList[i], guessedWords[numGuessedWords-1])){
                numGuessedWords++;
                guessedWords = realloc(guessedWords, sizeof(char*)*numGuessedWords);
                guessedWords[numGuessedWords-1] = malloc(strlen(playerInput+1));
                strcpy(guessedWords[numGuessedWords-1], wordList[i]);
                numCPUPasses = 0;
                break;
            }
        }
        if (CPUPasses) numCPUPasses++;
        
        
        if (numPlayerPasses > 1 && numCPUPasses > 1) break;
        
    }
	
}
