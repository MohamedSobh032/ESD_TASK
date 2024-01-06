
#define  F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include "STD_Macros.h"
#include "UART.h"
#include "Interrupt.h"

#include "Timer2.h"
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
		// Read temperature from UART
		ActualTemp = UART_GetInteger();
		// if the temperature is still higher than 50
		if (ActualTemp > 50)
		{
			// keep counting 500 ms
			count_ticks++;
			// when it reaches 14 counts, it means it counted 7 seconds
			if (count_ticks == 14)
			{
				// abnormal state entered
				// Rotate the servo to 90 degrees
				SETBIT(PORTC,7);
				_delay_us(1500);
				CLEARBIT(PORTC,7);
				
				// Raise flag to 1, and set the emergency
				count_ticks = 0;
				EmergFlag = 1;
				Emerg = 1;
			}
		}
		else
		{
			// Here, if the temperature is lower than 50, leave emergency state by raising the flag and setting the emergency to 0
			EmergFlag = 1;
			Emerg = 0;
			count_ticks = 0;
		}
	}
}
