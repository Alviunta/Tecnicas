/* 
programa SOCKET SERVIDOR Stream (TCP) el servidor envia al socket
lo que recibe del socket y muestra en pantalla lo recibido en 
el socket: Cliente:--> datos rx socket
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int des_socket, sck_server, rx_socket, largo, cont, pid;
char buffer_rx[256], buff[200],buffaux[100];
struct sockaddr_in struct_direccion={};
int SockEscucha,SockConexion;

int main(int argc, const char *argv[])      {

   if (argc != 2){
       argv[1]="2000"; } 


 //****************** 1 *******************//
 //-- socket(): Crear el socket -----------//
   SockEscucha=socket(AF_INET, SOCK_STREAM, 0);
   
   if(( SockEscucha)<0) {
       printf ("ERROR en funcion socket()\n");
   exit(-1);     } 
   
   printf ("Paso 1: Servidor creo socket\n");

 //****************** 2 *******************//

//-- preparar el address:port -------------//
   struct_direccion.sin_family = AF_INET;
   struct_direccion.sin_addr.s_addr = htonl(INADDR_ANY);  // asigna una IP de la maquina
   struct_direccion.sin_port = htons(atoi (argv[1]));     // puerto

 //-- bind(): asociamos el socket a la direccion------//

   if (bind (SockEscucha, (struct sockaddr *)&struct_direccion,sizeof(struct sockaddr_in))<0) {
       printf ("ERROR en funcion bind()\n");
   exit(-1);     } 

   printf ("Paso 2: Asociar bind() \n");

 //****************** 3 *******************//
 //-- listen(): Permitir hasta 1 conexion pendiente --// (El 2do argumento de listen es i+1 conexiones pendientes posibles)

   if ((listen(SockEscucha, 0))<0) { //como cada proceso hijo va a manejar una conexion, 0+1
       printf ("ERROR en funcion listen()\n");
   exit(-1);     } 

   printf ("Paso 3: Permitir conexiones listen()\n");

  while(1) {

 //****************** 4 *******************//
 //-- accept(): se bloquea hasta que entre una conexion --//

   printf ("Paso 4: Bloqueo hasta que entre conexion accept()\n");
   cont=0;     
   SockConexion=accept(SockEscucha, NULL, 0) ;
	if(fork()==0) 
	{
	   if (SockConexion >=0) {  
	   //MENSAJE BIENVENIDA
	      if (cont==0) {
	           printf ("Desbloqueo de accept, entro conexion: %d\n",SockConexion);
	           printf ("Mi pid es %d y el pid de papa es %d\n", getpid(),getppid());

           	   strcpy(buff, "Bienvenido al servidor. Mi PID es:");
	           gcvt(getpid(), 100 ,buffaux);
	           strncat(buff, buffaux,sizeof (buffaux));
		   strcat(buff, "\n");
		   
	           send (SockConexion ,buff, sizeof (buff),0 ); 
	
	      cont=1;  }   
	     //ECO
	      while (( rx_socket = read(SockConexion, buffer_rx, sizeof (buffer_rx))) > 0) {  //lee del socket    
	                  write (SockConexion ,buffer_rx, rx_socket);         //escribe en socket
                  	  write (STDOUT_FILENO , "cliente:--> ", 12);         //escribe leyenda en pantalla
	                  write (STDOUT_FILENO , buffer_rx, rx_socket);      //escribe lo leido del socket
	          }
	    } 
	    else { 
	           printf ("Error en la conexion\n");  
	           }
	}
	/*else 
	{
		SockConexion=accept(SockEscucha, NULL, 0) ;
	}*/
  }

 //****************** 5 *******************//
 //------------cierrar la conexion --------// 

   close(SockConexion); 
 
  return 0;
}  
