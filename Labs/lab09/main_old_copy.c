#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPrioridade.c"
#define FILA_MAX 100

void ExecutaComando(char *strCMD, FilaP *filaDePrioridades, Heap *HeapClientes);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de leitura: ");
    return (-1);
  }
  int n;
  if(!fscanf(fp, "%d\n", &n)){
    return 0;
  }
  Heap *HeapClientes = CriaHeap(FILA_MAX);
  FilaP *filaDePrioridade = malloc(sizeof(FilaP));
  filaDePrioridade->heapMin = CriaHeap(FILA_MAX);
  filaDePrioridade->heapMax = CriaHeap(FILA_MAX);
  filaDePrioridade->nelems = 0;
  
  char strComando[26];
  for (int i=0; i<n; i++){
    if(fgets(strComando, 26, fp)){
      strComando[strcspn(strComando, "\n")] = '\0';
    }
    ExecutaComando(strComando, filaDePrioridade, HeapClientes);
  }
  fclose(fp);
  return 0;
}

void ExecutaComando(char *strCMD, FilaP *filaDePrioridades, Heap *HeapClientes){
  char cmd = strCMD[0];
  int prioridadeC;
  char nomeCliente[20];

  if (cmd == 'I'){
      int i = 2, j = 0;
      while (strCMD[i] != ' '){
        nomeCliente[j] = strCMD[i];
        j++, i++;
      }
      nomeCliente[j] = '\0';
      do{
        i++;
      }while(!ehNum(strCMD[i]));

      prioridadeC = 0;
      while(strCMD[i] != '\0'){
        prioridadeC = prioridadeC * 10 + (strCMD[i] - '0');
        i++;
      }
      printf("%d", prioridadeC);
      InsereNoHeap(HeapClientes, nomeCliente, prioridadeC);
      printf("%s, %d", HeapClientes->heap->sobrenome, HeapClientes->heap->prioridade);
      filaDePrioridades->heapMin = HeapClientes;
      transformaMinimo(filaDePrioridades->heapMin, 0);
      filaDePrioridades->heapMax = HeapClientes;
      transformaMaximo(filaDePrioridades->heapMax, 0);
      filaDePrioridades->nelems = HeapClientes->nelems;
  }
  
  if (cmd == 'P'){
    if (filaDePrioridades->heapMax == NULL && filaDePrioridades->heapMin == NULL){
      printf("[ ]");
    }
    else {
      printf("[%s %d ... %s %d]\n", filaDePrioridades->heapMax->heap[0].sobrenome, filaDePrioridades->heapMax->heap[0].prioridade, filaDePrioridades->heapMin->heap[0].sobrenome, filaDePrioridades->heapMin->heap[0].prioridade);
    }
  }
  
  if (cmd == 'L'){
    printf("Mesa liberada para Sr(a) %s.\n", filaDePrioridades->heapMax->heap[0].sobrenome);
    removeCliente(filaDePrioridades->heapMax);
  }
  
  if (cmd == 'D'){
    printf("Sr(a) %s desistiu de esperar e foi embora.\n", filaDePrioridades->heapMin->heap[0].sobrenome);
    removeCliente(filaDePrioridades->heapMin);
  }
  
  if (cmd == 'M'){
    int i = 2, j = 0;
    while (strCMD[i] != ' '){
      nomeCliente[j] = strCMD[i];
      j++, i++;
    }
    nomeCliente[j] = '\0';
    do{
      i++;
    }while(!ehNum(strCMD[i]));

    prioridadeC = 0;
    while(strCMD[i] != '\0'){
      prioridadeC = prioridadeC * 10 + (strCMD[i] - '0');
      i++;
    }
  }
}