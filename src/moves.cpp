#include "moves.h"
#include <math.h>

void plat()
{
	servos_command(SERVO_ARG, -90);
	servos_command(SERVO_ARD, 90);
	servos_command(SERVO_PTG, 0);
	servos_command(SERVO_PTD, 0);
	servos_command(SERVO_AVG, 90);
	servos_command(SERVO_AVD, -90);
}

void servos_command_time(uint8_t index, float pos,int timeMilliSeconds)
{
	float currentPos =	servos_get_pos(index);
	float deltaPos = currentPos - pos;
	uint8_t signe = (deltaPos > 0 ? 1:-1);
	int wait = timeMilliSeconds / deltaPos;
	
	deltaPos = abs(deltaPos);
	while(deltaPos > 0)
	{
		servos_command(index,currentPos += signe);
		sleep(wait);
	}

}