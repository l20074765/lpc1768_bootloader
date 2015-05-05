#include "ymodem.h"
#include "ymodemApi.h"
#include "config.h"
#include "uart0.h"
#include "iap.h"
#include "string.h"
#include "timer.h"


uint16		FileLength;
uint16		Y_TimeOut,WaitTime;
uint8		packets_received, session_begin;	
uint8		file_name[FILE_NAME_LENGTH];
uint8		file_size[FILE_SIZE_LENGTH];
uint8		StartCode[3];
uint16		FlashDestination;
uint16		RxCnt;
uint8		HandCnt;
uint32		DownCheckSum,FlashCheckSum;

#define YMODEM_BUF_SIZE	1032
static	uint16 		recvcnt = 0;
static	uint8		recvbuf[YMODEM_BUF_SIZE];

static	uint8		wrFlashBuf[1024];
static	uint16		wrFlashIndex = 0;


uint8	    GucIapTmp[ IAP_BUF_LENGTH ] = "";
uint32      IAP_Flash_Address    = 0x00006000;

//清除扇区
void SetFlashBlank( void )
{
	uint8 i;
	__disable_irq();
	IAP_prepare_sector( USER_START_SECTOR, MAX_USER_SECTOR);

	
	
	IAP_Flash_Address = USER_FLASH_START;
	__enable_irq();
	
	
		
    	
}

//将数据写入flash
uint8 IAPWriteData( uint8 *dataSrc, uint32 dataLen )
{
	uint8 i;
	uint32    writelen = IAP_BUF_LENGTH;
	
	__disable_irq();
	memset( GucIapTmp, 0,   IAP_BUF_LENGTH );

	memcpy( GucIapTmp, dataSrc, dataLen );
	
	if ( dataLen <= 4096ul ){
		writelen = 4096ul;
	}
	if ( dataLen <= 1024ul ){
		writelen = 1024ul;
	}
	if ( dataLen <= 512ul ){
		writelen = 512ul;
	}
	if ( dataLen <= 256ul ){
		writelen = 256ul;
	}
	
	
	IAP_prepare_sector(USER_START_SECTOR, MAX_USER_SECTOR);
	IAP_write_flash((uint32 *)IAP_Flash_Address,(uint8 *)GucIapTmp, writelen); // 写数据到扇区

	


	__enable_irq();


	IAP_Flash_Address += writelen;

	return 1;
}





void	UART1_RxPackage(void)
{
	uint32	j;	
	RxCnt = 0;
	for(j = 0;	j < 9300; j++)	
	{
		if(!uart0_IsEmpty())
		{
			recvbuf[RxCnt] = uart0_getChar();
			if(++RxCnt >= 1032)	RxCnt = 0;
			j = 0;	
		}
		
	}
}


uint16 Str2Int(uint8 *inputstr)
{
	uint16	val;
	uint8	i;
	
	val = 0;
	for (i = 0; i < 5; i++)
	{
		if((inputstr[i] < '0') || (inputstr[i] > '9'))	break;
		val = val * 10 + inputstr[i] - '0';
	}
	return val;
}



void	Tx_DEC_U16(uint16 j)
{
	uint8	i;
	uint8	tmp[10];
	for(i=4; i<5; i--)	tmp[i] = j % 10 + '0',	j = j / 10;
	for(i=0; i<4; i++)
	{
		if(tmp[i] != '0')	break;
		tmp[i] = ' ';
	}
	for(i=0; i<5; i++)	uart0_putChar(tmp[i]);
}



void	Tx_HEX_U32(uint32 j)
{
	uint8	i,k;
	uint8	tmp[10];
	for(i=8; i>0; i--)
	{
		k = ((uint8)j) & 0x0f;
		if(k <= 9)	tmp[i] = k+'0';
		else		tmp[i] = k-10+'A';
		j >>= 4;
	}
	for(i=1; i<9; i++)	uart0_putChar(tmp[i]);
}



void	ReturnNameAndLength(void)
{
	uint16	i;
	uart0_putStr("================================\r\n File name:     ",
		sizeof("================================\r\n File name:     "));
	for(i=0; i<FILE_NAME_LENGTH; i++)	
	{
		if(file_name[i] == 0)	break;
		uart0_putChar(file_name[i]);
	}
	uart0_putStr("\r\n File length:   ",
		sizeof("\r\n File length:   "));
	Tx_DEC_U16(FileLength);
	uart0_putStr(" Bytes\r\n DownChexkSum:  ",
		sizeof(" Bytes\r\n DownChexkSum:  "));
	Tx_HEX_U32(DownCheckSum);
	uart0_putStr("\r\n ISP Versiom:   2015-5-05 by Yoc   ",
		sizeof("\r\n ISP Versiom:   2013-4-29 by Coody"));
	uart0_putStr("\r\n================================\r\n\r\n",
		sizeof("\r\n================================\r\n\r\n"));
}



