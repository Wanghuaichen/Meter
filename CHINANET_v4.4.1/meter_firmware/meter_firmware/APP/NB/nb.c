#include "init.h"
int8_t * AT_REBOOT = "AT+NRB\r\n";

int8_t * AT_NBAND = "AT+NBAND=5\r\n";

int8_t * AT_CFUN = "AT+CFUN=1\r\n";
int8_t * AT_IP_CMNET = "AT+CGDCONT=1,\"IP\",\"CTWAP\"\r\n";     //int8_t * AT_IP_CMNET = "AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n";   //
int8_t * AT_COPS = "AT+COPS=1,2,\"46011\"\r\n";        //int8_t * AT_COPS = "AT+COPS=1,2,\"46000\"\r\n";               //
int8_t * AT_CGATT = "AT+CGATT=1\r\n";
int8_t * AT_CGATT_Q = "AT+CGATT?\r\n";
int8_t * AT_NSMI = "AT+NSMI=1\r\n";
int8_t * AT_NNMI = "AT+NNMI=2\r\n";

int8_t * AT_NSOCR = "AT+NSOCR=DGRAM,17,1234,1\r\n";
int8_t * AT_IMEI_Q = "AT+CGSN=1\r\n";

int8_t * AT_NSORF = "AT+NSORF=0,200\r\n";

//scrambling operating
int8_t * AT_CFUN_0 = "AT+CFUN=0\r\n";
int8_t * AT_NCOFIG_Q= "AT+NCOFIG?\r\n";
int8_t * AT_NCONFIG_0 = "AT+NCONFIG=CR_0354_0338_SCRAMBLING,TRUE\r\n";
int8_t * AT_NCONFIG_1 = "AT+NCONFIG=CR_0859_SI_AVOID,TRUE\r\n";
//////////////



extern volatile u8 * nb_replay;
int8_t* res_order ="AA";  //meter control order
int8_t* res_order_end  ="EA";  //meter control order end
int8_t* res_addr  ="AD";  //meter addr
int8_t* res_addr_end  ="ED";  //meter addr_end
int8_t* res_replay="AB";  //replay
int8_t* res_replay_end  ="EB";  //meter control order end

int8_t* order_sum_end  ="EF";  //meter control order end
int8_t* order_sum_start  ="AF";  //meter control order end

int8_t* get_message  ="NSONMI";  //meter control order end

int8_t* clock_start_flag ="BC";  //meter control order
int8_t* clock_end_flag   ="CA";  //meter control order end

int8_t* command_start_flag ="DDDD";  //meter control order
int8_t* command_end_flag   ="BBBBBB";  //meter control order end

int8_t* IP_start_flag ="AC";  //meter control order
int8_t* IP_end_flag   ="EE";  //meter control order end

u8 nb_connect_cloud()
{
	scrambling(TRUE);  //开扰码
 	internet_test(AT_REBOOT, "REBOOTING", 5000); //串口2发送字符串AT_REBOOT，直到串口2收到“OK”停止发送，否则间隔3000ms继续发送 字符串AT_REBOOT
  internet_test(AT_CFUN, "OK", 3000);
	internet_test(AT_NBAND, "OK", 3000);
	internet_test(AT_IP_CMNET, "OK", 3000);
	internet_test(AT_COPS, "OK", 3000);
	internet_test(AT_CGATT, "OK", 5000);
	internet_test(AT_CGATT_Q, "CGATT:1", 5000);
	internet_test(AT_NSOCR, "OK", 3000);
	printf("connect to cloud successful!\r\n");
	LED_Set(SIG,0);
	LED_Set(ONLINE,0);
}
	//scrambling operating
