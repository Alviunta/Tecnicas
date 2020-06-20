#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MENSAJE "Mensaje para proceso B"
#define FIFO_PATH "/tmp/MI_FIFO"

main(){

	int err, fifo_d;

	unlink(FIFO_PATH);    //si la FIFO existe la borro
	
	//CREO LA FIFO
	err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
	if(err == -1) {
		write (0, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe")); 
	}else {
		write (0, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n")); 
	}

	//ABRE FIFO
	write (0, "\nPROCESO A", sizeof("\nPROCESO A")); 
	fifo_d = open(FIFO_PATH, O_WRONLY, 0);
	if(fifo_d == -1){
		write (0, "\nError al abrir FIFO ", sizeof("\nError al abrir FIFO "));
		return -1;
	}
	else {
		write (0, "\nFIFO abierto correctamente", sizeof("\nFIFO abierto correctamente"));
	}

	// ESCRIBE MENSAJE EN FIFO
	err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
	if(err == -1) {
		write (0, "\n Error al escribir en FIFO", sizeof("\nError al escribir en FIFO"));
	}
	else {
		write (0, "\nEscritos MENSAJE en FIFO", sizeof("\nEscritos MENSAJE en FIFO"));
	}

	//CIERRO FIFO Y TERMINO PROCESO
	close(fifo_d);
	//Eliminación FIFO
	//if (unlink(FIFO_PATH) < 0) {
 	//	printf("\nNo se puede borrar FIFO.\n");  }
	return 0;
}
