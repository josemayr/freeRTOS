#include <Arduino_FreeRTOS.h>

//define task handles
TaskHandle_t taskAsterisco_Handler;
TaskHandle_t taskBarra_Handler;
TaskHandle_t taskDolar_Handler;

// define two Tasks
void taskAsterisco( void *pvParameters );
void taskBarra( void *pvParameters );
void taskDolar ( void *pvParameteres );

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }


  // Now set up two Tasks to run independently.
  xTaskCreate(
    taskAsterisco
    ,  "Asterisco" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle

  xTaskCreate(
    taskBarra
    ,  "Barra" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle

  xTaskCreate(
    taskDolar
    ,  "Dolar" // A name just for humans
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



void taskAsterisco( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  for (;;) {
    Serial.print("*");
    vTaskDelay(5000);
  }
}


void taskBarra( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  for (;;) {
    Serial.print("/");
    vTaskDelay(15000);
  }
}

void taskDolar( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  for (;;) {
    Serial.print("$");
    vTaskDelay(60000);
  }
}
