// Compiladores - 2016.2
// Lucas Pinho Badaró e Pedro
// 1º Trabalho: AFD usando tabela

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

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


enum estados {q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, qerro, qeof};
typedef enum estados Estados;
int valorToken;
int linha = 1;
FILE *arquivo;

char palavrasReservadas[40] = {
  'i','f','\0',               //0-2
  't','h','e','n','\0',       //3-7
  'e','n','d','i','f','\0',   //8-13
  'w','h','i','l','e','\0',   //14-19
  'd','o','\0',               //20-22
  'e','n','d','d','o','\0',   //23-28
  'r','e','a','d','\0',       //29-33
  'w','r','i','t','e','\0'};  //34-39

typedef struct no {
  char *item;
  struct no *prox;
} *lista;

lista listaReservadas = NULL;

void inserir(lista *p, char *x) {
  lista n = malloc(sizeof(struct no));
  assert(n != NULL);
  n->item = x;
  n->prox = *p;
  *p = n;
}

void remover(lista *p) {
  lista n = *p;
  if(n == NULL)
    return;
  *p = n->prox;
  free(n);
}

lista buscar(char *x, lista ini) {
  lista p;
  p = ini;
  while((p != NULL) && (strcmp(x, p->item) != 0))
    p = p->prox;
  return p;
}

// fopen -> Open file
void iniciar(char *str) {
  arquivo = fopen(str,"r+");
  if(arquivo == NULL) {
    printf("\nARQUIVO NAO PODE SER ABERTO\nVERIFIQUE SE O ARQUIVO ESTA NO MESMO DIREOTIO DO PROGRAMA\n");
    exit(1);
  }

  inserir(&listaReservadas,&palavrasReservadas[0]);
  inserir(&listaReservadas,&palavrasReservadas[3]);
  inserir(&listaReservadas,&palavrasReservadas[8]);
  inserir(&listaReservadas,&palavrasReservadas[14]);
  inserir(&listaReservadas,&palavrasReservadas[20]);
  inserir(&listaReservadas,&palavrasReservadas[23]);
  inserir(&listaReservadas,&palavrasReservadas[29]);
  inserir(&listaReservadas,&palavrasReservadas[34]);
}

// strcmp -> Compares the C string str1 to the C string str2.
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

void imprime(char *lex, int token) {
  switch(token){

    case TIF:
      printf("%d\t\t%s\t\t%s\n",linha,"TIF",lex);
    break;

    case TTHEN:
      printf("%d\t\t%s\t\t%s\n",linha,"TTHEN",lex);
    break;

    case TENDIF:
      printf("%d\t\t%s\t\t%s\n",linha,"TENDIF",lex);
    break;

    case TWHILE:
      printf("%d\t\t%s\t\t%s\n",linha,"TWHILE",lex);
    break;

    case TDO:
      printf("%d\t\t%s\t\t%s\n",linha, "TDO",lex);
    break;

    case TENDDO:
      printf("%d\t\t%s\t\t%s\n",linha,"TENDDO",lex);
    break;

    case TREAD:
      printf("%d\t\t%s\t\t%s\n",linha,"TREAD",lex);
    break;

    case TWRITE:
      printf("%d\t\t%s\t\t%s\n",linha,"TWRITE",lex);
    break;

    case TID:
      printf("%d\t\t%s\t\t%s\n",linha,"TID",lex);
    break;

    case TNUM:
      printf("%d\t\t%s\t\t%s\n",linha,"TNUM",lex);
    break;

    default:
      printf("erro");
   }
}

