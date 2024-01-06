/*
 * Interrupt.h
 *
 * Created: 5/6/2023 3:10:03 PM
 *  Author: Mohamed
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void INT0_INIT();
void INT1_INIT();

extern volatile int ActualTemp;				// This is the variable that will read will save the value of the temperature on
extern volatile char SpeedControl;
extern volatile float speed;			// This variable will read the potentiometer

#endif /* INTERRUPT_H_ */