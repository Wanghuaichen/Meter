#include "init.h"
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
void sys_init()
{
	delay_init(64);	    	 //延时函数初始化	  
	Adc_Init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart1_init(2400);	 	// 电表串口初始化为2400，偶校验 
	LED_Init();
	uart2_init(9600);	 	  //模组对应串口初始化为9600
	uart3_init(9600);	 	//log日志输出串口初始化为115200 
//	LCD_Init();			   		//初始化LCD  
 	My_RTC_Init();	  			//RTC初始化
}
extern volatile u8 meter_status[64];
extern volatile u8 fm_version[32];
u8 get_meter_number(u8 *number)
{
	u16 temp=0;
	int i=0;
	int j=0;
	u8 flag[4]={0,250,50,0};
	STMFLASH_Read(FLASH_METER_NUMBER,(u16*)number,4);
	temp= number[0]+number[1]+number[2]+number[3];
	if((temp<=300)||(temp>=333)) 
	{
		STMFLASH_Write(FLASH_METER_NUMBER,(u16*)flag,4);
		STMFLASH_Write(FLASH_METER_STATUS,(u16*)meter_status,64);	
		STMFLASH_Write(FLASH_FM_VERSION,(u16*)fm_version,32);

		STMFLASH_Write(FLASH_IP,(u16*)UDP_IP,20);
		STMFLASH_Write(FLASH_SOCKET,(u16*)UDP_SOCKET,6);	
		
    update_fre();
		
	}

}