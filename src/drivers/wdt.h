#ifndef _WDT_H_
#define _WDT_H_

#include "common.h"

#define WDEN		0x00000001
#define WDRESET		0x00000002
#define WDTOF		0x00000004
#define WDINT		0x00000008

#define WDT_FEED_VALUE	0x003FFFFF


extern volatile uint32 wdt_counter;


void WDT_feed( void );
uint32 WDT_init( void );
void WDT_IRQHandler(void) ;

#endif
