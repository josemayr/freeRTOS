#include <Arduino_FreeRTOS.h>

//define task handles
TaskHandle_t taskABC_Handler;
TaskHandle_t taskNumbers_Handler;


// define two Tasks
void taskNumbers( void *pvParameters );
void taskABC( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }


  // Now set up two Tasks to run independently.
  xTaskCreate(
    taskABC
    ,  "Letters" // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle
  
  xTaskCreate(
    taskNumbers
    ,  "Numbers" // A name just for humans
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



void taskNumbers( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  for (;;) {
    for (int i = 0; i <= 9; i++) {
      Serial.print(i);
    }
   // vTaskDelay(100);
  }
}

void taskABC( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  for (;;) {
    for (int i = 0; i < 24; i++) {
      Serial.print(char('a' + i));
    }
    //vTaskDelay(100);
  }
}
