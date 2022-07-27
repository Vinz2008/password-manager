#include <stdio.h>

int is_space(unsigned char c);

int is_term(unsigned char c);

int getLineCSV(char** lineParsed, FILE* fptr);

void CSVToString(char** CSVList,int CSVListLength, char* str);