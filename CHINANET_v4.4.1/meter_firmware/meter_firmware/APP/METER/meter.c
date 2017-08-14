#include "meter.h"
#include "usart.h"
#include "init.h"
#include "flash.h"
#include "led.h"
#include "version.h"
//u8 cut[29] =  {0x68, 0x98, 0x99, 0x21, 0x00, 0x00, 0x00, 0x68, 0x1C, 0x10, 0x35, 0x33, 0x33, 0x33, 0x63, 0x63, 0x63, 0x63, 0x4D, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x5A,0x16,'\n'};
//u8 con[29] =  {0x68, 0x98, 0x99, 0x21, 0x00, 0x00, 0x00, 0x68, 0x1C, 0x10, 0x35, 0x33, 0x33, 0x33, 0x63, 0x63, 0x63, 0x63, 0x4E, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x5B, 0x16,'\n'}; //"68 73 98 21 00 00 00 68 1C 10 35 33 33 33 63 63 63 63 4E 33 33 33 33 33 33 33 35 16"}; //??
//u8 readdushu[17]     = {0x68, 0x98, 0x99, 0x21, 0x00, 0x00, 0x00, 0x68, 0x11, 0x04, 0x33, 0x33, 0x34, 0x33, 0x04, 0x16,'\n'}; //????
//u8 readvoltage[17]   = {0x68, 0x98, 0x99, 0x21, 0x00, 0x00, 0x00, 0x68, 0x11, 0x04, 0x33, 0x34, 0x34, 0x35, 0x07, 0x16,'\n'}; //????
//u8 readcurrent[17]   = {0x68, 0x98, 0x99, 0x21, 0x00, 0x00, 0x00, 0x68, 0x11, 0x04, 0x33, 0x34, 0x35, 0x35, 0x08, 0x16,'\n'}; //????

u8 meter_databack[100] = {0};
u8 nb_databack[50] = {0};




int meter_databack_count = 0;
int nb_databack_count = 0;
extern volatile u8 fm_version[32];

u8 meter_cutoff(u8 meter_id,Meter * met)
{
	u16 time=0;
	meter_cut_code_calculate(meter_id,met);
	RS485_Set(Write);
	meter_databack_count = 0;
	UART1_Print((*met).cut_code);	
	RS485_Set(Read);
	meter_databack_count = 0;
	while((!((meter_databack[meter_databack_count]==0x16)&&(meter_databack_count>=10)))&&(time<=10000))
	{
	  mydelay_us(50);
    time ++;
	}
	delay_ms(10);
}

u8 meter_connect(u8 meter_id,Meter * met)
{	
	u16 time=0;
	meter_con_code_calculate(meter_id,met);
	RS485_Set(Write);
	meter_databack_count = 0;
	UART1_Print((*met).connect_code);	
	RS485_Set(Read);
	meter_databack_count = 0;
	while((!((meter_databack[meter_databack_count]==0x16)&&(meter_databack_count>=10)))&&(time<=10000))
	{
	  mydelay_us(50);
    time ++;
	}
	delay_ms(10);
}

u8 meter_read_cost(u8 meter_id,Meter * met)	
{	
	u16 time=0;
	u8 i =0;
	u8 data_back_send[50];
	meter_cost_code_calculate(meter_id,met);
	RS485_Set(Write);
	meter_databack_count = 0;
	UART1_Print((*met).cost_code);	
	RS485_Set(Read);
	meter_databack_count = 0;
  delay_ms(500);
	for(i=0;i<50;i++)
	{
		data_back_send[i] = meter_databack[i];
	}
	for(i=0;i<50;i++)
	{
		if((data_back_send[i]==0X68)&&i<6)
		break;
	}
	(*met).cost_value[0]  = meter_databack[i+14];
  (*met).cost_value[1]  = meter_databack[i+15];
  (*met).cost_value[2]  = meter_databack[i+16];	
	(*met).cost_value[3]  = meter_databack[i+17];	
	(*met).cost_value[4]  = '\n';	
	delay_ms(10);
}

