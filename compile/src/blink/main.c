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

long counter = 0;

ISR(TIMER1_COMPA_vect)
{
    counter++;

    if (counter%500 == 0) {
        LED_PORT ^= _BV(LED_PIN);

    }
}

int main (void)
{
    cli();
 
    uart_init(UART_BAUD_SELECT_DOUBLE_SPEED(115200, F_CPU));   
    // 1000 Hz
    TCCR1A = 0;
    TCCR1B = _BV(CS10) | _BV(CS11) | _BV(WGM12);
    OCR1AH = 0;
    OCR1AL = 249;
    TIMSK1 |= _BV(OCIE1A);

    LED_DDR |= _BV(LED_PIN);

    sei();

    while (1) {
        _delay_ms(500);
printf("Coucou!\r\n");
    }
}
