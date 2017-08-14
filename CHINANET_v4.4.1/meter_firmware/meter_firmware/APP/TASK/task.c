#include "task.h"
#include "init.h"
extern Meter meter;
extern u8 meter_number[4];
extern int8_t  UDP_IP[16];
extern int8_t  UDP_SOCKET[6];
extern u8 ipLen;
extern u8 imei[15];
extern volatile u8 meter_status[64];
extern  volatile u8 fm_version[32];
extern u8 clockMessage[10];
extern u8 command_message[200];
extern u8 meter_databack[100];
extern int meter_databack_count;
extern u8 ip_message[30];
u8 meter_task()
{
  u8 ip_len= ipLen;
	u8 pos =0;
	u8 count=0;
	u8 meter_on = 0;
	u8 rep_cc[100];
	rep_cc[0] = 'A';
	rep_cc[1] = 'T';
	rep_cc[2] = '+';
	rep_cc[3] = 'N';
	rep_cc[4] = 'S';
	rep_cc[5] = 'O';
	rep_cc[6] = 'S';
	rep_cc[7] = 'T';
	rep_cc[8] = '=';
	rep_cc[9] = '0';
	rep_cc[10] = ',';
	for(pos=0;pos<ip_len;pos++)
	rep_cc[11+pos] = UDP_IP[pos];
	rep_cc[11+pos] = ',';
	rep_cc[12+pos] = UDP_SOCKET[0];
	rep_cc[13+pos] = UDP_SOCKET[1];
	rep_cc[14+pos] = UDP_SOCKET[2];
	rep_cc[15+pos] = UDP_SOCKET[3];
	rep_cc[16+pos] = ',';
	rep_cc[17+pos] = '9';
	rep_cc[18+pos] = ',';
	rep_cc[19+pos] = 'C';
	rep_cc[20+pos] = 'C';
	rep_cc[21+pos] = imei[0];
	rep_cc[22+pos] = imei[1];
	rep_cc[23+pos] = imei[2];
	rep_cc[24+pos] = imei[3];
	rep_cc[25+pos] = imei[4];
	rep_cc[26+pos] = imei[5];
	rep_cc[27+pos] = imei[6];
	rep_cc[28+pos] = imei[7];
	rep_cc[29+pos] = imei[8];
	rep_cc[30+pos] = imei[9];
	rep_cc[31+pos] = imei[10];
	rep_cc[32+pos] = imei[11];
	rep_cc[33+pos] = imei[12];
	rep_cc[34+pos] = imei[13];
	rep_cc[35+pos] = imei[14];
	rep_cc[36+pos] = '0';
	rep_cc[37+pos] = '\r';
	rep_cc[38+pos] = '\n';
	#ifdef DEBUG
	printf("running meter ttttttttttttttttttttttttask\r\n\r\n\r\n");
#endif
	 TIM_Cmd(TIM2, DISABLE);  //close tick
   TIM_Cmd(TIM3, DISABLE);  //close tick
 
	 LED_Set(METER,0);
	 STMFLASH_Read(FLASH_METER_NUMBER,(u16*)meter_number,4);
   STMFLASH_Read(FLASH_METER_STATUS,(u16*)meter_status,64);
	 STMFLASH_Read(FLASH_FM_VERSION,(u16*)fm_version,32);
#ifdef DEBUG
	printf("meter_status: 0 %c   fm_version: 0 %c\r\n",meter_status[16],fm_version[0]);
	printf("meter_status: 1 %c   fm_version: 1 %c\r\n",meter_status[17],fm_version[1]);
	printf("meter_status: 2 %c   fm_version: 2 %c\r\n",meter_status[18],fm_version[2]);
	printf("meter_status: 3 %c   fm_version: 3 %c\r\n",meter_status[19],fm_version[3]);
	printf("meter_status: 4 %c   fm_version: 4 %c\r\n",meter_status[20],fm_version[4]);
	printf("meter_status: 5 %c   fm_version: 5 %c\r\n",meter_status[21],fm_version[5]);
	printf("meter_status: 6 %c   fm_version: 6 %c\r\n",meter_status[22],fm_version[6]);
	printf("meter_status: 7 %c   fm_version: 7 %c\r\n",meter_status[23],fm_version[7]);
	printf("meter_status: 8 %c   fm_version: 8 %c\r\n",meter_status[24],fm_version[8]);
	printf("meter_status: 9 %c   fm_version: 9 %c\r\n",meter_status[25],fm_version[9]);
	printf("meter_status: 10 %c   fm_version: 10 %c\r\n",meter_status[26],fm_version[10]);
	printf("meter_status: 11 %c   fm_version: 11 %c\r\n",meter_status[27],fm_version[11]);
	printf("meter_status: 12 %c   fm_version: 12 %c\r\n",meter_status[28],fm_version[12]);
	printf("meter_status: 13 %c   fm_version: 13 %c\r\n",meter_status[29],fm_version[13]);
	printf("meter_status: 14 %c   fm_version: 14 %c\r\n",meter_status[30],fm_version[14]);
	printf("meter_status: 15 %c   fm_version: 15 %c\r\n",meter_status[31],fm_version[15]);
	printf("meter_status: 16 %c   fm_version: 16 %c\r\n",meter_status[32],fm_version[16]);
	printf("meter_status: 17 %c   fm_version: 17 %c\r\n",meter_status[33],fm_version[17]);
	printf("meter_status: 18 %c   fm_version: 18 %c\r\n",meter_status[34],fm_version[18]);
	printf("meter_status: 19 %c   fm_version: 19 %c\r\n",meter_status[35],fm_version[19]);
	printf("meter_status: 20 %c   fm_version: 20 %c\r\n",meter_status[36],fm_version[20]);
	printf("meter_status: 21 %c   fm_version: 21 %c\r\n",meter_status[37],fm_version[21]);
	printf("meter_status: 22 %c   fm_version: 22 %c\r\n",meter_status[38],fm_version[22]);
	printf("meter_status: 23 %c   fm_version: 23 %c\r\n",meter_status[39],fm_version[23]);
	printf("meter_status: 24 %c   fm_version: 24 %c\r\n",meter_status[40],fm_version[24]);
	printf("meter_status: 25 %c   fm_version: 25 %c\r\n",meter_status[41],fm_version[25]);
	printf("meter_status: 26 %c   fm_version: 26 %c\r\n",meter_status[42],fm_version[26]);
	printf("meter_status: 27 %c   fm_version: 27 %c\r\n",meter_status[43],fm_version[27]);
	printf("meter_status: 28 %c   fm_version: 28 %c\r\n",meter_status[44],fm_version[28]);
	printf("meter_status: 29 %c   fm_version: 29 %c\r\n",meter_status[45],fm_version[29]);
	printf("meter_status: 30 %c   fm_version: 30 %c\r\n",meter_status[46],fm_version[30]);
	printf("meter_status: 31 %c   fm_version: 31 %c\r\n",meter_status[47],fm_version[31]);
#endif
 	 if(meter_number[0]>32){printf("meter_task_error:meter id is bigger than meter number");return 0;}
	 if(meter_number[0]==0)
   {
	      UART2_Print(rep_cc);
		 		#ifdef DEBUG
			  printf(rep_cc);
		    #endif
	 }
	 for(count=1;count<=meter_number[0];count++)
	 {
		 if(meter_status[count-1+16]!= 'B') 
		 {
			 IWDG_Feed();//喂狗
			 USART_Cmd(USART2, DISABLE);  
			if(fm_version[count-1]== 'A') 
			{
			  uart1_init(2400);	
				delay_ms(100);
				meter_read_all_value(count,&meter);            //read meter 13 vlotage,current,cost,and store the vlaues with the meter object
				updateTime(count);
				data_update(count,&meter);                     //updata the flash
				USART_Cmd(USART2, ENABLE);                     //使能串口1 	
				nb_upload(count);
				meter_on = 1;
			}
			else if(fm_version[count-1]== 'B') 
			{
			  uart1_init(1200);	
				delay_ms(100);
				meter_read_1997_value(count,&meter);            //read meter 13 vlotage,current,cost,and store the vlaues with the meter object
				updateTime(count);
				data_update(count,&meter);                     //updata the flash
				USART_Cmd(USART2, ENABLE);                     //使能串口1 	
				nb_upload(count);
				meter_on = 1;
			}
			else printf("meter version error!\r\n");
		 }
		 IWDG_Feed();//喂狗
	 }
	 if((meter_on==0)&&(meter_number[0]!=0))
    {
		   UART2_Print(rep_cc);
		   #ifdef DEBUG
			 printf(rep_cc);
		   #endif
		}
	    meter_on = 0;
      TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
      TIM_Cmd(TIM3, ENABLE);  //使能TIMx 
	    LED_Set(METER,1);
}


