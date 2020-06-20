/*
 * Ejercicio 3 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define FRASE_A "INFORMACION IMPORTANTE A"
#define FRASE_B "INFORMACION IMPORTANTE B"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){
	
	write (0, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
}

int main (){

	int ipc[2], proc;
	int leido, success;
	char buff[BUFF_SIZE] = {0};

	signal(SIGPIPE, pipe_sign_handler); //Establece el manejador de la señal SIGPIPE
	
	pipe(ipc);	//Abre la tuberia

	switch (fork()){ //Crea proceso hijo
		
		case 0:	//HIJO
		close(ipc[0]);		//Cierra extremo de lectura en hijo
		strncpy(buff, FRASE_A, sizeof(FRASE_A)); 
		write(ipc[1], buff, sizeof(FRASE_A));	//Escribe en pipe el buff
		exit(0);
		break;
		
		default:
		switch (fork()){ //Crea proceso hijo2
				
			case 0: //HIJO2
				close(ipc[0]);		//Cierra extremo de lectura
				strncpy(buff, FRASE_B, sizeof(FRASE_B)); 
				write(ipc[1], buff,    sizeof(FRASE_B));	//Escribe en pipe el buff
				exit(0);		
			break;
			default:
				close(ipc[1]);		//Cierra extremo de escritura
				int i;
				for(i=0; i<2; i++){
					leido = read(ipc[0], buff, sizeof(buff)); //Lee de la pipe
					if(leido < 1){
						write (0, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
					}else {
						write (0, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
						write (0, buff, leido-1);
						printf(", por el proceso padre, pid %d \n", getpid());
					}
				}
				
				close(ipc[0]);	//cierra extremo de lectura
				wait(NULL);	
				wait(NULL);					
				exit(0);
			break;
		}
	}	
}
