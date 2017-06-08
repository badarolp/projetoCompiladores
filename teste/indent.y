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

%union {int num; char id;}         /* Definições dp yacc */
%start programa
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

programa    : stmt-seq                        {printf("programa    : stmt-seq\n");}
;

stmt-seq    : stmt-seq TSEM stmt          		{printf("stmt-seq    : stmt-seq TSEM stmt\n");}
            | stmt														{printf("stmt\n");}
;

stmt        : if-stmt													{printf("stmt        : if-stmt\n");}
            | while-stmt											{printf("stmt        : while-stmt\n");}
            | assign-stmt											{printf("stmt        : assign-stmt\n");}
            | read-stmt												{printf("stmt        : read-stmt\n");}
            | write-stmt											{printf("stmt        : write-stmt\n");}
;

if-stmt     : TIF exp TTHEN stmt-seq TENDIF   {printf("if-stmt     : TIF exp TTHEN stmt-seq TENDIF\n");}
;

while-stmt  : TWHILE exp TDO stmt-seq TENDDO  {printf("while-stmt  : TWHILE exp TDO stmt-seq TENDDO\n");}
;

assign-stmt : TID TASSIGN exp                 {printf("assign-stmt : TID TASSIGN exp\n");}
;

read-stmt   : TREAD TID                       {printf("read-stmt   : TREAD TID\n");}

write-stmt  : TWRITE exp                      {printf("write-stmt  : TWRITE exp\n");}

exp         : simple-exp TSMA simple-exp      {printf("exp         : simple-exp TSMA simple-exp\n");}
            | simple-exp TBIG simple-exp      {printf("exp         : simple-exp TBIG simple-exp\n");}
            | simple-exp TEQ simple-exp       {printf("exp         : simple-exp TEQ simple-exp\n");}
            | simple-exp											{printf("exp         : simple-exp\n");}
;

simple-exp  : simple-exp TSUM termo           {printf("simple-exp  : simple-exp TSUM termo\n");}
            | simple-exp TSUB termo           {printf("simple-exp  : simple-exp TSUB termo\n");}
            | termo														{printf("simple-exp  : termo\n");}
;

termo       : termo TMUL fator                {printf("\n");}
            | termo TDIV fator                {printf("\n");}
            | fator														{printf("\n");}
;

fator       : TOPP exp TCLP                   {printf("\n");}
            | TNUM                            {printf("\n");}
            | TID                             {printf("\n");}
;

%%
