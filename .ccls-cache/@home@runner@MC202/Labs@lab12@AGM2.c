#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_NOS 100
#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i+1)
#define FilhoDireito(i) (2*i+2)

typedef enum _bool {
  false, true
} bool;

typedef struct _Arco{
  int no1, no2, custo;
} Arco;

typedef struct _Grafo{
  int nnos, narcos;
  Arco arcos[MAX_NOS];
} Grafo;

typedef struct _NoFila{
  int vt, chave;
} NoFila;

typedef struct _fila {
  int tam_max;
  int qtde;
  int *pos;
  NoFila **arr;
} Fila;

Fila *CriaFila(int tam_max);
void adicionaArco(Grafo *g, int no1, int no2, int custo);
void printGrafo(Grafo *grafo);
int calculaAGM(Grafo *g);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de leitura");
    return (-1);
  }

  int n, custo, noCount;
  if (!fscanf(fp, "%d", &n)){
    return (-1);
  }

  Grafo grafo[MAX_NOS];
  grafo->narcos = 0;
  char no1, no2;
  for (int i = 0; i < n; i++){
    if(fscanf(fp, " %c %c %d", &no1, &no2, &custo)){
      adicionaArco(grafo, no1-'A', no2-'A', custo);
      if (no1-'A' >= noCount){
        noCount = no1-'A'+1;
      }
      if (no2-'A' >= noCount){
        noCount = no2-'A'+1;
      }
    }
  }
  grafo->nnos = noCount;
  printf("%d", calculaAGM(grafo));
  
  return 0;
}

Fila *CriaFila(int tam_max) {
  Fila *Q = (Fila*) calloc(1, sizeof(Fila));
  Q->pos = (int*)calloc(tam_max, sizeof(int));
  Q->tam_max = tam_max;
  Q->qtde = 0;
  Q->arr = (NoFila**)calloc(tam_max, sizeof(NoFila*));
  return Q;
}

NoFila *CriaNoFila(int vt, int chave){
  NoFila *aux = (NoFila*)calloc(1, sizeof(NoFila));
  aux->vt = vt;
  aux->chave = chave;
  return aux;
}

void trocaNoFila(NoFila **a, NoFila **b){
  NoFila *aux = *a;
  *a = *b;
  *b = aux;
}

void heapify(Fila *Q, int idx){
  int menor = idx;
  int esq = FilhoEsquerdo(idx);
  int dir = FilhoDireito(idx);
  if (esq < Q->tam_max && Q->arr[esq]->chave < Q->arr[menor]->chave)
    menor = esq;
  if (dir < Q->tam_max && Q->arr[dir]->chave < Q->arr[menor]->chave)
    menor = dir;
  if (menor != idx){
    NoFila *menorNo = Q->arr[menor];
    NoFila *NoIdx = Q->arr[idx];
    Q->pos[menorNo->vt] = idx;
    Q->pos[NoIdx->vt] = menor;
    trocaNoFila(&Q->arr[menor], &Q->arr[idx]);
    heapify(Q, menor);
  }
}

bool filaVazia(Fila *Q){
  return Q->qtde == 0;
}

NoFila *extraiMenorNo(Fila *Q){
  if (filaVazia(Q)){ return NULL;}
  NoFila *raiz = Q->arr[0];
  NoFila *ultimo = Q->arr[Q->qtde - 1];
  Q->arr[0] = ultimo;
  Q->pos[raiz->vt] = Q->qtde - 1;
  Q->pos[ultimo->vt] = 0;
  Q->qtde--;
  heapify(Q, 0);
  return raiz;
}

void diminuiChave(Fila *Q, int vt, int chave){
  int i = Q->pos[vt];
  Q->arr[i]->chave = chave;
  while (i && Q->arr[i]->chave < Q->arr[Pai(i)]->chave){
    Q->pos[Q->arr[i]->vt] = Pai(i);
    Q->pos[Q->arr[Pai(i)]->vt] = i;
    trocaNoFila(&Q->arr[i], &Q->arr[Pai(i)]);
    i = Pai(i);
  }
}

bool estaNaAGM(int v, bool AGM[]){
  return AGM[v];
}

void adicionaArco(Grafo *g, int no1, int no2, int custo){
  Arco arco = {no2, custo};
  g[no1].arcos[g[no1].narcos] = arco;
  g[no1].narcos++;
}

void printGrafo(Grafo *grafo){
  printf("Num. Nós: %d\t\n", grafo->nnos);
  for (int i = 0; i < grafo->nnos; i++){
    for (int j = 0; j < grafo->narcos; j++){
      printf("Nó: %c até %c -Custo: %d\n", i+'A', grafo[i].arcos[j].no2+'A', grafo[i].arcos[j].custo);
    }
  }
}

int calculaAGM(Grafo *g){
  int pred[MAX_NOS], chave[MAX_NOS];
  bool AGM[MAX_NOS];
  for (int i = 0; i < g->nnos; i++){
    chave[i] = INT_MAX;
    AGM[i] = false;
  }
  chave[0] = 0;
  pred[0] = -1;
  Fila *Q = CriaFila(g->nnos);
  Q->arr[0] = CriaNoFila(0, chave[0]);
  Q->pos[0] = 0;
  Q->qtde++;
  for (int v = 1; v < g->nnos; ++v){
    Q->arr[v] = CriaNoFila(v, chave[v]);
    Q->pos[v] = v;
    Q->qtde++;
  }
  while(!filaVazia(Q)){
    NoFila *menorNo = extraiMenorNo(Q);
    int u = menorNo->vt;
    AGM[u] = true;

    for (int v = 0; v < g->nnos; v++){
      if (g[u].arcos[v].custo && !estaNaAGM(v, AGM) && g[u].arcos[v].custo < chave[v]){
        chave[v] = g[u].arcos[v].custo;
        pred[v] = u;
        diminuiChave(Q, v, chave[v]);
      }
    }
  }
  
  int custo = 0;
  for (int i = 0; i < g->nnos; i++){
    custo += chave[i];
  }
  return custo;
}
