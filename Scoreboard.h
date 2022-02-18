//header file for Scoreboard.c

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
void createScoreBoard(int isMultiplayer);
void insertSinglePlayer(char* first, char* last, char* country, int score, int words, int added);
void insertMultiPlayer(char* first, char* last, char* country, int score, char* result, int words, int added);
#endif