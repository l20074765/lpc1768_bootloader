/*==========================================================================
##                   LPC-bootloader
##
##              Copyright(c) 2015-2016 Yoc All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      start.c lpc1768Æô¶¯ÎÄ¼ş
##
##--------------------------------------------------------------------------
##
##  Created by	:	Yoc 
##			QQ	:	1760668483
##        Date	:	2015.04.29
##==========================================================================*/


extern void LPC_start(void);
extern void UART0_IRQHandler (void);
extern void TIMER0_IRQHandler(void);




void _start(void);
void default_isr(void);




extern char _mem_stack_base, _mem_stack_end;
extern char _data_lma_start;
extern char _data_start;
extern char _data_end;
extern char _bss_start;
extern char _bss_end;


/*
 * Control IRQs
 */
static inline void __attribute__((used)) __enable_irq(void)
{
	asm volatile ("cpsie i");
}

static inline void __attribute__((used)) __disable_irq(void)
{
	asm volatile ("cpsid i");
}


unsigned int vectors[] __attribute__((section(".vectors"))) = {

	(unsigned int)&_mem_stack_end,	//Top of Stack
	(unsigned int)&_start,			//Reset Handler
	(unsigned int)&default_isr,		//NMI Handler
	(unsigned int)&default_isr,		//Hard Fault Handler
	(unsigned int)&default_isr,		//MPU Fault Handler
	(unsigned int)&default_isr,		//Bus Fault Handler
	(unsigned int)&default_isr,		//Usage Fault Handler
	(unsigned int)&default_isr,		//Reserved
	(unsigned int)&default_isr,		//Reserved
	(unsigned int)&default_isr,		//Reserved
	(unsigned int)&default_isr,		//Reserved
	(unsigned int)&default_isr,		//SVCall Handler
	(unsigned int)&default_isr,		//Debug Monitor Handler
	(unsigned int)&default_isr,		//Reserved
	(unsigned int)&default_isr,		//PendSV Handler
	(unsigned int)&default_isr,		//SysTick Handler
	
	//External Interrupts
	(unsigned int)&default_isr,		//16: Watchdog Timer
	(unsigned int)&TIMER0_IRQHandler,//17: Timer0
	(unsigned int)&default_isr,		//18: Timer1
	(unsigned int)&default_isr,		//19: Timer2
	(unsigned int)&default_isr,		//20: Timer3
	(unsigned int)&UART0_IRQHandler,	//21: UART0
	(unsigned int)&default_isr,		//22: UART1
	(unsigned int)&default_isr,		//23: UART2
	(unsigned int)&default_isr,		//24: UART3
	(unsigned int)&default_isr,		//25: PWM1
	(unsigned int)&default_isr,		//26: I2C0
	(unsigned int)&default_isr,		//27: I2C1
	(unsigned int)&default_isr,		//28: I2C2
	(unsigned int)&default_isr,		//29: SPI
	(unsigned int)&default_isr,		//30: SSP0
	(unsigned int)&default_isr,		//31: SSP1
	(unsigned int)&default_isr,		//32: PLL0 Lock (Main PLL)
	(unsigned int)&default_isr,		//33: Real Time Clock
	(unsigned int)&default_isr,		//34: External Interrupt 0
	(unsigned int)&default_isr,		//35: External Interrupt 1
	(unsigned int)&default_isr,		//36: External Interrupt 2
	(unsigned int)&default_isr,		//37: External Interrupt 3
	(unsigned int)&default_isr,		//38: A/D Converter
	(unsigned int)&default_isr,		//39: Brown-Out Detect
	(unsigned int)&default_isr,		//40: USB
	(unsigned int)&default_isr,		//41: CAN
	(unsigned int)&default_isr,		//42: General Purpose DMA
	(unsigned int)&default_isr,		//43: I2S
	(unsigned int)&default_isr,		//44: Ethernet
	(unsigned int)&default_isr,		//45: Repetitive Interrupt Timer
	(unsigned int)&default_isr,		//46: Motor Control PWM
	(unsigned int)&default_isr,		//47: Quadrature Encoder Interface
	(unsigned int)&default_isr,		//48: PLL1 Lock (USB PLL)
	(unsigned int)&default_isr,		//49: USB Activity interrupt to wakeup
	(unsigned int)&default_isr		//50: CAN Activity interrupt to wakeup
	
};


 /*
  * Reset entry point
  */
void _start(void)
{
	unsigned int i,len;
	char *src = &_data_lma_start;
	char *dst = &_data_start;
	__disable_irq();

	//Copy data and initialize BSS
	len = &_data_end - &_data_start;
	for(i = 0;i < len;i++){
		*dst++ = *src++;
	}
	
	len = &_bss_end - &_bss_start;
	dst = &_bss_start;
	for(i = 0;i < len;i++){
		*dst++ = 0;
	}
	
	__enable_irq();
	LPC_start();
	

}



void __attribute__((naked, noreturn)) default_isr(void);
void default_isr(void)
{
	for (;;);
	
}
