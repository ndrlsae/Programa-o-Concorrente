/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Comunicação entre threads usando variável compartilhada e exclusao mutua com bloqueio */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

long int soma = 0; //variavel compartilhada entre as threads

int num = 0;
pthread_mutex_t mutex; //variavel de lock para exclusao mutua

//int estado = 0;
pthread_cond_t cond;

int nthreads;
int bloqueadas = 0;

//funcao barreira
void barreira(int Nthreads){
  //static int bloqueadas = 0;
  pthread_mutex_lock(&mutex);
  if (bloqueadas == (Nthreads-1)){
    pthread_cond_broadcast(&cond);
    bloqueadas = 0;}
  else {
    bloqueadas++;
    pthread_cond_wait(&cond, &mutex);}
  pthread_mutex_unlock(&mutex);
}



//funcao executada pelas threads
void *ExecutaTarefa (void *arg) {
  long int id = (long int) arg;
  printf("Thread : %ld esta executando...\n", id);

  for (int i=0; i<100000; i++) {
     //--entrada na SC
     pthread_mutex_lock(&mutex);
     //--SC (seção critica)
     if (!(soma%10) && num<20){
       //printf("thread %ld, soma = %li, i = %i \n", id, soma, i);
       //pthread_cond_wait(&cond, &mutex;}
       barreira(nthreads);}
     soma++;

     //incrementa a variavel compartilhada 
     //soma++
     //--saida da SC
     //pthread_mutex_unlock(&mutex);
  }
  printf("Thread : %ld terminou!\n", id);
  pthread_exit(NULL);
}

//funcao executada pela thread de log
void *extra (void *args) {
  printf("Extra : esta executando...\n");
  while(num < 20) {
    pthread_mutex_lock(&mutex);
     if (!(soma%10)){ //imprime se 'soma' for multiplo de 10
        printf("soma = %ld \n", soma);
        num++;}
        //pthread_cond_broadcast(&cond);}
     pthread_mutex_unlock(&mutex);}
  printf("Extra : terminou!\n");
  pthread_exit(NULL);
}

//fluxo principal
int main(int argc, char *argv[]) {
   pthread_t *tid; //identificadores das threads no sistema
   //int nthreads; //qtde de threads (passada linha de comando)

   //--le e avalia os parametros de entrada
   if(argc<2) {
      printf("Digite: %s <numero de threads>\n", argv[0]);
      return 1;
   }
   nthreads = atoi(argv[1]);

   //--aloca as estruturas
   tid = (pthread_t*) malloc(sizeof(pthread_t)*(nthreads+1));
   if(tid==NULL) {puts("ERRO--malloc"); return 2;}

   //--inicilaiza o mutex (lock de exclusao mutua)
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&cond, NULL);

   //--cria as threads
   for(long int t=0; t<nthreads; t++) {
     if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *)t)) {
       printf("--ERRO: pthread_create()\n"); exit(-1);
     }
   }

   //--cria thread de log
   if (pthread_create(&tid[nthreads], NULL, extra, NULL)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
   }

   //--espera todas as threads terminarem
   for (int t=0; t<nthreads+1; t++) {
     if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
     } 
   } 

   //--finaliza o mutex
   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond);
   
   printf("Valor de 'soma' = %ld\n", soma);

   return 0;
}
