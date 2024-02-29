/*

PROJECT PLAN

1. Use external interrrupts to trigger a UART transfer from the ESP32.
2. Get serial data about GPS location, UTC time, and RA-DEC coordinates.
3. Use the already built library to convert RA-DEC to ALT-AZ.
4. Turn the stepper motors to the required stellar object.
5. Keep focusing until another interrupt gives another object.
(Time updates can also come from an interrupt.)

*/

#include <Arduino.h>
#include "CoordinateConverter.h"

#define SerialINT 2

// Variables to be updated based on the Serial data from the ESP32.
volatile int year = 2000, month = 1, day = 1, hour = 12, minute = 0;
volatile double second = 0;
volatile double latitude = 0, longitude = 0;
double ra = 0, dec = 0;

// Local coordinate values.
double altitude = 0, azimuth = 0;

void handleSerial();

void setup()
{
  pinMode(SerialINT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SerialINT), handleSerial, RISING);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void handleSerial()
{
  // The function definition depends on how the ESP32 encodds data.
}
