#include "wdt.h"
#include "config.h"

volatile uint32 wdt_counter;

/*****************************************************************************
** Function name:		WDTHandler
**
** Descriptions:		Watchdog timer interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void WDT_IRQHandler(void) 
{
  LPC_WDT -> WDMOD &= ~WDTOF;		/* clear the time-out terrupt flag */		  
   
  wdt_counter++;
//  while(1);

}

/*****************************************************************************
** Function name:		WDTInit
**
** Descriptions:		Initialize watchdog timer, install the
**				watchdog timer interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the VIC table
**				is full and WDT interrupt handler can be
**				installed.
** 
*****************************************************************************/
uint32 WDT_init( void )
{

  wdt_counter = 0;

  NVIC_EnableIRQ(WDT_IRQn);

  LPC_WDT -> WDTC = WDT_FEED_VALUE;	/* once WDEN is set, the WDT will start after feeding */

  LPC_WDT -> WDMOD = WDEN | WDRESET;

  LPC_WDT -> WDFEED = 0xAA;		/* Feeding sequence */
  LPC_WDT -> WDFEED = 0x55;    
  return( 1 );
}

/*****************************************************************************
** Function name:		WDTFeed
**
** Descriptions:		Feed watchdog timer to prevent it from timeout
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void WDT_feed( void )
{
	__disable_irq();
  	LPC_WDT -> WDFEED = 0xAA;		/* Feeding sequence */
  	LPC_WDT -> WDFEED = 0x55;
  	__enable_irq();
  	return;
}