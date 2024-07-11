#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

const int motorSpeedPin = D4;
const int motorDirectionPin = D5;

// PID constants
const float Kp = 40.0; // Proportional gain
const float Ki = 0.01; // Integral gain
const float Kd = 0.01; // Derivative gain

float setpoint = 0.0; // Desired angle
float previousError = 0.0;
float integral = 0.0;

void setup(void) {
  Serial.begin(115200);

  pinMode(motorDirectionPin, OUTPUT);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // Check if there's serial data available
  if (Serial.available() > 0) {
    // Read the serial input and set it as the new setpoint

    float temp = Serial.parseFloat();

    if(int(temp) != 0){setpoint = temp;}
    Serial.print("New Setpoint: ");
    Serial.println(setpoint);
  }

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float A_X = a.acceleration.x;

  // Calculate PID terms
  float error = setpoint - A_X;
  integral += error;
  float derivative = error - previousError;

  // Calculate PID output
  float output = Kp * error + Ki * integral + Kd * derivative;

  // Map PID output to motor speed
  int motorSpeed = constrain(int(output), -255, 255);

  // Set motor direction based on the sign of the output
  digitalWrite(motorDirectionPin, (output < 0) ? HIGH : LOW);

  // Set motor speed
  analogWrite(motorSpeedPin, abs(motorSpeed));

  // Save the current error for the next iteration
  previousError = error;

  // Print out the values
  Serial.print("Rotation X: ");
  Serial.print(A_X);
  Serial.print(" | PID Output: ");
  Serial.print(output);
  Serial.print(" | Set_point: ");
  Serial.println(setpoint);


  // delay(10);
}
