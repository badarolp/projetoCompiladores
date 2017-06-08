/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indent.h
 */
/* Declarações */

/*
#define APrograma 0
#define AStmtSeq 1
#define AStmt 2
#define AIfStmt 3
#define AWhileStmt 4
#define AAssignStmt 5
#define AReadStmt 6
#define AWriteStmt 7
#define AExp 8
#define ASimpleExp 9
#define ATermo 10
#define AFator 11
#define AAssign 12
#define ARead 13
#define AWrite 14
#define APar 15
#define ANum 16
#define AId 17
*/

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
struct ast *newast(struct ast *l, int nodetype, struct ast *r);

/* Deleta e libera a AST */
void treefree(struct ast *);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);
