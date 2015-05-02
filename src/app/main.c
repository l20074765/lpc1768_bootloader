#include <stdio.h>
#include <string.h>
#include "uart0.h"


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
	FIO2DIR |= (7 << 5);
	while(1){
		FIO2SET |= (7 << 5);
		delay(100);
		FIO2CLR |= (7 << 5);
		delay(100);
		uart0_putStr("Hello....\r\n",sizeof("Hello....\r\n"));
	}
	return 0;
}
