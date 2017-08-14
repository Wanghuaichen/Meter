#ifndef __DELAY_H
#define __DELAY_H
#include "sys.h"  
void delay_init(u8 t);
void delay_ms( u16 ms);
void delay_ms_sub(u16 sub_ms);
void delay_us(u32 us);
void mydelay_us(u16 time);
void mydelay_ms(u16 time);
#endif