u8 order_1_task(u8 *mes,Meter * met)    //开关电表
{
	u8 ip_len= ipLen;
	u8 pos =0;
	u8 id=0;
	u8 ks=0;
	u8 order=0;
	u8 rep[50];
	id = (mes[0]-'0')*10+(mes[1]-'0');
	order = (mes[2]-'0')*10+(mes[3]-'0'-7);
	if((id<1)&&(id>32)) {printf("meter order number error\r\n");return 0;}
  if((order!=0X0D)&&(order!=0X0C)) {printf("meter order error\r\n");return 0;}
	if(order==0X0D) 
		{
			ks = verify();
			if(ks ==1)
			{
			  meter_cutoff(id,met);
	//		if(((*met).cut_back_value[10]==0X16)||((*met).cut_back_value[11]==0X16)||((*met).cut_back_value[12]==0X16)){
				rep[0] = 'A';
				rep[1] = 'T';
				rep[2] = '+';
				rep[3] = 'N';
				rep[4] = 'S';
				rep[5] = 'O';
				rep[6] = 'S';
				rep[7] = 'T';
				rep[8] = '=';
				rep[9] = '0';
				rep[10] = ',';
				for(pos=0;pos<ip_len;pos++)
				rep[11+pos] = UDP_IP[pos];
				rep[11+pos] = ',';
				rep[12+pos] = UDP_SOCKET[0];
				rep[13+pos] = UDP_SOCKET[1];
				rep[14+pos] = UDP_SOCKET[2];
				rep[15+pos] = UDP_SOCKET[3];
				rep[16+pos] = ',';
				rep[17+pos] = '4';
				rep[18+pos] = ',';
				rep[19+pos] = 'A';
				rep[20+pos] = 'A';
				rep[21+pos] = '7';
				rep[22+pos] = 'B';
				rep[23+pos] = mes[0];
				rep[24+pos] = mes[1];
				rep[25+pos] = '2';
				rep[26+pos] = 'D';
				rep[27+pos] = '\r';
				rep[28+pos] = 'n';
				UART2_Print(rep);//	}
		   }
		}
		else if(order==0X0C) 
		{ 
			ks = verify();
			if(ks ==1)
			{
		  	meter_connect(id,met);
	//		if(((*met).cut_back_value[10]==0X16)||((*met).cut_back_value[11]==0X16)||((*met).cut_back_value[12]==0X16)){
		  	rep[0] = 'A';
				rep[1] = 'T';
				rep[2] = '+';
				rep[3] = 'N';
				rep[4] = 'S';
				rep[5] = 'O';
				rep[6] = 'S';
				rep[7] = 'T';
				rep[8] = '=';
				rep[9] = '0';
				rep[10] = ',';
				for(pos=0;pos<ip_len;pos++)
	      rep[11+pos] = UDP_IP[pos];
				rep[11+pos] = ',';
				rep[12+pos] = UDP_SOCKET[0];
				rep[13+pos] = UDP_SOCKET[1];
				rep[14+pos] = UDP_SOCKET[2];
				rep[15+pos] = UDP_SOCKET[3];
				rep[16+pos] = ',';
				rep[17+pos] = '4';
				rep[18+pos] = ',';
				rep[19+pos] = 'A';
				rep[20+pos] = 'A';
				rep[21+pos] = '7';
				rep[22+pos] = 'B';
				rep[23+pos] = mes[0];
				rep[24+pos] = mes[1];
				rep[25+pos] = '2';
				rep[26+pos] = 'C';
				rep[27+pos] = '\r';
				rep[28+pos] = 'n';
				UART2_Print(rep);//	}
		}
	}
}
extern int meters_get; 
extern u8 meter_addr_message[32][15];
u8 order_2_task(u8 *mes,Meter * met)
{
	u8 ip_len= ipLen;
	u8 pos =0;
	u8 task_2_id=0;
	u8 i;
	u8  bitv[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	u8 meter_task_addr[12]={0};
	u8 number_temp;
	u16 sum1 = 0;
	u16 sum2 = 0;
	u8 rep[80];
	rep[0] = 'A';
	rep[1] = 'T';
	rep[2] = '+';
	rep[3] = 'N';
	rep[4] = 'S';
	rep[5] = 'O';
	rep[6] = 'S';
	rep[7] = 'T';
	rep[8] = '=';
	rep[9] = '0';
	rep[10] = ',';
	for(pos=0;pos<ip_len;pos++)
	rep[11+pos] = UDP_IP[pos];
	rep[11+pos] = ',';
	rep[12+pos] = UDP_SOCKET[0];
	rep[13+pos] = UDP_SOCKET[1];
	rep[14+pos] = UDP_SOCKET[2];
	rep[15+pos] = UDP_SOCKET[3];
	rep[16+pos] = ',';
	rep[17+pos] = '1';
	rep[18+pos] = '5';
	rep[19+pos] = ',';
	rep[20+pos] = 'A';
	rep[21+pos] = 'A';
	rep[22+pos] = '7';
	rep[23+pos] = 'B'; 
	if((meters_get<1)&&(meters_get>32)){ printf("meter addr write error\r\n"); return 0;}
	else 
	for(i=0;i<meters_get;i++)
	{
		              task_2_id = (meter_addr_message[i][12]-'0')*10+meter_addr_message[i][13]-'0';
									meter_task_addr[0]=meter_addr_message[i][0];
									meter_task_addr[1]=meter_addr_message[i][1];
									meter_task_addr[2]=meter_addr_message[i][2];
									meter_task_addr[3]=meter_addr_message[i][3];
									meter_task_addr[4]=meter_addr_message[i][4];
									meter_task_addr[5]=meter_addr_message[i][5];
									meter_task_addr[6]=meter_addr_message[i][6];
									meter_task_addr[7]=meter_addr_message[i][7];
									meter_task_addr[8]=meter_addr_message[i][8];
									meter_task_addr[9]=meter_addr_message[i][9];
									meter_task_addr[10]=meter_addr_message[i][10];
									meter_task_addr[11]=meter_addr_message[i][11];
		              
					        STMFLASH_Read(FLASH_METER_NUMBER,(u16*)meter_number,4);	
		              if((task_2_id>meter_number[0])&&task_2_id<=32) meter_number[0] = meter_number[0]+1;
						     	write_meter_addr(task_2_id,meter_task_addr);
	              	setVersion(task_2_id,met);
		              delay_ms(10);
		              number_temp=(meter_addr_message[i][12]-'0')*10+(meter_addr_message[i][13]-'0');
		              if(task_2_id<=32&&task_2_id>=1)
									{
		                  STMFLASH_Write(FLASH_METER_NUMBER,(u16*)meter_number,4);
											meter_status[task_2_id-1+16] = 'A'; 
										  rep[23+pos] = 'B'; 
										  bitv[number_temp-1] =1;
									}
								  else if((task_2_id>32)&&(task_2_id<=64))
									{
					            meter_status[task_2_id-33+16] = 'B'; 	//清楚电表		
										  printf("\r\ndelete meter %d\r\n",task_2_id-33);
											rep[23+pos] = 'C'; 
										  bitv[task_2_id-33] =1;
									}                   			            		             		
         	printf("meter_addr_message:\r\n");
		      printf(meter_addr_message[i]);
		    	printf("\r\n");
				}
	        STMFLASH_Write(FLASH_METER_STATUS,(u16*)meter_status,64);
	        sum1 = bitv[0]*1+bitv[1]*2+bitv[2]*4+bitv[3]*8+bitv[4]*16+bitv[5]*32+bitv[6]*64+bitv[7]*128+bitv[8]*256+bitv[9]*512+bitv[10]*1024+bitv[11]*2048+bitv[12]*4096+bitv[13]*8192+bitv[14]*16384+bitv[15]*32768;
				  sum2 = bitv[16]*1+bitv[17]*2+bitv[18]*4+bitv[19]*8+bitv[20]*16+bitv[21]*32+bitv[22]*64+bitv[23]*128+bitv[24]*256+bitv[25]*512+bitv[26]*1024+bitv[27]*2048+bitv[28]*4096+bitv[29]*8192+bitv[30]*16384+bitv[31]*32768;
				  rep[24+pos] = (sum2/256)/16;
				  rep[25+pos] = (sum2/256)%16;
					rep[26+pos] = (sum2%256)/16;
				  rep[27+pos] = (sum2%256)%16;
				  rep[28+pos] = (sum1/256)/16;
				  rep[29+pos] = (sum1/256)%16;
					rep[30+pos] = (sum1%256)/16;
				  rep[31+pos] = (sum1%256)%16;
				for(i=24+pos;i<32+pos;i++)
				{
					switch(rep[i])
					{
						case 0:rep[i]='0';break;
						case 1:rep[i]='1';break;
						case 2:rep[i]='2';break;
						case 3:rep[i]='3';break;					
						case 4:rep[i]='4';break;
						case 5:rep[i]='5';break;
						case 6:rep[i]='6';break;
						case 7:rep[i]='7';break;
						case 8:rep[i]='8';break;
						case 9:rep[i]='9';break;
						case 10:rep[i]='A';break;
						case 11:rep[i]='B';break;
						case 12:rep[i]='C';break;
						case 13:rep[i]='D';break;
						case 14:rep[i]='E';break;
						case 15:rep[i]='F';break;
						default:break;
					}
				}
	       	rep[32+pos] = '2';
				  rep[33+pos] = 'D';
					rep[34+pos] = imei[0];
					rep[35+pos] = imei[1];
					rep[36+pos] = imei[2];
					rep[37+pos] = imei[3];
					rep[38+pos] = imei[4];
					rep[39+pos] = imei[5];
					rep[40+pos] = imei[6];
					rep[41+pos] = imei[7];
					rep[42+pos] = imei[8];
					rep[43+pos] = imei[9];
					rep[44+pos] = imei[10];
					rep[45+pos] = imei[11];
					rep[46+pos] = imei[12];
					rep[47+pos] = imei[13];
					rep[48+pos] = imei[14];
					rep[49+pos] = '0';
							
				
				  rep[50+pos] = '\r';
			  	rep[51+pos] = '\n';
				  UART2_Print(rep);
			  	printf(rep);
	               // meter_number[0]=meters_get;
				        //  meter_number[0]=meters_get+meter_number[0];
			  	STMFLASH_Write(FLASH_METER_NUMBER,(u16*)meter_number,4);

#ifdef DEBUG
	printf("meter addr is:");
  printf(meter_task_addr);
	printf("\r\n");
#endif
}
u8 order_3_task(u8 *mes,Meter * met)
{
	printf("get cloud replay messsage\r\n");
}
extern u8 order_sum[100];

u8 order_4_task(u8 *mes,Meter * met)
{
	u8 ip_len= ipLen;
	u8 pos =0;
	u8 rep[100];
	u8 rep_sta[200];
	u8 i;
	u16 j = 0;
	u16 dj=0;
	rep[0] = 'A';
	rep[1] = 'T';
	rep[2] = '+';
	rep[3] = 'N';
	rep[4] = 'S';
	rep[5] = 'O';
	rep[6] = 'S';
	rep[7] = 'T';
	rep[8] = '=';
	rep[9] = '0';
	rep[10] = ',';
	for(pos=0;pos<ip_len;pos++)
	rep[11+pos] = UDP_IP[pos];
	rep[11+pos] = ',';
	rep[12+pos] = UDP_SOCKET[0];
	rep[13+pos] = UDP_SOCKET[1];
	rep[14+pos] = UDP_SOCKET[2];
	rep[15+pos] = UDP_SOCKET[3];
	rep[16+pos] = ',';
	
	rep[22+pos] = imei[0];
	rep[23+pos] = imei[1];
	rep[24+pos] = imei[2];
	rep[25+pos] = imei[3];
	rep[26+pos] = imei[4];
	rep[27+pos] = imei[5];
	rep[28+pos] = imei[6];
	rep[29+pos] = imei[7];
	rep[30+pos] = imei[8];
	rep[31+pos] = imei[9];
	rep[32+pos] = imei[10];
	rep[33+pos] = imei[11];
	rep[34+pos] = imei[12];
	rep[35+pos] = imei[13];
	rep[36+pos] = imei[14];
	rep[37+pos] = '0';
	
	TIM_Cmd(TIM2, DISABLE);  //close tick
  TIM_Cmd(TIM3, DISABLE);  //close tick
	for(i=0;i<32;i++)
	{
		 IWDG_Feed();//喂狗
		if(order_sum[i]=='2')
		{
			if(verify())
			{
					meter_cutoff((i+1),met);
					IWDG_Feed();//喂狗
					rep_sta[j++]= (i+1)/10 + '0';
					rep_sta[j++]= (i+1)%10 + '0';
					rep_sta[j++]= '2';
					rep_sta[j++]= 'D';
			}
		}
		else if(order_sum[i]=='1')
		{
			if(verify())
			{
					meter_connect((i+1),met);	
					IWDG_Feed();//喂狗
					rep_sta[j++]= (i+1)/10 + '0';
					rep_sta[j++]= (i+1)%10 + '0';
					rep_sta[j++]= '2';
					rep_sta[j++]= 'C';
			}
		}
	}
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
  TIM_Cmd(TIM3, ENABLE);  //使能TIMx 
	rep_sta[j++]= 'E';
	rep_sta[j++]= 'F';
	rep_sta[j++]= '\r';
	rep_sta[j++]= '\n';
  j= (j-4)/2+10;   
			rep[17+pos] = j/10 + '0';
			rep[18+pos] = j%10 + '0';
      rep[19+pos] = ',';
      rep[20+pos] = 'A';
    	rep[21+pos] = 'F';
	
		  for(i=38+pos;i<200;i++)
			{
				rep[i] = rep_sta[dj++];
				if(rep_sta[dj]=='\n') break;
			}			
			  printf("%c\r\n\r\n",rep[17+pos]);
			  printf("%c\r\n\r\n",rep[18+pos]);
				printf("%d\r\n\r\n",j);
	UART2_Print(rep);
	printf("meter command replay\r\n");
	printf(rep);
	for(i=0;i<200;i++) {order_sum[i] = 0; rep_sta[i] = 0;}
}
u8 order_5_task(u8 *mes,Meter * met)
{
	u8 i;
  setClock(clockMessage[0],clockMessage[1],clockMessage[2],clockMessage[3],clockMessage[4],clockMessage[5],clockMessage[6],clockMessage[7],clockMessage[8],clockMessage[9],clockMessage[10],clockMessage[11]);
	printf("clockMessage:%s\r\n",clockMessage);
}
u8 order_6_task(u8 *mes,Meter * met)   //
{
	u8 ip_len= ipLen;
	u8 pos =0;
	u8 rep[100];
	u8 rep_meter[200];
	u8 meter_command[100];
	u8 data_command_number=0;
	u8 serior_bound=0;
	u8 i;
	u16 j = 0;
	rep[0] = 'A';
	rep[1] = 'T';
	rep[2] = '+';
	rep[3] = 'N';
	rep[4] = 'S';
	rep[5] = 'O';
	rep[6] = 'S';
	rep[7] = 'T';
	rep[8] = '=';
	rep[9] = '0';
	rep[10] = ',';
	for(pos=0;pos<ip_len;pos++)
	rep[11+pos] = UDP_IP[pos];
	rep[11+pos] = ',';
	rep[12+pos] = UDP_SOCKET[0];
	rep[13+pos] = UDP_SOCKET[1];
	rep[14+pos] = UDP_SOCKET[2];
	rep[15+pos] = UDP_SOCKET[3];
	rep[16+pos] = ',';
	rep[17+pos] = '1';
	rep[18+pos] = '0';
	rep[19+pos] = ',';
  rep[20+pos] = 'D';
	rep[21+pos] = 'D';
	rep[22+pos] = imei[0];
	rep[23+pos] = imei[1];
	rep[24+pos] = imei[2];
	rep[25+pos] = imei[3];
	rep[26+pos] = imei[4];
	rep[27+pos] = imei[5];
	rep[28+pos] = imei[6];
	rep[29+pos] = imei[7];
	rep[30+pos] = imei[8];
	rep[31+pos] = imei[9];
	rep[32+pos] = imei[10];
	rep[33+pos] = imei[11];
	rep[34+pos] = imei[12];
	rep[35+pos] = imei[13];
	rep[36+pos] = imei[14];
	rep[37+pos] = '0';
	rep[38+pos] = 'D';
	rep[39+pos] = 'D';
	rep[40+pos] = '\r';
	rep[41+pos] = '\n';
	UART2_Print(rep);
	
	
	for(i=0;i<40+pos;i++)
	rep_meter[i] = rep[i];
	
	TIM_Cmd(TIM2, DISABLE);  //close tick
  TIM_Cmd(TIM3, DISABLE);  //close tick
	data_command_number=(command_message[0]-'0')*10+(command_message[1]-'0');
	serior_bound=(command_message[2]-'0')*16+(command_message[3]-'0');
	switch(serior_bound)
	{
		case 0X01:uart1_init(1200);break;
		case 0X02:uart1_init(2400);break;
		case 0X03:uart1_init(4800);break;
		case 0X04:uart1_init(9600);break;
		default:printf("serial bound error:%d\r\n",serior_bound);break;
	}
	for(i=0;i<data_command_number*2;i++)
	{
		switch(command_message[i+4])
		{
			case '0':command_message[i+4]=0;break;
			case '1':command_message[i+4]=1;break;
			case '2':command_message[i+4]=2;break;
			case '3':command_message[i+4]=3;break;
			case '4':command_message[i+4]=4;break;
			case '5':command_message[i+4]=5;break;
			case '6':command_message[i+4]=6;break;
			case '7':command_message[i+4]=7;break;
			case '8':command_message[i+4]=8;break;
			case '9':command_message[i+4]=9;break;
			case 'A':command_message[i+4]=0X0A;break;
			case 'B':command_message[i+4]=0X0B;break;
			case 'C':command_message[i+4]=0X0C;break;
			case 'D':command_message[i+4]=0X0D;break;
			case 'E':command_message[i+4]=0X0E;break;
			case 'F':command_message[i+4]=0X0F;break;
			default:break;
		}
	}
	for(i=0,j=0;i<data_command_number;i++)
	{
		meter_command[i]=command_message[j+4]*16+command_message[j+5];
		j+=2;
	}
	RS485_Set(Write);
	meter_databack_count = 0;
  UART1_TEST(meter_command,data_command_number);    
	RS485_Set(Read);
  delay_ms(2000);
	
	for(i=0,j=0;i<meter_databack_count;i++)
	{
	rep_meter[40+pos+j]=meter_databack[i]/16;
	j++;
	rep_meter[40+pos+j]=meter_databack[i]%16;
	j++;
	}
	
	for(i=40+pos;i<40+pos+j;i++)
	{
		switch(rep_meter[i])
		{
			case 0:rep_meter[i]='0';break;
			case 1:rep_meter[i]='1';break;
			case 2:rep_meter[i]='2';break;
			case 3:rep_meter[i]='3';break;
			case 4:rep_meter[i]='4';break;
			case 5:rep_meter[i]='5';break;
			case 6:rep_meter[i]='6';break;
			case 7:rep_meter[i]='7';break;
			case 8:rep_meter[i]='8';break;
			case 9:rep_meter[i]='9';break;
			case 10:rep_meter[i]='A';break;
			case 11:rep_meter[i]='B';break;
			case 12:rep_meter[i]='C';break;
			case 13:rep_meter[i]='D';break;
			case 14:rep_meter[i]='E';break;
			case 15:rep_meter[i]='F';break;
			default:break;
		}
	}
	rep_meter[17+pos] = '1'+meter_databack_count/10;
	rep_meter[18+pos] = '0'+meter_databack_count%10;
	rep_meter[40+pos+j]='\r';
	rep_meter[41+pos+j]='\n';
	UART2_Print(rep_meter);
#ifdef DEBUG
	printf(rep_meter);
#endif
	
	
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
  TIM_Cmd(TIM3, ENABLE);  //使能TIMx 
}

u8 order_7_task(u8 *mes,Meter * met)
{
	change_ip(ip_message);
	printf("change ip successful!\r\n");
}
u8 order_8_task()
{
	set_fre();
	return 1;
}
u8 order_task(u8 fun,u8 *mes,Meter * met)
{
	switch(fun)
	{
		case 1:order_1_task(mes,met);break;
		case 2:order_2_task(mes,met);break;
		case 3:order_3_task(mes,met);break;
		case 4:order_4_task(mes,met);break;
		case 5:order_5_task(mes,met);break;
		case 6:order_6_task(mes,met);break;
		case 7:order_7_task(mes,met);break;
		default: 
#ifdef DEBUG
	  //printf("no orders get\r\n");
#endif
		break;
	}
}