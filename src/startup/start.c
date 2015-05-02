/*==========================================================================
##                   LPC-bootloader
##
##              Copyright(c) 2015-2016 Yoc Ltd. All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      start.c lpc1768Æô¶¯ÎÄ¼þ
##
##--------------------------------------------------------------------------
##
##  Created by   :     yoc
##        Date   :     2015.04.29
##==========================================================================*/



extern void LPC_start(void);

void _start(void);
void default_isr(void);

extern char _mem_stack_base, _mem_stack_end;
extern char _data_lma_start;
extern char _data_start;
extern char _data_end;
extern char _bss_start;
extern char _bss_end;


/*
 * Control IRQs
 */
static inline void __attribute__((used)) __enable_irq(void)
{
	asm volatile ("cpsie i");
}

static inline void __attribute__((used)) __disable_irq(void)
{
	asm volatile ("cpsid i");
}


unsigned int vectors[] __attribute__((section(".vectors"))) = {

	/*
	 * The first word is the stack base address (stack grows downwards)
	 * Stack is defined by reserving an area at high RAM in u-boot.lds.
	 */
	(unsigned long)&_mem_stack_end,

	/*
	 * Reset entry point
	 */
	(unsigned int)&_start,

	/*
	 * Other exceptions
	 */
	(unsigned int)&default_isr
};


 /*
  * Reset entry point
  */
void _start(void)
{
	unsigned int i,len;
	char *src = &_data_lma_start;
	char *dst = &_data_start;
	__disable_irq();

	//Copy data and initialize BSS
	len = &_data_end - &_data_start;
	for(i = 0;i < len;i++){
		*dst++ = *src++;
	}
	
	len = &_bss_end - &_bss_start;
	dst = &_bss_start;
	for(i = 0;i < len;i++){
		*dst++ = 0;
	}
	LPC_start();
	

}



void __attribute__((naked, noreturn)) default_isr(void);
void default_isr(void)
{
	/*
	 * Dump the registers
	 */
	//asm("mov r0, sp; bl dump_ctx");

	/* And hang
	 */
	for (;;) ;
}
