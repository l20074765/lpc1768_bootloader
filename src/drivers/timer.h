#ifndef _TIMER_H_
#define _TIMER_H_
#include "common.h"


#define 	DEV_TIMER_0  	0          //Timer 0
#define  	DEV_TIMER_1		1      		//Timer 1

typedef struct{
  uint8          invoke;                 //是否执行回调
  uint32         counter;
  void            (*callback)( void );
}DEV_Timer_t;

extern DEV_Timer_t DEV_Timer0, DEV_Timer1;


uint32 timer_init(uint8 timerId, uint32 TimerInterval ) ;
void delayMs(uint32 delayInMs);

#endif
