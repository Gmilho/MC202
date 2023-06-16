#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _Lista{
  int valor;
  struct _Lista *prox;
} lista;

typedef struct _HashTable{
  lista *listaHash;
  int size;
} hash;

hash *CriaTabelaHash(int size);
int criaChave(char *nome);
void insereHash(hash *HashTable, char *nome);
void insereNoFinal(hash *hashTable, int hashId, int hashVal);
int executaBuscaHash(hash *HashTable, char *nome);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  int n;
  fscanf(fp, "%d", &n);
  hash *HashT = CriaTabelaHash(n);
  for (int i = 0; i < n; i++){
    char nomeH[51];
    if(fgets(nomeH, sizeof(nomeH), fp)!=NULL){
      nomeH[strlen(nomeH) - 1] = '\0';
    }
    insereHash(HashT, nomeH);
  }
  printf("%d", executaBuscaHash(HashT, argv[2]));
}

hash *CriaTabelaHash(int size){
  hash *aux = (hash*)calloc(1, sizeof(hash));
  aux->listaHash = (lista*)calloc(size, sizeof(lista));
  aux->size = size;
  return aux;
}

int criaChave(char *nome){
  int chave = 0;
  for (int i = 0; i < strlen(nome); i++){
   if (nome[i] != '\0'){
    chave = chave * 7 + (nome[i]-'0'); 
   }
  }
  return chave;
}

void insereHash(hash *HashTable, char *nome){
  int chave = criaChave(nome);
  chave = abs(chave); //caso a potência da função ser maior 2^31, a chave vira negativa
  int hashId = (chave % HashTable->size);
  insereNoFinal(HashTable, hashId, chave);
}

void insereNoFinal(hash *hashTable, int hashId, int hashVal){
  lista *aux = (lista*)calloc(1, sizeof(lista));
  lista *ultimo = &hashTable->listaHash[hashId];
  aux->valor = hashVal;
  aux->prox = NULL;
  if (&hashTable->listaHash[hashId] == NULL){
    hashTable->listaHash[hashId] = *aux;
    return;
  }
  while (ultimo->prox != NULL){
    ultimo = ultimo->prox;
  }
  ultimo->prox = aux;
}

int executaBuscaHash(hash *HashTable, char *nome){
  int chave = criaChave(nome);
  chave = abs(chave);
  int hashId = (chave % HashTable->size);
  lista *atual = HashTable->listaHash[hashId].prox;
  if (HashTable->listaHash[hashId].valor == chave){
    return 1;
  } else {
    while (atual != NULL){
      if (atual->valor == chave) return 1;
      else atual = atual->prox;
    }
  }
  return 0;
}