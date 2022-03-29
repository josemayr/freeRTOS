#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "task.h"

#define PIN_PULSADOR 1

//COMO RECIBIMOS EL PULSADOR???


//manejador para el semรกforo como variable global
SemaphoreHandle_t xSemaphore = NULL;

void setup() {
  Serial.begin(9600);

  // se crea el semรกforo binario
  xSemaphore = xSemaphoreCreateBinary();

  xTaskCreate(taskPrint,
              "Print",
              1024,
              NULL,
              1,
              NULL);
              
  xSemaphoreGive(xSemaphore);
}

void loop() {}

void taskPrint(void *pvParameters)
{
  for (;;) {
    // Espero por la notificaciรณn de la ISR
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
      printf("Pulsador pulsado.\n");
      xSemaphoreGive(xSemaphore);
      vTaskDelay(1);
    }
  }
}
