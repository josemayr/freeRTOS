#include <Arduino_FreeRTOS.h>
#include <timers.h>
#include <task.h>

/* The periods assigned to the one-shot and auto-reload timers. */
#define ONE_SHOT_TIMER_PERIOD pdMS_TO_TICKS( 60000 )
#define AUTO_RELOAD_TIMER_PERIOD pdMS_TO_TICKS( 5000 )

//create reference hanlders for one-shot and auto-relaod timers
TimerHandle_t xTimerOneShot, xTimerAutoReload;
BaseType_t xTimer1Started, xTimer2Started;

//TaskHandle_t xTaskOne, xTaskAuto;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two Tasks to run independently.

  xTimerOneShot = xTimerCreate("OneShot",
                               ONE_SHOT_TIMER_PERIOD,
                               pdFALSE,
                               0,
                               vTimerOneShotCallback);

  xTimerAutoReload = xTimerCreate("AutoReload",
                                  AUTO_RELOAD_TIMER_PERIOD,
                                  pdTRUE,
                                  0,
                                  vTimerAutoReloadCallback);

  /* Check the software timers were created. */
  if ( ( xTimerOneShot != NULL ) && ( xTimerAutoReload != NULL ) )
  {
    xTimer1Started = xTimerStart( xTimerOneShot, 0 );
    xTimer2Started = xTimerStart( xTimerAutoReload, 0 );

    if ( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
    {
      /* Start the scheduler. */
      vTaskStartScheduler();
    }
  }
}

void loop()
{
  // Empty. Things are done in Tasks.
}

static void vTimerOneShotCallback( TimerHandle_t xTimer )
{
  Serial.println("*");
}
static void vTimerAutoReloadCallback( TimerHandle_t xTimer )
{
  Serial.println("%");
}
