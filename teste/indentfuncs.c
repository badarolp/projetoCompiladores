/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indentfuncs.c
 */
/* Funções e Main */

#include "indent.h"
#include <stdio.h>
#include <stdlib.h>

struct ast * mkNode(struct ast *l, int nodetype, struct ast *r) {
  struct ast *a = malloc(sizeof(struct ast));
  a->nodetype = nodetype;
  a->l = l;
  a->r = r;
  return a;
}

struct ast * mkNodeAssign(char id, struct ast *exp) {
  struct astAssign *a = malloc(sizeof(struct astAssign));
  a->nodetype = AAssign;
  a->id = id;
  a->exp = exp;
  return a;
}

struct ast * mkNodeRead(char id) {
  struct astRead *a = malloc(sizeof(struct astRead));
  a->nodetype = ARead;
  a->id = id;
  return a;
}

struct ast * mkNodeWrite(struct ast *exp) {
  struct astWrite *a = malloc(sizeof(struct astWrite));
  a->nodetype = AWrite;
  a->exp = exp;
  return a;
}

struct ast * mkNodePar(struct ast *exp) {
  struct astPar *a = malloc(sizeof(struct astPar));
  a->nodetype = APar;
  a->exp = exp;
  return a;
}

struct ast * mkNodeNum(int num) {
  struct astNum *a = malloc(sizeof(struct astNum));
  a->nodetype = ANum;
  a->num = num;
  return a;
}

struct ast * mkNodeId(char id) {
  struct astId *a = malloc(sizeof(struct astId));
  a->nodetype = AId;
  a->id = id;
  return a;
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);}

int main (int argc, char *argv[]) {
  /*
  char *file_contents;
  long input_file_size;
  FILE *input_file = fopen("fat.t", "rb");
  fseek(input_file, 0, SEEK_END);
  input_file_size = ftell(input_file);
  rewind(input_file);
  file_contents = malloc(input_file_size * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, input_file);
  fclose(input_file);
  */
  return yyparse();
}