// fgetc   -> Get character from stream
// isalpha -> Check if character is alphabetic
// isdigit -> Check if character is decimal digit
// isalnum -> Check if character is alphanumeric
// ungetc  -> Unget character from stream
// fscanf  -> Read formatted data from stream
int getToken() {
  Estados estado = q0;
  int charAtual;
  char lexema[20];
  int iLex = 0;
  while(1) {
    switch(estado) {

      case q0:
        charAtual = fgetc(arquivo);
        while((charAtual == ' ') || (charAtual == '\t'))
          charAtual = fgetc(arquivo);
        if(charAtual == '\n')
          linha++;
        else if(isalpha(charAtual))
          estado = q1;
        else if(isdigit(charAtual))
          estado = q2;
        else if(charAtual == '<')
          estado = q3;
        else if(charAtual == '>')
          estado = q4;
        else if(charAtual == '=')
          estado = q5;
        else if(charAtual == '+')
          estado = q6;
        else if(charAtual == '-')
          estado = q7;
        else if(charAtual == '*')
          estado = q8;
        else if(charAtual == '/')
          estado = q9;
        else if(charAtual == ':')
          estado = q10;
        else if(charAtual == '(')
          estado = q12;
        else if(charAtual == ')')
          estado = q13;
        else if(charAtual == ';')
          estado = q14;
        else if(charAtual == EOF)
          return qeof;
        else {
          printf("ERRO NA LINHA: %d\nSÍMBOLO %c DESCONHECIDO\n", linha, charAtual);
          exit(1);
        }
      break;

      case q1:
        while(isalnum(charAtual)) {
          lexema[iLex++] = charAtual;
          charAtual = fgetc(arquivo);
        }
        lexema[iLex++] = '\0';
        ungetc(charAtual, arquivo);
        lista list = buscar(lexema, listaReservadas);
        if(list != NULL) {
          int token = verificaToken(list->item);
          imprime(list->item, token);
          return token;
        }
        else {
          imprime(lexema,TID);
          return TID;
        }
        estado = q0;
      break;

      case q2:
        while(isdigit(charAtual)){
          lexema[iLex++] = charAtual;
          charAtual = fgetc(arquivo);
        }
        if(isalpha(charAtual))
          estado = qerro;
        else {
          ungetc(charAtual, arquivo);
          while(iLex > 0)
            ungetc(lexema[--iLex], arquivo);
          fscanf(arquivo, "%d",&charAtual);
          printf("%d\t\t%s\t\t%d\n", linha,"TNUM" , charAtual);
          return TNUM;
        }
      break;

      case q3:
        printf("%d\t\t%s\t\t%c\n", linha , "TSMA", charAtual);
        return charAtual;
      break;

      case q4:
        printf("%d\t\t%s\t\t%c\n", linha , "TBIG", charAtual);
        return charAtual;
      break;

      case q5:
        printf("%d\t\t%s\t\t%c\n", linha , "TEQ", charAtual);
        return charAtual;
      break;

      case q6:
        printf("%d\t\t%s\t\t%c\n", linha , "TSUM", charAtual);
        return charAtual;
      break;

      case q7:
        lexema[iLex++] = charAtual;
        charAtual = fgetc(arquivo);
        if(charAtual == '-')
          estado = q15;
        else {
          ungetc(charAtual,arquivo);
          printf("%d\t\t%s\t\t%c\n", linha , "TSMA", lexema[--iLex]);
          return charAtual;
        }
      break;

      case q8:
        printf("%d\t\t%s\t\t%c\n", linha , "TMUL", charAtual);
        return charAtual;
      break;

      case q9:
        printf("%d\t\t%s\t\t%c\n", linha , "TDIV", charAtual);
        return charAtual;
      break;

      case q10:
        lexema[iLex++] = charAtual;
        charAtual = fgetc(arquivo);
        if(charAtual == '=') {
          lexema[iLex++] = charAtual;
          estado = q11;
        }
        else {
          printf("ERRO NA LINHA: %d SIMBOLO "":"" DESCONHECIDO\n", linha);
          exit(1);
        }
      break;

      case q11:
        lexema[iLex] = '\0';
        printf("%d\t\t%s\t\t%s\n", linha , "TASSIGN", lexema);
        return TASSIGN;
      break;

      case q12:
        printf("%d\t\t%s\t\t%c\n", linha , "TOPP", charAtual);
        return charAtual;
      break;

      case q13:
        printf("%d\t\t%s\t\t%c\n", linha , "TCLP", charAtual);
        return charAtual;
      break;

      case q14:
        printf("%d\t\t%s\t\t%c\n", linha , "TSEM", charAtual);
        return charAtual;
      break;

      case q15:
        while(charAtual != '\n')
          charAtual = fgetc(arquivo);
        return charAtual;
      break;

      case qerro:
        while(isalnum(charAtual)) {
          lexema[iLex] = charAtual;
          charAtual = fgetc(arquivo);
        }
        lexema[iLex] = '\0';
        printf("IDENTIFICADOR (%s) MAL FORMADO NA LINHA: %d\n", lexema, linha);
        exit(1);
      break;

      default:
        printf("ERRO NO COMPILADOR, LINHA: %d\n", linha);
        exit(1);
        break;
    }
  }
  return 0;
}

// fclose -> Close file
int main(int argc, char *argv[]) {
  iniciar(argv[1]);
  printf("___________________________________\n");
  printf("|LINHA\t|\tTOKEN\t|\tLEXEMA|\n");
  printf("___________________________________\n");
  do {
    valorToken = getToken();
  }while(valorToken != qeof);
  printf("___________________________________\n");
  fclose(arquivo);
  while(listaReservadas != NULL) {
    remover(&listaReservadas);
  }
  return 0;
}
