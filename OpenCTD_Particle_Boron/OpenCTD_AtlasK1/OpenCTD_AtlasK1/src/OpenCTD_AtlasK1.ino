/*
 * Project OpenCTD_AtlasK1
 * Description: Conductivity sensor example
 * Author: PJB
 * Date: 8-May-2019
 */

float EC_float = 0;  // Electrical conductivity.

char EC_data[48];    // A 48 byte character array to hold incoming data from the conductivity circuit. 
char *EC;            // Character pointer for string parsing.

byte received_from_sensor = 0;  // How many characters have been received.
byte string_received = 0;       // Whether it received a string from the EC circuit.

SYSTEM_MODE(MANUAL);

void setup() {
  Cellular.off();
  Serial1.begin(9600); // Set baud rate for conductivity circuit.
}


void loop() {
  // Read any pending data from the EC circuit.
  if (Serial1.available() > 0) {
    received_from_sensor = Serial1.readBytesUntil(13, EC_data, 48);

    // Null terminate the data by setting the value after the final character to 0.
    EC_data[received_from_sensor] = 0;
  }

  delay(10);

  // Parse data, if EC_data begins with a digit, not a letter (testing ASCII values).
  if ((EC_data[0] >= 48) && (EC_data[0] <=57)) {
    parse_data();
  }

  Serial.println(EC);

  delay(50);

}

// Parses data from the EC Circuit.
void parse_data() {

  EC = strtok(EC_data, ",");                  

}