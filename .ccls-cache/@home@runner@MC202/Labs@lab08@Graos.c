#include <stdlib.h>
#include <stdio.h>
#include "ArvoreBinaria.c"

char *strdup(const char *str);
int SomaGraos(ArvBin *A);
void extraiInteiros(const char* str, int* array, int* count);

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

  int somaAinteira = SomaGraos(A);
  int somaEsq = SomaGraos(A->esq);
  int somaDir = SomaGraos(A->dir);

  printf("%d\n", somaAinteira);
  printf("%d", MAX(somaEsq, somaDir));
  
  return 0;
}

char *strdup(const char *str){
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup)
    {
        strcpy(dup, str);
    }
    return dup;
}

int SomaGraos(ArvBin *A){
  if (A==NULL){ return 0;}
  int resp = A->info;
  int respE = SomaGraos(A->esq);
  int respD = SomaGraos(A->dir);
  int soma = resp + respE + respD;
  printf("%d, %d\n", resp, soma);
  return soma;
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