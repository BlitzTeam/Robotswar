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