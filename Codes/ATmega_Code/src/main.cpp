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
#include <vector>
#include "CoordinateConverter.h"
#include "DataDecoder.h"
#include "Stepper.h"
#include "Accelerometer.h"

// The accelerometer we use is an MPU6050.
#define ACC_I2C_ADDR 0x69

#define AZIMUTH_ANGULAR_RESOLUTION 1 // degrees
#define ALTITUDE_ANGULAR_RESOLUTION 1 // degrees

// #define Serial_INT 2 // Interrupts seem not working.

// Variables to be updated based on the Serial data from the ESP32.
volatile int year = 2000, month = 1, day = 1, hour = 12, minute = 0;
volatile double second = 0;
volatile double latitude = 0, longitude = 0;
double ra = 0, dec = 0;
bool valuesUpdated = true;

// Local coordinate values.
double altitude = 0, azimuth = 0;

float roll = 0, yawn = 0;

CoordinateConverter converter;
Accelerometer accelerometer;

// Function Declarations
void handleSerial();
void autoUpdateTime();

void setup()
{
  accelerometer.begin(ACC_I2C_ADDR);

  // Need the accelerometer to be horizontally flat.
  // If not practical, comment this out.
  // accelerometer.calibrateError();
  
  pinModeSteppers();

  Serial.begin(115200);
  // Maybe need to add some initial delay to get the initial data from the ESP32 in the setup.

  // pinMode(Serial_INT, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(Serial_INT), handleSerial, RISING);

  autoUpdateTime();
}

void loop()
{
  handleSerial();

  if (valuesUpdated)
  {
    converter.updateLocation(latitude, longitude);
    converter.updateDateUTC(day, month, year);
    converter.updateTimeUTC(hour, minute, second);
    converter.update_RA_DEC(ra, dec);
    valuesUpdated = false;
  }

  converter.updateTimeUTC(hour, minute, second);
  converter.updateDateUTC(day, month, year); // Only necessary on a moment after midnight.

  vector<double> altaz = converter.convert();
  altitude = altaz[0];
  azimuth = altaz[1];

  // Beep if altitude is below zero.

  // Turn bottom part to `azimuth`.
  yawn = 0; // Magnetometer.getYawn();  // This should return absolute angle from the North.
  bool motorDirectionDown = (azimuth - yawn) >= 0;  // Might neeed to change to <=, depending on the actual setup.
  while (azimuth - yawn < AZIMUTH_ANGULAR_RESOLUTION) {
    rotate(STEPPER_DOWN, motorDirectionDown);
  }

  // Turn top part to `altitude`.
  roll = accelerometer.getRoll(); // Either roll or pitch depending on how the accelerometer is mounted.
  bool motorDirectionUp = (altitude - roll) >= 0;  // Might neeed to change to <=, depending on the actual setup.
  while (altitude - roll < ALTITUDE_ANGULAR_RESOLUTION) {
    rotate(STEPPER_UP, motorDirectionUp);
  }
}

// Function Definitions
void handleSerial()
{
  if (Serial.available())
  {
    const int buffSize = 50;
    char input[buffSize];
    Serial.readStringUntil('\n').toCharArray(input, buffSize);

    data inputData = decode(input);

    if (inputData.type == "DATE")
    {
      day = (int)inputData.value1;
      month = (int)inputData.value2;
      year = (int)inputData.value3;
    }
    else if (inputData.type == "TIME")
    {
      hour = (int)inputData.value1;
      minute = (int)inputData.value2;
      second = inputData.value3;
    }
    else if (inputData.type == "GPS")
    {
      latitude = inputData.value1;
      longitude = inputData.value2;
    }
    else if (inputData.type == "RADEC")
    {
      ra = inputData.value1;
      dec = inputData.value2;
    }

    valuesUpdated = true;
  }

  // == TODO ==
  // Send an acknowledgement back to the ESP32 after a successful reception of data.
}

void autoUpdateTime()
{
  // The following are internal registers in ATmega328.
  // Internal interrupts (Timers) are used to keep track of time precisely.
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
  // e.g.: Update from 30th June to 1st of July.
  // However, let's assume this is enough for demonstration.

  // Setting back to 3036, otherwise it starts back from 0.
  TCNT1 = 3036;
}