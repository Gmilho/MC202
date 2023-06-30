#ifndef _PILHA_H_
#define _PILHA_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

/* Pilha em vetor (não tem sentido ser circular) */

typedef struct _pilha {
  int   qtde;     // número de elementos na pilha
  int   tam_max;  // tamanho máximo da pilha
  int  *val;      // vetor dos valores
} Pilha;

Pilha *CriaPilha(int tam_max);
void   DestroiPilha(Pilha **Q);
bool   PilhaVazia(Pilha *Q);
bool   PilhaCheia(Pilha *Q);
bool   Empilha(Pilha *Q, int elem);                 /* push: insere na pilha (última posicao) */
bool   Desempilha(Pilha *Q, int *elem);             /* pop: remove da pilha (última posicao) */
bool   ConsultaPilha(Pilha *Q, int elem, int *ndes); /* busca o elemento e retorna o número de desempilhamentos que faltam para ele sair da pilha */
void   ImprimePilha(Pilha *Q);

#endif