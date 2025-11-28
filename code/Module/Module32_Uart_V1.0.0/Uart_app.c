/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Uart.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/04/28
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

l_contSend l_contData = {0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //lcx move

uint16_t modbus_crc16(uint8_t *data, uint16_t length) 
{
    uint16_t crc = 0xFFFF;  // 初始值
    for (uint16_t i = 0; i < length; i++) 
    {
        crc ^= data[i];     // 与当前字节异或 
        for (uint8_t j = 0; j < 8; j++) {
            uint8_t lsb = crc & 0x01;  // 检查最低位 
            crc >>= 1;                 // 右移1位 
            if (lsb) crc ^= 0xA001;    // 若移出位为1，则异或多项式 
        }
    }
    return crc;
}

#if defined		UART3_lhh
/*
	unsigned char cont_Enable : 1;
	unsigned short set_Enable;
	unsigned char compHz;
	unsigned short indoor_Wind;
	unsigned short ourdoor_Wind;
	unsigned short elec_open;
	unsigned char four_is;
	unsigned char PFC_switch;
	unsigned char niuju_switch;
	unsigned char dianpure_switch;
	unsigned char outdoorHeat_switch;
	unsigned char	spare_one;
	unsigned short spare_two;
	unsigned short spare_three;
	*/

//l_contSend l_contData = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void    Uart3_Config_lhh(void)
{
		GPIO_InitStruType y;
    UART_InitStruType uart;
    memset(&y, 0, sizeof(y));
    memset(&uart, 0, sizeof(uart));

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_5;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_1, &y);               //PA26---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_4;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_0, &y);               //PA27---RxD

    uart.UART_StopBits = UART_StopBits_1;          //停止位个数:1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式:8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性:正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式:8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性:正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择:Pclk
    UART_Init(UART3, &uart);

    UART_TBIMConfig(UART3, UART_TRBIM_Byte);
    UART_RBIMConfig(UART3, UART_TRBIM_Byte);
    UART_ITConfig(UART3, UART_IT_RB, ENUM_ENABLE);
    NVIC_Init(NVIC_UART3_IRQn, NVIC_Priority_1, ENUM_ENABLE);
    UART3_TxEnable();                               //UART3发送使能
    UART3_RxEnable();								//UART3接收使能 
}

/****************************************************************************************************
Function Name       :void F_CRC16(unsigned char *Array, unsigned char *Rcvbuf, unsigned char Len) 
Description         :crc check
Input               :
Return              :
Author              :lhh  2024-1-8
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void F_CRC16(unsigned char *Array,  unsigned char Len) 
{
	unsigned short int  IX, IY;
	unsigned short int  CRC_val;
	CRC_val = 0xFFFF;//set all 1
	if (Len<=0)
	CRC_val = 0;
	else
	{
		Len--;
		for (IX=0;IX<=Len;IX++) 
		{
			CRC_val=CRC_val^(unsigned short int)(Array[IX]); 
			for(IY=0;IY<=7;IY++) 
			{
				if ((CRC_val&1)!=0) CRC_val=(CRC_val>>1)^0xA001; 
				else CRC_val=CRC_val>>1;    // 
			}
		} 
	}
	g_crcbuf[0] = (CRC_val & 0xff00)>>8;  // 
	g_crcbuf[1] = (CRC_val & 0x00ff);     // 
}  


/****************************************************************************************************
Function Name       :void app_Rec()
Description         :receive data from upper monitor
Input               :
Return              :
Author              :lhh 2024-1-8
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/

void app_Rec(void)
{ 
  unsigned short int first_address;
	switch(g_rxbuf[1])
	{
		case 0x03:			// read 5406to 5429 states
		{
			F_CRC16(g_rxbuf, g_rx_length-2);
			if((g_rxbuf[g_rx_length-1]==g_crcbuf[0])&&(g_rxbuf[g_rx_length-2]==g_crcbuf[1]))
			{
				first_address = (unsigned short)(((unsigned short)g_rxbuf[2]<<8) + (unsigned short)g_rxbuf[3]);
				if(first_address == 5406)
				{
                    send_Three_Data();
					
				}
				else
				{
					//first address err
				}
			}
			else
			{
   
				//crc err
				
			}
		} 
		break;
    
		case 0x10:	//write compress states 6402and 6403	
		{ 
			F_CRC16(g_rxbuf, g_16rx_length-2);
			if((g_rxbuf[g_16rx_length-1]==g_crcbuf[0])&&(g_rxbuf[g_16rx_length-2]==g_crcbuf[1]))
			{
				first_address = (unsigned short)(((unsigned short)g_rxbuf[2] <<8) + (unsigned short)g_rxbuf[3]);
				if(first_address == 6403)
				{
					l_contData.set_Enable = (unsigned short)(((unsigned short)g_rxbuf[7] <<8) + (unsigned short)g_rxbuf[8]);
					if(l_contData.set_Enable != 0)
					{
						if(l_contData.set_Enable & 0x0001)
						{
						//compHz = (unsigned short)(((unsigned short)g_rxbuf[9] <<8) + (unsigned short)g_rxbuf[10]);
							l_contData.compHz = (unsigned short)g_rxbuf[10];
							if(l_contData.compHz >80)  l_contData.compHz = 80;
						}
						if(l_contData.set_Enable & 0x0002)
						{
						 l_contData.indoor_Wind = (unsigned short)(((unsigned short)g_rxbuf[11] <<8) + (unsigned short)g_rxbuf[12]);
						}
						if(l_contData.set_Enable & 0x0004)
						{
						 l_contData.ourdoor_Wind = (unsigned short)(((unsigned short)g_rxbuf[13] <<8) + (unsigned short)g_rxbuf[14]);
						
						}
						if(l_contData.set_Enable & 0x0008)
						{
						 l_contData.elec_open = (unsigned short)(((unsigned short)g_rxbuf[15] <<8) + (unsigned short)g_rxbuf[16]);
						}
						if(l_contData.set_Enable & 0x0010)
						{
							if(g_rxbuf[17] == 1) l_contData.four_is = 1;
							else if(g_rxbuf[17] == 2) l_contData.four_is = 2;
							else l_contData.four_is = 0;
						}
						if(l_contData.set_Enable & 0x0020)
						{
						 l_contData.PFC_switch = g_rxbuf[18] ;
						
						}
						if(l_contData.set_Enable & 0x0040)
						{
						 l_contData.niuju_switch = g_rxbuf[19];
						}
						if(l_contData.set_Enable & 0x0080)
						{
						 l_contData.dianpure_switch = g_rxbuf[20];
						}
						if(l_contData.set_Enable & 0x0100)
						{
						l_contData.outdoorHeat_switch = g_rxbuf[21];
						}
						if(l_contData.set_Enable & 0x0200)
						{
						l_contData.spare_one = g_rxbuf[22];
						}
						
						if(l_contData.set_Enable & 0x0400)
						{
						 l_contData.spare_two = (unsigned short)(((unsigned short)g_rxbuf[23] <<8) + (unsigned short)g_rxbuf[24]);
						
						}
						if(l_contData.set_Enable & 0x0800)
						{
						 l_contData.spare_three = (unsigned short)(((unsigned short)g_rxbuf[25] <<8) + (unsigned short)g_rxbuf[26]);
						}
					}	
					
					l_contData.cont_Enable = 1;
						
					send_OneSix_Data();
				}
				else
				{
					//first address err
				}
			}
			else
			{
				//crc err	
			}
		}
		break;
		
		default:
		{
        //funtion code error
		}
	
	}
		
		
}

/****************************************************************************************************
Function Name       :void send_Three_Data()
Description         :根据功能应用发送信息帧
Input               :
Return              :
Author              :lhh 2024-1-8
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/

void send_Three_Data(void)
{
    g_txbuf[0] = 0x01; //地址码
    g_txbuf[1] = 0x03; //功能码
			
    g_txbuf[2] = 46;   //寄存器数量
				
    g_txbuf[3] = CommMotDrv.TxBuf.u8_Byte6;//Comp.u8_TargetHZ;    //压缩机目标频率
				
    g_txbuf[4] = Comp.u8_RealHZ; //压缩机运行频率

    g_txbuf[5] = 0x00;    //内机故障码
		g_txbuf[6] = 0x00;	  //
		/*
			1 为故障 0为正常
		System.f_InEEpromErr;		//EEPROM故障 F2
		F_uart4_CommErr;		   	//室内板与显示板通信故障 E8
		T1.f_Error;		   		//T1传感器故障
		T2.f_Error;		   		//T2传感器故障
		T3.f_Error;		   		//T3传感器故障	
		T4.f_Error;	   			//T4传感器故障
		Tp.f_Error;	   			//TP传感器故障
		*/

		g_txbuf[5] |= (unsigned char)System.f_InEEpromErr;
