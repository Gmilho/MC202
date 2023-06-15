#include <stdio.h>
#include <stdlib.h>
#include "FilaPrioridade.c"
#define FILA_MAX 100

void ExecutaComando(char *strCMD, FilaP *filaDePrioridades);

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
  FilaP *filaDePrioridade = (FilaP*)calloc(1, sizeof(FilaP));
  filaDePrioridade->heapMax = CriaHeap(FILA_MAX);
  filaDePrioridade->heapMin = CriaHeap(FILA_MAX);
  filaDePrioridade->nelems = 0;
  filaDePrioridade->maxsize = FILA_MAX;

  char *strComando = (char*)calloc(26, sizeof(char));
  for (int i=0; i<n; i++){
    if(fgets(strComando, 26, fp)){
      strComando[strcspn(strComando, "\n")] = '\0';
    }
    ExecutaComando(strComando, filaDePrioridade);
  }
  fclose(fp);
  return 0;
}

void ExecutaComando(char *strCMD, FilaP *filaDePrioridades){
  char cmd = strCMD[0];
  int prioridadeC;
  char nomeCliente[21];

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
    
      InsereNoHeap(filaDePrioridades->heapMax, nomeCliente, prioridadeC);
    
      transformaMaximo(filaDePrioridades->heapMax, 0);
    
      InsereNoHeap(filaDePrioridades->heapMin, nomeCliente, prioridadeC);

      transformaMinimo(filaDePrioridades->heapMin, 0);
  }
  
  if (cmd == 'P'){
    printf("[%s %d ... %s %d]\n", filaDePrioridades->heapMax->heap[0].sobrenome, filaDePrioridades->heapMax->heap[0].prioridade, filaDePrioridades->heapMin->heap[0].sobrenome, filaDePrioridades->heapMin->heap[0].prioridade);
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

    /*for (int x = 0; x < H->maxsize; x++){
      if (H->heap[x].sobrenome == nomeCliente){
        H->heap[x].prioridade = prioridadeC;
      }
    }*/
    
  }
}