u8 meter_read_voltage(u8 meter_id,Meter * met)
{	
	u16 time=0;
  u8 i =0;
	u8 data_back_send[50];
	meter_voltage_code_calculate(meter_id,met);
	RS485_Set(Write);
	meter_databack_count = 0;
	UART1_Print((*met).voltage_code);	
	RS485_Set(Read);
	meter_databack_count = 0;
	while((!((meter_databack[meter_databack_count]==0x16)&&(meter_databack_count>=10)))&&(time<=10000))
	{
	  mydelay_us(50);
    time ++;
	}
		for(i=0;i<50;i++)
	{
		data_back_send[i] = meter_databack[i];
	}
	for(i=0;i<50;i++)
	{
		if((data_back_send[i]==0X68)&&i<6)
		break;
	}
	(*met).voltage_value[0]  = meter_databack[i+14];
  (*met).voltage_value[1]  = meter_databack[i+15];
	(*met).voltage_value[2]  = '\n';
	delay_ms(10);
}

u8 meter_read_current(u8 meter_id,Meter * met)
{	
	u16 time=0;
	u8 i =0;
	u8 data_back_send[50];
	meter_current_code_calculate(meter_id,met);
	RS485_Set(Write);
	meter_databack_count = 0;
	UART1_Print((*met).current_code);	
	RS485_Set(Read);
	meter_databack_count = 0;
	while((!((meter_databack[meter_databack_count]==0x16)&&(meter_databack_count>=10)))&&(time<=10000))
	{
	  mydelay_us(50);
    time ++;
	}
			for(i=0;i<50;i++)
	{
		data_back_send[i] = meter_databack[i];
	}
	for(i=0;i<50;i++)
	{
		if((data_back_send[i]==0X68)&&i<6)
		break;
	}
	(*met).current_value[0]  = meter_databack[i+14];
  (*met).current_value[1]  = meter_databack[i+15];
  (*met).current_value[2]  = meter_databack[i+16];	
	(*met).current_value[3]  = '\n';
	delay_ms(10);
}

u8 meter_read_all_value(u8 meter_id,Meter * met)
 {
	 
  meter_read_cost(meter_id,met);	
 	meter_read_current(meter_id,met);	
	meter_read_voltage(meter_id,met);	
	#ifdef DEBUG
	printf("meter data read successful\r\n");
	#endif
}
 u8 meter_read_1997_value(u8 meter_id,Meter * met)
 {
  u16 time=0;
	u8 i =0;
	u8 data_back_send[50];
	u8 meter1997Flag[7] ={22,0,0,0,0,0};
	u8 * data1997;
  USART_Cmd(USART2, DISABLE); 
	getVersion(meter_id,met);
	RS485_Set(Write);
	meter_databack_count = 0;
	memset(USART1_RX_BUF, 0,200);
	for(i=0;i<100;i++)
	meter_databack[i] = 0;
	UART1_Print((*met).cost_code);	
	RS485_Set(Read);
  delay_ms(500);
	for(i=0;i<50;i++)
	{
		data_back_send[i] = meter_databack[i];
	}
		for(i=0;i<40;i++)
	{
		if((data_back_send[i]==meter1997Flag[0])&&(data_back_send[i+1]==meter1997Flag[1])&&(data_back_send[i+2]==meter1997Flag[2])&&(data_back_send[i+3]==meter1997Flag[3])&&(data_back_send[i+4]==meter1997Flag[4])&&(data_back_send[i+5]==meter1997Flag[5])&&(data_back_send[i+6]==meter1997Flag[6]))
		break;
	}
	if(i>5)
	{
	    (*met).cost_value[0]  = data_back_send[i-5];
      (*met).cost_value[1]  = data_back_send[i-4];
      (*met).cost_value[2]  = data_back_send[i-3];
	    (*met).cost_value[3]  = data_back_send[i-2];
	    (*met).cost_value[4]  = '\n';	
	}
		
	delay_ms(10);
	#ifdef DEBUG
	printf("meter data read successful\r\n");
	#endif
	 USART_Cmd(USART2, ENABLE); 
}
u8 meter_data_updata(u8 meter_id,Meter * met)
 {
 ;
	   //  copy_Str2_to_Str1(meter.voltage_value,met.voltage_value);
 }
