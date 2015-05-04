#include "timer.h"
#include "config.h"
#include "board.h"

DEV_Timer_t DEV_Timer0 = {0,0,(void *)0};
DEV_Timer_t DEV_Timer1 = {0,0,(void *)0};


/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
//uint8_t iic_buf[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//uint8_t iic_rdbuf[20] = "";
void TIMER0_IRQHandler (void) 
{  
//  uint8_t ret;
  


  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  //timer0_counter++;
//  iic_buf[0] = 	DEV_Timer0.Counter;
//
//  if( DEV_Timer0.Counter % 4 == 0 )
//  {
//   ret = I2C_WriteNByte(0xA0, 1, 0x00, iic_buf, 8);
//   Debug_Printf("IICW:ret:%d\r\n",ret);
//  }else if( DEV_Timer0.Counter % 2 == 0 ) {
//   ret =   I2C_ReadNByte( 0xA0, 1, 0x00, iic_rdbuf, 8);
//
//	Debug_Printf("IICR:ret:%d %s\r\n",ret, iic_rdbuf);
//  }
  DEV_Timer0.counter ++;

  DEV_Timer0.invoke = 1;

 

  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER1_IRQHandler (void)  
{  
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
 
  DEV_Timer1.counter ++;
  // Debug_Printf("TIMER1 IRQ:%d\r\n", timer1_counter);
 
  DEV_Timer1.invoke = 1;
  return;
}

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void enable_timer( uint8 timerId )
{

  switch( timerId )
  {
   	case DEV_TIMER_0:
	{
  	  LPC_TIM0->TCR = 1;
	  break;
	}
	case DEV_TIMER_1:
	{
	   LPC_TIM1->TCR = 1;
	   break;
	}
  }

  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void disable_timer( uint8 timerId )
{
  switch( timerId )
  {
   	case DEV_TIMER_0:
	{
  	  LPC_TIM0->TCR = 0;
	  break;
	}
	case DEV_TIMER_1:
	{
	   LPC_TIM1->TCR = 0;
	   break;
	}
  }
  return;
}


uint32 timer_init(uint8 timerId, uint32 TimerInterval ) 
{
 	uint8 res = 0;
	switch( timerId ){
		case DEV_TIMER_0:{
			LPC_SC->PCONP  |= (0x01 << 1); //enable timer0 power      
			DEV_Timer0.counter = 0;
			LPC_TIM0->MR0 = TimerInterval;
			LPC_TIM0->MCR = 3;				
			NVIC_EnableIRQ(TIMER0_IRQn);
			LPC_TIM0->TCR  = 0x01;
			res = 1;
		}
		case DEV_TIMER_1:{
			LPC_SC->PCONP  |= (0x01 << 2); //enable timer1 power      
			DEV_Timer1.counter = 0;
			LPC_TIM1->MR0 = TimerInterval;
			LPC_TIM1->MCR = 3;				
			NVIC_EnableIRQ(TIMER1_IRQn);
			LPC_TIM1->TCR = 0x01;
			res = 1;
		}
		default:break;
	}
	
	return res;
}



/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**						until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void delayMs(uint32 delayInMs)
{
  	uint32 t;
	if(delayInMs <= 10){
		t = (FPCLK / 100-1);
	}
	else{
		t = delayInMs * (FPCLK / 100-1) / 10;
	}
	LPC_TIM1->TCR = 0x02;		/* reset timer */
	LPC_TIM1->PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM1->MR0 =	t;
	LPC_TIM1->IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM1->MCR = 0x04;		/* stop timer on match */
	LPC_TIM1->TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (LPC_TIM1->TCR & 0x01);
	return;

}



