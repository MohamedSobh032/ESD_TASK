/*
 * Timer2.h
 *
 * Created: 5/19/2023 3:57:57 PM
 *  Author: Abd-Allah Ahmad Aref
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_

#define PS_2 8
#define CTC 200

#define NOVF(x) (((unsigned long long)x)*F_CPU*10ul)/(256*1ul*((unsigned long long)PS_2)*1000ul)
#define PRELOAD_t2(x) ((10-x)*256)/10
#define NOVFCTC(x) (((unsigned long long)x)*F_CPU*10ul)/(CTC*1ul*((unsigned long long)PS_2)*1000ul)
extern volatile int count_t2;
extern volatile int MaxCount_t2;
extern volatile int Preload_t2;
extern volatile char EmergFlag;
extern volatile char Emerg;
 
void Timer2_INIT(int DesiredT); //NORMAL MODE INTIALIZATION
void Timer0CTC_INIT(int DesiredT);



#endif /* TIMER2_H_ */