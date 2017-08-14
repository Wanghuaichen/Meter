#include "init.h"
const u8 encode[100]=
{
 56,89,75,88,55,77,35,60,23,12,
 5 ,85,47,43,31,99,40,34,66,33,
 44,0 ,30,70,45,20,48,7 ,95,32,
 64,29,16,6 ,86,68,67,84,27,69,
 62,11,79,36,42,50,38,4 ,91,9,
 39,13,98,25,80,73,2 ,37,90,83,
 92,82,59,93,8 ,54,22,51,78,17,
 57,58,14,72,46,94,52,41,76,21,
 96,97,1 ,65,15,74,28,61,3 ,87,
 26,81,63,10,19,24,53,71,49,18
};
int8_t* key_start_flag ="BF";  //meter control order
int8_t* key_end_flag   ="BD";  //meter control order end
extern int8_t * AT_NSORF;
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
extern u8 imei[15];

extern RTC_TimeTypeDef RTC_TimeStruct;
extern RTC_DateTypeDef RTC_DateStruct;

u8 verify()
{
	u8 ip_len= ipLen;
	u8 pos =0;
  volatile u8 * en_replay;
	u8 key_v[2];
	u8 password = 0;
	u8 time_now[6];
	u8 key_messgae[100];
	u16 time_key=0;
	key_messgae[0] = 'A';
	key_messgae[1] = 'T';
	key_messgae[2] = '+';
	key_messgae[3] = 'N';
	key_messgae[4] = 'S';
	key_messgae[5] = 'O';
	key_messgae[6] = 'S';
	key_messgae[7] = 'T';
	key_messgae[8] = '=';
	key_messgae[9] = '0';
	key_messgae[10] = ',';
	for(pos=0;pos<ip_len;pos++)
	key_messgae[11+pos] = UDP_IP[pos];
	key_messgae[11+pos] = ',';
	key_messgae[12+pos] = UDP_SOCKET[0];
	key_messgae[13+pos] = UDP_SOCKET[1];
	key_messgae[14+pos] = UDP_SOCKET[2];
	key_messgae[15+pos] = UDP_SOCKET[3];
	key_messgae[16+pos] = ',';
	key_messgae[17+pos] = '1';
	key_messgae[18+pos] = '5';
	key_messgae[19+pos] = ',';
	key_messgae[20+pos] = 'B';
	key_messgae[21+pos] = 'F';
	key_messgae[22+pos] = imei[0];
	key_messgae[23+pos] = imei[1];
	key_messgae[24+pos] = imei[2];
	key_messgae[25+pos] = imei[3];
	key_messgae[26+pos] = imei[4];
	key_messgae[27+pos] = imei[5];
	key_messgae[28+pos] = imei[6];
	key_messgae[29+pos] = imei[7];
	key_messgae[30+pos] = imei[8];
	key_messgae[31+pos] = imei[9];
	key_messgae[32+pos] = imei[10];
	key_messgae[33+pos] = imei[11];
	key_messgae[34+pos] = imei[12];
	key_messgae[35+pos] = imei[13];
	key_messgae[36+pos] = imei[14];
	key_messgae[37+pos] = '0';
	
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
				
	time_now[0] = RTC_DateStruct.RTC_Year;
	time_now[1] = RTC_DateStruct.RTC_Month;
	time_now[2] = RTC_DateStruct.RTC_Date;
	time_now[3] = RTC_TimeStruct.RTC_Hours;
	time_now[4] = RTC_TimeStruct.RTC_Minutes;
	time_now[5] = RTC_TimeStruct.RTC_Seconds;
	time_key = (time_now[0]/10)+(time_now[0]%10)*10+(time_now[1]/10)+(time_now[1]%10)*10+(time_now[2]/10)+(time_now[2]%10)*10+(time_now[3]/10)+(time_now[3]%10)*10+(time_now[4]/10)+(time_now[4]%10)*10+(time_now[5]/10)+(time_now[5]%10)*10;
	time_key = time_key%100;
	
	key_messgae[38+pos] = (time_now[0]/10)+'0';
	key_messgae[39+pos] = (time_now[0]%10)+'0';
	key_messgae[40+pos] = (time_now[1]/10)+'0';
	key_messgae[41+pos] = (time_now[1]%10)+'0';
	key_messgae[42+pos] = (time_now[2]/10)+'0';
	key_messgae[43+pos] = (time_now[2]%10)+'0';
	key_messgae[44+pos] = (time_now[3]/10)+'0';
	key_messgae[45+pos] = (time_now[3]%10)+'0';
	key_messgae[46+pos] = (time_now[4]/10)+'0';
	key_messgae[47+pos] = (time_now[4]%10)+'0';
	key_messgae[48+pos] = (time_now[5]/10)+'0';
	key_messgae[49+pos] = (time_now[5]%10)+'0';
	
  key_messgae[50+pos] = '\r';
  key_messgae[51+pos] = '\n';
	
	internet_test(key_messgae, "OK", 3000);
	delay_ms(5000);
	Send_MQ(AT_NSORF, "OK", 1000);	
	if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)key_end_flag)))  
	{
		en_replay = strstr((const char *)USART2_RX_BUF, (const char *)key_start_flag);
		en_replay++;en_replay++;
		key_v[0] = (*en_replay);en_replay++;
		key_v[1] = (*en_replay);
		password = (key_v[0]-'0')*10+(key_v[1]-'0');
	}
	if(encode[time_key]==password)
	return 1;
	else return 0;
}