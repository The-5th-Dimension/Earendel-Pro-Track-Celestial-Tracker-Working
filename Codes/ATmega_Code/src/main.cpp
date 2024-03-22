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
#include "PseudoMagnetometer.h"

// The accelerometer we use is an MPU6050.
#define ACC_I2C_ADDR 0x68

#define AZIMUTH_ANGULAR_RESOLUTION 5 // degrees
#define ALTITUDE_ANGULAR_RESOLUTION 5 // degrees

// #define Serial_INT 2 // Interrupts seem not working.

// Variables to be updated based on the Serial data from the ESP32.

// SOME RANDOM (EXPECTED ON DEMONSTRATION DAY) VALUES ARE SET FOR BETTER ACCURACY.
volatile int year = 2024, month = 3, day = 23, hour = 4, minute = 30; // Expected day and time of demonstration.
volatile double second = 0;
volatile double latitude = 6.9271, longitude = 79.8612;
double ra = 6.75, dec = -16.7;  // Sirius
bool valuesUpdated = true;
double currentAzimuth = 0;
unsigned int azimuthStep = 0;

// Local coordinate values.
double altitude = 0, azimuth = 0;

float roll = 0;
// float yawn = 0;

CoordinateConverter converter;
Accelerometer accelerometer;

// Function Declarations
void handleSerial();
void autoUpdateTime();
void debugPrint();
double absolute(double); // Custom function to find the absolute value.

void setup()
{
  // Serial output for debug data output.
  Serial.begin(115200);

  accelerometer.begin(ACC_I2C_ADDR);

  // Need the accelerometer to be horizontally flat.
  // If not practical, comment this out.
  // accelerometer.calibrateError();
  
  pinModeSteppers();

  // Maybe need to add some initial delay to get the initial data from the ESP32 in the setup.

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

  // Lowest angle for the telescope is 0 degrees.
  if (altitude < 0) {
    altitude = 0;
  }

  // Turn bottom part to `azimuth`.

  // ===== WORKS ONLY WITH A MAGNETOMETER =====
  // yawn = 0; // Magnetometer.getYawn();  // This should return absolute angle from the North.
  // bool motorDirectionDown = (azimuth - yawn) >= 0;  // Might neeed to change to <=, depending on the actual setup.
  // if (absolute(azimuth - yawn) > AZIMUTH_ANGULAR_RESOLUTION) {
  //   rotate(STEPPER_DOWN, motorDirectionDown);
  // }
  // ==========


  // ALTERNATE METHOD WITHOUT A MAGNETOMETER
  // THIS METHOD REQUIRES THE INITIAL ALIGNMENT TO NORTH.
  //========================
  bool motorDirectionDown;
  // Might need to interchange >= and <, depending on the actual setup.
  if (currentAzimuth >= azimuth) {
    motorDirectionDown = DIR_1;
  }
  else if (currentAzimuth < azimuth) {
    motorDirectionDown = DIR_2;
  }

  double remainingAngle = absolute(currentAzimuth - azimuth);


  if ((azimuthStep < angleToSteps(remainingAngle)) &&  (absolute(currentAzimuth - azimuth) > AZIMUTH_ANGULAR_RESOLUTION)) {
    rotate(STEPPER_DOWN, motorDirectionDown);
    if (currentAzimuth >= azimuth) {
      currentAzimuth -= stepsToAngle(1);
    }
    else if (currentAzimuth < azimuth) {
      currentAzimuth += stepsToAngle(1);
    }
    azimuthStep++;
  }

  // Turn top part to `altitude`.
  roll = accelerometer.getRoll(); // Either roll or pitch depending on how the accelerometer is mounted.
  bool motorDirectionUp = altitude >= roll;  // Might neeed to change to <=, depending on the actual setup.
  if (absolute(altitude - roll) > ALTITUDE_ANGULAR_RESOLUTION) {
    rotate(STEPPER_UP, motorDirectionUp);
  }

  // // DEBUG
  // debugPrint();
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
  if (second >= 60)
  {
    second = 0;
    minute += 1;
  }
  if (minute >= 60)
  {
    minute = 0;
    hour += 1;
  }
  if (hour >= 24)
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

void debugPrint() {
  Serial.print(String(year) + "." + String(month) + "." + String(day) + "\t");
  Serial.print(String(hour) + ":" + String(minute) + "." + String(second) + "\t");
  Serial.print("Latitude: " + String(latitude) + ", Longitude: " + String(longitude) + "\t");
  Serial.print("RA: " + String(ra) + ", DEC: " + String(dec) + "\t");
  Serial.print("Altitude: " + String(altitude) + ", Azimuth: " + String(azimuth) + "\t");
  // Serial.print("Roll: " + String(roll) + ", Yawn: " + String(yawn) + "\t");
  Serial.print("Roll: " + String(roll) + ", CurrentAzimuth: " + String(currentAzimuth) + "\t");
  Serial.println();
}

double absolute(double value) {
  if (value >=0 ) {
    return value;
  }
  else {
    return -1 * value;
  }
}