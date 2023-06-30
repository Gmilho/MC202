#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Pilha.c"

#define tmnh_Buffer 1000

int Operacoes(Pilha *p, char *strInp, int tmInp);
int CharEhNumero(char c);

int main(int argc, char **argv){
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
      perror("Erro de leitura: ");
      return (-1);
    }
    char buffer[tmnh_Buffer];
    int n;

    if(!fscanf(fp, "%d", &n)){
      return 0;
    }
  
    char *strEntrada = (char *)calloc(n+1, sizeof(char));
    Pilha *n_pilha = CriaPilha(n);

    int i = 0;
    while(fgets(buffer, tmnh_Buffer - 1, fp) != NULL) 
    {
      strEntrada[i] = buffer[0];
      i++;
    }
  
    Operacoes(n_pilha, strEntrada, n);
  
    int res = 0;
    for (int i = 0; i < n; i++){
      res += n_pilha->val[i];  
    }
  
    printf("%d", res);

    DestroiPilha(&n_pilha);
    free(strEntrada);
    fclose(fp);

    return 0;
}

int Operacoes(Pilha *p, char *strInp, int tmInp){
  for (int i = 0; i < tmInp+1; i++){
    if(CharEhNumero(strInp[i])){ Empilha(p, (strInp[i]-'0'));}
    int elem;
    if((int)strInp[i] == 43){
      if (p->qtde >= 1){
        elem = p->val[p->qtde-1] + p->val[p->qtde - 2];
        Empilha(p, elem);
      }
    }
    if((int)strInp[i] == 68){
      elem = p->val[p->qtde-1];
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
  if (c-'0' <= 9 && c-'0' >= 0){
    return 1;
  }
  return 0;
}