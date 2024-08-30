#include <stdio.h>
#include <stdlib.h>

#include<pthread.h>
#include "timer.h"


#define TEXTO

float * f_thread(void *arg){//float *matriz1, float *matriz2, int N, int M, int K){
  float *matrizR; //matriz resultado
  matrizR = (float*) malloc(sizeof(float) * N * K);


  float soma_parcial;
  for(int i=0; i<N; i++){
    for(int j=0; j<K; j++){
      soma_parcial = 0;
      for(int k=0; k<M; k++){
        soma_parcial += matriz1[i*M + k]*matriz2[k*K + j];
      }
      matrizR[i*M + j] = soma_parcial;
    }}
  return matrizR;
}


int main(int argc, char *argv[]){
  float *MatrizA;
  float *MatrizB;
  float *MatrizC;
  int Nlinhas, Mcolunas, Nlinhas2, Mcolunas2;
  long long int tam1, tam2, tam3;

  FILE* arquivo1;
  FILE* arquivo2;
  size_t ret;

  if(argc < 3) {printf("ERRO! Inisira os argumentos corretamente: \n %s <arquivoMatriz1> <arquivoMatriz2>\n", argv[0]); return 1;}

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

  MatrizC = f_seq(MatrizA, MatrizB, Nlinhas, Mcolunas, Mcolunas2);

#ifdef TEXTO
  printf("Matriz de Entrada A:\n");
  for(int i=0; i<Nlinhas; i++){
    for(int j=0; j<Mcolunas; j++){ printf("%.5f ", MatrizA[i*Mcolunas+j]);}
    printf("\n");}

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

  return 0;
}
