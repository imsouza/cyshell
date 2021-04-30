#ifndef EP2_UTIL_H
#define EP2_UTIL_H

#include <stdio.h>

#ifdef __linux__
#define SYSTEM "Linux"
#elif __MACH__
#define SYSTEM "Mac OS X"
#elif __MSDOS__
#define SYSTEM "Windows"
#else
#define SYSTEM "SO deconhecido..."
#endif

#define ERRO(msg) fprintf(stderr, "ERRO: %s\n", #msg)
#define AVISO(msg) fprintf(stdout, "AVISO: %s\n", #msg)

#define ITEM    0
#define VALOR   1
#define POSFIXA 2

// Operadores aritmeticos e parenteses
#define MAX_SIMBOLOS 9

typedef enum {
  false,
  true
} bool;

typedef char *String;

void *mallocSafe(size_t nbytes);

int getPrecedenciaOperadores(int operador);

char *getOperador(int operador);

#endif