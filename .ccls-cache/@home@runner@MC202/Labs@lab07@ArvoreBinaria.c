#include "ArvoreBinaria.h"

NoAB *criaNoAB(int info){
  NoAB *aux = (NoAB*)calloc(1, sizeof(NoAB));
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
  NoAB *cabeca = criaNoAB(pos[(*indicePos)--]);
  int i;
  for (i = simComeco; i <= simFim; i++){
    if (sim[i] == cabeca->info){
      break;
    }
  }
  cabeca->dir = constroiAB(sim, pos, i+1, simFim, indicePos);
  cabeca->esq = constroiAB(sim, pos, simComeco, i-1, indicePos);

  return cabeca;
}

NoAB *criaArvore(int *sim, int *pos, int n){
  int *indicePos = &n;
  return constroiAB(sim, pos, 0, n, indicePos);
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

void imprimeArvore(ArvBin *A, int nivel){
  if (A == NULL){
    return;
  }
  imprimeArvore(A->dir, nivel+1);
  for (int i = 0; i < nivel; i++){
    printf("    ");
  }
  printf("%d\n", A->info);
  imprimeArvore(A->esq, nivel+1);
}

void destroiArvore(ArvBin *A){
  if (A != NULL){
    destroiArvore(A->dir);
    destroiArvore(A->esq);
    free(A);
  }
}