#include <stdlib.h>
#include <wirish/wirish.h>

typedef struct
{
	int pinid;
	int chan;
	HardwareTimer* timer;
}t_motor;

char* buf;
char* buf2;
int i;
HardwareTimer timer1(1);
int duty;
int chan;
t_motor servo, servo2;
servo.pinid = 27;
servo.chan = 1;
servo.timer = &timer1;
servo2.pinid = 26;
servo2.chan = 2;
servo2.timer = &timer1;

void setup() {
	timer1.setPrescaleFactor(24);
	timer1.setOverflow(60000);
	timer1.refresh();
	timer1.resume();
    pinMode(servo.pinid, PWM);
    pinMode(servo2.pinid, PWM);
    buf = (char*)malloc(8);
    buf2 = (char*)malloc(2);
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
	if(duty != -1)
	{
		duty *= 0.52;
		duty += 2000;
	}
	else
		duty = 0;
	if((duty < 2000 && duty) || duty > 7200)
	{
		SerialUSB.print("Value ");
		SerialUSB.print(duty);
		SerialUSB.println(" out of bounds !");
	}
	else
	{
		timer1.setCompare(chan, duty);
		SerialUSB.print("Duty of motor ");
		SerialUSB.print(chan);
		SerialUSB.print(" set to ");
		SerialUSB.print(duty);
		SerialUSB.println(" !");
	}
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
