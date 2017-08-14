#include "fre.h"
#include "init.h"
u8 fre_message[20];
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
extern volatile u8 imei[15];

u16  T_FRE_REF=60;      //5s
u16  T_FRE_TASK=15;      //5s

void set_fre()
{
	u8 fre[8];
	u8 i;
	u8 send_message[50]={0};	
  u8 ip_len= ipLen;
	u8 pos =0;
	for(i=0;i<8;i++)fre[i]=fre_message[i];
  STMFLASH_Write(FRE_ADDR,(u16*)fre,8);
	
	T_FRE_REF =(fre[0]-'0')*1000+(fre[1]-'0')*100+(fre[2]-'0')*10+(fre[3]-'0');
	T_FRE_TASK =(fre[4]-'0')*1000+(fre[5]-'0')*100+(fre[6]-'0')*10+(fre[7]-'0');	
	#ifdef DEBUG
	printf("str:%s\r\n",fre);
  #endif
	send_message[0] = 'A';
	send_message[1] = 'T';
	send_message[2] = '+';
	send_message[3] = 'N';
	send_message[4] = 'S';
	send_message[5] = 'O';
	send_message[6] = 'S';
	send_message[7] = 'T';
	send_message[8] = '=';
	send_message[9] = '0';
	send_message[10] = ',';

	for(pos=0;pos<ip_len;pos++)
	send_message[11+pos] = UDP_IP[pos];
	
	send_message[11+pos] = ',';
	send_message[12+pos] = UDP_SOCKET[0];
	send_message[13+pos] = UDP_SOCKET[1];
	send_message[14+pos] = UDP_SOCKET[2];
	send_message[15+pos] = UDP_SOCKET[3];
	send_message[16+pos] = ',';
	send_message[17+pos] = '1';
	send_message[18+pos] = '0';
	send_message[19+pos] = ',';
	send_message[20+pos] = '0';
	send_message[21+pos] = imei[0];
	send_message[22+pos] = imei[1];
	send_message[23+pos] = imei[2];
	send_message[24+pos] = imei[3];
	send_message[25+pos] = imei[4];
	send_message[26+pos] = imei[5];
	send_message[27+pos] = imei[6];
	send_message[28+pos] = imei[7];
	send_message[29+pos] = imei[8];
	send_message[30+pos] = imei[9];
	send_message[31+pos] = imei[10];
	send_message[32+pos] = imei[11];
	send_message[33+pos] = imei[12];
	send_message[34+pos] = imei[13];
	send_message[35+pos] = imei[14];
  send_message[36+pos] = 'C';
  send_message[37+pos] = 'F';
  send_message[38+pos] = 'E';
  send_message[39+pos] = 'C';
	send_message[40+pos] = '\r';
	send_message[41+pos] = '\n';
 	SendCmd(send_message, "OK",1000);
}

void update_fre()
{
	u8 str[4];
	str[0] = T_FRE_REF/1000+'0';
	str[1] = (T_FRE_REF/100)%10+'0';
	str[2] = (T_FRE_REF/10)%10+'0';
	str[3] = T_FRE_REF%10+'0';
	
	str[4] = T_FRE_TASK/1000+'0';
	str[5] = (T_FRE_TASK/100)%10+'0';
	str[6] = (T_FRE_TASK/10)%10+'0';
	str[7] = T_FRE_TASK%10+'0';
	
	printf("str:%s",str);
	STMFLASH_Write(FRE_ADDR,(u16*)(str),8);
}
void get_fre()
{
	u8 fro[50];
	STMFLASH_Read(FRE_ADDR,(u16*)fro,12);
	T_FRE_REF =(fro[0]-'0')*1000+(fro[1]-'0')*100+(fro[2]-'0')*10+(fro[3]-'0');
	T_FRE_TASK =(fro[4]-'0')*1000+(fro[5]-'0')*100+(fro[6]-'0')*10+(fro[7]-'0');	
}