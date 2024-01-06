/*
 * Interrupt.c
 *
 * Created: 5/5/2023 4:11:10 PM
 *  Author: Mohamed
 */ 
#define F_CPU 1000000ul
#include <avr/io.h>
#include "STD_Macros.h"
#include "Timer0.h"
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int ActualTemp = 0;

void INT0_INIT()
{
	SETBIT(MCUCR,ISC01);	//Condition - gebnah mel datasheet - falling edge
	sei();					//Enabling the Global Interrupt
	SETBIT(GICR,INT0);		//Enable Interrupt 0
	CLEARBIT(DDRD,2);
}

ISR(INT0_vect)
{
	//
}

void INT1_INIT()
{
	SETBIT(MCUCR,ISC11);
	SETBIT(MCUCR,ISC10);
	sei();
	SETBIT(GICR,INT1);
	CLEARBIT(DDRD,3);
}

ISR(INT1_vect)
{
	SETBIT(PORTD,6);
	_delay_ms(100);
	CLEARBIT(PORTD,6);
}