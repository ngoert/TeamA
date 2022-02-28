#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
/*
#include "Scoreboard.h"
#include "play.h"
#include "playerInfo.h"
*/
#include "checkWord.h"
#include "substring.h"
#include "ai.h"
#define MAX 80
#define PORT 8081
#define SA struct sockaddr
   
// Driver function
int main()
{
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


    while(1){
        printf("Guessed words:\n");
        for(int i = 0; i < numGuessedWords; i++){
            printf("%s\n", guessedWords[i]);
        }
        
        while(1){
        // Players turn
        printf("Letters: %s\n", scramble);
        strcpy(playerInput, "1");
        int fd[2];
        time_t t = time(NULL);
        pipe(fd);
        fcntl(fd[0], F_SETFL, O_NONBLOCK);
        pid_t pid = fork();
        if (pid){
            close(fd[1]);
            while (time(NULL) - t < 20 && !strcmp(playerInput, "1")){
                read(fd[0], &playerInput, sizeof(playerInput));
            }
            close(fd[0]);
            kill(pid, SIGTERM);
            wait(NULL);
        } else {
            close(fd[0]);
            scanf("%s", playerInput);
            write(fd[1], &playerInput, sizeof(playerInput));
            close(fd[1]);
            exit(0);
        }
        if(!strcmp(playerInput, "1") || !strcmp(playerInput, "0")) {
            numPlayerPasses++;
            break;
        } else {
            if (isPossible(playerInput, scramble) && substring(playerInput, guessedWords[numGuessedWords-1])){
                if (isValid(playerInput, input)){
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

