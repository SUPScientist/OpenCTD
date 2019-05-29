/*
 * Project OpenCTD_complete_noCell
 * Description: An attempt to replicate the OceanographyforEveryone/OpenCTD project on a Particle Boron; this first attempt does not utilize cellular data transfer.
 * Author: PJB
 * Date: 8-May-2019
 */


// MS5803_I2C libraries for communicating with the pressure sensor.                                                                              
#include <MS5803_I2C.h> //CAN WE MAKE THIS LIBRARY SMALLER?

// DS18B20 library and OneWire "sublibrary" used for temperature sensor.
#include <DS18B20.h>
#include <math.h>

// For the SD card reader.           
#include <SPI.h>
#include "SdFat.h"

// For the Real-Time Clock
// #include <RTClib.h>

// Conductivity sensor
float EC_float = 0;  // Electrical conductivity.
char EC_data[48];    // A 48 byte character array to hold incoming data from the conductivity circuit. 
char *EC;            // Character pointer for string parsing.
byte received_from_sensor = 0;  // How many characters have been received.
byte string_received = 0;       // Whether it received a string from the EC circuit.

// Temperature sensor
DS18B20  ds18b20(D2, true); //Sets Pin D2 for Water Temp Sensor and says this is the only sensor on bus. 
double   celsius;
const int      MAXRETRY          = 4;

/* Pressure sensor
* Begin class with selected address
* available addresses (selected by jumper on board)
* default is ADDRESS_HIGH
* ADDRESS_HIGH = 0x76
* ADDRESS_LOW  = 0x77
*/  
MS5803 sensor(ADDRESS_HIGH);
double pressure_abs; //define absolute pressure variable

// SD Card
const uint8_t chipSelect = SS; // SD chip select pin.  Be sure to disable any other SPI devices such as Enet.
SdFat sd; // File system object.
SdFile file; // Log file.
#define FILE_BASE_NAME "Data" // Log file base name.  Must be six characters or less.
// Make filename something generic with numbers at the end so we always check to see if a given filename exists
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13] = FILE_BASE_NAME "00.csv";

// Particle-specific: so that we can manually disable cellular capabilities (cellular.off() call below)
SYSTEM_MODE(MANUAL); 

// Start up system. 
void setup(void) {
  // Keep things simple with cell off for now
  Cellular.off(); 

  Serial.begin(9600);   // Set baud rate.
  Serial1.begin(9600); // Set baud rate for conductivty circuit.

  pinMode(10, OUTPUT);  // Set data output pin for the SD card reader.
  
  sensor.reset(); //reset pressure sensor 
  sensor.begin(); //initialize pressure sensor
  // sensors.begin();  // Intialize the temperature sensors. // PJB commented out as it doesn't appear to be initialized
  
  delay(250);       // Wait a quarter second to continue.

  // Initialize SD card at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }

  if (file.open("datalog.txt", FILE_WRITE)) {
    file.println("");
    file.println("=== New Cast ===");
    file.close();
  }
  else {
    Serial.println("SD Card Error!");
  }

}

void loop(void) {

  // Read any pending data from the EC circuit.
  if (Serial1.available() > 0) {
    received_from_sensor = Serial1.readBytesUntil(13, EC_data, 48);

    // Null terminate the data by setting the value after the final character to 0.
    EC_data[received_from_sensor] = 0;
  }

  // Parse data, if EC_data begins with a digit, not a letter (testing ASCII values).
  if ((EC_data[0] >= 48) && (EC_data[0] <=57)) {
    parse_data();
  }

  delay(10);  // Wait 10 milliseconds.

  // Read temp sensor
  getTemp();

  // Log to the SD card...
  file.open("datalog.txt", FILE_WRITE);
  file.print(Time.now());
  file.print(",");
  file.print(sensor.getPressure(ADC_4096));
  file.print(",");
  file.print(celsius);
  file.print(",");
  file.println(EC);
  file.close();

  // Log to the serial monitor.
  Serial.print(Time.now());
  Serial.print(",");
  Serial.print(sensor.getPressure(ADC_4096));
  Serial.print(","); 
  Serial.print(celsius);
  Serial.print(",");
  Serial.print(EC);
  Serial.println("");

  delay(50);  // Wait 50 milliseconds.
}


// Parses data from the EC Circuit.
void parse_data() {

  EC = strtok(EC_data, ",");                  

}

void getTemp(){
  float _temp;
  int   i = 0;

  do {
    _temp = ds18b20.getTemperature();
  } while (!ds18b20.crcCheck() && MAXRETRY > i++);

  if (i < MAXRETRY) {
    celsius = _temp;
  }
  else {
    celsius = -999;
    Serial.println("Invalid reading");
  }
}