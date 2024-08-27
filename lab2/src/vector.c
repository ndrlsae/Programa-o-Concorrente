#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

//#define TEXTO


float* f_vector(long int dim){
  float* vetor; //vetor retorno
  vetor = (float*) malloc(sizeof(float) * dim); //inicializei o ponteiro
  if(!vetor){printf("erro alocando\n"); return NULL;}
  
  float x; //elemento a ser colocado no vetor
  //double soma = 0; //acumula a soma do vetor

  int fator = 1;
  float pi = 3.1415926;


  //srand(time(NULL));
  for(long int i = 0; i < dim; i++){
    x = (rand() % MAX)/pi * fator;
    //printf("x = %f \n", x);
    vetor[i] = x;
    //soma += x;
    //printf("soma = %f \n", soma);
    fator *= -1;
  }

  return vetor;

}

int main(int argc, char*argv[]){
  float *vetor1, *vetor2;
  long int n;
  double prod_int = 0;
  FILE *descritorArquivo;
  size_t ret;

  if(argc < 3) { printf("falta argumento\n"); return 1;}

  n = atoi(argv[1]);

  vetor1 = f_vector(n); 
  vetor2 = f_vector(n); 

  for(long int i = 0; i<n; i++){
    prod_int += vetor1[i]*vetor2[i];
  }

  #ifdef TEXTO
  printf("%ld\n", n);

  printf("vetor1: \n");
  for(long int i = 0; i < n; i++){
    printf("%f ,", vetor1[i]);
  }
  printf("\n");

  printf("vetor2: \n");
  for(long int i = 0; i < n; i++){
    printf("%f, ", vetor2[i]);
  }
  printf("\n");

  printf("produto interno = %.26f\n", prod_int);

  #endif

  //escreve vetor no arquivo
  descritorArquivo = fopen(argv[2], "wb"); //write binary
  if(!descritorArquivo){ printf("Erro criando arquivo\n"); return 3;}

  ret = fwrite(&n, sizeof(long int), 1, descritorArquivo);
  ret = fwrite(vetor1, sizeof(float), n, descritorArquivo);
  ret = fwrite(vetor2, sizeof(float), n, descritorArquivo);

  if(ret < n){ printf("Erro de escrita no arquivo\n"); return 4;}

  ret = fwrite(&prod_int, sizeof(double), 1, descritorArquivo);

  fclose(descritorArquivo);
  free(vetor1);
  free(vetor2);

  return 0;


}
  
