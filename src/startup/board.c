#include "board.h"
#include "config.h"
#include "uart0.h"

extern int main(void);



#define CLOCK_SETUP           1
#define SCS_Val               0x00000020
#define CLKSRCSEL_Val         0x00000001	//选择主振荡器作为PLL0时钟源
#define PLL0_SETUP            1
#define PLL0CFG_Val           0x0000000B
#define PLL1_SETUP            1
#define PLL1CFG_Val           0x00000023
#define CCLKCFG_Val           0x00000003	//CCLK 为 PLL0 4分频
#define USBCLKCFG_Val         0x00000000
#define PCLKSEL0_Val          0x00000000
#define PCLKSEL1_Val          0x00000000
#define PCONP_Val             0x842887DE
#define CLKOUTCFG_Val         0x00000000

#define FLASH_SETUP           1
#define FLASHCFG_Val          0x0000503A






/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32 SystemFrequency = IRC_OSC; /*!< System Clock Frequency (Core Clock)  */



void LPC_systemInit (void)
{
#if (CLOCK_SETUP)                       /* Clock Setup                        */
  LPC_SC->SCS       = SCS_Val;
  if (SCS_Val & (1 << 5)) {             /* If Main Oscillator is enabled      */
    while ((LPC_SC->SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */
  }

  LPC_SC->CCLKCFG   = (FCCO / FCCLK) - 1;      /* Setup Clock Divider                */

  //关闭所有外设
  LPC_SC->PCLKSEL0  = PCLKSEL0_Val;     /* Peripheral Clock Selection         */
  LPC_SC->PCLKSEL1  = PCLKSEL1_Val;

#if (PLL0_SETUP)
  //FCCO =（2×M×FIN）/ N  = 2 * 12 * FIN / 1 = 24 * 12000000UL
  LPC_SC->CLKSRCSEL = CLKSRCSEL_Val;    /* Select Clock Source for PLL0       */

  LPC_SC->PLL0CFG   = (((PLL_NVALUE - 1) << 16) | (PLL_MVALUE - 1));    //M = 11+ 1  N =0 + 1
  LPC_SC->PLL0CON   = 0x01;             /* PLL0 Enable                        */
  LPC_SC->PLL0FEED  = 0xAA;
  LPC_SC->PLL0FEED  = 0x55;
  while (!(LPC_SC->PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

  LPC_SC->PLL0CON   = 0x03;             /* PLL0 Enable & Connect              */
  LPC_SC->PLL0FEED  = 0xAA;
  LPC_SC->PLL0FEED  = 0x55;
#endif

#if (PLL1_SETUP)
  LPC_SC->PLL1CFG   = PLL1CFG_Val;
  LPC_SC->PLL1CON   = 0x01;             /* PLL1 Enable                        */
  LPC_SC->PLL1FEED  = 0xAA;
  LPC_SC->PLL1FEED  = 0x55;
  while (!(LPC_SC->PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

  LPC_SC->PLL1CON   = 0x03;             /* PLL1 Enable & Connect              */
  LPC_SC->PLL1FEED  = 0xAA;
  LPC_SC->PLL1FEED  = 0x55;
#else
  LPC_SC->USBCLKCFG = USBCLKCFG_Val;    /* Setup USB Clock Divider            */
#endif

 //关闭所有外设 除了GPIO
  LPC_SC->PCONP     = (0x01UL << 15);        /* Power Control for Peripherals      */

  LPC_SC->CLKOUTCFG = CLKOUTCFG_Val;    /* Clock Output Configuration         */
#endif

  /* Determine clock frequency according to clock register values             */
  if (((LPC_SC->PLL0STAT >> 24)&3)==3) {/* If PLL0 enabled and connected      */
    switch (LPC_SC->CLKSRCSEL & 0x03) {
      case 0:                           /* Internal RC oscillator => PLL0     */
      case 3:                           /* Reserved, default to Internal RC   */
        SystemFrequency = (IRC_OSC * 
                          (((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1))) /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1))   /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
      case 1:                           /* Main oscillator => PLL0            */
        SystemFrequency = (OSC_CLK * 
                          (((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1))) /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1))   /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
      case 2:                           /* RTC oscillator => PLL0             */
        SystemFrequency = (RTC_CLK * 
                          (((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1))) /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1))   /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
    }
  } else {
    switch (LPC_SC->CLKSRCSEL & 0x03) {
      case 0:                           /* Internal RC oscillator => PLL0     */
      case 3:                           /* Reserved, default to Internal RC   */
        SystemFrequency = IRC_OSC / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
      case 1:                           /* Main oscillator => PLL0            */
        SystemFrequency = OSC_CLK / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
      case 2:                           /* RTC oscillator => PLL0             */
        SystemFrequency = RTC_CLK / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
    }
  }

#if (FLASH_SETUP == 1)                  /* Flash Accelerator Setup            */
 
#if FCCLK <= 20000000
    LPC_SC->FLASHCFG = ((0x01ul << 12) & (~(0x003f))) | 0x003a;                 /*  Flash访问使用1个CPU时钟     */
#endif                                                                  /*  FCCLK                       */

#if FCCLK > 20000000 && FCCLK <= 40000000
    LPC_SC->FLASHCFG = ((0x02ul << 12) & (~(0x003f))) | 0x003a;                 /*  Flash访问使用2个CPU时钟     */
#endif                                                                  /*  FCCLK                       */

#if FCCLK > 40000000 && FCCLK <= 60000000
    LPC_SC->FLASHCFG = ((0x03ul << 12) & (~(0x003f))) | 0x003a;                 /*  Flash访问使用3个CPU时钟     */
#endif                                                                  /*  FCCLK                       */

#if FCCLK > 60000000 && FCCLK <= 80000000
    LPC_SC->FLASHCFG = ((0x04ul << 12) & (~(0x003f))) | 0x003a;                 /*  Flash访问使用4个CPU时钟     */
#endif                                                                  /*  FCCLK                       */

#if FCCLK > 80000000 && FCCLK <= 100000000
    LPC_SC->FLASHCFG = ((0x05ul << 12) & (~(0x003f))) | 0x003a;                 /*  Flash访问使用5个CPU时钟     */
#endif       

#endif
}


void LPC_start(void)
{
	LPC_systemInit();
	uart0_init();

	
	main();
}



