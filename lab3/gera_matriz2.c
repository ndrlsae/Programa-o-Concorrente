#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define TEXTO

int main(int argc, char*argv[]){
  float *matriz; //ponteiro pra float
  int Nlinhas, Mcolunas; //dimensões da matriz NxM
  long long int tam; //quantidade de termos na matriz

  float pi = 3.141592;
  FILE* arquivo;
  size_t ret;

  if(argc < 4) {printf("ERRO! Insira os argumentos corretos: \n %s <linhas> <colunas> <arquivosaida.bin> \n", argv[0]); return 1;}

  Nlinhas = atoi(argv[1]);
  Mcolunas = atoi(argv[2]);
  tam = Nlinhas * Mcolunas;

  //aloca memória para a matriz (como vetor de tamanho N*M)
  matriz = (float*) malloc(sizeof(float) * tam);
  if(!matriz){printf("Erro de alocação da matriz\n"); return 2;}

  //construindo matriz com números "aleatórios"
  srand(time(NULL));
  for(long int i = 0; i<tam; i++){
    *(matriz+i) = (rand() % 100) * pi/3;
  }

#ifdef TEXTO
  printf ("Matriz %ix%i:\n", Nlinhas, Mcolunas);

  for(int i=0; i < Nlinhas; i++){
    for(int j=0; j <Mcolunas; j++){
      printf("%0.5f ", matriz[i*Mcolunas + j]);
    }
    printf("\n");
  }
#endif 

  //salvando a matriz no arquivo
  arquivo = fopen(argv[3], "wb"); //arquivo binário
  if(!arquivo){printf("Erro abrindo arquivo\n"); return 3;}

  ret = fwrite(&Nlinhas, sizeof(int), 1, arquivo);
  ret = fwrite(&Mcolunas, sizeof(int), 1, arquivo);

  ret = fwrite(matriz, sizeof(float), tam, arquivo);

  if(ret<tam){printf("Erro escrevendo no arquivo\n"); return 4;}

  fclose(arquivo);
  free(matriz);
  return 0;
}
