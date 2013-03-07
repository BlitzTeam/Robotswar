#ifndef _SERVOCONTROLLER_H_
#define _SERVOCONTROLLER_H_

#define DEFAULT_ANGLE 512
#define INIT_ANGLE 256


#include "Servo/Servo.h"
/** Class for interfacing with RC servomotors. */
class ServoController : public Servo{
public:
	void init();
	void zero();
	void goCompliant();
	void changeAngle(int inc);
	void setAngle(int tar);
	int isCompliant();
	
	ServoController();

private :
	int16 zeroAngle; 
	int16 initAngle;
	int16 currAngle;
	int compliant; //bool
};

#endif  /* _SERVO_H_ */
