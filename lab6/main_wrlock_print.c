#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "list_int.h"
#include "timer.h"
#include "wrlock.h"

struct list_node_s* head_p = NULL;

int nthreads;

#define QTDE_OPS 100
#define QTDE_INI 10000
#define MAX_VALUE 1000



void func_demorada(){
  int h = 0;
  for (int i = 0; i<1000; i++){
    h += 2*i+i*22;}}

void * tarefa(void * arg){
  long int id = (long int) arg;
  int op;
  int in, out, reads;
  in = out = reads = 0;

  for(long int i=id; i < QTDE_OPS; i+=nthreads){
    op = rand() % 100;
    if(op<90){
      printf("thread %li: quero ler\n", id);
      init_read();
      Member(i%MAX_VALUE, head_p);
      func_demorada();
      finish_read();
      printf("thread %li: terminei de ler\n", id);
      reads++;}
    else if (90<=op && op<95){
      printf("thread %li: quero inserir\n", id);
      init_write();
      Insert(i%MAX_VALUE, &head_p);
      func_demorada();
      finish_write();
      printf("thread %li: inseri\n", id);
      in++;}
    else if(op>=95){
      printf("thread %li: quero deletar\n", id);
      init_write();
      Delete(i%MAX_VALUE, &head_p);
      func_demorada();
      finish_write();
      printf("thread %li: deletei\n", id);
      out++;}
  }

  printf("Thread %ld: insert = %d delete = %d read = %d \n", id, in, out, reads);
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

  //Printando os Parâmetros
  printf("QTDE_OPS = %i \nQTDE_INI = %i \nMAX_VALUE = %i \n \n", QTDE_OPS, QTDE_INI, MAX_VALUE);
  printf("0.9 LÊ \n0.05 INSERE \n0.05 DELETA\n \n");

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









