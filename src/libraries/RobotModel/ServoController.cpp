#include "RobotModel/ServoController.h"

ServoController::ServoController():zeroAngle(DEFAULT_ANGLE),currAngle(INIT_ANGLE),initAngle(INIT_ANGLE){} 

void ServoController::init()
{
	currAngle=this->initAngle;
	Servo::write(this->initAngle);
	
}

void ServoController::zero()
{
	currAngle=this->zeroAngle;
	Servo::write(this->zeroAngle);
}

void ServoController::changeAngle(int inc)
{
	int16 old = currAngle;
	currAngle+=inc;
	if(currAngle != old)
		Servo::write(this->currAngle);
}
