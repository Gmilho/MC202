#include "ArvoreBinaria.h"

NoArvoreBinaria *criaNoAB(int info){
  NoArvoreBinaria *aux = (NoArvoreBinaria*)calloc(1, sizeof(NoArvoreBinaria));
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

NoArvoreBinaria *constroiAB(int *sim, int *pos, int simComeco, int simFim, int *indicePos){
  if (simComeco>simFim){ return NULL;}
  NoArvoreBinaria *cabeca = criaNoAB(pos[*indicePos]);
  (*indicePos)--;
  if (simComeco == simFim){ return cabeca;}
  int indiceCabeca = encontraNoVetor(sim, simComeco, simFim, cabeca->info);
  cabeca->dir = constroiAB(sim, pos, indiceCabeca + 1, simFim, indicePos);
  cabeca->esq = constroiAB(sim, pos, simComeco, indiceCabeca - 1, indicePos);
  return cabeca;
}

NoArvoreBinaria *criaArvore(int *sim, int *pos, int n){
  int indicePos = n-1;
  return constroiAB(sim, pos, 0, n-1, &indicePos);
}