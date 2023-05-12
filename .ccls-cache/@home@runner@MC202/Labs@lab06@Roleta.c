#include<stdlib.h>
#include<stdio.h>
#include"Pilha.h"

int Operacoes(struct pilha *p, char *strInp, int tmInp);
int CharEhNumero(char c);

int main(int argc, char*argv[]){
    FILE *fp = fopen(argv[1], "r");

    int n;
    fscanf(fp, "%d", &n);
    struct pilha *n_pilha = novaPilha(n);
    char strEntrada[n];
    for (int i = 0; i < n; i++){
        char buffer;
        scanf("%c", &buffer);
        strEntrada[i] = buffer;
    }
    
    printf("%d", Operacoes(n_pilha, strEntrada, n));

    return 0;
}

int Operacoes(struct pilha *p, char *strInp, int tmInp){
    for (int i = 0; i < tmInp; i++){
        if(CharEhNumero(strInp[i])){ Empilha(p, (strInp[i]-'0'));}
        else{
            switch(strInp[i]){
                int elem;
                case '+':
                    if (p->stack[p->topo] == 0){ break;}
                    elem = Desempilha(p);
                    elem += Desempilha(p);
                    Empilha(p, elem);
                break;
            
                case 'D':
                    elem = Desempilha(p) * 2;
                    Empilha(p, elem);
                break;
            
                case 'C':
                    Desempilha(p);
                break;
            
                case 'I':
                    elem = Desempilha(p) * -1;
                    Empilha(p, elem);
                break;
            }
        }
    }
    return Desempilha(p);
}

int CharEhNumero(char c){
    if ((int)c <= 57 && (int)c >= 48){
        return 1;
    }
    return 0;
}