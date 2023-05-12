#ifndef PILHA H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct pilha{
 int tamanho;
 int topo;
 int *stack;
}plh;

struct pilha* novaPilha(int n);
int TamanhoPilha(struct pilha *p);
int PilhaEstaVazia(struct pilha *p);
int PilhaEstaCheia(struct pilha *p);
void Empilha(struct pilha *p, int elem);
int Desempilha(struct pilha *p);
int RetornaElemAntTopo(struct pilha *p);

#endif