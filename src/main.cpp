#include <cstdlib>
#include <wirish/wirish.h>
#include <servos.h>
#include <terminal.h>

#define SERVO_AG 0
#define SERVO_AD 1

volatile bool flag = false;
volatile bool isUSB = false;
volatile bool cmdrunning = false;
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

TERMINAL_COMMAND(dance, "BOOGIE WONDERLAND !") //Marche pas :(
{
	servos_set_pos(SERVO_AD, 90);
	servos_set_pos(SERVO_AG, 90);
	delay_us(1000000);
	servos_set_pos(SERVO_AD, 80);
	servos_set_pos(SERVO_AG, 80);
	delay_us(300000);
	servos_set_pos(SERVO_AD, 70);
	servos_set_pos(SERVO_AG, 70);
	delay_us(300000);
	servos_set_pos(SERVO_AD, 60);
	servos_set_pos(SERVO_AG, 60);
	delay_us(300000);
	servos_set_pos(SERVO_AD, 50);
	servos_set_pos(SERVO_AG, 50);
	delay_us(300000);
	servos_set_pos(SERVO_AD, 40);
	servos_set_pos(SERVO_AG, 40);
	delay_us(300000);
	servos_set_pos(SERVO_AD, 30);
	servos_set_pos(SERVO_AG, 30);
	delay_us(300000);
}

TERMINAL_COMMAND(sinus, "Sinus on a servo")
{
	if(argc != 1)
	{
		terminal_io()->println("Usage : sinus <servo>");
		return;
	}
	cmdrunning = true;
	int pos=-90, dir=1;
	while(cmdrunning)
	{
		pos+=dir;
		if(pos == -90 || pos == 90)
			dir*=-1;
		servos_set_pos(servos_index(argv[0]), pos);
		delay_us(10000);
	}
}
	
/**
 * Function called @50Hz
 */
void tick()
{
    counter++;
    if(Serial3.available())
    	cmdrunning = false;
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
    servos_register(3, "AG");
	servos_calibrate(0, 2640, 3514, 5710, false);
	servos_register(5, "AD");
	servos_calibrate(1, 3720, 5801, 6855, false);
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

