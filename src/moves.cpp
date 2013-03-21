#include "moves.h"

void plat()
{
	servos_command(SERVO_ARG, -90);
	servos_command(SERVO_ARD, 90);
	servos_command(SERVO_PTG, 0);
	servos_command(SERVO_PTD, 0);
	servos_command(SERVO_AVG, 90);
	servos_command(SERVO_AVD, -90);
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
	servos_reset(SERVO_AVG);
	servos_reset(SERVO_AVD);
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
	delay_us(1000000);
	pushup();
	delay_us(1000000);
	plat();
	delay_us(1000000);
	pushup();
	delay_us(1000000);
	plat();
	delay_us(1000000);
	pushup();
}