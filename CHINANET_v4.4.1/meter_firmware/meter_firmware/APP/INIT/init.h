#ifndef __INIT_H
#define __INIT_H
#include <string.h>
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "rtc.h"
#include "key.h"
#include "nb.h"
#include "meter.h"
#include "stmflash.h"
#include "flash.h"
#include "timer.h"
#include "wdog.h"
#include "adc.h"
#include "encode.h"
#include "alarm.h"
#include "string.h"
#include "ip.h"
extern void sys_init(void);
extern u8 get_meter_number(u8 *number);
#endif