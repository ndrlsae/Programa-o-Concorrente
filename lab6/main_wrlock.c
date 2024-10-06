#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "list_int.h"
#include "timer.h"
#include "wrlock.h"

struct list_node_s* head_p = NULL;

int nthreads;

#define QTDE_OPS 20
#define QTDE_INI 10
#define MAX_VALUE 100

//int read = 0;
//int write = 0;
//int q_write = 0;



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









