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
void executaHashing(hash *HashTable, int chave);
int executaBuscaHash(hash *HashTable, char *nome);

int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  int n;
  fscanf(fp, "%d", &n);
  hash *HashT = CriaTabelaHash(n);
  for (int i = 0; i < n; i++){
    char *nomeH;
    fgets(nomeH, 51, fp);
    int chave = criaChave(nomeH);
    executaHashing(HashT, chave);
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

void executaHashing(hash *HashTable, int chave){
  int indice = (chave % 100);
  HashTable->listaHash[indice].valor = chave;
}

int BuscaLista(lista *listaAux, int hashId){
  if (listaAux->valor == hashId){
   return 1; 
  }
  else BuscaLista(listaAux->prox, hashId);
  return 0;
}

int executaBuscaHash(hash *HashTable, char *nome){
  int chave = criaChave(nome);
  int hashId;
  for (int i = 0; i < HashTable->size; i++){
    if (BuscaLista(&HashTable->listaHash[i], hashId)){
      return 1;
    }
  }
  return 0;
}