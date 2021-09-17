#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "util.h"
#include "categorias.h"
#include "objeto.h"

/* Mensagens de erro de sintaxe */
#define SYNTAX_ERROR(pos,erroMsg) \
    fprintf(stderr, "    %s\n", linha); \
    fprintf(stderr, "    %*c^\n", pos, ' '); \
    ERRO(criaFilaObjetos em Lexer.c: erroMsg);

static const char *whiteSpace = " \t\v\f\n";

/* Caracteres dos Operadores */
static const char *carOperadores = "^%*/+-_";


/* Verifica se a string é um delimitador */
bool isDelimiter (char ch) {
  return (strchr(whiteSpace, ch)|| \
          strchr(carOperadores, ch)|| \
  ch == '(' || ch == ')' || ( ch != '.'  && ispunct(ch)));
}


/* Verifica se a string é um operador (ou parênteses) */
bool isOperator (char ch) {
  return (strchr(carOperadores, ch) || ch == '(' || ch == ')');
}


/* Verifica se a string é um identificador válido */
bool validIdentifier (char* str) {
    return ( isalpha(str[0]) );
}

/* Verifica se a string é um número inteiro */
bool isInteger (char* str) {
  int i, len = strlen(str);
  if (len == 0) {
    return false;
  }

  for (i = 0; i < len; i++) {
    if (!isdigit(str[i]) || (str[i] == '-' && i > 0)) {
      return false;
    }
  }

  return true;
}

void removeSpaces (char *str) {
  int count = 0;

  for (int i = 0; str[i]; i++) {
    if (!strchr(whiteSpace, str[i])) {
      str[count++] = str[i];
    }
  }

  str[count] = '\0';
}

/* Verifica se a string é um número real */
bool isRealNumber (char* str) {
  int i, len = strlen(str);
  bool hasDecimal = false;
  if (len == 0) {
    return false;
  }

  for (i = 0; i < len; i++) {
    if ((!isdigit(str[i]) && str[i] != '.') || \
       (str[i] == '-' && i > 0)) {
      return false;
    } if (str[i] == '.' && hasDecimal) {
      return false;
    } if (str[i] == '.') {
      hasDecimal = true;
    }
  }

  return hasDecimal;
}


char* subString (char* str, int left, int right) {
  int i;
  char *subStr = mallocSafe(sizeof(char) * (right - left + 2));

  for (i = left; i <= right; i++) {
    subStr[i - left] = str[i];
  }

  subStr[right - left + 1] = '\0';
  return subStr;
}

/* Separa o string em operadores, operandos e delimitadores */
Fila *criaFilaObjetos (String linha) {
  Fila *filaObjetos = criaFila();
  int left = 0, right = 0;
  
  removeSpaces(linha);

  int len = strlen(linha);

  while (right <= len && left <= right) {

    Objeto *objeto = NULL;
    bool encontrouObjeto = false;

    while ( (right < len) && (!isDelimiter(linha[right]) ) ) {
      right++;
    }

    if (left == right && linha[right] == '\0') {
      break;
    }

    if ( isDelimiter(linha[right]) && left == right ) {
      encontrouObjeto = true;
      if ( isOperator(linha[right]) ) {
        /* procura pelo operador */
        int j = 0;
        while (j < MAX_SIMBOLOS && strncmp(&linha[right], \
              getOperador(j), strlen(getOperador(j)))) {
          j++;
        }

        if (j == MAX_SIMBOLOS){
          SYNTAX_ERROR(right, ErroSintaxe: sintaxe inválida!);
        } else {
          objeto = criaObjeto();
          objeto->categoria = j;
          objeto->valor.pStr = getOperador(j);
        }
      }

      right++;
      left = right;
    }

    else if ((isDelimiter(linha[right]) && left != right)|| \
             (right == len && left != right)) {
      String subStr = subString(linha, left, right - 1);
      encontrouObjeto = true;
      if ( isInteger(subStr) ) {
        objeto = criaObjeto();
        objeto->categoria = INT_STR;
        objeto->valor.pStr = subStr;
      } else if ( isRealNumber(subStr) ) {
        objeto = criaObjeto();
        objeto->categoria = FLOAT_STR;
        objeto->valor.pStr = subStr;
      } else {
        free(subStr);
      }

      left = right;
    } if (objeto == NULL) {
        if (encontrouObjeto){
          right--;
        }

        SYNTAX_ERROR(right, ErroSintaxe: sintaxe inválida!);
        liberaFila(filaObjetos);
        return NULL;
    } else {
      //imprimeObjeto(objeto, ITEM);
      enqueue(filaObjetos, objeto);
    }
  }
  return filaObjetos;
}

