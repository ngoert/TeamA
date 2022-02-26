#ifndef CHECKWORD_H
#define CHECKWORD_H
char* getInput();
char* getScramble(char* input);
int isInInput(char* input, char* word);
int isInDictionary(char* search);
int isValid(char* word, char* input);
void changeCase(char* word, int toCapital);
#endif