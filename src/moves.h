#ifndef _MOVES_H_
#define _MOVES_H_

#include <servos.h>
#include <spline.h>

#define ARG0 0	//11
#define ARG1 1	//3
#define ARD0 2	//5
#define ARD1 3	//8
#define AVG0 4	//9
#define AVG1 5	//10
#define AVG2 6	//16
#define AVD0 7	//27
#define AVD1 8	//26
#define AVD2 9	//25
#define AVD3 10	//15
#define CALE 11//4
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