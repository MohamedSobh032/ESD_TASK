/*
 * LCD.h
 *
 * Created: 4/14/2023 3:51:47 PM
 *  Author: Mohamed
 */ 


#ifndef LCD_H_
#define LCD_H_


void LCD_send_command(char cmd);
void LCD_send_data(char cmd);

void LCD_INIT();

void LCD_String(char arr[]);
void LCD_Integer(int x);
void LCD_ClearScreen();


#define EN_PIN 4

#endif /* LCD_H_ */