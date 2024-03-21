#include <Arduino.h>
#include "Stepper.h"

void pinModeSteppers() {
    pinMode(STEPPER_DOWN_STEP, OUTPUT);
    pinMode(STEPPER_DOWN_DIR, OUTPUT);

    pinMode(STEPPER_UP_STEP, OUTPUT);
    pinMode(STEPPER_UP_DIR, OUTPUT);
}

void rotate(int motor, int direction) {
    if (motor == STEPPER_DOWN) {
        if (direction == DIR_1) {
            digitalWrite(STEPPER_DOWN_DIR, LOW);
        }
        else if (direction == DIR_2) {
            digitalWrite(STEPPER_DOWN_DIR, HIGH);
        }

        digitalWrite(STEPPER_DOWN_STEP, HIGH); 
        delayMicroseconds(500); 
        digitalWrite(STEPPER_DOWN_STEP, LOW); 
        delayMicroseconds(500); 
    } else if (motor == STEPPER_UP) {
        if (direction == DIR_1) {
            digitalWrite(STEPPER_UP_DIR, LOW);
        }
        else if (direction == DIR_2) {
            digitalWrite(STEPPER_UP_DIR, HIGH);
        }

        digitalWrite(STEPPER_UP_STEP, HIGH); 
        delayMicroseconds(500); 
        digitalWrite(STEPPER_UP_STEP, LOW); 
        delayMicroseconds(500); 
    }
}