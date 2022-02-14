/*
TEMPORARY AND MAY CAUSE ERRORS
*/

#include <stdio.h>
#include <string.h>

#define FIRST 10
#define LAST 9
#define COUNTRY 7

/** writes entry into scoreboard */

void appendScoreBoard(char* first, char* last, char* country, int score, int words, int added){
    FILE * file = fopen("scoreboard.txt", "a");
    char temp[256];
    int firstOffset, lastOffset, countryOffset, scoreOffset, wordsOffset, addedOffset;
    firstOffset = (strlen(first) + FIRST)/2;
    lastOffset = (strlen(last) + LAST)/2 + FIRST-firstOffset;
    countryOffset = (strlen(country) + COUNTRY)/2 + LAST - lastOffset + FIRST - firstOffset;
    scoreOffset = 3 + LAST - lastOffset + FIRST - firstOffset + COUNTRY - countryOffset;
    sprintf(temp, " %*s  %*s  %*s  %*d  %*d  %*d\n", firstOffset, first, lastOffset, last, countryOffset, country, scoreOffset, score, 13, words, 21, added);
    fwrite(temp, sizeof(char), strlen(temp), file);
    fclose(file);
}

/** Creates Scoreboard if one doesn't exist */

void createScoreBoard(){
    FILE * file;
    char temp[256];
    if (!(file = fopen("scoreboard.txt", "r"))) {
        file = fopen("scoreboard.txt", "w");
        sprintf(temp, " %*s  %*s  %*s  %*s  %*s  %*s\n", FIRST, "First name", LAST, "Last name", COUNTRY, "Country", 5, "Score", 21, "Number of words found", 21, "Number of words added");
        fwrite(temp, sizeof(char), strlen(temp), file);
        strcpy(temp, "-------------------------------------------------------------------------------------\n");
        fwrite(temp, sizeof(char), strlen(temp), file);
    }
    fclose(file);
}

/** Insert player into appropriate slot */

void insertScoreBoard(char* first, char* last, char* country, int score, int words, int added){
    FILE * file = fopen("scoreboard.txt", "r");
    char tempFirst[6][11], tempLast[6][10], tempCountry[6][8], header[256], header2[256];
    int tempScore[6], tempWords[6], tempAdded[6], i, flag, flag2;
    fgets(header, 86, file);
    fgets(header2, 87, file);
    
    flag = 1;
    flag2 = 1;
    i=1;
    while (i < 6) {
        if (fscanf(file, "%s%s%s%d%d%d", tempFirst[i-flag], tempLast[i-flag], tempCountry[i-flag], &tempScore[i-flag], &tempWords[i-flag], &tempAdded[i-flag]) == EOF){
            flag2--;
            break;
        }
        if (score > tempScore[i-1] && flag){
            strcpy(tempFirst[i], tempFirst[i-1]);
            strcpy(tempLast[i], tempLast[i-1]);
            strcpy(tempCountry[i], tempCountry[i-1]);
            tempScore[i] = tempScore[i-1];
            tempWords[i] = tempWords[i-1];
            tempAdded[i] = tempAdded[i-1];
            
            strcpy(tempFirst[i-1], first);
            strcpy(tempLast[i-1], last);
            strcpy(tempCountry[i-1], country);
            tempScore[i-1] = score;
            tempWords[i-1] = words;
            tempAdded[i-1] = added;
            flag--;
        }
        i++;
    }
    if (flag) {
        strcpy(tempFirst[i-1], first);
        strcpy(tempLast[i-1], last);
        strcpy(tempCountry[i-1], country);
        tempScore[i-1] = score;
        tempWords[i-1] = words;
        tempAdded[i-1] = added;
    }
    i = i - flag2;
    fclose(file);
    file = fopen("scoreboard.txt", "w");
    //sprintf(temp, " %*s  %*s  %*s  %*s  %*s  %*s\n", FIRST, "First name", LAST, "Last name", COUNTRY, "Country", 5, "Score", 21, "Number of words found", 21, "Number of words added");
    fwrite(header, sizeof(char), strlen(header), file);
    //strcpy(temp, "-------------------------------------------------------------------------------------\n");
    fwrite(header2, sizeof(char), strlen(header2), file);
    fclose(file);
    for (int j = 0; j < i; j++) appendScoreBoard(tempFirst[j], tempLast[j], tempCountry[j], tempScore[j], tempWords[j], tempAdded[j]);
}

int main()
{
    createScoreBoard();
    /*
    writeScoreBoard("John", "Doe", "Russia", 15, 32, 1);
    writeScoreBoard("Diane", "zamorack", "USA", 5, 2, 16);
    writeScoreBoard("a", "b", "c", 5, 2, 16);
    writeScoreBoard("asdfasdfas", "asdfasdfa", "asdfasd", 1, 1, 1);
    */
    insertScoreBoard("test", "test", "test", 16, 1, 1);
    insertScoreBoard("John", "Doe", "Russia", 15, 32, 1);

    return 0;
}
