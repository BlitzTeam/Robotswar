#ifndef _MOVES_H_
#define _MOVES_H_

#include <servos.h>
#include <spline.h>

#define SERVO_ARG 0
#define SERVO_ARD 1
#define SERVO_PTD 2
#define SERVO_AVD 3
#define SERVO_PTG 4
#define SERVO_AVG 5
#define SECONDE 1000000


#define SPLINE_SINUS_TEMPO 2


extern char * servosNames[SERVOS_MAX_NB];

extern Spline * currentMove[SERVOS_MAX_NB]; // declare in moves.c


void plat();
void debout();
void pompes();
void pompes_avant();
void wave_droit();
void wave_gauche();
void twist();

void move_init();
void move_sinus(uint8_t index);
void move_stop();

 #endif