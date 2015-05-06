/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           uart0.h
** Last modified Date:  2013-01-04
** Last Version:         
** Descriptions:        uart0驱动程序相关函数声明                      
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-04
** Version:             V0.1 
** Descriptions:        The original version
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:        
********************************************************************************************************/
#ifndef __UART0_H 
#define __UART0_H

#include "common.h"

void uart0_init (uint32 baud);
void uart0_putChar(uint8 ch);
void uart0_putStr(uint8 *str, uint32 len);
uint8 uart0_IsEmpty(void);
uint8 uart0_getChar(void);
void uart0_clear(void) ;


#endif
/**************************************End Of File*******************************************************/
