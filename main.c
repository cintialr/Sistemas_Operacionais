//gcc -pthread main.c -o main
//./main

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_PESSOAS 2 // x homens e x mulheres
#define N_CABINES 1 //qtd de cabines

sem_t sem_cabines;
sem_t cabine; //semaforo da cabine
sem_t usou_cabine; //semaforo que controla quem já utilizou a cabine
pthread_mutex_t lock_cabine = PTHREAD_MUTEX_INITIALIZER;

void * banheiro(void *index) {

  while(1) {
    //Espera uma pessoa entrar na fila
    sem_wait(&cabine);
    sleep(1); //Entrar na cabine 
    printf("--------USANDO AS CABINES--------\n"); 
    //Liberar a cabine
    sem_post(&usou_cabine);
  }
  pthread_exit(0);
}

void* mulher_banheiro(void* index) {
  while(1){
  int id = *(int*) index;
  sleep(id);
  if(sem_trywait(&sem_cabines) == 0){ //para entrar na fila
    printf("--------ENTRAR NA FILA--------\n"); 
    printf("Mulher %d entrou na fila do banheiro \n",id);
    //Região crítica
    //Usar a cabine
    pthread_mutex_lock(&lock_cabine);
      //Libera seu lugar na fila 
      sem_post(&sem_cabines); 
      //Entrar na cabine
      sem_post(&cabine); 
      printf("Mulher %d entrou na cabine\n",id);
      //Esperar usar a cabine
      sem_wait(&usou_cabine);
      pthread_mutex_unlock(&lock_cabine); //Liberar a cabine
      printf("Mulher %d saiu da cabine\n",id);  
  }
  pthread_exit(0);
  }
}
void* homem_banheiro(void* index) {
  while(1){
  int id = *(int*) index;
  sleep(id);
  if(sem_trywait(&sem_cabines) == 0){ //para entrar na fila
    printf("--------ENTRAR NA FILA--------\n"); 
    printf("Homem %d entrou na fila do banheiro \n",id);
    //Usar a cabine
    pthread_mutex_lock(&lock_cabine);
    //Libera seu lugar na fila 
    sem_post(&sem_cabines);
    //Entrar na fila
    sem_post(&cabine); 
    printf("Homem %d entrou na cabine\n",id);
    //Esperar usar a cabine
    sem_wait(&usou_cabine);
    pthread_mutex_unlock(&lock_cabine); //Liberar a cabine
    printf("Homem %d saiu da cabine\n",id);
    }
  pthread_exit(0);
  }
}

int main() {

  pthread_t thread_banheiro;
  pthread_t thread_mulher[N_PESSOAS];
  pthread_t thread_homem[N_PESSOAS];
 
  int i, id[N_PESSOAS];

  //inicializando os semaforos
  //sem_init(sem_t *, int, unsigned int)
  sem_init(&sem_cabines, 0, N_PESSOAS);
  sem_init(&cabine, 0, 0);
  sem_init(&usou_cabine, 0, 0);

  pthread_create(&thread_banheiro, NULL, banheiro, NULL);
   
  for (i = 0; i < N_PESSOAS; i++) {
    id[i] = i;
    pthread_create(&thread_mulher[i], NULL, mulher_banheiro, (void*) &id[i]);
  }
    for (i = 0; i < N_PESSOAS; i++) {
    id[i] = i;
    pthread_create(&thread_homem[i], NULL, homem_banheiro, (void*) &id[i]);
  }

  for (i = 0; i < N_PESSOAS; i++) 
    pthread_join(thread_mulher[i], NULL);

  for (i = 0; i < N_PESSOAS; i++) 
    pthread_join(thread_homem[i], NULL);
    
  return 0;
}
