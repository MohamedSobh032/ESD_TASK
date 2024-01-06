/*
 * ADC.c
 *
 * Created: 5/6/2023 3:16:35 PM
 *  Author: Mohamed
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include "STD_Macros.h"
#include "ADC.h"
#include <util/delay.h>

void ADC_INIT()
{
	SETBIT(ADMUX,REFS0);
	SETBIT(ADCSRA,ADEN);
	SETBIT(ADCSRA,ADPS2);
	SETBIT(ADCSRA,ADPS1);
	SETBIT(ADCSRA,ADPS0);
}

int ADC_READ(int channel)
{
	if (channel < 8)
	{
		ADMUX = channel | (ADMUX & 0xE0);
		SETBIT(ADCSRA,ADSC);
		while (READBIT(ADCSRA,ADIF) == 0);
		_delay_us(10);
		return (int) ADCL + (int)ADCH * 256;
	}
}