#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

void changeCase(char* word, int toCapital){
    for (int i = 0; word[i]; i++){
        if (toCapital) word[i] = toupper(word[i]);
        else word[i] = tolower(word[i]);
    }
}

char* getScramble(char* input){
    FILE* file = fopen(input, "r");
    char* scramble = malloc(256);
    fscanf(file, "%s", scramble);
    fclose(file);
    return scramble;
}

int isInDictionary(char* search){
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

int isInInput(char* input, char* word){
    changeCase(word, 1);
    FILE* file = fopen(input, "r");
    char* temp = malloc(256);
    fgets(temp, 256, file);
    fgets(temp, 256, file);
    fgets(temp, 256, file);
    while(fscanf(file, "%s", temp) != EOF){
        if (!strcmp(word, temp)) {
            fclose(file);
            return 1;
        } 
    }
    fclose(file);
    return 0;
}

int isValid(char* word, char* input){
    int inputPipe[2];
    pipe(inputPipe);
    int isFound;
    
    if(fork()){
        close(inputPipe[1]);
        read(inputPipe[0], &isFound, sizeof(isFound));
        close(inputPipe[0]);
        wait(NULL);
    } else {
        close(inputPipe[0]);
        isFound = isInInput(input, word);
        write(inputPipe[1], &isFound, sizeof(isFound));
        close(inputPipe[1]);
        exit(EXIT_SUCCESS);
    }
    
    if (isFound) return 1;
    
    int dictPipe[2];
    pipe(dictPipe);
    
    if (fork()){
        close(dictPipe[1]);
        read(dictPipe[0], &isFound, sizeof(isFound));
        close(dictPipe[0]);
        wait(NULL);
        if (isFound) return 2;
        else return 0;
    } else {
        close(dictPipe[0]);
        isFound = isInDictionary(word);
        write(dictPipe[1], &isFound, sizeof(isFound));
        close(dictPipe[1]);
        if (isFound){
            FILE* file = fopen(input, "a");
            fwrite("\n", sizeof(char), 1, file);
            changeCase(word, 1);
            fwrite(word, sizeof(char), strlen(word), file);
            fclose(file);
        }
        exit(EXIT_SUCCESS);
    }
}

char* getInput(){
    time_t t;
    srand((unsigned) time(&t));
    int number = rand()%10 + 1;
    char* temp = malloc(13);
    if (number < 10) sprintf(temp, "input_0%d.txt", number);
    else sprintf(temp, "input_%d.txt", number);
    return temp;
}

/*
int main()
{

    time_t t;
    srand((unsigned) time(&t));
    int number = rand()%10 + 1;
    char temp[9];
    if (number < 10) sprintf(temp, "input_0%d", number);
    else sprintf(temp, "input_%d", number);
    printf("%s\n", temp);

    char input[] = "input_01.txt";
    char* scramble = getScramble(input);
    if (checkInput(input, "VIA")) printf("yes");
    else printf("no");
    return 0;
}
*/

/*
EIAHVC

Possible Words:
ACE
EVE
ICE
VIA
CHI
VIE
VAC
CAVE
EACH
HAVE
ACHE
HIVE
CHIVE
HEAVE
ACHIEVE
*/