u8 read_meter_addr(u8 meter_id,Meter * met)             //read meter addr from flash
 {
	 switch(meter_id)
	 {
		 case 1: STMFLASH_Read(FLASH_ADDR_M1,(u16*)((*met).maddr),6);break;
		 case 2: STMFLASH_Read(FLASH_ADDR_M2,(u16*)((*met).maddr),6);break;
		 case 3: STMFLASH_Read(FLASH_ADDR_M3,(u16*)((*met).maddr),6);break;
		 case 4: STMFLASH_Read(FLASH_ADDR_M4,(u16*)((*met).maddr),6);break;
		 case 5: STMFLASH_Read(FLASH_ADDR_M5,(u16*)((*met).maddr),6);break;
		 case 6: STMFLASH_Read(FLASH_ADDR_M6,(u16*)((*met).maddr),6);break;
		 case 7: STMFLASH_Read(FLASH_ADDR_M7,(u16*)((*met).maddr),6);break;
		 case 8: STMFLASH_Read(FLASH_ADDR_M8,(u16*)((*met).maddr),6);break;
		 case 9: STMFLASH_Read(FLASH_ADDR_M9,(u16*)((*met).maddr),6);break;
		 case 10: STMFLASH_Read(FLASH_ADDR_M10,(u16*)((*met).maddr),6);break;
		 case 11: STMFLASH_Read(FLASH_ADDR_M11,(u16*)((*met).maddr),6);break;
		 case 12: STMFLASH_Read(FLASH_ADDR_M12,(u16*)((*met).maddr),6);break;
		 case 13: STMFLASH_Read(FLASH_ADDR_M13,(u16*)((*met).maddr),6);break;
		 case 14: STMFLASH_Read(FLASH_ADDR_M14,(u16*)((*met).maddr),6);break;
		 case 15: STMFLASH_Read(FLASH_ADDR_M15,(u16*)((*met).maddr),6);break;
		 case 16: STMFLASH_Read(FLASH_ADDR_M16,(u16*)((*met).maddr),6);break;
		 case 17: STMFLASH_Read(FLASH_ADDR_M17,(u16*)((*met).maddr),6);break;
		 case 18: STMFLASH_Read(FLASH_ADDR_M18,(u16*)((*met).maddr),6);break;
		 case 19: STMFLASH_Read(FLASH_ADDR_M19,(u16*)((*met).maddr),6);break;
		 case 20: STMFLASH_Read(FLASH_ADDR_M20,(u16*)((*met).maddr),6);break;
		 case 21: STMFLASH_Read(FLASH_ADDR_M21,(u16*)((*met).maddr),6);break;
		 case 22: STMFLASH_Read(FLASH_ADDR_M22,(u16*)((*met).maddr),6);break;
		 case 23: STMFLASH_Read(FLASH_ADDR_M23,(u16*)((*met).maddr),6);break;
		 case 24: STMFLASH_Read(FLASH_ADDR_M24,(u16*)((*met).maddr),6);break;
		 case 25: STMFLASH_Read(FLASH_ADDR_M25,(u16*)((*met).maddr),6);break;
		 case 26: STMFLASH_Read(FLASH_ADDR_M26,(u16*)((*met).maddr),6);break;
		 case 27: STMFLASH_Read(FLASH_ADDR_M27,(u16*)((*met).maddr),6);break;
		 case 28: STMFLASH_Read(FLASH_ADDR_M28,(u16*)((*met).maddr),6);break;
		 case 29: STMFLASH_Read(FLASH_ADDR_M29,(u16*)((*met).maddr),6);break;
		 case 30: STMFLASH_Read(FLASH_ADDR_M30,(u16*)((*met).maddr),6);break;
		 case 31: STMFLASH_Read(FLASH_ADDR_M31,(u16*)((*met).maddr),6);break;
		 case 32: STMFLASH_Read(FLASH_ADDR_M32,(u16*)((*met).maddr),6);break;
		 default :printf("maddr read error\r\n");break;
	 }
#ifdef DEBUG
	   printf("maddr read successful\r\n");
#endif
 }
