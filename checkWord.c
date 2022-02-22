#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* getScramble(char* input){
    FILE* file = fopen(input, "r");
    char* scramble = malloc(256);
    fgets(scramble, 256, file);
    fclose(file);
    return scramble;
}

int checkInput(char* input, char* word){
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

int main()
{
    /*
    time_t t;
    srand((unsigned) time(&t));
    int number = rand()%10 + 1;
    char temp[9];
    if (number < 10) sprintf(temp, "input_0%d", number);
    else sprintf(temp, "input_%d", number);
    printf("%s\n", temp);
    */
    char input[] = "input_01.txt";
    char* scramble = getScramble(input);
    if (checkInput(input, "VIA")) printf("yes");
    else printf("no");
    return 0;
}

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
