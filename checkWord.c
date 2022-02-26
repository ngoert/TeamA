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
    if (isInInput(input, word)) return 1;
    int fd[2];
    pipe(fd);
    if (fork()){
        close(fd[1]);
        int val;
        read(fd[0], &val, sizeof(val));
        close(fd[0]);
        wait(NULL);
        if (val) return 2;
        else return 0;
    } else {
        close(fd[0]);
        int val = isInDictionary(word);
        write(fd[1], &val, sizeof(val));
        close(fd[1]);
        if (val){
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
    char* temp = malloc(9);
    if (number < 10) sprintf(temp, "input_0%d", number);
    else sprintf(temp, "input_%d", number);
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
