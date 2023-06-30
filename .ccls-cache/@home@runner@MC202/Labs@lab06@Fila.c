#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum _bool {
  false, true
} bool;

typedef struct _fila {
    int ini, fim; // Posição inicial e final da fila
    int qtde; // Número de elementos na fila
    int tam_max; // Tamanho máximo na fila
    int *val; // Vetor com os valores
} Fila;

/* Prototipagem das funções */
Fila *CriaFila(int tam_max);
void DestroiFila(Fila **Q);
bool FilaVazia(Fila *Q);
bool FilaCheia(Fila *Q);
bool ConsultaFila(Fila *Q, int elem, int *pos);
bool InsereFila(Fila *Q, int elem);
bool RemoveFila(Fila *Q);
void ImprimeFila(Fila *Q);



/* Cria uma fila e retorna um ponteiro para ela */
Fila *CriaFila(int tam_max) {
    Fila *Q    = (Fila*) calloc(1, sizeof(Fila));
    Q->val     = (int*) calloc(tam_max, sizeof(int));
    Q->tam_max = tam_max;
    Q->qtde    = 0;
    Q->ini     = Q->fim = 0;

    return Q;
}

/* Destroi a fila na memória */
void DestroiFila(Fila **Q) {
    Fila *Qaux = *Q;
    if (Qaux != NULL){
      free(Qaux->val); // desaloca o vetor de int
      free(Qaux);
      *Q = NULL;
    }
}

/* Checa se a fila está vazia */
bool FilaVazia(Fila *Q) {
    return (Q->qtde == 0);
}

/* Checa se a fila está cheia */
bool FilaCheia(Fila *Q) {
    return (Q->qtde == Q->tam_max);
}

/* Checa se um elemento está presente na fila e retorna sua posição */
bool ConsultaFila(Fila *Q, int elem, int *pos)
{
    if (FilaVazia(Q)) {
        printf("Aviso: Fila está vazia\n");
        return false; // falha ao consultar fila
    }
    else {
      /* Note que se a fila estiver cheia, Q->ini == Q->fim */
      for (int i=0; i < Q->qtde; i++){	
	if (elem == Q->val[(i+Q->ini)%Q->tam_max]){
	  *pos = (i+Q->ini)%Q->tam_max;
	  return true; // sucesso ao consultar fila
	}
      }
    }
    return false;
}

/* Insere um valor (elem) na fila */
bool InsereFila(Fila *Q, int elem) {
    if (FilaCheia(Q)) {
        printf("Aviso: Fila está cheia\n");
        return false; // falha na insercao
    }
    else {
        Q->val[Q->fim] = elem;
        Q->fim = (Q->fim+1) % Q->tam_max;
        Q->qtde++; 
        return true; // sucesso na insercao
    }
}

/* Remove o elemento na frente da fila */
bool RemoveFila(Fila *Q) {
    if (FilaVazia(Q)) {
        printf("Aviso: Fila está vazia\n");
        return false; // falha na remocao
    }
    else {
      Q->ini = (Q->ini+1) % Q->tam_max;
      Q->qtde--; 
      return true; // sucesso na remocao
    }
}

/* Imprime a fila */
void ImprimeFila(Fila *Q)
{
  for (int i=0; i < Q->qtde; i++){	
    printf("%d ",Q->val[(i+Q->ini)%Q->tam_max]);
  }
  printf("\n");
}

/* Lê o input */
void LeArquivo(char *arq, int *dias, int *atraso, int *esquece){
	
	FILE *fp = fopen(arq,"r");
	fscanf(fp, "%d %d %d\n", dias, atraso, esquece);
	fclose(fp);
}

/* Função solução */
int Solucao(Fila *Q, int dias, int atraso, int esquece){
  InsereFila(Q, 1);
  for (int i = 1; i < dias+1; i++){
    for (int j = Q->ini; j < Q->qtde; j++){
      if (i - Q->val[j] >= esquece){
        RemoveFila(Q);
      }
      else if(i - Q->val[j] >= atraso){
        InsereFila(Q, i);
      }
    }
  }
  return Q->qtde;
}

/* A Função main está pronta */
int main(int argc, char **argv){

  /* Declarações */
	int dias, atraso, esquece, resposta;
	clock_t comeco, fim;
	double tempo;
	Fila *Q = CriaFila(100000);

  /* Lendo o Input*/
	LeArquivo(argv[1], &dias, &atraso, &esquece);

  /* Solucionando o problema */
	comeco = clock();
	resposta = Solucao(Q, dias, atraso, esquece);
	fim = clock();
	
	tempo = (((double) (fim - comeco))/CLOCKS_PER_SEC)*1000000;

  /* Liberando a fila da memória*/
	DestroiFila(&Q);
	
  /*Printando o resultado */
	if(argc > 2) printf("Resposta: %d\nTempo: %.0lf microsegundos\n",resposta,tempo);
	else printf("%d\n",resposta);
	
	return 0;
}