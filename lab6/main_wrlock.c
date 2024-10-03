#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "list_int.h"
#include "timer.h"


struct list_node_s* head_p = NULL;

int nthreads;

int read = 0;
int write = 0;
int q_write = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_read, cond_write;

void init_read(){
  pthread_mutex_lock(&mutex);
  while (write > 0 || q_write > 0){
    printf("leitor %i: %i escritores estão escrevendo/esperando, vou esperar", read, write);
    pthread_cond_wait(&cond_read, &mutex);}
  read++;
  pthread_mutex_unlock(&mutex);
}

void finish_read(){
  pthread_mutex_lock(&mutex);
  read--;
  if(read == 0){
    printf("leitor: terminei de ler");
    pthread_cond_signal(&cond_write);}
  pthread_mutex_unlock(&mutex);
}

void init_write(){
  pthread_mutex_lock(&mutex);
  while(read > 0 || write > 0){
    printf("escritor: %i estão lendo e %i estão escrevendo", read, write);
    q_write++;
    pthread_cond_wait(&cond_write, &mutex);}
  write++;
  pthread_mutex_unlock(&mutex);
}

void finish_write(){
  pthread_mutex_lock(&mutex);
  write--;
  pthread_cond_signal(&cond_write);
  q_write--;
  pthread_cond_broadcast(&cond_read);
  pthread_mutex_unlock(&mutex);
}





