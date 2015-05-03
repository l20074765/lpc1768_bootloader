/*==========================================================================
##                   LPC-bootloader
##
##              Copyright(c) 2015-2016 Yoc Ltd. All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      uart0.h lpc1768通用头文件 与移植相关
##
##--------------------------------------------------------------------------
##
##  Created by   :     yoc
##        Date   :     2015.04.29
##==========================================================================*/

#include "config.h"
#include "board.h"
#include <string.h>

#define	_DEBUG_TRACE
//#define	UART0_BPS			9600
#define	UART0_BUF_LEN		128

volatile uint8 uart0_buf[UART0_BUF_LEN];
volatile uint8 uart0_rd;
volatile uint8 uart0_wr;

/*********************************************************************************************************
** Function name:     	InitUart0
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为9600
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uart0_init (uint32 baud)
{
    uint32 ulFdiv; 
	LPC_SC->PCONP  |= (1 << 3);              	/* Enable power to Uart0 block  */
	LPC_PINCON->PINSEL0 &= ~(0x0F << 4);   
	LPC_PINCON->PINSEL0 |= (0x01 << 6) | (0x01 << 4); //配置管脚为串口功能
	LPC_PINCON->PINMODE0 &= ~(0x0F << 4); //上拉 
    LPC_UART0->LCR = 0x83;                                                  //允许设置波特率
    ulFdiv = (FPCLK / 16) / baud;                              //设置波特率
    LPC_UART0->DLM  = ulFdiv / 256;
    LPC_UART0->DLL  = ulFdiv % 256; 
    LPC_UART0->LCR  = 0x03;                                                  //锁定波特率
    LPC_UART0->FCR  = 0x87;                                                  //使能FIFO，设置8个字节触发点
    LPC_UART0->IER  = 0x01;                                                  //使能接收中断
	uart0_rd  = 0;
	uart0_wr  = 0;
	memset((void *)uart0_buf,0x00,UART0_BUF_LEN);				//初始化缓冲区

}
/*********************************************************************************************************
* Function Name:        uart0_isrHandler
* Description:          UART0 中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void uart0_isrHandler (void)
{
	#if 0
	unsigned char Num;
	unsigned char rxd_head;
	unsigned char rxd_data;
	
	//OS_ENTER_CRITICAL();
	OSIntEnter();      
    while((U0IIR & 0x01) == 0)                          			//判断是否有中断挂起
	{
        switch(U0IIR & 0x0E) 										//判断中断标志
		{                                         
            case 0x04 : for (Num = 0; Num < 8; Num++)				//接收数据中断
						{
		                	rxd_data = U0RBR;
							rxd_head = (Uart0RxdHead + 1);
					        if( rxd_head >= UART0BUFFERLEN ) 
					           	rxd_head = 0;
					        if( rxd_head != Uart0RxdTail) 
					        {
					           	Uart0RevBuff[Uart0RxdHead] = rxd_data;
					           	Uart0RxdHead = rxd_head;
					        }
		                }
		                break;
            case 0x0C : while((U0LSR & 0x01) == 0x01)				//字符超时中断，判断数据是否接收完毕
						{                         
		                	rxd_data = U0RBR;
							rxd_head = (Uart0RxdHead + 1);
					        if( rxd_head >= UART0BUFFERLEN ) 
					           	rxd_head = 0;
					        if( rxd_head != Uart0RxdTail) 
					        {
					           	Uart0RevBuff[Uart0RxdHead] = rxd_data;
					           	Uart0RxdHead = rxd_head;
					        }
		                }
		                break;
            default	: break;
        }
    }
    OSIntExit();
    //OS_EXIT_CRITICAL();
	#endif
}
/*********************************************************************************************************
** Function name:	    uart0_putChar
** Descriptions:	    向串口发送子节数据，并等待数据发送完成，使用查询方式
** input parameters:    ch:要发送的数据
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uart0_putChar(uint8 ch)
{
    LPC_UART0->THR = ch;                                                      //写入数据
    while((LPC_UART0->LSR & 0x20) == 0);                                      //等待数据发送完毕
}

/*********************************************************************************************************
** Function name:	    Uart0PutStr
** Descriptions:	    向串口发送字符串
** input parameters:    Str:  要发送的字符串指针
**                      Len:   要发送的数据个数
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uart0_putStr(uint8 *str, uint32 len)
{
    uint32 i;  
    for (i=0;i<len;i++) {
        uart0_putChar(*str++);
    }
}
/*********************************************************************************************************
** Function name:	    uart0_IsEmpty
** Descriptions:	    判断缓冲区是否非空
** input parameters:    无
** output parameters:   无
** Returned value:      1：非空；0：空
*********************************************************************************************************/
uint8 uart0_IsEmpty(void)
{
	return (uart0_rd == uart0_wr);
}


/*********************************************************************************************************
** Function name:     	uart0_clear
** Descriptions:	    清除串口0接收缓冲区
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uart0_clear(void) 
{
	uart0_rd = 0;
	uart0_wr = 0;
}	



/*********************************************************************************************************
** Function name:	    uart0_getChar
** Descriptions:	    从串口缓冲区读取一个字节，读之前需要判断缓冲区非空
** input parameters:    无
** output parameters:   无
** Returned value:      读取到的数据
*********************************************************************************************************/
uint8 uart0_getChar(void)
{
    uint8 ch;
    ch = uart0_buf[uart0_rd++];
	uart0_rd = uart0_rd % UART0_BUF_LEN;
	return ch;
}


/**************************************End Of File*******************************************************/
