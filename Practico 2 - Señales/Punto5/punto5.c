#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void manejador(int a){
   write(0,"\n Me rehuso a terminar\n",sizeof("\n Me rehuso a terminar\n"));
}

int main ()
{

   signal(SIGKILL, manejador);
   
   printf("Proceso PID = %d\n", getpid());   
   
   while(1);
   
   exit(0);
}
