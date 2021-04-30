#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"
#include "fila.h"
#include "lexer.h"
#include "posfixa.h"
#include "avalia.h"

/* Número máximo de caracteres em uma linha */
#define MAX_TAMANHO 128

void itemParaValor(Objeto *);

int main (int argc, char *argv[]) {
  char linha[MAX_TAMANHO];
  FILE *fEntrada = stdin;
  char *nomeArqScript = NULL;

  /* Opções de execução */
  bool modoInterativo = true;
  bool exibirNotacaoPosFixa = false;

  /* Lê os valores passados como argumento para o programa */
  for (int i = 1; i < argc; ++i) {
    if (!strncmp(argv[i], "-e", 2)) {
      exibirNotacaoPosFixa = true;
    } else if (!strncmp(argv[i], "-s", 2)){
      modoInterativo = false;
      nomeArqScript = argv[i + 1];
    }
  }

  if (!modoInterativo) {
    fEntrada = fopen(nomeArqScript, "r");
    if (fEntrada == NULL) {
      printf("Arquivo '%s' não encontrado\n", nomeArqScript);
      exit(1);
    }
  }

  printf("Estrutura de Dados - EP2\n");
  printf("Cyshell 🐍 1.0.0 (%s, %s)\n", __DATE__, __TIME__);
  printf("[GCC %s] on %s\n", __VERSION__, SYSTEM);

  if (modoInterativo) {
    printf(">>> ");
  }

  /* Analisa cada linha do arquivo ou da entrada padrão */
  while (fgets(linha, MAX_TAMANHO, fEntrada) != NULL) {
    // substitui o '\n' por '\0'
    if (linha[strlen(linha) - 1] == '\n') {
      linha[strlen(linha) - 1] = '\0';
    } if (!modoInterativo) {
      printf("Analisando a expressão: '%s'\n", linha);
    }

    Fila *filaObjetos = criaFilaObjetos(linha);
    //imprimeFila(filaObjetos, ITEM);

    if (filaObjetos) {
      converteElementosFila(filaObjetos, itemParaValor);
      //imprimeFila(filaObjetos, VALOR);

      Fila *posfixa = infixaParaPosfixa(filaObjetos);
      if (exibirNotacaoPosFixa) {
        printf("Expressão pós-fixa: ");
        imprimePosFixa(posfixa);
      }

      Objeto *resultado = avalia(posfixa);
       if (resultado){
         imprimeValor(resultado);
         liberaObjeto(resultado);
       }

      liberaFila(posfixa);
      liberaFila(filaObjetos);
    }

    if (modoInterativo) {
      printf(">>> ");
    }
  }
  fclose(fEntrada);
  return 0;
}


/* Faz a conversão do campo valor de um objeto para o seu valor correto */
void itemParaValor (Objeto *obj) {
  char *c = obj->valor.pStr;
  if (obj->categoria >= 0 && obj->categoria <= 6) {
    obj->valor.vInt = getPrecedenciaOperadores(obj->categoria); 
  }
  else if (obj->categoria == FLOAT_STR || obj->categoria == INT_STR){
    if (obj->categoria == FLOAT_STR) { 
      obj->valor.vFloat = atof(obj->valor.pStr);  
      obj->categoria = FLOAT;
    }
    else {
      obj->valor.vInt = atoi(obj->valor.pStr);
      obj->categoria = INT;
    }
    if(c != NULL) {
      free(c);
    }
  } else if (obj->categoria == ABRE_PARENTESES || \
             obj->categoria == FECHA_PARENTESES) {
    obj->valor.vInt = 0;
  }
}
