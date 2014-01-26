#ifndef MOTOR_H_
#define MOTOR_H_

#include "../globals.h"

void initMotor();

void leftMotor(s16 speed);
void rightMotor(s16 speed);

void shutdownMotor();

#endif /* MOTOR_H_ */