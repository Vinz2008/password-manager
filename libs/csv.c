#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_space(unsigned char c) {
  if (c == ' ' || c == 0x09) return 1; 
  return 0;
}

int is_term(unsigned char c) {
  if (c == '\r' || c == '\n') return 1;
  return 0;
}

int getLineCSV(char** lineParsed, FILE* fptr){
  char* tok;
  char line[1000];
  int i = 0;
  printf("test1\n");
  if (fgets(line, 1000, fptr)){
    tok = strtok(line, ";");
    while (tok != NULL){
      printf("tok : %s\n", tok);
      lineParsed[i] = malloc(1000 * sizeof(char));
      strcpy(lineParsed[i], tok);
      i++;
      tok = strtok(NULL, ";");
    }
  return 1;
  }
  return 0;
}