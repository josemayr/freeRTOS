#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "task.h"

#define PIN_PULSADOR 2

bool pressed = false;

void pulsadorISR(){
  pressed = true;
  Serial.println(pressed);
}

//manejador para el semaforo como variable global
SemaphoreHandle_t xSemaphore = NULL;

void setup() {
  Serial.begin(9600);

  // se crea el semaforo binario
  xSemaphore = xSemaphoreCreateBinary();

  xTaskCreate(taskPrint,
              "Print",
              1024,
              NULL,
              1,
              NULL);
              
  xSemaphoreGive(xSemaphore);

  attachInterrupt(digitalPinToInterrupt(PIN_PULSADOR),pulsadorISR,RISING);
}

void loop() {}

void taskPrint(void *pvParameters)
{
  for (;;) {
    if (pressed && (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)) {
      printf("Pulsador pulsado.\n");
      xSemaphoreGive(xSemaphore);
      pressed = false;
      vTaskDelay(1);
    }
  }
}
