#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

struct fila {
    Objeto *inicio;
    Objeto *fim;
    int n;
};


Fila *criaFila () {
  Fila *f = mallocSafe(sizeof(Fila));
  f->inicio = f->fim = NULL;
  f->n = 0;
  return f;
}


/* Faz a desalocação da fila */
void liberaFila (Fila *f) {
  Objeto *aux = f->inicio;

  while(aux) {
    Objeto *temp = aux->proximo;
    free(aux);
    aux = temp;
  }

  free(f);
  f = NULL;
}


/* Insere um novo objeto a fila */
void enqueue (Fila *f, Objeto *o) {
  if(filaVazia(f)) {
    f->inicio = o;
  } else {
    f->fim->proximo = o;
  }

  f->fim = o;
  f->n++;
}


/*Remove (apaga) o primeiro elemento da fila */
void dequeue (Fila *f) {
  if (!filaVazia(f)) {
    Objeto *temp = f->inicio;
    f->inicio = f->inicio->proximo;
    f->n--;
    free(temp);
  } else {
    return;
  }
}


/* Retorna o primeiro elemento da fila */
Objeto *front (Fila *f) {
  return f->inicio;
}


/* Verifica se a fila está vazia */
bool filaVazia (Fila *f) {
  return (f==NULL || f->n == 0);
}


/* Retorna o número de elementos na fila */
int tamanhoFila (Fila *f) {
  if (filaVazia(f)) return 0;
  return f->n;
}


/* Retorna uma cópia da fila passada como parâmetro */
Fila *copiaFila (Fila *f) {
  Fila *copia = criaFila();

  Objeto *temp = f->inicio;

  while (temp->proximo != NULL) {
    enqueue(copia, copiaObjeto(temp));
    temp = temp->proximo;
  }

  enqueue(copia, copiaObjeto(temp));

  return copia;
}


/* Fução que imprime os elementos da fila */
void imprimeFila (Fila *f, int tipo) {
  Objeto *temp = f->inicio;

  while (temp != NULL) {
    imprimeObjeto(temp, tipo);
    temp = temp->proximo;
  }
}


/* Função de Alta Ordem que recebe uma fila e uma função (cb). */
void converteElementosFila (Fila *f, void (*cb)(Objeto *)) {
  Objeto *temp = f->inicio;

  while (temp != NULL) {
    cb(temp);
    temp = temp->proximo;
  }
}