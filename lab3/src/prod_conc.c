#include <stdio.h>
#include <stdlib.h>

#include<pthread.h>
#include "timer.h"


//#define TEXTO


int Nlinhas, Mcolunas, Nlinhas2, Mcolunas2;
float *MatrizA;
float *MatrizB;
float *MatrizC;

int nthreads;

void * f_thread(void *tid){//float *matriz1, float *matriz2, int N, int M, int K){
  long int id = (long int) tid;
  float soma_parcial;

  for(long int i=id; i<Nlinhas; i+=nthreads){
    for(long int j=0; j<Mcolunas2; j++){
      soma_parcial = 0;
      for(long int k=0; k<Mcolunas; k++){
        soma_parcial += MatrizA[i*Mcolunas + k]*MatrizB[k*Mcolunas2 + j];
      }
      MatrizC[i*Mcolunas2 + j] = soma_parcial;
    }}
  //free(tid);
  pthread_exit(NULL);
}


int main(int argc, char *argv[]){
  long long int tam1, tam2, tam3;

  double inicio, fim, delta;

  FILE* arquivo1;
  FILE* arquivo2;

  FILE* arquivo_saida;

  size_t ret;

  pthread_t *tid_sistema;


  GET_TIME(inicio);

  if(argc < 5) {printf("ERRO! Inisira os argumentos corretamente: \n %s <arquivoMatriz1> <arquivoMatriz2> <arquivosaida> <nº de threads>\n", argv[0]); return 1;}

  nthreads = atoi(argv[4]);


  //extraindo informações dos arquivos

  //Abrindo os arquivos
  arquivo1 = fopen(argv[1], "rb");
  if(!arquivo1) {printf("Erro de abertura do arquivo 1\n"); return 2;}
  
  arquivo2 = fopen(argv[2], "rb");
  if(!arquivo2) {printf("Erro de abertura do arquivo 2\n"); return 2;}

  //Lendo arquivo 1
  ret = fread(&Nlinhas, sizeof(int), 1, arquivo1);
  if(!ret){printf("Erro de leitura nas dimensões do arquivo 1 \n"); return 3;}
  ret = fread(&Mcolunas, sizeof(int), 1, arquivo1);
  if(!ret){printf("Erro de leitura nas dimensões do arquivo 1 \n"); return 3;}
  
  //Lendo arquivo 2
  ret = fread(&Nlinhas2, sizeof(int), 1, arquivo2);
  if(!ret){printf("Erro de leitura nas dimensões do arquivo 2 \n"); return 3;}
  ret = fread(&Mcolunas2, sizeof(int), 1, arquivo2);
  if(!ret){printf("Erro de leitura nas dimensões do arquivo 2 \n"); return 3;}
  


  //testa se podemos multiplicar matrizes com essas dimensões
  if(Mcolunas != Nlinhas2){printf("Erro de dimensão de matrizes. \n Matriz1 é %i x %i e Matriz2 é %i x %i", Nlinhas, Mcolunas, Nlinhas2, Mcolunas2); return 4;}

  tam1 = Nlinhas*Mcolunas;
  tam2 = Nlinhas2*Mcolunas2;
  tam3 = Nlinhas*Mcolunas2;

  //alocando memória para as matrizes
  MatrizA = (float*) malloc(sizeof(float) * tam1);
  if(!MatrizA){ printf("Erro alocando memória para Matriz1\n"); return 3;}

  MatrizB = (float*) malloc(sizeof(float) * tam2);
  if(!MatrizB){ printf("Erro alocando memória para Matriz2\n"); return 3;}
 
  MatrizC = (float*) malloc(sizeof(float) * tam3);
  if(!MatrizC){ printf("Erro alocando memória para a matriz de saída\n"); return 3;} 

  //carregando os elementos do arquivo
  
  ret = fread(MatrizA, sizeof(float), tam1, arquivo1);
  if(ret<tam1){printf("Erro lendo os elementos do arquivo 1\n"); return 5;}

  ret = fread(MatrizB, sizeof(float), tam2, arquivo2);
  if(ret<tam2){printf("Erro lendo os elementos do arquivo 2\n"); return 5;}

  fclose(arquivo1);
  fclose(arquivo2);

  GET_TIME(fim);
  printf("Matriz%ix%i(%lli) * Matriz%ix%i(%lli) \nMatriz%ix%i(%lli)\n%i threads:\n", Nlinhas, Mcolunas, tam1, Nlinhas2, Mcolunas2, tam2, Nlinhas, Mcolunas2, tam3, nthreads);
  delta = fim - inicio;
  printf("Inicialização: %lf\n", delta);

  GET_TIME(inicio);
  tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid_sistema==NULL){printf("Erro malloc de tid_sistema\n"); return 3;}

  //criando threads
  for(long int t=0; t<nthreads; t++){
    if(pthread_create(tid_sistema + t, NULL, f_thread, (void*) t)){
      printf("Erro no pthread_create %li \n", t); return 6;
    }
  }
  for(int i=0; i<nthreads; i++){
    pthread_join(*(tid_sistema + i), NULL);
  }
  
  GET_TIME(fim);
  delta = fim - inicio;
  printf("Processamento: %lf\n", delta);

  GET_TIME(inicio);
  //preenchendo arquivo de saida
  arquivo_saida = fopen(argv[3], "wb");
  if(!arquivo_saida) {printf("Erro criando arquivo de saída\n"); return 7;}

  ret = fwrite(&Nlinhas, sizeof(int), 1, arquivo_saida);
  ret = fwrite(&Mcolunas2, sizeof(int), 1, arquivo_saida);

  ret = fwrite(MatrizC, sizeof(float), tam3, arquivo_saida);
  if(ret < tam3){printf("Erro de escrita no arquivo\n"); return 8;}

  fclose(arquivo_saida);

#ifdef TEXTO
  printf("Matriz de Entrada A:\n");
  for(int i=0; i<Nlinhas; i++){
    for(int j=0; j<Mcolunas; j++){ printf("%.5f ", MatrizA[i*Mcolunas+j]);}
    printf("\n");}

  printf("cheguei no print\n");

  printf("Matriz de Entrada B:\n");
  for(int i=0; i<Nlinhas2; i++){
    for(int j=0; j<Mcolunas2; j++){ printf("%.5f ", MatrizB[i*Mcolunas2+j]);}
    printf("\n");}

  printf("Matriz de Saída C:\n");
  for(int i=0; i<Nlinhas; i++){
    for(int j=0; j<Mcolunas2; j++){ printf("%.5f ", MatrizC[i*Mcolunas2+j]);}
    printf("\n");}
#endif

  free(MatrizA);
  free(MatrizB);
  free(MatrizC);

  GET_TIME(fim);
  delta = fim - inicio;
  printf("Finalização: %lf\n", delta);

  return 0;
}
