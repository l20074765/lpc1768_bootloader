/******************************************************************************
 * @file:    LPC17xx.h
 * @purpose: CMSIS Cortex-M3 Core Peripheral Access Layer Header File for 
 *           NXP LPC17xx Device Series 
 * @version: V1.04
 * @date:    2. July 2009
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2008 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#ifndef __LPC17xx_H__
#define __LPC17xx_H__

#include "common.h"

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn           = -14,      /*!< 2 Non Maskable Interrupt                         */
  MemoryManagement_IRQn         = -12,      /*!< 4 Cortex-M3 Memory Management Interrupt          */
  BusFault_IRQn                 = -11,      /*!< 5 Cortex-M3 Bus Fault Interrupt                  */
  UsageFault_IRQn               = -10,      /*!< 6 Cortex-M3 Usage Fault Interrupt                */
  SVCall_IRQn                   = -5,       /*!< 11 Cortex-M3 SV Call Interrupt                   */
  DebugMonitor_IRQn             = -4,       /*!< 12 Cortex-M3 Debug Monitor Interrupt             */
  PendSV_IRQn                   = -2,       /*!< 14 Cortex-M3 Pend SV Interrupt                   */
  SysTick_IRQn                  = -1,       /*!< 15 Cortex-M3 System Tick Interrupt               */

/******  LPC17xx Specific Interrupt Numbers *******************************************************/
  WDT_IRQn                      = 0,        /*!< Watchdog Timer Interrupt                         */
  TIMER0_IRQn                   = 1,        /*!< Timer0 Interrupt                                 */
  TIMER1_IRQn                   = 2,        /*!< Timer1 Interrupt                                 */
  TIMER2_IRQn                   = 3,        /*!< Timer2 Interrupt                                 */
  TIMER3_IRQn                   = 4,        /*!< Timer3 Interrupt                                 */
  UART0_IRQn                    = 5,        /*!< UART0 Interrupt                                  */
  UART1_IRQn                    = 6,        /*!< UART1 Interrupt                                  */
  UART2_IRQn                    = 7,        /*!< UART2 Interrupt                                  */
  UART3_IRQn                    = 8,        /*!< UART3 Interrupt                                  */
  PWM1_IRQn                     = 9,        /*!< PWM1 Interrupt                                   */
  I2C0_IRQn                     = 10,       /*!< I2C0 Interrupt                                   */
  I2C1_IRQn                     = 11,       /*!< I2C1 Interrupt                                   */
  I2C2_IRQn                     = 12,       /*!< I2C2 Interrupt                                   */
  SPI_IRQn                      = 13,       /*!< SPI Interrupt                                    */
  SSP0_IRQn                     = 14,       /*!< SSP0 Interrupt                                   */
  SSP1_IRQn                     = 15,       /*!< SSP1 Interrupt                                   */
  PLL0_IRQn                     = 16,       /*!< PLL0 Lock (Main PLL) Interrupt                   */
  RTC_IRQn                      = 17,       /*!< Real Time Clock Interrupt                        */
  EINT0_IRQn                    = 18,       /*!< External Interrupt 0 Interrupt                   */
  EINT1_IRQn                    = 19,       /*!< External Interrupt 1 Interrupt                   */
  EINT2_IRQn                    = 20,       /*!< External Interrupt 2 Interrupt                   */
  EINT3_IRQn                    = 21,       /*!< External Interrupt 3 Interrupt                   */
  ADC_IRQn                      = 22,       /*!< A/D Converter Interrupt                          */
  BOD_IRQn                      = 23,       /*!< Brown-Out Detect Interrupt                       */
  USB_IRQn                      = 24,       /*!< USB Interrupt                                    */
  CAN_IRQn                      = 25,       /*!< CAN Interrupt                                    */
  DMA_IRQn                      = 26,       /*!< General Purpose DMA Interrupt                    */
  I2S_IRQn                      = 27,       /*!< I2S Interrupt                                    */
  ENET_IRQn                     = 28,       /*!< Ethernet Interrupt                               */
  RIT_IRQn                      = 29,       /*!< Repetitive Interrupt Timer Interrupt             */
  MCPWM_IRQn                    = 30,       /*!< Motor Control PWM Interrupt                      */
  QEI_IRQn                      = 31,       /*!< Quadrature Encoder Interface Interrupt           */
  PLL1_IRQn                     = 32,       /*!< PLL1 Lock (USB PLL) Interrupt                    */
  USBActivity_IRQn              = 33,       /* USB Activity interrupt                             */
  CANActivity_IRQn              = 34,       /* CAN Activity interrupt                             */
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __MPU_PRESENT             1         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          5         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */



#define __IO	volatile
#define __O		volatile
#define __I		volatile const 


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/