u8 write_meter_addr(u8 meter_id,u8 meter_addr[12])      //将电表地址写入flash
{
	 switch(meter_id)
	 {
		 case 1: STMFLASH_Write(FLASH_ADDR_M1,(u16*)meter_addr,6);break;
		 case 2: STMFLASH_Write(FLASH_ADDR_M2,(u16*)meter_addr,6);break;
		 case 3: STMFLASH_Write(FLASH_ADDR_M3,(u16*)meter_addr,6);break;
		 case 4: STMFLASH_Write(FLASH_ADDR_M4,(u16*)meter_addr,6);break;
		 case 5: STMFLASH_Write(FLASH_ADDR_M5,(u16*)meter_addr,6);break;
		 case 6: STMFLASH_Write(FLASH_ADDR_M6,(u16*)meter_addr,6);break;
		 case 7: STMFLASH_Write(FLASH_ADDR_M7,(u16*)meter_addr,6);break;
		 case 8: STMFLASH_Write(FLASH_ADDR_M8,(u16*)meter_addr,6);break;
		 case 9: STMFLASH_Write(FLASH_ADDR_M9,(u16*)meter_addr,6);break;
		 case 10: STMFLASH_Write(FLASH_ADDR_M10,(u16*)meter_addr,6);break;
		 case 11: STMFLASH_Write(FLASH_ADDR_M11,(u16*)meter_addr,6);break;
		 case 12: STMFLASH_Write(FLASH_ADDR_M12,(u16*)meter_addr,6);break;
		 case 13: STMFLASH_Write(FLASH_ADDR_M13,(u16*)meter_addr,6);break;
		 case 14: STMFLASH_Write(FLASH_ADDR_M14,(u16*)meter_addr,6);break;
		 case 15: STMFLASH_Write(FLASH_ADDR_M15,(u16*)meter_addr,6);break;
		 case 16: STMFLASH_Write(FLASH_ADDR_M16,(u16*)meter_addr,6);break;
		 case 17: STMFLASH_Write(FLASH_ADDR_M17,(u16*)meter_addr,6);break;
		 case 18: STMFLASH_Write(FLASH_ADDR_M18,(u16*)meter_addr,6);break;
		 case 19: STMFLASH_Write(FLASH_ADDR_M19,(u16*)meter_addr,6);break;
		 case 20: STMFLASH_Write(FLASH_ADDR_M20,(u16*)meter_addr,6);break;
		 case 21: STMFLASH_Write(FLASH_ADDR_M21,(u16*)meter_addr,6);break;
		 case 22: STMFLASH_Write(FLASH_ADDR_M22,(u16*)meter_addr,6);break;
		 case 23: STMFLASH_Write(FLASH_ADDR_M23,(u16*)meter_addr,6);break;
		 case 24: STMFLASH_Write(FLASH_ADDR_M24,(u16*)meter_addr,6);break;
		 case 25: STMFLASH_Write(FLASH_ADDR_M25,(u16*)meter_addr,6);break;
		 case 26: STMFLASH_Write(FLASH_ADDR_M26,(u16*)meter_addr,6);break;
		 case 27: STMFLASH_Write(FLASH_ADDR_M27,(u16*)meter_addr,6);break;
		 case 28: STMFLASH_Write(FLASH_ADDR_M28,(u16*)meter_addr,6);break;
		 case 29: STMFLASH_Write(FLASH_ADDR_M29,(u16*)meter_addr,6);break;
		 case 30: STMFLASH_Write(FLASH_ADDR_M30,(u16*)meter_addr,6);break;
		 case 31: STMFLASH_Write(FLASH_ADDR_M31,(u16*)meter_addr,6);break;
		 case 32: STMFLASH_Write(FLASH_ADDR_M32,(u16*)meter_addr,6);break;
		 default :printf("meter_addr write error\r\n");break;
	 }
#ifdef DEBUG
	   printf("maddr write successful\r\n");
#endif
}

