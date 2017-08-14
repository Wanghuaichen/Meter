#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART1_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define USART2_REC_LEN  			500  	//定义最大接收字节数 200
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收
 
#define USART3_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;         		//接收状态标记	

extern u8  USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         		//接收状态标记

extern u8  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         		//接收状态标记	

//如果想串口中断接收，请不要注释以下宏定义
extern void uart1_init(u32 bound);
extern void uart2_init(u32 bound);
extern void uart3_init(u32 bound);

extern void UART1_TEST(char * str,u8 l);  //串口3发送函数
extern void UART1_Print(char * str);
extern void UART2_Print(char * str);
extern void UART3_Print(char * str);
extern void Print(char * str);
extern void UART3_test_print(char * str) ;

extern volatile u16 usart2_rcv_len;
extern void USART2_Write(USART_TypeDef* USARTx, uint8_t *Data, uint32_t len);
extern void SendCmd(int8_t* cmd, int8_t* result, int32_t timeOut);
extern void internet_test(int8_t* cmd, int8_t* result, int32_t timeOut);
extern void Send_MQ(int8_t* cmd, int8_t* result, int32_t timeOut);
extern void IMEI_GET(int8_t* cmd, int8_t* result, int32_t timeOut);


#endif