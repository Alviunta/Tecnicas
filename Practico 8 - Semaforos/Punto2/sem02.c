/* Ejercicio 2 del TP de semaforos sin nombre */

#include <stdio.h>
#include <pthread.h>    
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>   

//------- variables globales

int t, total, contador, s;
sem_t sem;

//------------------------------------------------------------

void *HILO(void *nro){
int local, j, numero;
	
	numero = *(int*)nro;
	s = sem_wait(&sem);
	if (s != 0) {
		printf("ERROR sem_wait()\n");
		exit(-1);     }

	for(j=0; j < contador; j++){
		local = total;
		local = local + 10;
		total = local;	   }
	
	s=sem_post(&sem);
	if (s != 0) {
		printf("ERROR sem_post()\n");
		exit(-1);     }
	printf("Hilo %d, total = %d\n", numero,total);
	
	pthread_exit(NULL);
}

//------------------------------------------------------------

int main()	{
int rc, n_hilos,s;
int arre[10];
   
	total = 0;
	contador = 100000;
	n_hilos = 10;
	
	pthread_t hilo[n_hilos];
	//------ inicializa el sem sin nombre 
	s=sem_init(&sem, 0, 1);
	if (s != 0) {
		printf("ERROR sem_init()\n");
		exit(-1);     }

	for(t=0; t < n_hilos; t++){
	
		arre[t] = t;
		
		rc = pthread_create(&hilo[t], NULL, HILO , (void *)&arre[t]  );
		if (rc){
			printf("ERROR; pthread_create() = %d\n", rc);
			exit(-1);      }
	}

//-------------------------------------

	for(t=0; t < n_hilos; t++){
		pthread_join(hilo[t],NULL);   
	}
	
	printf("total = %d\n",total);
	
	pthread_exit(NULL);
}

