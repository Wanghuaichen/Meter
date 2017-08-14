#include "ip.h"
#include "init.h"
#include "flash.h"
extern u8 ip_message[30];
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
void change_ip(u8 *str)
{
	u8 len;
	u8 i;
	for(i=0;i<=15;i++)UDP_IP[i]=0;
	UDP_SOCKET[0]=str[0];
	UDP_SOCKET[1]=str[1];
	UDP_SOCKET[2]=str[2];
	UDP_SOCKET[3]=str[3];
	len =(str[4]-'0')*10+(str[5]-'0');
	ipLen=len;
	for(i=0;i<=len;i++)
	{
		UDP_IP[i]=str[6+i];
	}
	for(i=0;i<=len;i++)
	{
		if(UDP_IP[i]=='A')UDP_IP[i]='.';
	}
	STMFLASH_Write(FLASH_IP,(u16*)UDP_IP,30);
	STMFLASH_Write(FLASH_SOCKET,(u16*)UDP_SOCKET,4);
	STMFLASH_Write(FLASH_IP_LEN,(u16*)(&ipLen),4);
#ifdef DEBUG
	printf(str);
	printf(UDP_IP);
	printf(UDP_SOCKET);	
#endif

}
void get_ip()
{
	int i,j;
	STMFLASH_Read(FLASH_IP,(u16*)UDP_IP,10);
 	STMFLASH_Read(FLASH_SOCKET,(u16*)UDP_SOCKET,4);
	
	for(i=0;i<15;i++)
	{
    if(UDP_IP[i]=='B')break;
  }
	ipLen=i;
	printf("\r\n");
	printf("ipLen:%d\r\n",ipLen);
	printf("IP:");
	printf(UDP_IP);
	printf("\r\n");
  printf("SOCKET:");
	printf(UDP_SOCKET);
	printf("\r\n");
}