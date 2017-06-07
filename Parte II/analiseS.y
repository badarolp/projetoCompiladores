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

assign-stmt : TID TASSIGN exp {$$ = $1 = $3;}

read-stmt : TREAD TID {$$ = $1 $2;}

write-stmt : TWRITE exp

exp : simple-exp TSMA simple-exp {$$ = $1 < $3;}
    | simple-exp TBIG simple-exp {$$ = $1 > $3;}
    | simple-exp TEQ simple-exp  {$$ = $1 = $3;}
    | simple-exp

simple-exp : simple-exp TSUM termo {$$ = $1 + $3;}
           | simple-exp TSUB termo {$$ = $1 - $2;}
           | termo

termo : termo TMUL fator {$$ = $1 * $3;}
      | termo TDIV fator {$$ = $1 / $3;}
      | fator

fator : TOPP exp TCLP {$$ = ( $2 )}
      | TNUM          {$$ = $1;}
      | TID           {$$ = $1;}

%%
