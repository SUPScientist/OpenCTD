/*
 * Project OpenCTD_BlinkTest
 * Description: Blink an LED
 * Author: PJB
 * Date: 30-Apr-2019
 */
#include "Particle.h"

void setup();
void loop();
#line 9 "/Users/pjb/Dropbox/Particle_Projects/OPO_OpenCTDTest/OpenCTD_BlinkTest/src/OpenCTD_BlinkTest.ino"
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

  // We'll leave it on for 1 second...
  delay(100);

  // Then we'll turn it off...
  digitalWrite(led1, LOW);

  // Wait 1 second...
  delay(100);


}
