// Robby Hallock
// Group A
// robert.hallock@okstate.edu
// 3/2/2022

// scoreBoard.c header file

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
void createScoreBoard(int isMultiplayer);
void insertSinglePlayer(char* first, char* last, char* country, int score, int words, int added);
void insertMultiPlayer(char* first, char* last, char* country, int score, char* result, int words, int added);
#endif