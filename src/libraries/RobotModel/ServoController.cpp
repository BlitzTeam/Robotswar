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

void ServoController::goCompliant()
{
	writeMicroseconds(0);
	currAngle = -1;
	compliant = 1;
}
void ServoController::changeAngle(int inc)
{
	int16 old = currAngle;
	compliant = 0;
	currAngle += inc;
	if(currAngle < this->getminAngle())
		currAngle = this->getminAngle();
	if(currAngle > this->getmaxAngle())
		currAngle = this->getmaxAngle();
	if(currAngle != old)
		Servo::write(this->currAngle);
}

void ServoController::setAngle(int tar)
{
	int16 old = currAngle;
	currAngle = tar;
	if(currAngle < this->getminAngle())
		currAngle = this->getminAngle();
	if(currAngle > this->getmaxAngle())
		currAngle = this->getmaxAngle();
	if(currAngle != old)
		Servo::write(this->currAngle);
}

int ServoController::isCompliant()
{
	return compliant;
}
