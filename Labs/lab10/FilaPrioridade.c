#include "FilaPrioridade.h"

//TODO alterar funcao retorna para nao retirar da fila

Heap *CriaHeap(int maxsize){
  Heap *aux = (Heap*)malloc(sizeof(Heap));
  aux->maxsize = maxsize;
  aux->nelems = 0;
  aux->heap = (Clientes*)calloc(maxsize, sizeof(Clientes));
  return aux;
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
  while (i != 0 && H->heap[i].prioridade < H->heap[Pai(i)].prioridade){
    Troca(&H->heap[i], &H->heap[Pai(i)]);
    i = Pai(i);
  }
  while (i != 0 && H->heap[i].prioridade > H->heap[Pai(i)].prioridade){
    Troca(&H->heap[i], &H->heap[Pai(i)]);
    i = Pai(i);
  }
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

Clientes retornaUltimoCliente(Heap *H){
  if (HeapVazio(H) == 1){
    Clientes dummyCliente;
    dummyCliente.prioridade = -1;
    return dummyCliente;
  }
  transformaMinimo(H, 0);
  Clientes ultCliente = H->heap[0];
  H->heap[0] = H->heap[H->nelems - 1];
  H->nelems--;
  return ultCliente;
}

Clientes retornaPrimCliente(Heap *H){
  if (HeapVazio(H) == 1){
    Clientes dummyCliente;
    dummyCliente.prioridade = -1;
    return dummyCliente;
  }
  transformaMaximo(H, 0);
  Clientes primCliente = H->heap[0];
  H->heap[0] = H->heap[H->nelems - 1];
  H->nelems--;
  return primCliente;
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