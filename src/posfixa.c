#include <stdio.h>
#include <stdlib.h>

#include "posfixa.h"
#include "pilha.h"

Fila *infixaParaPosfixa (Fila *infixa) {
  Pilha *operadores = criaPilha();
  Fila *posFixa = criaFila();

  while (!filaVazia(infixa)) {
    Objeto *resposta = front(infixa);

    switch (resposta->categoria) {
      case FLOAT:
      case INT:
        enqueue(posFixa, copiaObjeto(resposta));
        break;

      case ABRE_PARENTESES:
        empilha(operadores, copiaObjeto(resposta));
        break;

      case FECHA_PARENTESES:
        while (topoPilha(operadores)->categoria != ABRE_PARENTESES) {
          enqueue(posFixa, copiaObjeto(topoPilha(operadores)));
          desempilha(operadores);
        }

        desempilha(operadores);
        break;

      default:
        if (resposta->categoria != OPER_EXPONENCIACAO && \
            resposta->categoria != OPER_MENOS_UNARIO) {
          while (!pilhaVazia(operadores) &&
                  topoPilha(operadores)->valor.vInt >= \
                  getPrecedenciaOperadores(resposta->categoria)) {
            enqueue(posFixa, copiaObjeto(topoPilha(operadores)));
            desempilha(operadores);
          }

          empilha(operadores, copiaObjeto(resposta));
        } else {
          empilha(operadores, copiaObjeto(resposta));
        }

        break;
      }

    dequeue(infixa);
  }

  while (!pilhaVazia(operadores)) {
    enqueue(posFixa, copiaObjeto(topoPilha(operadores)));
    desempilha(operadores);
  }

  liberaPilha(operadores);

  return posFixa;
}


void imprimePosFixa (Fila *posfixa) {
  Fila *f = copiaFila(posfixa);

  while (!filaVazia(f)) {
    Objeto *obj = front(f);
    imprimeObjeto(obj, POSFIXA);
    dequeue(f);
  }
  
  printf("\n");
  liberaFila(f);
}