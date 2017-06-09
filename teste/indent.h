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

struct astAssign {
  int nodetype;
  char id;
  struct ast *exp;
};

struct astRead {
  int nodetype;
  char id;
};

struct astWrite {
 int nodetype;
 struct ast *exp;
};

struct astPar {
 int nodetype;
 struct ast *exp;
};

struct astNum {
  int nodetype;
  int num;
};

struct astId {
  int nodetype;;
  char id;
};

struct ast * mkNode(struct ast *l, int nodetype, struct ast *r);

struct ast * mkNodeAssign(char id, struct ast *exp);

struct ast * mkNodeRead(char id);

struct ast * mkNodeWrite(struct ast *exp);

struct ast * mkNodePar(struct ast *exp);

struct ast * mkNodeNum(int num);

struct ast * mkNodeId(char id);

void yyerror (char *s);
