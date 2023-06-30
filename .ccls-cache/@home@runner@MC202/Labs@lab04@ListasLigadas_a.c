#include<stdlib.h>
#include<stdio.h>

typedef struct NoLista{
    int base;
    int expoente;
    struct NoLista *prox;
}No, ListaLigada;

void Troca(No *a, No *b);
void OrdenaExpoente(No *NoCabeca);
void CalculaDerivada(No *NoCabeca);
No   *InsereNaLista(No *NoCabeca, int F_base, int F_expoente);
void ImprimeLista(No *NoCabeca);
void DestroiLista(No *NoCabeca);

int main(int argc, char **argv){
  int nNos;
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de Leitura: ");
    return (-1);
  }
  
  if(!fscanf(fp, "%d", &nNos)){
    return 1;
  }

  No *NoCabeca = NULL;
  for (int i = 0; i < nNos; i++){
    int F_base, F_expoente;
    if(!fscanf(fp, "%d %d", &F_base, &F_expoente)){
      return 1;
    }
    NoCabeca = InsereNaLista(NoCabeca, F_base, F_expoente);
  }
  fclose(fp);
  
  OrdenaExpoente(NoCabeca);
  CalculaDerivada(NoCabeca);
  ImprimeLista(NoCabeca);

  DestroiLista(NoCabeca);
  
  return 0;
}

void Troca(No *a, No *b){
  int t_expo = a->expoente;
  int t_base = a->base;
  
  a->expoente = b->expoente;
  a->base = b->base;
  
  b->base = t_base;
  b->expoente = t_expo;
}

No *InsereNaLista(No *NoCabeca, int F_base, int F_expoente){
  No *p = (No*)calloc(1, sizeof(No));
  p->base = F_base;
  p->expoente = F_expoente;
  p->prox = NULL;
  if (NoCabeca == NULL){
    NoCabeca = p;
  } else {
    p->prox = NoCabeca;
    NoCabeca = p;
  }
  return NoCabeca;
}

void OrdenaExpoente(No *NoCabeca){
  int trocado;
  No *aux;
  No *ant = NULL;

  if (NoCabeca == NULL){
    return;
  }
  
  do {
    trocado = 0;
    aux = NoCabeca;
    while (aux->prox != ant){
      if (aux->expoente > aux->prox->expoente && aux->prox->base != 0){
        Troca(aux, aux->prox);
        trocado = 1;
      }
      aux = aux->prox;
    }
  } while(trocado);
  
}

void CalculaDerivada(No *NoCabeca){
  if (NoCabeca == NULL){ return;}
  CalculaDerivada(NoCabeca->prox);
  if(NoCabeca != NULL){
    int exp = NoCabeca->expoente;
    NoCabeca->expoente = NoCabeca->expoente - 1;
    NoCabeca->base = NoCabeca->base * exp;
  }
}

void ImprimeLista(No *NoCabeca){
  if(NoCabeca == NULL){ return;}
  ImprimeLista(NoCabeca->prox);
  if (NoCabeca->base == 0){ return;}
  if(NoCabeca->base < 0){
    printf("- %.2fx^%d ", (double)NoCabeca->base * (-1), NoCabeca->expoente);
  } else {
    printf("+ %.2fx^%d ", (double)NoCabeca->base, NoCabeca->expoente);
  }
}

void DestroiLista(No *NoCabeca){
  No *aux;
  while (NoCabeca != NULL){
    aux = NoCabeca;
    NoCabeca = NoCabeca->prox;
    free(aux);
  }
}