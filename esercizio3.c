#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#define num_thread 100

pthread_t id[num_thread];

sem_t sem;
sem_t rx_wr;

int val=0;

void* scrittura (void* arg) {
	//sem_wait(&sem);	
	sem_wait(&rx_wr);
	printf("sto scrivendo: %i\n", ++val);
	sem_post(&rx_wr);
}

void* lettura (void* arg) {
	sem_wait(&rx_wr);
	sem_post(&rx_wr);
	//sem_wait(&sem);
	printf("sto leggendo: %i\n", val);
	}

int main() {
	sem_init(&rx_wr, 0, 1);
	sem_init(&sem, 0, 1);
	int i=0;
	int seed;
	scanf("Inserire seed: %i", &seed);
	srand(seed);
	int j=rand()%num_thread;
	int k=100-j;

	for (i=0; i<j; i++) 
		pthread_create(&id[i], NULL, &scrittura, NULL);

	for (i=j; i<num_thread; i++) 
		pthread_create(&id[i], NULL, &lettura, NULL);

	for (i=0; i<num_thread; i++)
		pthread_join(id[i], NULL);	

	return 0;
}
