/*
 * Project OpenCTD_Test0
 * Description:
 * Author:
 * Date:
 */
#include "Particle.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

int led1 = D7;

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Cellular.off();
  pinMode(led1, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  // To blink the LED, first we'll turn it on...
  digitalWrite(led1, HIGH);

  // Keep LED on for (x) milliseconds
  delay(1000);

  // Then we'll turn it off...
  digitalWrite(led1, LOW);

  // Wait (y) milliseconds...
  delay(1000);


}