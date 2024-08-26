#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long int n;
float *vet1, *vet2;
int nthreads;


void *multiplica(void *tid) {
  long int id = (long int) tid;

  float soma_local, *ret;

  //multiplicando e fazendo soma_local
  for(long int i = id; i < n; i+=nthreads){
    soma_local += vet1[i]*vet2[i];
    //printf("somei n = %ld \n", i);
  }

  ret = malloc(sizeof(float));
  if(ret!=NULL){ *ret = soma_local;}
  else {printf("Erro de alocação\n");}

  pthread_exit((void*) ret);
}

double var_rel(double vs, double vc){
  double e = abs((vs - vc)/vs);
  printf("e = %f \n", e);
  return e;
}

int erro(double a, double b, double epsilon){
  if (abs(a-b) > epsilon){
    printf("Os números não são iguais\n");
    return 1;
  }
  return abs(a-b) < epsilon;
}

int main(int argc, char *argv[]){
  FILE *arq;
  size_t ret;

  double soma_ori; //esse pra pegar do arquivo original
  float soma_threads; //resultado
  float *ret_threads; //pegar retorno das threads

  double eps = 1e-9;

  pthread_t *tid_sistema;

  if(argc < 3){printf("erro aqui\n"); return 1;}

  arq = fopen(argv[1], "rb");
  if(arq==NULL){printf("Erro abrindo arquivo"); exit(-1);}

  ret = fread(&n, sizeof(long int), 1, arq);
  if(!ret) {printf("Erro de leitura da primeira linha\n"); return 3;}
  printf("n = %ld\n", n);
  
  vet1 = malloc(sizeof(float)*n);
  if(vet1==NULL){printf("Erro no malloc do vet1\n"); exit(-1);}
  ret = fread(vet1, sizeof(float), n, arq);
  if(ret < n){printf("erro lendo vet1\n"); return 4;}

  vet2 = malloc(sizeof(float)*n);
  if(vet2==NULL){printf("Erro no malloc do vet2\n"); exit(-1);}
  ret = fread(vet2, sizeof(float), n, arq);
  if(ret < n){printf("erro lendo vet2\n"); return 4;}

  nthreads = atoi(argv[2]);

  if(nthreads>n){nthreads = n;};

  tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid_sistema==NULL){printf("erro malloc do tid_sistema\n"); exit(-1);}

  //criando threads
  for(long int i=0; i<nthreads; i++){
    if (pthread_create(&tid_sistema[i], NULL, multiplica, (void*) i)){
    printf("Erro no pthread_create"); exit(-1);
    }
  }

  //espera todos terminarem
  soma_threads = 0;
  for(int i=0; i <nthreads; i++){
    if(pthread_join(tid_sistema[i], (void*) &ret_threads)){
      printf("erro no join\n"); exit(-1);
    }
    soma_threads += *ret_threads;
    free(ret_threads);
  }

  ret = fread(&soma_ori, sizeof(double), 1, arq);
  //imprime resultados
  printf("\n");
  printf("soma original = %.26f\n", soma_ori);
  printf("soma concorrente = %.26f\n", soma_threads);
 
  free(vet1);
  free(vet2);
  free(tid_sistema);

  fclose(arq);
  double erro_rel = var_rel(soma_threads, soma_ori);
  printf("variação relativa: %.26f \n", erro_rel);

  return erro(soma_threads, soma_ori, eps);
}


  
