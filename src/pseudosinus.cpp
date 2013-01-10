#include <stdlib.h>
#include <wirish/wirish.h>
#include "./libraries/Servo/Servo.h"


int i;
int supahcounter;
int dir;
int duty;
Servo servo1;
Servo servo2;

void setup() {
	pinMode(26, PWM);
    pinMode(27, PWM);
    servo1.attach(27);
	servo2.attach(26);
	supahcounter = 1;
	dir = 1;
	}
void loop() {
	supahcounter += dir;
	if(supahcounter == 0 || supahcounter == 180)
		dir *= -1;
	servo1.write(supahcounter);
	servo2.write(180-supahcounter);
	delay(10);
}

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
