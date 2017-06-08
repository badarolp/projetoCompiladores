#include <stdio.h>
#include <string.h>

#define TIF     256
#define TTHEN   257
#define TENDIF  258
#define TWHILE  259
#define TDO     260
#define TENDDO  261
#define TREAD   262
#define TWRITE  263
#define TID     264
#define TNUM    265
#define TASSIGN 265

#define numAlfabeto 50
#define ESTADOS 18

#define ESTADOFINAL 0

#define estadoInicial 0

#define espacoBranco ' '  //TERMINO DA CADEIA
#define quebraLinha '\n'  //TERMINO DE LINHA
#define tabulacao '\t'    //TABULACAO

int pos = -1;
//int TIF=0, TTHEN=0, TENDIF=0, TWHILE=0, TENDDO=0, TDO=0, TREAD=0, TWRITE=0;
char c;
FILE *arq;
int estadoAtual = 0;
int estadoAnterior = 0;
char lexema[10];
int posLex = 0;
int returnCarac = 0;
int linha = 1;
int t = 0;

int tabela_t[ESTADOS][numAlfabeto] =
	{  		/*   ;   =   :   >   <   +   -   *	 /	  (	   )   a   b   c   d   e   f   g   h   i   j	k   l 	 m	  n	   o	p	 q	   r	s	 t	  u	   v	w	 x	  y	   z	0	 1	  2	   3	4	 5	  6	   7	8	9     espacoBranco   quebraLinha    tabulacao 	*/
	/*  G  */{  1,  6,  2,  5,  4,  7,  8,  9,  10,  13,  14, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL    },
	/* q01 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q02 */{  17, 3, 17, 17, 17, 17, 17, 17,  17,  17,  17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17, 	   17,            17,            17    },
	/* q03 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q04 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q05 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q06 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q07 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q08 */{  0,  0,  0,  0,  0,  0, 16,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q09 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q10 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q11 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  17, 17, 17, 17, 17, 17, 17, 17, 17, 17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q12 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,   ESTADOFINAL,  ESTADOFINAL,  ESTADOFINAL},
	/* q13 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q14 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q15 */{  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,   15,  15,  15,  15,  15,  15,  15,  15,  15,  15,   ESTADOFINAL,   ESTADOFINAL,   ESTADOFINAL},
	/* q16 */{ 16, 16, 16, 16, 16, 16, 16, 16,  16,  16,  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,        16,            0,        	 16    },
	/* erro*/{ 17, 17, 17, 17, 17, 17, 17, 17,  17,  17,  17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17, 	   17,            17,            17    }
};


//Vetor de terminais do alfabeto
char alfabeto[] = {';', '=', ':', '>', '<', '+', '-', '*', '/', '(', ')', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '\n', '\t'};


//Vetor de tokens

char token[18][20] = {"TSEM ", ":", "TASSIGN", "TSMA", "TBIG ", "TEQ", "TSUM", "TSUB ", "TMUL ", "TDIV", "TNUM ", "IDENT", "TOPP", "TCLP", "IDENT", "COMENT", "", "ERROR"};


char *reservadas[8] = {"if", "then", "endif", "read", "write", "do", "enddo", "while"}; //Vetor de palavras reservadas


//Função devolve o char apos analise
int devolverChar() {
	if(c != EOF) fseek(arq, -1, SEEK_CUR);
}

//Verificar se esta no alfabeto
int VerificaChar() {
	int i = 0;
	int retorno = -1;
	for(i=0; i<numAlfabeto; i++){

		if(c == alfabeto[i]){
			retorno = i;
		}
	}
//Se o caracter fizer parte do alfabeto, ja retorna a pos dele no vetor, que é a coluna da matriz!
return retorno;
}

int verificaToken(char *lex) {
  int resultado;
  if(strcmp("if", lex) == 0)
    resultado = TIF;
  else if(strcmp("then", lex) == 0)
    resultado = TTHEN;
  else if(strcmp("endif", lex) == 0)
    resultado = TENDIF;
  else if(strcmp("while", lex) == 0)
    resultado = TWHILE;
  else if(strcmp("do", lex) == 0)
    resultado = TDO;
  else if(strcmp("enddo", lex) == 0)
    resultado = TENDDO;
  else if(strcmp("read", lex) == 0)
    resultado = TREAD;
  else if(strcmp("write", lex) == 0)
    resultado = TWRITE;
  return resultado;
}

