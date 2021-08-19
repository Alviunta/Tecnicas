#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int pid;
char aux[50];

void manejador_hdl(int a){
	pid = wait(NULL);
	sprintf(aux,"\n Terminó hijo: %d\n", pid);
	write(0,aux,sizeof(aux));
}

int main ()
{
	pid_t pid1, pid2, pid3;
  
	signal(SIGCHLD, manejador_hdl);  //Ctrl + z
   
	pid1=fork();
	if(pid1==0) //HIJO 1
	{
		printf("Proceso hijo 1, PID = %d\n", getpid());   
		while(1);
	}
	
	pid2=fork();
	if(pid2==0) //HIJO 2
	{
		printf("Proceso hijo 2, PID = %d\n", getpid());
		while(1);
	}
	
	pid3=fork();
	if(pid3==0)
	{
		printf("Proceso hijo 3, PID = %d\n", getpid());
		while(1);
	}
	//Espera del padre

	sleep(2);
	kill(pid1, SIGKILL);
	sleep(2);
	kill(pid2, SIGKILL);
	sleep(2);
	kill(pid3, SIGKILL);
	sleep(4);
	exit(0);
}
