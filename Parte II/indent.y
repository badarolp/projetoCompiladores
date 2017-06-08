/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indent.y
 */
/* Indentador com AST */

void yyerror (char *s);

%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "indent.h"
%}

%union{
  struct ast *a;
  int		   numVal;
  string*	 idVal;
}

%token stmt-seq
%token stmt
%token if-stmt
%token while-stmt
%token assign-stmt
%token read-stmt
%token write-stmt
%token <intVal> exp
%token <intVal> simple-exp
%token <intVal> termo
%token <intVal> fator

%start programa

%%

programa    : stmt-seq                        {
                                              indent($1);
                                              treefree($2);
                                              }
;

stmt-seq    : stmt-seq TSEM stmt-seq          {$$ = mkNode($1,';',$3);}
            | stmt-seq TSEM
            | stmt
;

stmt        : if-stmt
            | while-stmt
            | assign-stmt
            | read-stmt
            | write-stmt
;

if-stmt     : TIF exp TTHEN stmt-seq TENDIF    {$$ = mkNode($2, "I", $4);}
;

while-stmt  : TWHILE exp TDO stmt-seq TENDDO  {$$ = mkNode($2, "W", $4);}
;

assign-stmt : TID TASSIGN exp                 {$$ = mkNode($1,'A',$3);}
;

read-stmt   : TREAD TID                       {$$ = mkNode($2,'R');}

write-stmt  : TWRITE exp                      {$$ = mkNode($2,'W');}

exp         : simple-exp TSMA simple-exp      {$$ = mkNode($1,'<',$3);}
            | simple-exp TBIG simple-exp      {$$ = mkNode($1,'>',$3);}
            | simple-exp TEQ simple-exp       {$$ = mkNode($1,'=',$3);}
            | simple-exp
;

simple-exp  : simple-exp TSUM termo           {$$ = mkNode($1,'+',$3);}
            | simple-exp TSUB termo           {$$ = mkNode($1,'-',$3);}
            | termo
;

termo       : termo TMUL fator                {$$ = mkNode($1,'*',$3);}
            | termo TDIV fator                {$$ = mkNode($1,'/',$3);}
            | fator
;

fator       : TOPP exp TCLP                   {$$ = mkNode($2,'P');}
            | TNUM                            ???
            | TID                             ???
;

%%

/* Código em C */

int funcoesAqui() {
	return 0;
}

int main (void) {
	return yyparse();
}
