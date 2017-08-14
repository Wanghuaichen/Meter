#include "alarm.h"
#include "usart.h"
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
extern u8 imei[15];
void alarm()
{
	u8 a_message[60];
	u8 ip_len= ipLen;
	u8 pos =0;
	a_message[0] = 'A';
	a_message[1] = 'T';
	a_message[2] = '+';
	a_message[3] = 'N';
	a_message[4] = 'S';
	a_message[5] = 'O';
	a_message[6] = 'S';
	a_message[7] = 'T';
	a_message[8] = '=';
	a_message[9] = '0';
	a_message[10] = ',';
  for(pos=0;pos<ip_len;pos++)
	a_message[11+pos] = UDP_IP[pos];
	a_message[11+pos] = ',';
	a_message[12+pos] = UDP_SOCKET[0];
	a_message[13+pos] = UDP_SOCKET[1];
	a_message[14+pos] = UDP_SOCKET[2];
	a_message[15+pos] = UDP_SOCKET[3];
	a_message[16+pos] = ',';
	a_message[17+pos] = '9';
	a_message[18+pos] = ',';
	a_message[19+pos] = 'A';
	a_message[20+pos] = 'E';
	a_message[21+pos] = imei[0];
	a_message[22+pos] = imei[1];
	a_message[23+pos] = imei[2];
	a_message[24+pos] = imei[3];
	a_message[25+pos] = imei[4];
	a_message[26+pos] = imei[5];
	a_message[27+pos] = imei[6];
	a_message[28+pos] = imei[7];
	a_message[29+pos] = imei[8];
	a_message[30+pos] = imei[9];
	a_message[31+pos] = imei[10];
	a_message[32+pos] = imei[11];
	a_message[33+pos] = imei[12];
	a_message[34+pos] = imei[13];
	a_message[35+pos] = imei[14];
	a_message[36+pos] = '0';
  a_message[37+pos] = '\r';
	a_message[38+pos] = '\n';
	Send_MQ(a_message, "OK", 1000);	
}