//		g_txbuf[5] |= (unsigned char)F_uart4_CommErr<<1;
		g_txbuf[5] |= (unsigned char)T1.f_Error<<2;
		g_txbuf[5] |= (unsigned char)T2.f_Error<<3;
		g_txbuf[5] |= (unsigned char)T3.f_Error<<4;
		g_txbuf[5] |= (unsigned char)T4.f_Error<<5;
		g_txbuf[5] |= (unsigned char)Tp.f_Error<<5;
		
		/*
			U8    f_VoltLowPro        :1;		//电压过低保护
			U8    f_CurrentProtect    :1;		//过电流保护
			U8	  f_InOutCommErr	  :1;		//室内外通信故障
			U8    f_OutEEpromErr	  :1;		//室外E方故障
			U8    f_InEEpromErr	  	  :1;		//室内E方故障
			U8    f_T4Limit   	      :1;		//T4限频作用下限频标志
			U8    f_T4LimitOff		  :1;		//T4限频引起停机标志
	*/
		g_txbuf[6] |= (unsigned char)System.f_VoltLowPro;
		g_txbuf[6] |= (unsigned char)System.f_CurrentProtect<<1;
		g_txbuf[6] |= (unsigned char)System.f_InOutCommErr<<2;
		g_txbuf[6] |= (unsigned char)System.f_OutEEpromErr<<3;
		g_txbuf[6] |= (unsigned char)System.f_InEEpromErr<<4;
		//g_txbuf[6] |= (unsigned char)System.f_T4Limit<<5;
		g_txbuf[6] |= (unsigned char)System.f_T4LimitOff<<6;
		
    g_txbuf[7] = 0x00;//内机保护码
		g_txbuf[8] = 0x00;//
		/*
		U8    f_Tp		  :1;		//排气温度保护
		U8    f_T2Cold    :1;		//制冷T2温度防冻结保护
		U8    f_T3Cold    :1;		//制冷T3温度防过热保护
		U8    f_CurrCold  :1;		//制冷电流过大保护
		U8    f_CurrHeat  :1;		//制热电流过大保护
		U8    f_CompCurr  :1;		//压缩机电流过大保护
		*/				
		g_txbuf[7] |= (unsigned char)Protect.f_Tp &0x01;
		g_txbuf[7] |= (unsigned char)Protect.f_T2Cold<<1;
		g_txbuf[7] |= (unsigned char)Protect.f_T3Cold<<2;
		g_txbuf[7] |= (unsigned char)Protect.f_CurrCold<<3;
		g_txbuf[7] |= (unsigned char)Protect.f_CurrHeat<<4;
		g_txbuf[7] |= (unsigned char)Protect.f_CompCurr<<5;
		
		
		g_txbuf[9] = 0x00;//外机故障码1	
		/*
			Fan.Indoor.f_Error  内机风机故障	
			Fan.Outdoor.f_Error 外风机故障
		*/
		
		g_txbuf[9] |= (unsigned char)Fan.Indoor.f_Error;//
		g_txbuf[9] |= (unsigned char)Fan.Outdoor.f_Error<<1;//
		
		g_txbuf[10] = 0x00;	//外机故障码2
		/*
				U8    f_FourWayAbn    :1;		//四通阀导致压机逼停
				U8    f_IPMPro		  :1;		//IPM模块保护
			U8    f_IPMErr		  :1;		//IPM模块故障
			U8    f_StartErr	  :1;		//启动故障
		*/
		g_txbuf[10] = (unsigned char)Comp.f_FourWayAbn;
		g_txbuf[10] = (unsigned char)Comp.f_IPMPro<<1;
		g_txbuf[10] = (unsigned char)Comp.f_IPMErr<<2;
		g_txbuf[10] = (unsigned char)Comp.f_StartErr<<3;
		
		g_txbuf[11] = 0x00;  //外机故障码3
		
		
		
				
    g_txbuf[12] = 0x00; //2	//外机保护标志1
    g_txbuf[13] = 0x00;//128	//外机保护标志2
				
    g_txbuf[14] = T1.s8_Value + 40; // T=25-40=-15 室内温度T+40
			
    g_txbuf[15] =  T2.s8_Value + 40; // T=26-40=-14 室内盘管温度T+40

    g_txbuf[16] = 0x00;//82	//室内湿度值
			
    g_txbuf[17] = T3.s8_Value + 40;//室外盘管温度16-40=-24			
    g_txbuf[18] = T4.s8_Value + 40;//室外环境温度30-40=-10
    
    g_txbuf[19] = Tp.s8_Value + 40; //1,室外排气温度=1-40=-39
				
    g_txbuf[20] = 0x00;    //IPM温度

    g_txbuf[21] = (unsigned char)(Fan.Indoor.u16_TargetRPM & 0x00ff);//内风机目标风速(Fan.Indoor.u16_TargetRPM & 0xff00)>>8;
    g_txbuf[22] = (unsigned char)((Fan.Indoor.u16_TargetRPM & 0xff00)>>8);
                
    g_txbuf[23] = (unsigned char)(Fan.Indoor.u16_RealRPM & 0x00ff);	//内风机实际运行风速
    g_txbuf[24] = (unsigned char)((Fan.Indoor.u16_RealRPM & 0xff00)>>8);	//
    
    g_txbuf[25] = 0x00;//电子膨胀阀开度
    g_txbuf[26] = 0x00;	
                
    g_txbuf[27] = (unsigned char)(Fan.Outdoor.u16_TargetRPM & 0x00ff);//外风机目标速度
    g_txbuf[28] = (unsigned char)((Fan.Outdoor.u16_TargetRPM & 0xff00)>>8);//
                
    g_txbuf[29] = (unsigned char)(Fan.Outdoor.u16_RealRPM & 0x00ff);//外风机实际运行速度
    g_txbuf[30] = (unsigned char)((Fan.Outdoor.u16_RealRPM & 0xff00)>>8);//
    
		//unsigned short l_mV =  (unsigned short)CommMotDrv.ReqSet.Rx.Byte13.u8_VoltBusValueDiv2<<1;
    g_txbuf[31] = 0x00;	//母线电压
    g_txbuf[32] = 0x00;//
     

		unsigned char IndoorMode = BaseRunTx_Byte5_InDoorRunMode();
		/*
			ENUM_MBDXBYTE5_RESERVED,	//预留 0 
			ENUM_MBDXBYTE5_COOL,		//制冷   1 
			ENUM_MBDXBYTE5_DRY,			//除湿   2
			ENUM_MBDXBYTE5_ONLYFAN,		//只送风  3
			ENUM_MBDXBYTE5_HEAT,		//制热   4
			ENUM_MBDXBYTE5_OFF,			//关机   5
			ENUM_MBDXBYTE5_FORCECOOL,	//强制制冷  6
			ENUM_MBDXBYTE5_DEFROST,		//化霜  7
			ENUM_MBDXBYTE5_COOLDRY,		//干燥清洁  8
			ENUM_MBDXBYTE5_COOLECO,		//制冷节能模式  9
		*/
    g_txbuf[33] = IndoorMode;// //室内运行模式
		
		
    g_txbuf[34] = l_outDoorMode; //室外运行模式
 
 
    g_txbuf[35] = 0x00;	//整机电流
    g_txbuf[36] = 0x00; //3200
                
    g_txbuf[37] = System.u16_ACVoltValue & 0x00ff;//交流电压
    g_txbuf[38] = (System.u16_ACVoltValue & 0x00ff)>>8;	//
                
    g_txbuf[39] = 0x00;	//PFC状态
                    
    g_txbuf[40] = Defrost.f_Enable;//55   化霜状态
                
    g_txbuf[41] = 0; //PFC电流
    g_txbuf[42] = 0; //0
                
    g_txbuf[43] = 0;		//预留1	
    g_txbuf[44] = 0;	
                
    g_txbuf[45] = 0;		//预留2
    g_txbuf[46] = 0;	
                
    g_txbuf[47] = 0; //预留3				
    g_txbuf[48] = 0;//
                
            
    F_CRC16(g_txbuf, 49);
    g_txbuf[49] = g_crcbuf[1];//crc
    g_txbuf[50] = g_crcbuf[0];//crc
    
    g_tx_length = 51;
    
    UART_ITConfig(UART3, UART_IT_TB, ENUM_ENABLE);    //??????,?????????????
}

/****************************************************************************************************
Function Name       :void send_OneSix_Data()
Description         :根据功能应用发送信息帧
Input               :
Return              :
Author              :lhh
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/

void send_OneSix_Data(void)
{
    g_txbuf[0] = 0x01; //
    g_txbuf[1] = 0x10;
                
    g_txbuf[2] = g_rxbuf[2];//6403
    g_txbuf[3] = g_rxbuf[3];
                
    g_txbuf[4] = g_rxbuf[4];//?????
    g_txbuf[5] = g_rxbuf[5]; 
                
    F_CRC16(g_txbuf, 6);
    g_txbuf[6] = g_crcbuf[1];//
    g_txbuf[7] = g_crcbuf[0];    		
    g_tx_length = 8;
    UART_ITConfig(UART3, UART_IT_TB, ENUM_ENABLE);    //??????,?????????????
}
#endif


#if defined		UART0_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart0(void) 
Description         :初始化串口0
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart0_Config(void)
{	
	GPIO_InitStruType y;
	UART_InitStruType uart;
	memset(&y, 0, sizeof(y));
	memset(&uart, 0, sizeof(uart));
	
    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_1, &y);               //PB1---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_0, &y);               //PB0---RxD

    uart.UART_StopBits = UART_StopBits_1;          //停止位个数:1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式:8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性:正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式:8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性:正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择:Pclk
    UART_Init(UART0, &uart);

    UART_TBIMConfig(UART0, UART_TRBIM_Byte);
    UART_RBIMConfig(UART0, UART_TRBIM_Byte);
    UART_ITConfig(UART0, UART_IT_RB, ENUM_ENABLE);
    NVIC_Init(NVIC_UART0_IRQn, NVIC_Priority_1, ENUM_ENABLE);
    UART0_TxEnable();                               //UART0发送使能
    UART0_RxEnable();								//UART0接收使能
}
/****************************************************************************************************
Function Name       :void	App_Uart0_Write_Frame(void)
Description         :根据功能应用发送信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_Uart0_Write_Frame(void)
{
    U8 i;

    U16 checksum;

    U8_Uart0_AppTxBuf[UART0_TX_HEAD_FIRST]   = C_UART0_TX_HEAD_FIRST;	 //头码1
//    U8_Uart0_AppTxBuf[UART0_TX_HEAD_SECOND]  = C_UART0_TX_HEAD_SECOND;   //头码2		

	U8_Uart0_AppTxBuf[1]  = C_COMMMOTDRV_TX_SRCADDR; //通讯源地址       //发送字节数据
    U8_Uart0_AppTxBuf[2]  = C_COMMMOTDRV_TX_TAGADDR; //通讯目标地址     //发送字节数据
    U8_Uart0_AppTxBuf[3]  = CommMotDrv.u8_TXCommand; //运行命令         //发送字节数据
    U8_Uart0_AppTxBuf[4]  = C_COMMMOTDRV_LENTH;      //参数长度         //发送字节数据
    U8_Uart0_AppTxBuf[5]  = CommMotDrv.TxBuf.u8_Byte5;                  //发送字节数据
    U8_Uart0_AppTxBuf[6]  = CommMotDrv.TxBuf.u8_Byte6;                  //发送字节数据
    U8_Uart0_AppTxBuf[7]  = CommMotDrv.TxBuf.u8_Byte7;                  //发送字节数据
    U8_Uart0_AppTxBuf[8]  = CommMotDrv.TxBuf.u8_Byte8;                  //发送字节数据
    U8_Uart0_AppTxBuf[9]  = CommMotDrv.TxBuf.u8_Byte9;                  //发送字节数据
    U8_Uart0_AppTxBuf[10] = CommMotDrv.TxBuf.u8_Byte10;                 //发送字节数据
 	U8_Uart0_AppTxBuf[11] = CommMotDrv.TxBuf.u8_Byte11;					//发送字节数据
    U8_Uart0_AppTxBuf[12] = CommMotDrv.TxBuf.u8_Byte12;                 //发送字节数据
    U8_Uart0_AppTxBuf[13] = CommMotDrv.TxBuf.u8_Byte13;                 //发送字节数据
    U8_Uart0_AppTxBuf[14] = CommMotDrv.TxBuf.u8_Byte14;                 //发送字节数据
    U8_Uart0_AppTxBuf[15] = CommMotDrv.TxBuf.u8_Byte15;                 //发送字节数据
    U8_Uart0_AppTxBuf[16] = CommMotDrv.TxBuf.u8_Byte16;                 //发送字节数据
    U8_Uart0_AppTxBuf[17] = CommMotDrv.TxBuf.u8_Byte17; 

    checksum = 0;
		
		if(CommMotDrv.u8_TXCommand == C_COMMMOTDRV_CMD_REQSET)
			l_contData.cont_Enable = 0;
    
    for (i=0; i<UART0_TX_CHKSUML; i++)
    {
        checksum += U8_Uart0_AppTxBuf[i];
    }
    
    checksum ^= 0xFFFF;
    checksum += 1;
    
    U8_Uart0_AppTxBuf[UART0_TX_CHKSUML] = checksum & 0xFF;                //校验-低位
	U8_Uart0_AppTxBuf[UART0_TX_CHKSUMH] = checksum >> 8;    

    for (i=0; i<UART0_TX_LEN; i++)                                        //(根据功能需要发送多少个字节,可能是常数可能是变量) =>  Uart0.u8_TxNum = UART_TX_LEN
    {
        U8_Uart0_TxBuf[i] = U8_Uart0_AppTxBuf[i];	
        U8_Uart0_AppTxBuf[i] = 0;
    }		
    
        
    if (Uart0.Enum_TxState == ENUM_TXSTATE_IDLE)	
    {
        F_uart0_TxReady = CF_ENABLE;
		
    }
}
/****************************************************************************************************
Function Name       :void	App_Uart0_Read_Frame(void)
Description         :根据功能应用接收信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Uart0_Read_Frame(void)
{
    U8  i;  
    U16  chksum;
	U8   ChkSumL, ChkSumH;
    volatile U8  temp;
             
    if (F_uart0_Receiving == CF_ENABLE)
    {
        if (Uart0.u8_RxTimerOut < C_UART_RXTIMEOUTCOUNT)
        {
            Uart0.u8_RxTimerOut++;
        }
        else
        {
            Uart0.u8_RxTimerOut = 0;
            F_uart0_Receiving = CF_DISABLE;
            F_uart0_RxComplete = CF_ENABLE;
        }
    }


    if (F_uart0_RxComplete == CF_ENABLE)
    {        
        chksum = 0;
        for (i=0; i<UART0_RX_CHKSUML; i++)
        {
            chksum += U8_Uart0_DrvRxBuf[i];
        }
        chksum ^= 0xFFFF;
        chksum += 1;
            
		ChkSumL = chksum & 0xFF;
		ChkSumH = chksum >> 8;
              
        if (U8_Uart0_DrvRxBuf[UART0_RX_HEAD_FIRST] == C_UART0_RX_HEAD_FIRST)   	//头码正确
        {
            if ((U8_Uart0_DrvRxBuf[UART0_RX_CHKSUML] == ChkSumL) && (U8_Uart0_DrvRxBuf[UART0_RX_CHKSUMH] == ChkSumH))             //检验通过，指令处理
            {
                           
                for (i=0; i<UART0_RX_LEN; i++)
                {
                    U8_Uart0_RxBuf[i] = U8_Uart0_DrvRxBuf[i];
                }
                

                //数据接收分析
				if ((U8_Uart0_RxBuf[1] == C_COMMMOTDRV_RX_SRCADDR) && (U8_Uart0_RxBuf[2] == C_COMMMOTDRV_RX_TAGADDR) && (U8_Uart0_RxBuf[4] == C_COMMMOTDRV_LENTH))  
				{
					CommMotDrv.u8_RXCommand = U8_Uart0_RxBuf[3];                
								   
					CommMotDrv.RxBuf.u8_Byte5  = U8_Uart0_RxBuf[5];                //接收数据
					CommMotDrv.RxBuf.u8_Byte6  = U8_Uart0_RxBuf[6];                //接收数据
					CommMotDrv.RxBuf.u8_Byte7  = U8_Uart0_RxBuf[7];                //接收数据
					CommMotDrv.RxBuf.u8_Byte8  = U8_Uart0_RxBuf[8];                //接收数据
					CommMotDrv.RxBuf.u8_Byte9  = U8_Uart0_RxBuf[9];                //接收数据
					CommMotDrv.RxBuf.u8_Byte10 = U8_Uart0_RxBuf[10];               //接收数据
					CommMotDrv.RxBuf.u8_Byte11 = U8_Uart0_RxBuf[11];               //接收数据
					CommMotDrv.RxBuf.u8_Byte12 = U8_Uart0_RxBuf[12];               //接收数据
					CommMotDrv.RxBuf.u8_Byte13 = U8_Uart0_RxBuf[13];               //接收数据
					CommMotDrv.RxBuf.u8_Byte14 = U8_Uart0_RxBuf[14];               //接收数据
					CommMotDrv.RxBuf.u8_Byte15 = U8_Uart0_RxBuf[15];               //接收数据
					CommMotDrv.RxBuf.u8_Byte16 = U8_Uart0_RxBuf[16];               //接收数据
					CommMotDrv.RxBuf.u8_Byte17 = U8_Uart0_RxBuf[17];               //接收数据
				}

                
                Uart0.u16_AbnormalCount = 0;                  //收到完整数据，清零通讯超时计数
                F_uart0_TimeOut = CF_DISABLE;                //通讯正常
				F_uart0_CommErr = CF_DISABLE;
				Uart0.u16_ErrCount = 0;                          
            }
            
            /***一定要在处理完接收数据后才清零，因为清零后串口会开始接收数据，会覆盖旧的数据***/
            F_uart0_RxComplete = CF_DISABLE;
            Uart0.u8_RxCnt = 0;
        }
    }


    if (Uart0.u16_AbnormalCount >= 25)							//连续2.5s接收异常强制发送复位
    {
        Uart0.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
//        Uart0.u8_TxCnt = 0;								        //通信超时强制发送状态复位(波特率较低不要清0)
    }

    if (++Uart0.u16_AbnormalCount >= C_UART_ABNORMALCOUNT)       //通信超时
    {
        Uart0.u16_AbnormalCount = C_UART_ABNORMALCOUNT;
        F_uart0_TimeOut = CF_ENABLE;

        if (++Uart0.u16_ErrCount >= C_UART_ERRCOUNT)
        {
            Uart0.u16_ErrCount = C_UART_ERRCOUNT;
			F_uart0_CommErr = CF_ENABLE;
        }	
    
        Uart0.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
//        Uart0.u8_TxCnt = 0;								        //通信超时强制发送状态复位(波特率较低不要清0)
        
    }
    else
    {
        F_uart0_TimeOut = CF_DISABLE;
        F_uart0_CommErr = CF_DISABLE;
        Uart0.u16_ErrCount = 0;
    }	
}
#endif

