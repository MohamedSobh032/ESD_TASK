/*
 * IncFile1.h
 *
 * Created: 5/20/2023 3:08:29 PM
 *  Author: Mohamed
 */ 


#ifndef UART_H_
#define UART_H_



void UART_INIT(char boderate);
char UART_RX();
void UART_TX(char T);
int UART_GetInteger();
void UART_SendString(char arr[10]);
void UART_GetString(char arr[10]);

#endif /* UART_H_ */