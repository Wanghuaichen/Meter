#include "timer.h"
#include "led.h"
#include "sys.h"
#include "wdog.h"
#include "init.h"
extern u8 meter_task_sem;
extern RTC_TimeTypeDef RTC_TimeStruct;
extern RTC_DateTypeDef RTC_DateStruct;

extern u16  T_FRE_REF;      //5s
extern u16 T_FRE_TASK;      //5s


void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
static int tasktime = 0;
extern int8_t * AT_CGATT_Q;
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
extern u8 imei[15];
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	u8 * res_str = "CGATT:1";
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
      TIM_Cmd(TIM3, DISABLE);  //ʹ��TIMx		
			tasktime++;
			if(tasktime>=T_FRE_TASK)    //  n* 20s
			{
		    	tasktime=0;
					printf("timer 3               %d\r\n",tasktime);
				  
			  	meter_task();
			}
			if(tasktime >= 180)    //  n* 20s
			{
			
				#ifdef DEBUG
        printf("internet testiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing!!!");
				#endif
				internet_test(AT_CGATT_Q, "CGATT:1", 3000);
				tasktime = 0;
      
			}
	  	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־
      TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					
		}
}
void TIM2_Int_clock(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
extern int ic;
extern u8 meter_number[4]; 
extern volatile u8 function;
extern u8 order_message[20];
extern u8 mstr[12];
extern Meter meter;
void TIM2_IRQHandler(void)   //TIM3�ж�
{
	static u16 i=0;
	u16 adc_v = 0;
	u8 ip_len= ipLen;
	u8 pos =0;
	u8 rep_cm[100];
	IWDG_Feed();//ι��
	rep_cm[0] = 'A';
	rep_cm[1] = 'T';
	rep_cm[2] = '+';
	rep_cm[3] = 'N';
	rep_cm[4] = 'S';
	rep_cm[5] = 'O';
	rep_cm[6] = 'S';
	rep_cm[7] = 'T';
	rep_cm[8] = '=';
	rep_cm[9] = '0';
	rep_cm[10] = ',';
	for(pos=0;pos<ip_len;pos++)
	rep_cm[11+pos] = UDP_IP[pos];
	rep_cm[11+pos] = ',';
	rep_cm[12+pos] = UDP_SOCKET[0];
	rep_cm[13+pos] = UDP_SOCKET[1];
	rep_cm[14+pos] = UDP_SOCKET[2];
	rep_cm[15+pos] = UDP_SOCKET[3];
	rep_cm[16+pos] = ',';
	rep_cm[17+pos] = '9';
	rep_cm[18+pos] = ',';
	rep_cm[19+pos] = 'C';
	rep_cm[20+pos] = 'C';
	rep_cm[21+pos] = imei[0];
	rep_cm[22+pos] = imei[1];
	rep_cm[23+pos] = imei[2];
	rep_cm[24+pos] = imei[3];
	rep_cm[25+pos] = imei[4];
	rep_cm[26+pos] = imei[5];
	rep_cm[27+pos] = imei[6];
	rep_cm[28+pos] = imei[7];
	rep_cm[29+pos] = imei[8];
	rep_cm[30+pos] = imei[9];
	rep_cm[31+pos] = imei[10];
	rep_cm[32+pos] = imei[11];
	rep_cm[33+pos] = imei[12];
	rep_cm[34+pos] = imei[13];
	rep_cm[35+pos] = imei[14];
	rep_cm[36+pos] = '0';
	rep_cm[37+pos] = '\r';
	rep_cm[38+pos] = '\n';
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
		{
			TIM_Cmd(TIM2, DISABLE);  //ʹ��TIMx		
			i++;
			#ifdef DEBUG
			printf("timer 2 running\r\n");
		  #endif
			if(i==1)
			{
	  	  LED_Set(LED6,0);
			  LED_Set(LED7,1);
			}
			else
			{
	  	  LED_Set(LED6,1);
			  LED_Set(LED7,0);
			}
			if(i>=T_FRE_REF)
			{
				i = 0;
				UART2_Print(rep_cm);
		 		#ifdef DEBUG
			  printf(rep_cm);
		    #endif
			  IWDG_Feed();//ι��
				function = nb_receive();         //pick out orders from nb_data_back array
#ifdef DEBUG
	    	printf("cloud_order:%d\r\n",function);	
        STMFLASH_Read(FLASH_METER_NUMBER,(u16*)meter_number,2);		
			  printf("meter number:%d\n",(*meter_number));
				printf("order_message:%s\r\n",order_message);
				RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
				RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
				STMFLASH_Read(FLASH_ADDR_M1,(u16*)mstr,6);		
				printf("meter1 addr:%s\r\n",mstr);
				printf("year:%d  ",RTC_DateStruct.RTC_Year);
				printf("month:%d  ",RTC_DateStruct.RTC_Month);
				printf("date:%d  ",RTC_DateStruct.RTC_Date);
				printf("hour:%d  ",RTC_TimeStruct.RTC_Hours);
				printf("minute:%d  ",RTC_TimeStruct.RTC_Minutes);
				printf("second:%d  \r\n",RTC_TimeStruct.RTC_Seconds);
				
				adc_v = Get_Adc_Average(ADC_Channel_1,5);
				#ifdef DEBUG
				printf("adc value: %d\r\n",adc_v);
				#endif
				if(adc_v<=BAT_WARNNING)alarm();
				
#endif
	    	order_task(function,order_message,&meter);	
			
			}
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
			TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx		
		}
}













