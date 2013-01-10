#include <stdlib.h>
#include <wirish/wirish.h>
#include "./libraries/Servo/Servo.h"

char* buf;
char* buf2;
int i;
int duty;
int chan;
Servo servo1;
Servo servo2;

void setup() {
    pinMode(26, PWM);
    pinMode(27, PWM);
    buf = (char*)malloc(8);
    buf2 = (char*)malloc(2);
    servo1.attach(27);
	servo2.attach(26);
	servo1.write(90);
	servo2.write(90);
}

void loop() {
	i = 0;
	do
	{
		buf[i] = SerialUSB.read();
		SerialUSB.write(buf[i]);
		i++;
 	}
 	while(buf[i-1] != 13);
 	SerialUSB.println();
	buf[i-1]='\0';
	buf2[0] = buf[0];
	buf2[1] = '\0';
	chan = atoi(buf2);
	duty = atoi(buf+2);
	if(chan == 1)
		servo1.write(duty);
	if(chan == 2)
		servo2.write(duty);
	SerialUSB.print("Angle of motor ");
	SerialUSB.print(chan);
	SerialUSB.print(" set to ");
	SerialUSB.print(duty);
	SerialUSB.println(" !");
}

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }
	free(buf);
	free(buf2);
    return 0;
}
