/*
 * Watchdog.c
 *
 * Created: 8/31/2023 8:35:46 AM
 *  Author: Mohamed
 */ 
#define  F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "Watchdog.h"

void WDT_ON()
{
	/*
	Watchdog timer enables with typical timeout period 2.1 
	second.
	*/
	SETBIT(WDTCR,WDE);
	CLEARBIT(WDTCR,WDP0);
	CLEARBIT(WDTCR,WDP1);
	CLEARBIT(WDTCR,WDP2);
}

void WDT_OFF()
{
	/*
	This function use for disable the watchdog timer.
	*/
	WDTCR = (1<<WDTOE)|(1<<WDE);
	WDTCR = 0x00;
}