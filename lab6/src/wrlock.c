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
  pthread_mutex_lock(&mutex);
  while (write > 0 || q_write > 0){
    pthread_cond_wait(&cond_read, &mutex);}
  read++;
  pthread_mutex_unlock(&mutex);
}

void finish_read(){
  pthread_mutex_lock(&mutex);
  read--;
  if(read == 0){
    pthread_cond_signal(&cond_write);}
  pthread_mutex_unlock(&mutex);
}

void init_write(){
  pthread_mutex_lock(&mutex);
  q_write++;
  while(read > 0 || write > 0){
    pthread_cond_wait(&cond_write, &mutex);}
  q_write--;
  write++;
  pthread_mutex_unlock(&mutex);
}

void finish_write(){
  pthread_mutex_lock(&mutex);
  write--;
  pthread_cond_signal(&cond_write);
  pthread_cond_broadcast(&cond_read);
  pthread_mutex_unlock(&mutex);
}










