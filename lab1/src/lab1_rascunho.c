#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>


typedef struct{
  int Val, idVector;
} idNum;

typedef struct{
  int threads, len, r;
  idNum *lista;
} l_Args;

void *soma1(void *arg){
  l_Args args = *(l_Args*) arg;

  printf("lista antes de somar 1:\n");
  for(int i = 0; i<args.len; i++){ printf("numero %d,   posição %d \n", args.lista[i].Val, args.lista[i].idVector);}

  for(int j = args.r; j < args.len; j += args.threads){
    printf("Somando 1 ao valor %d na posição %d do vetor \n", args.lista[j].Val, j);
    args.lista[j].Val = args.lista[j].Val + 1;
  }

  free(arg);
  pthread_exit(NULL);
}

idNum f_vector(int len){
  idNum vector[len];
  for(int i = 0; i < len; i++){
    vector[i].Val = i + 1;
    vector[i].idVector = i;
    printf("na posição %d temos %d \n", i, i + 1);
  }
 printf("lista criada:\n");
  for(int i = 0; i<len; i++){ printf("numero %d,   posição %d \n", vector[i].Val, vector[i].idVector);}

  return *vector;
}

bool testa(idNum *lista_nova, int len){
  bool resp = true;
  printf("criando lista para fazer teste com o vetor modificado:\n");
  idNum lista_original = f_vector(len);
  for(int i = 0; i < len; i++){
    if (lista_nova[i].Val - (&lista_original)[i].Val != 1){
      resp = false;
      printf("a lista nova tem %d enquanto a original tinha %d na posição %d \n", lista_nova[i].Val, (&lista_original)[i].Val, i);
      printf("Fim do teste\n");
      return resp;
    }

  }
  printf("Tudo certo\n");
  printf("Fim do teste\n");
  return resp;
}


int main(int argc, char* argv[]){
  l_Args *args;

  if(argc < 3){
    printf("Erro 1: insira os argumentos M e N\n");
    return 1;
  }

  int M = atoi(argv[1]);
  int N = atoi(argv[2]);

  printf("M = %d e N = %d \n", M, N);

  idNum Lista = f_vector(N);


  printf("Começar a criação de threads\n");

  pthread_t tid_sistema[M];

  for(int i = 0; i < M; i++){

    args = malloc(sizeof(l_Args));
    if(args == NULL){
      printf("Erro 3: erro na alocação\n");
      return 3;
    }

    args->threads = M;
    args->len = N;
    args->r = i;
    args->lista = &Lista;

    printf("Criando a thread %d \n", i);

    if(pthread_create(&tid_sistema[i], NULL, soma1, (void*) args)){
      printf("Erro na criação da thread %d\n", i);
    }
  }

  printf("Fim da thread principal \n");

  testa(&Lista, N);
  pthread_exit(NULL); 


}


























