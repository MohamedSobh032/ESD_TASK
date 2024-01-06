/*
 * UART.c
 *
 * Created: 5/20/2023 3:09:52 PM
 *  Author: Mohamed
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include "STD_Macros.h"
#include "UART.h"


void UART_INIT(char boderate)
{
	UBRRH = (char)(boderate >>8) ;
	UBRRL = (char) boderate ;
	UCSRB=UCSRB | (1<<RXEN);
	UCSRB=UCSRB | (1<<TXEN);
	UCSRC = (1<<URSEL) |(1<<UCSZ0)|(1<<UCSZ1);
	CLEARBIT(DDRD,0);
	SETBIT(DDRD,1);
}

char UART_RX()
{
	while(READBIT(UCSRA,RXC)==0);
	return UDR;
}

void UART_TX(char T)
{
	while(READBIT(UCSRA,UDRE)==0);
	UDR = T;
	while(READBIT(UCSRA,TXC)==0);
}


int UART_GetInteger()
{
	char arr[4];
	int i = 0;
	int ret = 0;
	arr[i] = UART_RX();
	while (arr[i] != '\n' && arr[i] != '\r')
	{
		if (arr[i] >= '0' && arr[i] <= '9')
		{
			arr[i] = arr[i] - '0';
			ret = (ret*10) + arr[i];
		}
		i++;
		arr[i] = UART_RX();
	}
	return ret;
	
}

void UART_SendString(char arr[])
{
	int c = 0;
	while(arr[c] != 0)
	{
		UART_TX(arr[c]);
		c++;
	}
}

void UART_GetString(char arr[])  //Receive a character until carriage return or newline
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		arr[i] = '\0';
	}
	i = 0;
	arr[i] = UART_RX();
	while (arr[i] != '\n' && arr[i] != '\r')
	{
		i++;
		arr[i] = UART_RX();
	}
	arr[i] = '\0';
}



