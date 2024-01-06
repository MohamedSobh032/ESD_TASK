/*
 * Timer.c
 *
 * Created: 5/12/2023 3:23:29 PM
 *  Author: Mohamed
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "Timer0.h"



void TIMER0_FPWM_INIT()
{
	SETBIT(TCCR0,WGM00);
	SETBIT(TCCR0,WGM01);
	SETBIT(TCCR0,COM01);	//nin-inverting
	SETBIT(TCCR0,CS00);		//PS 1
	SETBIT(DDRB,3);
}


void Change_DC(float DC)
{
	int temp = (int)(255.0 * DC) ;
	OCR0 = temp;
}

