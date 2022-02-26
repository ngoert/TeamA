#ifndef AI_H
#define AI_H
char** getWords(char* input, int* n);
void swap(char* a, char* b);
char* removeWord(int i, char** words, int* n);
void checkWords(char* word, char** words, int* n);
char* getWord(char** words, int* n);
#endif