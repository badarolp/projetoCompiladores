%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int linhaCount = 1;
%}

%x comentario

LINHA       \n
DIGITO      [0-9]
LETRA       [a-zA-Z]

%%
"--"			              {BEGIN(comentario);}
<comentario>\n		      {BEGIN(INITIAL); linhaCount++;}
<comentario>.		        {}
{LINHA}			            {linhaCount++;}
[ \t]+			            {}
if			                {printf("%d\t| TIF\t\t| %s\n_________________________________\n", linhaCount, yytext);}
then                    {printf("%d\t| TTHEN\t\t| %s\n_________________________________\n", linhaCount, yytext);}
endif                   {printf("%d\t| TENDIF\t| %s\n_________________________________\n", linhaCount, yytext);}
while                	  {printf("%d\t| TWHILE\t| %s\n_________________________________\n", linhaCount, yytext);}
endwhile                {printf("%d\t| TENDWHILE\t\t| %s\n_________________________________\n", linhaCount, yytext);}
do                      {printf("%d\t| TDO\t\t| %s\n_________________________________\n", linhaCount, yytext);}
enddo                   {printf("%d\t| TENDDO\t| %s\n_________________________________\n", linhaCount, yytext);}
read                    {printf("%d\t| TREAD\t\t| %s\n_________________________________\n", linhaCount, yytext);}
write                   {printf("%d\t| TWRITE\t| %s\n_________________________________\n", linhaCount, yytext);}
"+"                     {printf("%d\t| TSUM\t\t| %s\n_________________________________\n", linhaCount, yytext);}
"*"                     {printf("%d\t| TMUL\t\t| %s\n_________________________________\n", linhaCount, yytext);}
"-"                     {printf("%d\t| TSUB\t\t| %s\n_________________________________\n", linhaCount, yytext);}
"/"                     {printf("%d\t| TDIV\t\t| %s\n_________________________________\n", linhaCount, yytext);}
{DIGITO}+{LETRA}+       {printf("ERRO NA LINHA %d (IDENTIFICADOR %s MAL FORMADO)\n_________________________________\n", linhaCount,yytext);}
{DIGITO}+               {printf("%d\t| TNUM\t\t| %s\n_________________________________\n", linhaCount, yytext);}
{LETRA}[a-zA-Z0-9]*     {printf("%d\t| TID\t\t| %s\n_________________________________\n",linhaCount, yytext);}
"("                     {printf("%d\t| TOPP\t\t| %s\n_________________________________\n", linhaCount, yytext);}
")"                     {printf("%d\t| TCLP\t\t| %s\n_________________________________\n", linhaCount, yytext);}
";"                     {printf("%d\t| TSEM\t\t| %s\n_________________________________\n", linhaCount, yytext);}
"="                     {printf("%d\t| TEQ\t\t| %s\n_________________________________\n", linhaCount, yytext);}
":="                    {printf("%d\t| TASSIGN\t| %s\n_________________________________\n", linhaCount, yytext);}
"<"                     {printf("%d\t| TSMA\t\t| %s\n_________________________________\n", linhaCount, yytext);}
">"                     {printf("%d\t| TBIG\t\t| %s\n_________________________________\n", linhaCount, yytext);}
.                       {printf("ERRO NA LINHA: %d SÍMBOLO %s DESCONHECIDO\n_________________________________\n",linhaCount,yytext);}
%%

int main(int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    printf("_________________________________\n");
    printf("LINHA\t| LEXEMA\t| TOKEN\n");
    printf("_________________________________\n");
    yylex();
    printf("_________________________________\n");
    fclose(yyin);
    return 0;
}
