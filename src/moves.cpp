#include "moves.h"
#include <math.h>

#include <terminal.h>

Spline * currentMove[SERVOS_MAX_NB]; // exported in moves.h
char * servosNames[SERVOS_MAX_NB]; //exported in move.h

static Spline splineSinus;

void move_init()
{
	servos_register(11,"ARG0");
	servos_register(3,"ARG1");
	servos_register(5,"ARD0");
	servos_register(8,"ARD1");
	servos_register(9,"AVG0");
	servos_register(10,"AVG1");
	servos_register(16,"AVG2");
	servos_register(27,"AVD0");
	servos_register(26,"AVD1");
	servos_register(25,"AVD2");
	servos_register(15,"AVD3");
	servos_register(4,"CALLE");

	int i;
	for(i=0;i<SERVOS_MAX_NB;i++)
		currentMove[i] = NULL;

	splineSinus.addPoint(0.0*SPLINE_SINUS_TEMPO,0.0);
	splineSinus.addPoint(50.0*SPLINE_SINUS_TEMPO,60.0);
	splineSinus.addPoint(150.0*SPLINE_SINUS_TEMPO,-60);
	splineSinus.addPoint(200.0*SPLINE_SINUS_TEMPO,0.0);

}

void move_sinus(uint8_t index)
{
	if(!currentMove[index])
	{
		terminal_io()->println("Go Sinus !");

		currentMove[index] = &splineSinus;
	}
	else
	{
		currentMove[index] = NULL;
		terminal_io()->println("Stop Sinus !");

	}
}


void plat()
{
	servos_command(SERVO_ARG, -90);
	servos_command(SERVO_ARD, 90);
	servos_command(SERVO_PTG, 0);
	servos_command(SERVO_PTD, 0);
	servos_command(SERVO_AVG, 70);
	servos_command(SERVO_AVD, -70);
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
		delay_us(50000);
	}
	servos_command(SERVO_AVG, -30);
	servos_command(SERVO_AVD, 30);
}

void pompes()
{
	plat();
	delay_us(SECONDE);
	debout();
	delay_us(SECONDE);
	plat();
	delay_us(SECONDE);
	debout();
	delay_us(SECONDE);
	plat();
	delay_us(SECONDE);
	debout();
}

void wave_droit()
{
	servos_command(SERVO_PTD, 50);
	delay_us(SECONDE);
	for (int i = 0 ; i < 4;i++)
	{
		servos_command(SERVO_AVD,-60);
		delay_us(SECONDE/2);
		servos_command(SERVO_AVD,-30);
		delay_us(SECONDE/2);
	}
	delay_us(SECONDE);
	servos_command(SERVO_PTD,0);
}

void wave_gauche()
{
	servos_command(SERVO_PTG, -50);
	delay_us(SECONDE);
	for (int i = 0 ; i < 4; i++)
	{
		servos_command(SERVO_AVG,60);
		delay_us(SECONDE/2);
		servos_command(SERVO_AVG,30);
		delay_us(SECONDE/2);		
	}
	delay_us(SECONDE);
	servos_command(SERVO_PTG,0);
}

void pompes_avant()
{
	plat();
	delay_us(SECONDE/2);
	pushup();
	delay_us(SECONDE/2);
	plat();
	delay_us(SECONDE/2);
	pushup();
	delay_us(SECONDE/2);
	plat();
	delay_us(SECONDE/2);
	pushup();
}



void twist()
{
	debout();
	servos_command(SERVO_PTD, -50);
	servos_command(SERVO_PTG, 50);
	int i;
	for(i = -50;i < 10;i++)
	{
		servos_command(SERVO_AVD, i);
		servos_command(SERVO_AVG, i*(-1));
		delay_us(10000);
	}
	delay_us(SECONDE*0.2);
	debout();
	delay_us(SECONDE*0.5);
}

void move_stop()
{
		int i;
	for(i=0;i<SERVOS_MAX_NB;i++)
		currentMove[i] = NULL;

}