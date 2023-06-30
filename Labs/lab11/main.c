#include <stdlib.h>
#include <stdio.h>
#include "Graph.c"

int *idxAdj(int *arr, int tam, int *novotam);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de leitura");
    return (-1);
  }

  int n;
  if (!fscanf(fp, "%d\n", &n)){
    return (-1);
  }

  Grafo *g = iniciaGrafo(n);
  
  int **arr = (int**)calloc(n, sizeof(int*));
  for (int i = 0; i < n; i++){
    arr[i] = (int*)calloc(n, sizeof(int));
  }
  
  char list[26];
  for (int i = 0; i < 26; i++){
    list[i] = 'A'+i;
  }
  
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if(!fscanf(fp, "%d", &arr[i][j])){
        return (-1);
      }
    }
  }
  fclose(fp);
  
  for (int i = 0; i < g->numNos; i++){
    g->no[i].nomeNo = list[i];
    int novotam;
    int *idxAdjacencias = idxAdj(arr[i], n, &novotam);
    g->no[i].adj = idxAdjacencias;
    g->no[i].m = novotam;
    /*for (int j = 0; j < g->no[i].m; j++){
      printf("%d ", g->no[i].adj[j]);
    }
    printf("\n");*/
  }
  
  for (int i = 0; i < n; i++){
    free(arr[i]);
  }
  free(arr);

  buscaEmLargura(g, 1);
  printf("\n");
  buscaEmProfundidade(g, 1);
  
  for (int i = 0; i < g->numNos; i++){
    free(g->no[i].adj);
  }
  free(g->no);
  free(g);
  
  return 0;
}

int *idxAdj(int *arr, int tam, int *novotam){
  int *idxs = (int*)calloc(tam, sizeof(int));
  int count = 0;
  for (int i = 0; i < tam; i++){
    if (arr[i] == 1){
      idxs[count] = i;
      count++;
    }
  }
  *novotam = count;
  return idxs;
}