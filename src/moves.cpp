#include "moves.h"
#include <math.h>

void plat()
{
	servos_command(SERVO_ARG, -90);
	servos_command(SERVO_ARD, 90);
	servos_command(SERVO_PTG, 0);
	servos_command(SERVO_PTD, 0);
	servos_command(SERVO_AVG, 70);
	servos_command(SERVO_AVD, -70);
}

void servos_command_time(uint8_t index, float pos,int timeMilliSeconds)
{
	float currentPos =	servos_get_command(index);
	float deltaPos = currentPos - pos;
	uint8_t signe = (deltaPos > 0 ? 1:-1);
	int wait = timeMilliSeconds / deltaPos;
	
	deltaPos = abs(deltaPos);
	while(deltaPos > 0)
	{
		servos_command(index,currentPos += signe);
		delay_us(wait*2000);
		deltaPos--;
	}
}

void debout()
{
	servos_reset(SERVO_ARG);
	servos_reset(SERVO_ARD);
	servos_reset(SERVO_PTG);
	servos_reset(SERVO_PTD);
	servos_reset(SERVO_AVG);
	servos_reset(SERVO_AVD);
}

void pushup()
{
	int i;
	for(i = -70; i<30; i++)
	{
		servos_command(SERVO_AVG, i*(-1));
		servos_command(SERVO_AVD, i);
		delay_us(100000);
	}
	servos_command(SERVO_AVG, -30);
	servos_command(SERVO_AVD, 30);
}

void pompes()
{
	plat();
	delay_us(1000000);
	debout();
	delay_us(1000000);
	plat();
	delay_us(1000000);
	debout();
	delay_us(1000000);
	plat();
	delay_us(1000000);
	debout();
}

void pompes_avant()
{
	plat();
	delay_us(500000);
	pushup();
	delay_us(500000);
	plat();
	delay_us(500000);
	pushup();
	delay_us(500000);
	plat();
	delay_us(500000);
	pushup();
}
