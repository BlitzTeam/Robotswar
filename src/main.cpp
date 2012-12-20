#include <stdlib.h>
#include <wirish/wirish.h>

int servo = 25;
char * buf;
int i;
unsigned int duty;

void setup() {
    pinMode(servo, PWM);
    buf = (char*)malloc(8);
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
	duty = atoi(buf);
	if(duty < 0 || duty > 65535)
	{
		SerialUSB.print("Value ");
		SerialUSB.print(duty);
		SerialUSB.println(" out of bounds !");
	}
	else
	{
		pwmWrite(servo, duty);
		SerialUSB.print("Duty set to ");
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
