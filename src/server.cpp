#include <cstdlib>
#include <wirish/wirish.h>
#include <servos.h>
#include <terminal.h>
#include <spline.h>
#include "moves.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#define START_NUM_SERVO 3
#define ORDER_FORWARD 0
#define ORDER_BACKWARD 1
#define ORDER_TURNLEFT 2
#define ORDER_TURNRIGHT 3
#define ORDER_SIEGEMODE 4

volatile bool flag = false;
volatile bool isUSB = true;
volatile int counter = 0;

/**
 * Interrupt @50hz, set the flag
 */
void setFlag()
{
    flag = true;
}

/**
 * Setting up the board
 */
void setup()
{
    //Initialize robotcampus servos
    servos_init();
    
    //Begining on WiFly Mode
    Serial3.begin(115200);
    
    //Attach the 50Hz interrupt
    servos_attach_interrupt(setFlag);
    /*
    servos_register(3, "ARG");
	servos_calibrate(0, 1920, 3514, 5710, false);
	servos_register(5, "ARD");
	servos_calibrate(1, 3720, 5801, 7500, false);
	servos_register(27, "PTD");
	servos_calibrate(2, 2280, 4804, 7304, false);
	servos_register(26, "AVD");
	servos_calibrate(3, 1920, 3477, 6414, false);
	servos_register(9, "PTG");
	servos_calibrate(4, 1560, 4250, 7136, false);
	servos_register(10, "AVG");
	servos_calibrate(5, 2280, 5704, 7304, false);
	*/
	int i;

	move_init();
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain()
{
    init();
}

int main(void)
{
    setup();

    while (true) 
    {
        counter++;
		int i = 0;
		for(;i<SERVOS_MAX_NB;i++)
		{
			if(currentMove[i])
			{
				int pos = currentMove[i]->getMod(counter*1.0);
				servos_command(i, pos);
			}
			flag = false;
		}
	}
    return 0;
}

