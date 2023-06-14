#ifndef ARVOREBINARIA
#define ARVOREBINARIA

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef MAX
#define MAX(x,y) (((x) > (y))?(x):(y))
#endif

typedef struct _ArvoreBinaria {
  char info; /* informacao */
  struct _ArvoreBinaria *esq, *dir; /* subarvores esquerda e direita */
} ArvoreBinaria, NoArvoreBinaria;

/* Cria no de arvore binaria com subarvores esquerda e direita */

NoArvoreBinaria *CriaNoArvoreBinaria(ArvoreBinaria *esq, ArvoreBinaria *dir, char info);

ArvoreBinaria *ConstroiABvetorSimPos(int sim[], int pos[], int n);

#endif