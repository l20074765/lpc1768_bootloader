#include "led.h"
#include "config.h"



void LED_ctrl(uint8 no,uint8 s)
{
	LPC_GPIO2->FIODIR |= (0x01UL << no);
	if(s == LED_ON)
		LPC_GPIO2->FIOSET |= (0x01UL << no);
	else
		LPC_GPIO2->FIOCLR |= (0x01UL << no);
	
}


