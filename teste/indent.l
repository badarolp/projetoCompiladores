/* Lucas Pinho Badaró
 * Pedro Ribeiro
 * indent.l
 */
/* Reconhece tokens */

%{
#include "indent.tab.h"
int linhaCount = 1;
%}
%x comentario

LINHA       \n
DIGITO      [0-9]
LETRA       [a-zA-Z]


%%

"--"                { BEGIN(comentario);}
<comentario>\n      { BEGIN(INITIAL); linhaCount++;}
<comentario>.       { }
{LINHA}             { linhaCount++;}
[ \t]+              { }
if                  { return TIF;}
then                { return TTHEN;}
endif               { return TENDIF;}
while               { return TWHILE;}
endwhile            { return TENDWHILE;}
do                  { return TDO;}
enddo               { return TENDDO;}
read                { return TREAD;}
write               { return TWRITE;}
"+"                 { return TSUM;}
"*"                 { return TMUL;}
"-"                 { return TSUB;}
"/"                 { return TDIV;}
{DIGITO}+{LETRA}+   { yyerror("ERRO NA LINHA %d (IDENTIFICADOR %s MAL FORMADO)\n_________________________________\n", linhaCount,yytext);}
{LETRA}[a-zA-Z0-9]* { yylval.id = yytext[0]; return TID;}
{DIGITO}+           { yylval.num = atoi(yytext); return TNUM;}
"("                 { return TOPP;}
")"                 { return TCLP;}
";"                 { return TSEM;}
"="                 { return TEQ;}
":="                { return TASSIGN;}
"<"                 { return TSMA;}
">"                 { return TBIG;}
.                   { yyerror("ERRO NA LINHA: %d SÍMBOLO %s DESCONHECIDO\n_________________________________\n",linhaCount,yytext);}

%%

int yywrap (void) {return 1;}
