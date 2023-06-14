#include "ArvoreBinaria2.h"

NoArvoreBinaria *criaNo(int data){
  NoArvoreBinaria *novoNo = (NoArvoreBinaria*)calloc(1, sizeof(NoArvoreBinaria));
  novoNo->info = data;
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  return novoNo;
}

NoArvoreBinaria utConst(int sim[], int pos[]);