#include <string.h>
#include <math.h>

#include "avalia.h"
#include "categorias.h"
#include "pilha.h"

Objeto *avalia (Fila *posFixa) {
  Pilha *pilhaDeExecucao = criaPilha();

  Objeto *resposta = NULL;

  while (!filaVazia(posFixa)) {
    Objeto *va1 = NULL;
    Objeto *va2 = NULL;

    switch (front(posFixa)->categoria) {
      case FLOAT:
      case INT:
        empilha(pilhaDeExecucao, copiaObjeto(front(posFixa)));
        break;

      case OPER_ADICAO:
        resposta = criaObjeto();
        va1 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);
        va2 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);

        if (va1->categoria == INT && va2->categoria == INT) {
          resposta->categoria  = INT;
          resposta->valor.vInt = va1->valor.vInt + va2->valor.vInt;
        } else {
          if (va1->categoria == FLOAT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va1->valor.vFloat + va2->valor.vFloat;
          } else if (va1->categoria == FLOAT && va2->categoria == INT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va1->valor.vFloat + va2->valor.vInt;
          } else if (va1->categoria == INT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va1->valor.vInt + va2->valor.vFloat;
          }
        } 

        empilha(pilhaDeExecucao, resposta);
        break;


      case OPER_SUBTRACAO:
        resposta = criaObjeto();
        va1 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);
        va2 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);

        if (va1->categoria == INT && va2->categoria == INT) {
          resposta->categoria  = INT;
          resposta->valor.vInt = va2->valor.vInt - va1->valor.vInt;
        } else {
          if (va1->categoria == FLOAT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vFloat - va1->valor.vFloat;
          } else if (va1->categoria == FLOAT && va2->categoria == INT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vInt - va1->valor.vFloat;
          } else if (va1->categoria == INT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vFloat - va1->valor.vInt;
          }
        } 

        empilha(pilhaDeExecucao, resposta);
        break;


      case OPER_MULTIPLICACAO:
        resposta = criaObjeto();
        va1 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);
        va2 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);

        if (va1->categoria == INT && va2->categoria == INT) {
          resposta->categoria  = INT;
          resposta->valor.vInt = va2->valor.vInt * va1->valor.vInt;
        } else {
          if (va1->categoria == FLOAT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vFloat * va1->valor.vFloat;
          } else if (va1->categoria == FLOAT && va2->categoria == INT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vInt * va1->valor.vFloat;
          } else if (va1->categoria == INT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vFloat * va1->valor.vInt;
          }
        } 

        empilha(pilhaDeExecucao, resposta);
        break;


      case OPER_DIVISAO:
        resposta = criaObjeto();
        va1 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);
        va2 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);

        if (va1->categoria == INT && va2->categoria == INT) {
          resposta->categoria  = INT;
          resposta->valor.vInt = va2->valor.vInt / va1->valor.vInt;
        } else {
          if (va1->categoria == FLOAT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vFloat / va1->valor.vFloat;
          } else if (va1->categoria == FLOAT && va2->categoria == INT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vInt / va1->valor.vFloat;
          } else if (va1->categoria == INT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = va2->valor.vFloat / va1->valor.vInt;
          }
        } 

        empilha(pilhaDeExecucao, resposta);
        break;


      case OPER_RESTO_DIVISAO:
        resposta = criaObjeto();
        va1 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);
        va2 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);

        if (va1->categoria == INT && va2->categoria == INT) {
          resposta->categoria  = INT;
          resposta->valor.vInt = va2->valor.vInt % va1->valor.vInt;
        } else {
          if (va1->categoria == FLOAT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vInt = va2->valor.vInt % va1->valor.vInt;
          } else if (va1->categoria == FLOAT && va2->categoria == INT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vInt = va2->valor.vInt % va1->valor.vInt;
          } else if (va1->categoria == INT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vInt = va2->valor.vInt % va1->valor.vInt;
          }
        } 

        empilha(pilhaDeExecucao, resposta);
        break;


      case OPER_EXPONENCIACAO:
        resposta = criaObjeto();
        va1 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);
        va2 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);

        if (va1->categoria == INT && va2->categoria == INT) {
          resposta->categoria  = INT;
          resposta->valor.vInt = pow(va2->valor.vInt, va1->valor.vInt);
        } else {
          if (va1->categoria == FLOAT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = pow(va2->valor.vFloat, va1->valor.vFloat);
          } else if (va1->categoria == FLOAT && va2->categoria == INT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = pow(va2->valor.vInt, va1->valor.vFloat);
          } else if (va1->categoria == INT && va2->categoria == FLOAT) {
            resposta->categoria    = FLOAT;
            resposta->valor.vFloat = pow(va2->valor.vFloat, va1->valor.vInt);
          }
        } 

        empilha(pilhaDeExecucao, resposta);
        break;


      case OPER_MENOS_UNARIO:
        resposta = criaObjeto();
        va1 = copiaObjeto(topoPilha(pilhaDeExecucao));
        desempilha(pilhaDeExecucao);

        if (va1->categoria == INT) {
          resposta->categoria  = INT;
          resposta->valor.vInt = -(va1->valor.vInt);
        } else {
          resposta->categoria    = FLOAT;
          resposta->valor.vFloat = -(va1->valor.vFloat);
        } 

        empilha(pilhaDeExecucao, resposta);
        break;


      default:
        break;
    }

    if (va1) { liberaObjeto(va1); }
    if (va2) { liberaObjeto(va2); }

    dequeue(posFixa);
  }

  Objeto *copiaPilha = copiaObjeto(topoPilha(pilhaDeExecucao));

  liberaPilha(pilhaDeExecucao);

  return copiaPilha;
}
