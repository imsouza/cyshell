#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

typedef struct pilha {
    Objeto *inicio;
    int n;
} Pilha;


Pilha *criaPilha (){
    Pilha *p = mallocSafe(sizeof(Pilha));
    p->inicio  = NULL;
    p->n = 0;
    return p;
}


/* Faz a desalocação da pilha */
void liberaPilha (Pilha *p) {
  Objeto *aux = p->inicio;

  while (aux != NULL) {
    Objeto *temp = aux->proximo;
    free(aux);
    aux = temp;
  }

  free(p);
  p = NULL;
}


/* Insere um novo objeto a pilha */
void empilha (Pilha *p, Objeto *no) {
  no->proximo = p->inicio;
  p->inicio = no;
  p->n++;
}


/* Remove (apaga) o último elemento da pilha */
void desempilha (Pilha *p){
  if (!pilhaVazia(p)) {
    Objeto *temp = p->inicio;
    p->inicio =  p->inicio->proximo;
    p->n--;
    free(temp);
    temp = NULL;
  }
}


/* Retorna o objeto do topo da pilha */
Objeto *topoPilha (Pilha *p){
  return p->inicio;
}


/* Verifica se a pilha está vazia */
bool pilhaVazia (Pilha *p){
  return (p == NULL || p->n == 0);
}


/* Retorna o número de elementos na pilha */
int tamanhoPilha (Pilha *p) {
  if (pilhaVazia(p)) return 0;
  return p->n;
}

/* Fução que imprime os elementos da pilha */
void imprimePilha (Pilha *p, int tipo) {
  Objeto *temp = p->inicio;

  while (temp != NULL) {
    imprimeObjeto(temp, tipo);
    temp = temp->proximo;
  } 
}