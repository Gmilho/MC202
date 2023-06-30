#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"

#define NIL -1
#define INT_MAX 2147483647

Grafo *iniciaGrafo(int numNos){
  Grafo *g = (Grafo*)calloc(1, sizeof(Grafo));
  if (g == NULL){
    return NULL;
  }
  g->numNos = numNos;
  g->no = (No*)calloc(g->numNos, sizeof(No));
  if (g->no == NULL){
    free(g);
    return NULL;
  }
  for (int i = 0; i < g->numNos; i++){
    g->no[i].adj = (int *)calloc(numNos, sizeof(int));
  }
  return g;
}

void printGrafoTeste(Grafo *g){
  for (int i = 0; i < g->numNos; i++){
    for (int j = 0; j < g->no[i].m; j++){
      printf("%c -- %c\n", g->no[i].nomeNo, g->no[g->no[i].adj[j]].nomeNo);
    }
  }
}

Fila *CriaFila(int tam){
  Fila *aux = (Fila *)calloc(1, sizeof(Fila));
  aux->val = (int*)calloc(tam, sizeof(int));
  aux->fim = aux->ini = 0;
  aux->qtde = 0;
  aux->maxSize = tam;
  return aux;
}

void DestroiFila(Fila **F) {
  Fila *aux = *F;
  if (aux != NULL){
    free(aux->val);
    free(aux);
    *F = NULL;
  }
}

int FilaVazia(Fila *F){
  if (F->qtde == 0){ return 1;}
  return 0;
}

void insereNaFila(Fila *F, int val){
  if (F->qtde == F->maxSize){ return;}
  F->val[F->fim] = val;
  F->fim = (F->fim + 1)%F->maxSize;
  F->qtde++;
}

int removeDaFila(Fila *F){
  if (F->qtde == 0){ return -1;}
  int elem;
  elem = F->val[F->ini];
  F->ini = (F->ini+1) % F->maxSize;
  F->qtde--;
  return(elem);
}

void buscaEmLargura(Grafo *g, int raiz){
  int cor[g->numNos];
  
  for (int i = 0; i < g->numNos; i++){
    cor[i] = 0;
    g->no[i].comprimento = INT_MAX;
    g->no[i].predecessor = NIL;
  }
  
  g->no[raiz].comprimento = 0;
  Fila *Fila = CriaFila(g->numNos);
  cor[raiz] = 1;
  
  insereNaFila(Fila, raiz);
  
  while(!FilaVazia(Fila)){
    int u = removeDaFila(Fila);
    
    cor[u] = 2;
    
    for (int j = 0; j < g->no[u].m; j++){
      int v = g->no[u].adj[j];
      if (cor[v] == 0){
        g->no[v].predecessor = u;
        g->no[v].comprimento = g->no[u].comprimento + 1;
        cor[v] = 1;
        insereNaFila(Fila, v);
      }
    }
  }
  for (int i = 0; i < g->numNos; i++){
    int pred = g->no[i].predecessor;
    if (pred != NIL){
      printf("%c ", g->no[pred].nomeNo);
    }
  }
  printf("\n");
  for (int i = 0; i < g->numNos; i++){
    int pred = g->no[i].predecessor;
    if (pred != NIL){
      printf("%d ", g->no[pred].comprimento);
    }
  }
  DestroiFila(&Fila);
}

void buscaEmProfundidade(Grafo *g, int raiz){
  int cor[g->numNos];
  
  for (int i = 0; i < g->numNos; i++){
    cor[i] = 0;
    g->no[i].comprimento = INT_MAX;
    g->no[i].predecessor = NIL;
  }
  
  g->no[raiz].comprimento = 0;
  cor[raiz] = 1;
  Fila *fila = CriaFila(g->numNos);
  insereNaFila(fila, raiz);
  
  while(!FilaVazia(fila)){
    int u = removeDaFila(fila);
    cor[u] = 2;
    
    for (int j = 0; j < g->no[u].m; j++){
      int v = g->no[u].adj[j];
      if (cor[v] != 2){
        g->no[v].predecessor = u;
        g->no[v].comprimento = g->no[u].comprimento +1;
        if (cor[u] == 0){
          insereNaFila(fila, v);
          cor[v] = 1;
        }
      }
    }
  }
  for (int j = 0; j < g->numNos; j++){
    int pred = g->no[j].predecessor;
    if (pred != NIL){
      printf("%c ", g->no[pred].nomeNo);
    } else {
      printf("NIL ");
    }
  }
  DestroiFila(&fila);
}