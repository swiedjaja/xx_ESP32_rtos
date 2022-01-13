#include <Arduino.h>
#include "device.h"

void taskBlinkRed(void* arg);
void taskBlinkGreen(void* arg);

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  xTaskCreatePinnedToCore(taskBlinkRed, "Blink Led Red", 2048, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(taskBlinkGreen, "Blink Led Green", 2048, NULL, 1, NULL, 1);
}

void loop() {
  vTaskDelay(0);
}

void taskBlinkRed(void* arg)
{
  for(;;)
  {
    TickType_t nTickStart = xTaskGetTickCount();
    digitalWrite(LED_RED, HIGH);
    // vTaskDelay(100/portTICK_PERIOD_MS);
    delay(250);
    digitalWrite(LED_RED, LOW);
    delay(250);
    // vTaskDelay(900/portTICK_PERIOD_MS);

    TickType_t nElapaseTick = xTaskGetTickCount() - nTickStart;
    Serial.printf("[Red] Core-%d : %u\n", xPortGetCoreID(), nElapaseTick);
  }
}

void taskBlinkGreen(void* arg)
{
  for(;;)
  {
    TickType_t nTickStart = xTaskGetTickCount();
    digitalWrite(LED_GREEN, HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(LED_GREEN, LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);

    TickType_t nElapaseTick = xTaskGetTickCount() - nTickStart;
    Serial.printf("[Green] Core-%d : %u\n", xPortGetCoreID(), nElapaseTick);
  }
}