
#define  F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include "STD_Macros.h"
#include "ADC.h"
#include "Interrupt.h"
#include "Timer2.h"
#include "UART.h"
#include <util/delay.h>
int count_ticks = 0;
volatile int count_t2=0;
volatile int MaxCount_t2=0;
volatile int Preload_t2=0;
volatile char EmergFlag = 0;
volatile char Emerg = 1;

void Timer2_INIT(int DesiredT)
{
	SETBIT(TCCR2,CS01);
	SETBIT(TIMSK,TOIE2);
	sei(); //global interrupt enable
	int cal=NOVF(DesiredT);
	Preload_t2=PRELOAD_t2(cal);
	MaxCount_t2=cal/10;
}

ISR(TIMER2_OVF_vect)
{
	count_t2++;
	if (count_t2 >= MaxCount_t2)
	{
		//Counting 500 ms
		count_t2 = 0;
		ActualTemp = (500.0 * ADC_READ(0)) / 1024.0;
		UART_SendInteger(ActualTemp);
		// if the temperature is still higher than 50
		if (ActualTemp > 50)
		{
			// keep counting 500 ms
			count_ticks++;
			// when it reaches 14 counts, it means it counted 7 seconds
			if (count_ticks == 14)
			{
				// raise the flag to leave emergency state, and set the emergency to be equal to 1
				// so it can go in the main to the abnormal state
				count_ticks = 0;
				EmergFlag = 1;
				Emerg = 1;
			}
		}
		else
		{
			// Here, if the temperature is lower than 50, leave emergency state by raising the flag and setting the emergency to 0
			count_ticks = 0;
			EmergFlag = 1;
			Emerg = 0;
		}
	}
}
