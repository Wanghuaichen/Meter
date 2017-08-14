#include "led.h"

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);	 //使能PB
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_0);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_1);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_6);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_7);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_8);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_14);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_15);						 //PB.5 输出高
	
	
	
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);	 //使能PB
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PB.5 输出高

}
 
void LED_Set(uint16_t GPIO_Pin, BitAction BitVal)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin,BitVal);
}

void LED_Flip(uint16_t GPIO_Pin)
{
	static int i=0;
	i=!i;
	GPIO_WriteBit(GPIOB,GPIO_Pin,i);
}

void RS485_Set(u8 rs)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_11,rs);
	delay_ms(5);
}

void BC95_Set(u8 rs)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_15,rs);
	delay_ms(5);
}