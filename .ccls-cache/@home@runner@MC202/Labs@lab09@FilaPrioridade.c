#include "FilaPrioridade.h"

int HeapCheio(Heap *H) {
  if (H->tamMaxH >= HEAP_MAX && H->tamMinH >= HEAP_MAX)
    return 1;
  else
    return 0;
}

int HeapVazio(Heap *H) {
  if (H->tamMaxH <= 0 && H->tamMinH <= 0)
    return 1;
  else
    return 0;
}

void InsereNoHeap(Heap *H, char *nomeCliente, int prioridadeC) {
  Clientes aux;
  strcpy(aux.sobrenome, nomeCliente);
  aux.prioridade = prioridadeC;
  
  H->heapMin[H->tamMinH] = aux;
  int i = H->tamMinH;
  H->tamMinH++;
  while (i != 0 && H->heapMin[i].prioridade < H->heapMin[Pai(i)].prioridade){
    Troca(&H->heapMin[i], &H->heapMin[Pai(i)]);
    i = Pai(i);
  }

  H->heapMax[H->tamMaxH] = aux;
  int j = H->tamMaxH;
  H->tamMaxH++;
  while (j != 0 && H->heapMax[j].prioridade > H->heapMax[Pai(j)].prioridade){
    Troca(&H->heapMax[j], &H->heapMax[Pai(j)]);
    j = Pai(j);
  }
  
}

void transformaMinimo(Clientes *C, int tamMin, int indice) {
  int menor = indice;
  int esq = FilhoEsquerdo(indice);
  int dir = FilhoDireito(indice);
  if (esq < tamMin && C[esq].prioridade < C[menor].prioridade)
    menor = esq;
  
  if (dir < tamMin && C[dir].prioridade < C[menor].prioridade)
    menor = dir;

  if (menor != indice) {
    Troca(&C[indice], &C[menor]);
    transformaMinimo(C, tamMin, menor);
  }
}

void transformaMaximo(Clientes *C, int tamMax, int indice) {
  int maior = indice;
  int esq = FilhoEsquerdo(indice);
  int dir = FilhoDireito(indice);
  if (esq < tamMax && C[esq].prioridade > C[maior].prioridade)
    maior = esq;
  
  if (dir < tamMax && C[dir].prioridade > C[maior].prioridade)
    maior = dir;
  
  if (maior != indice) {
    Troca(&C[indice], &C[maior]);
    transformaMaximo(C, tamMax, maior);
  }
}

void Troca(Clientes *x, Clientes *y) {
  Clientes aux = *x;
  *x = *y;
  *y = aux;
}

void atualizaPrioridade(Heap *H, char *nomeCliente, int prioridadeC){
  int i;
  for (i = 0; i < H->tamMinH; i++){
    if (strcmp(H->heapMin[i].sobrenome, nomeCliente) == 0){
      H->heapMin[i].prioridade = prioridadeC;
      break;
    }
  }
  transformaMinimo(H->heapMin, H->tamMinH, i);

  int j;
  for (j = 0; j < H->tamMaxH; j++){
    if (strcmp(H->heapMax[j].sobrenome, nomeCliente) == 0){
      H->heapMax[j].prioridade = prioridadeC;
      break;
    }
  }
  transformaMaximo(H->heapMax, H->tamMaxH, j);
}

void removeClienteMax(Heap *H, char *nomeCliente){
  int i;
  for (i = 0; i < H->tamMaxH; i++){
    if (strcmp(H->heapMax[i].sobrenome, nomeCliente) == 0){
      H->heapMax[i].prioridade = -1;
      break;
    }
  }
  transformaMaximo(H->heapMax, H->tamMaxH, i);
  H->tamMaxH--;
}

void removeClienteMin(Heap *H, char *nomeCliente){
  int i;
  for (i = 0; i < H->tamMinH; i++){
    if (strcmp(H->heapMin[i].sobrenome, nomeCliente) == 0){
      H->heapMin[i].prioridade = -1;
      break;
    }
  }
  transformaMinimo(H->heapMin, H->tamMinH, i);
  H->tamMinH--;
}

int retornaIdxMaxHeap(Heap *H){
  for (int i = 0; i < H->tamMaxH; i++){
    if (H->heapMax[i].prioridade != -1){
      return i;
    }
  }
  return -1;
}

int retornaIdxMinHeap(Heap *H){
  for (int i = 0; i < H->tamMinH; i++){
    if (H->heapMin[i].prioridade != -1){
      return i;
    }
  }
  return -1;
}

int ehNum(char c) {
  if (c - '0' >= 0 && c - '0' <= 9) {
    return 1;
  }
  return 0;
}