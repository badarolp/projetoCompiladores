/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indent.y
 */
/* Indentador com AST */

%{
#include "indent.h"
#include <stdio.h>
#include <stdlib.h>
%}

%union {struct ast *a; int num; char id;}         /* Definições dp yacc */
%start programa

%type <a> stmt-seq
%type <a> stmt
%type <a> if-stmt
%type <a> while-stmt
%type <a> assign-stmt
%type <a> read-stmt
%type <a> write-stmt
%type <a> exp
%type <a> simple-exp
%type <a> termo
%type <a> fator

%token TIF
%token TTHEN
%token TENDIF
%token TWHILE
%token TENDWHILE
%token TDO
%token TENDDO
%token TREAD
%token TWRITE
%token TSUM
%token TMUL
%token TSUB
%token TDIV
%token TOPP
%token TCLP
%token TSEM
%token TEQ
%token TASSIGN
%token TSMA
%token TBIG
%token <num> TNUM
%token <id> TID

%%

programa    : stmt-seq		                    {printf(indent($1));}
;

stmt-seq    : stmt-seq TSEM stmt              {$$ = mkNode($1, ';', $3);}
            | stmt
;

stmt        : if-stmt
            | while-stmt
            | assign-stmt
            | read-stmt
            | write-stmt
;

if-stmt     : TIF exp TTHEN stmt-seq TENDIF   {$$ = mkNode($2, AIf, $4);}
;

while-stmt  : TWHILE exp TDO stmt-seq TENDDO  {$$ = mkNode($2, AWhile, $4);}
;

assign-stmt : TID TASSIGN exp                 {$$ = mkNodeAssign($1, $3);}
;

read-stmt   : TREAD TID                       {$$ = mkNodeRead($2);}
;

write-stmt  : TWRITE exp                      {$$ = mkNodeWrite($2);}
;

exp         : simple-exp TSMA simple-exp      {$$ = mkNode($1, '<', $3);}
            | simple-exp TBIG simple-exp      {$$ = mkNode($1, '>', $3);}
            | simple-exp TEQ simple-exp       {$$ = mkNode($1, '=', $3);}
            | simple-exp
;

simple-exp  : simple-exp TSUM termo           {$$ = mkNode($1, '+', $3);}
            | simple-exp TSUB termo           {$$ = mkNode($1, '-', $3);}
            | termo
;

termo       : termo TMUL fator                {$$ = mkNode($1, '*', $3);}
            | termo TDIV fator                {$$ = mkNode($1, '/', $3);}
            | fator
;

fator       : TOPP exp TCLP                   {$$ = mkNodePar($2);}
            | TNUM                            {$$ = mkNodeNum($1);}
            | TID                             {$$ = mkNodeId($1);}
;

%%
