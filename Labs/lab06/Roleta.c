#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include"Pilha.h"

#define tmnh_Buffer 1000

int Operacoes(Pilha *p, char *strInp, int tmInp);
int CharEhNumero(char c);

int main(int argc, char **argv){
    FILE *fp = fopen(argv[1], "r");

    char buffer[tmnh_Buffer];
    int n;

    fscanf(fp, "%d", &n);
    char *strEntrada = (char *)calloc(n+1, sizeof(char));
    Pilha *n_pilha = CriaPilha(n);

    int i = 0;
    while(fgets(buffer, tmnh_Buffer - 1, fp) != NULL) 
    {
      strEntrada[i] = buffer[0];
      i++;
    }
  
    printf("%d", Operacoes(n_pilha, strEntrada, n));

    return 0;
}

int Operacoes(Pilha *p, char *strInp, int tmInp){
    for (int i = 0; i < tmInp+1; i++){
        if(CharEhNumero(strInp[i])){ Empilha(p, (strInp[i]-'0'));}
        int elem;
        if((int)strInp[i] == 43){
            if (p->qtde >= 1){
                elem = p->val[p->qtde] + p->val[p->qtde - 1];
                Empilha(p, elem);
            }
        }
        if((int)strInp[i] == 68){
            Desempilha(p, &elem);
            Empilha(p, elem * 2);
        }
        if((int)strInp[i] == 67){
            Desempilha(p, &elem);
        }
        if((int)strInp[i] == 73){
            Desempilha(p, &elem);
            Empilha(p, elem *-1);
        }
    }
    return p->val[p->qtde-1];
}

int CharEhNumero(char c){
    if ((int)c <= 57 && (int)c >= 48){
        return 1;
    }
    return 0;
}