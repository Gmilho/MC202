#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "ArvoreBinaria.c"

void extraiInteiros(const char* str, int* array, int* count);
void Espelho(ArvBin *A);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de leitura: ");
    return (-1);
  }
  int n, contaSim, contaPos;
  
  if(!fscanf(fp, "%d", &n)){
    return 0;
  }
  
  int vetorSim[n], vetorPos[n];
  char strSimIN[256], strPosIN[256], strDummy[32];
  
  fgets(strDummy, 32, fp);
  fgets(strSimIN, 256, fp);
  fgets(strPosIN, 256, fp);
  
  extraiInteiros(strSimIN, vetorSim, &contaSim);
  extraiInteiros(strPosIN, vetorPos, &contaPos);

  ArvBin *A = criaArvore(vetorSim, vetorPos, n);

  Espelho(A);
  imprimePreOrdem(A);
  printf("\n");
  imprimeOrdemSim(A);
  printf("\n");
  imprimePosOrdem(A);
  return 0;
}

void extraiInteiros(const char* str, int* array, int* count) {
  *count = 0;
  const char* delimitador = " \t\n";
  char* token;
  char* copia = strdup(str);
  token = strtok(copia, delimitador);

  while (token != NULL) {
    int num = atoi(token);

    if (num != 0) {
      array[*count] = num;
      (*count)++;
    }
      token = strtok(NULL, delimitador);
  }
  free(copia);
}

void Espelho(ArvBin *A){
  if (A==NULL){ return;}
  NoAB *aux = (NoAB*)malloc(sizeof(NoAB));
  aux = A->esq;
  A->esq = A->dir;
  A->dir = aux;
  Espelho(A->dir);
  Espelho(A->esq);
}
