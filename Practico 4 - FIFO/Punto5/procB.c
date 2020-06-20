#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_PATH "/tmp/MI_FIFO"

main(){

	int fifo_d;
	char buff[80];
	int leido;
	
	write (0, "\nPROCESO B", sizeof("\nPROCESO B")); 
	
	//Abre fifo como lectura
	fifo_d = open(FIFO_PATH, O_RDONLY, 0); 
	if(fifo_d == -1){
		write (0, "\nError al abrir FIFO ", sizeof("\nError al abrir FIFO "));
		return -1;
	}else {
		write (0, "\nFIFO abierto correctamente", sizeof("\nFIFO abierto correctamente"));
	}

	// Se lee FIFO
	leido = read(fifo_d, buff, sizeof(buff));	
	if(leido == -1){
		write (0, "\nError al leer en FIFO", sizeof("\nError al leer en FIFO"));
	}else {
		write (0, "\nLeido del FIFO: ", sizeof("\nLeido del FIFO: "));
		write (0, buff, leido-1); 
	}

	//CIERRO FIFO Y TERMINO PROCESO
	close(fifo_d);
	//Eliminación FIFO
	//if (unlink(FIFO_PATH) < 0) {
 	//	printf("\nNo se puede borrar FIFO.\n");  }
	
	return 0;
}
