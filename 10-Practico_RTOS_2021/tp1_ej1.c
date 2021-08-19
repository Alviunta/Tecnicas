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

static void vTarea1(void *pvParameters)
{
	
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
		
		printf("T1 El valor de GPIO_0 es %d \r\n", Board_GPIO_GetStatus(BOARD_GPIO_0));
		
	}
}

static void vTarea2(void *pvParameters)
{
	const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL );
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); // se inicializa la variable con la actual cantidad de ticks. Luego es manejada por la API de vTaskDelayUntil()
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
		
		Board_LED_Toggle(1); //Cambia el estado del led 
		Board_LED_Toggle(5); //Cambia el estado del led 
		
		printf("T2 CAMBIE ESTADO LED VERDE, los tics del reloj son: %d\r\n",xTaskGetTickCount());
		vTaskDelayUntil( &xLastWakeTime, xDelay1000ms ); //Asegura cierta cantidad de tics entre una ejecucion y otra
		
	}
}


int main(void)
{
	//Se inicializa HW
	/* Se crean las tareas */
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, NULL );
	
	vTaskStartScheduler(); /* y por último se arranca el planificador . */
	//Nunca llegara a ese lazo  .... espero
	for( ;; );
	return 0;
	
}

