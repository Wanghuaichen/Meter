#ifndef __TASK_H
#define __TASK_H
#include "sys.h"
#include "meter.h"
extern u8 meter_task(void);
extern u8 order_1_task(u8 *mes,Meter * met);
extern u8 order_2_task(u8 *mes,Meter * met);
extern u8 order_3_task(u8 *mes,Meter * met);
extern u8 order_4_task(u8 *mes,Meter * met);
extern u8 order_5_task(u8 *mes,Meter * met);
extern u8 order_6_task(u8 *mes,Meter * met);
extern u8 order_7_task(u8 *mes,Meter * met);
extern u8 order_8_task();
extern u8 order_task(u8 fun,u8 *mes,Meter * met);


#endif