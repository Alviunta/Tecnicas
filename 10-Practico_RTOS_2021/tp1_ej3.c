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


#define PRIO_TAREA1 2
#define PRIO_TAREA2 1
#define TAM_PILA 150
#define mainDELAY_LOOP_COUNT        ( 0xffffff )

TaskHandle_t xTask2Handle2;


void vApplicationIdleHook( void )
{
	//Se va a ejecutar cuando ninguna tarea este lista. No hay que hacerla con loop. No se puede bloquear (usar esperas activas si fuese necesario)
}

static void vTarea1(void *pvParameters)
{
	
	TickType_t xLastWakeTime;
	UBaseType_t uxPriority; //variable de prioridad
	uxPriority = uxTaskPriorityGet( NULL ); //retorna la prioridad
	const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL ); //macro para convertir ms en ticks
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
		//Esto va en el bucle de la tarea
		printf("T1 Las entradas GPIO tienen los valores:   %d%d%d%d \r\n", Board_GPIO_GetStatus(BOARD_GPIO_3),Board_GPIO_GetStatus(BOARD_GPIO_2),Board_GPIO_GetStatus(BOARD_GPIO_1) ,Board_GPIO_GetStatus(BOARD_GPIO_0) );
		
		
		xLastWakeTime=xTaskGetTickCount();
		while((xTaskGetTickCount()-xLastWakeTime)<xDelay1000ms)
		{
			//acá no poner nada. Está esperando que se cumpla la condición para salir
		}
		//Acá termino la espera
		
		printf( "T1 Aumentando prioridad T2\r\n" );
		vTaskPrioritySet( xTask2Handle2,  (uxPriority+1)  ); // Cambia la prioridad de la tarea.
	}
}

static void vTarea2(void *pvParameters)
{
	/* As per most tasks, this task is implemented in an infinite loop. */
	UBaseType_t uxPriority; //variable de prioridad
	uxPriority = uxTaskPriorityGet( NULL ); //retorna la prioridad
	for( ;; ) {
		printf ("T2 esta running. \n" );
		
		
		Board_LED_Toggle(5); /* Green */
		
		
		printf("\nT2 Cambie el estado del led verde \r\n");
		
		printf( "T2 Disminuyendo mi prioridad\r\n" );
		vTaskPrioritySet( NULL, ( uxPriority - 2 ) ); // Cambia la prioridad de la tarea
		
		
	}
}


int main(void)
{
	//Se inicializa HW
	/* Se crean las tareas */

	
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, &xTask2Handle2 );
	vTaskStartScheduler(); /* y por último se arranca el planificador . */
	//Nunca llegara a ese lazo  .... espero
	for( ;; );
	return 0;
	
}

