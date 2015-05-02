/*==========================================================================
##                   LPC-bootloader
##
##              Copyright(c) 2015-2016 Yoc Ltd. All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      common.h lpc1768通用头文件 与移植相关
##
##--------------------------------------------------------------------------
##
##  Created by   :     yoc
##        Date   :     2015.04.29
##==========================================================================*/

#ifndef _COMMON_H_
#define _COMMON_H_


typedef unsigned char 	uint8;
typedef unsigned short  uint16;
typedef unsigned int  	uint32;
typedef unsigned long  	uint64;
typedef char 			int8;
typedef short 			int16;
typedef int 			int32;
typedef long 			int64;


/*********************************************************************************************************
**定义通用宏函数
*********************************************************************************************************/

#define HUINT16(v)   	(((v) >> 8) & 0xFF)
#define LUINT16(v)   	((v) & 0xFF)
#define INTEG16(h,l)  	(((uint16)h << 8) | l)
#define H0UINT32(v)		(((v) >> 24) & 0xFF)
#define H1UINT32(v)		(((v) >> 16) & 0xFF)
#define L0UINT32(v)		(((v) >> 8) & 0xFF)
#define L1UINT32(v)		((v) & 0xFF)
#define INTEG32(h0,h1,l0,l1)  	((((uint32)(h0)) << 24)| \
								(((uint32)(h1)) << 16) | \
								(((uint32)(l0)) << 8)  |  ((uint32)(l1)))





#endif

