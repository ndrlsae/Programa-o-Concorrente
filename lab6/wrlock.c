#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//#include "list_int.h"
//#include "timer.h"


#define QTDE_OPS 20
#define QTDE_INI 10
#define MAX_VALUE 100

int read = 0;
int write = 0;
int q_write = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_read, cond_write;

void init_read(){
  pthread_mutex_lock(&mutex);
  while (write > 0 || q_write > 0){
    printf("leitor %i: %i escritores estão escrevendo/esperando, vou esperar\n", read, q_write + 1);
    pthread_cond_wait(&cond_read, &mutex);}
  read++;
  printf("leitor %i: comecei a ler\n", read);
  pthread_mutex_unlock(&mutex);
}

void finish_read(){
  pthread_mutex_lock(&mutex);
  read--;
  if(read == 0){
    printf("TODOS os leitores terminaram de ler \n");
    pthread_cond_signal(&cond_write);}
  printf("leitor %i: terminei de ler \n", read);
  pthread_mutex_unlock(&mutex);
}

void init_write(){
  pthread_mutex_lock(&mutex);
  while(read > 0 || write > 0){
    printf("escritor: %i estão lendo e %i estão escrevendo\n", read, write);
    q_write++;
    pthread_cond_wait(&cond_write, &mutex);
    q_write--;}
  printf("escritor %i: comecei a escrever\n", write);
  write++;
  pthread_mutex_unlock(&mutex);
}

void finish_write(){
  pthread_mutex_lock(&mutex);
  write--;
  pthread_cond_signal(&cond_write);
  printf("parei de escrever e deixei %i na fila \n", q_write);
  pthread_cond_broadcast(&cond_read);
  pthread_mutex_unlock(&mutex);
}










