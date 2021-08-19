//TEMPLATE RTOS

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "string.h"
#include "stdlib.h"
#include "semphr.h"


#define PRIO_TAREA1 1
#define PRIO_TAREA2 2
#define TAM_PILA 150
#define mainDELAY_LOOP_COUNT        ( 0xffffff )

void vApplicationIdleHook( void )
{
	//Se va a ejecutar cuando ninguna tarea este lista. No hay que hacerla con loop. No se puede bloquear (usar esperas activas si fuese necesario)
}


static void vTarea2(void *pvParameters)
{
	Board_LED_Toggle(4); //Cambia el estado del led 2
	printf("T2 - Cambie estado puerto serie. \r\n");
	vTaskDelete( NULL ); //Se borra a si misma
}

static void vTarea1(void *pvParameters)
{
	int a;
	TickType_t xLastWakeTime, xDelayms;
	xLastWakeTime = xTaskGetTickCount(); // se inicializa la variable con la actual cantidad de ticks. Luego es manejada por la API de vTaskDelayUntil()
	xDelayms= pdMS_TO_TICKS( 500UL ); //macro para convertir ms en ticks;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
		
		a= Board_GPIO_GetStatus(BOARD_GPIO_2);
		
		printf("T1 - El estado de la entrada GPIO2 es: %d\r\n", a);
		if (a==1)
		{
		xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, NULL );
		}
		
		vTaskDelayUntil( &xLastWakeTime, xDelayms ); //Asegura cierta cantidad de tics entre una ejecucion y otra
		
	}
}

int main(void)
{
	//Se inicializa HW
	/* Se crean las tareas */
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	
	
	vTaskStartScheduler(); /* y por último se arranca el planificador . */
	//Nunca llegara a ese lazo  .... espero
	for( ;; );
	return 0;
	
}

