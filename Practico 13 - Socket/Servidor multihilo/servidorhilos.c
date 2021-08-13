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
#include <pthread.h>
#include <string.h>

int t=0;
void *hilos(void *nro)
{
     int SocketAct=*(int*)nro;		//HACE DE SockConexion
     char buffer_rx[256],buff[200],buffaux[100];
     int rx_socket;
     
     printf ("Desbloqueo de accept, entro conexion: %d\n",SocketAct);
     strcpy(buff, "Bienvenido al servidor. soy el hilo:");
     gcvt(t, 100 ,buffaux);
     strncat(buff, buffaux,sizeof (buffaux));
     strcat(buff, "\n");	   
     send (SocketAct ,buff, sizeof (buff),0 );   

     while ( (rx_socket = read(SocketAct, buffer_rx, sizeof (buffer_rx))) > 0) 
     {  //lee del socket
     
     	write (SocketAct,buffer_rx, rx_socket);         //escribe en socket
     	write (STDOUT_FILENO , "cliente:--> ", 12);         //escribe leyenda en pantalla
        write (STDOUT_FILENO , buffer_rx, rx_socket);      //escribe lo leido del socket
     }
     printf("Conexion %d terminada\n", SocketAct);     
     close(SocketAct); 

     pthread_exit(NULL);
}

int main(int argc, const char *argv[])      {

   if (argc != 2){
       argv[1]="2000"; } 

pthread_t hilo[5];
struct sockaddr_in struct_direccion={};
int SockEscucha,SockConexion[5];

int rc;
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
 //-- listen(): Permitir hasta 5 conexion pendiente --//

   if ((listen(SockEscucha, 5))<0) {
       printf ("ERROR en funcion listen()\n");
   exit(-1);     } 

   printf ("Paso 3: Permitir conexiones listen()\n");
 //****************** 4 *******************//
 //-- accept(): se bloquea hasta que entre una conexion --//
 
   printf ("Paso 4: Bloqueo hasta que entre conexion accept()\n");
  while(1) {
   SockConexion[t]=accept(SockEscucha, NULL, 0) ;	
   if (SockConexion[t] >=0) {  
	
	rc=pthread_create(&hilo[t],NULL,hilos,(void*)(&SockConexion[t]));
	if(rc!=0)
 	{
	  printf("Error al crear hilo\n");
	  exit(-1);
	}
	printf("Atendido por el hilo: %d\n",t); //t es el numero de hilo ¿DEBERIA SER HASTA 5??????
      t++;
    }
    else { 
           printf ("Error en la conexion\n");  
           }
   
  }

 //****************** 5 *******************//
 //------------cierrar la conexion --------// 

   close(SockEscucha); 
 
  return 0;
}  
