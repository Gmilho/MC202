#include <stdio.h>
#include <stdlib.h>
#define MAX_VETOR 100

int   *CriaVetor(int n);
void  ImprimeVetor(int *v, int n);
int   **CriaMatrizInt(int nlin, int ncol);
void  ImprimeMatrizInt(int **m, int nlin, int ncol);
void  DestroiMatrizInt(int **m, int nlin);
void  mergeSort(int *v, int tam);
void  junta(int *v, int *esq, int *dir, int tamEsq, int tamDir);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de Leitura: ");
    return (-1);
  }
  
  int n, k;
  if (!fscanf(fp, "%d\n", &n)){
    return (-1);
  }
  if (n == 0){ printf("\n"); return 0;}

  int **arr = (int**)calloc(MAX_VETOR, sizeof(int*));
  for (int i = 0; i < MAX_VETOR; i++){
    arr[i] = (int*)calloc(MAX_VETOR, sizeof(int));
  }
  
  for (int i = 0; i < n; i++) {
    int k;
    if (!fscanf(fp, "%d", &k)){
      return 1;
    }
    if (n == 1){ 
      int x; 
      if (!fscanf(fp, "%d", &x)){
        return 1;
      }
      printf("%d\n", x); 
      return 0;
    }
    for (int j = 0; j < k; j++){
      if (!fscanf(fp, "%d", &arr[i][j])){
        return 1;
      }
    }
  }
  fclose(fp);

  int *vetor = CriaVetor(n * MAX_VETOR);
  int indice = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < MAX_VETOR; j++){
      vetor[indice] = arr[i][j];
      indice++;
    }
  }
  for (int i = 0; i < MAX_VETOR; i++){
    free(arr[i]);
  }
  free(arr);
  
  mergeSort(vetor, n * MAX_VETOR);
  ImprimeVetor(vetor, n * MAX_VETOR);
  free(vetor);
  
  return 0;
}

int *CriaVetor(int n)
{
  int *v = (int *)calloc(n,sizeof(int));
  return(v);
}

void ImprimeVetor(int *v, int n)
{
  for(int i=0; i < n; i++)
    if(v[i] == 0){ i++;}
    else { printf("%d ", v[i]);}
  printf("\n");
}

void ImprimeMatrizInt(int **m, int nlin, int ncol)
{
  for (int l = 0; l < nlin; l++){
    for (int c = 0; c < ncol; c++)
      printf("%d ", m[l][c]);
    printf("\n");
  }
}

void mergeSort(int *v, int tam){
  if (tam < 2){ return;}
  int x = tam/2, y = tam - x;
  int esq[x], dir[y];
  for (int i = 0; i < x; i++){
    esq[i] = v[i];
  }
  for (int i = x; i < tam; i++){
    dir[i - x] = v[i];
  }
  mergeSort(esq, x);
  mergeSort(dir, y);

  junta(v, esq, dir, x, y);
}

void junta(int *v, int *esq, int *dir, int tamEsq, int tamDir){
  int i = 0, j = 0, k = 0;
  while (i < tamEsq && j < tamDir) {
    if (esq[i] <= dir[j]) {
      v[k] = esq[i];
      i++;
    } else {
      v[k] = dir[j];
      j++;
    }
      k++;
  }
  while (i < tamEsq) {
    v[k] = esq[i];
    i++;
    k++;
  }
  while (j < tamDir) {
    v[k] = dir[j];
    j++;
    k++;
  }
}