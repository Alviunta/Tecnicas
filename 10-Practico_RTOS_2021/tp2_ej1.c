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

const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL ); //macro para convertir ms en ticks

SemaphoreHandle_t sem; //Declaración (tiene que ser global para que lo vean todas las tareas que lo usan)

void vApplicationIdleHook( void )
{
	//Se va a ejecutar cuando ninguna tarea este lista. No hay que hacerla con loop. No se puede bloquear (usar esperas activas si fuese necesario)
}

static void vTarea1(void *pvParameters)
{
	TickType_t xLastWakeTime;
	
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
		
	//Esto va en el bucle de la tarea
	xLastWakeTime=xTaskGetTickCount();
	while((xTaskGetTickCount()-xLastWakeTime)<xDelay1000ms)
	{
	//acá no poner nada. Está esperando que se cumpla la condición para salir
	}
	printf("T1 termina busy waiting \r\n");
	xSemaphoreGive (sem);//Lo suelta
	}
}

static void vTarea2(void *pvParameters)
{
	const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL );
	
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
		xSemaphoreTake (sem , portMAX_DELAY); //Lo toma con un timeout determinado
		Board_LED_Toggle(2); //Cambia el estado del led 2
		printf("T2 Cambio estado led \r\n");		
	}
}


int main(void)
{
	//Se inicializa HW
	/* Se crean las tareas */
	sem = xSemaphoreCreateBinary ();  //Inicialización: se inicializa por defecto en 0, se hace antes de crear las tareas
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, NULL );
	
	vTaskStartScheduler(); /* y por último se arranca el planificador . */
	//Nunca llegara a ese lazo  .... espero
	for( ;; );
	return 0;
	
}

