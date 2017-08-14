#ifndef __METER_H
#define __METER_H
#include "sys.h"
#define value_count 12           
typedef struct Met
{
	u8  maddr[14];           //电表地址  	13，14位为版本号              //  默认为2007   当13位为19 14位为97时  版本号为1997
	
	u8  cost_code[17];            //电表电量读取指令
	u8  voltage_code[17];         //电表电压读取指令
	u8  current_code[17];         //电表电流读取指令
	u8  cut_code[29];             //电表拉闸指令
	u8  connect_code[29];         //电表合闸指令
	
	u8  timeList[12][7];          //时间记录
	u8  cost_value[5];           //电表电量值
	u8  voltage_value[3];        //电表电压值
	u8  current_value[4];        //电表电流值
	u8  cut_back_value[50];       //电表拉闸返回
	u8  connect_back_value[50];   //电表合闸返回
	

	
	u8  value_package[13]; //4,3,2，1
	
	u8  con_flag;                 //电表合闸标记
	u8  cut_flag;	                //电表拉闸标记
	
}Meter;

extern u8 meter_cutoff(u8 meter_id,Meter * met);    //

extern u8 meter_connect(u8 meter_id,Meter * met);   //

extern u8 meter_read_cost(u8 meter_id,Meter * met);   // 

extern u8 meter_read_voltage(u8 meter_id,Meter * met);// 

extern u8 meter_read_current(u8 meter_id,Meter * met);// 

extern u8 meter_read_all_value(u8 meter_id,Meter * met);    // 

extern u8 meter_read_1997_value(u8 meter_id,Meter * met);    // 

extern u8 meter_data_updata(u8 meter_id,Meter * met);

extern u8 read_meter_addr(u8 meter_id,Meter * met);   // 

extern u8 write_meter_addr(u8 meter_id,u8 addr[12]);      // 

extern u8 meter_code_calculate(u8 meter_id,Meter * met);   // 

extern u8 meter_voltage_code_calculate(u8 meter_id, Meter *met); //calculate meter voltage code string
extern u8 meter_current_code_calculate(u8 meter_id, Meter* met);  //calculate meter current code string
extern u8 meter_cost_code_calculate(u8 meter_id, Meter* met);     //calculate meter cost code string
extern u8 meter_cut_code_calculate(u8 meter_id, Meter* met);     //calculate meter cut code string
extern u8 meter_con_code_calculate(u8 meter_id, Meter* met);     //calculate meter connect code string
extern u8 pack_meter_value(u8 meter_id,Meter *met);

#endif