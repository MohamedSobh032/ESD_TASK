#define  F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "STD_Macros.h"
#include "UART.h"
#include "ADC.h"
#include "Timer0.h"
#include "Timer2.h"
#include "Interrupt.h"
#include "Watchdog.h"


int main(void)
{
	// De Initialize Watchdog Timer
	WDT_OFF();
	//Initially Write Normal on EEPROM
	eeprom_update_byte(( uint8_t *) 64, 'N');
	// This is the bit that will be used to control the interrupt of the MCU2
	SETBIT(DDRD,6);
    // Initialize UART to communicate with the MCU2
    UART_INIT(12);
    //Initialize Interrupt that will control if the Machine is on or off
    INT1_INIT();
	// Initialize the PWM (of timer0) to Control Fan
	TIMER0_FPWM_INIT();
	// Initialize ADC that will read from potentiometer
	ADC_INIT();
	int i = 0;
	for (i = 0; i < 150; i++)
	{ ActualTemp = (500.0 * ADC_READ(0)) / 1024.0; }		// To not count on useless measurement
	
	while (1) 
    {
		if ((eeprom_read_byte((const uint8_t*)64)) == 'N')
		{
			ActualTemp = (500.0 * ADC_READ(0)) / 1024.0;		// Calculate the Temperature
			UART_SendInteger(ActualTemp);						// Send temperature to MCU2
			if (ActualTemp < 20)								// If temperature less than 20, turn off the fan
			{ Change_DC(0.0); }
			else if (ActualTemp <= 40)							// depending on temperature, control the speed of the fan
			{ Change_DC( ((float)(ActualTemp-20)) * 0.05 ); }
			else
			{
				Change_DC(1);									// If the temperature is higher than 40, max speed the fan
				if (ActualTemp > 50)							// If the temperature is 50, start emergency state
				{
					Timer2_INIT(500);							// The timer interrupt is set to 500 ms
					// Write Emergency on EEPROM
					while(EmergFlag == 0){;}					// delay the whole system, until the flag is up
					if (Emerg == 1)								// if emergency = 1, it means, that the flag was up because the timer has count 7 seconds
					{
						eeprom_update_byte(( uint8_t *) 64, 'A');			// Write Abnormal on EEPROM
						// De initialize timer 2
						CLEARBIT(TCCR2,CS02);
						CLEARBIT(TCCR2,CS01);
						CLEARBIT(TCCR2,CS00);
						// Clear flags
						EmergFlag = 0;
						Emerg = 0;
						WDT_ON();											// Initialize Watchdog timer with the lowest time
						while(1){;}											// so the system can reset
					}											// if it was up because temp became lower than 50, do nothing
					// De initialize timer 2
					CLEARBIT(TCCR2,CS02);
					CLEARBIT(TCCR2,CS01);
					CLEARBIT(TCCR2,CS00);
					// Clear flags
					EmergFlag = 0;
					Emerg = 0;
				}
			}
		}
		else if ((eeprom_read_byte((const uint8_t*)64)) == 'A')
		{ 
			/* Do Nothing */
			Change_DC(0.0);
			WDT_ON();
			while(1){;}
		}
    }
}