#if defined		UART1_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart1(void) 
Description         :初始化串口1
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart1_Config(void)
{
	GPIO_InitStruType y;
	UART_InitStruType uart;
	memset(&y, 0, sizeof(y));
	memset(&uart, 0, sizeof(uart));
	
    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_3, &y);               //PB3---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_2, &y);               //PB2---RxD

    uart.UART_StopBits = UART_StopBits_1;          //停止位个数:1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式:8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性:正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式:8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性:正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择:Pclk
    UART_Init(UART1, &uart);

    UART_TBIMConfig(UART1, UART_TRBIM_Byte);
    UART_RBIMConfig(UART1, UART_TRBIM_Byte);
    UART_ITConfig(UART1, UART_IT_RB, ENUM_ENABLE);
    NVIC_Init(NVIC_UART1_IRQn, NVIC_Priority_1, ENUM_ENABLE);
    UART1_TxEnable();                               //UART1发送使能
    UART1_RxEnable();								//UART1接收使能 
   
}
/****************************************************************************************************
Function Name       :void	App_Uart1_Write_Frame(void)
Description         :根据功能应用发送信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_Uart1_Write_Frame(void)
{
    U8 i;

    U8 checksum;

    U8_Uart1_AppTxBuf[UART1_TX_HEAD_FIRST]   = C_UART1_TX_HEAD_FIRST;	//头码1
    U8_Uart1_AppTxBuf[UART1_TX_HEAD_SECOND]  = C_UART1_TX_HEAD_SECOND;  //头码2		

    U8_Uart1_AppTxBuf[2]  = 0;                                          //发送字节数据
    U8_Uart1_AppTxBuf[3]  = 0;                                          //发送字节数据
    U8_Uart1_AppTxBuf[4]  = 0;                                          //发送字节数据
    U8_Uart1_AppTxBuf[5]  = 0;                                          //发送字节数据
    U8_Uart1_AppTxBuf[6]  = 0;                                          //发送字节数据
    U8_Uart1_AppTxBuf[7]  = 0;                                          //发送字节数据
    U8_Uart1_AppTxBuf[8]  = 0;                                          //发送字节数据
    U8_Uart1_AppTxBuf[9]  = 0;                                          //发送字节数据
    U8_Uart1_AppTxBuf[10] = 0;                                          //发送字节数据
    
    checksum = 0;
    
    for (i=0; i<UART1_TX_CHKSUM; i++)
    {
        checksum += U8_Uart1_AppTxBuf[i];
    }
    
    checksum ^= 0xFF;
    checksum += 1;
    
    U8_Uart1_AppTxBuf[UART1_TX_CHKSUM] = checksum;                      //校验

    for (i=0; i<UART1_TX_LEN; i++)                                      //(根据功能需要发送多少个字节,可能是常数可能是变量) =>  Uart1.u8_TxNum = UART_TX_LEN
    {
        U8_Uart1_TxBuf[i] = U8_Uart1_AppTxBuf[i];	
        U8_Uart1_AppTxBuf[i] = 0;
    }		
    
        
    if (Uart1.Enum_TxState == ENUM_TXSTATE_IDLE)	
    {
        F_uart1_TxReady = CF_ENABLE;	
    }
} 
/****************************************************************************************************
Function Name       :void	App_Uart1_Read_Frame(void)
Description         :根据功能应用接收信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Uart1_Read_Frame(void)
{
    U8  i;  
    U8  chksum;
    volatile U8  temp;
             
    if (F_uart1_Receiving == CF_ENABLE)
    {
        if (Uart1.u8_RxTimerOut < C_UART_RXTIMEOUTCOUNT)
        {
            Uart1.u8_RxTimerOut++;
        }
        else
        {
            Uart1.u8_RxTimerOut = 0;
            F_uart1_Receiving = CF_DISABLE;
            F_uart1_RxComplete = CF_ENABLE;
        }
    }


    if (F_uart1_RxComplete == CF_ENABLE)
    {        
        chksum = 0;
        for (i=0; i<UART1_RX_CHKSUM; i++)
        {
            chksum += U8_Uart1_DrvRxBuf[i];
        }
        chksum ^= 0xFF;
        chksum += 1;
              
        if ((U8_Uart1_DrvRxBuf[UART1_RX_HEAD_FIRST] == C_UART1_RX_HEAD_FIRST) && (U8_Uart1_DrvRxBuf[UART1_RX_HEAD_SECOND] == C_UART1_RX_HEAD_SECOND))   //头码正确
        {
            if (U8_Uart1_DrvRxBuf[UART1_RX_CHKSUM] == chksum)              //检验通过，指令处理
            {
                           
                for (i=0; i<UART1_RX_LEN; i++)
                {
                    U8_Uart1_RxBuf[i] = U8_Uart1_DrvRxBuf[i];
                }
                

                //数据接收分析
                temp = U8_Uart1_RxBuf[2];                //接收数据
                temp = U8_Uart1_RxBuf[3];                //接收数据
                temp = U8_Uart1_RxBuf[4];                //接收数据
                temp = U8_Uart1_RxBuf[5];                //接收数据
                temp = U8_Uart1_RxBuf[6];                //接收数据


                
                Uart1.u16_AbnormalCount = 0;                 //收到完整数据，清零通讯超时计数
                F_uart1_TimeOut = CF_DISABLE;                //通讯正常
				F_uart1_CommErr = CF_DISABLE;
				Uart1.u16_ErrCount = 0; 				
                          
            }
            
            /***一定要在处理完接收数据后才清零，因为清零后串口会开始接收数据，会覆盖旧的数据***/
            F_uart1_RxComplete = CF_DISABLE;
            Uart1.u8_RxCnt = 0;
        }
    }


    if (Uart1.u16_AbnormalCount >= 25)							//连续2.5s接收异常强制发送复位
    {
        Uart1.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
        Uart1.u8_TxCnt = 0;								        //通信超时强制发送状态复位
    }

    if (++Uart1.u16_AbnormalCount >= C_UART_ABNORMALCOUNT)       //通信超时
    {
        Uart1.u16_AbnormalCount = C_UART_ABNORMALCOUNT;
        F_uart1_TimeOut = CF_ENABLE;

        if (++Uart1.u16_ErrCount >= C_UART_ERRCOUNT)
        {
            Uart1.u16_ErrCount = C_UART_ERRCOUNT;
			F_uart1_CommErr = CF_ENABLE;
        }	
    
        Uart1.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
        Uart1.u8_TxCnt = 0;								        //通信超时强制发送状态复位
        
    }
    else
    {
        F_uart1_TimeOut = CF_DISABLE;
        F_uart1_CommErr = CF_DISABLE;
        Uart1.u16_ErrCount = 0;
    }	
}
#endif

#if defined		UART2_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart2(void) 
Description         :初始化串口2
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart2_Config(void)
{
	GPIO_InitStruType y;
	UART_InitStruType uart;
	memset(&y, 0, sizeof(y));
	memset(&uart, 0, sizeof(uart));
	
    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_5;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_5, &y);               //PB5---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_4;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_4, &y);               //PB4---RxD

	uart.UART_StopBits = UART_StopBits_1;          //停止位个数:1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式:8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性:正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式:8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性:正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择:Pclk
    UART_Init(UART2, &uart);

    UART_TBIMConfig(UART2, UART_TRBIM_Byte);
    UART_RBIMConfig(UART2, UART_TRBIM_Byte);
    UART_ITConfig(UART2, UART_IT_RB, ENUM_ENABLE);
    NVIC_Init(NVIC_UART2_IRQn, NVIC_Priority_1, ENUM_ENABLE);
    
    UART2_TxEnable();                               //UART2发送使能
    UART2_RxEnable();								//UART2接收使能 
   
}