/*------------- System Control (SC) ------------------------------------------*/
typedef struct
{
  __IO uint32 FLASHCFG;               /* Flash Accelerator Module           */
       uint32 RESERVED0[31];
  __IO uint32 PLL0CON;                /* Clocking and Power Control         */
  __IO uint32 PLL0CFG;
  __I  uint32 PLL0STAT;
  __O  uint32 PLL0FEED;
       uint32 RESERVED1[4];
  __IO uint32 PLL1CON;
  __IO uint32 PLL1CFG;
  __I  uint32 PLL1STAT;
  __O  uint32 PLL1FEED;
       uint32 RESERVED2[4];
  __IO uint32 PCON;
  __IO uint32 PCONP;
       uint32 RESERVED3[15];
  __IO uint32 CCLKCFG;
  __IO uint32 USBCLKCFG;
  __IO uint32 CLKSRCSEL;
  __IO uint32	CANSLEEPCLR;
  __IO uint32	CANWAKEFLAGS;
       uint32 RESERVED4[10];
  __IO uint32 EXTINT;                 /* External Interrupts                */
       uint32 RESERVED5;
  __IO uint32 EXTMODE;
  __IO uint32 EXTPOLAR;
       uint32 RESERVED6[12];
  __IO uint32 RSID;                   /* Reset                              */
       uint32 RESERVED7[7];
  __IO uint32 SCS;                    /* Syscon Miscellaneous Registers     */
  __IO uint32 IRCTRIM;                /* Clock Dividers                     */
  __IO uint32 PCLKSEL0;
  __IO uint32 PCLKSEL1;
       uint32 RESERVED8[4];
  __IO uint32 USBIntSt;               /* USB Device/OTG Interrupt Register  */
  __IO uint32 DMAREQSEL;              /* DMA Request Select Register        */
  __IO uint32 CLKOUTCFG;              /* Clock Output Configuration         */
 } LPC_SC_TypeDef;

/*------------- Pin Connect Block (PINCON) -----------------------------------*/
typedef struct
{
  __IO uint32 PINSEL0;
  __IO uint32 PINSEL1;
  __IO uint32 PINSEL2;
  __IO uint32 PINSEL3;
  __IO uint32 PINSEL4;
  __IO uint32 PINSEL5;
  __IO uint32 PINSEL6;
  __IO uint32 PINSEL7;
  __IO uint32 PINSEL8;
  __IO uint32 PINSEL9;
  __IO uint32 PINSEL10;
       uint32 RESERVED0[5];
  __IO uint32 PINMODE0;
  __IO uint32 PINMODE1;
  __IO uint32 PINMODE2;
  __IO uint32 PINMODE3;
  __IO uint32 PINMODE4;
  __IO uint32 PINMODE5;
  __IO uint32 PINMODE6;
  __IO uint32 PINMODE7;
  __IO uint32 PINMODE8;
  __IO uint32 PINMODE9;
  __IO uint32 PINMODE_OD0;
  __IO uint32 PINMODE_OD1;
  __IO uint32 PINMODE_OD2;
  __IO uint32 PINMODE_OD3;
  __IO uint32 PINMODE_OD4;
  __IO uint32 I2CPADCFG;
} LPC_PINCON_TypeDef;

/*------------- General Purpose Input/Output (GPIO) --------------------------*/
typedef struct
{
  __IO uint32 FIODIR;
       uint32 RESERVED0[3];
  __IO uint32 FIOMASK;
  __IO uint32 FIOPIN;
  __IO uint32 FIOSET;
  __O  uint32 FIOCLR;
} LPC_GPIO_TypeDef;

typedef struct
{
  __I  uint32 IntStatus;
  __I  uint32 IO0IntStatR;
  __I  uint32 IO0IntStatF;
  __O  uint32 IO0IntClr;
  __IO uint32 IO0IntEnR;
  __IO uint32 IO0IntEnF;
       uint32 RESERVED0[3];
  __I  uint32 IO2IntStatR;
  __I  uint32 IO2IntStatF;
  __O  uint32 IO2IntClr;
  __IO uint32 IO2IntEnR;
  __IO uint32 IO2IntEnF;
} LPC_GPIOINT_TypeDef;

/*------------- Timer (TIM) --------------------------------------------------*/
typedef struct
{
  __IO uint32 IR;
  __IO uint32 TCR;
  __IO uint32 TC;
  __IO uint32 PR;
  __IO uint32 PC;
  __IO uint32 MCR;
  __IO uint32 MR0;
  __IO uint32 MR1;
  __IO uint32 MR2;
  __IO uint32 MR3;
  __IO uint32 CCR;
  __I  uint32 CR0;
  __I  uint32 CR1;
       uint32 RESERVED0[2];
  __IO uint32 EMR;
       uint32 RESERVED1[12];
  __IO uint32 CTCR;
} LPC_TIM_TypeDef;

