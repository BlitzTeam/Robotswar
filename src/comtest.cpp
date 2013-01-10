#include <stdlib.h>
#include <wirish/wirish.h>

unsigned char * buf;
int nb;

void setup() {
    /* Set up the LED to blink  */
    pinMode(20, OUTPUT);
    //SerialUSB.begin();
}

void loop() {
	while(!SerialUSB.available());
	nb = SerialUSB.available();
	buf = (unsigned char*)malloc(nb * sizeof(unsigned char));
	int i = nb;
	for(; nb > 0; nb--)
		buf[i-nb] = SerialUSB.read();
	buf[i]='\0';
	for(; nb < i; nb++)	
	{
		if(buf[nb] == 13 )
			SerialUSB.println();
		else
			SerialUSB.write((buf[nb]+8)%255);
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
