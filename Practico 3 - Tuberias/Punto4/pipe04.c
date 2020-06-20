/*
 * Ejercicio 4 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){
	
	write (0, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
	exit(-1);
}

int main (){

	int ipc[2], proc;
	int leido, success;
	char buff[BUFF_SIZE] = {0};

	signal(SIGPIPE, pipe_sign_handler); //establece el manejador para la señal sigpipe
	
	if (pipe(ipc) == -1)	//abre la tuberia
		exit(-1);
	
	close(ipc[0]); //Cierra el extremo de lectura 		OJO -> esta MAL
	
	switch (fork()){ //Crea un proceso hijo
		
		case 0: //HIJO
			close(ipc[1]);	//cierra extremo de escritura en el hijo
			printf("Leyendo tuberia... \n");
			leido = read(ipc[0], buff, sizeof(buff)); //lee de la tuberia
			if(leido < 1){
				write (0, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
			}else {
				write (0, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
				write (0, buff, leido-1);
				printf(", por el proceso hijo, pid %d \n", getpid());
			}
			exit(0);
			
		default://PADRE
			strncpy(buff, DATA, sizeof(DATA));
			write(ipc[1], buff, sizeof(DATA)); //Escribe el buffer en la tuberia
		
			wait(NULL);		
			
			exit(0);		
	}
}
