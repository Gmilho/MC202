#include <stdio.h>
#include <stdlib.h>
#define MAX_ARCOS 100
#define INT_MAX 2147483647

typedef struct _Arco{
  char no1;
  char no2;
  int custo;
} Arco;

typedef struct _Grafo{
  int nnos;
  int narcos;
  Arco arcos[MAX_ARCOS];
} Grafo;

Arco criaArco(char no1, char no2, int custo);
void adicionaArco(Grafo *g, Arco arco);
void printGrafo(Grafo *grafo);
int calculaAGM(Grafo *g);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de leitura");
    return (-1);
  }

  int n, custo;
  if (!fscanf(fp, "%d", &n)){
    return (-1);
  }

  Grafo grafo;
  grafo.nnos = 0;
  grafo.narcos = 0;
  char no1, no2;
  for (int i = 0; i < n; i++){
    if(fscanf(fp, "%c %c %d", &no1, &no2, &custo)){
      if (no1 - 'A' >= grafo.nnos){
        grafo.nnos = no1 - 'A' +1;
      }
      if (no2 - 'A' >= grafo.nnos){
        grafo.nnos = no1 - 'A' +1;
      }
      adicionaArco(&grafo, criaArco(no1, no2, custo));
    }
  }
  grafo.nnos++;
  printGrafo(&grafo);
  printf("%d", calculaAGM(&grafo));
  
  return 0;
}

Arco criaArco(char no1, char no2, int custo){
  Arco aux;
  aux.no1 = no1;
  aux.no2 = no2;
  aux.custo = custo;
  return aux;
}

void adicionaArco(Grafo *g, Arco arco){
  g->arcos[g->narcos++] = arco;
}

void printGrafo(Grafo *grafo){
  printf("Num. Nós: %d\t", grafo->nnos);
  for (int i = 0; i < grafo->narcos; i++){
    printf("%c -- %c -- %d\n", grafo->arcos[i].no1, grafo->arcos[i].no2, grafo->arcos[i].custo);
  }
}

int calculaAGM(Grafo *g){
  int visitado[MAX_ARCOS], chave[MAX_ARCOS], pred[MAX_ARCOS];
  int tamfila = 0, fila[MAX_ARCOS];
  int custo = 0;
  for (int i = 0; i < g->nnos; i++){
    chave[i] = INT_MAX;
    pred[i] = -1;
  }
  chave[0] = 0;
  visitado[0] = 0;
  fila[tamfila++] = 0;
  while(tamfila>1){
    int idxmin = 0;
    for (int i = 1; i < g->narcos; i++)
      if (g->arcos[idxmin].custo < g->arcos[i].custo)
        idxmin = i;
    int v = fila[idxmin];
    fila[idxmin] = fila[++tamfila];
    visitado[v] = 1;
    custo += g->arcos[v].custo;
  }
  return custo;
}