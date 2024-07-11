#include <StandardCplusplus.h>
#include <vector>

#include "Accelerometer.h"

#define I2C_ADDRESS 0x68

Accelerometer accelerometer;
struct accComp accValues;

void setup() {
  // put your setup code here, to run once:
  accelerometer.begin(I2C_ADDRESS);
  Serial.begin(9600);
  Serial.println("Calibrating accelerometer errors... Do not move.");\
  delay(1000);
  accelerometer.calibrateError();
  Serial.println("Done.");
}

void loop() {
  // put your main code here, to run repeatedly:
  accValues = accelerometer.getAcceleration();
  Serial.print(String(accValues.AccX) + "\t" + String(accValues.AccY) + "\t" + String(accValues.AccZ) + "\t\t");
  Serial.print("Roll: " + String(accelerometer.getRoll()) + "\t");
  Serial.print("Pitch: " + String(accelerometer.getPitch()));
  Serial.println();

  // delay(1000);
}
