#ifndef EP2_FILA_H
#define EP2_FILA_H

#include "categorias.h"
#include "util.h"
#include "objeto.h"

typedef struct fila Fila;

Fila *criaFila();

void liberaFila(Fila *f);

void enqueue(Fila *, Objeto *);

void dequeue(Fila *);

Objeto *front(Fila *);

bool filaVazia(Fila *);

int tamanhoFila(Fila *);

Fila *copiaFila(Fila *);

void imprimeFila(Fila *, int);

void converteElementosFila(Fila *, void (*cb)(Objeto *));

#endif