/*------------- Pulse-Width Modulation (PWM) ---------------------------------*/
typedef struct
{
  __IO uint32 IR;
  __IO uint32 TCR;
  __IO uint32 TC;
  __IO uint32 PR;
  __IO uint32 PC;
  __IO uint32 MCR;
  __IO uint32 MR0;
  __IO uint32 MR1;
  __IO uint32 MR2;
  __IO uint32 MR3;
  __IO uint32 CCR;
  __I  uint32 CR0;
  __I  uint32 CR1;
  __I  uint32 CR2;
  __I  uint32 CR3;
       uint32 RESERVED0;
  __IO uint32 MR4;
  __IO uint32 MR5;
  __IO uint32 MR6;
  __IO uint32 PCR;
  __IO uint32 LER;
       uint32 RESERVED1[7];
  __IO uint32 CTCR;
} LPC_PWM_TypeDef;

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
typedef struct
{
  union {
  __I  uint8  RBR;
  __O  uint8  THR;
  __IO uint8  DLL;
       uint32 RESERVED0;
  };
  union {
  __IO uint8  DLM;
  __IO uint32 IER;
  };
  union {
  __I  uint32 IIR;
  __O  uint8  FCR;
  };
  __IO uint8  LCR;
       uint8  RESERVED1[7];
  __I  uint8  LSR;
       uint8  RESERVED2[7];
  __IO uint8  SCR;
       uint8  RESERVED3[3];
  __IO uint32 ACR;
  __IO uint8  ICR;
       uint8  RESERVED4[3];
  __IO uint8  FDR;
       uint8  RESERVED5[7];
  __IO uint8  TER;
       uint8  RESERVED6[39];
  __I  uint8  FIFOLVL;
} LPC_UART_TypeDef;

typedef struct
{
  union {
  __I  uint8  RBR;
  __O  uint8  THR;
  __IO uint8  DLL;
       uint32 RESERVED0;
  };
  union {
  __IO uint8  DLM;
  __IO uint32 IER;
  };
  union {
  __I  uint32 IIR;
  __O  uint8  FCR;
  };
  __IO uint8  LCR;
       uint8  RESERVED1[7];
  __I  uint8  LSR;
       uint8  RESERVED2[7];
  __IO uint8  SCR;
       uint8  RESERVED3[3];
  __IO uint32 ACR;
  __IO uint8  ICR;
       uint8  RESERVED4[3];
  __IO uint8  FDR;
       uint8  RESERVED5[7];
  __IO uint8  TER;
       uint8  RESERVED6[39];
  __I  uint8  FIFOLVL;
} LPC_UART0_TypeDef;

typedef struct
{
  union {
  __I  uint8  RBR;
  __O  uint8  THR;
  __IO uint8  DLL;
       uint32 RESERVED0;
  };
  union {
  __IO uint8  DLM;
  __IO uint32 IER;
  };
  union {
  __I  uint32 IIR;
  __O  uint8  FCR;
  };
  __IO uint8  LCR;
       uint8  RESERVED1[3];
  __IO uint8  MCR;
       uint8  RESERVED2[3];
  __I  uint8  LSR;
       uint8  RESERVED3[3];
  __I  uint8  MSR;
       uint8  RESERVED4[3];
  __IO uint8  SCR;
       uint8  RESERVED5[3];
  __IO uint32 ACR;
       uint32 RESERVED6;
  __IO uint32 FDR;
       uint32 RESERVED7;
  __IO uint8  TER;
       uint8  RESERVED8[27];
  __IO uint8  RS485CTRL;
       uint8  RESERVED9[3];
  __IO uint8  ADRMATCH;
       uint8  RESERVED10[3];
  __IO uint8  RS485DLY;
       uint8  RESERVED11[3];
  __I  uint8  FIFOLVL;
} LPC_UART1_TypeDef;

/*------------- Serial Peripheral Interface (SPI) ----------------------------*/
typedef struct
{
  __IO uint32 SPCR;
  __I  uint32 SPSR;
  __IO uint32 SPDR;
  __IO uint32 SPCCR;
       uint32 RESERVED0[3];
  __IO uint32 SPINT;
} LPC_SPI_TypeDef;

/*------------- Synchronous Serial Communication (SSP) -----------------------*/
typedef struct
{
  __IO uint32 CR0;
  __IO uint32 CR1;
  __IO uint32 DR;
  __I  uint32 SR;
  __IO uint32 CPSR;
  __IO uint32 IMSC;
  __IO uint32 RIS;
  __IO uint32 MIS;
  __IO uint32 ICR;
  __IO uint32 DMACR;
} LPC_SSP_TypeDef;

/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
typedef struct
{
  __IO uint32 I2CONSET;
  __I  uint32 I2STAT;
  __IO uint32 I2DAT;
  __IO uint32 I2ADR0;
  __IO uint32 I2SCLH;
  __IO uint32 I2SCLL;
  __O  uint32 I2CONCLR;
  __IO uint32 MMCTRL;
  __IO uint32 I2ADR1;
  __IO uint32 I2ADR2;
  __IO uint32 I2ADR3;
  __I  uint32 I2DATA_BUFFER;
  __IO uint32 I2MASK0;
  __IO uint32 I2MASK1;
  __IO uint32 I2MASK2;
  __IO uint32 I2MASK3;
} LPC_I2C_TypeDef;

/*------------- Inter IC Sound (I2S) -----------------------------------------*/
typedef struct
{
  __IO uint32 I2SDAO;
  __IO uint32 I2SDAI;
  __O  uint32 I2STXFIFO;
  __I  uint32 I2SRXFIFO;
  __I  uint32 I2SSTATE;
  __IO uint32 I2SDMA1;
  __IO uint32 I2SDMA2;
  __IO uint32 I2SIRQ;
  __IO uint32 I2STXRATE;
  __IO uint32 I2SRXRATE;
  __IO uint32 I2STXBITRATE;
  __IO uint32 I2SRXBITRATE;
  __IO uint32 I2STXMODE;
  __IO uint32 I2SRXMODE;
} LPC_I2S_TypeDef;

