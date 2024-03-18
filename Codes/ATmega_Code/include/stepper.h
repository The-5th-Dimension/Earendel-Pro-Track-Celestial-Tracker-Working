#ifndef STEPPER_H
#define STEPPER_H

#define STEPPER_DOWN 0
#define STEPPER_UP 1

#define DIR_1 0
#define DIR_2 1

#define STEPPER_DOWN_STEP 12
#define STEPPER_DOWN_DIR 13

#define STEPPER_UP_STEP 14
#define STEPPER_UP_DIR 15


void pinModeSteppers();
void rotate(int, int);

#endif