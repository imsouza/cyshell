#ifndef EP2_OBJETO_H
#define EP2_OBJETO_H

#include "util.h"
#include "categorias.h"

typedef union valor {
  int    vInt;    
  double  vFloat;  
  String  pStr;    
} Valor;

typedef struct objeto {
  Categoria categoria;
  Valor valor;
  struct objeto *proximo;
} Objeto;

Objeto *criaObjeto();

void liberaObjeto(Objeto *);

void imprimeValor(Objeto *);

void imprimeObjeto(Objeto *, int);

Objeto *copiaObjeto(Objeto *);

#endif