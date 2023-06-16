#include<stdlib.h>
#include<stdio.h>

typedef struct NoLista{
   int tamanho;
    int base;
    int expoente;
    struct NoLista *prox;
}No, ListaLigada;

void OrdenaExpoente(struct NoLista *NoCabeca);
void CalculaDerivada(struct NoLista *NoCabeca);
void InsereNaLista(struct NoLista **NoCabeca, int F_base, int F_expoente);
void ImprimeLista(struct NoLista *NoCabeca);
void ImprimeResultadoX(struct NoLista *NoCabeca, char X);
int Tamanho(struct NoLista *NoCabeca);

int main(int argc, char *argv[]){
    char *nomearq;
    nomearq = argv[1];
    char X = argv[2];
    FILE *fp = fopen(nomearq, "r");

    int nNos;

    fscanf(fp, "%d", &nNos);

    No *NoCabeca = (No*)malloc(sizeof(No));

    for (int i = 0; i < nNos; i++){
        int F_base, F_expoente;
        fscanf(fp, "%d %d", &F_base, &F_expoente);
        InsereNaLista(&NoCabeca, F_base, F_expoente);
    }



    return 0;
}

void InsereNaLista(struct NoLista **NoCabeca, int F_base, int F_expoente){
    No *p = (No*)malloc(sizeof(No));
    p->base = F_base;
    p->expoente = F_expoente;
    p->prox = *NoCabeca;
    *NoCabeca = p;
    *NoCabeca->tamanho = *NoCabeca->tamanho+1;
}

void OrdenaExpoente(struct NoLista *NoCabeca){
    No *p = NoCabeca;
    while (p->prox != NULL){
        if(p->expoente < p->prox->expoente){
            int tempB, tempEx;
            tempB = p->base;
            tempEx = p->expoente;
            p->base = p->prox->base;
            p->prox->base = tempB;
            p->expoente = p->prox->expoente;
            p->prox->expoente = tempEx;
        }
        p = p->prox;
    }
}

void CalculaDerivada(struct NoLista *NoCabeca){
    No *p = NoCabeca;
    while (p->prox != NULL){
        p->base = p->base * p->expoente;
        p->expoente = p->expoente-1;
        p = p->prox;
    }
}


void ImprimeLista(struct NoLista *NoCabeca){
    while(NoCabeca != NULL){
        if (NoCabeca->prox->base == 0 || NoCabeca->prox->prox == NULL){
            printf("%.2fx^%d ", (double)NoCabeca->base, NoCabeca->expoente);
            exit(0);
        }
        printf("%.2fx^%d + ", (double)NoCabeca->base, NoCabeca->expoente);
        NoCabeca = NoCabeca->prox;
    }
}

void ImprimeResultadoX(struct NoLista *NoCabeca, char X){
    No *p = NoCabeca;
    int cnvX = X - '0';
    double resultado, potencia;
    while(p->prox != NULL){
        if (p->expoente == 0){ potencia = 1;}
        else {
            for (int i = 0; i < p->expoente+1; i++){
                potencia = potencia * cnvX;
            }
        }
        resultado += p->base * potencia;
        p = p->prox;
    }
    printf("%lf", resultado);
}

int Tamanho(struct NoLista *NoCabeca){
    if (NoCabeca != NULL){
        return NoCabeca->tamanho;
    } else { return 0;}
}