u8 meter_code_calculate(u8 meter_id, Meter * met)
{
  meter_voltage_code_calculate(meter_id,met);
	meter_current_code_calculate(meter_id,met);
	meter_cost_code_calculate(meter_id,met);
	meter_cut_code_calculate(meter_id,met);
	meter_con_code_calculate(meter_id,met); 
}
//u8 readvoltage[17]   = {0x68, 0x98, 0x99, 0x21, 0x00, 0x00, 0x00, 0x68, 0x11, 0x04, 0x33, 0x34, 0x34, 0x35, 0x07, 0x16,'\n'}; //????

u8 meter_voltage_code_calculate(u8 meter_id, Meter* met)
{
   u8 str[50];
	 int i;
   read_meter_addr(meter_id,met);
   str[0] = 0x68;
   str[1] = ((*met).maddr[10]-'0')*16+(*met).maddr[11]-'0';
	 str[2] = ((*met).maddr[8]-'0')*16+(*met).maddr[9]-'0';
   str[3] = ((*met).maddr[6]-'0')*16+(*met).maddr[7]-'0';
	 str[4] = ((*met).maddr[4]-'0')*16+(*met).maddr[5]-'0';
	 str[5] = ((*met).maddr[2]-'0')*16+(*met).maddr[3]-'0';
	 str[6] = ((*met).maddr[0]-'0')*16+(*met).maddr[1]-'0';
	 str[7] = 0x68;
	 str[8] = 0x11;
	 str[9] = 0x04;
	 str[10]= 0x33;
	 str[11]= 0x34;
	 str[12]= 0x34;
	 str[13]= 0x35;
	 str[14]=str[0]+str[1]+ str[2]+ str[3]+ str[4]+ str[5]+ str[6]+ str[7]+ str[8]+ str[9]+ str[10]+ str[11]+ str[12]+ str[13];
	 str[15]=0x16;
	 str[16]='\n';
   for(i=0;i<17;i++)
	 (*met).voltage_code[i]=str[i];
#ifdef DEBUG
	  printf("meter_voltage_code_calculate successful\r\n");
#endif  
}

//u8 readcurrent[17]   = {0x68, 0x98, 0x99, 0x21, 0x00, 0x00, 0x00, 0x68, 0x11, 0x04, 0x33, 0x34, 0x35, 0x35, 0x08, 0x16,'\n'}; //????

u8 meter_current_code_calculate(u8 meter_id, Meter* met)
{
   u8 str[50];
	 int i;
   read_meter_addr(meter_id,met);
   str[0] = 0x68;
   str[1] = ((*met).maddr[10]-'0')*16+(*met).maddr[11]-'0';
	 str[2] = ((*met).maddr[8]-'0')*16+(*met).maddr[9]-'0';
   str[3] = ((*met).maddr[6]-'0')*16+(*met).maddr[7]-'0';
	 str[4] = ((*met).maddr[4]-'0')*16+(*met).maddr[5]-'0';
	 str[5] = ((*met).maddr[2]-'0')*16+(*met).maddr[3]-'0';
	 str[6] = ((*met).maddr[0]-'0')*16+(*met).maddr[1]-'0';
	 str[7] = 0x68;
	 str[8] = 0x11;
	 str[9] = 0x04;
	 str[10]= 0x33;
	 str[11]= 0x34;
	 str[12]= 0x35;
	 str[13]= 0x35;
	 str[14]=str[0]+str[1]+ str[2]+ str[3]+ str[4]+ str[5]+ str[6]+ str[7]+ str[8]+ str[9]+ str[10]+ str[11]+ str[12]+ str[13];
	 str[15]=0x16;
	 str[16]='\n';
   for(i=0;i<17;i++)
	 (*met).current_code[i]=str[i];
#ifdef DEBUG
	  printf("meter_current_code_calculate successful\r\n");
#endif
}