/*------------- Repetitive Interrupt Timer (RIT) -----------------------------*/
typedef struct
{
  __IO uint32 RICOMPVAL;
  __IO uint32 RIMASK;
  __IO uint8  RICTRL;
       uint8  RESERVED0[3];
  __IO uint32 RICOUNTER;
} LPC_RIT_TypeDef;

/*------------- Real-Time Clock (RTC) ----------------------------------------*/
typedef struct
{
  __IO uint8  ILR;
       uint8  RESERVED0[7];
  __IO uint8  CCR;
       uint8  RESERVED1[3];
  __IO uint8  CIIR;
       uint8  RESERVED2[3];
  __IO uint8  AMR;
       uint8  RESERVED3[3];
  __I  uint32 CTIME0;
  __I  uint32 CTIME1;
  __I  uint32 CTIME2;
  __IO uint8  SEC;
       uint8  RESERVED4[3];
  __IO uint8  MIN;
       uint8  RESERVED5[3];
  __IO uint8  HOUR;
       uint8  RESERVED6[3];
  __IO uint8  DOM;
       uint8  RESERVED7[3];
  __IO uint8  DOW;
       uint8  RESERVED8[3];
  __IO uint16 DOY;
       uint16 RESERVED9;
  __IO uint8  MONTH;
       uint8  RESERVED10[3];
  __IO uint16 YEAR;
       uint16 RESERVED11;
  __IO uint32 CALIBRATION;
  __IO uint32 GPREG0;
  __IO uint32 GPREG1;
  __IO uint32 GPREG2;
  __IO uint32 GPREG3;
  __IO uint32 GPREG4;
  __IO uint8  RTC_AUXEN;
       uint8  RESERVED12[3];
  __IO uint8  RTC_AUX;
       uint8  RESERVED13[3];
  __IO uint8  ALSEC;
       uint8  RESERVED14[3];
  __IO uint8  ALMIN;
       uint8  RESERVED15[3];
  __IO uint8  ALHOUR;
       uint8  RESERVED16[3];
  __IO uint8  ALDOM;
       uint8  RESERVED17[3];
  __IO uint8  ALDOW;
       uint8  RESERVED18[3];
  __IO uint16 ALDOY;
       uint16 RESERVED19;
  __IO uint8  ALMON;
       uint8  RESERVED20[3];
  __IO uint16 ALYEAR;
       uint16 RESERVED21;
} LPC_RTC_TypeDef;

/*------------- Watchdog Timer (WDT) -----------------------------------------*/
typedef struct
{
  __IO uint8  WDMOD;
       uint8  RESERVED0[3];
  __IO uint32 WDTC;
  __O  uint8  WDFEED;
       uint8  RESERVED1[3];
  __I  uint32 WDTV;
  __IO uint32 WDCLKSEL;
} LPC_WDT_TypeDef;

/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/
typedef struct
{
  __IO uint32 ADCR;
  __IO uint32 ADGDR;
       uint32 RESERVED0;
  __IO uint32 ADINTEN;
  __I  uint32 ADDR0;
  __I  uint32 ADDR1;
  __I  uint32 ADDR2;
  __I  uint32 ADDR3;
  __I  uint32 ADDR4;
  __I  uint32 ADDR5;
  __I  uint32 ADDR6;
  __I  uint32 ADDR7;
  __I  uint32 ADSTAT;
  __IO uint32 ADTRM;
} LPC_ADC_TypeDef;

/*------------- Digital-to-Analog Converter (DAC) ----------------------------*/
typedef struct
{
  __IO uint32 DACR;
  __IO uint32 DACCTRL;
  __IO uint16 DACCNTVAL;
} LPC_DAC_TypeDef;

/*------------- Motor Control Pulse-Width Modulation (MCPWM) -----------------*/
typedef struct
{
  __I  uint32 MCCON;
  __O  uint32 MCCON_SET;
  __O  uint32 MCCON_CLR;
  __I  uint32 MCCAPCON;
  __O  uint32 MCCAPCON_SET;
  __O  uint32 MCCAPCON_CLR;
  __IO uint32 MCTIM0;
  __IO uint32 MCTIM1;
  __IO uint32 MCTIM2;
  __IO uint32 MCPER0;
  __IO uint32 MCPER1;
  __IO uint32 MCPER2;
  __IO uint32 MCPW0;
  __IO uint32 MCPW1;
  __IO uint32 MCPW2;
  __IO uint32 MCDEADTIME;
  __IO uint32 MCCCP;
  __IO uint32 MCCR0;
  __IO uint32 MCCR1;
  __IO uint32 MCCR2;
  __I  uint32 MCINTEN;
  __O  uint32 MCINTEN_SET;
  __O  uint32 MCINTEN_CLR;
  __I  uint32 MCCNTCON;
  __O  uint32 MCCNTCON_SET;
  __O  uint32 MCCNTCON_CLR;
  __I  uint32 MCINTFLAG;
  __O  uint32 MCINTFLAG_SET;
  __O  uint32 MCINTFLAG_CLR;
  __O  uint32 MCCAP_CLR;
} LPC_MCPWM_TypeDef;

