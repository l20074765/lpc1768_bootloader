#include <stdio.h>
#include <string.h>
#include "uart0.h"
#include "timer.h"
#include "board.h"


#define FIO2DIR                 (*(volatile unsigned long *)0x2009c040)
#define FIO2SET                 (*(volatile unsigned long *)0x2009c058)
#define FIO2CLR                 (*(volatile unsigned long *)0x2009c05c)


void delay(unsigned int ms)
{
	unsigned int i,j;
	for(i = 0;i < ms;i++)
		for(j = 0;j < 10000;j++);
}

int main(void)
{
	LPC_systemInit();
	uart0_init(9600);
	//timer_init( DEV_TIMER_0, FPCLK/100 ); // FPCLK/1000 10ms¶¨Ê±Æ÷  FPCLK = 24000000

	FIO2DIR |= (7 << 5);
	while(1){
		FIO2SET |= (7 << 5);
		delay(100);
		FIO2CLR |= (7 << 5);
		delay(100);
		uart0_putStr("Hello yoc....\r\n",sizeof("Hello yoc....\r\n"));
	}
	return 0;
}
