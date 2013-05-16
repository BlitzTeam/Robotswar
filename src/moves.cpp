#include "moves.h"
#include <math.h>

#include <terminal.h>

Spline * currentMove[SERVOS_MAX_NB]; // exported in moves.h
char * servosNames[SERVOS_MAX_NB]; //exported in move.h

static Spline splineSinus;
static Spline  move[SERVOS_MAX_NB];
static Spline moveAV1;

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
	servos_register(4,"CALE");

	servos_calibrate(0, 2280, 2625, 5734, false);
	servos_calibrate(1, 1560, 3272, 6808, false);
	servos_calibrate(2, 4080, 6711, 7138, false);
	servos_calibrate(3, 1920, 5424, 7056, false);
	servos_calibrate(4, 1920, 4812, 7056, false);
	servos_calibrate(5, 2280, 6990, 6990, false);
	servos_calibrate(6, 2280, 3904, 7304, false);
	servos_calibrate(7, 2280, 4264, 6990, false);
	servos_calibrate(8, 1920, 1956, 7056, false);
	servos_calibrate(9, 1920, 5526, 7056, false);
	servos_calibrate(10, 1920, 7056, 7056, false);
	servos_calibrate(11, 2640, 2820, 4175, false);

	int i;
	for(i=0;i<SERVOS_MAX_NB;i++)
		currentMove[i] = NULL;

	splineSinus.addPoint(0.0*SPLINE_SINUS_TEMPO,0.0);
	splineSinus.addPoint(50.0*SPLINE_SINUS_TEMPO,60.0);
	splineSinus.addPoint(150.0*SPLINE_SINUS_TEMPO,-60);
	splineSinus.addPoint(200.0*SPLINE_SINUS_TEMPO,0.0);

	move[ARG0].addPoint(0.0*SPLINE_TEMPO,12);
	move[ARG0].addPoint(50.0*SPLINE_TEMPO,-20);
	move[ARG0].addPoint(100.0*SPLINE_TEMPO,12);

	move[ARG1].addPoint(0.0*SPLINE_TEMPO,-72);
	move[ARG1].addPoint(50.0*SPLINE_TEMPO,0);
	move[ARG1].addPoint(100.0*SPLINE_TEMPO,-72);


	move[ARD0].addPoint(0.0*SPLINE_TEMPO,20);
	move[ARD0].addPoint(50.0*SPLINE_TEMPO,-5);
	move[ARD0].addPoint(100.0*SPLINE_TEMPO,20);


	move[ARD1].addPoint(0.0*SPLINE_TEMPO,54);
	move[ARD1].addPoint(50.0*SPLINE_TEMPO,-10);
	move[ARD1].addPoint(100.0*SPLINE_TEMPO,54);


	move[AVD1].addPoint(0.0*SPLINE_TEMPO,2);
	move[AVD1].addPoint(50.0*SPLINE_TEMPO,38);
	move[AVD1].addPoint(100.0*SPLINE_TEMPO,2);

	move[AVG1].addPoint(0.0*SPLINE_TEMPO,0);
	move[AVG1].addPoint(50.0*SPLINE_TEMPO,-36);
	move[AVG1].addPoint(100.0*SPLINE_TEMPO,0);

	move[AVG2].addPoint(0.0*SPLINE_TEMPO,23);
	move[AVG2].addPoint(50.0*SPLINE_TEMPO,-52);
	move[AVG2].addPoint(100.0*SPLINE_TEMPO,23);

	move[AVD2].addPoint(0.0*SPLINE_TEMPO,-18);
	move[AVD2].addPoint(50.0*SPLINE_TEMPO,48);
	move[AVD2].addPoint(100.0*SPLINE_TEMPO,-18);
}

void move_go()
{
	currentMove[AVD1] = &move[AVD1];
	currentMove[AVG1] = &move[AVG1];
	currentMove[AVD2] = &move[AVD2];
	currentMove[AVG2] = &move[AVG2];
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

void move_stop()
{
		int i;
	for(i=0;i<SERVOS_MAX_NB;i++)
		currentMove[i] = NULL;

}