/*------------- Quadrature Encoder Interface (QEI) ---------------------------*/
typedef struct
{
  __O  uint32 QEICON;
  __I  uint32 QEISTAT;
  __IO uint32 QEICONF;
  __I  uint32 QEIPOS;
  __IO uint32 QEIMAXPOS;
  __IO uint32 CMPOS0;
  __IO uint32 CMPOS1;
  __IO uint32 CMPOS2;
  __I  uint32 INXCNT;
  __IO uint32 INXCMP;
  __IO uint32 QEILOAD;
  __I  uint32 QEITIME;
  __I  uint32 QEIVEL;
  __I  uint32 QEICAP;
  __IO uint32 VELCOMP;
  __IO uint32 FILTER;
       uint32 RESERVED0[998];
  __O  uint32 QEIIEC;
  __O  uint32 QEIIES;
  __I  uint32 QEIINTSTAT;
  __I  uint32 QEIIE;
  __O  uint32 QEICLR;
  __O  uint32 QEISET;
} LPC_QEI_TypeDef;

/*------------- Controller Area Network (CAN) --------------------------------*/
typedef struct
{
  __IO uint32 mask[512];              /* ID Masks                           */
} LPC_CANAF_RAM_TypeDef;

typedef struct                          /* Acceptance Filter Registers        */
{
  __IO uint32 AFMR;
  __IO uint32 SFF_sa;
  __IO uint32 SFF_GRP_sa;
  __IO uint32 EFF_sa;
  __IO uint32 EFF_GRP_sa;
  __IO uint32 ENDofTable;
  __I  uint32 LUTerrAd;
  __I  uint32 LUTerr;
  __IO uint32 FCANIE;
  __IO uint32 FCANIC0;
  __IO uint32 FCANIC1;
} LPC_CANAF_TypeDef;

typedef struct                          /* Central Registers                  */
{
  __I  uint32 CANTxSR;
  __I  uint32 CANRxSR;
  __I  uint32 CANMSR;
} LPC_CANCR_TypeDef;

typedef struct                          /* Controller Registers               */
{
  __IO uint32 MOD;
  __O  uint32 CMR;
  __IO uint32 GSR;
  __I  uint32 ICR;
  __IO uint32 IER;
  __IO uint32 BTR;
  __IO uint32 EWL;
  __I  uint32 SR;
  __IO uint32 RFS;
  __IO uint32 RID;
  __IO uint32 RDA;
  __IO uint32 RDB;
  __IO uint32 TFI1;
  __IO uint32 TID1;
  __IO uint32 TDA1;
  __IO uint32 TDB1;
  __IO uint32 TFI2;
  __IO uint32 TID2;
  __IO uint32 TDA2;
  __IO uint32 TDB2;
  __IO uint32 TFI3;
  __IO uint32 TID3;
  __IO uint32 TDA3;
  __IO uint32 TDB3;
} LPC_CAN_TypeDef;

/*------------- General Purpose Direct Memory Access (GPDMA) -----------------*/
typedef struct                          /* Common Registers                   */
{
  __I  uint32 DMACIntStat;
  __I  uint32 DMACIntTCStat;
  __O  uint32 DMACIntTCClear;
  __I  uint32 DMACIntErrStat;
  __O  uint32 DMACIntErrClr;
  __I  uint32 DMACRawIntTCStat;
  __I  uint32 DMACRawIntErrStat;
  __I  uint32 DMACEnbldChns;
  __IO uint32 DMACSoftBReq;
  __IO uint32 DMACSoftSReq;
  __IO uint32 DMACSoftLBReq;
  __IO uint32 DMACSoftLSReq;
  __IO uint32 DMACConfig;
  __IO uint32 DMACSync;
} LPC_GPDMA_TypeDef;

typedef struct                          /* Channel Registers                  */
{
  __IO uint32 DMACCSrcAddr;
  __IO uint32 DMACCDestAddr;
  __IO uint32 DMACCLLI;
  __IO uint32 DMACCControl;
  __IO uint32 DMACCConfig;
} LPC_GPDMACH_TypeDef;

