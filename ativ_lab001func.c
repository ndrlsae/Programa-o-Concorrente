#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
  int idThread, nThreads;
} t_Args;


typedef struct{
  int Val, idVector;
} idNum;


//void* *soma1(void *arg){
//  int n = *(int*) arg;
//
//  for(int j = n; j<=N; j+M){
//    vector[j].Val = vector[j].Val + 1;
//    printf("Somando 1 ao valor %d na posição %d do vetor \n", vector[j].Val, j);
//  }
//}

int main(int argc, char* argv[]) {
  int *args;

  if(argc < 3){
    printf("Erro 1\n");

    return 1;
  }

  int M = atoi(argv[1]);
  int N = atoi(argv[2]);

  printf("M = %d e N = %d \n", M, N);


  printf("esse é o argumento 3 %s\n", argv[3]);  
  printf("esse é o primeiro char do argumento 3 %c\n", argv[3][0]);
//  if(argc < 3 + N){
//    printf("Erro 2");
//    return 2;
//  }


  idNum vector[N];
  for(int i = 0; i < N; i++){
    char *val = &argv[3][i];
    printf("esse é o val %s \n", val);
    vector[i].Val = atoi(val);
    vector[i].idVector = i;
  }


void *soma1(void *arg){
  int n = *(int*) arg;

  for(int j = n; j < N; j+=M){
    vector[j].Val = vector[j].Val + 1;
    printf("Somando 1 ao valor %d na posição %d do vetor \n", vector[j].Val, j);
    printf("fim do for com j = %d \n",j);
  }
  printf("saimos do for");
  pthread_exit(NULL);
}

  printf("Oii to aqui na 67\n");
  //int j = 0;
  //int r = 0;
  //for(int i = 0; i<=N; i+=M){
  //  j = j+1;
  //}
  //r = N - M*j;

  pthread_t tid_sistema[M];

  for(int i=0; i<M; i++){
    printf("Alocando\n");

    args = malloc(sizeof(idNum));
    if(args == NULL){
      printf("erro aloca\n");
      return 3;
    }
    printf("Alocou\n");
    *args = i;

    printf("Criando thread número %d \n", i);

    if(pthread_create(&tid_sistema[i], NULL, soma1, (void*) args)){
      printf("Erro na criação de thread\n");
    }
    printf("fim do for %d \n", i);

  }

  printf("Fim da thread principal\n");

  pthread_exit(NULL);

  
}
