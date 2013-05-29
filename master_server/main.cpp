#include <stdlib.h>
#include <wirish/wirish.h>
#include <servos.h>
#include <terminal.h>
#include <spline.h>
#include <usb_cdcacm.h>
#include "myservos.h"

#define EYE1 6
#define EYE2 7


#define AMPLITUDE 40
#define DIR_AMPLITUDE 20

Spline s1;
Spline s2;

volatile bool isUSB = false;
volatile bool move = false;
volatile double t = 0.0;
volatile double leftGain = 1.0;
volatile double rightGain = 1.0;
volatile double timeGain = 2.0;
volatile double amplitudeGain = 1.0;
volatile double altitudeGain = 1.0;
volatile double backGain = 0.4;
volatile double balance = 1.0;
volatile double frontBalance = 1.0;
volatile double backBalance = 1.0;
volatile double leftOffset = 0.0;
volatile double rightOffset = 0.0;
volatile double frontOffset = 0.0;
volatile double backOffset = 0.0;
volatile double open = 0.0;
volatile double phase = 0.25;
volatile double frontOOffset = 0.0;
volatile double backOOffset = 0.0;
volatile double direction = 0.0;
volatile bool bipod = false;
volatile double phaseFR = 0.0f;
volatile double phaseFL = 3.0f;
volatile double phaseBR = 2.0f;
volatile double phaseBL = 1.0f;

TERMINAL_COMMAND(fbooffset, "Front/Back offsets")
{
    float l, r;
    if (argc == 2) {
        frontOOffset = atof(argv[0]);
        backOOffset = atof(argv[1]);
        terminal_io()->println("Fixed FB gain");
    }
}

TERMINAL_COMMAND(baud, "See the baudrate of the emulator")
{
    terminal_io()->println(usb_cdcacm_get_baud());
}

TERMINAL_COMMAND(phase, "Sets the phase")
{
    if (argc) {
        phase = atof(argv[0]);
        terminal_io()->println("Setting phase");
    }
}

volatile bool attack = false;

TERMINAL_COMMAND(attack, "Do an attack")
{
    if (argc && atoi(argv[0])) {
        attack = true;
    } else {
        attack = false;
    }
}

TERMINAL_COMMAND(move, "Enable/Disable the move")
{
    move = !move;
    terminal_io()->println("Toggling move state");
}

TERMINAL_COMMAND(time, "Time gain")
{
    float g;
    if (argc) {
        g = atof(argv[0]);
        terminal_io()->println("Fixed time gain");
        timeGain = g;
    }
}

TERMINAL_COMMAND(fboffset, "Front/Back offsets")
{
    float l, r;
    if (argc == 2) {
        frontOffset = atof(argv[0]);
        backOffset = atof(argv[1]);
        terminal_io()->println("Fixed FB gain");
    }
}

TERMINAL_COMMAND(lroffset, "Left/Right offsets")
{
    float l, r;
    if (argc == 2) {
        leftOffset = atof(argv[0]);
        rightOffset = atof(argv[1]);
        terminal_io()->println("Fixed LR gain");
    }
}

TERMINAL_COMMAND(open, "Opening")
{
    if (argc == 1) {
        open = atof(argv[0]);
        terminal_io()->println("Fixed Opening");
    }
}

TERMINAL_COMMAND(amp, "Amplitude gain")
{
    float g;
    if (argc) {
        g = atof(argv[0]);
        terminal_io()->println("Fixed amplitude gain");
        amplitudeGain = g;
    }
}

TERMINAL_COMMAND(alt, "Altitude gain")
{
    float g;
    if (argc) {
        g = atof(argv[0]);
        terminal_io()->println("Fixed altitude gain");
        altitudeGain = g;
    }
}

TERMINAL_COMMAND(back, "Back gain")
{
    float g;
    if (argc) {
        g = atof(argv[0]);
        terminal_io()->println("Fixed back gain");
        backGain = g;
    }
}

TERMINAL_COMMAND(dir, "Direction")
{
    float g;
    if (argc) {
        g = atof(argv[0]);
        terminal_io()->println("Fixed direction");
		direction = g;
        if (g > 0) {
            leftGain = 1.0 - g;
            rightGain = 1.0;
        } else {
            g = -g;
            leftGain = 1.0;
            rightGain = 1.0 - g;
        }
    }
}

