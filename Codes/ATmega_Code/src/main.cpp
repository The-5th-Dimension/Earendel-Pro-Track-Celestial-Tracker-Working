#include <Arduino.h>

/*

PROJECT PLAN

1. Use external interrrupts to trigger a UART transfer from the ESP32.
2. Get serial data about GPS location, UTC time, and RA-DEC coordinates.
3. Use the already built library to convert RA-DEC to ALT-AZ.
4. Turn the stepper motors to the required stellar object.
5. Keep focusing until another interrupt gives another object.
(Time updates can also come from an interrupt.)

*/

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
