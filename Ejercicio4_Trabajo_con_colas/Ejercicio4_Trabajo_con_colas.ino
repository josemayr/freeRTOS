#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <task.h>
#include <semphr.h>

//define task handles
TaskHandle_t writeTask_Handler;
TaskHandle_t readTask_Handler;

// Definir la variable de cola
QueueHandle_t queue;
int queueSize = 4;

// define Tasks
void writeTask( void *pvParameters );
void readTask( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  randomSeed(analogRead(A0));

  queue = xQueueCreate( queueSize, sizeof( int ) );

  if (queue == NULL) {
    Serial.println("Error creating the queue");
  }

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two Tasks to run independently.
  xTaskCreate(
    writeTask
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



void writeTask( void *pvParameters )  // This is a Task.
{

  int value = random(0, 9);
  for (;;) {
    if (sizeof(queue) / sizeof(int) < 4) {
      if (xQueueSendToBack(queue, &value, 1000) != pdTRUE) {
        printf("Error writeTask1");
      }
      else {
        //Serial.print((sizeof(queue)/sizeof(int)));
      }
      //vTaskDelay(100);
    }
  }
}

void readTask( void *pvParameters )  // This is a Task.
{
  int valueTotal = -1;
  
  for (;;) {
    if (uxQueueSpacesAvailable(queue) == 0) {
      while(uxQueueSpacesAvailable(queue) < 4) {
        if (xQueueReceive(queue, &valueTotal, 4000) == pdPASS) {
          Serial.print(valueTotal);
        }
      }
      Serial.println();
    }
  }
}
