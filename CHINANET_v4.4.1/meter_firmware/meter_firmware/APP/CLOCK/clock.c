#include "clock.h"
#include "flash.h"
#include "rtc.h"
extern RTC_TimeTypeDef RTC_TimeStruct;
extern RTC_DateTypeDef RTC_DateStruct;
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
extern u8 imei[15];

void updateTime(u8 id)
{
	u8 clockList[12][6]={0};
	u8 i=0;
	
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
for(i=0;i<11;i++)
	{
			clockList[11-i][0] = clockList[10-i][0];
			clockList[11-i][1] = clockList[10-i][1];
			clockList[11-i][2] = clockList[10-i][2];
			clockList[11-i][3] = clockList[10-i][3];
			clockList[11-i][4] = clockList[10-i][4];
			clockList[11-i][5] = clockList[10-i][5];
	}
	clockList[0][0] = RTC_DateStruct.RTC_Year;
	clockList[0][1] = RTC_DateStruct.RTC_Month;
	clockList[0][2] = RTC_DateStruct.RTC_Date;
	clockList[0][3] = RTC_TimeStruct.RTC_Hours;
	clockList[0][4] = RTC_TimeStruct.RTC_Minutes;
	clockList[0][5] = RTC_TimeStruct.RTC_Seconds;
 	switch(id)
	{
		case 1:STMFLASH_Write(FLASH_TIME_LIST_M1,(u16*)clockList,72);break;
		case 2:STMFLASH_Write(FLASH_TIME_LIST_M2,(u16*)clockList,72);break;
		case 3:STMFLASH_Write(FLASH_TIME_LIST_M3,(u16*)clockList,72);break;
		case 4:STMFLASH_Write(FLASH_TIME_LIST_M4,(u16*)clockList,72);break;
		case 5:STMFLASH_Write(FLASH_TIME_LIST_M5,(u16*)clockList,72);break;
		case 6:STMFLASH_Write(FLASH_TIME_LIST_M6,(u16*)clockList,72);break;
		case 7:STMFLASH_Write(FLASH_TIME_LIST_M7,(u16*)clockList,72);break;
		case 8:STMFLASH_Write(FLASH_TIME_LIST_M8,(u16*)clockList,72);break;
		case 9:STMFLASH_Write(FLASH_TIME_LIST_M9,(u16*)clockList,72);break;
		case 10:STMFLASH_Write(FLASH_TIME_LIST_M10,(u16*)clockList,72);break;
		case 11:STMFLASH_Write(FLASH_TIME_LIST_M11,(u16*)clockList,72);break;
		case 12:STMFLASH_Write(FLASH_TIME_LIST_M12,(u16*)clockList,72);break;
		case 13:STMFLASH_Write(FLASH_TIME_LIST_M13,(u16*)clockList,72);break;
		case 14:STMFLASH_Write(FLASH_TIME_LIST_M14,(u16*)clockList,72);break;
		case 15:STMFLASH_Write(FLASH_TIME_LIST_M15,(u16*)clockList,72);break;
		case 16:STMFLASH_Write(FLASH_TIME_LIST_M16,(u16*)clockList,72);break;
		case 17:STMFLASH_Write(FLASH_TIME_LIST_M17,(u16*)clockList,72);break;
		case 18:STMFLASH_Write(FLASH_TIME_LIST_M18,(u16*)clockList,72);break;
		case 19:STMFLASH_Write(FLASH_TIME_LIST_M19,(u16*)clockList,72);break;
		case 20:STMFLASH_Write(FLASH_TIME_LIST_M20,(u16*)clockList,72);break;
		case 21:STMFLASH_Write(FLASH_TIME_LIST_M21,(u16*)clockList,72);break;
		case 22:STMFLASH_Write(FLASH_TIME_LIST_M22,(u16*)clockList,72);break;
		case 23:STMFLASH_Write(FLASH_TIME_LIST_M23,(u16*)clockList,72);break;
		case 24:STMFLASH_Write(FLASH_TIME_LIST_M24,(u16*)clockList,72);break;
		case 25:STMFLASH_Write(FLASH_TIME_LIST_M25,(u16*)clockList,72);break;
	  case 26:STMFLASH_Write(FLASH_TIME_LIST_M26,(u16*)clockList,72);break;
		case 27:STMFLASH_Write(FLASH_TIME_LIST_M27,(u16*)clockList,72);break;
		case 28:STMFLASH_Write(FLASH_TIME_LIST_M28,(u16*)clockList,72);break;
		case 29:STMFLASH_Write(FLASH_TIME_LIST_M29,(u16*)clockList,72);break;
		case 30:STMFLASH_Write(FLASH_TIME_LIST_M30,(u16*)clockList,72);break;
		case 31:STMFLASH_Write(FLASH_TIME_LIST_M31,(u16*)clockList,72);break;
		case 32:STMFLASH_Write(FLASH_TIME_LIST_M32,(u16*)clockList,72);break;
		default :break;
	}  
}

