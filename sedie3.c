#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define TRUE 1
#define FALSE 0


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
sem_t semaforo, judge_semaphore,reset_semaphore;
int num_concorrenti;

typedef struct chair{
	int istaken;
	struct chair* next;
}CHAIR;




typedef struct competitors{
	pthread_t* thread;
	int id;
	int isseated;
	struct competitors* next;
}COMPETITORS;



void comp_thread_start();

CHAIR* head;						//TESTA LISTA SEDIE
COMPETITORS* c_head;	//TESTA LISTA COMPETITOR




//-------------------------------------------------------------------------

int search_for_chair(COMPETITORS* a){
CHAIR* tmp=NULL;
tmp=head;
if(a->isseated==FALSE){
	while(tmp!=NULL){
		if(tmp->istaken==FALSE){
			tmp->istaken=TRUE;
			a->isseated=TRUE;
			return TRUE;
			}else
			tmp=tmp->next;
						}
						return FALSE;
					}else{
					sem_post(&semaforo);
					return -1;
					}
			
}
																//OK


void reset_chairlist(){
	CHAIR* tmp;
	tmp=head->next;
	free(head);
	head=tmp;								
	while(tmp!=NULL){
	tmp->istaken=FALSE;
	tmp=tmp->next;
		}
}






void* comp_thread(void* arg){
COMPETITORS* temp;
temp=(COMPETITORS*)arg;
while(num_concorrenti!=2){
		sem_wait(&semaforo);
		int search;
		pthread_mutex_lock(&mutex);
		search=search_for_chair(temp);
		if(search==TRUE)
			printf("Il competitor %i si è seduto...\n",(int)(temp->id));
		else{
		if(search==FALSE){
			printf("Il competitor %i ha perso...\n\n",(int)(temp->id)) ;
			sem_post(&judge_semaphore);
			sem_post(&reset_semaphore);
			pthread_mutex_unlock(&mutex);
			//return (void*)NULL;
			pthread_exit(NULL);
			}
			
			
		}
		pthread_mutex_unlock(&mutex);
	}
	if(num_concorrenti==2)
		printf("Vince il competitor %i!!!\n",(int)(temp->id));
		
}



void reset_complist(){
COMPETITORS* tmp;
	tmp=c_head;
	while(tmp!=NULL){
	tmp->isseated=FALSE;
	tmp=tmp->next;
		}
}


//--------------------------------------------------------------
void* giudice(void* arg){
	comp_thread_start();
	while(num_concorrenti!=1){
		int i;
		sem_wait(&judge_semaphore);
									
		for(i=0;i<num_concorrenti; i++, sem_post(&semaforo));
		
		sem_wait(&reset_semaphore);
		pthread_mutex_lock(&mutex);
			reset_chairlist();
			reset_complist();
			num_concorrenti--;
			pthread_mutex_unlock(&mutex);
	}
	//comp_thread_join();
	pthread_exit(NULL);
}






//-------------------------------------------------------------------------------------

void comp_thread_start(){
	int i=1;
		pthread_mutex_lock(&mutex);

			if(c_head!=NULL){
				pthread_t* tmp=NULL;
				COMPETITORS* c_tmp=NULL;
				c_tmp=c_head;
							
				do{
				int ret;
				tmp=c_tmp->thread;
				ret=pthread_create(tmp,NULL,&comp_thread,c_tmp);
				c_tmp=c_tmp->next;
				i++;
				}while(c_tmp!=NULL);
		pthread_mutex_unlock(&mutex);
	}
}

//--------------------------------------------------------------



void comp_thread_join(){


			if(c_head!=NULL){
				pthread_t* tmp=NULL;
				COMPETITORS * c_tmp=NULL;
				c_tmp=c_head;
							
				do{
				int ret;
				pthread_mutex_lock(&mutex);
				tmp=c_tmp->thread;
				pthread_t t=*tmp;
				pthread_mutex_unlock(&mutex);
				pthread_join(t,NULL);
				pthread_mutex_lock(&mutex);
				c_tmp=c_tmp->next;
				pthread_mutex_unlock(&mutex);
				}while(c_tmp!=NULL);
	}

}



//---------------------------------------------------------------------------------------------------------------------------------------------

void lists_create(int dim){
	int i;

	CHAIR* new=NULL;
	COMPETITORS* tmp=NULL;																													
	pthread_t *thread=NULL;
	for(i=dim-1;i>0;i--){
		new=(CHAIR*)malloc(sizeof(CHAIR));
		new->next=head;																								//OK
		head=new;
		head->istaken=FALSE;
	}
	for(i=dim;i>0;i--){
		tmp=(COMPETITORS*)malloc(sizeof(COMPETITORS));
		thread=(pthread_t*)malloc(sizeof(pthread_t*));
		if(tmp==NULL || thread==NULL)
		{
			printf("tmp: %p\nthread: %p\n",tmp,thread);
			exit(-1);
			}
		tmp->next=c_head;
		c_head=tmp;
		
		c_head->isseated=FALSE;
		c_head->id=i;
		c_head->thread=thread;
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------


void init(){
	head=NULL;
	c_head=NULL;
	sem_init(&semaforo,0,0);
	sem_init(&judge_semaphore,0,1);
		sem_init(&reset_semaphore,0,0);
}




int main(){
int dim;

printf("Inserisci il numero dei competitor:\n");
scanf("%i",&dim);
	if(dim>0)
		num_concorrenti=dim;
	else{	
		printf("numero errato");
		return 0;
	}

init();
lists_create(dim);
pthread_t com;

pthread_t judge;
pthread_create(&judge,NULL,&giudice,(void*)NULL); //creo il thread giudice
pthread_join(judge,NULL);


}
