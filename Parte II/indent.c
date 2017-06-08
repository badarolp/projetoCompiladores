/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indent.c
 */
/* Funções e Main */

#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include "indent.h"

const char * indent(struct ast *a) {

  char * strLL = "";
  char * strRR = "";
  char * strLeft = "";
  char * strRight = "";
  char * strRoot = ""
  char * strReturn = "";

  if(!a)
    yyerror("internal error, null eval");

  switch(a->nodetype) {

    /* programa */
    /* stmt-seq */

    /* stmt-seq */
    /* stmt-seq TSEM stmt */
    case ';':
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
      strLeft = indent(a->l);
      strRoot = " := ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;


    /* read-stmt */
    /* TREAD TID */
    case ARead:
      strLeft = "read ";
      strRight = indent(a->l);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRight);
      break;


    /* write-stmt */
    /* TWRITE exp */
    case AWhile:
      strLeft = "write ";
      strRight = indent(a->l);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRight);
      break;


    /* exp */
    /* simple-exp TSMA simple-exp */
    case '<':
      strLeft = indent(a->l);
      strRoot = " < ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp TBIG simple-exp */
    case '>':
      strLeft = indent(a->l);
      strRoot = " > ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp TEQ simple-exp */
    case '=':
      strLeft = indent(a->l);
      strRoot = " = ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;


    /* simple-exp */
    /* simple-exp TSUM termo */
    case '+':
      strLeft = indent(a->l);
      strRoot = " + ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp TSUB termo */
    case '-':
      strLeft = indent(a->l);
      strRoot = " - ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;


    /* termo */
    /* simple-exp TMUL fator */
    case '*':
      strLeft = indent(a->l);
      strRoot = " * ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* simple-exp TDIV fator */
    case '/':
      strLeft = indent(a->l);
      strRoot = " / ";
      strRight = indent(a->r);
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;


    /* fator */
    /* TOPP exp TCLP */
    case APar:
      strLeft = "(";
      strRoot = indent(a->l);
      strRight = ")";
      strcat(strReturn, strLeft);
      strcat(strReturn, strRoot);
      strcat(strReturn, strRight);
      break;

    /* TNUM */
    case ANum: //- Mudar ID
      strRoot = ((struct numValue *)a)->v;
      strcat(strReturn, strRoot);
      break;

    /* TID */
    case AId: //- Mudar ID
      strRoot = ((struct idName *)a)->n;
      strcat(strReturn, strRoot);
      break;

  default: printf("internal error: bad node %c\n", a->nodetype);
  }
  return strReturn;
}

void treefree(struct ast *a) {

  switch(a->nodetype) {

    /* two subtrees */
  case '+':
  case '-':
  case '*':
  case '/':
  case '1':  case '2':  case '3':  case '4':  case '5':  case '6':
  case 'L':
    treefree(a->r);

    /* one subtree */
  case '|':
  case 'M': case 'C': case 'F':
    treefree(a->l);

    /* no subtree */
  case 'K': case 'N':
    break;

  case '=':
    free( ((struct symasgn *)a)->v);
    break;

  case 'I': case 'W':
    free( ((struct flow *)a)->cond);
    if( ((struct flow *)a)->tl) free( ((struct flow *)a)->tl);
    if( ((struct flow *)a)->el) free( ((struct flow *)a)->el);
    break;

  default: printf("internal error: free bad node %c\n", a->nodetype);
  }

  free(a); /* always free the node itself */

}

void yyerror(char *s, ...) {
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

int main() {
  return yyparse();
}

struct ast * mkNode(struct ast *l, int nodetype, struct ast *r) {

  struct ast *a = malloc(sizeof(struct ast));

  if(!a) {
    yyerror("out of space");
    exit(0);
  }

  a->nodetype = nodetype;
  a->l = l;
  a->r = r;

  return a;

}

struct ast * mkId(int value) {

  struct numValue *a = malloc(sizeof(struct numValue));

  if(!a) {
    yyerror("out of space");
    exit(0);
  }

  a->nodetype = AId;
  a->value = value;
  return (struct ast *)a;
}

void treefree(struct ast *a) {

  switch(a->nodetype) {

    /* two subtrees */
  case '+':
  case '-':
  case '*':
  case '/':
  case '1':  case '2':  case '3':  case '4':  case '5':  case '6':
  case 'L':
    treefree(a->r);

    /* one subtree */
  case '|':
  case 'M': case 'C': case 'F':
    treefree(a->l);

    /* no subtree */
  case 'K': case 'N':
    break;

  case '=':
    free( ((struct symasgn *)a)->v);
    break;

  case 'I': case 'W':
    free( ((struct flow *)a)->cond);
    if( ((struct flow *)a)->tl) free( ((struct flow *)a)->tl);
    if( ((struct flow *)a)->el) free( ((struct flow *)a)->el);
    break;

  default: printf("internal error: free bad node %c\n", a->nodetype);
  }

  free(a); /* always free the node itself */

}

void yyerror(char *s, ...) {
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

int main() {
  printf("> ");
  return yyparse();
}