void setClock(u8 t1,u8 t2,u8 t3,u8 t4,u8 t5,u8 t6,u8 t7,u8 t8,u8 t9,u8 t10,u8 t11,u8 t12)
{
	u8 ip_len= ipLen;
	u8 pos =0;
	u8 myyear,mymonth,myday,myhour,mymin,mysec;
	u8 clockMessage[100];
	u8 clock_now[6];
	myyear = (t1-'0')*10+(t2-'0');
	mymonth = (t3-'0')*10+(t4-'0');
	myday = (t5-'0')*10+(t6-'0');
	myhour = (t7-'0')*10+(t8-'0');
	mymin = (t9-'0')*10+(t10-'0');
	mysec = (t11-'0')*10+(t12-'0');
	
	//if(myhour<=12)
	RTC_Set_Time(myhour,mymin,mysec,RTC_H12_AM);	//设置时间
	//else if(myhour>12)
	//{
	//  myhour = myhour-12;
	 // RTC_Set_Time(myhour,mymin,mysec,RTC_H12_PM);	//设置时间
	//}
	RTC_Set_Date(myyear,mymonth,myday,0);		//设置日期
	
	clockMessage[0] = 'A';
	clockMessage[1] = 'T';
	clockMessage[2] = '+';
	clockMessage[3] = 'N';
	clockMessage[4] = 'S';
	clockMessage[5] = 'O';
	clockMessage[6] = 'S';
	clockMessage[7] = 'T';
	clockMessage[8] = '=';
	clockMessage[9] = '0';
	clockMessage[10] = ',';
  for(pos=0;pos<ip_len;pos++)
	clockMessage[11+pos] = UDP_IP[pos];
	clockMessage[11+pos] = ',';
	clockMessage[12+pos] = UDP_SOCKET[0];
	clockMessage[13+pos] = UDP_SOCKET[1];
	clockMessage[14+pos] = UDP_SOCKET[2];
	clockMessage[15+pos] = UDP_SOCKET[3];
	clockMessage[16+pos] = ',';
	clockMessage[17+pos] = '1';
	clockMessage[18+pos] = '5';
	clockMessage[19+pos] = ',';
	clockMessage[20+pos] = 'B';
	clockMessage[21+pos] = 'C';
	clockMessage[22+pos] = imei[0];
	clockMessage[23+pos] = imei[1];
	clockMessage[24+pos] = imei[2];
	clockMessage[25+pos] = imei[3];
	clockMessage[26+pos] = imei[4];
	clockMessage[27+pos] = imei[5];
	clockMessage[28+pos] = imei[6];
	clockMessage[29+pos] = imei[7];
	clockMessage[30+pos] = imei[8];
	clockMessage[31+pos] = imei[9];
	clockMessage[32+pos] = imei[10];
	clockMessage[33+pos] = imei[11];
	clockMessage[34+pos] = imei[12];
	clockMessage[35+pos] = imei[13];
	clockMessage[36+pos] = imei[14];
	clockMessage[37+pos] = '0';
	
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
				
	clock_now[0] = RTC_DateStruct.RTC_Year;
	clock_now[1] = RTC_DateStruct.RTC_Month;
	clock_now[2] = RTC_DateStruct.RTC_Date;
	clock_now[3] = RTC_TimeStruct.RTC_Hours;
	clock_now[4] = RTC_TimeStruct.RTC_Minutes;
	clock_now[5] = RTC_TimeStruct.RTC_Seconds;
	
	clockMessage[38+pos] = (clock_now[0]/10)+'0';
	clockMessage[39+pos] = (clock_now[0]%10)+'0';
	clockMessage[40+pos] = (clock_now[1]/10)+'0';
	clockMessage[41+pos] = (clock_now[1]%10)+'0';
	clockMessage[42+pos] = (clock_now[2]/10)+'0';
	clockMessage[43+pos] = (clock_now[2]%10)+'0';
	clockMessage[44+pos] = (clock_now[3]/10)+'0';
	clockMessage[45+pos] = (clock_now[3]%10)+'0';
	clockMessage[46+pos] = (clock_now[4]/10)+'0';
	clockMessage[47+pos] = (clock_now[4]%10)+'0';
	clockMessage[48+pos] = (clock_now[5]/10)+'0';
	clockMessage[49+pos] = (clock_now[5]%10)+'0';
	
  clockMessage[50+pos] = '\r';
  clockMessage[51+pos] = '\n';
	
	internet_test(clockMessage, "OK", 3000);
#ifdef DEBUG
printf(clockMessage);
#endif
}