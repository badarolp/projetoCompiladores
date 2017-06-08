/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indent.h
 */
/* Declarações */

struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
};

struct flow {
  int nodetype;			   /* type I ou W */
  struct ast *cond;		 /* condição */
  struct ast *tl;		   /* then ou do */
};

/* Construir a ast */
struct ast *newast(struct ast *l, int nodetype, struct ast *r);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl);

/* Deleta e libera a AST */
void treefree(struct ast *);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);
