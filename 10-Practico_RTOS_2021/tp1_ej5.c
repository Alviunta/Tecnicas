//TEMPLATE RTOS

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "string.h"
#include "stdlib.h"
#include "semphr.h"


#define PRIO_TAREA1 2
#define PRIO_TAREA2 2
#define PRIO_TAREA3 1
#define TAM_PILA 150
#define mainDELAY_LOOP_COUNT        ( 0xffffff )
# define TAM_COLA 20 /* 20 mensajes */
# define TAM_MSG 4 

QueueHandle_t cola; // Hay que declararla Global, se usa en distintas tareas

void vApplicationIdleHook( void )
{
	//Se va a ejecutar cuando ninguna tarea este lista. No hay que hacerla con loop. No se puede bloquear (usar esperas activas si fuese necesario)
}

static void vTarea1(void *pvParameters)
{
	BaseType_t xStatus; //Variable de estado de cola
	
	char mensaje[5];
	strcpy(mensaje,"0500");
	
	//Enviar
	
	for( ;; ) {
		xStatus = xQueueSend (cola, (void *) mensaje, portMAX_DELAY); //Escribe en la cola 
		if (xStatus==pdFAIL) printf("Error en la escritura (Tarea1)\r\n");
		else printf("T1 Escribio en la cola \r\n");
		/* As per most tasks, this task is implemented in an infinite loop. */
		//PODRIA IR UN TASK DELAY
	}
}

static void vTarea2(void *pvParameters)
{
	BaseType_t xStatus; //Variable de estado de cola
	
	char mensaje[5];
	strcpy(mensaje,"0100");
	
	//Enviar
	
	for( ;; ) {
		xStatus = xQueueSend (cola, (void *) mensaje, portMAX_DELAY); //Escribe en la cola 
		if (xStatus==pdFAIL) printf("Error en la escritura (Tarea1)\r\n");
		else printf("T1 Escribio en la cola \r\n");
		/* As per most tasks, this task is implemented in an infinite loop. */

		
	}
}

static void vTarea3(void *pvParameters)
{
	char cad [5];
	int a;
	TickType_t xLastWakeTime, xDelaymsON, xDelaymsOFF;
	xLastWakeTime = xTaskGetTickCount(); // se inicializa la variable con la actual cantidad de ticks. Luego es manejada por la API de vTaskDelayUntil()
	xDelaymsOFF= pdMS_TO_TICKS( 300UL ); //macro para convertir ms en ticks;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
	if (xQueueReceive (cola, (void *) cad,(portTickType) 0xFFFFFFFF )==pdTRUE) //Recibe datos de la cola
	{
		printf("T3 Lee cola: \r");
		a=atoi(cad); //Convierte a int lo recibido
		printf("%d. \r\n", a);
	}
	else printf("Error en la lectura.\r\n");
	
	Board_LED_Set(3, TRUE); //prende "LED 5" ( amarillo )
	xDelaymsON= pdMS_TO_TICKS( a ); //macro para convertir ms en ticks;
	printf("T3 Delay de %d ms\n",a);
	vTaskDelayUntil( &xLastWakeTime, xDelaymsON ); //Asegura cierta cantidad de tics entre una ejecucion y otra
	Board_LED_Set(3, FALSE); //prende "LED 5" ( amarillo )
	vTaskDelayUntil( &xLastWakeTime, xDelaymsOFF ); //Asegura cierta cantidad de tics entre una ejecucion y otra
	}
}

int main(void)
{
	//Se inicializa HW
	/* Se crean las tareas */
	cola = xQueueCreate (TAM_COLA, TAM_MSG); //Crea la cola (generalmente en el main)
	
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, NULL );
	xTaskCreate(vTarea3, (const char *)"Tarea3", TAM_PILA, NULL, PRIO_TAREA3, NULL );
	
	
	vTaskStartScheduler(); /* y por último se arranca el planificador . */
	//Nunca llegara a ese lazo  .... espero
	for( ;; );
	return 0;
	
}

