#include<stdlib.h>
#include<stdio.h>

typedef struct NoLista{
    int base;
    int expoente;
    struct NoLista *prox;
}No;

typedef struct _Lista{
  int tam;
  No *NoCabeca;
}Lista;

void Troca(No *a, No *b);
void OrdenaExpoente(No *NoCabeca);
void CalculaDerivada(No *NoCabeca);
Lista  *InsereNaLista(Lista *Lista, int F_base, int F_expoente);
void ImprimeLista(No *NoCabeca);
void RemoveFinalDaLista(No *NoFinalLista);
void RemoveInicioDaLista(No *NoIniLista);
double pot(double X, int potencia);
void ImprimeResultadoX(No *NoCabeca, float x);
int Tamanho(Lista *Lista);

int main(int argc, char **argv){
  int nNos;
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL){
    perror("Erro de Leitura: ");
    return (-1);
  }

  //float x = atof(argv[2]);
  
  if(!fscanf(fp, "%d", &nNos)){
    return 0;
  }

  Lista *Lista = calloc(1, sizeof(Lista));
  if (Lista){
    Lista->NoCabeca = NULL;
    Lista->tam = 0;
  }
  
  for (int i = 0; i < nNos; i++){
    int F_base, F_expoente;
    if(!fscanf(fp, "%d %d", &F_base, &F_expoente)){
      return 0;
    }
    InsereNaLista(Lista, F_base, F_expoente);
  }

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

Lista *InsereNaLista(Lista *Lista, int F_base, int F_expoente){
    No *p = (No*)calloc(1, sizeof(No));
    p->base = F_base;
    p->expoente = F_expoente;
    p->prox = NULL;
    if (Lista == NULL){
      Lista->NoCabeca = p;
    } else {
      p->prox = Lista->NoCabeca;
      Lista->NoCabeca = p;
    }
  Lista->tam++;
  return Lista;
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

void CalculaDerivada(struct NoLista *NoCabeca){
  if (NoCabeca == NULL){ return;}
  CalculaDerivada(NoCabeca->prox);
  if(NoCabeca != NULL){
    int exp = NoCabeca->expoente;
    NoCabeca->expoente = NoCabeca->expoente - 1;
    NoCabeca->base = NoCabeca->base * exp;
  }
}

void ImprimeLista(struct NoLista *NoCabeca){
  if(NoCabeca == NULL){ return;}
  ImprimeLista(NoCabeca->prox);
  if (NoCabeca->base == 0){ exit(0);}
  if(NoCabeca->base < 0){
    printf("- %.2fx^%d ", (double)NoCabeca->base * (-1), NoCabeca->expoente);
  } else {
    printf("+ %.2fx^%d ", (double)NoCabeca->base, NoCabeca->expoente);
  }
}

void RemoveFinalDaLista(No *NoFinalLista){
  No *ant = NULL;
  No *aux = NoFinalLista;
  if (aux == NULL){ return;}
  while (aux->prox != NULL){
    ant = aux;
    aux = aux->prox;
  }
  ant->prox = NULL;
  free(aux);
}

void RemoveInicioDaLista(No *NoIniLista){
  No *aux = NoIniLista;
  NoIniLista = NoIniLista->prox;
  free(aux);
}

double pot(double X, int potencia) {
  double resultado = 1.0;
  if (potencia != 0){
    for(int i=0; i<potencia; i++) {
      resultado *= X;
    }
  }
  return resultado;
}

void ImprimeResultadoX(No *NoCabeca, float x){
  float resultado = 0.0;
  while(NoCabeca != NULL){
    float p_resultado = NoCabeca->base * (pot(x, NoCabeca->expoente));
    resultado += p_resultado;
    printf("%d %d\n", NoCabeca->base, NoCabeca->expoente);
    NoCabeca = NoCabeca->prox;
  }
  printf("%lf\n", resultado);
}

int Tamanho(Lista *Lista){
  return Lista->tam;
}