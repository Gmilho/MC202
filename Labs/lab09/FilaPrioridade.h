#ifndef _FILAPRIORIDADE_H_
#define _FILAPRIORIDADE_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i+1)
#define FilhoDireito(i) (2*i+2)

typedef struct _Clientes{
  int prioridade;
  char *sobrenome;
  int idxMax, idxMin;
} Clientes;

typedef struct _heap{
  int maxsize, nelems;
  Clientes *heap;
} Heap;

typedef struct _FilaDePrioridades{
  Heap *heapMin, *heapMax;
  int maxsize, nelems;
} FilaP;

Heap     *CriaHeap(int maxsize);
void     InsereNoHeap(Heap *H, char *nomeCliente, int prioridadeC);
void     removeCliente(Heap *H);
int      HeapCheio(Heap *H);
int      HeapVazio(Heap *H);
void     transformaMinimo(Heap *H, int indice);
void     transformaMaximo(Heap *H, int indice);
void     Troca(Clientes *x, Clientes *y);
int      ehNum(char c);

#endif