/****************************************************************************************************
Function Name       :void	App_UART2_Write_Frame(void)
Description         :根据功能应用发送信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_Uart2_Write_Frame(void)
{
	static uint16_t u16InDoorSpeedSetBak;
	uint16_t u16CRC;
	uint8_t i;
	if ((Fan.Indoor.u16_TargetRPM != 0) 
	 && (u16InDoorSpeedSetBak == 0))
	{
		Fan.Indoor.SetMBStatus = ENUM_FANSETMB_ONSPEEDSET;  
	}
	else if ((Fan.Indoor.u16_TargetRPM == 0) 
	 && (u16InDoorSpeedSetBak != 0))
	{
		Fan.Indoor.SetMBStatus = ENUM_FANSETMB_OFFSET;  
	}
	else if ((Fan.Indoor.u16_TargetRPM != 0) 
	 && (u16InDoorSpeedSetBak != 0)
	 && (u16InDoorSpeedSetBak != Fan.Indoor.u16_TargetRPM))
	{
		Fan.Indoor.SetMBStatus = ENUM_FANSETMB_RUNSPEEDSET;  
	}
	else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_INIT)
	{
		Fan.Indoor.SetMBStatus = ENUM_FANSETMB_OFFSET;
	}
	u16InDoorSpeedSetBak = Fan.Indoor.u16_TargetRPM;


	Uart2.u8_TxNum = 8;	
	if ((Fan.Indoor.SetMBStatus == ENUM_FANSETMB_SPEEDSETRANGE))
	{
		U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
	    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND06;  //头码2	
	    U8_Uart2_AppTxBuf[2] = 0x04;
	    U8_Uart2_AppTxBuf[3] = 0x52;
	    //Fan.Indoor.u16_TargetRPM
	    U8_Uart2_AppTxBuf[4] = 0x05;
	    U8_Uart2_AppTxBuf[5] = 0xDC;
	}
	else if ((Fan.Indoor.SetMBStatus == ENUM_FANSETMB_ONSPEEDSET)
	 || (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_RUNSPEEDSET)
	 || (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_ONSET))
	{//风速设定
		U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
	    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND10;  //头码2	
	    U8_Uart2_AppTxBuf[2] = 0x03;
	    U8_Uart2_AppTxBuf[3] = 0xE7;
	    U8_Uart2_AppTxBuf[4] = 0;
	    U8_Uart2_AppTxBuf[5] = 2;
	    U8_Uart2_AppTxBuf[6] = 4;
	    //Fan.Indoor.u16_TargetRPM
	    U8_Uart2_AppTxBuf[7] = (U8)((Fan.Indoor.u16_TargetRPM ) >>8);//4;//
	    U8_Uart2_AppTxBuf[8] = (U8)(Fan.Indoor.u16_TargetRPM );	//0xB0;
	    U8_Uart2_AppTxBuf[9] = 0;
	    U8_Uart2_AppTxBuf[10] = 3;
		Uart2.u8_TxNum = 13;
	}
//	else if ((Fan.Indoor.SetMBStatus == ENUM_FANSETMB_ONSPEEDSET)
//	 || (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_RUNSPEEDSET))
//	{//风速设定
//		U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
//	    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND06;  //头码2	
//	    U8_Uart2_AppTxBuf[2] = 0x03;
//	    U8_Uart2_AppTxBuf[3] = 0xE7;
//	    //Fan.Indoor.u16_TargetRPM
//	    U8_Uart2_AppTxBuf[4] = (U8)((Fan.Indoor.u16_TargetRPM ) >>8);
//	    U8_Uart2_AppTxBuf[5] = (U8)(Fan.Indoor.u16_TargetRPM );
//	}
//	else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_ONSET)
//	{
//		U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
//	    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND06;  //头码2
//	    U8_Uart2_AppTxBuf[2] = 0x03;		//地址
//	    U8_Uart2_AppTxBuf[3] = 0xE8;
//	    U8_Uart2_AppTxBuf[4] = 0;		
//	    U8_Uart2_AppTxBuf[5] = 3;
//	}
	else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_RUNCHECK)
	{//查询故障和开机命令
		U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
	    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND03;  //头码2
	    U8_Uart2_AppTxBuf[2] = 0x04;
	    U8_Uart2_AppTxBuf[3] = 0x4B;	//地址
	    U8_Uart2_AppTxBuf[4] = 0;		
	    U8_Uart2_AppTxBuf[5] = 6;
	}
	else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_ONSPEEDSETCHECK)
	{
		U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
	    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND03;  //头码2
	    U8_Uart2_AppTxBuf[2] = 0x03;
	    U8_Uart2_AppTxBuf[3] = 0xE7;	//地址
	    U8_Uart2_AppTxBuf[4] = 0;		
	    U8_Uart2_AppTxBuf[5] = 1;
	}
	else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_OFFSET)
	{
		U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
	    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND06;  //头码2
	    U8_Uart2_AppTxBuf[2] = 0x03;		//地址
	    U8_Uart2_AppTxBuf[3] = 0xE8;
	    U8_Uart2_AppTxBuf[4] = 0;		
	    U8_Uart2_AppTxBuf[5] = 2;
	}
	else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_OFFCHECK)
	{
		U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
	    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND03;  //头码2
	    U8_Uart2_AppTxBuf[2] = 0x04;
	    U8_Uart2_AppTxBuf[3] = 0x4B;	//地址
	    U8_Uart2_AppTxBuf[4] = 0;		
	    U8_Uart2_AppTxBuf[5] = 1;
	}
	
	
	
	u16CRC = modbus_crc16(U8_Uart2_AppTxBuf,(Uart2.u8_TxNum - 2));
	U8_Uart2_AppTxBuf[Uart2.u8_TxNum -2] = (U8)(u16CRC);
	U8_Uart2_AppTxBuf[Uart2.u8_TxNum -1] = (U8)(u16CRC >>8);
	
	for (i=0; i<Uart2.u8_TxNum/*UART2_TX_LEN*/; i++)                                      //(根据功能需要发送多少个字节,可能是常数可能是变量) =>  Uart2.u8_TxNum = UART_TX_LEN
    {
        U8_Uart2_TxBuf[i] = U8_Uart2_AppTxBuf[i];	
        U8_Uart2_AppTxBuf[i] = 0;
    }	
    
//	if (Uart2.f_txok)
//	{
		Uart2.u8_WaitCount++;
//	Uart2.u8_WaitCount++;

	if (Uart2.u8_WaitCount >= 3)	//300ms
	{
		Uart2.u8_WaitCount = 0;
		
		if (Uart2.Enum_TxState == ENUM_TXSTATE_IDLE)	
		{
			F_uart2_TxReady = CF_ENABLE;

			Uart2.f_txok = 0;
			Uart2.u8_WaitCount = 0;
		}
	}
}
//{
//    U8 i;
//	U8 temp;
//    U8 checksum;
//
//    U8_Uart2_AppTxBuf[UART2_TX_HEAD_FIRST]   = C_UART2_TX_HEAD_FIRST;	//头码1
//    U8_Uart2_AppTxBuf[UART2_TX_HEAD_SECOND]  = C_UART2_TX_HEAD_SECOND;  //头码2		
//
//    U8_Uart2_AppTxBuf[2]  = 0x00;  					 //目标地址                                       
//    
//	if (WiFi.f_Reset)	//操作wifi复位
//	{
//		U8_Uart2_AppTxBuf[3]  = 0x03;
//	}
//	else
//	{
//		U8_Uart2_AppTxBuf[3]  = U8_Uart2_RxBuf[3];       //功能码  	
//	}
//	
//	if (U8_Uart2_RxBuf[3] == 0x05)		//网络命令
//	{
//		U8_Uart2_AppTxBuf[4]  = 0x0B;       //数据长度 
//		U8_Uart2_AppTxBuf[5]  = 0x02;       
//		U8_Uart2_AppTxBuf[6]  = 0x00;       
//		U8_Uart2_AppTxBuf[7]  = 0x00;                                           
//		U8_Uart2_AppTxBuf[8]  = 0x00;                                           
//		U8_Uart2_AppTxBuf[9]  = 0x00;                                           
//		U8_Uart2_AppTxBuf[10] = 0x00;                                           
//		U8_Uart2_AppTxBuf[11] = 0x00;       
//		U8_Uart2_AppTxBuf[12] = 0x00;       
//		U8_Uart2_AppTxBuf[13] = 0x00;                                           
//		U8_Uart2_AppTxBuf[14] = 0x00;
//		
//		temp = U8_Uart2_RxBuf[13];
//		U8_Uart2_AppTxBuf[15] = temp;
//		
//		if (temp == 0x08)	//Config
//		{
//			WiFi.Enum_Status = ENUM_TWIFISTATUS_CONFIG;
//		}
//		else if (temp == 0x04)	//PP
//		{
//			WiFi.Enum_Status = ENUM_TWIFISTATUS_PP;
//		}
//		else if (temp == 0x02)	//SA
//		{
//			WiFi.Enum_Status = ENUM_TWIFISTATUS_SA;
//		}
//		else if (temp == 0x01)	//AP
//		{
//			WiFi.Enum_Status = ENUM_TWIFISTATUS_AP;
//
//			if (Tempr.u8_TempFSet == 89)	//应对显示板程序问题
//			{
//				Tempr.u8_TempCSet = 32;
//			}	
//				
//		}
//		else
//		{
//			WiFi.Enum_Status = ENUM_TWIFISTATUS_NULL;
//		}
//		
//		Uart2.u8_TxNum = 17;
//		
//	}
//	else				 								 //接收传输命令0x03或者查询命令0x04
//	{
//		if (WiFi.f_Reset)
//		{
//			U8_Uart2_AppTxBuf[4] = 0x0B;       //数据长度 
//			
//			U8_Uart2_AppTxBuf[5] = 0x02;
//			U8_Uart2_AppTxBuf[6] = 0x00;
//			U8_Uart2_AppTxBuf[7] = 0x00;
//			U8_Uart2_AppTxBuf[8] = 0x00;
//			U8_Uart2_AppTxBuf[9] = 0x00;
//			U8_Uart2_AppTxBuf[10] = 0x00;
//			U8_Uart2_AppTxBuf[11] = 0x00;
//			U8_Uart2_AppTxBuf[12] = 0x00;
//			U8_Uart2_AppTxBuf[13] = 0x00;
//			U8_Uart2_AppTxBuf[14] = 0x00;
//			U8_Uart2_AppTxBuf[15] = 0x80;		//reset
//			
//			Uart2.u8_TxNum = 17;
//		}			
//		else
//		{	
//			
//			U8_Uart2_AppTxBuf[4]  = 0x3C;       //数据长度                   	   
//			
//			U8_Uart2_AppTxBuf[5]  = WiFi.Slave.Byte1.Byte;       
//			U8_Uart2_AppTxBuf[6]  = WiFi.Slave.Byte2.Byte;       
//			U8_Uart2_AppTxBuf[7]  = WiFi.Slave.Byte3.Byte;                                           
//			U8_Uart2_AppTxBuf[8]  = WiFi.Slave.Byte4.Byte;                                           
//			U8_Uart2_AppTxBuf[9]  = WiFi.Slave.Byte5.Byte;                                           
//			U8_Uart2_AppTxBuf[10] = WiFi.Slave.Byte6.Byte;                                           
//			U8_Uart2_AppTxBuf[11] = WiFi.Slave.Byte7.Byte;       
//			U8_Uart2_AppTxBuf[12] = WiFi.Slave.Byte8.Byte;       
//			U8_Uart2_AppTxBuf[13] = WiFi.Slave.Byte9.Byte;                                           
//			U8_Uart2_AppTxBuf[14] = WiFi.Slave.Byte10.Byte;    
//			
//			U8_Uart2_AppTxBuf[15] = WiFi.Slave.Byte11.Byte;       
//			U8_Uart2_AppTxBuf[16] = WiFi.Slave.Byte12.Byte;       
//			U8_Uart2_AppTxBuf[17] = WiFi.Slave.Byte13.Byte;                                           
//			U8_Uart2_AppTxBuf[18] = WiFi.Slave.Byte14.Byte;                                           
//			U8_Uart2_AppTxBuf[19] = WiFi.Slave.Byte15.Byte;                                           
//			U8_Uart2_AppTxBuf[20] = WiFi.Slave.Byte16.Byte;                                           
//			U8_Uart2_AppTxBuf[21] = WiFi.Slave.Byte17.Byte;       
//			U8_Uart2_AppTxBuf[22] = WiFi.Slave.Byte18.Byte;       
//			U8_Uart2_AppTxBuf[23] = WiFi.Slave.Byte19.Byte;                                           
//			U8_Uart2_AppTxBuf[24] = WiFi.Slave.Byte20.Byte;	
//
//			U8_Uart2_AppTxBuf[25] = WiFi.Slave.Byte21.Byte;       
//			U8_Uart2_AppTxBuf[26] = WiFi.Slave.Byte22.Byte;       
//			U8_Uart2_AppTxBuf[27] = WiFi.Slave.Byte23.Byte;                                           
//			U8_Uart2_AppTxBuf[28] = WiFi.Slave.Byte24.Byte;                                           
//			U8_Uart2_AppTxBuf[29] = WiFi.Slave.Byte25.Byte;                                           
//			U8_Uart2_AppTxBuf[30] = WiFi.Slave.Byte26.Byte;                                           
//			U8_Uart2_AppTxBuf[31] = WiFi.Slave.Byte27.Byte;       
//			U8_Uart2_AppTxBuf[32] = WiFi.Slave.Byte28.Byte;       
//			U8_Uart2_AppTxBuf[33] = WiFi.Slave.Byte29.Byte;                                           
//			U8_Uart2_AppTxBuf[34] = WiFi.Slave.Byte30.Byte;	
//
//			U8_Uart2_AppTxBuf[35] = WiFi.Slave.Byte31.Byte;       
//			U8_Uart2_AppTxBuf[36] = WiFi.Slave.Byte32.Byte;       
//			U8_Uart2_AppTxBuf[37] = WiFi.Slave.Byte33.Byte;                                           
//			U8_Uart2_AppTxBuf[38] = WiFi.Slave.Byte34.Byte;                                           
//			U8_Uart2_AppTxBuf[39] = WiFi.Slave.Byte35.Byte;                                           
//			U8_Uart2_AppTxBuf[40] = WiFi.Slave.Byte36.Byte;                                           
//			U8_Uart2_AppTxBuf[41] = WiFi.Slave.Byte37.Byte;       
//			U8_Uart2_AppTxBuf[42] = WiFi.Slave.Byte38.Byte;       
//			U8_Uart2_AppTxBuf[43] = WiFi.Slave.Byte39.Byte;                                           
//			U8_Uart2_AppTxBuf[44] = WiFi.Slave.Byte40.Byte;
//
//			U8_Uart2_AppTxBuf[45] = WiFi.Slave.Byte41.Byte;       
//			U8_Uart2_AppTxBuf[46] = WiFi.Slave.Byte42.Byte;       
//			U8_Uart2_AppTxBuf[47] = WiFi.Slave.Byte43.Byte;                                           
//			U8_Uart2_AppTxBuf[48] = WiFi.Slave.Byte44.Byte;                                           
//			U8_Uart2_AppTxBuf[49] = WiFi.Slave.Byte45.Byte;                                           
//			U8_Uart2_AppTxBuf[50] = WiFi.Slave.Byte46.Byte;                                           
//			U8_Uart2_AppTxBuf[51] = WiFi.Slave.Byte47.Byte;       
//			U8_Uart2_AppTxBuf[52] = WiFi.Slave.Byte48.Byte;       
//			U8_Uart2_AppTxBuf[53] = WiFi.Slave.Byte49.Byte;                                           
//			U8_Uart2_AppTxBuf[54] = WiFi.Slave.Byte50.Byte;
//			
//			U8_Uart2_AppTxBuf[55] = WiFi.Slave.Byte51.Byte;       
//			U8_Uart2_AppTxBuf[56] = WiFi.Slave.Byte52.Byte;       
//			U8_Uart2_AppTxBuf[57] = WiFi.Slave.Byte53.Byte;                                           
//			U8_Uart2_AppTxBuf[58] = WiFi.Slave.Byte54.Byte;                                           
//			U8_Uart2_AppTxBuf[59] = WiFi.Slave.Byte55.Byte;                                           
//			U8_Uart2_AppTxBuf[60] = WiFi.Slave.Byte56.Byte;                                           
//			U8_Uart2_AppTxBuf[61] = WiFi.Slave.Byte57.Byte;       
//			U8_Uart2_AppTxBuf[62] = WiFi.Slave.Byte58.Byte;       
//			U8_Uart2_AppTxBuf[63] = WiFi.Slave.Byte59.Byte;                                           
//			U8_Uart2_AppTxBuf[64] = WiFi.Slave.Byte60.Byte;
//
//
//			Uart2.u8_TxNum = 66;
//		}
//	}
//		
//    checksum = 0;
//    
//    for (i=0; i<(Uart2.u8_TxNum-1)/*UART2_TX_CHKSUM*/; i++)
//    {
//        checksum ^= U8_Uart2_AppTxBuf[i];
//    }
//    
////    checksum ^= 0xFF;
////    checksum += 1;
//    
//    U8_Uart2_AppTxBuf[(Uart2.u8_TxNum-1)/*UART2_TX_CHKSUM*/] = checksum;                      //校验
//
//    for (i=0; i<Uart2.u8_TxNum/*UART2_TX_LEN*/; i++)                                      //(根据功能需要发送多少个字节,可能是常数可能是变量) =>  Uart2.u8_TxNum = UART_TX_LEN
//    {
//        U8_Uart2_TxBuf[i] = U8_Uart2_AppTxBuf[i];	
//        U8_Uart2_AppTxBuf[i] = 0;
//    }		
//    
//       
//	if (Uart2.f_txok)
//	{
//		Uart2.u8_WaitCount++;
//
//	}
//	else
//	{
//		Uart2.u8_WaitCount = 0;
//
//	}
//		
//
//	if (Uart2.u8_WaitCount >= 3)	//300ms
//	{
//		Uart2.u8_WaitCount = 3;
//		
//		if (Uart2.Enum_TxState == ENUM_TXSTATE_IDLE)	
//		{
//			F_uart2_TxReady = CF_ENABLE;
//
//			Uart2.f_txok = 0;
//			Uart2.u8_WaitCount = 0;
//		}
//	}
//		
//} 
/****************************************************************************************************
Function Name       :void	App_Uart2_Read_Frame(void)
Description         :根据功能应用接收信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Uart2_Read_Frame(void)
{
    U8  i;  
    U8  chksum;
    uint16_t u16CRC,u16Spset,u16SetOn,u16DriverErr;
    volatile U8  temp;
             
    if (F_uart2_Receiving == CF_ENABLE)
    {
        if (Uart2.u8_RxTimerOut < C_UART_RXTIMEOUTCOUNT)
        {
            Uart2.u8_RxTimerOut++;
        }
        else
        {
            Uart2.u8_RxTimerOut = 0;
            F_uart2_Receiving = CF_DISABLE;
            F_uart2_RxComplete = CF_ENABLE;
        }
    }


    if (F_uart2_RxComplete == CF_ENABLE)
    {
		if (U8_Uart2_DrvRxBuf[UART2_RX_HEAD_FIRST] == C_UART2_RX_HEAD_FIRST)
		{
			u16CRC =  ((uint16_t)(U8_Uart2_DrvRxBuf[Uart2.u8_RxNum -1]) << 8);
			u16CRC += (uint16_t)U8_Uart2_DrvRxBuf[Uart2.u8_RxNum - 2];
			if (modbus_crc16(U8_Uart2_DrvRxBuf,(Uart2.u8_RxNum - 2)) == u16CRC)		//校验通过
			{
				if(U8_Uart2_DrvRxBuf[1] == 0x03)	//03命令
				{
//					Fan.Indoor.u16_RealRPM = (uint16_t)((U8_Uart2_DrvRxBuf[45]) << 8)
//											 + (uint16_t)(U8_Uart2_DrvRxBuf[46]);
					if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_ONSPEEDSETCHECK)
					{
						u16Spset =  (uint16_t)((U8_Uart2_DrvRxBuf[3]) << 8)
											 + (uint16_t)(U8_Uart2_DrvRxBuf[4]);
						if (u16Spset == 0)
						{
							Fan.Indoor.SetMBStatus = ENUM_FANSETMB_ONSPEEDSET;
						}
						else 
						{
							Fan.Indoor.SetMBStatus = ENUM_FANSETMB_ONSET;
						}
					}
					else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_RUNCHECK)
					{
						
						u16SetOn = (uint16_t)((U8_Uart2_DrvRxBuf[3]) << 8)
											 + (uint16_t)(U8_Uart2_DrvRxBuf[4]);

											 
						if ((U8_Uart2_DrvRxBuf[5] == 0) && (U8_Uart2_DrvRxBuf[6] == 0)
						&& (U8_Uart2_DrvRxBuf[7] == 0) && (U8_Uart2_DrvRxBuf[8] == 0)
						&& (U8_Uart2_DrvRxBuf[9] == 0) && (U8_Uart2_DrvRxBuf[10] == 0)
						&& (U8_Uart2_DrvRxBuf[11] == 0) && (U8_Uart2_DrvRxBuf[12] == 0))
						{
							u16DriverErr = 0;
						}
						else 
						{
							u16DriverErr = 1;
						}
						
					
						if ((u16DriverErr != 0) || (IFCB(u16SetOn,0) == 0))
						{
							Fan.Indoor.f_Error = 1;	
						}
						else 
						{
							Fan.Indoor.f_Error = 0;	
						} 
						Fan.Indoor.u16_RealRPM = (uint16_t)((U8_Uart2_DrvRxBuf[13]) << 8)
											 + (uint16_t)(U8_Uart2_DrvRxBuf[14]);
						Fan.Indoor.SetMBStatus = ENUM_FANSETMB_ONSET;
					}
					else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_OFFCHECK)
					{
						u16SetOn = (uint16_t)((U8_Uart2_DrvRxBuf[3]) << 8)
											 + (uint16_t)(U8_Uart2_DrvRxBuf[4]);

						if (IFCB(u16SetOn,0) == 0)
						{
							Fan.Indoor.SetMBStatus = ENUM_FANSETMB_OFFSET;
						}
					}
				}
				else 		//06命令
				{
					
					if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_SPEEDSETRANGE)
					{
						Fan.Indoor.SetMBStatus = ENUM_FANSETMB_ONSPEEDSET;
					} 
					else if ((Fan.Indoor.SetMBStatus == ENUM_FANSETMB_ONSPEEDSET)
						||(Fan.Indoor.SetMBStatus == ENUM_FANSETMB_RUNSPEEDSET))
					{
						Fan.Indoor.SetMBStatus = ENUM_FANSETMB_ONSPEEDSETCHECK;
					} 
					else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_ONSET)
					{
						Fan.Indoor.SetMBStatus = ENUM_FANSETMB_RUNCHECK;
					}
					else if (Fan.Indoor.SetMBStatus == ENUM_FANSETMB_OFFSET)
					{
						Fan.Indoor.SetMBStatus = ENUM_FANSETMB_OFFCHECK;
					}
					
				}

				Uart2.u16_AbnormalCount = 0;                 //收到完整数据，清零通讯超时计数
                F_uart2_TimeOut = CF_DISABLE;                //通讯正常
				F_uart2_CommErr = CF_DISABLE;
				Uart2.u16_ErrCount = 0; 				
                    
				Uart2.f_txok = 1;
				Uart2.u8_WaitCount = 0;
			}
			/***一定要在处理完接收数据后才清零，因为清零后串口会开始接收数据，会覆盖旧的数据***/
            F_uart2_RxComplete = CF_DISABLE;
            Uart2.u8_RxCnt = 0;
		}
    }
