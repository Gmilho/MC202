#include<stdlib.h>
#include<stdio.h>

typedef struct NoLista{
    int base;
    int expoente;
    struct NoLista *prox;
}No, ListaLigada;

void OrdenaExpoente(struct NoLista *NoCabeca);
void CalculaDerivada(struct NoLista *NoCabeca);
void InsereNaLista(struct NoLista **NoCabeca, int F_base, int F_expoente);
void ImprimeLista(struct NoLista *NoCabeca);

int main(int argc, char *argv[]){
    char *nomearq;
    int nNos;
    nomearq = argv[1];
    FILE *fp = fopen(nomearq, "r");

    fscanf(fp, "%d", &nNos);

    No *NoCabeca = (No*)malloc(sizeof(No));

    for (int i = 0; i < nNos; i++){
        int F_base, F_expoente;
        fscanf(fp, "%d %d", &F_base, &F_expoente);
        InsereNaLista(&NoCabeca, F_base, F_expoente);
    }

    CalculaDerivada(NoCabeca);
    OrdenaExpoente(NoCabeca);
    ImprimeLista(NoCabeca);

    return 0;
}

void InsereNaLista(struct NoLista **NoCabeca, int F_base, int F_expoente){
    No *p = (No*)malloc(sizeof(No));
    p->base = F_base;
    p->expoente = F_expoente;
    p->prox = *NoCabeca;
    *NoCabeca = p;
}

void OrdenaExpoente(struct NoLista *NoCabeca){
    No *p = NoCabeca;
    while (p->prox != NULL){
        if(p->expoente < p->prox->expoente){
            if (p->expoente < 0){
                p = p->prox;
            }
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
    while (p != NULL){
        p->base = p->base * p->expoente;
        p->expoente = p->expoente-1;
        p = p->prox;
    }
}

void ImprimeLista(struct NoLista *NoCabeca){
    while(NoCabeca != NULL){
        if (NoCabeca->prox->base == 0){
            printf(" + %.2fx^%d ", (double)NoCabeca->base, NoCabeca->expoente);
            exit(0);
        }
        if (NoCabeca->base < 0){
            printf(" - %.2fx^%d ", ((double)NoCabeca->base * -1), NoCabeca->expoente);
            NoCabeca = NoCabeca->prox;
        }
        printf(" + %.2fx^%d ", (double)NoCabeca->base, NoCabeca->expoente);
        NoCabeca = NoCabeca->prox;
    }
}