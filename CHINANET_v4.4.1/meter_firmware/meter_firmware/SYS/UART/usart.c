#include "sys.h"
#include "usart.h"	 
#include "delay.h"
#include <string.h>
#include "wdog.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART3->ISR&0X40)==0);//循环发送,直到发送完毕   
    USART3->TDR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	  
  
void uart1_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//使能USART1，GPIOA时钟
  
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_7); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_7); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10


  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_Even;//偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}
extern u8 meter_databack[100];
extern int meter_databack_count;
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	   meter_databack[meter_databack_count] = USART1->RDR;
	   meter_databack_count++;
   }

void UART1_Print(char * str)   //串口3发送函数
{

	while(*str != '\n')
	{
				USART_SendData(USART1, *str);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		    str ++;
		    delay_ms(5);
	}
	delay_ms(5);
}
void UART1_TEST(char * str,u8 l)   //串口3发送函数
{
  u8 len =0;
	for(len=0;len<l;len++)
	{
				USART_SendData(USART1, *str);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		    str ++;
		    delay_ms(5);
	}
	delay_ms(5);
}
#endif	

 
#if EN_USART2_RX   //如果使能了接收
//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记	  
  
void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//使能USART1，GPIOA时钟
  
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_7); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_7); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10


  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口1 

}
//extern u8 CoAP_databack[100];
//extern int CoAP_databack_count;
volatile int8_t udp_data=1;
volatile int8_t rx_idle=0;

void USART2_IRQHandler(void)                	//串口1中断服务程序
	{
	  unsigned int data;
#if 1
    //if(USART2->ISR & 0x0F)
    //{
        // See if we have some kind of error
        // Clear interrupt (do nothing about it!)
        //data = USART2->RDR;
    //}
    //else if(USART2->ISR & USART_FLAG_RXNE)   //Receive Data Reg Full Flag
    {		
        data = USART2->RDR;
		    USART2_RX_BUF[usart2_rcv_len++]=data;
			  if(usart2_rcv_len>=512) usart2_rcv_len = 0;
		}
	
#endif
}

void UART2_Print(char * str)   //串口3发送函数
{
  while(*str != '\n')
	{
				USART_SendData(USART2, *str);//向串口1发送数据
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		    str ++;
	}
        USART_SendData(USART2, '\n');//向串口1发送数据
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
}
#endif	


#if EN_USART3_RX   //如果使能了接收
//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART3_RX_BUF[USART3_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART3_RX_STA=0;       //接收状态标记	  
  
void uart3_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	//使能USART1，GPIOA时钟
  
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_7); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_7); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PA9，PA10


  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口1
  // USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口1 

}

void USART3_IRQHandler(void)                	//串口1中断服务程序
	{

}

void UART3_Print(char * str)   //串口3发送函数
{
  while(*str != '\n')
	{
				USART_SendData(USART3, *str);//向串口1发送数据
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		    str ++;
	}
		
}

void UART3_test_print(char * str)   //串口3发送函数
{
	u8 i =0 ;
  for(i=0;i<12;i++)
	{
				USART_SendData(USART3, *str);//向串口1发送数据
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		    str ++;
	}
				USART_SendData(USART3,'\n');//向串口1发送数据
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		
}
void Print(char * str)   //串口3发送函数
{
  UART3_Print(str);		
}
#endif	

void USART2_Write(USART_TypeDef* USARTx, uint8_t *Data, uint32_t len)
{
    uint32_t i;
    USART_ClearFlag(USARTx, USART_FLAG_TC);
    for(i = 0; i < len; i++)
    {
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}
volatile u16 usart2_rcv_len=0;
void SendCmd(int8_t* cmd, int8_t* result, int32_t timeOut)
{
 	while(1)
    {
        memset(USART2_RX_BUF, 0, strlen((const char *)USART2_RX_BUF));
        usart2_rcv_len = 0;

        USART2_Write(USART2, (uint8_t*)cmd, strlen((const char *)cmd));
			  IWDG_Feed();
        delay_ms(timeOut);
        printf("%s %d cmd:%s,rsp:%s\n", __func__, __LINE__, cmd, (const char *)USART2_RX_BUF);
         if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)result)))
       {
            break;
         }
        else
          {
            delay_ms(100);
          }
     }
		 memset(USART2_RX_BUF, 0, strlen((const char *)USART2_RX_BUF));
   	 usart2_rcv_len=0; 
}
void Send_MQ(int8_t* cmd, int8_t* result, int32_t timeOut)
{
	  static int i = 0;
 	while(1)
    {   
			  
        memset(USART2_RX_BUF, 0, strlen((const char *)USART2_RX_BUF));
        usart2_rcv_len = 0;

        USART2_Write(USART2, (uint8_t*)cmd, strlen((const char *)cmd));
			  IWDG_Feed();
        delay_ms(timeOut);
        printf("%s %d cmd:%s,rsp:%s\n", __func__, __LINE__, cmd, (const char *)USART2_RX_BUF);
         if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)result)))
       {
				    i = 0;
            break;
         }
        else
          {
            delay_ms(100);
						i++;
          }
				if(i>=5){i=0;break;}
     }
}
void internet_test(int8_t* cmd, int8_t* result, int32_t timeOut)
{
	int test_num=0;
 	while(1)
    {   
			  test_num++;
        memset(USART2_RX_BUF, 0, strlen((const char *)USART2_RX_BUF));
        usart2_rcv_len = 0;

        USART2_Write(USART2, (uint8_t*)cmd, strlen((const char *)cmd));
			  IWDG_Feed();
        delay_ms(timeOut);
        printf("%s %d cmd:%s,rsp:%s\n", __func__, __LINE__, cmd, (const char *)USART2_RX_BUF);
         if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)result)))
       {
				    test_num = 0;
            break;
         }
        else 
          {
            delay_ms(100);
          }
				if(test_num>=10) 
				{
					test_num = 0;
					LED_Set(ERROR,0);
					NVIC_SystemReset();
				}
     }
		 memset(USART2_RX_BUF, 0, strlen((const char *)USART2_RX_BUF));
   	 usart2_rcv_len=0; 
}
void IMEI_GET(int8_t* cmd, int8_t* result, int32_t timeOut)
{
	const char * flag ="CGSN:";
	u8 * str;
	u8 i=0;
 	while(1)
    {
        memset(USART2_RX_BUF, 0, strlen((const char *)USART2_RX_BUF));
        usart2_rcv_len = 0;
      
        USART2_Write(USART2, (uint8_t*)cmd, strlen((const char *)cmd));
        delay_ms(timeOut);
        printf("%s %d cmd:%s,rsp:%s\n", __func__, __LINE__, cmd, (const char *)USART2_RX_BUF);
         if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)flag)))
       {
				    str = strstr((const char *)USART2_RX_BUF, (const char *)flag);
						str += 5;
						for(i=0;i<15;i++)
						{
						result[i] = *str;
						str++;
						}
            break;
         }
        else
          {
            delay_ms(1000);
          }
     }
   	     usart2_rcv_len=0;
}