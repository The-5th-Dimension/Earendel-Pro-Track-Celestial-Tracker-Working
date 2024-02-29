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
#include <StandardCplusplus.h>
#include "CoordinateConverter.h"

#define Serial_INT 2

// Variables to be updated based on the Serial data from the ESP32.
volatile int year = 2000, month = 1, day = 1, hour = 12, minute = 0;
volatile double second = 0;
volatile double latitude = 0, longitude = 0;
double ra = 0, dec = 0;

// Local coordinate values.
double altitude = 0, azimuth = 0;

void handleSerial();
void autoUpdateTime();

void setup()
{
  pinMode(Serial_INT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Serial_INT), handleSerial, RISING);

  autoUpdateTime();
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void handleSerial()
{
  // The function definition depends on how the ESP32 encodds data.
}

void autoUpdateTime()
{
  // The following are internal registers in ATmega328.
  // Internal interrupts are used to precissely keep track of time.
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 3036;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
}

ISR(TIMER1_OVF_vect)
{
  second += 1;
  if (second == 60)
  {
    second = 0;
    minute += 1;
  }
  if (minute == 60)
  {
    minute = 0;
    hour += 1;
  }
  if (hour == 24)
  {
    hour = 0;
    day += 1;
  }
  // This should be extended to work well with month and year boundaries.
  // e.g.: Update from 31st March to 1st April.
  // However, let's assume this is enough for demonstration.

  // Setting back to 3036, otherwise it starts back from 0.
  TCNT1 = 3036;
}