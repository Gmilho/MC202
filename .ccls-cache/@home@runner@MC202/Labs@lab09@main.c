#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPrioridade.c"

void ExecutaComando(char *strCMD, Heap *filaDePrioridades);

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

  Heap *fila = (Heap*)calloc(1, sizeof(Heap));
  fila->tamMaxH = 0;
  fila->tamMinH = 0;
  
  char strComando[26];
  for (int i = 0; i < n; i++){
    if(fgets(strComando, 26, fp)){
      strComando[strcspn(strComando, "\n")] = '\0';
    }
    ExecutaComando(strComando, fila);
  }
  fclose(fp);
  free(fila);
  
  return 0;
}

void ExecutaComando(char *strCMD, Heap *filaDePrioridades){
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
    InsereNoHeap(filaDePrioridades, nomeCliente, prioridadeC);
  }
  
  if (cmd == 'P'){
    transformaMinimo(filaDePrioridades->heapMin, filaDePrioridades->tamMinH, 0);
    transformaMaximo(filaDePrioridades->heapMax, filaDePrioridades->tamMaxH, 0);
    int i = retornaIdxMaxHeap(filaDePrioridades);
    int j = retornaIdxMinHeap(filaDePrioridades);
    
    if (HeapVazio(filaDePrioridades)){ printf("[ ]\n");}
    if (filaDePrioridades->heapMax[i].prioridade == 0 || filaDePrioridades->heapMin[j].prioridade == 0){ printf("[ ]\n");}
    else {
      printf("[%s %d ... %s %d]\n", filaDePrioridades->heapMax[i].sobrenome, filaDePrioridades->heapMax[i].prioridade, filaDePrioridades->heapMin[j].sobrenome, filaDePrioridades->heapMin[j].prioridade);
    }
    
  }
  
  if (cmd == 'L'){
    if (HeapVazio(filaDePrioridades)){ return;}
    transformaMaximo(filaDePrioridades->heapMax, filaDePrioridades->tamMaxH, 0);
    printf("Mesa liberada para Sr(a) %s.\n", filaDePrioridades->heapMax[0].sobrenome);
    removeClienteMax(filaDePrioridades, filaDePrioridades->heapMax[0].sobrenome);
  }
  
  if (cmd == 'D'){
    if (HeapVazio(filaDePrioridades)){ return;}
    transformaMinimo(filaDePrioridades->heapMin, filaDePrioridades->tamMinH, 0);
    printf("Sr(a) %s desistiu de esperar e foi embora.\n", filaDePrioridades->heapMin[0].sobrenome);
    removeClienteMin(filaDePrioridades, filaDePrioridades->heapMin[0].sobrenome);
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
    atualizaPrioridade(filaDePrioridades, nomeCliente, prioridadeC);
  }
}