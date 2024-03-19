#include <Arduino.h>
// #include <StandardCplusplus.h>
#include <vector>
#include <cmath>
#include <Wire.h>

#include "Accelerometer.h"

using namespace std;

Accelerometer::Accelerometer(int addr) {
    i2c_address = addr;

    initialize();
}

void Accelerometer::initialize() {
    Wire.begin();                      // Initialize comunication
    Wire.beginTransmission(i2c_address);       // Start communication with MPU6050
    Wire.write(0x6B);                  // Talk to the register 6B
    Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);        //end the transmission
}

vector<float> Accelerometer::getAcceleration() {
    Wire.beginTransmission(i2c_address);
    Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(i2c_address, 6, true); // Read 6 registers total, each axis value is stored in 2 registers

    vector<float> readings;

    // //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
    accX = (Wire.read() << 8 | Wire.read()) / 16384.0;
    accY = (Wire.read() << 8 | Wire.read()) / 16384.0;
    accZ = (Wire.read() << 8 | Wire.read()) / 16384.0;

    readings.push_back(accX); // X-axis value
    readings.push_back(accY); // Y-axis value
    readings.push_back(accZ); // Z-axis value

    return readings;
}

void Accelerometer::calibrateError() {
    // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
    // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
    // Read accelerometer values 200 times
    int c = 0;
    float errorX = 0, errorY = 0;

    while (c < 200) {
        vector<float> readings = getAcceleration();
        // Sum all readings
        errorX += + ((atan((readings[1]) / sqrt(pow((readings[0]), 2) + pow((readings[2]), 2))) * 180 / PI));
        errorY += + ((atan(-1 * (readings[0]) / sqrt(pow((readings[1]), 2) + pow((readings[2]), 2))) * 180 / PI));
        c++;
    }

    //Divide the sum by 200 to get the error value
    accErrorX = errorX / 200;
    accErrorY = errorY / 200;
}

float Accelerometer::getRoll() {
    return (atan(accY / sqrt(pow(accX, 2) + pow(accZ, 2))) * 180 / PI) - accErrorX;
    
}

float Accelerometer::getPitch() {
    return (atan(-1 * accX / sqrt(pow(accY, 2) + pow(accZ, 2))) * 180 / PI) - accErrorY;
}