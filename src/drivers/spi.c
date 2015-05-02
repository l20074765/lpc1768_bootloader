#include "spi.h"
#include "config.h"


void spi_init (void)
{
	LPC_SC->PCONP        |= (1 << 8);              	/* Enable power to SPI block  */
}


