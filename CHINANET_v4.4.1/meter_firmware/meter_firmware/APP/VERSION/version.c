#include "version.h"
#include "init.h"
extern int meter_databack_count;
extern int nb_databack_count;
extern u8 meter_databack[50];
extern volatile u8 fm_version[32];
u8 setVersion(u8 id,Meter* met)
{
	u8 command_meter[17];
	u8 i=0;
	u8 flag_68=0;
  u8 data_back_send[50]={0};
	uart1_init(2400);	
	meter_cost_code_calculate(id,met);
	RS485_Set(Write);
	meter_databack_count = 0;
	memset(USART1_RX_BUF, 0,200);
	meter_databack[0] = 0;meter_databack[1] = 0;meter_databack[2] = 0;meter_databack[3] = 0;meter_databack[4] = 0;meter_databack[5] = 0;meter_databack[6] = 0;meter_databack[7] = 0;meter_databack[8] = 0;meter_databack[9] = 0;meter_databack[10] = 0;meter_databack[11] = 0;meter_databack[12] = 0;meter_databack[13] = 0;meter_databack[14] = 0;meter_databack[15] = 0;meter_databack[16] = 0;meter_databack[17] = 0;meter_databack[18] = 0;
	UART1_Print((*met).cost_code);	
	RS485_Set(Read);
	meter_databack_count = 0;
  delay_ms(500);
	for(i=0;i<50;i++)
	{
		data_back_send[i] = meter_databack[i];
	}
	flag_68 = 0;
	for(i=0;i<50;i++)
	{
		if(data_back_send[i]==0X68)flag_68++;
	}
	if(flag_68>=2) 
	{
		flag_68 = 0;
		fm_version[id-1] = 'A';
		STMFLASH_Write(FLASH_FM_VERSION,(u16*)fm_version,32);
#ifdef DEBUG
		printf("version:2007\\r\n");
#endif
		return 1;
	}
	uart1_init(1200);	
	getVersion(id,met);
	RS485_Set(Write);
	meter_databack_count = 0;
	memset(USART1_RX_BUF, 0,200);
	meter_databack[0] = 0;meter_databack[1] = 0;meter_databack[2] = 0;meter_databack[3] = 0;meter_databack[4] = 0;meter_databack[5] = 0;meter_databack[6] = 0;meter_databack[7] = 0;meter_databack[8] = 0;meter_databack[9] = 0;meter_databack[10] = 0;meter_databack[11] = 0;meter_databack[12] = 0;meter_databack[13] = 0;meter_databack[14] = 0;meter_databack[15] = 0;meter_databack[16] = 0;meter_databack[17] = 0;meter_databack[18] = 0;
	UART1_Print((*met).cost_code);	
	RS485_Set(Read);
	meter_databack_count = 0;
  delay_ms(500);
	for(i=0;i<50;i++)
	{
		data_back_send[i] = meter_databack[i];
	}
	flag_68 = 0;
	for(i=0;i<50;i++)
	{
		if(data_back_send[i]==0X68)flag_68++;
	}
	if(flag_68>=1) 
	{
		flag_68 = 0;
		fm_version[id-1] = 'B';
		STMFLASH_Write(FLASH_FM_VERSION,(u16*)fm_version,32);
#ifdef DEBUG
		printf("version:1997\\r\n");
#endif
		return 2;
	}
	else 
#ifdef DEBUG
		printf("version:unkonw\\r\n");
	  UART3_Print(data_back_send);
#endif
		return 0;
  	
}
u8 getVersion(u8 id,Meter* met)
{
	 u8 str[50];
	 int i=0;
   read_meter_addr(id,met);
   str[0] = 0x68;
   str[1] = ((*met).maddr[10]-'0')*16+(*met).maddr[11]-'0';
	 str[2] = ((*met).maddr[8]-'0')*16+(*met).maddr[9]-'0';
   str[3] = ((*met).maddr[6]-'0')*16+(*met).maddr[7]-'0';
	 str[4] = ((*met).maddr[4]-'0')*16+(*met).maddr[5]-'0';
	 str[5] = ((*met).maddr[2]-'0')*16+(*met).maddr[3]-'0';
	 str[6] = ((*met).maddr[0]-'0')*16+(*met).maddr[1]-'0';
	 str[7] = 0x68;
	 str[8] = 0x01;
	 str[9] = 0x02;
	 str[10]= 0x43;
	 str[11]= 0xC3;
	 str[12]=str[0]+str[1]+ str[2]+ str[3]+ str[4]+ str[5]+ str[6]+ str[7]+ str[8]+ str[9]+ str[10]+ str[11];
	 str[13]=0x16;
	 str[14]='\n';
   for(i=0;i<16;i++)
	 (*met).cost_code[i]=str[i];
#ifdef DEBUG
	  printf("meter_cost_code_calculate successful\r\n");
#endif
}