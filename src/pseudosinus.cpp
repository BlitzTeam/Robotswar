#include <stdlib.h>
#include <wirish/wirish.h>

int servo = 27;
int i;
int supahcounter;
int dir;
HardwareTimer timer(1);
int duty;

void setup() {
	timer.setPrescaleFactor(24);
	timer.setOverflow(60000);
	timer.refresh();
	timer.resume();
    pinMode(servo, PWM);
    supahcounter = 2100;
    dir = 100;
}
void loop() {
	supahcounter += dir;
	if(supahcounter == 2000 || supahcounter == 7300)
		dir *= -1;
	timer.setCompare(1, supahcounter);
	delay(50);
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
