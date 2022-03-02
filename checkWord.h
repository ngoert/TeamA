// Robby Hallock
// Group A
// robert.hallock@okstate.edu
// 3/2/2022

// checkWord.c header file

#ifndef CHECKWORD_H
#define CHECKWORD_H
char* getInput();
char* getScramble(char* input);
int isInInput(char* input, char* word);
int isInDictionary(char* word, char* input);
//int isValid(char* word, char* input);
void changeCase(char* word, int toCapital);
int isPossible(char* word, char* scramble);
char** getPossible(char* input, int* totalWords);
int inStringArray(char* word, char** wordList, int size);
#endif