//u8 readdushu[17]     = {0x68, 0x98, 0x99, 0x21, 0x00, 0x00, 0x00, 0x68, 0x11, 0x04, 0x33, 0x33, 0x34, 0x33, 0x04, 0x16,'\n'}; //????

u8 meter_cost_code_calculate(u8 meter_id, Meter* met)
{
   u8 str[50];
	 int i;
   read_meter_addr(meter_id,met);
   str[0] = 0x68;
   str[1] = ((*met).maddr[10]-'0')*16+(*met).maddr[11]-'0';
	 str[2] = ((*met).maddr[8]-'0')*16+(*met).maddr[9]-'0';
   str[3] = ((*met).maddr[6]-'0')*16+(*met).maddr[7]-'0';
	 str[4] = ((*met).maddr[4]-'0')*16+(*met).maddr[5]-'0';
	 str[5] = ((*met).maddr[2]-'0')*16+(*met).maddr[3]-'0';
	 str[6] = ((*met).maddr[0]-'0')*16+(*met).maddr[1]-'0';
	 str[7] = 0x68;
	 str[8] = 0x11;
	 str[9] = 0x04;
	 str[10]= 0x33;
	 str[11]= 0x33;
	 str[12]= 0x34;
	 str[13]= 0x33;
	 str[14]=str[0]+str[1]+ str[2]+ str[3]+ str[4]+ str[5]+ str[6]+ str[7]+ str[8]+ str[9]+ str[10]+ str[11]+ str[12]+ str[13];
	 str[15]=0x16;
	 str[16]='\n';
   for(i=0;i<17;i++)
	 (*met).cost_code[i]=str[i];
#ifdef DEBUG
	  printf("meter_cost_code_calculate successful\r\n");
#endif
}

//0x68, 0x1C, 0x10, 0x35, 0x33, 0x33, 0x33,v 0x63, 0x63, 0x63, 0x63, 0x4D, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x5A,0x16,'\n'};

u8 meter_cut_code_calculate(u8 meter_id, Meter* met)
{
   u8 str[50];
	 int i;
   read_meter_addr(meter_id,met);
   str[0] = 0x68;
   str[1] = ((*met).maddr[10]-'0')*16+(*met).maddr[11]-'0';
	 str[2] = ((*met).maddr[8]-'0')*16+(*met).maddr[9]-'0';
   str[3] = ((*met).maddr[6]-'0')*16+(*met).maddr[7]-'0';
	 str[4] = ((*met).maddr[4]-'0')*16+(*met).maddr[5]-'0';
	 str[5] = ((*met).maddr[2]-'0')*16+(*met).maddr[3]-'0';
	 str[6] = ((*met).maddr[0]-'0')*16+(*met).maddr[1]-'0';
	 str[7] = 0x68;
	 str[8] = 0x1C;
	 str[9] = 0x10;
	 str[10]= 0x35;
	 str[11]= 0x33;
	 str[12]= 0x33;
	 str[13]= 0x33;
	 str[14]= 0x63;
	 str[15]= 0x63;
	 str[16]= 0x63;
	 str[17]= 0x63;
	 str[18]= 0x4D;
	 str[19]= 0x33;
	 str[20]= 0x44;
	 str[21]= 0x44;
	 str[22]= 0x44;
   str[23]= 0x44;
 	 str[24]= 0x45;
 	 str[25]= 0xBB;
   str[26]=str[0]+str[1]+str[2]+str[3]+str[4]+str[5]+str[6]+str[7]+str[8]+str[9]+str[10]+str[11]+str[12]+str[13]+str[14]+str[15]+str[16]+str[17]+str[18]+str[19]+str[20]+str[21]+str[22]+str[23]+str[24]+str[25];
	 str[27]=0x16;
	 str[28]='\n';
   for(i=0;i<29;i++)
	 (*met).cut_code[i]=str[i];
#ifdef DEBUG
	  printf("meter_cut_code_calculate successful\r\n");
#endif
}
//0x35, 0x33, 0x33, 0x33, 0x63, 0x63, 0x63, 0x63, 0x4E, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x5B, 0x16,'\n'}; //"68 73 98 21 00 00 00 68 1C 10 35 33 33 33 63 63 63 63 4E 33 33 33 33 33 33 33 35 16"}; //??