//    {        
//        chksum = 0;
//        for (i=0; i<(U8_Uart2_DrvRxBuf[4]+5)/*UART2_RX_CHKSUM*/; i++)
//        {
//            chksum ^= U8_Uart2_DrvRxBuf[i];
//        }
////        chksum ^= 0xFF;
////        chksum += 1;
//              
//        if ((U8_Uart2_DrvRxBuf[UART2_RX_HEAD_FIRST] == C_UART2_RX_HEAD_FIRST) && (U8_Uart2_DrvRxBuf[UART2_RX_HEAD_SECOND] == C_UART2_RX_HEAD_SECOND))   //头码正确
//        {
//            if (U8_Uart2_DrvRxBuf[(U8_Uart2_DrvRxBuf[4]+5)/*UART2_RX_CHKSUM*/] == chksum)              //检验通过，指令处理
//            {
//                           
//                for (i=0; i<(U8_Uart2_DrvRxBuf[4]+6)/*UART2_RX_LEN*/; i++)
//                {
//                    U8_Uart2_RxBuf[i] = U8_Uart2_DrvRxBuf[i];
//                }
//                
//
//				if ((U8_Uart2_RxBuf[2] == 0x01) && (U8_Uart2_RxBuf[3] == 0x03) && (U8_Uart2_RxBuf[4] == 0x1C))//功能码是0x03, 数据长度28,即APP有操作
//                {
//				
//					//数据接收分析
//					WiFi.Master.Byte1.Byte = U8_Uart2_RxBuf[5];               
//					WiFi.Master.Byte2.Byte = U8_Uart2_RxBuf[6];
//					WiFi.Master.Byte3.Byte = U8_Uart2_RxBuf[7];               
//					WiFi.Master.Byte4.Byte = U8_Uart2_RxBuf[8];
//					WiFi.Master.Byte5.Byte = U8_Uart2_RxBuf[9];               
//					WiFi.Master.Byte6.Byte = U8_Uart2_RxBuf[10];
//					WiFi.Master.Byte7.Byte = U8_Uart2_RxBuf[11];               
//					WiFi.Master.Byte8.Byte = U8_Uart2_RxBuf[12];
//					WiFi.Master.Byte9.Byte = U8_Uart2_RxBuf[13];               
//					WiFi.Master.Byte10.Byte = U8_Uart2_RxBuf[14];
//					WiFi.Master.Byte11.Byte = U8_Uart2_RxBuf[15];               
//					WiFi.Master.Byte12.Byte = U8_Uart2_RxBuf[16];
//					WiFi.Master.Byte13.Byte = U8_Uart2_RxBuf[17];               
//					WiFi.Master.Byte14.Byte = U8_Uart2_RxBuf[18];
//					WiFi.Master.Byte15.Byte = U8_Uart2_RxBuf[19];               
//					WiFi.Master.Byte16.Byte = U8_Uart2_RxBuf[20];
//					WiFi.Master.Byte17.Byte = U8_Uart2_RxBuf[21];               
//					WiFi.Master.Byte18.Byte = U8_Uart2_RxBuf[22];
//					WiFi.Master.Byte19.Byte = U8_Uart2_RxBuf[23];
//					WiFi.Master.Byte20.Byte = U8_Uart2_RxBuf[24];
//					WiFi.Master.Byte21.Byte = U8_Uart2_RxBuf[25];               
//					WiFi.Master.Byte22.Byte = U8_Uart2_RxBuf[26];
//					WiFi.Master.Byte23.Byte = U8_Uart2_RxBuf[27];               
//					WiFi.Master.Byte24.Byte = U8_Uart2_RxBuf[28];
//					WiFi.Master.Byte25.Byte = U8_Uart2_RxBuf[29];               
//					WiFi.Master.Byte26.Byte = U8_Uart2_RxBuf[30];
//					WiFi.Master.Byte27.Byte = U8_Uart2_RxBuf[31];
//					temp = U8_Uart2_RxBuf[32];
//				}
//
//                
//                Uart2.u16_AbnormalCount = 0;                 //收到完整数据，清零通讯超时计数
//                F_uart2_TimeOut = CF_DISABLE;                //通讯正常
//				F_uart2_CommErr = CF_DISABLE;
//				Uart2.u16_ErrCount = 0; 				
//                    
//				Uart2.f_txok = 1;
//				Uart2.u8_WaitCount = 0;
//
//            }
//            
//            /***一定要在处理完接收数据后才清零，因为清零后串口会开始接收数据，会覆盖旧的数据***/
//            F_uart2_RxComplete = CF_DISABLE;
//            Uart2.u8_RxCnt = 0;
//        }
//    }


