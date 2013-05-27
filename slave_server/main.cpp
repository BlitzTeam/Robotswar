#include <string>
#include <cstdlib>
#include <wirish/wirish.h>
#include <servos.h>
#include <terminal.h>

#define SERVO_BR1 0
#define SERVO_BR2 1
#define SERVO_BL1 2
#define SERVO_BL2 3
#define SERVO_FM1 4
#define SERVO_FR1 5
#define SERVO_FR2 6
#define SERVO_FR3 7
#define SERVO_FR4 8
#define SERVO_FL1 9
#define SERVO_FL2 10
#define SERVO_FL3 11

volatile bool flag = false;
volatile bool isUSB = false;
volatile int counter = 0;

using namespace std;

string buffer;
int current_id = 0;

/**
 * Example counter, incremented @50hz
 */
TERMINAL_COMMAND(counter, "See the counter")
{
    terminal_io()->print("Counter: ");
    terminal_io()->println(counter);
}

/**
 * Function called @50Hz
 */
void tick()
{
    counter++;
    
   	unsigned int available_cout = SerialUSB.available();
   	if (available_cout > 0)
   	{
   		for (unsigned int i = 0; i < available_cout; i++)
   		{
   			char newchar = SerialUSB.read();

   			if (newchar == '|')
   			{
   				float value = atof(buffer.c_str());
   				SerialUSB.print('+');
   				servos_command(current_id, value);
   				buffer.clear();
   			}
   			else if (newchar == ':')
   			{
   				current_id = atoi(buffer.c_str());
   				buffer.clear();
   			}
   			else
				buffer += newchar;		
   		}
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
    
    uint16_t offset = 60 * DEFAULT_STEPS_PER_DEGREE;
    
    servos_register(5, "BR1");
	servos_calibrate(0, 3630, 4407 + offset, 7251, false, 4407);
	servos_register(8, "BR2");
	servos_calibrate(1, 2100, 4375, 6919, false);

	servos_register(11, "BL1");
	servos_calibrate(2, 2100, 4859 + offset, 5813, true, 4859);
	servos_register(3, "BL2");
	servos_calibrate(3, 2010, 4124, 6908, false);

	servos_register(4, "FM1");
	servos_calibrate(4, 2190, 3978, 6772, false);

	servos_register(27, "FR1");
	servos_calibrate(5, 2010, 4699, 6039, false);
	servos_register(26, "FR2");
	servos_calibrate(6, 1920, 4385 - offset, 6960, true, 4385);
	servos_register(25, "FR3");
	servos_calibrate(7, 2010, 5060, 6908, false);
	servos_register(15, "FR4");
	servos_calibrate(8, 2010, 6908, 6908, false);

	servos_register(9, "FL1");
	servos_calibrate(9, 2280, 4255, 7038, false);
	servos_register(10, "FL2");
	servos_calibrate(10, 1920, 4730 + offset, 7200, false, 4730);
	servos_register(16, "FL3");
	servos_calibrate(11, 2280, 5129, 7038, false);
    
    servos_enable_all();
    
    //Attach the 50Hz interrupt
    servos_attach_interrupt(setFlag);
}

/**
 * Main loop
 */
 
void loop()
{
    //Handle @50Hz interrupt
    if (flag) 
    {
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

    while (true) 
	{
        loop();
    }

    return 0;
}


