#ifndef _BOARD_H_
#define _BOARD_H_

#include "common.h"


/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define XTAL        (12000000UL)        /* Oscillator frequency               */
#define OSC_CLK     (      XTAL)        /* Main oscillator frequency          */
#define RTC_CLK     (   32000UL)        /* RTC oscillator frequency           */
#define IRC_OSC     ( 4000000UL)        /* Internal RC oscillator frequency   */


#define FOSC                        XTAL                           	 /*  振荡器频率                  */


// FCCLK = FOSC  * 8 = 96MHZ
#define FCCLK                      (FOSC  * 8)                          /*  主时钟频率<=100Mhz          */
                                                                        /*  FOSC的整数倍                */
#define FCCO                       (FCCLK * 4)                          /*  PLL频率(275Mhz~550Mhz)      */
                                                                        /*  与FCCLK相同，或是其的偶数倍 */
#define FPCLK                      (FCCLK / 4)                          /*  外设时钟频率,FCCLK的1/2、1/4*/
                                                                        /*  或与FCCLK相同               */

#define PLL_NVALUE                  1UL                                   /*  1~256                       */
#define PLL_MVALUE                ((FCCO / FOSC) * (PLL_NVALUE) / 2)    /*  6~512                       */


void LPC_systemInit (void);

#endif
