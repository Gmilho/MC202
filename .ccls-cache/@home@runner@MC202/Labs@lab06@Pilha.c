#include<stdio.h>
#include<stdlib.h>
#include"Pilha.h"

struct pilha* novaPilha(int n){
 struct pilha *p = (struct pilha*)calloc(1, sizeof(struct pilha));
 p->tamanho = n;
 p->topo = -1;
 p->stack = (int*)calloc(n, sizeof(int));
 return p;
}

int TamanhoPilha(struct pilha *p){
 return p->topo +1; 
}

int PilhaEstaVazia(struct pilha *p){
 return TamanhoPilha(p) == 0; 
}

int PilhaEstaCheia(struct pilha *p){
 return TamanhoPilha(p) == p->tamanho - 1;
}

void Empilha(struct pilha *p, int elem){
  if(PilhaEstaCheia(p)){ printf("Pilha cheia\n"); exit(0);}
  p->topo += 1;
  p->stack[p->topo] = elem;
}

int Desempilha(struct pilha *p){
 if(!PilhaEstaVazia(p)){ int elm = p->stack[p->topo]; p->topo--; return elm;}
 return 0;
}

int RetornaElemAntTopo(struct pilha *p){
 if(!PilhaEstaVazia(p)){ return p->stack[p->topo - 1];}
 return 0;
}