//    if (Uart2.u16_AbnormalCount >= 25)							//连续2.5s接收异常强制发送复位
//    {
//        Uart2.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
//        Uart2.u8_TxCnt = 0;								        //通信超时强制发送状态复位
//    }

    if (++Uart2.u16_AbnormalCount >= C_UART_ABNORMALCOUNT)       //通信超时
    {
        Uart2.u16_AbnormalCount = C_UART_ABNORMALCOUNT;
        F_uart2_TimeOut = CF_ENABLE;

        if (++Uart2.u16_ErrCount >= C_UART_ERRCOUNT)
        {
            Uart2.u16_ErrCount = C_UART_ERRCOUNT;
			F_uart2_CommErr = CF_ENABLE;
			Fan.Indoor.f_Error = CF_ENABLE;
//			WiFi.Enum_Status = ENUM_TWIFISTATUS_NULL;
        }	
    
        Uart2.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
//        Uart2.u8_TxCnt = 0;								        //通信超时强制发送状态复位
        
    }
    else
    {
        F_uart2_TimeOut = CF_DISABLE;
        F_uart2_CommErr = CF_DISABLE;
        Uart2.u16_ErrCount = 0;
    }	
}
#endif

#if defined		UART3_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart3(void) 
Description         :初始化串口3
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart3_Config(void)
{
	GPIO_InitStruType y;
    UART_InitStruType uart;
    memset(&y, 0, sizeof(y));
    memset(&uart, 0, sizeof(uart));

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_5;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_1, &y);               //PA26---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_4;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_0, &y);               //PA27---RxD

    uart.UART_StopBits = UART_StopBits_1;          //停止位个数:1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式:8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性:正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式:8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性:正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择:Pclk
    UART_Init(UART3, &uart);

    UART_TBIMConfig(UART3, UART_TRBIM_Byte);
    UART_RBIMConfig(UART3, UART_TRBIM_Byte);
    UART_ITConfig(UART3, UART_IT_RB, ENUM_ENABLE);
    NVIC_Init(NVIC_UART3_IRQn, NVIC_Priority_1, ENUM_ENABLE);
    UART3_TxEnable();                               //UART3发送使能
    UART3_RxEnable();								//UART3接收使能 
   
}
/****************************************************************************************************
Function Name       :void	App_Uart3_Write_Frame(void)
Description         :根据功能应用发送信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_Uart3_Write_Frame(void)
{
    U8 i;
	S16 TempValue;
	U32 NumValue;

//    U8 checksum;

//    U8_Uart3_AppTxBuf[UART3_TX_HEAD_FIRST]   = C_UART3_TX_HEAD_FIRST;	//头码1
//    U8_Uart3_AppTxBuf[UART3_TX_HEAD_SECOND]  = C_UART3_TX_HEAD_SECOND;  //头码2		

//--------------------------------------------------------------------------------------------------//	
	
	U8_Uart3_AppTxBuf[0]  = '/';	
	U8_Uart3_AppTxBuf[1]  = '*';	
	
//--------------------------------------------------------------------------------------------------// 
	//1
	TempValue = T1.s16_ValueMul10;
	if (TempValue >= 0)
	{
		U8_Uart3_AppTxBuf[2]  = '+';                                      //发送字节数据
		
	}
	else
	{
		U8_Uart3_AppTxBuf[2]  = '-'; 
		TempValue = 0 - TempValue;
	}
	U8_Uart3_AppTxBuf[3]  = 0x30 + TempValue/1000;                        //百                
	U8_Uart3_AppTxBuf[4]  = 0x30 + TempValue%1000/100;                    //十                  
	U8_Uart3_AppTxBuf[5]  = 0x30 + TempValue%100/10;                      //个                     
	U8_Uart3_AppTxBuf[6]  = '.';                                          //小数点
	U8_Uart3_AppTxBuf[7]  = 0x30 + TempValue%10;                      	  //0.1        
	
	U8_Uart3_AppTxBuf[8]  = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//2
	TempValue = T2.s16_ValueMul10;
	if (TempValue >= 0)
	{
		U8_Uart3_AppTxBuf[9]  = '+';                                      //发送字节数据
		
	}
	else
	{
		U8_Uart3_AppTxBuf[9]  = '-'; 
		TempValue = 0 - TempValue;
	}
	U8_Uart3_AppTxBuf[10]  = 0x30 + TempValue/1000;                        //百                
	U8_Uart3_AppTxBuf[11]  = 0x30 + TempValue%1000/100;                    //十                  
	U8_Uart3_AppTxBuf[12]  = 0x30 + TempValue%100/10;                      //个                     
	U8_Uart3_AppTxBuf[13]  = '.';                                          //小数点
	U8_Uart3_AppTxBuf[14]  = 0x30 + TempValue%10;                      	  //0.1 	
	
	U8_Uart3_AppTxBuf[15] = ',';
	
//--------------------------------------------------------------------------------------------------//		
	//3
	TempValue = T3.s16_ValueMul10;
	if (TempValue >= 0)
	{
		U8_Uart3_AppTxBuf[16]  = '+';                                      //发送字节数据
		
	}
	else
	{
		U8_Uart3_AppTxBuf[16]  = '-'; 
		TempValue = 0 - TempValue;
	}
	U8_Uart3_AppTxBuf[17]  = 0x30 + TempValue/1000;                        //百                
	U8_Uart3_AppTxBuf[18]  = 0x30 + TempValue%1000/100;                    //十                  
	U8_Uart3_AppTxBuf[19]  = 0x30 + TempValue%100/10;                      //个                     
	U8_Uart3_AppTxBuf[20]  = '.';                                          //小数点
	U8_Uart3_AppTxBuf[21]  = 0x30 + TempValue%10;                      	  //0.1 	
	
	U8_Uart3_AppTxBuf[22] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//4
	TempValue = T4.s16_ValueMul10;
	if (TempValue >= 0)
	{
		U8_Uart3_AppTxBuf[23]  = '+';                                      //发送字节数据
		
	}
	else
	{
		U8_Uart3_AppTxBuf[23]  = '-'; 
		TempValue = 0 - TempValue;
	}
	U8_Uart3_AppTxBuf[24]  = 0x30 + TempValue/1000;                        //百                
	U8_Uart3_AppTxBuf[25]  = 0x30 + TempValue%1000/100;                    //十                  
	U8_Uart3_AppTxBuf[26]  = 0x30 + TempValue%100/10;                      //个                     
	U8_Uart3_AppTxBuf[27]  = '.';                                          //小数点
	U8_Uart3_AppTxBuf[28]  = 0x30 + TempValue%10;                      	  //0.1 	
	
	U8_Uart3_AppTxBuf[29] = ',';
	
//--------------------------------------------------------------------------------------------------//		
	//5
	TempValue = Tp.s16_ValueMul10;
	if (TempValue >= 0)
	{
		U8_Uart3_AppTxBuf[30]  = '+';                                      //发送字节数据
		
	}
	else
	{
		U8_Uart3_AppTxBuf[30]  = '-'; 
		TempValue = 0 - TempValue;
	}
	U8_Uart3_AppTxBuf[31]  = 0x30 + TempValue/1000;                        //百                
	U8_Uart3_AppTxBuf[32]  = 0x30 + TempValue%1000/100;                    //十                  
	U8_Uart3_AppTxBuf[33]  = 0x30 + TempValue%100/10;                      //个                     
	U8_Uart3_AppTxBuf[34]  = '.';                                          //小数点
	U8_Uart3_AppTxBuf[35]  = 0x30 + TempValue%10;                      	  //0.1 	
	
	U8_Uart3_AppTxBuf[36] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//6
	U8_Uart3_AppTxBuf[37] = 0x30 + Comp.u8_TargetFreq/10;
	U8_Uart3_AppTxBuf[38] = 0x30 + Comp.u8_TargetFreq%10;
	
	U8_Uart3_AppTxBuf[39] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//7
	U8_Uart3_AppTxBuf[40] = 0x30 + Fan.Indoor.u16_TargetRPM/1000;
	U8_Uart3_AppTxBuf[41] = 0x30 + Fan.Indoor.u16_TargetRPM%1000/100;
	U8_Uart3_AppTxBuf[42] = 0x30 + Fan.Indoor.u16_TargetRPM%100/10;
	U8_Uart3_AppTxBuf[43] = 0x30 + Fan.Indoor.u16_TargetRPM%10;
	
	U8_Uart3_AppTxBuf[44] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//8  步进电机角度
	NumValue = StepMotor.var.u16_agcurrent;
	NumValue *= 5625;//56.25;
	NumValue >>= 6;
	NumValue /= 100;
	U8_Uart3_AppTxBuf[45] = 0x30 + NumValue/1000;
	U8_Uart3_AppTxBuf[46] = 0x30 + NumValue%1000/100;
	U8_Uart3_AppTxBuf[47] = 0x30 + NumValue%100/10;	
	U8_Uart3_AppTxBuf[48] = '.';
	U8_Uart3_AppTxBuf[49] = 0x30 + NumValue%10;
	U8_Uart3_AppTxBuf[50] = ',';	

//--------------------------------------------------------------------------------------------------//	
	//9  低功耗
	U8_Uart3_AppTxBuf[51] = 0x30 + PowEnPTC.f_DrvOn;
	U8_Uart3_AppTxBuf[52] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//10
	U8_Uart3_AppTxBuf[53] = 0x30 + PowEn12V.f_DrvOn;
	U8_Uart3_AppTxBuf[54] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//11
	U8_Uart3_AppTxBuf[55] = 0x30 + PowEnPTCB.f_DrvOn;//EAHeater.f_DrvOn;
	U8_Uart3_AppTxBuf[56] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//12
	U8_Uart3_AppTxBuf[57] = 0x30 + FourWay.f_DrvOn;
	U8_Uart3_AppTxBuf[58] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//13
	U8_Uart3_AppTxBuf[59] = 0x30 + WiFi.f_DrvOn;
	U8_Uart3_AppTxBuf[60] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//14
	U8_Uart3_AppTxBuf[61] = 0x30 + UVC.f_DrvOn;
	U8_Uart3_AppTxBuf[62] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//15
	U8_Uart3_AppTxBuf[63] = 0x30 + WPMotor.f_DrvOn;
	U8_Uart3_AppTxBuf[64] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//16
	U8_Uart3_AppTxBuf[65] = 0x30 + WaterBox.f_Full;
	U8_Uart3_AppTxBuf[66] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//17
	U8_Uart3_AppTxBuf[67] = 0x30 + WaterBox.f_WatLow;
	U8_Uart3_AppTxBuf[68] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//18
	switch (Tempr.T1TSDeltaZone)
	{
		case	ENUM_TEMPDELTAZONE_INIT:  U8_Uart3_AppTxBuf[69] = 'X'; break;      //初始值-不明确区间
		case	ENUM_TEMPDELTAZONE_A:	  U8_Uart3_AppTxBuf[69] = 'A'; break;
		case	ENUM_TEMPDELTAZONE_B:	  U8_Uart3_AppTxBuf[69] = 'B'; break;
		case	ENUM_TEMPDELTAZONE_C:     U8_Uart3_AppTxBuf[69] = 'C'; break;
		case	ENUM_TEMPDELTAZONE_D:     U8_Uart3_AppTxBuf[69] = 'D'; break;
		case	ENUM_TEMPDELTAZONE_E:     U8_Uart3_AppTxBuf[69] = 'E'; break;
		case	ENUM_TEMPDELTAZONE_F:     U8_Uart3_AppTxBuf[69] = 'F'; break;
		case	ENUM_TEMPDELTAZONE_G:     U8_Uart3_AppTxBuf[69] = 'G'; break;
		case	ENUM_TEMPDELTAZONE_H:     U8_Uart3_AppTxBuf[69] = 'H'; break;
		case	ENUM_TEMPDELTAZONE_I:     U8_Uart3_AppTxBuf[69] = 'I'; break;
		case	ENUM_TEMPDELTAZONE_J:     U8_Uart3_AppTxBuf[69] = 'J'; break;
		case	ENUM_TEMPDELTAZONE_K:     U8_Uart3_AppTxBuf[69] = 'K'; break;
		
		default: break;
	}

	U8_Uart3_AppTxBuf[70] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//19
	if (SystemMode.f_ConTemp) 	U8_Uart3_AppTxBuf[71] = 'Y';
	else						U8_Uart3_AppTxBuf[71] = 'N';	
	U8_Uart3_AppTxBuf[72] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//20
	if (SystemMode.f_RoughCon) 	U8_Uart3_AppTxBuf[73] = 'Y';
	else						U8_Uart3_AppTxBuf[73] = 'N';	
	U8_Uart3_AppTxBuf[74] = ',';
	
//--------------------------------------------------------------------------------------------------//	
	//21
	if (Comp.u8_RealHZ < 99)
	{
		U8_Uart3_AppTxBuf[75] = 0x30 + Comp.u8_RealHZ/10;
		U8_Uart3_AppTxBuf[76] = 0x30 + Comp.u8_RealHZ%10;	
	}
	else
	{
		U8_Uart3_AppTxBuf[75] = '9';
		U8_Uart3_AppTxBuf[76] = '9';
	}
	U8_Uart3_AppTxBuf[77] = ',';
	
//--------------------------------------------------------------------------------------------------//
	//22
	U8_Uart3_AppTxBuf[78] = 0x30 + Fan.Indoor.u16_RealRPM/1000;
	U8_Uart3_AppTxBuf[79] = 0x30 + Fan.Indoor.u16_RealRPM%1000/100;
	U8_Uart3_AppTxBuf[80] = 0x30 + Fan.Indoor.u16_RealRPM%100/10;
	U8_Uart3_AppTxBuf[81] = 0x30 + Fan.Indoor.u16_RealRPM%10;
	U8_Uart3_AppTxBuf[82] = ',';	
	
	
//--------------------------------------------------------------------------------------------------//
	//23
	U8_Uart3_AppTxBuf[83] = 0x30 + Fan.Outdoor.u16_RealRPM/1000;
	U8_Uart3_AppTxBuf[84] = 0x30 + Fan.Outdoor.u16_RealRPM%1000/100;
	U8_Uart3_AppTxBuf[85] = 0x30 + Fan.Outdoor.u16_RealRPM%100/10;
	U8_Uart3_AppTxBuf[86] = 0x30 + Fan.Outdoor.u16_RealRPM%10;
	U8_Uart3_AppTxBuf[87] = ',';

//--------------------------------------------------------------------------------------------------//
	//24
	NumValue = System.u16_DCVoltValue;
	U8_Uart3_AppTxBuf[88] = 0x30 + NumValue/100;
	U8_Uart3_AppTxBuf[89] = 0x30 + NumValue%100/10;
	U8_Uart3_AppTxBuf[90] = 0x30 + NumValue%10;
	U8_Uart3_AppTxBuf[91] = ',';

//--------------------------------------------------------------------------------------------------//
	//25
	NumValue = System.u8_OutDoorCurrentMul8;
	NumValue *= 10;
	NumValue >>= 3;
	U8_Uart3_AppTxBuf[92] = 0x30 + NumValue/100;
	U8_Uart3_AppTxBuf[93] = 0x30 + NumValue%100/10;
	U8_Uart3_AppTxBuf[94] = '.';
	U8_Uart3_AppTxBuf[95] = 0x30 + NumValue%10;
	U8_Uart3_AppTxBuf[96] = ',';

//--------------------------------------------------------------------------------------------------//
	//26
	if (System.Mode == ENUM_SYSMODE_HUM)			NumValue = Tempr.u8_HumiCSet;
	else											NumValue = Tempr.u8_TempCSet;

	U8_Uart3_AppTxBuf[97] = 0x30 + NumValue/100;
	U8_Uart3_AppTxBuf[98] = 0x30 + NumValue%100/10;
	U8_Uart3_AppTxBuf[99] = 0x30 + NumValue%10;
	U8_Uart3_AppTxBuf[100] = ',';

	//-------------------
	//27  lcx add db
	U8_Uart3_AppTxBuf[101] = 0x30 + Remember.u8_DB_TempCSet/100;
	U8_Uart3_AppTxBuf[102] = 0x30 + Remember.u8_DB_TempCSet%100/10;
	U8_Uart3_AppTxBuf[103] = 0x30 + Remember.u8_DB_TempCSet%10;
	
	U8_Uart3_AppTxBuf[104] = ',';
	
	U8_Uart3_AppTxBuf[105]	= '*';										  //发送字节数据
	U8_Uart3_AppTxBuf[106] = '/';										  //发送字节数据

//	U8_Uart3_AppTxBuf[105]	= '=';										  //发送字节数据
//	U8_Uart3_AppTxBuf[106] = '=';										  //发送字节数据

	
	//----------------

//--------------------------------------------------------------------------------------------------//

//    U8_Uart3_AppTxBuf[101]  = '*';                                        //发送字节数据
//    U8_Uart3_AppTxBuf[102] = '/';                                         //发送字节数据
    
//    checksum = 0;
//    
//    for (i=0; i<UART3_TX_CHKSUM; i++)
//    {
//        checksum += U8_Uart3_AppTxBuf[i];
//    }
//    
//    checksum ^= 0xFF;
//    checksum += 1;
//    
//    U8_Uart3_AppTxBuf[UART3_TX_CHKSUM] = checksum;                      //校验

    for (i=0; i<UART3_TX_LEN; i++)                                      //(根据功能需要发送多少个字节,可能是常数可能是变量) =>  Uart3.u8_TxNum = UART_TX_LEN
    {
        U8_Uart3_TxBuf[i] = U8_Uart3_AppTxBuf[i];	
        U8_Uart3_AppTxBuf[i] = 0;
    }		
    
        
    if (Uart3.Enum_TxState == ENUM_TXSTATE_IDLE)	
    {
        F_uart3_TxReady = CF_ENABLE;	
    }
}
/****************************************************************************************************
Function Name       :void	App_Uart3_Read_Frame(void)
Description         :根据功能应用接收信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Uart3_Read_Frame(void)
{
    U8  i;  
    U8  chksum;
    volatile U8  temp;
             
    if (F_uart3_Receiving == CF_ENABLE)
    {
        if (Uart3.u8_RxTimerOut < C_UART_RXTIMEOUTCOUNT)
        {
            Uart3.u8_RxTimerOut++;
        }
        else
        {
            Uart3.u8_RxTimerOut = 0;
            F_uart3_Receiving = CF_DISABLE;
            F_uart3_RxComplete = CF_ENABLE;
        }
    }


    if (F_uart3_RxComplete == CF_ENABLE)
    {        
        chksum = 0;
        for (i=0; i<UART3_RX_CHKSUM; i++)
        {
            chksum += U8_Uart3_DrvRxBuf[i];
        }
        chksum ^= 0xFF;
        chksum += 1;
              
        if ((U8_Uart3_DrvRxBuf[UART3_RX_HEAD_FIRST] == C_UART3_RX_HEAD_FIRST) && (U8_Uart3_DrvRxBuf[UART3_RX_HEAD_SECOND] == C_UART3_RX_HEAD_SECOND))   //头码正确
        {
            if (U8_Uart3_DrvRxBuf[UART3_RX_CHKSUM] == chksum)              //检验通过，指令处理
            {
                           
                for (i=0; i<UART3_RX_LEN; i++)
                {
                    U8_Uart3_RxBuf[i] = U8_Uart3_DrvRxBuf[i];
                }
                

                //数据接收分析
                temp = U8_Uart3_RxBuf[2];                //接收数据
                temp = U8_Uart3_RxBuf[3];                //接收数据
                temp = U8_Uart3_RxBuf[4];                //接收数据
                temp = U8_Uart3_RxBuf[5];                //接收数据
                temp = U8_Uart3_RxBuf[6];                //接收数据


                
                Uart3.u16_AbnormalCount = 0;                 //收到完整数据，清零通讯超时计数
                F_uart3_TimeOut = CF_DISABLE;                //通讯正常
				F_uart3_CommErr = CF_DISABLE;
				Uart3.u16_ErrCount = 0; 				
                          
            }
            
            /***一定要在处理完接收数据后才清零，因为清零后串口会开始接收数据，会覆盖旧的数据***/
            F_uart3_RxComplete = CF_DISABLE;
            Uart3.u8_RxCnt = 0;
        }
    }


    if (Uart3.u16_AbnormalCount >= 25)							//连续2.5s接收异常强制发送复位
    {
        Uart3.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
//        Uart3.u8_TxCnt = 0;								        //通信超时强制发送状态复位
    }

    if (++Uart3.u16_AbnormalCount >= C_UART_ABNORMALCOUNT)       //通信超时
    {
        Uart3.u16_AbnormalCount = C_UART_ABNORMALCOUNT;
        F_uart3_TimeOut = CF_ENABLE;

        if (++Uart3.u16_ErrCount >= C_UART_ERRCOUNT)
        {
            Uart3.u16_ErrCount = C_UART_ERRCOUNT;
			F_uart3_CommErr = CF_ENABLE;
        }	
    
        Uart3.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
//        Uart3.u8_TxCnt = 0;								        //通信超时强制发送状态复位
        
    }
    else
    {
        F_uart3_TimeOut = CF_DISABLE;
        F_uart3_CommErr = CF_DISABLE;
        Uart3.u16_ErrCount = 0;
    }	
}
#endif