u8 meter_con_code_calculate(u8 meter_id, Meter* met)
{
   u8 str[50];
	 int i;
   read_meter_addr(meter_id,met);
   str[0] = 0x68;
   str[1] = ((*met).maddr[10]-'0')*16+(*met).maddr[11]-'0';
	 str[2] = ((*met).maddr[8]-'0')*16+(*met).maddr[9]-'0';
   str[3] = ((*met).maddr[6]-'0')*16+(*met).maddr[7]-'0';
	 str[4] = ((*met).maddr[4]-'0')*16+(*met).maddr[5]-'0';
	 str[5] = ((*met).maddr[2]-'0')*16+(*met).maddr[3]-'0';
	 str[6] = ((*met).maddr[0]-'0')*16+(*met).maddr[1]-'0';
	 str[7] = 0x68;
	 str[8] = 0x1C;
	 str[9] = 0x10;
	 str[10]= 0x35;
	 str[11]= 0x33;
	 str[12]= 0x33;
	 str[13]= 0x33;
	 str[14]= 0x63;
	 str[15]= 0x63;
	 str[16]= 0x63;
	 str[17]= 0x63;
	 str[18]= 0x4E;
	 str[19]= 0x33;
	 str[20]= 0x44;
	 str[21]= 0x44;
	 str[22]= 0x44;
   str[23]= 0x44;
 	 str[24]= 0x45;
 	 str[25]= 0xBB;
   str[26]=str[0]+str[1]+str[2]+str[3]+str[4]+str[5]+str[6]+str[7]+str[8]+str[9]+str[10]+str[11]+str[12]+str[13]+str[14]+str[15]+str[16]+str[17]+str[18]+str[19]+str[20]+str[21]+str[22]+str[23]+str[24]+str[25];
	 str[27]=0x16;
	 str[28]='\n';
   for(i=0;i<29;i++)
	 (*met).connect_code[i]=str[i];
#ifdef DEBUG
	  printf("meter_cut_code_calculate successful\r\n");
#endif
}

u8 pack_meter_value(u8 meter_id,Meter *met)
{
	(*met).value_package[0] = (*met).cost_value[0];
	(*met).value_package[1] = (*met).cost_value[1];
	(*met).value_package[2] = (*met).cost_value[2];
	(*met).value_package[3] = (*met).cost_value[3];
	(*met).value_package[4] = (*met).current_value[0];
	(*met).value_package[5] = (*met).current_value[1];
	(*met).value_package[6] = (*met).current_value[2];
	(*met).value_package[7] = (*met).voltage_value[0];
	(*met).value_package[8] = (*met).voltage_value[1];
	(*met).value_package[9] = meter_id;
	(*met).value_package[10] = 0X1D;
	(*met).value_package[11] ='\r';
	(*met).value_package[12] ='\n';
}
u8 write_meter_package_to_flash(u8 meter_id)
{
	;
}