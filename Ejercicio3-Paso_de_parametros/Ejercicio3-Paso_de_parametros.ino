#include <Arduino_FreeRTOS.h>

//define task handles
TaskHandle_t task_Handler;

// define Tasks
void task( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  const char *TextToTask = "texto a enviar";

  // Now set up two Tasks to run independently.
  xTaskCreate(
    task
    ,  "Task 1" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  (void*)&TextToTask //Parameters for the task
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



void task( void *pvParameters )  // This is a Task.
{
  char* TaskName = ( char* ) pvParameters;

  for (;;) {
    Serial.println( String(TaskName) );
    vTaskDelay(100);
  }

  

    
    
   
}