#if defined		UART4_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart4(void) 
Description         :初始化串口4
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart4_Config(void)
{
	GPIO_InitStruType y;
    UART_InitStruType uart;
    memset(&y, 0, sizeof(y));
    memset(&uart, 0, sizeof(uart));

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_7;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_10, &y);               //PB10---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_7;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOB, GPIO_Pin_9, &y);               //PB9---RxD

    uart.UART_StopBits = UART_StopBits_1;          //停止位个数:1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式:8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性:正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式:8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性:正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择:Pclk
    UART_Init(UART4, &uart);

    UART_TBIMConfig(UART4, UART_TRBIM_Byte);
    UART_RBIMConfig(UART4, UART_TRBIM_Byte);
    UART_ITConfig(UART4, UART_IT_RB, ENUM_ENABLE);
    NVIC_Init(NVIC_UART4_IRQn, NVIC_Priority_1, ENUM_ENABLE);
    UART4_TxEnable();                               //UART4发送使能
    UART4_RxEnable();								//UART4接收使能 
   
}
/****************************************************************************************************
Function Name       :void	App_Uart4_Write_Frame(void)
Description         :根据功能应用发送信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_Uart4_Write_Frame(void)
{}
//{
//    U8 i;
//
////    U8 checksum;
//
//    U8_Uart4_AppTxBuf[UART4_TX_HEAD_FIRST]   = C_UART4_TX_HEAD_FIRST;	//头码1
//    U8_Uart4_AppTxBuf[UART4_TX_HEAD_SECOND]  = C_UART4_TX_HEAD_SECOND;  //头码2		
//
//    U8_Uart4_AppTxBuf[2]  = C_COMMDISP_TX_BYTE3;    	//数据长度      //发送字节数据
//    U8_Uart4_AppTxBuf[3]  = CommDisp.Tx.Byte4.Byte;                     //发送字节数据
//    U8_Uart4_AppTxBuf[4]  = CommDisp.Tx.Byte5.Byte;                     //发送字节数据
//    U8_Uart4_AppTxBuf[5]  = CommDisp.Tx.Byte6.Byte;                     //发送字节数据
//    U8_Uart4_AppTxBuf[6]  = CommDisp.Tx.Byte7.Byte;                     //发送字节数据
//    U8_Uart4_AppTxBuf[7]  = CommDisp.Tx.Byte8.Byte;                     //发送字节数据
//    U8_Uart4_AppTxBuf[8]  = CommDisp.Tx.Byte9.Byte;                     //发送字节数据
//    U8_Uart4_AppTxBuf[9]  = CommDisp.Tx.Byte10.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[10] = CommDisp.Tx.Byte11.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[11] = CommDisp.Tx.Byte12.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[12] = CommDisp.Tx.Byte13.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[13] = CommDisp.Tx.Byte14.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[14] = CommDisp.Tx.Byte15.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[15] = CommDisp.Tx.Byte16.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[16] = CommDisp.Tx.Byte17.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[17] = CommDisp.Tx.Byte18.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[18] = CommDisp.Tx.Byte19.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[19] = CommDisp.Tx.Byte20.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[20] = CommDisp.Tx.Byte21.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[21] = CommDisp.Tx.Byte22.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[22] = CommDisp.Tx.Byte23.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[23] = CommDisp.Tx.Byte24.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[24] = CommDisp.Tx.Byte25.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[25] = CommDisp.Tx.Byte26.Byte;                    //发送字节数据
//    U8_Uart4_AppTxBuf[26] = CommDisp.Tx.Byte27.Byte;                    //发送字节数据
//
//   
//    U8_Uart4_AppTxBuf[UART4_TX_CHKSUM] = CommDisp_Check8(U8_Uart4_AppTxBuf, (UART4_TX_LEN-1));   //校验
//    
////    checksum = 0;
////    
////    for (i=0; i<UART4_TX_CHKSUM; i++)
////    {
////        checksum += U8_Uart4_AppTxBuf[i];
////    }
////    
////    checksum ^= 0xFF;
////    checksum += 1;
////    
////    U8_Uart4_AppTxBuf[UART4_TX_CHKSUM] = checksum;                      //校验
//
//    for (i=0; i<UART4_TX_LEN; i++)                                      //(根据功能需要发送多少个字节,可能是常数可能是变量) =>  Uart4.u8_TxNum = UART_TX_LEN
//    {
//        U8_Uart4_TxBuf[i] = U8_Uart4_AppTxBuf[i];	
//        U8_Uart4_AppTxBuf[i] = 0;
//    }		
//    
//        
//    if (Uart4.Enum_TxState == ENUM_TXSTATE_IDLE)	
//    {
//        F_uart4_TxReady = CF_ENABLE;	
//    }
//}
/****************************************************************************************************
Function Name       :void	App_Uart4_Read_Frame(void)
Description         :根据功能应用接收信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Uart4_Read_Frame(void)
{

}
//{
//    U8  i;  
//    U8  chksum;
//    volatile U8  temp;
//             
//    if (F_uart4_Receiving == CF_ENABLE)
//    {
//        if (Uart4.u8_RxTimerOut < C_UART_RXTIMEOUTCOUNT)
//        {
//            Uart4.u8_RxTimerOut++;
//        }
//        else
//        {
//            Uart4.u8_RxTimerOut = 0;
//            F_uart4_Receiving = CF_DISABLE;
//            F_uart4_RxComplete = CF_ENABLE;
//        }
//    }
//
//
//    if (F_uart4_RxComplete == CF_ENABLE)
//    {        
////        chksum = 0;
////        for (i=0; i<UART4_RX_CHKSUM; i++)
////        {
////            chksum += U8_Uart4_DrvRxBuf[i];
////        }
////        chksum ^= 0xFF;
////        chksum += 1;
//		
//		chksum = CommDisp_Check8(U8_Uart4_DrvRxBuf, (UART4_RX_LEN-1));
//              
//        if ((U8_Uart4_DrvRxBuf[UART4_RX_HEAD_FIRST] == C_UART4_RX_HEAD_FIRST) && (U8_Uart4_DrvRxBuf[UART4_RX_HEAD_SECOND] == C_UART4_RX_HEAD_SECOND))   //头码正确
//        {
//            if (U8_Uart4_DrvRxBuf[UART4_RX_CHKSUM] == chksum)              //检验通过，指令处理
//            {
//                           
//                for (i=0; i<UART4_RX_LEN; i++)
//                {
//                    U8_Uart4_RxBuf[i] = U8_Uart4_DrvRxBuf[i];
//                }
//                
//                //数据接收分析
//                if (U8_Uart4_RxBuf[2] == C_COMMDISP_RX_BYTE3)             //接收字节长度一致
//				{
//					CommDisp.Rx.Byte4.Byte  = U8_Uart4_RxBuf[3];          //接收数据
//					CommDisp.Rx.Byte5.Byte  = U8_Uart4_RxBuf[4];          //接收数据
//					CommDisp.Rx.Byte6.Byte  = U8_Uart4_RxBuf[5];          //接收数据
//					CommDisp.Rx.Byte7.Byte  = U8_Uart4_RxBuf[6];          //接收数据
//					CommDisp.Rx.Byte8.Byte  = U8_Uart4_RxBuf[7];          //接收数据
//					CommDisp.Rx.Byte9.Byte  = U8_Uart4_RxBuf[8];          //接收数据
//					CommDisp.Rx.Byte10.Byte = U8_Uart4_RxBuf[9];          //接收数据
//					CommDisp.Rx.Byte11.Byte = U8_Uart4_RxBuf[10];         //接收数据					
//					CommDisp.Rx.Byte12.Byte = U8_Uart4_RxBuf[11];		  //接收数据
//					CommDisp.Rx.Byte13.Byte = U8_Uart4_RxBuf[12];		  //接收数据
//					CommDisp.Rx.Byte14.Byte = U8_Uart4_RxBuf[13];		  //接收数据
//					CommDisp.Rx.Byte15.Byte = U8_Uart4_RxBuf[14];		  //接收数据
//					
//					
//				}
//
//
//                
//                Uart4.u16_AbnormalCount = 0;                  //收到完整数据，清零通讯超时计数
//                F_uart4_TimeOut = CF_DISABLE;                //通讯正常
//				F_uart4_CommErr = CF_DISABLE;
//				Uart4.u16_ErrCount = 0; 				
//                          
//            }
//            
//            /***一定要在处理完接收数据后才清零，因为清零后串口会开始接收数据，会覆盖旧的数据***/
//            F_uart4_RxComplete = CF_DISABLE;
//            Uart4.u8_RxCnt = 0;
//        }
//    }
//
//
//    if (Uart4.u16_AbnormalCount >= 25)							//连续2.5s接收异常强制发送复位
//    {
//        Uart4.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
//        Uart4.u8_TxCnt = 0;								        //通信超时强制发送状态复位
//    }
//
//    if (++Uart4.u16_AbnormalCount >= C_UART_ABNORMALCOUNT)       //通信超时
//    {
//        Uart4.u16_AbnormalCount = C_UART_ABNORMALCOUNT;
//        F_uart4_TimeOut = CF_ENABLE;
//
//        if (++Uart4.u16_ErrCount >= C_UART_ERRCOUNT)
//        {
//            Uart4.u16_ErrCount = C_UART_ERRCOUNT;
//			F_uart4_CommErr = CF_ENABLE;
//        }	
//    
//        Uart4.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
//        Uart4.u8_TxCnt = 0;								        //通信超时强制发送状态复位
//        
//    }
//    else
//    {
//        F_uart4_TimeOut = CF_DISABLE;
//        F_uart4_CommErr = CF_DISABLE;
//        Uart4.u16_ErrCount = 0;
//    }	
//}
#endif

