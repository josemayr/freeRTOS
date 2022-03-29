#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <task.h>
#include <semphr.h>

//define task handles
TaskHandle_t task_Handler;

// Definir la variable de cola 
QueueHandle_t queue;
int queueSize = 4;


// define Tasks
void writeTask1( void *pvParameters );
void writeTask2( void *pvParameters );
void writeTask3( void *pvParameters );
void writeTask4( void *pvParameters );
void readTask( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  queue = xQueueCreate( queueSize, sizeof( int ) );

  if (queue == NULL) {
    Serial.println("Error creating the queue");
  }

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two Tasks to run independently.
  xTaskCreate(
    writeTask1
    ,  "writer" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle
  xTaskCreate(
    writeTask2
    ,  "writer" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle
  xTaskCreate(
    writeTask3
    ,  "writer" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle
  xTaskCreate(
    writeTask4
    ,  "writer" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle

  xTaskCreate(
    readTask
    ,  "reader" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/



void writeTask1( void *pvParameters )  // This is a Task.
{

  int value = 1;
  for (;;) {
    if (xQueueSendToBack(queue, &value, 1000) != pdTRUE) {
      printf("Error writeTask1");
    }
    vTaskDelay(1000);
  }
}

void writeTask2( void *pvParameters )  // This is a Task.
{

  int value = 2;
  for (;;) {
    if (xQueueSendToBack(queue, &value, 1000) != pdTRUE) {
      printf("Error writeTask2");
    }
    vTaskDelay(1000);
  }
}

void writeTask3( void *pvParameters )  // This is a Task.
{

  int value = 3;
  for (;;) {
    if (xQueueSendToBack(queue, &value, 1000) != pdTRUE) {
      printf("Error writeTask3");
    }
    vTaskDelay(1000);
  }
}

void writeTask4( void *pvParameters )  // This is a Task.
{

  int value = 4;
  for (;;) {
    if (xQueueSendToBack(queue, &value, 1000) != pdTRUE) {
      printf("Error writeTask4");
    }
    vTaskDelay(1000);
  }
}

void readTask( void *pvParameters )  // This is a Task.
{
  int i;
  int valueTotal;

  for (;;) {
    if (xQueueReceive(queue, &valueTotal, 4000) != pdTRUE) {
     // if (len(queue) == 4) {
      //FALTA LEER LOS VALORES EN COLA Y VER SI USAR INT U OTRA OPCION
     // }
    }
    else {
      printf("Fallo al leer la cola.");
    }
  }
}
