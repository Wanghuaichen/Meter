#include "init.h"
#include "task.h"
int8_t  UDP_IP[16] = "112.124.6.31B";
int8_t  UDP_SOCKET[6] = {'1','2','3','4','\r','\n'};
u8 ipLen=12;
extern int8_t * AT_IMEI_Q;
u8 imei[15] = {'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
Meter meter;
u8  data_num[12][12]= {0};
volatile u8 function = 0;
u8 order_message[20];
u8 order_sum[200] = {0};
u8 meter_addr_message[32][15];
volatile u8 * nb_replay;
u8 meter_number[4]={0,0,0,0};
volatile u8 meter_status[64] = {'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A'};
volatile u8 fm_version[32] =   {'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A'};
u8 meter_task_sem=0;
u8 mstr[12]={0};
u8 ip_message[30];
int ic=0;
int main()
{
	
    order_message[19]='\n';
	
    sys_init();  
	
   	nb_connect_cloud();                      //nb�豸��������
	
  	IMEI_GET(AT_IMEI_Q,imei, 5000); //����2�����ַ���AT_REBOOT��ֱ������2�յ���OK��ֹͣ���ͣ�������3000ms�������� �ַ���AT_REBOOT
    
	  printf("imei:%s\r\n",imei);
	
	  get_meter_number(meter_number);
	
	  get_ip();
	
	  get_fre();
    
	  meter_task_sem=0; 
		IWDG_Init(7,4000); // �������Ź������Ƶ��Ϊ64,����ֵΪ5000,���ʱ��Ϊ10s	

		TIM3_Int_Init(20000,64000);// 20s
		TIM2_Int_clock(1000,63999);  //3 seconds
#ifdef DEBUG
	printf("rebootiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing\r\n\r\n\r\n");
#endif
#ifdef METRE_CLEAR
//meter_number[0]=0;
//STMFLASH_Write(FLASH_METER_NUMBER,(u16*)meter_number,4);			
#endif
    UART2_Print("AT+NMGS=1,CC\r\n");
	 while(1)
	{
		;
		}
	  
}