/*
 * Ejercicio 4  TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){
	pid_t pid;
	int i;

	pid = fork();
	switch(pid)
	{
		case -1:
		{
			printf("ERROR al crear proceso");
			exit(-1);
			break;
		}
		case 0:
		{
			printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
			printf("Soy el hijo\n");
			break;
		}
		default:
		{
			printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
			printf("Soy el padre\n");
			break;
		}
	}
	sleep(30); 
	exit(0);
}
