#include <stdio.h>
#include <string.h>
#include "uart0.h"
#include "timer.h"
#include "board.h"
#include "ymodemApi.h"
#include "config.h"

#define FIO2DIR                 (*(volatile unsigned long *)0x2009c040)
#define FIO2SET                 (*(volatile unsigned long *)0x2009c058)
#define FIO2CLR                 (*(volatile unsigned long *)0x2009c05c)



int main(void)
{
	uint8 ch,res;
	uint32 i = 3;

	NVIC->ICER[0] = 0xFFFFFFFF;
	NVIC->ICER[1] = 0xFFFFFFFF;
	NVIC->ICER[2] = 0xFFFFFFFF;
	NVIC->ICER[3] = 0xFFFFFFFF;
	NVIC->ICER[4] = 0xFFFFFFFF;
	NVIC->ICER[5] = 0xFFFFFFFF;
	NVIC->ICER[6] = 0xFFFFFFFF;
	NVIC->ICER[7] = 0xFFFFFFFF;
	
	
	LPC_systemInit();
	uart0_init(115200);
	timer_init( DEV_TIMER_0, FPCLK/100 ); // FPCLK/1000 10ms¶¨Ê±Æ÷  FPCLK = 24000000
	__enable_irq();
	
	FIO2DIR |= (7 << 5);

	
	while(1){
		FIO2SET |= (7 << 5);
		delayMs(500);
		FIO2CLR |= (7 << 5);
		delayMs(500);
		res = uart_download();
		if(res == 1)
		{
			uart0_putStr("\r\n\r\n Programming Completed Successfully!\r\n",
				sizeof("\r\n\r\n Programming Completed Successfully!\r\n"));
			ReturnNameAndLength();
			IAP_execute_user_code();
		}
		else{
			uart0_putStr("IAP Error...\r\n",sizeof("IAP Error...\r\n"));
		}

		
	}
	return 0;
}
