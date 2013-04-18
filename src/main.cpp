#include <cstdlib>
#include <wirish/wirish.h>
#include <servos.h>
#include <terminal.h>
#include <spline.h>
#include "moves.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define START_NUM_SERVO 3


volatile bool flag = false;
volatile bool isUSB = true;
volatile int counter = 0;



/**
 * Example counter, incremented @50hz
 */

TERMINAL_COMMAND(counter, "See the counter")
{
    terminal_io()->print("Counter: ");
    terminal_io()->println(counter);
}

TERMINAL_COMMAND(switchcom, "Switch between USB and WiFI")
{
	if(isUSB)
	{
		terminal_io()->println("Switching to WiFI control");
		isUSB = false;
        terminal_init(&Serial3);
	}
	else
	{
		terminal_io()->println("Switching to USB control");
		isUSB = true;
        terminal_init(&SerialUSB);
	}
}

TERMINAL_COMMAND(spline_dump, "Dump the current splines on a servomotor. Takes two args")
{

	for (int i = 0; i < SERVOS_MAX_NB; i++)
	{
		if (currentMove[i] != NULL)
		{
			terminal_io()->print("Static Spline ");
			terminal_io()->print(argv[1]);
			terminal_io()->println(";");
			for (int j = 0; j < currentMove[i]->getPointCount(); j++)
			{
				terminal_io()->print(argv[1]);
				terminal_io()->print("->addPoint(");
				terminal_io()->print(currentMove[i]->getPointX(j));
				terminal_io()->print(", ");
				terminal_io()->print(currentMove[i]->getPointY(j));
				terminal_io()->println(");");
			}
		}
		
	}
}

TERMINAL_COMMAND(spline_ui, "Create a new Spline. Usage: spline_ui [ServoLabel] [number of points]")
{
    if (argc == 2) 
    {
        uint8_t i = servos_index(argv[0]);
        if (i != (uint8_t)-1) 
        {
        	int pos = 0;
        	int pointCounter = 0;
        	int numberOfPoints(atoi(argv[1]));
        	Spline spline;
        	while (pointCounter < numberOfPoints)
        	{		    	
		        terminal_bar_init(-90, 90, (int)(servos_get_command(i)));
		        while (terminal_bar_escaped() == false) 
		        {
		            pos = terminal_bar_tick();
		            servos_command(i, pos);
		        }
   
		        spline.addPoint((double) (pointCounter * 50.0), (double) pos);
		       	pointCounter++;
		    }
		    
		    currentMove[i] = &spline;
        } 
        else 
            terminal_io()->println("Unknown label");
    } 
    else 
        terminal_io()->println("Bad usage");
}

TERMINAL_COMMAND(sinus, "Sinus on a servo")
{
	if(argc != 1)
	{
		terminal_io()->println("Usage : sinus <servo>");
		return;
	}
	int id = servos_index(argv[0]);
	move_sinus(id);

}

TERMINAL_COMMAND(stopmove, "Stops all the moves")
{
	move_stop();
}

/**
 * Function called @50Hz
 */
void tick()
{
    counter++;
    int i;
    for(i=0;i<SERVOS_MAX_NB;i++)
		if(currentMove[i])
		{
			int pos = currentMove[i]->getMod(counter*1.0);
			servos_command(i, pos);
		}
	flag = false;
}

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

    //...or not (temp)
    terminal_init(&SerialUSB);
    //terminal_init(&Serial3);
    
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

/**
 * Main loop
 */
void loop()
{
    //Handle terminal communication
    terminal_tick();

    //If something is available on USB, switching to USB
/*    if (SerialUSB.available() && !isUSB && enableUSB) {
        isUSB = true;
        terminal_init(&SerialUSB);
    }*/

    //Handle @50Hz interrupt
    if (flag) {
        tick();
    }
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

    while (true) {
        loop();
    }

    return 0;
}