/*------------- Universal Serial Bus (USB) -----------------------------------*/
typedef struct
{
  __I  uint32 HcRevision;             /* USB Host Registers                 */
  __IO uint32 HcControl;
  __IO uint32 HcCommandStatus;
  __IO uint32 HcInterruptStatus;
  __IO uint32 HcInterruptEnable;
  __IO uint32 HcInterruptDisable;
  __IO uint32 HcHCCA;
  __I  uint32 HcPeriodCurrentED;
  __IO uint32 HcControlHeadED;
  __IO uint32 HcControlCurrentED;
  __IO uint32 HcBulkHeadED;
  __IO uint32 HcBulkCurrentED;
  __I  uint32 HcDoneHead;
  __IO uint32 HcFmInterval;
  __I  uint32 HcFmRemaining;
  __I  uint32 HcFmNumber;
  __IO uint32 HcPeriodicStart;
  __IO uint32 HcLSTreshold;
  __IO uint32 HcRhDescriptorA;
  __IO uint32 HcRhDescriptorB;
  __IO uint32 HcRhStatus;
  __IO uint32 HcRhPortStatus1;
  __IO uint32 HcRhPortStatus2;
       uint32 RESERVED0[40];
  __I  uint32 Module_ID;

  __I  uint32 OTGIntSt;               /* USB On-The-Go Registers            */
  __IO uint32 OTGIntEn;
  __O  uint32 OTGIntSet;
  __O  uint32 OTGIntClr;
  __IO uint32 OTGStCtrl;
  __IO uint32 OTGTmr;
       uint32 RESERVED1[58];

  __I  uint32 USBDevIntSt;            /* USB Device Interrupt Registers     */
  __IO uint32 USBDevIntEn;
  __O  uint32 USBDevIntClr;
  __O  uint32 USBDevIntSet;

  __O  uint32 USBCmdCode;             /* USB Device SIE Command Registers   */
  __I  uint32 USBCmdData;

  __I  uint32 USBRxData;              /* USB Device Transfer Registers      */
  __O  uint32 USBTxData;
  __I  uint32 USBRxPLen;
  __O  uint32 USBTxPLen;
  __IO uint32 USBCtrl;
  __O  uint32 USBDevIntPri;

  __I  uint32 USBEpIntSt;             /* USB Device Endpoint Interrupt Regs */
  __IO uint32 USBEpIntEn;
  __O  uint32 USBEpIntClr;
  __O  uint32 USBEpIntSet;
  __O  uint32 USBEpIntPri;

  __IO uint32 USBReEp;                /* USB Device Endpoint Realization Reg*/
  __O  uint32 USBEpInd;
  __IO uint32 USBMaxPSize;

  __I  uint32 USBDMARSt;              /* USB Device DMA Registers           */
  __O  uint32 USBDMARClr;
  __O  uint32 USBDMARSet;
       uint32 RESERVED2[9];
  __IO uint32 USBUDCAH;
  __I  uint32 USBEpDMASt;
  __O  uint32 USBEpDMAEn;
  __O  uint32 USBEpDMADis;
  __I  uint32 USBDMAIntSt;
  __IO uint32 USBDMAIntEn;
       uint32 RESERVED3[2];
  __I  uint32 USBEoTIntSt;
  __O  uint32 USBEoTIntClr;
  __O  uint32 USBEoTIntSet;
  __I  uint32 USBNDDRIntSt;
  __O  uint32 USBNDDRIntClr;
  __O  uint32 USBNDDRIntSet;
  __I  uint32 USBSysErrIntSt;
  __O  uint32 USBSysErrIntClr;
  __O  uint32 USBSysErrIntSet;
       uint32 RESERVED4[15];

  union {
  __I  uint32 I2C_RX;                 /* USB OTG I2C Registers              */
  __O  uint32 I2C_WO;
  };
  __I  uint32 I2C_STS;
  __IO uint32 I2C_CTL;
  __IO uint32 I2C_CLKHI;
  __O  uint32 I2C_CLKLO;
       uint32 RESERVED5[824];

  union {
  __IO uint32 USBClkCtrl;             /* USB Clock Control Registers        */
  __IO uint32 OTGClkCtrl;
  };
  union {
  __I  uint32 USBClkSt;
  __I  uint32 OTGClkSt;
  };
} LPC_USB_TypeDef;

/*------------- Ethernet Media Access Controller (EMAC) ----------------------*/
typedef struct
{
  __IO uint32 MAC1;                   /* MAC Registers                      */
  __IO uint32 MAC2;
  __IO uint32 IPGT;
  __IO uint32 IPGR;
  __IO uint32 CLRT;
  __IO uint32 MAXF;
  __IO uint32 SUPP;
  __IO uint32 TEST;
  __IO uint32 MCFG;
  __IO uint32 MCMD;
  __IO uint32 MADR;
  __O  uint32 MWTD;
  __I  uint32 MRDD;
  __I  uint32 MIND;
       uint32 RESERVED0[2];
  __IO uint32 SA0;
  __IO uint32 SA1;
  __IO uint32 SA2;
       uint32 RESERVED1[45];
  __IO uint32 Command;                /* Control Registers                  */
  __I  uint32 Status;
  __IO uint32 RxDescriptor;
  __IO uint32 RxStatus;
  __IO uint32 RxDescriptorNumber;
  __I  uint32 RxProduceIndex;
  __IO uint32 RxConsumeIndex;
  __IO uint32 TxDescriptor;
  __IO uint32 TxStatus;
  __IO uint32 TxDescriptorNumber;
  __IO uint32 TxProduceIndex;
  __I  uint32 TxConsumeIndex;
       uint32 RESERVED2[10];
  __I  uint32 TSV0;
  __I  uint32 TSV1;
  __I  uint32 RSV;
       uint32 RESERVED3[3];
  __IO uint32 FlowControlCounter;
  __I  uint32 FlowControlStatus;
       uint32 RESERVED4[34];
  __IO uint32 RxFilterCtrl;           /* Rx Filter Registers                */
  __IO uint32 RxFilterWoLStatus;
  __IO uint32 RxFilterWoLClear;
       uint32 RESERVED5;
  __IO uint32 HashFilterL;
  __IO uint32 HashFilterH;
       uint32 RESERVED6[882];
  __I  uint32 IntStatus;              /* Module Control Registers           */
  __IO uint32 IntEnable;
  __O  uint32 IntClear;
  __O  uint32 IntSet;
       uint32 RESERVED7;
  __IO uint32 PowerDown;
       uint32 RESERVED8;
  __IO uint32 Module_ID;
} LPC_EMAC_TypeDef;




