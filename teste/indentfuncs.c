/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indentfuncs.c
 */
/* Funções e Main */

#include "indent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

const char * indent(struct ast *a) {

  char * strLL = "";
  char * strRR = "";
  char * strLeft = "";
  char * strRight = "";
  char * strRoot = "";
  char * strReturn = "";


  switch(a->nodetype) {

    /* programa */
    /* stmt-seq */

    /* stmt-seq */
    /* stmt-seq TSEM stmt */
    case ';':
      printf(";");
      strLeft = indent(a->l);
      strRoot = " ; ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;


    /* if-stmt */
    /* TIF exp TTHEN stmt-seq TENDIF */
    case AIf:
      strLL = "if ";
      strLeft = indent(a->l);
      strRoot = " then\n";
      strRight = indent(a->r);
      strRR = " tendif\n";
      strcat(strReturn, strLL);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      strcat(strReturn, strRR);
      break;


    /* while-stmt */
    /* TWHILE exp TDO stmt-seq TENDDO */
    case AWhile:
      strLL = "while ";
      strLeft = indent(a->l);
      strRoot = " do\n";
      strRight = indent(a->r);
      strRR = " enddo\n";
      strcat(strReturn, strLL);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      strcat(strReturn, strRR);
      break;


    /* assign-stmt */
    /* TID TASSIGN exp */
    case AAssign:
      printf("AAssign");
      strLeft = ((struct astAssign *)a)->id;
      strRoot = " := ";
      strRight = indent(((struct astAssign *)a)->exp);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;


    /* read-stmt */
    /* TREAD TID */
    case ARead:
      printf("ARead");
      strLeft = "read ";
      strRight = ((struct astRead *)a)->id;
      strcat(strReturn, strLeft);
      strcat(strReturn, strRight);
      break;


    /* write-stmt */
    /* TWRITE exp */
    case AWrite:
      printf("AWrite");
      strLeft = "write ";
      strRight = indent(((struct astWrite *)a)->exp);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRight);
      break;



    /* exp */
    /* simple-exp TSMA simple-exp */
    case '<':
      strLeft = indent(a->l);
      strRoot = '<';
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp TBIG simple-exp */
    case '>':
      strLeft = indent(a->l);
      strRoot = '>';
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp TEQ simple-exp */
    case '=':
      strLeft = indent(a->l);
      strRoot = '=';
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp */
    /* simple-exp TSUM termo */
    case '+':
      strLeft = indent(a->l);
      strRoot = '+';
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp TSUB termo */
    case '-':
      strLeft = indent(a->l);
      strRoot = '-';
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* termo */
    /* simple-exp TMUL fator */
    case '*':
      strLeft = indent(a->l);
      strRoot = '*';
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp TDIV fator */
    case '/':
      strLeft = indent(a->l);
      strRoot = '/';
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;


    /* fator */
    /* TOPP exp TCLP */
    case APar:
      strLeft = "(";
      strRoot = indent(((struct astPar *)a)->exp);
      strRight = ")";
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* TNUM */
    case ANum:
      strRoot = ((struct astNum *)a)->num;
      strcat(strReturn, strRoot);
      break;

    /* TID */
    case AId:
      strRoot = ((struct astId *)a)->id;
      strcat(strReturn, strRoot);
      break;

    default:
      printf("internal error: bad node %c\n", a->nodetype);
  }
  return strReturn;
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
