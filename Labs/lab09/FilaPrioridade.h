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
#define HEAP_MAX 100

typedef struct _Clientes{
  int prioridade;
  char sobrenome[20];
} Clientes;

typedef struct _FilaDePrioridades{
  Clientes heapMin[HEAP_MAX];
  Clientes heapMax[HEAP_MAX];
  int tamMinH, tamMaxH;
} Heap;

void     InsereNoHeap(Heap *H, char *nomeCliente, int prioridadeC);
void     atualizaPrioridade(Heap *H, char *nomeCliente, int prioridadeC);
void     removeClienteMax(Heap *H, char *nomeCliente);
void     removeClienteMin(Heap *H, char *nomeCliente);
int      retornaIdxMaxHeap(Heap *H);
int      retornaIdxMinHeap(Heap *H);
int      HeapCheio(Heap *H);
int      HeapVazio(Heap *H);
void     transformaMinimo(Clientes *C, int tamMin, int indice);
void     transformaMaximo(Clientes *C, int tamMax, int indice);
void     Troca(Clientes *x, Clientes *y);
int      ehNum(char c);

#endif