u8 scrambling(u8 status)
{
	if(TRUE)
	{
	internet_test(AT_CFUN_0, "OK", 3000);
	internet_test(AT_NCONFIG_0, "OK", 3000);
	internet_test(AT_NCONFIG_1, "OK", 3000);
	}
	else
	{
		internet_test(AT_CFUN_0, "OK", 3000);
		internet_test("AT+NCONFIG=CR_0354_0338_SCRAMBLING,FALSE\r\n", "OK", 3000);
		internet_test("AT+NCONFIG=CR_0859_SI_AVOID,FALSE\r\n", "OK", 3000);
	}
}
u8 nb_fresh()
{
	SendCmd(AT_IMEI_Q, "hhh", 5000);
}

u8 nb_frequence()
{
	;
}

u8 nb_get_metercode()
{
	;
}
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
extern u8 imei[15];
extern u8 fm_version[32];
u8 nb_upload(u8 meter_id)
{
	u8 ip_len= ipLen;
	u8 pos =0;
	u8   k=0;
	u8   nb_upload_package[80];
	u8   meter_package[16];	
#ifdef DEBUG
	printf("uploading data....\r\n");
#endif

	switch(meter_id)
	{
		case 1 :STMFLASH_Read (FLASH_DATA_ADDR_M1_1,(u16*)meter_package,6); break;
		case 2 :STMFLASH_Read (FLASH_DATA_ADDR_M2_1,(u16*)meter_package,6); break;
		case 3 :STMFLASH_Read (FLASH_DATA_ADDR_M3_1,(u16*)meter_package,6); break;
		case 4 :STMFLASH_Read (FLASH_DATA_ADDR_M4_1,(u16*)meter_package,6); break;
		case 5 :STMFLASH_Read (FLASH_DATA_ADDR_M5_1,(u16*)meter_package,6); break;
		case 6 :STMFLASH_Read (FLASH_DATA_ADDR_M6_1,(u16*)meter_package,6); break;
		case 7 :STMFLASH_Read (FLASH_DATA_ADDR_M7_1,(u16*)meter_package,6); break;
		case 8 :STMFLASH_Read (FLASH_DATA_ADDR_M8_1,(u16*)meter_package,6); break;
		case 9 :STMFLASH_Read (FLASH_DATA_ADDR_M9_1,(u16*)meter_package,6); break;
		case 10:STMFLASH_Read (FLASH_DATA_ADDR_M10_1,(u16*)meter_package,6);break;
		case 11:STMFLASH_Read (FLASH_DATA_ADDR_M11_1,(u16*)meter_package,6);break;
		case 12:STMFLASH_Read (FLASH_DATA_ADDR_M12_1,(u16*)meter_package,6);break;
		case 13:STMFLASH_Read (FLASH_DATA_ADDR_M13_1,(u16*)meter_package,6);break;
		case 14:STMFLASH_Read (FLASH_DATA_ADDR_M14_1,(u16*)meter_package,6);break;
		case 15:STMFLASH_Read (FLASH_DATA_ADDR_M15_1,(u16*)meter_package,6);break;
		case 16:STMFLASH_Read (FLASH_DATA_ADDR_M16_1,(u16*)meter_package,6);break;
		case 17:STMFLASH_Read (FLASH_DATA_ADDR_M17_1,(u16*)meter_package,6);break;
		case 18:STMFLASH_Read (FLASH_DATA_ADDR_M18_1,(u16*)meter_package,6);break;
		case 19:STMFLASH_Read (FLASH_DATA_ADDR_M19_1,(u16*)meter_package,6);break;
		case 20:STMFLASH_Read (FLASH_DATA_ADDR_M20_1,(u16*)meter_package,6);break;
		case 21:STMFLASH_Read (FLASH_DATA_ADDR_M21_1,(u16*)meter_package,6);break;
		case 22:STMFLASH_Read (FLASH_DATA_ADDR_M22_1,(u16*)meter_package,6);break;
		case 23:STMFLASH_Read (FLASH_DATA_ADDR_M23_1,(u16*)meter_package,6);break;
		case 24:STMFLASH_Read (FLASH_DATA_ADDR_M24_1,(u16*)meter_package,6);break;
		case 25:STMFLASH_Read (FLASH_DATA_ADDR_M25_1,(u16*)meter_package,6);break;
		case 26:STMFLASH_Read (FLASH_DATA_ADDR_M26_1,(u16*)meter_package,6);break;
		case 27:STMFLASH_Read (FLASH_DATA_ADDR_M27_1,(u16*)meter_package,6);break;
		case 28:STMFLASH_Read (FLASH_DATA_ADDR_M28_1,(u16*)meter_package,6);break;
		case 29:STMFLASH_Read (FLASH_DATA_ADDR_M29_1,(u16*)meter_package,6);break;
		case 30:STMFLASH_Read (FLASH_DATA_ADDR_M30_1,(u16*)meter_package,6);break;
		case 31:STMFLASH_Read (FLASH_DATA_ADDR_M31_1,(u16*)meter_package,6);break;
		case 32:STMFLASH_Read (FLASH_DATA_ADDR_M32_1,(u16*)meter_package,6);break;
		default : printf("data upload error");break;
	}
	
	nb_upload_package[0] = 'A';
	nb_upload_package[1] = 'T';
	nb_upload_package[2] = '+';
	nb_upload_package[3] = 'N';
	nb_upload_package[4] = 'S';
	nb_upload_package[5] = 'O';
	nb_upload_package[6] = 'S';
	nb_upload_package[7] = 'T';
	nb_upload_package[8] = '=';
	nb_upload_package[9] = '0';
	nb_upload_package[10] = ',';
	
	for(pos=0;pos<ip_len;pos++)
	nb_upload_package[11+pos] = UDP_IP[pos];
	nb_upload_package[11+pos] = ',';
	nb_upload_package[12+pos] = UDP_SOCKET[0];
	nb_upload_package[13+pos] = UDP_SOCKET[1];
	nb_upload_package[14+pos] = UDP_SOCKET[2];
	nb_upload_package[15+pos] = UDP_SOCKET[3];
	nb_upload_package[16+pos] = ',';
	nb_upload_package[17+pos] = '2';
	nb_upload_package[18+pos] = '0';
	nb_upload_package[19+pos] = ',';
	nb_upload_package[20+pos] = 'A';
	nb_upload_package[21+pos] = 'D';
  nb_upload_package[22+pos] = meter_package[0]/16 +  '0';
  nb_upload_package[23+pos] = meter_package[0]%16 +  '0';
  nb_upload_package[24+pos] = meter_package[1]/16 +  '0';
  nb_upload_package[25+pos] = meter_package[1]%16 +  '0';
  nb_upload_package[26+pos] = meter_package[2]/16 +  '0';
  nb_upload_package[27+pos] = meter_package[2]%16 +  '0';
  nb_upload_package[28+pos] = meter_package[3]/16 +  '0';
  nb_upload_package[29+pos] = meter_package[3]%16 +  '0';
	if(fm_version[meter_id-1]=='A')
	{
  nb_upload_package[30+pos] = meter_package[4]/16 +  '0';
  nb_upload_package[31+pos] = meter_package[4]%16 +  '0';
  nb_upload_package[32+pos] = meter_package[5]/16 +  '0';
  nb_upload_package[33+pos] = meter_package[5]%16 +  '0';
  nb_upload_package[34+pos] = meter_package[6]/16 +  '0';
  nb_upload_package[35+pos] = meter_package[6]%16 +  '0';
	
  nb_upload_package[36+pos] = meter_package[7]/16 +  '0';
  nb_upload_package[37+pos] = meter_package[7]%16 +  '0';
  nb_upload_package[38+pos] = meter_package[8]/16 +  '0';
  nb_upload_package[39+pos] = meter_package[8]%16 +  '0';
	}
		else if(fm_version[meter_id-1]=='B')
	{
  nb_upload_package[30+pos] =  '3';
  nb_upload_package[31+pos] =  '3';
  nb_upload_package[32+pos] =  '3';
  nb_upload_package[33+pos] =  '3';
  nb_upload_package[34+pos] =  '3';
  nb_upload_package[35+pos] =  '3';
	
  nb_upload_package[36+pos] =  '3';
  nb_upload_package[37+pos] =  '3';
  nb_upload_package[38+pos] =  '3';
  nb_upload_package[39+pos] =  '3';
	}
	
  nb_upload_package[40+pos] = meter_package[9]/16 +  '0';
  nb_upload_package[41+pos] = meter_package[9]%16 +  '0';
	nb_upload_package[42+pos] = '1';
  nb_upload_package[43+pos] = 'D';
	nb_upload_package[44+pos] = imei[0];
	nb_upload_package[45+pos] = imei[1];
	nb_upload_package[46+pos] = imei[2];
	nb_upload_package[47+pos] = imei[3];
	nb_upload_package[48+pos] = imei[4];
	nb_upload_package[49+pos] = imei[5];
	nb_upload_package[50+pos] = imei[6];
	nb_upload_package[51+pos] = imei[7];
	nb_upload_package[52+pos] = imei[8];
	nb_upload_package[53+pos] = imei[9];
	nb_upload_package[54+pos] = imei[10];
	nb_upload_package[55+pos] = imei[11];
	nb_upload_package[56+pos] = imei[12];
	nb_upload_package[57+pos] = imei[13];
	nb_upload_package[58+pos] = imei[14];
	nb_upload_package[59+pos] = '0';
  nb_upload_package[60+pos] = '\r';
  nb_upload_package[61+pos] = '\n';
	
	 for(k = 22+pos;k<42+pos;k++)
			 switch (nb_upload_package[k])
					{
						case '0': break;
						case '1': break;
						case '2': break;
						case '3': break;
						case '4': break;
						case '5': break;
						case '6': break;
						case '7': break;
						case '8': break;
						case '9': break;
						case ':': nb_upload_package[k] = 'A' ;break;
						case ';': nb_upload_package[k] = 'B' ;break;
						case '<': nb_upload_package[k] = 'C' ;break;
						case '=': nb_upload_package[k] = 'D' ;break;
						case '>': nb_upload_package[k] = 'E' ;break;
						case '?': nb_upload_package[k] = 'F' ;break;
						default:printf("nb data format error");break;
				 }
#ifdef DEBUG
	 UART3_Print(nb_upload_package);
#endif
   UART2_Print(nb_upload_package);
}
extern u8 order_message[20];
extern u8 order_sum[200];
extern u8 meter_addr_message[32][15];
extern u8 ip_message[30];
u8 clockMessage[10];
u8 command_message[200];
u8 meters_get = 0;
int8_t* data_fre_sta      ="CF";  // 
int8_t* data_fre_end      ="EC";  // 
extern u8 fre_message[20];
u8 nb_receive()
{
      
      int meters_temp;
	    u8 i;
	    Send_MQ(AT_NSORF, "OK", 500);	
      if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)res_order_end)))  
      {
				nb_replay = strstr((const char *)USART2_RX_BUF, (const char *)res_order);
				nb_replay++;nb_replay++;
				order_message[0] = (*nb_replay);nb_replay++;
				order_message[1] = (*nb_replay);nb_replay++;
				order_message[2] = (*nb_replay);nb_replay++;
				order_message[3] = (*nb_replay);
			  memset(USART2_RX_BUF, 0,900);
  			usart2_rcv_len = 0;
				return 1;
			}
		  else if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)res_addr_end)))  
      {
				nb_replay = strstr((const char *)USART2_RX_BUF, (const char *)res_addr);
				nb_replay++;nb_replay++;
				order_message[0] = (*nb_replay);nb_replay++;   //get meter number
				order_message[1] = (*nb_replay);nb_replay++;		//get meter number
        meters_get = 0;				                           //clear;
        meters_get = (order_message[0]-'0')*10+order_message[1]-'0';
				for(meters_temp=0;meters_temp<meters_get;meters_temp++)
				{
					meter_addr_message[meters_temp][0] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][1] = (*nb_replay);nb_replay++;					
					meter_addr_message[meters_temp][2] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][3] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][4] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][5] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][6] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][7] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][8] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][9] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][10] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][11] = (*nb_replay);nb_replay++;
          meter_addr_message[meters_temp][12] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][13] = (*nb_replay);nb_replay++;
					meter_addr_message[meters_temp][14] = '\n';
				}
			  memset(USART2_RX_BUF, 0,500);
  			usart2_rcv_len = 0;
				return 2;
			}
			else if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)res_replay_end)))  
      {
				nb_replay = strstr((const char *)USART2_RX_BUF,(const char *)res_replay);
				nb_replay++;nb_replay++;
				order_message[0] = (*nb_replay);nb_replay++;
				order_message[1] = (*nb_replay);nb_replay++;
				order_message[2] = (*nb_replay);nb_replay++;
				order_message[3] = (*nb_replay);
			  memset(USART2_RX_BUF, 0,500);
  			usart2_rcv_len = 0;
				return 3;
			}
			else if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)order_sum_end)))     //电表批量开关
      {
				nb_replay = strstr((const char *)USART2_RX_BUF,(const char *)order_sum_start);
				nb_replay++;nb_replay++;
				for(i=0;i<32;i++)
				{
				   order_sum[i] = (*nb_replay);nb_replay++;
				}
			  memset(USART2_RX_BUF, 0,500);
  			usart2_rcv_len = 0;
				return 4;
			}
			else if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)clock_end_flag)))     //电表批量开关
      {
				nb_replay = strstr((const char *)USART2_RX_BUF,(const char *)clock_start_flag);
				nb_replay++;nb_replay++;
				clockMessage[0] = (*nb_replay);nb_replay++;
				clockMessage[1] = (*nb_replay);nb_replay++;
				clockMessage[2] = (*nb_replay);nb_replay++;
				clockMessage[3] = (*nb_replay);nb_replay++;
				clockMessage[4] = (*nb_replay);nb_replay++;
				clockMessage[5] = (*nb_replay);nb_replay++;
				clockMessage[6] = (*nb_replay);nb_replay++;
				clockMessage[7] = (*nb_replay);nb_replay++;
				clockMessage[8] = (*nb_replay);nb_replay++;
				clockMessage[9] = (*nb_replay);nb_replay++;
				clockMessage[10] = (*nb_replay);nb_replay++;
				clockMessage[11] = (*nb_replay);nb_replay;
			  memset(USART2_RX_BUF, 0,900);
  			usart2_rcv_len = 0;
				return 5;
			}
			else if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)command_end_flag)))     //透传指令
      {
				nb_replay = strstr((const char *)USART2_RX_BUF,(const char *)command_start_flag);
				nb_replay++;nb_replay++;nb_replay++;nb_replay++;
				for(i=0;i<200;i++)
				{
			    	command_message[i] = (*nb_replay);
					  nb_replay++;
				}
			  memset(USART2_RX_BUF, 0,500);
  			usart2_rcv_len = 0;
				return 6;
			}
			else if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)IP_end_flag)))     //IP
      {
				nb_replay = strstr((const char *)USART2_RX_BUF,(const char *)IP_start_flag);
				nb_replay++;nb_replay++;
				for(i=0;i<30;i++)
				{
			    	ip_message[i] = (*nb_replay);
					  nb_replay++;
				}
			  memset(USART2_RX_BUF, 0,500);
  			usart2_rcv_len = 0;
				return 7;
			}
			else if((NULL != strstr((const char *)USART2_RX_BUF, (const char *)data_fre_end)))     //IP
      {
				nb_replay = strstr((const char *)USART2_RX_BUF,(const char *)data_fre_sta);
				nb_replay++;nb_replay++;
				for(i=0;i<8;i++)
				{
			    	fre_message[i] = (*nb_replay);
					  nb_replay++;
				}
			  memset(USART2_RX_BUF, 0,400);
  			usart2_rcv_len = 0;
				return 8;
       }
			return 0;
}
