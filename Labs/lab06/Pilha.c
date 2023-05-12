#include "Pilha.h"

Pilha *CriaPilha(int tam_max)
{
  Pilha *Q = (Pilha *)calloc(1,sizeof(Pilha));

  Q->val      = (int *)calloc(tam_max,sizeof(int));
  Q->qtde     = 0;
  Q->tam_max = tam_max;
  
  return(Q);
}

void DestroiPilha(Pilha **Q)
{
  Pilha *aux=*Q;

  if (aux != NULL){
    free(aux->val);
    free(aux);
    *Q = NULL;
  }
}

bool PilhaVazia(Pilha *Q)
{
  if (Q->qtde == 0)
    return(true);
  else
    return(false);
}

bool PilhaCheia(Pilha *Q)
{
  if (Q->qtde == Q->tam_max)
    return(true);
  else
    return(false);
}

bool Empilha(Pilha *Q, int elem)
{
  if (PilhaCheia(Q)){
    printf("Aviso: Pilha cheia\n");
    return(false);
  }
  
  Q->val[Q->qtde]=elem; 
  Q->qtde++;
  return(true);
}

bool Desempilha(Pilha *Q, int *elem)
{
  if (PilhaVazia(Q)){
    printf("Aviso: Pilha vazia\n");
    return(false);
  } 
  
  *elem = Q->val[Q->qtde-1]; // topo = Q->qtde-1  
  Q->qtde--;
  return(true);
}

void ImprimePilha(Pilha *Q)
{
  if (PilhaVazia(Q)){
    printf("Aviso: Pilha vazia\n");
    return;
  } 

  for (int i=Q->qtde-1; i >= 0; i--) 
    {
      printf("%d ",Q->val[i]);
    }
  printf("\n");
}

bool ConsultaPilha(Pilha *Q, int elem, int *ndes)
{
  if (PilhaVazia(Q)){
    printf("Aviso: Pilha vazia\n");
    return(false);
  } 

  for (int i=Q->qtde-1,j=0; i >= 0; i--,j++) 
    {
      if (Q->val[i]==elem){
	*ndes = j;
	return(true);
      }
    }
  printf("Aviso: elemento não encontrado\n");
  return(false);
}