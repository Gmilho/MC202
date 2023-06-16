#include "ArvoreBinaria.h"

NoAB *criaNoAB(int info){
  NoAB *aux = (NoAB*)malloc(sizeof(NoAB));
  aux->esq = NULL;
  aux->dir = NULL;
  aux->info = info;
  return aux;
}

int encontraNoVetor(int *vetor, int comeco, int fim, int info){
  for (int i = comeco; i <= fim; i++){
    if (vetor[i] == info){
      return i;
    }
  }
  return -1;
}

NoAB *constroiAB(int *sim, int *pos, int simComeco, int simFim, int *indicePos){
  if (simComeco>simFim){ return NULL;}
  NoAB *cabeca = criaNoAB(pos[*indicePos]);
  (*indicePos)--;
  if (simComeco == simFim){ return cabeca;}
  int indiceCabeca = encontraNoVetor(sim, simComeco, simFim, cabeca->info);
  cabeca->dir = constroiAB(sim, pos, indiceCabeca + 1, simFim, indicePos);
  cabeca->esq = constroiAB(sim, pos, simComeco, indiceCabeca - 1, indicePos);
  return cabeca;
}

NoAB *criaArvore(int *sim, int *pos, int n){
  int indicePos = n-1;
  return constroiAB(sim, pos, 0, n-1, &indicePos);
}

void imprimeOrdemSim(ArvBin *A){
  if (A==NULL){ return;}
  imprimeOrdemSim(A->esq);
  printf("%d ", A->info);
  imprimeOrdemSim(A->dir);
}

void imprimePreOrdem(ArvBin *A){
  if (A==NULL){ return;}
  printf("%d ", A->info);
  imprimePreOrdem(A->esq);
  imprimePreOrdem(A->dir);
}

void imprimePosOrdem(ArvBin *A){
  if (A==NULL){ return;}
  imprimePosOrdem(A->esq);
  imprimePosOrdem(A->dir);
  printf("%d ", A->info);
}