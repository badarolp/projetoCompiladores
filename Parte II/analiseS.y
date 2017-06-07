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

programa    : stmt-seq TSEM                   ???
;

stmt-seq    : stmt-seq TSEM stmt              {$$ = mkNode($1,';',$3);}
            | stmt
;

stmt        : if-stmt
            | while-stmt
            | assign-stmt
            | read-stmt
            | write-stmt
;

if-stmt     : TIF exp THEN stmt-seq TENDIF    {$$ = mkNode('I', $2, $4);}
;

while-stmt  : TWHILE exp TDO stmt-seq TENDDO  {$$ = mkFlow('W', $2, $4);}
;

assign-stmt : TID TASSIGN exp                 ???{$$ = mkAsgn($1,$3);}
;

read-stmt   : TREAD TID                       ???{}

write-stmt  : TWRITE exp                      ???{}

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

fator       : TOPP exp TCLP                   ???
            | TNUM                            ???
            | TID                             ???
%%
