#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <uart/uart.h>
#include "config.h"
#include <math.h>


#define MAX_STRING 50

int mini(int a, int b)
{
  return a > b ? b : a;
}

void getStringFromSerie(unsigned char * cha)
{
  int receive;
  int i=0; 
  while((receive = uart_getc()) != UART_NO_DATA)
    {
      
      int mess = receive;
      /*mess >>=
      if(mess > UART_BUFFER_OVERFLOW)
	break;
      */
      cha[i]= receive;
      i++;
    }
  cha[i] = '\0';
}

void getByteFromSerie(unsigned char &c)
{
	while((c = uart_getc()) == UART_NO_DATA);
	c %= 256;
} 

void loop()
{
  char tmp[MAX_STRING];
  getByteFromSerie(tmp);
  //if(tmp == "test") 
	printf("%c\r\n",tmp);
}

int main (void)
{
    cli();
    uart_init(UART_BAUD_SELECT_DOUBLE_SPEED(115200, F_CPU)); //initialisation com serie   
    sei();

    while (1) {
      loop();
    }
}
