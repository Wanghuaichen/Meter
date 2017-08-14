#include "data.h"
#include "string.h"
#include "init.h"
extern u8 data_num[12][12];
u8 data_update(u8 meter_id,Meter *met)
{
  LED_Set(UP,0);
	meter_1_data_updata(meter_id,met);
	LED_Set(UP,1);
}

//update meter_1 data
u8 meter_1_data_updata(u8 id,Meter  * met)
{
  u8 str[12]={0};
	u8 i=0;
	pack_meter_value(id,met);                 //get meter value package
	
	for(i=0;i<12;i++){data_num[11][i]= data_num[10][i];}
	for(i=0;i<12;i++){data_num[10][i]= data_num[9][i];}
	for(i=0;i<12;i++){data_num[9][i]= data_num[8][i];}
	for(i=0;i<12;i++){data_num[8][i]= data_num[7][i];}
	for(i=0;i<12;i++){data_num[7][i]= data_num[6][i];}
	for(i=0;i<12;i++){data_num[6][i]= data_num[5][i];}
	for(i=0;i<12;i++){data_num[5][i]= data_num[4][i];}
	for(i=0;i<12;i++){data_num[4][i]= data_num[3][i];}
	for(i=0;i<12;i++){data_num[3][i]= data_num[2][i];}
	for(i=0;i<12;i++){data_num[2][i]= data_num[1][i];}
	for(i=0;i<12;i++){data_num[1][i]= data_num[0][i];}
	
	for(i=0;i<12;i++){data_num[0][i]= (*met).value_package[i];}
	//INTX_DISABLE();
	switch(id)
	{
		case 1:STMFLASH_Write(FLASH_DATA_ADDR_M1_1,(u16*)data_num,72);break;
		case 2:STMFLASH_Write(FLASH_DATA_ADDR_M2_1,(u16*)data_num,72);break;	
		case 3:STMFLASH_Write(FLASH_DATA_ADDR_M3_1,(u16*)data_num,72);break;	
		case 4:STMFLASH_Write(FLASH_DATA_ADDR_M4_1,(u16*)data_num,72);break;	
		case 5:STMFLASH_Write(FLASH_DATA_ADDR_M5_1,(u16*)data_num,72);break;	
		case 6:STMFLASH_Write(FLASH_DATA_ADDR_M6_1,(u16*)data_num,72);break;	
		case 7:STMFLASH_Write(FLASH_DATA_ADDR_M7_1,(u16*)data_num,72);break;	
		case 8:STMFLASH_Write(FLASH_DATA_ADDR_M8_1,(u16*)data_num,72);break;	
		case 9:STMFLASH_Write(FLASH_DATA_ADDR_M9_1,(u16*)data_num,72);break;	
		case 10:STMFLASH_Write(FLASH_DATA_ADDR_M10_1,(u16*)data_num,72);break;	
		case 11:STMFLASH_Write(FLASH_DATA_ADDR_M11_1,(u16*)data_num,72);break;	
		case 12:STMFLASH_Write(FLASH_DATA_ADDR_M12_1,(u16*)data_num,72);break;	
		case 13:STMFLASH_Write(FLASH_DATA_ADDR_M13_1,(u16*)data_num,72);break;	
		case 14:STMFLASH_Write(FLASH_DATA_ADDR_M14_1,(u16*)data_num,72);break;	
		case 15:STMFLASH_Write(FLASH_DATA_ADDR_M15_1,(u16*)data_num,72);break;	
		case 16:STMFLASH_Write(FLASH_DATA_ADDR_M16_1,(u16*)data_num,72);break;	
		case 17:STMFLASH_Write(FLASH_DATA_ADDR_M17_1,(u16*)data_num,72);break;	
		case 18:STMFLASH_Write(FLASH_DATA_ADDR_M18_1,(u16*)data_num,72);break;	
		case 19:STMFLASH_Write(FLASH_DATA_ADDR_M19_1,(u16*)data_num,72);break;	
		case 20:STMFLASH_Write(FLASH_DATA_ADDR_M20_1,(u16*)data_num,72);break;	
		case 21:STMFLASH_Write(FLASH_DATA_ADDR_M21_1,(u16*)data_num,72);break;	
		case 22:STMFLASH_Write(FLASH_DATA_ADDR_M22_1,(u16*)data_num,72);break;	
		case 23:STMFLASH_Write(FLASH_DATA_ADDR_M23_1,(u16*)data_num,72);break;	
		case 24:STMFLASH_Write(FLASH_DATA_ADDR_M24_1,(u16*)data_num,72);break;	
		case 25:STMFLASH_Write(FLASH_DATA_ADDR_M25_1,(u16*)data_num,72);break;	
		case 26:STMFLASH_Write(FLASH_DATA_ADDR_M26_1,(u16*)data_num,72);break;	
		case 27:STMFLASH_Write(FLASH_DATA_ADDR_M27_1,(u16*)data_num,72);break;	
		case 28:STMFLASH_Write(FLASH_DATA_ADDR_M28_1,(u16*)data_num,72);break;	
		case 29:STMFLASH_Write(FLASH_DATA_ADDR_M29_1,(u16*)data_num,72);break;	
		case 30:STMFLASH_Write(FLASH_DATA_ADDR_M30_1,(u16*)data_num,72);break;	
		case 31:STMFLASH_Write(FLASH_DATA_ADDR_M31_1,(u16*)data_num,72);break;	
		case 32:STMFLASH_Write(FLASH_DATA_ADDR_M32_1,(u16*)data_num,72);break;	
		default : printf("data write flash failed\r\n");break;
	}
	//INTX_ENABLE();
	copy_package(str,(*met).value_package);
	
#ifdef DEBUG
	printf("meter %d data in flash: ",id);
  printf(str);
  printf("\r\n");
  printf("meter %d updata successful\r\n",id);
#endif
}


u8 copy_package(u8 *str1,u8 *str2)
{
	int num =0;
	for(num=0;num<12;num++)
	{
	    *str1=*str2;
		   str1++;
		   str2++;
	}
}