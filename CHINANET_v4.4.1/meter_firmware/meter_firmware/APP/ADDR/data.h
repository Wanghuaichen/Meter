#ifndef __DATA_H
#define __DATA_H
#include "sys.h"
#include "flash.h"
#include "meter.h"

extern u8 data_update(u8 meter_id,Meter *met);

extern u8 meter_1_data_updata(u8 id,Meter *met);

extern u8 copy_package(u8 str1[12],u8 str2[12]);

#endif