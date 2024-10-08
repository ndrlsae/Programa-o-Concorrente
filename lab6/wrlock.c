#include "wrlock.h"

#define QTDE_OPS 20
#define QTDE_INI 10
#define MAX_VALUE 100

int read = 0;
int write = 0;
int q_write = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_read, cond_write;

void init_read(){
  printf("leitor: quero ler\n");
  pthread_mutex_lock(&mutex);
  while (write > 0 || q_write > 0){
    printf("leitor: %i escritores estão escrevendo/esperando, vou esperar\n", q_write + 1);
    pthread_cond_wait(&cond_read, &mutex);}
  read++;
  pthread_mutex_unlock(&mutex);
  printf("leitor: comecei a ler\n");
}

void finish_read(){
  pthread_mutex_lock(&mutex);
  read--;
  printf("leitor: terminei de ler \n");
  if(read == 0){
    printf("TODOS os leitores terminaram de ler \n");
    pthread_cond_signal(&cond_write);}
  pthread_mutex_unlock(&mutex);
}

void init_write(){
  printf("escritor: quero escrever\n");
  pthread_mutex_lock(&mutex);
  while(read > 0 || write > 0){
    printf("escritor: %i estão lendo e %i estão escrevendo\n", read, write);
    q_write++;
    pthread_cond_wait(&cond_write, &mutex);
    q_write--;}
  printf("escritor: comecei a escrever \n");
  write++;
  pthread_mutex_unlock(&mutex);
}

void finish_write(){
  pthread_mutex_lock(&mutex);
  write--;
  printf("escritor: parei de escrever e deixei %i na fila \n", q_write);
  pthread_cond_signal(&cond_write);
  pthread_cond_broadcast(&cond_read);
  pthread_mutex_unlock(&mutex);
}