/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define LPC_FLASH_BASE        (0x00000000UL)
#define LPC_RAM_BASE          (0x10000000UL)
#define LPC_GPIO_BASE         (0x2009C000UL)
#define LPC_APB0_BASE         (0x40000000UL)
#define LPC_APB1_BASE         (0x40080000UL)
#define LPC_AHB_BASE          (0x50000000UL)
#define LPC_CM3_BASE          (0xE0000000UL)

/* APB0 peripherals                                                           */
#define LPC_WDT_BASE          (LPC_APB0_BASE + 0x00000)
#define LPC_TIM0_BASE         (LPC_APB0_BASE + 0x04000)
#define LPC_TIM1_BASE         (LPC_APB0_BASE + 0x08000)
#define LPC_UART0_BASE        (LPC_APB0_BASE + 0x0C000)
#define LPC_UART1_BASE        (LPC_APB0_BASE + 0x10000)
#define LPC_PWM1_BASE         (LPC_APB0_BASE + 0x18000)
#define LPC_I2C0_BASE         (LPC_APB0_BASE + 0x1C000)
#define LPC_SPI_BASE          (LPC_APB0_BASE + 0x20000)
#define LPC_RTC_BASE          (LPC_APB0_BASE + 0x24000)
#define LPC_GPIOINT_BASE      (LPC_APB0_BASE + 0x28080)
#define LPC_PINCON_BASE       (LPC_APB0_BASE + 0x2C000)
#define LPC_SSP1_BASE         (LPC_APB0_BASE + 0x30000)
#define LPC_ADC_BASE          (LPC_APB0_BASE + 0x34000)
#define LPC_CANAF_RAM_BASE    (LPC_APB0_BASE + 0x38000)
#define LPC_CANAF_BASE        (LPC_APB0_BASE + 0x3C000)
#define LPC_CANCR_BASE        (LPC_APB0_BASE + 0x40000)
#define LPC_CAN1_BASE         (LPC_APB0_BASE + 0x44000)
#define LPC_CAN2_BASE         (LPC_APB0_BASE + 0x48000)
#define LPC_I2C1_BASE         (LPC_APB0_BASE + 0x5C000)

/* APB1 peripherals                                                           */
#define LPC_SSP0_BASE         (LPC_APB1_BASE + 0x08000)
#define LPC_DAC_BASE          (LPC_APB1_BASE + 0x0C000)
#define LPC_TIM2_BASE         (LPC_APB1_BASE + 0x10000)
#define LPC_TIM3_BASE         (LPC_APB1_BASE + 0x14000)
#define LPC_UART2_BASE        (LPC_APB1_BASE + 0x18000)
#define LPC_UART3_BASE        (LPC_APB1_BASE + 0x1C000)
#define LPC_I2C2_BASE         (LPC_APB1_BASE + 0x20000)
#define LPC_I2S_BASE          (LPC_APB1_BASE + 0x28000)
#define LPC_RIT_BASE          (LPC_APB1_BASE + 0x30000)
#define LPC_MCPWM_BASE        (LPC_APB1_BASE + 0x38000)
#define LPC_QEI_BASE          (LPC_APB1_BASE + 0x3C000)
#define LPC_SC_BASE           (LPC_APB1_BASE + 0x7C000)

/* AHB peripherals                                                            */
#define LPC_EMAC_BASE         (LPC_AHB_BASE  + 0x00000)
#define LPC_GPDMA_BASE        (LPC_AHB_BASE  + 0x04000)
#define LPC_GPDMACH0_BASE     (LPC_AHB_BASE  + 0x04100)
#define LPC_GPDMACH1_BASE     (LPC_AHB_BASE  + 0x04120)
#define LPC_GPDMACH2_BASE     (LPC_AHB_BASE  + 0x04140)
#define LPC_GPDMACH3_BASE     (LPC_AHB_BASE  + 0x04160)
#define LPC_GPDMACH4_BASE     (LPC_AHB_BASE  + 0x04180)
#define LPC_GPDMACH5_BASE     (LPC_AHB_BASE  + 0x041A0)
#define LPC_GPDMACH6_BASE     (LPC_AHB_BASE  + 0x041C0)
#define LPC_GPDMACH7_BASE     (LPC_AHB_BASE  + 0x041E0)
#define LPC_USB_BASE          (LPC_AHB_BASE  + 0x0C000)

/* GPIOs                                                                      */
#define LPC_GPIO0_BASE        (LPC_GPIO_BASE + 0x00000)
#define LPC_GPIO1_BASE        (LPC_GPIO_BASE + 0x00020)
#define LPC_GPIO2_BASE        (LPC_GPIO_BASE + 0x00040)
#define LPC_GPIO3_BASE        (LPC_GPIO_BASE + 0x00060)
#define LPC_GPIO4_BASE        (LPC_GPIO_BASE + 0x00080)


