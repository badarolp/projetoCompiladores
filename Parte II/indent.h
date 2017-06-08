/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indent.h
 */
/* Declarações */

#define APrograma 0
#define AIf 1
#define AWhile 2
#define AAssign 3
#define ARead 4
#define AWrite 5
#define APar 6
#define ANum 7
#define AId 8


struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
};

struct numValue {
  int nodetype;
  int value;
};

struct idNome {
  int nodetype;
  int nome;
};

/* Construir a ast */
struct ast * mkNode(struct ast *l, int nodetype, struct ast *r);
struct ast * mkNum(int value);
struct ast * mkId(char * nome);

/* Identa código*/
const char * indent(struct ast *a);

/* Deleta e libera a AST */
void treefree(struct ast *);

/* interface to the lexer */
//extern int yylineno; /* from lexer */
//void yyerror(char *s, ...);
