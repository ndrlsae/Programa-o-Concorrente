#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "list_int.h"
#include "timer.h"


struct list_node_s* head_p = NULL;

int nthreads;

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


void * tarefa(void * arg){
  long int id = (long int) arg;
  int op;
  int in, out, read;
  in = out = read = 0;

  for(long int i=id; i < QTDE_OPS; i+=nthreads){
    op = rand() % 100;
    if(op<50){
      init_read();
      Member(i%MAX_VALUE, head_p);
      finish_read();
      read++;}
    else if (50<=op && op<75){
      init_write();
      Insert(i%MAX_VALUE, &head_p);
      finish_write();
      in++;}
    else if(op>=75){
      init_write();
      Delete(i%MAX_VALUE, &head_p);
      finish_write();
      out++;}
  }

  printf("Thread %ld: insert = %d delete = %d read = %d \n", id, in, out, read);
  pthread_exit(NULL);
}


int main(int argc, char* argv[]){
  pthread_t *tid;

  if(argc<2){printf("Falta argumento\n");return 1;}

  nthreads = atoi(argv[1]);

  for(int i =0; i<QTDE_INI; i++){
    Insert(i%MAX_VALUE, &head_p);}

  tid = malloc(sizeof(pthread_t)*nthreads);
  if(tid==NULL){printf("erro malloc\n"); return 2;}


  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond_read, NULL); 
  pthread_cond_init(&cond_write, NULL);

  for(long int i=0; i<nthreads; i++){
    if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
      printf("erro criação de threads\n"); return 3;}}

  for(int i=0; i<nthreads; i++){
    if(pthread_join(*(tid+i), NULL)){
      printf("erro no join\n"); return 4;}}

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond_read);
  pthread_cond_destroy(&cond_write);

  free(tid);

  Free_list(&head_p);

  return 0;
}









