#ifndef ARVOREBINARIA
#define ARVOREBINARIA

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef MAX
#define MAX(x,y) (((x) > (y))?(x):(y))
#endif

typedef struct ArvoreBinaria {
    int info;
    struct ArvoreBinaria *esq, *dir;
} ArvBin, NoAB;

int encontraNoVetor(int *vetor, int comeco, int fim, int info);
NoAB *constroiAB(int *sim, int *pos, int simComeco, int simFim, int *indicePos);
NoAB *criaArvore(int *sim, int *pos, int n);
void imprimeOrdemSim(ArvBin *A);
void imprimePreOrdem(ArvBin *A);
void imprimePosOrdem(ArvBin *A);

#endif