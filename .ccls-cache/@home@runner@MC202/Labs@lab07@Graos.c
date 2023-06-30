#include <stdlib.h>
#include <stdio.h>
#include "ArvoreBinaria.c"

int SomaGraos(ArvBin *A);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de leitura: ");
    return (-1);
  }
  
  int n;
  
  if(!fscanf(fp, "%d\n", &n)){
    return 0;
  }
  
  int vetorSim[n], vetorPos[n];
  for (int i = 0; i < n; i++){
    if(!fscanf(fp, "%d", &vetorSim[i])){
      return 0;
    }
  }
  for (int i = 0; i < n; i++){
    if(!fscanf(fp, "%d", &vetorPos[i])){
      return 0;
    }
  }
  fclose(fp);
  
  int x = sizeof(vetorSim)/sizeof(vetorSim[0]);
  
  ArvBin *A = criaArvore(vetorSim, vetorPos, x-1);

  int esqSum = SomaGraos(A->esq);
  int dirSum = SomaGraos(A->dir);
  int tSum = SomaGraos(A);

  printf("%d\n", MAX(tSum, MAX(esqSum, dirSum)));
  destroiArvore(A);
  
  return 0;
}

int SomaGraos(ArvBin *A){
  if (A == NULL){ 
    return 0;
  }
  if (A->info < 0){
    int somaEsq = SomaGraos(A->esq);
    int somaDir = SomaGraos(A->dir);
    if (somaEsq>0 || somaDir>0){
      return A->info + somaEsq + somaDir;
    } else {
      return 0;
    }
  }
  return A->info + SomaGraos(A->esq) + SomaGraos(A->dir);
}
