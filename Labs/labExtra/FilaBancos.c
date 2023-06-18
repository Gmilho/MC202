#include <stdio.h>
#include <stdlib.h>

float *CriaVetorFloat(int n);
void  DestroiVetorFloat(float **v);
void  ImprimeVetorFloatEmInt(float *v, int n);
int   **CriaMatrizInt(int nlin, int ncol);
void  ImprimeMatrizInt(int **m, int nlin, int ncol);
void  DestroiMatrizInt(int ***m, int nlin);
void  mergeSortFloat(float *v, int tam);
void  junta(float *v, float *esq, float *dir, int tamEsq, int tamDir);

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

  int **arr = CriaMatrizInt(100, 100);
  
  for (int i = 0; i < n; i++) {
    int k;
    fscanf(fp, "%d", &k);
    if (n == 1){ 
      int x; 
      fscanf(fp, "%d", &x); 
      printf("%d\n", x); 
      return 0;
    }
    for (int j = 0; j < k; j++){
      fscanf(fp, "%d", &arr[i][j]);
    }
  }

  float *vetor = CriaVetorFloat(n*100);
  int indice;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < 100; j++){
      vetor[indice] = arr[i][j];
      indice++;
    }
  }

  mergeSortFloat(vetor, n*100);
  ImprimeVetorFloatEmInt(vetor, n*100);
  DestroiMatrizInt(&arr, n);
  DestroiVetorFloat(&vetor);
  return 0;
}

float *CriaVetorFloat(int n)
{
  float *v = (float *)calloc(n,sizeof(float));
  return(v);
}

void DestroiVetorFloat(float **v)
{
  if ((*v) != NULL){
    free(*v);
    *v = NULL;
  }
}

void ImprimeVetorFloatEmInt(float *v, int n)
{
  for(int i=0; i < n; i++)
    if(v[i] == 0){ i++;}
    else { printf("%d ",(int)v[i]);}
  printf("\n");
}

int **CriaMatrizInt(int nlin, int ncol)
{
  int **m = (int **)calloc(nlin,sizeof(int *));
  
  for (int l=0; l < nlin; l++)
    m[l] = (int *)calloc(ncol,sizeof(int));
  return(m);
}

void ImprimeMatrizInt(int **m, int nlin, int ncol)
{
  for(int l=0; l < nlin; l++){
    for(int c=0; c < ncol; c++)
      printf("%03d ",m[l][c]);
    printf("\n");
  }
}

void DestroiMatrizInt(int ***m, int nlin)
{
  if ((*m) != NULL){
    for (int l=0; l < nlin; l++)
      free((*m)[l]);
    free(*m);
    *m = NULL;
  }
}

void mergeSortFloat(float *v, int tam){
  if (tam < 2){ return;}
  int meio = tam/2;
  float *esq = (float*)malloc(meio * sizeof(float));
  float *dir = (float*)malloc((tam - meio) * sizeof(float));
  for (int i = 0; i < meio; i++){
    esq[i] = v[i];
  }
  for (int i = meio; i < tam; i++){
    dir[i - meio] = v[i];
  }
  mergeSortFloat(esq, meio);
  mergeSortFloat(dir, tam - meio);

  junta(v, esq, dir, meio, tam - meio);
}

void junta(float *v, float *esq, float *dir, int tamEsq, int tamDir){
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