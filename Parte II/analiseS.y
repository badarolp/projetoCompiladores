%union{
  int		   intVal;
  string*	 opVal;
  string*	 id;
}

%start programa
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

%%
programa : stmt-seq TSEM

stmt-seq : stmt-seq TSEM stmt
         | stmt

stmt     : if-stmt
         | while-stmt
         | assign-stmt
         | read-stmt
         | write-stmt

if-stmt  : TIF exp THEN stmt-seq TENDIF

while-stmt : TWHILE exp TDO stmt-seq TENDDO

assign-stmt : TID TASSIGN exp

read-stmt : TREAD TID

write-stmt : TWRITE exp

exp : simple-exp TSMA simple-exp
    | simple-exp TBIG simple-exp
    | simple-exp TEQ simple-exp
    | simple-exp

simple-exp : simple-exp TSUM termo
           | simple-exp TSUB termo
           | termo

termo : termo TMUL fator
      | termo TDIV fator
      | fator

fator : TOPP exp TCLP
      | TNUM
      | TID

%%
