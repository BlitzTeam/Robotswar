
#ifndef _SERVOCONTROLLER_H_
#define _SERVOCONTROLLER_H_

#define DEFAULT_ANGLE 90
#define INIT_ANGLE 45


#include "Servo/Servo.h"
/** Class for interfacing with RC servomotors. */
class ServoController : public Servo{
public:
	void init();
	void zero();
	void changeAngle(int inc);
	
	ServoController();

private :
	int16 zeroAngle; 
	int16 initAngle;
	int16 currAngle;
};

#endif  /* _SERVO_H_ */
