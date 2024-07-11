#ifndef PSEUDO_MAGNETOMETER_H
#define PSEUDO_MAGNETOMETER_H

#define STEPS_PER_REVOLUTION 3200   // Should update to the correct value.

unsigned long int angleToSteps(double angle);
double stepsToAngle(double steps);

#endif