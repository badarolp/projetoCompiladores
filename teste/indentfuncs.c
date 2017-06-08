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

  //char * teste = "read x; if x > 0 then fat := 1; while x > 0 do fat := fat * x; x := x - 1 enddo write fat; endif";
  //printf(teste);
  return yyparse( );
}
