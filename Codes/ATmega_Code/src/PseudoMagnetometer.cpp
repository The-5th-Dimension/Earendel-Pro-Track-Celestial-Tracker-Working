#include "PseudoMagnetometer.h"

unsigned long int angleToSteps(double angle) {
    return (unsigned long int) angle * STEPS_PER_REVOLUTION;
}

double stepsToAngle(unsigned long int steps) {
    return steps / STEPS_PER_REVOLUTION * 1.0;
}

