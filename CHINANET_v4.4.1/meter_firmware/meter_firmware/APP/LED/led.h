#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"

#define ERROR  GPIO_Pin_8
#define UP    GPIO_Pin_7
#define METER  GPIO_Pin_6
#define ONLINE  GPIO_Pin_5

#define SIG  GPIO_Pin_0
#define LED5_R     GPIO_Pin_1

#define LED6  GPIO_Pin_13
#define LED7  GPIO_Pin_14

#define DE485 GPIO_Pin_11

#define BC95EN GPIO_Pin_15

#define On  0
#define Off   1

#define Write 1
#define Read 0

#define BC95_ENABLE 0
extern void LED_Init(void);//≥ı ºªØ
extern void LED_Set(uint16_t GPIO_Pin, BitAction BitVal);
extern void RS485_Set(u8 rs);
extern void BC95_Set(u8 rs);
extern void LED_Flip(uint16_t GPIO_Pin);

#endif
