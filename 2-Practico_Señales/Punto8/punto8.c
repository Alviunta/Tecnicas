#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int status;
int w;
char aux[50];

void manejador(int a){
	write(0,"\nTerminó hijo\n",sizeof("\n Terminó hijo\n"));
	w=wait(&status);
	
	sprintf(aux,"\nWait arrojo: %d\n", w);
	write(0,aux,sizeof(aux));
	
	sprintf(aux,"\nStatus arrojo: %d\n", status);
	write(0,aux,sizeof(aux));
}

int main ()
{
  
pid_t pid1;
signal(SIGCHLD, manejador);
pid1=fork();
if(pid1==0) //PADRE
{
	printf("\nSoy el proceso hijo, PID= %d\n",getpid());
	sleep(2);
	exit(0);
}
//PADRE
printf("\nSoy el proceso padre, PID= %d\n",getppid());
sleep(10);
signal(SIGCHLD, manejador);
exit(0);
return 0;
}
