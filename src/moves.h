#ifndef _MOVES_H_
#define _MOVES_H_

#include <servos.h>

#define SERVO_ARG 0
#define SERVO_ARD 1
#define SERVO_PTD 2
#define SERVO_AVD 3
#define SERVO_PTG 4
#define SERVO_AVG 5
#define SECONDE 100000

void plat();
void servos_command_time(uint8_t index, float pos,int timeMilliSeconds);
void debout();
void pompes();
void pompes_avant();
void wave_droit();
void wave_gauche();


 #endif