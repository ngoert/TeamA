#include <stdio.h>
#include <string.h>

#define FIRST 10
#define LAST 9
#define COUNTRY 7

/** Creates Scoreboard if one doesn't exist */

void createScoreBoard(int isMultiPlayer){
    FILE * file;
    char temp[256];
    if (isMultiPlayer){
        if (!(file = fopen("multiPlayer.txt", "r"))) {
            file = fopen("multiPlayer.txt", "w");
            sprintf(temp, " %*s  %*s  %*s  %*s  %*s  %*s  %*s\n", FIRST, "First name", LAST, "Last name", COUNTRY, "Country", 5, "Score", 8, "Win/Lose", 21, "Number of words found", 21, "Number of words added");
            fwrite(temp, sizeof(char), strlen(temp), file);
            strcpy(temp, "-----------------------------------------------------------------------------------------------\n");
            fwrite(temp, sizeof(char), strlen(temp), file);
        }
    } else {
        if (!(file = fopen("singlePlayer.txt", "r"))) {
            file = fopen("singlePlayer.txt", "w");
            sprintf(temp, " %*s  %*s  %*s  %*s  %*s  %*s\n", FIRST, "First name", LAST, "Last name", COUNTRY, "Country", 5, "Score", 21, "Number of words found", 21, "Number of words added");
            fwrite(temp, sizeof(char), strlen(temp), file);
            strcpy(temp, "-------------------------------------------------------------------------------------\n");
            fwrite(temp, sizeof(char), strlen(temp), file);
        }
    }
    fclose(file);
}

/** writes entry into singlePlayer.txt */

void appendSinglePlayer(char* first, char* last, char* country, int score, int words, int added){
    FILE * file = fopen("singlePlayer.txt", "a");
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

/** writes entry into multiPlayer.txt */

void appendMultiPlayer(char* first, char* last, char* country, int score, char* result, int words, int added){
    FILE * file = fopen("multiPlayer.txt", "a");
    char temp[512];
    int firstOffset, lastOffset, countryOffset, scoreOffset, wordsOffset, addedOffset;
    firstOffset = (strlen(first) + FIRST)/2;
    lastOffset = (strlen(last) + LAST)/2 + FIRST-firstOffset;
    countryOffset = (strlen(country) + COUNTRY)/2 + LAST - lastOffset + FIRST - firstOffset;
    scoreOffset = 3 + LAST - lastOffset + FIRST - firstOffset + COUNTRY - countryOffset;
    sprintf(temp, " %*s  %*s  %*s  %*d  %*s  %*d  %*d\n", firstOffset, first, lastOffset, last, countryOffset, country, scoreOffset, score, 8, result, 13, words, 21, added);
    fwrite(temp, sizeof(char), strlen(temp), file);
    fclose(file);
}

/** Insert player into appropriate slot in singlePlayer*/

void insertSinglePlayer(char* first, char* last, char* country, int score, int words, int added){
    FILE * file = fopen("singlePlayer.txt", "r");
    char tempFirst[6][11], tempLast[6][10], tempCountry[6][8], header[256], header2[256];
    int tempScore[6], tempWords[6], tempAdded[6], i, isNotFull, isNotInserted;
    fgets(header, 86, file);
    fgets(header2, 87, file);
    isNotFull = 0;
    isNotInserted = 1;
    i=0;
    while (i < 5) {
        if (fscanf(file, "%s%s%s%d%d%d", tempFirst[i], tempLast[i], tempCountry[i], &tempScore[i], &tempWords[i], &tempAdded[i]) == EOF) {
            isNotFull++;
            break;
        }
        i++;
    }
    fclose(file);
    for (int j = 0; j < i; j++){
        if (score > tempScore[j]){
            isNotInserted--;
            for (int k = i-2+isNotFull; k > j-1; k--){
                strcpy(tempFirst[k+1], tempFirst[k]);
                strcpy(tempLast[k+1], tempLast[k]);
                strcpy(tempCountry[k+1], tempCountry[k]);
                tempScore[k+1] = tempScore[k];
                tempWords[k+1] = tempWords[k];
                tempAdded[k+1] = tempAdded[k];
            }
            strcpy(tempFirst[j], first);
            strcpy(tempLast[j], last);
            strcpy(tempCountry[j], country);
            tempScore[j] = score;
            tempWords[j] = words;
            tempAdded[j] = added;
            break;
        }
    }
    if (isNotInserted && isNotFull) {
        strcpy(tempFirst[i], first);
        strcpy(tempLast[i], last);
        strcpy(tempCountry[i], country);
        tempScore[i] = score;
        tempWords[i] = words;
        tempAdded[i] = added;
    }
    file = fopen("singlePlayer.txt", "w");
    fwrite(header, sizeof(char), strlen(header), file);
    fwrite(header2, sizeof(char), strlen(header2), file);
    fclose(file);
    for (int j = 0; j < i+isNotFull; j++) appendSinglePlayer(tempFirst[j], tempLast[j], tempCountry[j],tempScore[j],tempWords[j],tempAdded[j]);
}

/** Insert player into appropriate slot in multiPlayer*/

void insertMultiPlayer(char* first, char* last, char* country, int score, char* result, int words, int added){
    FILE * file = fopen("multiPlayer.txt", "r");
    char tempFirst[6][11], tempLast[6][10], tempCountry[6][8], tempResult[6][5], header[256], header2[256];
    int tempScore[6], tempWords[6], tempAdded[6], i, isNotFull, isNotInserted;
    fgets(header, 96, file);
    fgets(header2, 97, file);
    isNotFull = 0;
    isNotInserted = 1;
    i=0;
    while (i < 5) {
        if (fscanf(file, "%s%s%s%d%s%d%d", tempFirst[i], tempLast[i], tempCountry[i], &tempScore[i], tempResult[i], &tempWords[i], &tempAdded[i]) == EOF) {
            isNotFull++;
            break;
        }
        i++;
    }
    fclose(file);
    for (int j = 0; j < i; j++){
        if (score > tempScore[j]){
            isNotInserted--;
            for (int k = i-2+isNotFull; k > j-1; k--){
                strcpy(tempFirst[k+1], tempFirst[k]);
                strcpy(tempLast[k+1], tempLast[k]);
                strcpy(tempCountry[k+1], tempCountry[k]);
                tempScore[k+1] = tempScore[k];
                strcpy(tempResult[k+1], tempResult[k]);
                tempWords[k+1] = tempWords[k];
                tempAdded[k+1] = tempAdded[k];
            }
            strcpy(tempFirst[j], first);
            strcpy(tempLast[j], last);
            strcpy(tempCountry[j], country);
            tempScore[j] = score;
            strcpy(tempResult[j], result);
            tempWords[j] = words;
            tempAdded[j] = added;
            break;
        }
    }
    if (isNotInserted && isNotFull) {
        strcpy(tempFirst[i], first);
        strcpy(tempLast[i], last);
        strcpy(tempCountry[i], country);
        tempScore[i] = score;
        strcpy(tempResult[i], result);
        tempWords[i] = words;
        tempAdded[i] = added;
    }
    file = fopen("multiPlayer.txt", "w");
    fwrite(header, sizeof(char), strlen(header), file);
    fwrite(header2, sizeof(char), strlen(header2), file);
    fclose(file);
    for (int j = 0; j < i+isNotFull; j++) appendMultiPlayer(tempFirst[j], tempLast[j], tempCountry[j], tempScore[j], tempResult[j], tempWords[j], tempAdded[j]);
}
