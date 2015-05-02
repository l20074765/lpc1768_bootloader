#include "iap.h"
#include "config.h"


const uint32 crp __attribute__((section(".crp"))) = CRP;

uint32 param_table[5];
uint32 result_table[5];

uint32 *flash_address = 0;
uint8 flash_buf[FLASH_BUF_SIZE];
uint32 byte_ctr = 0;
static uint32 cclk = CCLK;

const uint32 sector_start_map[MAX_FLASH_SECTOR] = {
	SECTOR_0_START,SECTOR_1_START,SECTOR_2_START,SECTOR_3_START,
	SECTOR_4_START,SECTOR_5_START,SECTOR_6_START,SECTOR_7_START,
	SECTOR_8_START,SECTOR_9_START,SECTOR_10_START,SECTOR_11_START,
	SECTOR_12_START,SECTOR_13_START,SECTOR_14_START,SECTOR_15_START,
	SECTOR_16_START,SECTOR_17_START,SECTOR_18_START,SECTOR_19_START,
	SECTOR_20_START,SECTOR_21_START,SECTOR_22_START,SECTOR_23_START,
	SECTOR_24_START,SECTOR_25_START,SECTOR_26_START,SECTOR_27_START,
	SECTOR_28_START,SECTOR_29_START	};

const uint32 sector_end_map[MAX_FLASH_SECTOR] = {
	SECTOR_0_END,SECTOR_1_END,SECTOR_2_END,SECTOR_3_END,
	SECTOR_4_END,SECTOR_5_END,SECTOR_6_END,SECTOR_7_END,
	SECTOR_8_END,SECTOR_9_END,SECTOR_10_END,SECTOR_11_END,
	SECTOR_12_END,SECTOR_13_END,SECTOR_14_END,SECTOR_15_END,
	SECTOR_16_END,SECTOR_17_END,SECTOR_18_END,SECTOR_19_END,
	SECTOR_20_END,SECTOR_21_END,SECTOR_22_END,SECTOR_23_END,
	SECTOR_24_END,SECTOR_25_END,SECTOR_26_END,SECTOR_27_END,
	SECTOR_28_END,SECTOR_29_END			};





static void IAP_entry(uint32 param_tab[],uint32 result_tab[])
{
    void (*iap)(uint32 [],uint32 []);
    iap = (void (*)(uint32 [],uint32 []))IAP_ADDRESS;
    iap(param_tab,result_tab);
}


void IAP_erase_sector(uint32 start_sector,uint32 end_sector,uint32 cclk)
{
    param_table[0] = ERASE_SECTOR;
    param_table[1] = start_sector;
    param_table[2] = end_sector;
    param_table[3] = cclk;
    IAP_entry(param_table,result_table);
}


void IAP_prepare_sector(uint32 start_sector,uint32 end_sector,uint32 cclk)
{
    param_table[0] = PREPARE_SECTOR_FOR_WRITE;
    param_table[1] = start_sector;
    param_table[2] = end_sector;
    param_table[3] = cclk;
    IAP_entry(param_table,result_table);
}



void IAP_write_data(uint32 cclk,uint32 flash_address,uint32 * flash_data_buf, uint32 count)
{

	__disable_irq();
    param_table[0] = COPY_RAM_TO_FLASH;
    param_table[1] = flash_address;
    param_table[2] = (uint32)flash_data_buf;
    param_table[3] = count;
    param_table[4] = cclk;
    IAP_entry(param_table,result_table);
	__enable_irq();
}


void IAP_find_erase_prepare_sector(uint32 cclk, uint32 flash_address)
{
    uint32 i;
	__disable_irq();

    for(i=USER_START_SECTOR;i<=MAX_USER_SECTOR;i++){
        if(flash_address < sector_end_map[i]){
            if( flash_address == sector_start_map[i]){
                IAP_prepare_sector(i,i,cclk);
                IAP_erase_sector(i,i,cclk);
            }
            IAP_prepare_sector(i,i,cclk);
            break;
        }
    }
	__enable_irq();

	
}






uint32 IAP_write_flash(uint32 * dst, uint8 * src, uint32 no_of_bytes)
{
  	uint32 i;
    if (flash_address == 0){
	  /* Store flash start address */
	  flash_address = (uint32 *)dst;
	}
	for( i = 0;i<no_of_bytes;i++ ){
	  flash_buf[(byte_ctr+i)] = *(src+i);
    }
	byte_ctr = byte_ctr + no_of_bytes;

	if( byte_ctr == FLASH_BUF_SIZE){
	  /* We have accumulated enough bytes to trigger a flash write */
	  IAP_find_erase_prepare_sector(cclk, (uint32)flash_address);
      if(result_table[0] != CMD_SUCCESS){
        while(1); /* No way to recover. Just let Windows report a write failure */
      }
      IAP_write_data(cclk,(uint32)flash_address,(uint32 *)flash_buf,FLASH_BUF_SIZE);
      if(result_table[0] != CMD_SUCCESS){
        while(1); /* No way to recover. Just let Windows report a write failure */
      }
	  /* Reset byte counter and flash address */
	  byte_ctr = 0;
	  flash_address = 0;
	}
    return(CMD_SUCCESS);
}




void IAP_erase_user_flash(void)
{
    IAP_prepare_sector(USER_START_SECTOR,MAX_USER_SECTOR,cclk);
    IAP_erase_sector(USER_START_SECTOR,MAX_USER_SECTOR,cclk);
	if(result_table[0] != CMD_SUCCESS){
      while(1); /* No way to recover. Just let Windows report a write failure */
    }
}



uint32 IAP_user_code_present(void)
{
    param_table[0] = BLANK_CHECK_SECTOR;
    param_table[1] = USER_START_SECTOR;
    param_table[2] = USER_START_SECTOR;
    IAP_entry(param_table,result_table);
	if( result_table[0] == CMD_SUCCESS ){
	    return (0);
	}
	else{
	    return (1);
	}
}


void boot_jump( uint32 address ){
	asm volatile ("ldr sp,[r0]");	//Load new stack pointer address								
	asm volatile ("ldr pc,[r0,#4]");	//Load new program counter address
}


void IAP_execute_user_code(void)
{
	/* Change the Vector Table to the USER_FLASH_START 
	in case the user application uses interrupts */
	SCB->VTOR = USER_FLASH_START & 0x1FFFFF80;
	boot_jump(USER_FLASH_START);
}

