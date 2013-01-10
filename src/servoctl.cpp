#include <stdlib.h>
#include <wirish/wirish.h>

int servo = 27;
int servo2 = 26;
char* buf;
char* buf2;
int i;
HardwareTimer timer(1);
int duty;
int chan;

void setup() {
	timer.setPrescaleFactor(24);
	timer.setOverflow(60000);
	timer.refresh();
	timer.resume();
    pinMode(servo, PWM);
    pinMode(servo2, PWM);
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
		timer.setCompare(chan, duty);
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

    return 0;
}
