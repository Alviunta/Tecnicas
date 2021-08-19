//TEMPLATE RTOS CON ISR
//Usa un semaforo (sem) para sincronizar entre tareas y ISR

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
# define TAM_COLA 20 /* 20 mensajes */
# define TAM_MSG 4 

const TickType_t xDelay300ms = pdMS_TO_TICKS( 300UL ); 	//macro para convertir ms en ticks
const TickType_t xDelay500ms = pdMS_TO_TICKS( 500UL ); 	//macro para convertir ms en ticks
const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL ); 	//macro para convertir ms en ticks
const TickType_t xDelay1500ms = pdMS_TO_TICKS( 1500UL ); 	//macro para convertir ms en ticks



SemaphoreHandle_t sem; //Recurso compartido con la ISR
	
QueueHandle_t cola; // Hay que declararla Global, se usa en distintas tareas

static void initHardware(void) //Inicializa el HW del microcontrolador
{
	SystemCoreClockUpdate();
	Board_Init();
}


static void InitTimer(void) //Seteamos cada cuantos microsegundos queremos una interrupcion
{
	Chip_RIT_Init(LPC_RITIMER);
	Chip_RIT_SetTimerInterval(LPC_RITIMER,3000); //Tiempo en ms del timer
}

void RIT_IRQHandler(void) //Cada vez que entra una interrupción ejecuta este código
{
	
	
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;	
	
	///* Despierta las tareas */
	xSemaphoreGiveFromISR( sem, &xHigherPriorityTaskWoken ); //Acá iria lo que deberias liberar con la ISR (en este caso sem)
	
	if( xHigherPriorityTaskWoken == pdTRUE ){
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
		/* Si el semÃ¡foro ha despertado una tarea , se fuerza un cambio de contexto */
	}
	/* Borra el flag de interrupciÃ³n */
	Chip_RIT_ClearInt(LPC_RITIMER);
}

void vApplicationIdleHook( void )
{
	//Se va a ejecutar cuando ninguna tarea este lista. No hay que hacerla con loop. No se puede bloquear (usar esperas activas si fuese necesario)
}

static void vTarea1(void *pvParameters)
{
	BaseType_t xStatus; //Variable de estado de cola
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); // se inicializa la variable con la actual cantidad de ticks. Luego es manejada por la API de vTaskDelayUntil()
	int c=0;
	char mensaje[5];
	sprintf(mensaje, "%d", c);
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; ) {
		c++;
		if (c==10000) c=0;
		sprintf(mensaje, "%d", c);
		xStatus = xQueueSend (cola, (void *) mensaje, portMAX_DELAY); //Escribe en la cola 
		if (xStatus==pdFAIL) printf("Error en la escritura (Tarea1)\r\n");
		else printf("T1 escribio en MQ\r\n");
		
		vTaskDelayUntil( &xLastWakeTime, xDelay1500ms ); //Asegura cierta cantidad de tics entre una ejecucion y otra
		
	}
}

static void vTarea2(void *pvParameters)
{
	char cad [5];
	int a;
		
	while(1)
	{
		//Esta tarea se bloqueará hasta que entre la ISR
		if (( xSemaphoreTake( sem, (portTickType) 1000 )) == pdTRUE) //Se desperto de la ISR
		{
			//Esto pasa cada vez que entra la ISR y se desbloquea el semáforo
			if (xQueueReceive (cola, (void *) cad,(portTickType) 0xFFFFFFFF )==pdTRUE) //Recibe datos de la cola
				{
				a=atoi(cad); //Convierte a int lo recibido
				printf("T2 Lee de MQ: %d \r\n", a);
			}
			else printf("Error en la lectura.\r\n");
			
		}
	}
}


int main(void)
{
	//Se inicializa HW
	initHardware(); /* Inicializa el Hardware del microcontrolador */
	InitTimer();
	
	/* Se inicializan los semÃ¡foros */
	sem = xSemaphoreCreateBinary ();  //se inicializa por defecto en 0
	//Se crea la cola de mensajes
	cola = xQueueCreate (TAM_COLA, TAM_MSG); //Crea la cola (generalmente en el main)
	
	/* Se crean las tareas */
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, NULL );
	
	NVIC_EnableIRQ(RITIMER_IRQn); //comentar que hace esta linea .....
	/* Set lowest priority for RIT */
	NVIC_SetPriority(RITIMER_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	
	vTaskStartScheduler(); /* y por Ãºltimo se arranca el planificador . */
	//Nunca llegara a ese lazo  .... espero
	for( ;; );
	return 0;
	
}
