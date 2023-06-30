#ifndef GRAPH_H
#define GRAPH_H

typedef struct _NodeGraph{
  char nomeNo;
  int *adj, m;
  int predecessor;
  int comprimento;
} No;

typedef struct _Graph{
  No *no;
  int numNos;
} Grafo;

typedef struct _Fila{
  int *val;
  int maxSize, ini, fim, qtde;
} Fila;

Grafo *iniciaGrafo(int numNos);
void  printGrafoTeste(Grafo *g);
Fila  *CriaFila(int tam);
void  insereNaFila(Fila *F, int val);
int   removeDaFila(Fila *F);
void  buscaEmLarguraProfessor(Grafo *g, int val);
void  buscaEmProfundidade(Grafo *g, int val);

#endif