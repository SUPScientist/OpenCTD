#include "application.h"
#line 1 "/Users/pjb/Dropbox/Particle_Projects/OPO_OpenCTDTest/OpenCTD_MS5803-14BA/OpenCTD_MS5803-14BA/src/OpenCTD_MS5803-14BA.ino"
/******************************************************************************
  SparkFun_MS5803_Demo.ino
  Demo Program for MS5803 pressure sensors.
  Casey Kuhns @ SparkFun Electronics
  7/20/2014
  https://github.com/sparkfun/MS5803-14BA_Breakout/
  The MS58XX MS57XX and MS56XX by Measurement Specialties is a low cost I2C pressure
  sensor.  This sensor can be used in weather stations and for altitude
  estimations. It can also be used underwater for water depth measurements.
  Resources:
  This library uses the Arduino Wire.h to complete I2C transactions.
  Development environment specifics:
	IDE: Arduino 1.0.5
	Hardware Platform: Arduino Pro 3.3V/8MHz
	T5403 Breakout Version: 1.0
**Updated for Arduino 1.8.8 5/2019**
  This code is beerware. If you see me (or any other SparkFun employee) at the
  local pub, and you've found our code helpful, please buy us a round!
  Distributed as-is; no warranty is given.
******************************************************************************/

#include <MS5803_I2C.h> // Click here to get the library: http://librarymanager/All#SparkFun_MS5803-14BA

// Begin class with selected address
// available addresses (selected by jumper on board)
// default is ADDRESS_HIGH

//  ADDRESS_HIGH = 0x76
//  ADDRESS_LOW  = 0x77

void setup();
void loop();
#line 31 "/Users/pjb/Dropbox/Particle_Projects/OPO_OpenCTDTest/OpenCTD_MS5803-14BA/OpenCTD_MS5803-14BA/src/OpenCTD_MS5803-14BA.ino"
MS5803 sensor(ADDRESS_HIGH);

//Create variables to store results
float temperature_c, temperature_f;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;

// Create Variable to store altitude in (m) for calculations;
double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)


SYSTEM_MODE(MANUAL);

void setup() {
  Cellular.off();

  // Start your preferred I2C object
  Wire.begin();
  //Initialize Serial Monitor
  Serial.begin(9600);
  //Retrieve calibration constants for conversion math.
  sensor.reset();
  sensor.begin();

  pressure_baseline = sensor.getPressure(ADC_4096);

}

void loop() {

  // To measure to higher degrees of precision use the following sensor settings:
  // ADC_256
  // ADC_512
  // ADC_1024
  // ADC_2048
  // ADC_4096

  // Read temperature from the sensor in deg C. This operation takes about
  temperature_c = sensor.getTemperature(CELSIUS, ADC_512);

  // Read temperature from the sensor in deg F. Converting
  // to Fahrenheit is not internal to the sensor.
  // Additional math is done to convert a Celsius reading.
  temperature_f = sensor.getTemperature(FAHRENHEIT, ADC_512);

  // Read pressure from the sensor in mbar.
  pressure_abs = sensor.getPressure(ADC_4096);

  Serial.println(pressure_abs); 

  delay(1000);

}