TERMINAL_COMMAND(balance, "Balance")
{
    float g;
    if (argc) {
        g = atof(argv[0]);
        terminal_io()->println("Fixed balance");

        if (g > 0) {
            backBalance = 1.0 - g;
            frontBalance = 1.0;
        } else {
           g = -g;
            backBalance = 1.0;
            frontBalance = 1.0 - g;
        }
    }
}

TERMINAL_COMMAND(gait, "Toggle gait")
{
	terminal_io()->println("Toggling gait");

	bipod = !bipod;
	if (bipod)
    {
    	phase = 0.5f;
        phaseFR = 0.0f;
        phaseFL = 1.0f;
        phaseBR = 1.0f;
        phaseBL = 0.0f;
    }
    else
    {
    	phase = 0.25f;
    	phaseFR = 0.0f;
        phaseFL = 3.0f;
        phaseBR = 2.0f;
        phaseBL = 1.0f;
    }
}

volatile bool flag = false;

void tick()
{
    flag = true;
}

TERMINAL_COMMAND(testSpline, "Test the spline")
{
    double x;

    for (x=0; x<1.0; x+=0.01) {
        terminal_io()->print(x);
        terminal_io()->print(" -> ");
        terminal_io()->println(s1.getMod(x));
    }
}

void scheduleMove()
{
    if (!move) {
        return;
    }

    t += timeGain*0.02;

    if (t > 1.0) t -= 1.0;
    if (t < 0.0) t += 1.0;

    double s = 1.0;
    if (amplitudeGain < 0) {
        s = -1.0;
    }

    double att = 0;
    double att2 = 0;
    if (attack) {
        att = 40;
        att2 = 20;
    }

    servos_command(SERVO_FR1, att2+frontOffset+rightOffset+s*s1.getMod(t + phaseFR * phase)*altitudeGain*AMPLITUDE*amplitudeGain);
    servos_command(SERVO_BL1, backOffset+leftOffset+s*s1.getMod(t + phaseBL * phase)*altitudeGain*AMPLITUDE*amplitudeGain);
    servos_command(SERVO_BR1, backOffset+rightOffset+s*s1.getMod(t + phaseBR * phase)*altitudeGain*AMPLITUDE*amplitudeGain);
    servos_command(SERVO_FL1, frontOffset+leftOffset+s*s1.getMod(t + phaseFL * phase)*altitudeGain*AMPLITUDE*amplitudeGain);

    servos_command(SERVO_FR2, att+frontOOffset+rightGain*s2.getMod(t + phaseFR * phase)*AMPLITUDE*amplitudeGain+open);
    servos_command(SERVO_BL2, backOOffset+leftGain*s2.getMod(t + phaseBL * phase)*AMPLITUDE*amplitudeGain-open);
    servos_command(SERVO_BR2, backOOffset+rightGain*s2.getMod(t + phaseBR * phase)*AMPLITUDE*amplitudeGain-open);
    servos_command(SERVO_FL2, frontOOffset+leftGain*s2.getMod(t + phaseFL * phase)*AMPLITUDE*amplitudeGain+open);
    
    // direction
    servos_command(SERVO_FL0, direction * DIR_AMPLITUDE);
    servos_command(SERVO_FR0, direction * DIR_AMPLITUDE);

}

void setup()
{
    pinMode(6, OUTPUT);
    pinMode(BOARD_LED_PIN, OUTPUT);
    
    servos_init();

    servos_register_all();
    
    // Begining on WiFly Mode
    Serial3.begin(921600);
    terminal_init(&Serial3);
    
    // Attach the 50Hz interrupt
    servos_attach_interrupt(tick);

    // First spline: /\_________
    s1.addPoint(0.0, 0.0);
    s1.addPoint(0.1, 1.0);
    s1.addPoint(0.2, 0.0);
    s1.addPoint(1.0, 0.0);

    // Second spline: _/`--------.._
    s2.addPoint(0.0, 0.0);
    s2.addPoint(0.05, 0.0);
    s2.addPoint(0.15, 1.0);
    s2.addPoint(1.0, 0.0);
}

void loop()
{
    terminal_tick();

    // If something is available on USB, switching to USB
    if (SerialUSB.available() && !isUSB) {
        isUSB = true;
        terminal_init(&SerialUSB);
    }

    if (flag) {
        scheduleMove();
        flag = false;
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

