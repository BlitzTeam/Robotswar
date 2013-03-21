
#include <cstdlib>
#include <wirish/wirish.h>
#include <servos.h>
#include <terminal.h>
#include "moves.h"

#define SERVO_ARG 0
#define SERVO_ARD 1
#define SERVO_PTD 2
#define SERVO_AVD 3
#define SERVO_PTG 4
#define SERVO_AVG 5


volatile bool flag = false;
volatile bool isUSB = false;
volatile int counter = 0;
volatile int sinusing;
volatile int sinuspos, sinusdir;

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

TERMINAL_COMMAND(dance, "BOOGIE WONDERLAND !")
{
	plat();
}

TERMINAL_COMMAND(sinus, "Sinus on a servo")
{
	if(argc != 1)
	{
		terminal_io()->println("Usage : sinus <servo>");
		return;
	}
	sinusing = servos_index(argv[0]);
	sinuspos=-90;
	sinusdir=1;
}

TERMINAL_COMMAND(sinustop, "Stops the sinus")
{
	sinusing = -1;
}

TERMINAL_COMMAND(plat, "Aplatit le robot")
{
	plat();
}
	
/**
 * Function called @50Hz
 */
void tick()
{
    counter++;
    if(sinusing != -1)
	{
		sinuspos+=sinusdir;
		if(sinuspos == -90 || sinuspos == 90)
			sinusdir*=-1;
		servos_command(sinusing, sinuspos);
		delay_us(10000);
	}
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
    terminal_init(&Serial3);
    
    //Attach the 50Hz interrupt
    servos_attach_interrupt(setFlag);

    servos_register(3, "ARG");
	servos_calibrate(0, 2640, 3514, 5710, false);
	servos_register(5, "ARD");
	servos_calibrate(1, 3720, 5801, 6855, false);
	servos_register(27, "PTD");
	servos_calibrate(2, 2280, 4804, 7304, false);
	servos_register(26, "AVD");
	servos_calibrate(3, 1920, 3477, 6414, false);
	servos_register(9, "PTG");
	servos_calibrate(4, 1560, 4250, 7136, false);
	servos_register(10, "AVG");
	servos_calibrate(5, 2280, 5704, 7304, false);

	sinusing = -1;
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