#if defined		UART5_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart5(void) 
Description         :初始化串口5
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart5_Config(void)
{
	GPIO_InitStruType y;
    UART_InitStruType uart;
    memset(&y, 0, sizeof(y));
    memset(&uart, 0, sizeof(uart));

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_4;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOA, GPIO_Pin_1, &y);               //PA1---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_1;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOA, GPIO_Pin_2, &y);               //PA2---RxD

    uart.UART_StopBits = UART_StopBits_1;          //停止位个数:1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式:8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性:正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式:8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性:正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择:Pclk
    UART_Init(UART5, &uart);

    UART_TBIMConfig(UART5, UART_TRBIM_Byte);
    UART_RBIMConfig(UART5, UART_TRBIM_Byte);
    UART_ITConfig(UART5, UART_IT_RB, ENABLE);
    NVIC_Init(NVIC_UART5_IRQn, NVIC_Priority_1, ENABLE);
    UART5_TxEnable();                               //UART5发送使能
    UART5_RxEnable();								//UART5接收使能 
   
}
/****************************************************************************************************
Function Name       :void	App_Uart5_Write_Frame(void)
Description         :根据功能应用发送信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_Uart5_Write_Frame(void)
{
    U8 i;

    U8 checksum;

    U8_Uart5_AppTxBuf[UART5_TX_HEAD_FIRST]   = C_UART5_TX_HEAD_FIRST;	//头码1
    U8_Uart5_AppTxBuf[UART5_TX_HEAD_SECOND]  = C_UART5_TX_HEAD_SECOND;  //头码2		

    U8_Uart5_AppTxBuf[2]  = 0;                                          //发送字节数据
    U8_Uart5_AppTxBuf[3]  = 0;                                          //发送字节数据
    U8_Uart5_AppTxBuf[4]  = 0;                                          //发送字节数据
    U8_Uart5_AppTxBuf[5]  = 0;                                          //发送字节数据
    U8_Uart5_AppTxBuf[6]  = 0;                                          //发送字节数据
    U8_Uart5_AppTxBuf[7]  = 0;                                          //发送字节数据
    U8_Uart5_AppTxBuf[8]  = 0;                                          //发送字节数据
    U8_Uart5_AppTxBuf[9]  = 0;                                          //发送字节数据
    U8_Uart5_AppTxBuf[10] = 0;                                          //发送字节数据
    
    checksum = 0;
    
    for (i=0; i<UART5_TX_CHKSUM; i++)
    {
        checksum += U8_Uart5_AppTxBuf[i];
    }
    
    checksum ^= 0xFF;
    checksum += 1;
    
    U8_Uart5_AppTxBuf[UART5_TX_CHKSUM] = checksum;                      //校验

    for (i=0; i<UART5_TX_LEN; i++)                                      //(根据功能需要发送多少个字节,可能是常数可能是变量) =>  Uart5.u8_TxNum = UART_TX_LEN
    {
        U8_Uart5_TxBuf[i] = U8_Uart5_AppTxBuf[i];	
        U8_Uart5_AppTxBuf[i] = 0;
    }		
    
        
    if (Uart5.Enum_TxState == ENUM_TXSTATE_IDLE)	
    {
        F_uart5_TxReady = CF_ENABLE;	
    }
}
/****************************************************************************************************
Function Name       :void	App_Uart5_Read_Frame(void)
Description         :根据功能应用接收信息帧
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Uart5_Read_Frame(void)
{
    U8  i;  
    U8  chksum;
    volatile U8  temp;
             
    if (F_uart5_Receiving == CF_ENABLE)
    {
        if (Uart5.u8_RxTimerOut < C_UART_RXTIMEOUTCOUNT)
        {
            Uart5.u8_RxTimerOut++;
        }
        else
        {
            Uart5.u8_RxTimerOut = 0;
            F_uart5_Receiving = CF_DISABLE;
            F_uart5_RxComplete = CF_ENABLE;
        }
    }


    if (F_uart5_RxComplete == CF_ENABLE)
    {        
        chksum = 0;
        for (i=0; i<UART5_RX_CHKSUM; i++)
        {
            chksum += U8_Uart5_DrvRxBuf[i];
        }
        chksum ^= 0xFF;
        chksum += 1;
              
        if ((U8_Uart5_DrvRxBuf[UART5_RX_HEAD_FIRST] == C_UART5_RX_HEAD_FIRST) && (U8_Uart5_DrvRxBuf[UART5_RX_HEAD_SECOND] == C_UART5_RX_HEAD_SECOND))   //头码正确
        {
            if (U8_Uart5_DrvRxBuf[UART5_RX_CHKSUM] == chksum)              //检验通过，指令处理
            {
                           
                for (i=0; i<UART5_RX_LEN; i++)
                {
                    U8_Uart5_RxBuf[i] = U8_Uart5_DrvRxBuf[i];
                }
                

                //数据接收分析
                temp = U8_Uart5_RxBuf[2];                //接收数据
                temp = U8_Uart5_RxBuf[3];                //接收数据
                temp = U8_Uart5_RxBuf[4];                //接收数据
                temp = U8_Uart5_RxBuf[5];                //接收数据
                temp = U8_Uart5_RxBuf[6];                //接收数据


                
                Uart5.u16_AbnormalCount = 0;                  //收到完整数据，清零通讯超时计数
                F_uart5_TimeOut = CF_DISABLE;                //通讯正常
				F_uart5_CommErr = CF_DISABLE;
				Uart5.u16_ErrCount = 0;                           
            }
            
            /***一定要在处理完接收数据后才清零，因为清零后串口会开始接收数据，会覆盖旧的数据***/
            F_uart5_RxComplete = CF_DISABLE;
            Uart5.u8_RxCnt = 0;
        }
    }


    if (Uart5.u16_AbnormalCount >= 25)						//连续2.5s接收异常强制发送复位
    {
        Uart5.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
        Uart5.u8_TxCnt = 0;								        //通信超时强制发送状态复位
    }

    if (++Uart5.u16_AbnormalCount >= C_UART_ABNORMALCOUNT)       //通信超时
    {
        Uart5.u16_AbnormalCount = C_UART_ABNORMALCOUNT;
        F_uart5_TimeOut = CF_ENABLE;

        if (++Uart5.u16_ErrCount >= C_UART_ERRCOUNT)
        {
            Uart5.u16_ErrCount = C_UART_ERRCOUNT;
			F_uart5_CommErr = CF_ENABLE;
        }	
    
        Uart5.Enum_TxState = ENUM_TXSTATE_OK;	                //通信超时强制发送状态复位
        Uart5.u8_TxCnt = 0;								        //通信超时强制发送状态复位
        
    }
    else
    {
        F_uart5_TimeOut = CF_DISABLE;
        F_uart5_CommErr = CF_DISABLE;
        Uart5.u16_ErrCount = 0;
    }	
}
#endif
