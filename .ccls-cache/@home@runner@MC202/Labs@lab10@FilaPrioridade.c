#include "FilaPrioridade.h"

Heap *CriaHeap(int maxsize){
  Heap *aux = (Heap*)malloc(sizeof(Heap));
  aux->maxsize = maxsize;
  aux->nelems = 0;
  aux->heap = (Clientes*)calloc(maxsize, sizeof(Clientes));
  return aux;
}

void removeCliente(Heap *H){
  Clientes *aux = (Clientes*)calloc(1, sizeof(Clientes));
  *aux = H->heap[0];
  for (int i = 0; i < H->nelems; i++){
   H->heap[i] = H->heap[i+1];  
  }
  H->nelems--;
  free(aux);
}

int HeapCheio(Heap *H)
{
  if (H->nelems >= H->maxsize)
    return 1;
  else
    return 0;
}

int HeapVazio(Heap *H)
{
  if (H->nelems <= 0)
    return 1;
  else
    return 0;
}

void InsereNoHeap(Heap *H, char *nomeCliente, int prioridadeC){
  if (HeapCheio(H) == 1){ return;}
  Clientes aux;
  aux.sobrenome = nomeCliente;
  aux.prioridade = prioridadeC;
  int i = H->nelems;
  H->heap[i] = aux;
  H->nelems++;
}

void transformaMinimo(Heap *H, int indice){
  int menor = indice;
  int esq = FilhoEsquerdo(indice);
  int dir = FilhoDireito(indice);
  if (esq < H->nelems && H->heap[esq].prioridade < H->heap[menor].prioridade){ menor = esq;}
  if (dir < H->nelems && H->heap[dir].prioridade < H->heap[menor].prioridade){ menor = dir;}
  if (menor != indice) {
    Troca(&H->heap[indice], &H->heap[menor]);
    transformaMinimo(H, menor);
  }
}

void transformaMaximo(Heap *H, int indice){
  int maior = indice;
  int esq = FilhoEsquerdo(indice);
  int dir = FilhoDireito(indice);
  if (esq < H->nelems && H->heap[esq].prioridade > H->heap[maior].prioridade){ maior = esq;}
  if (dir < H->nelems && H->heap[dir].prioridade > H->heap[maior].prioridade){ maior = dir;}
  if (maior != indice) {
    Troca(&H->heap[indice], &H->heap[maior]);
    transformaMaximo(H, maior);
  }
}

void Troca(Clientes *x, Clientes *y){
  Clientes aux = *x;
  *x = *y;
  *y = aux;
}

int ehNum(char c){
  if (c-'0' > 47 && c-'0' < 58){
    return 1;
  }
  return 0;
}