/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define LPC_SC                ((LPC_SC_TypeDef        *) LPC_SC_BASE       )
#define LPC_GPIO0             ((LPC_GPIO_TypeDef      *) LPC_GPIO0_BASE    )
#define LPC_GPIO1             ((LPC_GPIO_TypeDef      *) LPC_GPIO1_BASE    )
#define LPC_GPIO2             ((LPC_GPIO_TypeDef      *) LPC_GPIO2_BASE    )
#define LPC_GPIO3             ((LPC_GPIO_TypeDef      *) LPC_GPIO3_BASE    )
#define LPC_GPIO4             ((LPC_GPIO_TypeDef      *) LPC_GPIO4_BASE    )
#define LPC_WDT               ((LPC_WDT_TypeDef       *) LPC_WDT_BASE      )
#define LPC_TIM0              ((LPC_TIM_TypeDef       *) LPC_TIM0_BASE     )
#define LPC_TIM1              ((LPC_TIM_TypeDef       *) LPC_TIM1_BASE     )
#define LPC_TIM2              ((LPC_TIM_TypeDef       *) LPC_TIM2_BASE     )
#define LPC_TIM3              ((LPC_TIM_TypeDef       *) LPC_TIM3_BASE     )
#define LPC_RIT               ((LPC_RIT_TypeDef       *) LPC_RIT_BASE      )
#define LPC_UART0             ((LPC_UART0_TypeDef     *) LPC_UART0_BASE    )
#define LPC_UART1             ((LPC_UART1_TypeDef     *) LPC_UART1_BASE    )
#define LPC_UART2             ((LPC_UART_TypeDef      *) LPC_UART2_BASE    )
#define LPC_UART3             ((LPC_UART_TypeDef      *) LPC_UART3_BASE    )
#define LPC_PWM1              ((LPC_PWM_TypeDef       *) LPC_PWM1_BASE     )
#define LPC_I2C0              ((LPC_I2C_TypeDef       *) LPC_I2C0_BASE     )
#define LPC_I2C1              ((LPC_I2C_TypeDef       *) LPC_I2C1_BASE     )
#define LPC_I2C2              ((LPC_I2C_TypeDef       *) LPC_I2C2_BASE     )
#define LPC_I2S               ((LPC_I2S_TypeDef       *) LPC_I2S_BASE      )
#define LPC_SPI               ((LPC_SPI_TypeDef       *) LPC_SPI_BASE      )
#define LPC_RTC               ((LPC_RTC_TypeDef       *) LPC_RTC_BASE      )
#define LPC_GPIOINT           ((LPC_GPIOINT_TypeDef   *) LPC_GPIOINT_BASE  )
#define LPC_PINCON            ((LPC_PINCON_TypeDef    *) LPC_PINCON_BASE   )
#define LPC_SSP0              ((LPC_SSP_TypeDef       *) LPC_SSP0_BASE     )
#define LPC_SSP1              ((LPC_SSP_TypeDef       *) LPC_SSP1_BASE     )
#define LPC_ADC               ((LPC_ADC_TypeDef       *) LPC_ADC_BASE      )
#define LPC_DAC               ((LPC_DAC_TypeDef       *) LPC_DAC_BASE      )
#define LPC_CANAF_RAM         ((LPC_CANAF_RAM_TypeDef *) LPC_CANAF_RAM_BASE)
#define LPC_CANAF             ((LPC_CANAF_TypeDef     *) LPC_CANAF_BASE    )
#define LPC_CANCR             ((LPC_CANCR_TypeDef     *) LPC_CANCR_BASE    )
#define LPC_CAN1              ((LPC_CAN_TypeDef       *) LPC_CAN1_BASE     )
#define LPC_CAN2              ((LPC_CAN_TypeDef       *) LPC_CAN2_BASE     )
#define LPC_MCPWM             ((LPC_MCPWM_TypeDef     *) LPC_MCPWM_BASE    )
#define LPC_QEI               ((LPC_QEI_TypeDef       *) LPC_QEI_BASE      )
#define LPC_EMAC              ((LPC_EMAC_TypeDef      *) LPC_EMAC_BASE     )
#define LPC_GPDMA             ((LPC_GPDMA_TypeDef     *) LPC_GPDMA_BASE    )
#define LPC_GPDMACH0          ((LPC_GPDMACH_TypeDef   *) LPC_GPDMACH0_BASE )
#define LPC_GPDMACH1          ((LPC_GPDMACH_TypeDef   *) LPC_GPDMACH1_BASE )
#define LPC_GPDMACH2          ((LPC_GPDMACH_TypeDef   *) LPC_GPDMACH2_BASE )
#define LPC_GPDMACH3          ((LPC_GPDMACH_TypeDef   *) LPC_GPDMACH3_BASE )
#define LPC_GPDMACH4          ((LPC_GPDMACH_TypeDef   *) LPC_GPDMACH4_BASE )
#define LPC_GPDMACH5          ((LPC_GPDMACH_TypeDef   *) LPC_GPDMACH5_BASE )
#define LPC_GPDMACH6          ((LPC_GPDMACH_TypeDef   *) LPC_GPDMACH6_BASE )
#define LPC_GPDMACH7          ((LPC_GPDMACH_TypeDef   *) LPC_GPDMACH7_BASE )
#define LPC_USB               ((LPC_USB_TypeDef       *) LPC_USB_BASE      )

#endif  // __LPC17xx_H__