uint8 uart1GetCh(uint8 *ch,uint16 timeout) //ms
{
	uint16 i = (timeout <= 20) ?  1 : timeout / 20;
	while(i){
		if(uart0_IsEmpty()){
			delayMs(20);
			i--;
		}
		else{
			*ch = uart0_getChar();
			return 1;
		}
	}
	return 0;
}

#define YStart			0
#define YDataTrans		1
#define YEOT			2

#define Y_TIMEOUT   100


uint8 uart_download(void)
{
	uint16	i;
	uint8 res,ch,rcx = 0;
	uint16 recvlen;
	uint8  ymodemState = YStart;
	while(1){
		if(ymodemState == YStart){
			uart0_putChar(CRC16);//发送起始信号
			res = uart1GetCh(&ch,1000);//接收等待超时1秒
			if(res == 1){
				if(ch == SOH || ch == STX){ //128数据包  or 1024数据包
					recvlen = (ch == SOH) ? 128 : 1024;
					res = uart1GetCh(&ch,Y_TIMEOUT);
					if(ch != 0x00){
						//return 3;
					}
					res = uart1GetCh(&ch,Y_TIMEOUT);
					if(ch != 0xFF){
						//return 3;
					}
					for(i = 0;i < recvlen;i++){ //接收第一个数据包 为文件名数据包
						res = uart1GetCh(&ch,Y_TIMEOUT);
						if(res == 1){
							recvbuf[i] = ch;
						}
					}

					memset(file_name,0,sizeof(file_name));
					for(i = 0;i < recvlen;i++){
						if(recvbuf[i] == 0){
							break;
						}
						else{
							file_name[i] = ch;
							FileLength = i + 1;
						}
					}
					
					//接收校验码 暂不校验
					res = uart1GetCh(&ch,Y_TIMEOUT);
					res = uart1GetCh(&ch,Y_TIMEOUT);
					
					
					//调用子程序
					SetFlashBlank();
					wrFlashIndex = 0;
					memset(wrFlashBuf,0,sizeof(wrFlashBuf));
					uart0_putChar(ACK);//擦除完成 发送确认信号
					ymodemState=YDataTrans;//切换为数据接收状态
					uart0_putChar(CRC16); //在发送C 正式启动数据传输
				}
			}
			else{ 
				if(rcx++ > 50){
					return 0x10;
				}
				else{
					//uart1PutChar(NAK);//数据发送错误 请求重发
				}
			}

		}
		else if(ymodemState == YDataTrans){ //数据接收阶段
			res = uart1GetCh(&ch,Y_TIMEOUT);
			if(res != 1){
				uart0_putChar(NAK);
				continue;
			}
			if(ch == EOT){//收到EOT, 结束
				ymodemState = YEOT;
				if(wrFlashIndex > 0){
					IAPWriteData(wrFlashBuf, 256);
					wrFlashIndex == 0;
				}
				uart0_putChar(ACK);
			}
			else if(ch == SOH || ch == STX){ //接收数据包
				recvlen = (ch == SOH) ? 128 : 1024;
				res = uart1GetCh(&ch,Y_TIMEOUT);
				res = uart1GetCh(&ch,Y_TIMEOUT);
				for(i = 0;i < recvlen;i++){ //接收一个数据包 
					res = uart1GetCh(&ch,Y_TIMEOUT);
					recvbuf[i] = ch;
				}
				res = uart1GetCh(&ch,Y_TIMEOUT);//crc
				res = uart1GetCh(&ch,Y_TIMEOUT);
				//处理数据包
				for(i = 0;i < recvlen;i++){
					wrFlashBuf[wrFlashIndex++] = recvbuf[i];
					if(wrFlashIndex >= 256){
						IAPWriteData(wrFlashBuf, 256);
						memset(wrFlashBuf,0,1024);
						wrFlashIndex = 0;
					}
				}
				
				
				uart0_putChar(ACK);//保存完成 发送确认信号
			}
			else if(ch == CANCEL){
				return 2;
			}
		}
		else if(ymodemState == YEOT){ //传输结束阶段
			uart0_putChar(CRC16);
			res = uart1GetCh(&ch,1000);
			if(ch == SOH){
				res = uart1GetCh(&ch,Y_TIMEOUT);
				res = uart1GetCh(&ch,Y_TIMEOUT);
				for(i = 0;i < 128;i++){
					res = uart1GetCh(&ch,Y_TIMEOUT);
				}
				
				res = uart1GetCh(&ch,Y_TIMEOUT);//crc
				res = uart1GetCh(&ch,Y_TIMEOUT);
				uart0_putChar(ACK);
				return 1;
			}
			else{
				return 2;
			}
			
		}
		else{
			return 0x20;
		}
	}
	
	
}

