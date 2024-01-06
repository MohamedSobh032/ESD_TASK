#define  F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "UART.h"
#include "ADC.h"
#include "Timer0.h"
#include "Timer2.h"
#include "Interrupt.h"

int main(void)
{
	// Initialize UART to communicate with the MCU1
	UART_INIT(12);			
	//Initialize Interrupt that will control if the motor is on or off
	INT1_INIT();
	// Initialize LEDs, Servo and Buzzer
	DDRC |= 0x8f;
	CLEARBIT(PORTC,7);
	// Initialize the PWM (of timer0) to Control Motor 
	TIMER0_FPWM_INIT();
	// Initialize ADC that will read from potentiometer
	ADC_INIT();
    while (1) 
    {
		// if the push button was not clicked, run the machine normally, else stop it
		if (SpeedControl == 1)
		{
			speed = (float)(ADC_READ(0))/1024.0;
			Change_DC(speed);
		}
		else if (SpeedControl == 0)
		{ Change_DC(0.0); }
		// TEMPERATURE PART
		ActualTemp = UART_GetInteger();					// Read temperature from UART
		if (ActualTemp < 20)
		{
			// light up green
			PORTC = 0x01 | (PORTC & 0xf0);
		}
		else if(ActualTemp <= 40)
		{
			// light up yellow
			PORTC = 0x02 | (PORTC & 0xf0);
		}
		else 
		{
			// light up red
			PORTC = 0x04 | (PORTC & 0xf0);
			// if temperature is greater than 50, start emergency state
			if (ActualTemp > 50)
			{
				// light up red and buzzer
				PORTC = 0x0c | (PORTC & 0xf0);
				Timer2_INIT(500);						// The timer interrupt is set to 500 ms
				while(EmergFlag == 0){;}				// delay the whole system, until the flag is up
				if (Emerg == 1)							// if emergency = 1, it means, that the flag was up because the timer has count 7 seconds
				{
					// Turn off the machine for 5 seconds
					Change_DC(0.0);
					
					_delay_ms(5000);
					
					// after the 5 seconds end, set the servo back to 0 degrees
					SETBIT(PORTC,7);
					_delay_us(1000);
					CLEARBIT(PORTC,7);
				}										// if it was up because temp became lower than 50, do nothing
				// De initialize timer 2
				CLEARBIT(TCCR2,CS02);
				CLEARBIT(TCCR2,CS01);
				CLEARBIT(TCCR2,CS00);
				EmergFlag = 0;
				Emerg = 0;
			}
		}
    }
}