//Função para imprimir o lexema formado
int PrintLexema() {

		int x;
		int verificaReserv; //auxiliar para verificar existencia de RESERVADA

		//Verifica se é um identificador, para depois verificar se é uma reservada ou, de fato, ident
		if(strcmp(token[estadoAnterior - 1], "IDENT") == 0){

			//Compara o lexema com cada palavra reservada
			for(x=0; x<8; x++){

				if(strcmp(lexema, reservadas[x]) == 0){
					verificaReserv = 1;
				}
			}
			x=0;

			//Caso o lexema seja uma palavra reservada, verificaReserv tem o valor 1
			if(verificaReserv == 1){

				switch(verificaToken(lexema)){
    
    case TIF:   
      
      	printf(" %d\t| TIF     \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    case TTHEN:
      printf(" %d\t| TTHEN \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    case TENDIF:
      printf(" %d\t| TENDIF \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;      
    
    case TWHILE:
      printf(" %d\t| TWHILE \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    case TDO:
     printf(" %d\t| TDO    \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    case TENDDO:
      printf(" %d\t| TENDDO \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    case TREAD:
     printf(" %d\t| TREAD \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    case TWRITE:
      printf(" %d\t| TWRITE \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    case TID:
      printf(" %d\t| TID \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    case TNUM:
      printf(" %d\t| TNUM \t| ", linha);
				printf("%s", lexema);
				printf("\n");
    break;
    
    default:
      printf("erro");
   

	}

			}else{

				printf(" %d\t| %s \t| ", linha, token[estadoAnterior - 1]);
				printf("%s", lexema);
				printf("\n");
			}

		//Nao printar comentário
		}else if(strcmp(token[estadoAnterior - 1], "COMENT") != 0){
			printf(" %d\t| %s \t| ", linha, token[estadoAnterior - 1]);
			printf("%s", lexema);
			printf("\n");
		}

		//Limpando vetor Lexema
		for (t=0; t<10; t++) {
			lexema[t] = NULL;
		}
		posLex = 0;
		t=0;

	verificaReserv = 0;
}

//Função para percorrer a cadeia (arq)
int percorreCadeia() {

		//Enquanto houver caracters no arquivo, faça:
		while(!feof(arq)){

			//Pega o char
			c = fgetc(arq);

			if(c == EOF){
				PrintLexema();
			}else{

				//Verifica se faz parte do alfabeto, se sim, retorna a coluna da matriz
				pos = VerificaChar();

				//Contando num linhas
				if(c == '\n'){
					linha++;
				}

				//Se pos -1 o caracter nao faz parte do alfabeto
				if(pos == -1){
					printf("Caracter invalido: %c ", c);
					break;
				}else{

					//Anda na matriz, em busca do novo estado
					estadoAnterior = estadoAtual;
					estadoAtual = tabela_t[estadoAtual][pos];

					//Se estado atual for 0 e estado anterior diferente de 0 é porque ele reconheceu um token
					if(estadoAtual == 0 && estadoAnterior != 0){

						//Imprime lexema
						PrintLexema();

						//Se o char atual nao for espaco ' ', \t, \n, devolver char para ser analizado
						if(c != ' ' && c != '\t' && c != '\n'){
							devolverChar();
						}

					//Estado de ERRO
					}else if(estadoAtual == 17){
						printf("Erro na linha: %d", linha);
						break;

					//Caso estado atual não é 0: lexema ainda nao está completo
					//Caso seja 0, e estado anterior seja 0: relevando espaços brancos
					}else {

						//Adiciona no vetor lexema somente caracter 'válidos'
						if(c != ' ' && c != '\t' && c != '\n'){
							lexema[posLex] = c;
							posLex++;
						}
					}
				}

			}

		}
}

int main(){
	arq = fopen("fat.t", "rt");
	printf("LINHA \t| TOKEN \t| LEXEMA\n--------|---------------|---------\n");

	if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}
    else {

    	percorreCadeia();

	}
    fclose(arq);
	return 0;
}




