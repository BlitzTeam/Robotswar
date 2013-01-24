#include <stdlib.h>
#include <wirish/wirish.h>
#include "./RobotModel/ServoController.h"

char buf[3];
char buf2[2];
int i;
int duty;
int chan;
ServoController servo[2];

void setup() {
    pinMode(15, PWM);
    pinMode(16, PWM);
    servo[0].attach(15);
	servo[1].attach(16);
	servo[0].init();
	servo[1].init();
}

void loop() {
	i = 0;
	do
	{
		buf[i] = SerialUSB.read();
		//SerialUSB.write(buf[i]);
		i++;
 	}
 	while(buf[i-1] != 13 && i <= 3); //on attend un retour chariot;
 	
 	for(int i=0;i<2;i++)
 	{
		buf2[0] = buf[i];
		servo[i].changeAngle((atoi(buf2)-1)*2);
		//SerialUSB.print("[DEF] Angle of motor ");
		//SerialUSB.print(i);
		//SerialUSB.print("set to");
		//SerialUSB.print(atoi(buf2));
		
	}
	
	//SerialUSB.print("Angle of motor ");

 	
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
