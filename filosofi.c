#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define NUMFILOSOFI 5
#define DISP 1
#define NODISP 0
#define	TRUE 1
#define FALSE 0
#define lock pthread_mutex_unlock
#define unlock pthread_mutex_unlock
#define SEDUTO 1
#define ALZATO 0


sem_t semaforo;
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
int mangiatoia[NUMFILOSOFI];
int forchette[NUMFILOSOFI];

void* filosofo(void* arg){
	while(1){
	//printf("%i\n",arg);
		int id=(int)arg;
		
		sem_wait(&semaforo);
		//printf("%i\n",arg);
		
		if(mangiatoia[id]==ALZATO){
		if(findForch(id)){
			printf("Mangio %i\n",id);
		sleep(rand()%3);		//questo sleep serve per riuscire a leggere l'output
		printf("Mi alzo %i\n",id);
		posaforchette(id);

					}else
		sem_post(&semaforo);
		
			}else
		sem_post(&semaforo);
		}
}

void posaforchette(int id){
if(id!=0){
	lock(&mutex1);
			forchette[id]=DISP;
			forchette[id-1]=DISP;
			mangiatoia[id]=ALZATO;
//printf("posa: %i\n",id);
		sem_post(&semaforo);
		unlock(&mutex1);
		sleep(1);				//questi sleep servono ad evitare lo starvation
	}else{
	lock(&mutex1);
		forchette[id]=DISP;
    		forchette[NUMFILOSOFI-1]=DISP;
		mangiatoia[id]=ALZATO;
		sem_post(&semaforo);
//printf("posa: %i\n",id);
	  unlock(&mutex1);
		sleep(1);				//********************************************
		}
}



int findForch(int id){

if(id!=0){
	lock(&mutex1);

	if(forchette[id]==DISP && forchette[id-1]==DISP){
			forchette[id]=NODISP; 
			forchette[id-1]=NODISP;
			mangiatoia[id]=SEDUTO;	
		unlock(&mutex1);
		return TRUE;
}
	else{

		unlock(&mutex1);

		return FALSE;
	}
}else{
	lock(&mutex1);
	if(forchette[id]==DISP && forchette[NUMFILOSOFI-1]==DISP){
		forchette[id]=NODISP;
   		forchette[NUMFILOSOFI-1]=NODISP;
		mangiatoia[id]=SEDUTO;
		unlock(&mutex1);
		return TRUE;
	}
	else{
		unlock(&mutex1);
		return FALSE;
	}
}

}



int main(){
pthread_t filosofi[NUMFILOSOFI];
sem_init(&semaforo,0,2);
int z;
for(z=0;z<NUMFILOSOFI;z++){
mangiatoia[z]=ALZATO;
forchette[z]=DISP;
}

int i;
for(i=0;i<NUMFILOSOFI;i++){
pthread_create(&filosofi[NUMFILOSOFI],NULL,filosofo,i);
}

for(i=0;i<NUMFILOSOFI;i++){
pthread_join(filosofi[NUMFILOSOFI],NULL);
}


}
