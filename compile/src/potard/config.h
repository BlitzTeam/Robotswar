#ifndef CONFIG_H
#define CONFIG_H

#include <avr/io.h>

/**
 * Port and pin to blink
 */
#define LED_PORT PORTD
#define LED_DDR  DDRD
#define LED_PIN  PD2

#endif // CONFIG_H
