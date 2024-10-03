#include <stdio.h>
#include <stdlib.h>

#include <pthread>

int var_global = 0;
pthread_cond_t condvar;
pthread_mutex = cond

void * thread_1(void* arg){
  printf("Seja bem vinda!");

  pthread_exit(NULL);
  return NULL;}

void * thread_2(void* arg){
  printf("Bom dia!");
  pthread_exit(NULL);
  return NULL;}

void * thread_3(void* arg){
  printf("Quer um copo d'água?!");
  pthread_exit(NULL);
  return NULL;}

void * thread_4(void* arg){
  printf("Passe bem!");
  pthread_exit(NULL);
  return NULL;}

void * thread_5(void* arg){
  printf("Até mais tarde!");
  pthread_exit(NULL);
  return NULL;}


int main(int argc, char *argv[]){

  pthread_t *tid_sistema;
  int nthreads = 5;





  return 0;
}
