#include <stdio.h>
#include <stdlib.h>
#include "FilaPrioridade.c"

void ExecutaComando(char *strCMD, FilaP *filaDePrioridades);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  
  int n;
  fscanf(fp, "%d", &n);
  FilaP *filaDePrioridade = (FilaP*)calloc(1, sizeof(FilaP));
  filaDePrioridade->heapMax = CriaHeap(100);
  filaDePrioridade->heapMin = CriaHeap(100);
  filaDePrioridade->nelems = 0;
  filaDePrioridade->maxsize = 100;
  
  for (int i=0; i<n; i++){
    char *strComando;
    fgets(strComando, 25, fp);
    //executa_comando(cmd, FilaP)
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
      prioridadeC = strCMD[i] - '0';
    
      InsereNoHeap(filaDePrioridades->heapMax, nomeCliente, prioridadeC);
      transformaMaximo(filaDePrioridades->heapMax, 0);
      InsereNoHeap(filaDePrioridades->heapMin, nomeCliente, prioridadeC);
      transformaMinimo(filaDePrioridades->heapMax, 0);
  }
  
  if (cmd == 'P'){
    printf("[%s %d ... %s %d]\n", filaDePrioridades->heapMax->heap[0].sobrenome, filaDePrioridades->heapMax->heap[0].prioridade, filaDePrioridades->heapMin->heap[0].sobrenome, filaDePrioridades->heapMin->heap[0].prioridade);
  }
  
  if (cmd == 'L'){
    printf("Mesa liberada para Sr(a) %s.\n", filaDePrioridades->heapMax->heap[0].sobrenome);
  }
  
  if (cmd == 'D'){
    printf("Sr(a) %s desistiu de esperar e foi embora.\n", filaDePrioridades->heapMin->heap[0].sobrenome);
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
    prioridadeC = strCMD[i] - '0';

    /*for (int x = 0; x < H->maxsize; x++){
      if (H->heap[x].sobrenome == nomeCliente){
        H->heap[x].prioridade = prioridadeC;
      }
    }*/
    
  }
}