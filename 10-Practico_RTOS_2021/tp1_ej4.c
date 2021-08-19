//TEMPLATE RTOS

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "string.h"
#include "stdlib.h"
#include "semphr.h"
#include "chip.h"


#define PRIO_TAREA1 1
#define PRIO_TAREA2 2
#define TAM_PILA 150
#define mainDELAY_LOOP_COUNT        ( 0xffffff )

const TickType_t xDelay300ms = pdMS_TO_TICKS( 300UL ); //macro para convertir ms en ticks
const TickType_t xDelay500ms = pdMS_TO_TICKS( 500UL ); //macro para convertir ms en ticks
const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL ); //macro para convertir ms en ticks

TaskHandle_t xTask2Handle2;


void vApplicationIdleHook( void )
{
	//Se va a ejecutar cuando ninguna tarea este lista. No hay que hacerla con loop. No se puede bloquear (usar esperas activas si fuese necesario)
	TickType_t xLastWakeTime;
	xLastWakeTime=xTaskGetTickCount();
	while((xTaskGetTickCount()-xLastWakeTime)<xDelay300ms)
	{
	//acá no poner nada. Está esperando que se cumpla la condición para salir
	}
	printf( "TIdle cambiando estado led azul\r\n" );
	Board_LED_Toggle(2); /* Blue (RGB) */
}

static void vTarea1(void *pvParameters)
{
	char *sTexto;
	
	UBaseType_t uxPriority; //variable de prioridad
	uxPriority = uxTaskPriorityGet( NULL ); //retorna la propia prioridad
	
	TickType_t xLastWakeTime;
	
	/* The string to print out is passed in via the parameter.  Cast this to a character pointer. */
	sTexto = ( char * ) pvParameters;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
		printf( "%s Prioridad: %d \r\n", sTexto, uxPriority);
		
		xLastWakeTime = xTaskGetTickCount(); // se inicializa la variable con la actual cantidad de ticks. Luego es manejada por la API de vTaskDelayUntil()
	
		vTaskDelayUntil( &xLastWakeTime, xDelay500ms ); //Asegura cierta cantidad de tics entre una ejecucion y otra
	}
}


int main(void)
{
	//Se inicializa HW
	/* Se crean las tareas */
	const char *pcTextoTarea1 = "T1 is running\r\n";
	const char *pcTextoTarea2 = "T2 is running\r\n";
	
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, PRIO_TAREA1, NULL );
	xTaskCreate(vTarea1, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, PRIO_TAREA2, NULL );
	vTaskStartScheduler(); /* y por último se arranca el planificador . */
	//Nunca llegara a ese lazo  .... espero
	for( ;; );
	return 0;
	
}

