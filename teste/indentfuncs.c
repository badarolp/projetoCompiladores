#include "indent.h"
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>

/* C code */

int computeSymbolIndex(char token) {
  int idx = -1;
  if(islower(token)) {
    idx = token - 'a' + 26;
  } else if(isupper(token)) {
    idx = token - 'A';
  }
  return idx;
}

/* returns the value of a given symbol */
int symbolVal(char symbol) {
  int bucket = computeSymbolIndex(symbol);
  return symbols[bucket];
}

/* updates the value of a given symbol */
void updateSymbolVal(char symbol, int val) {
  int bucket = computeSymbolIndex(symbol);
  symbols[bucket] = val;
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);}

int main (int argc, char *argv[]) {
  /* init symbol table */
  int i;
  for(i=0; i<52; i++) {
    symbols[i] = 0;
  }

  char *file_contents;
  long input_file_size;
  FILE *input_file = fopen("fat.t", "rb");
  fseek(input_file, 0, SEEK_END);
  input_file_size = ftell(input_file);
  rewind(input_file);
  file_contents = malloc(input_file_size * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, input_file);
  fclose(input_file);

  return yyparse();
}
