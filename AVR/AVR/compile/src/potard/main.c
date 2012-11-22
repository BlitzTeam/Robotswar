#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <uart/uart.h>
#include "config.h"
#include <adc/adc.h>
#include <servo/servo.h>
#include <math.h>

int counter = 0;
int loop_counter = 0;

ISR(TIMER1_COMPA_vect)
{
  //counter++;

  //if (counter%500 == 0) {
      //LED_PORT ^= _BV(LED_PIN);

  //}
}

int mini(int a, int b)
{
  return a > b ? b : a;
}

void loop()
{
  //30k to 80k entre 3/4 et 8/9 voltage
  //if(loop_counter % 1000 == 0)
  //cValues[0]
  servo_set_duty(mini(adcValues[0]*4, 4000) + 4 );  
  counter += 1;
  //loop_counter += 1;
  _delay_ms(1);
  char *tmp;
  scanf("%s",&tmp);
  printf("%s",tmp);
  //printf("%d",adcValues[0]);
}

int main (void)
{
    cli();
    adc_run(1);//echantilloneur analogue (tableau qui contient les valeurs)
    uart_init(UART_BAUD_SELECT_DOUBLE_SPEED(115200, F_CPU)); //initialisation com serie   
    // 1000 Hz
    //TCCR1A = 0;
    //TCCR1B = _BV(CS10) | _BV(CS11) | _BV(WGM12);
    //OCR1AH = 0;
    //OCR1AL = 249;
    //TIMSK1 |= _BV(OCIE1A);
    servo_enable();//Active le servo (pin 9 par defaut, voir les sortie dans fichiers servo.c)
    servo_set_duty(2000);
    // LED_DDR |= _BV(LED_PIN);

    sei();

    while (1) {
      loop();
    }
}
