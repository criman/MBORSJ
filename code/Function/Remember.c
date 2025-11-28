/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Remember.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/08/30
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/

#include	"main.h"


STRUCT_REMEMBER    Remember;

/****************************************************************************************************
Function Name       :void    Init_Pin_WP_Enable(void)
Description         :EE读写允许引脚初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_Pin_WP_Enable(void)
{
	P_EEPwren_Off();		//默认不允许读写
	P_EEPwren_Output();		//配置输出模式
	P_EEPwren_Dispull();	//配置不上拉
}
/****************************************************************************************************
Function Name       :void    Remember_ReadEEFunc(void)
Description         :掉电记忆-读取EE数据(功能部分)
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_ReadEEFunc(void)
{
	U8     i, j;
	U8     ChkGood;
	U8     ChkSumL0, ChkSumH0;
	U16    ChkSum;
	
	ChkGood = 0;
	for (i=0; i<3; i++)	//读取最多3次
	{
		//功能信息
		Read_24C02(&EEP.u8_rdBuf[0],  0x00, 16);
		
		ChkSum = 0;
		
		for (j=0; j<14; j++)				//功能掉电记忆数据从地址0开始
		{
			ChkSum += EEP.u8_rdBuf[j];
		}		

		ChkSum ^= 0xFFFF;
		ChkSum += 1;
		
		ChkSumL0 = ChkSum & 0xFF;
		ChkSumH0 = ChkSum >> 8;
		
		
		//需要头码和校验码正确
		if ((EEP.u8_rdBuf[0] == C_REMEMBER_HEAD) && (ChkSumL0 == EEP.u8_rdBuf[14]) && (ChkSumH0 == EEP.u8_rdBuf[15])) 
		{
			//还需增加验证各字节是否全零(全零数据判定无效)
			if ((ChkSumL0 == C_REMEMBER_INVALIDCHKSUM_L) && (ChkSumH0 == C_REMEMBER_INVALIDCHKSUM_H)) 
			{
				ChkGood = 0;
			}
			else
			{
				ChkGood = 1;
				break;
			}
		}

	}

	/*
	if(Remember.u16_InitKey == 0x5A16 && Remember.f_AllDatInit == 1) //lcx add 20240516
	{
		ChkGood = 0;
		Remember.u16_InitKey = 0;
		Remember.f_AllDatInit = 0;
	}
	*/
	
	if (ChkGood == 0)	//读取值不正确按默认值并重新写EE
	{
		Remember_WriteEEFunc(0);
	}
	Remember.u8_DB_TempCSet = EEP.u8_rdBuf[4];  //lcx add db
	//功能模式相关参数
	System.Enum_Status = (ENUM_STATUS)EEP.u8_rdBuf[1];			//01.开关机 
	System.Mode = (ENUM_SYSMODE)EEP.u8_rdBuf[2];				//02.工作模式 
	Fan.Mode = (ENUM_FANMODE)EEP.u8_rdBuf[3];					//03.风速 
	Tempr.u8_TempCSet = EEP.u8_rdBuf[4];						//04.温度设定值 
	Tempr.u8_ColdCSet = EEP.u8_rdBuf[5];						//05.制冷温度设定值(℃) 
	Tempr.u8_HeatCSet = EEP.u8_rdBuf[6];						//06.制冷温度设定值(℃) 
	Tempr.u8_TempFSet = EEP.u8_rdBuf[7];						//07.温度设定值(℉) 
	Tempr.u8_ColdFSet = EEP.u8_rdBuf[8];						//08.制冷温度设定值(℉) 
	Tempr.u8_HeatFSet = EEP.u8_rdBuf[9];						//09.制冷温度设定值(℉) 
	
	Tempr.f_TempUnit = ((EEP.u8_rdBuf[10]&0x01)?1:0);  			//10.温度单位 0：℃	1：℉
	Fan.f_SweepLR = ((EEP.u8_rdBuf[10]&0x02)?1:0);  			//10.摆风状态是否设定打开
	Timer.f_Enable = ((EEP.u8_rdBuf[10]&0x04)?1:0);				//10.定时是否设定	
    SystemMode.f_Sleep = ((EEP.u8_rdBuf[10]&0x08)?1:0);         //10.睡眠是否设定
    UVC.f_FuncOn = ((EEP.u8_rdBuf[10]&0x10)?1:0);               //10.负离子是否设定
    WiFi.f_FuncOn = ((EEP.u8_rdBuf[10]&0x20)?1:0);              //10.wifi电源开启标志			
	
	Swing.u16_anglebak = EEP.u8_rdBuf[12]<<8;     				//11.12.摆叶角度
	Swing.u16_anglebak += EEP.u8_rdBuf[11];
	
	//备份摇头/UVC/wifi电源状态
	Fan.f_SweepLRChkBak = Fan.f_SweepLR;
	UVC.f_FuncOnBak = UVC.f_FuncOn;
	WiFi.f_FuncOnBak = WiFi.f_FuncOn;
	
	Timer.f_OffEn = Timer.f_Enable;								//定时标志连同定时关标志
	
	//保证导风角度在合理范围内
	if (Swing.u16_anglebak == 0)
	{
		Swing.u16_anglebak = C_STEPMOTOR_ANGLE_DEFAULT;
	}
	else if (Swing.u16_anglebak < C_STEPMOTOR_ANGLE_MIN)
	{
		Swing.u16_anglebak = C_STEPMOTOR_ANGLE_MIN;
	}
	else if (Swing.u16_anglebak > C_STEPMOTOR_ANGLE_MAX)
	{
		Swing.u16_anglebak = C_STEPMOTOR_ANGLE_MAX;
	}
}
/****************************************************************************************************
Function Name       :void    Remember_WriteEEFunc(void)
Description         :掉电记忆-写入EE数据(功能部分)
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_WriteEEFunc(U8 ParaType)
{
	U8     i, j;
	U8     ChkSumL0, ChkSumH0;
	U16    ChkSum;	
	
	//地址0-15存放功能信息
	EEP.u8_wrBuf[0] = C_REMEMBER_HEAD;	//头码
	
	if (ParaType == 0)		//0：默认值
	{
		//掉电记忆-读取EE参数-模式功能类别
		EEP.u8_wrBuf[1]  = C_REMEMBER_MODEFUNC_ONOFF;        			//01.开关机 默认关机
		EEP.u8_wrBuf[2]  = C_REMEMBER_MODEFUNC_WORKMODE;     			//02.工作模式 默认制冷模式
		EEP.u8_wrBuf[3]  = C_REMEMBER_MODEFUNC_SPEEDMODE;    			//03.风速 默认自动风
		EEP.u8_wrBuf[4]  = C_REMEMBER_MODEFUNC_TEMPCSET_DFT;  			//04.温度设定值 默认值  23
		EEP.u8_wrBuf[5]  = C_REMEMBER_MODEFUNC_COLDCSET_DFT; 			//05.制冷温度设定值(℃) - 23℃
		EEP.u8_wrBuf[6]  = C_REMEMBER_MODEFUNC_HEATCSET_DFT;			//06.制热温度设定值(℃) - 27℃
		EEP.u8_wrBuf[7]  = C_REMEMBER_MODEFUNC_TEMPFSET_DFT; 		    //07.温度设定值(℉) - 73℉
		EEP.u8_wrBuf[8]  = C_REMEMBER_MODEFUNC_COLDFSET_DFT; 		    //08.制冷温度设定值(℉) - 73℉
		EEP.u8_wrBuf[9]  = C_REMEMBER_MODEFUNC_HEATFSET_DFT;	        //09.制热温度设定值(℉) - 81℉
		
		EEP.u8_wrBuf[10] = 0;
		if (C_REMEMBER_MODEFUNC_TEMPUNIT)		EEP.u8_wrBuf[10] |= 0x01;	//10.温度单位-默认1：华氏度
		if (C_REMEMBER_MODEFUNC_SWEEP)			EEP.u8_wrBuf[10] |= 0x02;	//10.摆风状态-默认0：关闭
		if (C_REMEMBER_MODEFUNC_TIMER)			EEP.u8_wrBuf[10] |= 0x04;	//10.定时是否设定-默认无
		if (C_REMEMBER_MODEFUNC_SLEEP)			EEP.u8_wrBuf[10] |= 0x08;	//10.睡眠是否设定-默认无			
		if (C_REMEMBER_MODEFUNC_FLZ)			EEP.u8_wrBuf[10] |= 0x10;	//10.负离子是否设定-默认无
		if (C_REMEMBER_MODEFUNC_WIFIPWRONOFF)	EEP.u8_wrBuf[10] |= 0x20;	//10.wifi电源开启标志	
			
		EEP.u8_wrBuf[11] = C_STEPMOTOR_ANGLE_DEFAULT & 0xFF;
		EEP.u8_wrBuf[12] = C_STEPMOTOR_ANGLE_DEFAULT >> 8;

	}
	else	//非0:实际值
	{
		EEP.u8_wrBuf[1]  = System.Enum_Status;			
		EEP.u8_wrBuf[2]  = System.Mode;				
		EEP.u8_wrBuf[3]  = Fan.Mode;				
		EEP.u8_wrBuf[4]  = Tempr.u8_TempCSet;			
		EEP.u8_wrBuf[5]  = Tempr.u8_ColdCSet;
		EEP.u8_wrBuf[6]  = Tempr.u8_HeatCSet;		
		EEP.u8_wrBuf[7]  = Tempr.u8_TempFSet;		
		EEP.u8_wrBuf[8]  = Tempr.u8_ColdFSet;	
		EEP.u8_wrBuf[9]  = Tempr.u8_HeatFSet;		
		
		EEP.u8_wrBuf[10] = 0;
		if (Tempr.f_TempUnit)		EEP.u8_wrBuf[10] |= 0x01;
		if (Fan.f_SweepLR)			EEP.u8_wrBuf[10] |= 0x02;
		if (Timer.f_Enable)			EEP.u8_wrBuf[10] |= 0x04;
		if (SystemMode.f_Sleep)		EEP.u8_wrBuf[10] |= 0x08;
		if (UVC.f_FuncOn)			EEP.u8_wrBuf[10] |= 0x10;
		if (WiFi.f_FuncOn)			EEP.u8_wrBuf[10] |= 0x20;
		
		EEP.u8_wrBuf[11] = Swing.u16_anglebak & 0xFF;		
		EEP.u8_wrBuf[12] = Swing.u16_anglebak >> 8;		
		
	}
	//预留的也清零	
		
	EEP.u8_wrBuf[13] = 0;
	
	ChkSum = 0;
	for (i=0; i<14; i++)
	{
		ChkSum += EEP.u8_wrBuf[i];
	}
	ChkSum ^= 0xFFFF;
	ChkSum += 1;
	
	EEP.u8_wrBuf[14] = ChkSum & 0xFF;
	EEP.u8_wrBuf[15] = ChkSum >> 8;		

		
	i = 0;
	EEP.u7_Count = 0;
	EEP.Step = ENUM_STEP_IDLE;
	
	while (i < 3)	//最多三次失败重写
	{
		if (EEP.Step == ENUM_STEP_IDLE)
		{						
			Write_24C02(&EEP.u8_wrBuf[0],   0x00, 16);
		
			EEP.Step = ENUM_STEP_WR;
		}
		else if (EEP.Step == ENUM_STEP_WR)
		{
			if (EEP.f_1ms)
			{
				EEP.f_1ms = 0;
				if (++EEP.u7_Count >= 20)	//写EE 20ms后进行读取验证是否写对
				{
					EEP.u7_Count = 0;
					EEP.Step = ENUM_STEP_RD;
				}
			}
		}
		else if (EEP.Step == ENUM_STEP_RD)
		{
			
			Read_24C02(&EEP.u8_rdBuf[0],  0x00, 16);

			ChkSum = 0;
			
			for (j=0; j<14; j++)
			{
				ChkSum += EEP.u8_rdBuf[j];
			}
			
			ChkSum ^= 0xFFFF;
			ChkSum += 1;
			
			ChkSumL0 = ChkSum & 0xFF;
			ChkSumH0 = ChkSum >> 8;			
			
			
			if ((EEP.u8_rdBuf[0] == C_REMEMBER_HEAD) && (ChkSumL0 == EEP.u8_rdBuf[14]) && (ChkSumH0 == EEP.u8_rdBuf[15]))	//需头码和校验码正确
			{					
				for (j=1; j<16; j++)		//头码不纳入范围
				{
					if ((j!=14) && (j!=15))	//校验码不纳入范围
					{
						if (EEP.u8_rdBuf[j] != EEP.u8_wrBuf[j])		//出现数据不一样需重来一遍
						{
							EEP.Step = ENUM_STEP_IDLE;
							i += 1;
							break;
						}
					}
				}
				
				//正确跳出判断循环
				EEP.Step = ENUM_STEP_OK;
				break;					
			}
			else		//失败重来
			{
				EEP.Step = ENUM_STEP_IDLE;
				i += 1;
			}
		}
	}

	if (i >= 3)		//多次失败按默认值
	{
		for (j=1; j<16; j++)		//头码不纳入范围
		{
			if ((j!=14) && (j!=15))	//校验码不纳入范围
			{
				EEP.u8_rdBuf[j] = EEP.u8_wrBuf[j];	
			}
		}
		
		System.f_InEEpromErr = 1;	//报内机EEPROM故障
	}
}
/****************************************************************************************************
Function Name       :void    Remember_ReadEEPara(void)
Description         :掉电记忆-读取EE数据(参数部分)
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_ReadEEPara(void)
{
	U8     i, j;
	U8     ChkGood;
	U8     ChkSumL1, ChkSumH1;
	U16    ChkSum;
	
	ChkGood = 0;
	for (i=0; i<3; i++)	//读取最多3次
	{
		//参数信息
		Read_24C02(&EEP.u8_rdBuf[16],  0x10, 16);
		Read_24C02(&EEP.u8_rdBuf[32],  0x20, 16);		
		Read_24C02(&EEP.u8_rdBuf[48],  0x30, 16);
		Read_24C02(&EEP.u8_rdBuf[64],  0x40, 16);
		Read_24C02(&EEP.u8_rdBuf[80],  0x50, 16);	
		Read_24C02(&EEP.u8_rdBuf[96],  0x60, 16);
		Read_24C02(&EEP.u8_rdBuf[112], 0x70, 16);
		Read_24C02(&EEP.u8_rdBuf[128], 0x80, 16);
		Read_24C02(&EEP.u8_rdBuf[144], 0x90, 16);
		
		ChkSum = 0;
		
		for (j=16; j<158; j++)				//参数存放在从地址16开始
		{
			ChkSum += EEP.u8_rdBuf[j];
		}
		
		ChkSum ^= 0xFFFF;
		ChkSum += 1;
		
		ChkSumL1 = ChkSum & 0xFF;
		ChkSumH1 = ChkSum >> 8;
		
		//需要头码和校验码正确		
		if ((EEP.u8_rdBuf[16] == C_REMEMBER_HEAD) && (ChkSumL1 == EEP.u8_rdBuf[158]) && (ChkSumH1 == EEP.u8_rdBuf[159]))
		{
			//还需增加验证各字节是否全零(全零数据判定无效)
			if	(((ChkSumL1 == C_REMEMBER_INVALIDCHKSUM_L) && (ChkSumH1 == C_REMEMBER_INVALIDCHKSUM_H)) || ((EEP.u8_rdBuf[17] == 0) && (EEP.u8_rdBuf[87] == 0) && (EEP.u8_rdBuf[144] == 0)))
			{
				ChkGood = 0;
			}
			else
			{
				ChkGood = 1;				
			}
		}

	}

	Remember_WriteEEPara(ChkGood);	//0,读取值不正确按默认值并重新写EE; 1,正确时数据备份
	
}
/****************************************************************************************************
Function Name       :void    Remember_WritePara(void)
Description         :掉电记忆-写入EE数据(参数部分)
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_WriteEEPara(U8 ParaType)
{
	U8     i, j;
	U8     ChkSumL1, ChkSumH1;
	U16    ChkSum;	
	
	
	//地址16-159存放参数信息
	EEP.u8_wrBuf[16] = C_REMEMBER_HEAD;	//头码
	
	if (ParaType == 0)		//0：默认值
	{
		//1.室内风速							   	        (rpm/10)        13Byte
		EEP.u8_wrBuf[17] = C_REMEMBER_PARA01_00;        //125 			//测试-商检
		EEP.u8_wrBuf[18] = C_REMEMBER_PARA01_01;        //115			//测试-额定制冷
		EEP.u8_wrBuf[19] = C_REMEMBER_PARA01_02;        //80			//测试-最小制冷
		EEP.u8_wrBuf[20] = C_REMEMBER_PARA01_03;        //120			//测试-额定制热
		EEP.u8_wrBuf[21] = C_REMEMBER_PARA01_04;        //115			//常规-制冷-强力风
		EEP.u8_wrBuf[22] = C_REMEMBER_PARA01_05;        //105			//常规-制冷-高风
		EEP.u8_wrBuf[23] = C_REMEMBER_PARA01_06;        //90			//常规-制冷-中风
		EEP.u8_wrBuf[24] = C_REMEMBER_PARA01_07;        //80			//常规-制冷-低风
		EEP.u8_wrBuf[25] = C_REMEMBER_PARA01_08;        //70			//常规-制冷-微风
		EEP.u8_wrBuf[26] = C_REMEMBER_PARA01_09;        //115			//常规-制热-高风
		EEP.u8_wrBuf[27] = C_REMEMBER_PARA01_10;        //100			//常规-制热-中风
		EEP.u8_wrBuf[28] = C_REMEMBER_PARA01_11;        //90			//常规-制热-低风
		EEP.u8_wrBuf[29] = C_REMEMBER_PARA01_12;        //70			//常规-制热-微风

		//2.室外风速							   			(rpm/10)	    12Byte
		EEP.u8_wrBuf[30] = C_REMEMBER_PARA02_00;		//105	        //测试-额定制冷	
		EEP.u8_wrBuf[31] = C_REMEMBER_PARA02_01;		//80	        //测试-最小制冷	
		EEP.u8_wrBuf[32] = C_REMEMBER_PARA02_02;		//100	        //测试-额定制热	
		EEP.u8_wrBuf[33] = C_REMEMBER_PARA02_03;		//105	        //常规-制冷-强力风	
		EEP.u8_wrBuf[34] = C_REMEMBER_PARA02_04;		//105	        //常规-制冷-高风	
		EEP.u8_wrBuf[35] = C_REMEMBER_PARA02_05;		//105	        //常规-制冷-中风	
		EEP.u8_wrBuf[36] = C_REMEMBER_PARA02_06;		//105	        //常规-制冷-低风	
		EEP.u8_wrBuf[37] = C_REMEMBER_PARA02_07;		//70	        //常规-制冷-微风	
		EEP.u8_wrBuf[38] = C_REMEMBER_PARA02_08;		//100	        //常规-制热-高风	
		EEP.u8_wrBuf[39] = C_REMEMBER_PARA02_09;		//100	        //常规-制热-中风	
		EEP.u8_wrBuf[40] = C_REMEMBER_PARA02_10;		//100	        //常规-制热-低风	
		EEP.u8_wrBuf[41] = C_REMEMBER_PARA02_11;		//70	        //常规-制热-微风	
										   
		//3.压缩机运行档位					   			频率(Hz)	    32Byte
		EEP.u8_wrBuf[42] = C_REMEMBER_PARA03_00;		//0		   	    //制冷档位FC0	
		EEP.u8_wrBuf[43] = C_REMEMBER_PARA03_01;		//16	        //制冷档位FC1	
		EEP.u8_wrBuf[44] = C_REMEMBER_PARA03_02;		//20	        //制冷档位FC2	
		EEP.u8_wrBuf[45] = C_REMEMBER_PARA03_03;		//25	        //制冷档位FC3	
		EEP.u8_wrBuf[46] = C_REMEMBER_PARA03_04;		//30	        //制冷档位FC4	
		EEP.u8_wrBuf[47] = C_REMEMBER_PARA03_05;		//34	        //制冷档位FC5	
		EEP.u8_wrBuf[48] = C_REMEMBER_PARA03_06;		//36	        //制冷档位FC6	
		EEP.u8_wrBuf[49] = C_REMEMBER_PARA03_07;		//38	        //制冷档位FC7	
		EEP.u8_wrBuf[50] = C_REMEMBER_PARA03_08;		//42	        //制冷档位FC8	
		EEP.u8_wrBuf[51] = C_REMEMBER_PARA03_09;		//45	        //制冷档位FC9	
		EEP.u8_wrBuf[52] = C_REMEMBER_PARA03_10;		//47	        //制冷档位FC10	
		EEP.u8_wrBuf[53] = C_REMEMBER_PARA03_11;		//50	        //制冷档位FC11	
		EEP.u8_wrBuf[54] = C_REMEMBER_PARA03_12;		//50	        //制冷档位FC12	
		EEP.u8_wrBuf[55] = C_REMEMBER_PARA03_13;		//50	        //制冷档位FC13	
		EEP.u8_wrBuf[56] = C_REMEMBER_PARA03_14;		//50	        //制冷档位FC14	
		EEP.u8_wrBuf[57] = C_REMEMBER_PARA03_15;		//50	        //制冷档位FC15	
		EEP.u8_wrBuf[58] = C_REMEMBER_PARA03_16;		//0		        //制热档位FH0	
		EEP.u8_wrBuf[59] = C_REMEMBER_PARA03_17;		//16	        //制热档位FH1	
		EEP.u8_wrBuf[60] = C_REMEMBER_PARA03_18;		//20	        //制热档位FH2	
		EEP.u8_wrBuf[61] = C_REMEMBER_PARA03_19;		//25	        //制热档位FH3	
		EEP.u8_wrBuf[62] = C_REMEMBER_PARA03_20;		//30	        //制热档位FH4	
		EEP.u8_wrBuf[63] = C_REMEMBER_PARA03_21;		//34	        //制热档位FH5	
		EEP.u8_wrBuf[64] = C_REMEMBER_PARA03_22;		//36	        //制热档位FH6	
		EEP.u8_wrBuf[65] = C_REMEMBER_PARA03_23;		//38	        //制热档位FH7	
		EEP.u8_wrBuf[66] = C_REMEMBER_PARA03_24;		//42	        //制热档位FH8	
		EEP.u8_wrBuf[67] = C_REMEMBER_PARA03_25;		//45	        //制热档位FH9	
		EEP.u8_wrBuf[68] = C_REMEMBER_PARA03_26;		//47	        //制热档位FH10	
		EEP.u8_wrBuf[69] = C_REMEMBER_PARA03_27;		//50	        //制热档位FH11	
		EEP.u8_wrBuf[70] = C_REMEMBER_PARA03_28;		//50	        //制热档位FH12	
		EEP.u8_wrBuf[71] = C_REMEMBER_PARA03_29;		//50	        //制热档位FH13	
		EEP.u8_wrBuf[72] = C_REMEMBER_PARA03_30;		//50	        //制热档位FH14	
		EEP.u8_wrBuf[73] = C_REMEMBER_PARA03_31;		//50	        //制热档位FH15	
										   
		//4.制冷T4限频						   			频率档位	   		12Byte
		EEP.u8_wrBuf[74] = C_REMEMBER_PARA04_00;		//3		   		//T＜0℃		
		EEP.u8_wrBuf[75] = C_REMEMBER_PARA04_01;		//4		   		//0℃≤T＜10℃	
		EEP.u8_wrBuf[76] = C_REMEMBER_PARA04_02;		//6		   		//10℃≤T＜15℃	
		EEP.u8_wrBuf[77] = C_REMEMBER_PARA04_03;		//8		   		//15℃≤T＜20℃	
		EEP.u8_wrBuf[78] = C_REMEMBER_PARA04_04;		//9		   		//20℃≤T＜25℃	
		EEP.u8_wrBuf[79] = C_REMEMBER_PARA04_05;		//10		    //25℃≤T＜30℃	
		EEP.u8_wrBuf[80] = C_REMEMBER_PARA04_06;		//10		    //30℃≤T＜33℃	
		EEP.u8_wrBuf[81] = C_REMEMBER_PARA04_07;		//10		    //33℃≤T＜40℃	
		EEP.u8_wrBuf[82] = C_REMEMBER_PARA04_08;		//3		   		//40℃≤T＜45℃	
		EEP.u8_wrBuf[83] = C_REMEMBER_PARA04_09;		//3		   	 	//45℃≤T＜50℃	
		EEP.u8_wrBuf[84] = C_REMEMBER_PARA04_10;		//3		   		//50℃≤T＜55℃	
		EEP.u8_wrBuf[85] = C_REMEMBER_PARA04_11;		//3		   		//55℃≤T		
										   
		//5.制热T4限频						   			频率档位	   		14Byte
		EEP.u8_wrBuf[86] = C_REMEMBER_PARA05_00;        //10	        //T＜-10℃	    
		EEP.u8_wrBuf[87] = C_REMEMBER_PARA05_01;        //10	        //-10℃≤T＜-7℃	
		EEP.u8_wrBuf[88] = C_REMEMBER_PARA05_02;        //10	        //-7℃≤T＜-3℃	
		EEP.u8_wrBuf[89] = C_REMEMBER_PARA05_03;        //10	        //-3℃≤T＜-1℃	
		EEP.u8_wrBuf[90] = C_REMEMBER_PARA05_04;        //10	        //1℃≤T＜4℃	
		EEP.u8_wrBuf[91] = C_REMEMBER_PARA05_05;        //10	        //4℃≤T＜7℃	
		EEP.u8_wrBuf[92] = C_REMEMBER_PARA05_06;        //10	        //7℃≤T＜10℃	
		EEP.u8_wrBuf[93] = C_REMEMBER_PARA05_07;        //10	        //10℃≤T＜13℃	
		EEP.u8_wrBuf[94] = C_REMEMBER_PARA05_08;        //10	        //13℃≤T＜16℃	
		EEP.u8_wrBuf[95] = C_REMEMBER_PARA05_09;        //10	        //16℃≤T＜19℃	
		EEP.u8_wrBuf[96] = C_REMEMBER_PARA05_10;        //9	       	    //19℃≤T＜22℃	
		EEP.u8_wrBuf[97] = C_REMEMBER_PARA05_11;        //7	       	    //22℃≤T＜25℃	
		EEP.u8_wrBuf[98] = C_REMEMBER_PARA05_12;        //5	       	    //25℃≤T＜28℃	
		EEP.u8_wrBuf[99] = C_REMEMBER_PARA05_13;        //3	       	    //28℃≤T	    

		//6.制冷运行室内风速对压缩机频率的控制	   			最大档位	        5Byte
		EEP.u8_wrBuf[100] = C_REMEMBER_PARA06_00;	    //10	        //室内风机超高风时-E_
		EEP.u8_wrBuf[101] = C_REMEMBER_PARA06_01;       //10	        //室内风机高风时-E_	
		EEP.u8_wrBuf[102] = C_REMEMBER_PARA06_02;       //8	       	    //室内风机中风时-E_	
		EEP.u8_wrBuf[103] = C_REMEMBER_PARA06_03;       //8	            //室内风机低风时-E_	
		EEP.u8_wrBuf[104] = C_REMEMBER_PARA06_04;       //6	            //室内风机微风时-E_	

		//7.制热运行室内风速对压缩机频率的控制	   			最大档位	   		4Byte
		EEP.u8_wrBuf[105] = C_REMEMBER_PARA07_00;		//10	        //室内风机高风时-E_	
		EEP.u8_wrBuf[106] = C_REMEMBER_PARA07_01;		//8	       		//室内风机中风时-E_	
		EEP.u8_wrBuf[107] = C_REMEMBER_PARA07_02;		//8	       		//室内风机低风时-E_	
		EEP.u8_wrBuf[108] = C_REMEMBER_PARA07_03;		//6	       		//室内风机微风时-E_	

		//8.制热模式-管温矫正功能				  				℃		   		8Byte
		EEP.u8_wrBuf[109] = (U8)C_REMEMBER_PARA08_00;		//-2	        //室内风速中风时温度矫正	
		EEP.u8_wrBuf[110] = (U8)C_REMEMBER_PARA08_01;		//-3	        //室内风速低风时温度矫正	
		EEP.u8_wrBuf[111] = (U8)C_REMEMBER_PARA08_02;		//-4	        //室内风速微风时温度矫正	
		EEP.u8_wrBuf[112] = (U8)C_REMEMBER_PARA08_03;		//52	        //T2_HEAT0				
		EEP.u8_wrBuf[113] = (U8)C_REMEMBER_PARA08_04;		//58	        //T2_HEAT1				
		EEP.u8_wrBuf[114] = (U8)C_REMEMBER_PARA08_05;		//62	        //T2_HEAT2				
		EEP.u8_wrBuf[115] = (U8)C_REMEMBER_PARA08_06;		//64	        //T2_HEAT3				
		EEP.u8_wrBuf[116] = (U8)C_REMEMBER_PARA08_07;		//66	        //T2_HEAT4				

		//9.化霜功能							   				℃(含小数点) 	9Byte
		EEP.u8_wrBuf[117] = (U8)C_REMEMBER_PARA09_00;		//-10		   	//TDFI1		
		EEP.u8_wrBuf[118] = (U8)C_REMEMBER_PARA09_01;		//4		   		//DELTA_TDF1	
		EEP.u8_wrBuf[119] = (U8)C_REMEMBER_PARA09_02;		//-6		    //TDFI2		
		EEP.u8_wrBuf[120] = (U8)C_REMEMBER_PARA09_03;		//5		   		//DELTA_TDF2	
		EEP.u8_wrBuf[121] = (U8)C_REMEMBER_PARA09_04;		//-30		   	//TDFI3		
		EEP.u8_wrBuf[122] = (U8)C_REMEMBER_PARA09_05;		//-2		   	//TDFI4		
		EEP.u8_wrBuf[123] = (U8)C_REMEMBER_PARA09_06;		//30		   	//TDFE1		
		EEP.u8_wrBuf[124] = (U8)C_REMEMBER_PARA09_07;		//16		   	//TDFE2		

		//10.化霜时运行频率					   			档位		    1Byte
		EEP.u8_wrBuf[125] = C_REMEMBER_PARA10_00;		//10		    //化霜过程最大运行频率档位

		//11.压缩机保护-排气温度保护			   			℃		   		5Byte
		EEP.u8_wrBuf[126] = C_REMEMBER_PARA11_00;		//90		    //TP0
		EEP.u8_wrBuf[127] = C_REMEMBER_PARA11_01;		//95		    //TP1
		EEP.u8_wrBuf[128] = C_REMEMBER_PARA11_02;		//100		    //TP2
		EEP.u8_wrBuf[129] = C_REMEMBER_PARA11_03;		//105		    //TP3
		EEP.u8_wrBuf[130] = C_REMEMBER_PARA11_04;		//110		    //TP4

		//12.制冷室内换热器的防冻结	           				℃(含小数点) 	5Byte
		EEP.u8_wrBuf[131] = (U8)C_REMEMBER_PARA12_00;		//0		   		//T2_COLD0
		EEP.u8_wrBuf[132] = (U8)C_REMEMBER_PARA12_01;		//4		   		//T2_COLD1
		EEP.u8_wrBuf[133] = (U8)C_REMEMBER_PARA12_02;		//8		   		//T2_COLD2
		EEP.u8_wrBuf[134] = (U8)C_REMEMBER_PARA12_03;		//11		    //T2_COLD3
		EEP.u8_wrBuf[135] = (U8)C_REMEMBER_PARA12_04;		//14		    //T2_COLD4

		//13.制冷室外换热器防过热							℃(含小数点)		5Byte
		EEP.u8_wrBuf[136] = C_REMEMBER_PARA13_00;		//104		   	//T3_COOL0	
		EEP.u8_wrBuf[137] = C_REMEMBER_PARA13_01;		//116		   	//T3_COOL1	
		EEP.u8_wrBuf[138] = C_REMEMBER_PARA13_02;		//120		   	//T3_COOL2	
		EEP.u8_wrBuf[139] = C_REMEMBER_PARA13_03;		//124		   	//T3_COOL3	
		EEP.u8_wrBuf[140] = C_REMEMBER_PARA13_04;		//128		   	//T3_COOL4	

		//14.压缩机延时启动保护							分钟(范围：0~20)	1Byte
		EEP.u8_wrBuf[141] = C_REMEMBER_PARA14_00;		//10		  	//高负荷启停待机时间

		//15.测试模式压缩机运行档位						(范围：1~15)	   3Byte
		EEP.u8_wrBuf[142] = C_REMEMBER_PARA15_00;		//10		   //额定制冷压机运行档位
		EEP.u8_wrBuf[143] = C_REMEMBER_PARA15_01;		//1		       //最小制冷压机运行档位
		EEP.u8_wrBuf[144] = C_REMEMBER_PARA15_02;		//10		   //额定制热压机运行档位
	}
	else
	{
		for (i=17; i<145; i++)
		{
			EEP.u8_wrBuf[i] = EEP.u8_rdBuf[i];
		}
	}
	
	//预留的也清零
	for (i=145; i<158; i++)
	{
		EEP.u8_wrBuf[i] = 0;
	}
	
	ChkSum = 0;
	
	for (j=16; j<158; j++)
	{
		ChkSum += EEP.u8_wrBuf[j];
	}
	
	ChkSum ^= 0xFFFF;
	ChkSum += 1;
	
	EEP.u8_wrBuf[158] = ChkSum & 0xFF;
	EEP.u8_wrBuf[159] = ChkSum >> 8;			
	
	i = 0;
	EEP.u7_Count = 0;
	EEP.Step = ENUM_STEP_IDLE;
	
	while (i < 3)	//最多三次失败重写
	{
		if (EEP.Step == ENUM_STEP_IDLE)
		{
			Write_24C02(&EEP.u8_wrBuf[16],  0x10, 16);
			Write_24C02(&EEP.u8_wrBuf[32],  0x20, 16);
			Write_24C02(&EEP.u8_wrBuf[48],  0x30, 16);
			Write_24C02(&EEP.u8_wrBuf[64],  0x40, 16);
			Write_24C02(&EEP.u8_wrBuf[80],  0x50, 16);						
			Write_24C02(&EEP.u8_wrBuf[96],  0x60, 16);	
			Write_24C02(&EEP.u8_wrBuf[112], 0x70, 16);			
			Write_24C02(&EEP.u8_wrBuf[128], 0x80, 16);			
			Write_24C02(&EEP.u8_wrBuf[144], 0x90, 16);
			
			EEP.Step = ENUM_STEP_WR;
		}
		else if (EEP.Step == ENUM_STEP_WR)
		{
			if (EEP.f_1ms)
			{
				EEP.f_1ms = 0;
				if (++EEP.u7_Count >= 20)	//写EE 20ms后进行读取验证是否写对
				{
					EEP.u7_Count = 0;
					EEP.Step = ENUM_STEP_RD;
				}
			}
		}
		else if (EEP.Step == ENUM_STEP_RD)
		{		
			Read_24C02(&EEP.u8_rdBuf[16],  0x10, 16);
			Read_24C02(&EEP.u8_rdBuf[32],  0x20, 16);
			Read_24C02(&EEP.u8_rdBuf[48],  0x30, 16);
			Read_24C02(&EEP.u8_rdBuf[64],  0x40, 16);
			Read_24C02(&EEP.u8_rdBuf[80],  0x50, 16);		
			Read_24C02(&EEP.u8_rdBuf[96],  0x60, 16);
			Read_24C02(&EEP.u8_rdBuf[112], 0x70, 16);			
			Read_24C02(&EEP.u8_rdBuf[128], 0x80, 16);			
			Read_24C02(&EEP.u8_rdBuf[144], 0x90, 16);
			
			ChkSum = 0;
			
			for (j=16; j<158; j++)
			{
				ChkSum += EEP.u8_rdBuf[j];
			}
			
			ChkSum ^= 0xFFFF;
			ChkSum += 1;
			
			ChkSumL1 = ChkSum & 0xFF;
			ChkSumH1 = ChkSum >> 8;
			
			
			if ((EEP.u8_rdBuf[16] == C_REMEMBER_HEAD) && (ChkSumL1 == EEP.u8_rdBuf[158]) && (ChkSumH1 == EEP.u8_rdBuf[159]))
			{					
				for (j=17; j<160; j++)			//头码不纳入范围
				{
					if ((j!=158) && (j!=159)) 	//校验码不纳入范围
					{
						if (EEP.u8_rdBuf[j] != EEP.u8_wrBuf[j])
						{
							EEP.Step = ENUM_STEP_IDLE;
							i += 1;
							break;
						}
					}
				}
				
				//正确跳出判断循环
				EEP.Step = ENUM_STEP_OK;
				break;					
			}
			else		//失败重来
			{
				EEP.Step = ENUM_STEP_IDLE;
				i += 1;
			}
		}
	}

	if (i >= 3)		//多次失败按默认值
	{
		for (j=17; j<160; j++)			//头码不纳入范围
		{
			if ((j!=158) && (j!=159)) 	//校验码不纳入范围
			{
				EEP.u8_rdBuf[j] = EEP.u8_wrBuf[j];
			}
		}
	}
}
/****************************************************************************************************
Function Name       :void    LowVoltDetect(void)
Description         :低电压检测
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    LowVoltDetect(void)	//2ms运行一次
{
	U8  DataTemp;
	
	if (System.u8_PowerOn_Count >= 3)	//上电300ms后
	{
		if (SCU->LVDCON.LVDO)  //检测到低于低电压阈值
		{
			if (++Remember.u7_LVD_Count >= 5)	//连续10ms的检测到低电压
			{
				Remember.u7_LVD_Count = 0;
				Remember.f_LVD_En = 1;
			}
		}
		else
		{
			Remember.u7_LVD_Count = 0;
			Remember.f_LVD_En = 0;	
				
			P_EEPwren_Off();	//关闭允许写EE
		}
	}
	else
	{
		Remember.u7_LVD_Count = 0;
		Remember.f_LVD_En = 0;
	}
	
	
	if (Remember.f_LVD_En)
	{
		Remember.f_LVD_En = 0;
				
		//只有低电压发生且数据发送变化时才写入EE
		
		DataTemp = 0;		
		if (Tempr.f_TempUnit)		DataTemp |= 0x01;
		if (Fan.f_SweepLR)			DataTemp |= 0x02;
		if (Timer.f_Enable)			DataTemp |= 0x04;
		if (SystemMode.f_Sleep)		DataTemp |= 0x08;
		if (UVC.f_FuncOn)			DataTemp |= 0x10;
		if (WiFi.f_FuncOn)			DataTemp |= 0x20;	
		
		if ((EEP.u8_wrBuf[1]  != System.Enum_Status) ||			
			(EEP.u8_wrBuf[2]  != System.Mode) 		 ||				
			(EEP.u8_wrBuf[3]  != Fan.Mode) 			 ||				
			(EEP.u8_wrBuf[4]  != Tempr.u8_TempCSet)  ||			
			(EEP.u8_wrBuf[5]  != Tempr.u8_ColdCSet)  ||
			(EEP.u8_wrBuf[6]  != Tempr.u8_HeatCSet)  ||		
			(EEP.u8_wrBuf[7]  != Tempr.u8_TempFSet)  ||		
			(EEP.u8_wrBuf[8]  != Tempr.u8_ColdFSet)  ||	
			(EEP.u8_wrBuf[9]  != Tempr.u8_HeatFSet)  ||		
			(EEP.u8_wrBuf[10] != DataTemp))			
		{		
			P_EEPwren_On();						//允许写EE
			Remember_WriteEEFunc(1);
			P_EEPwren_Off();					//关闭允许写EE //lcx add
		}
	}
}



/****************************************************************************************************
Function Name       :void    SaveDatToEEP(void)
Description         :数据变化1s后写入EE
Input               :无
Return              :无
Author              :lcx
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    SaveDatToEEP(void)	//100ms运行一次
{
	U8  DataTemp;
	static U8 u8_lstBuf[11] = {0};

	//只有数据发送变化时才写入EE
	DataTemp = 0;		
	if (Tempr.f_TempUnit)		DataTemp |= 0x01;
	if (Fan.f_SweepLR)			DataTemp |= 0x02;
	if (Timer.f_Enable) 		DataTemp |= 0x04;
	if (SystemMode.f_Sleep) 	DataTemp |= 0x08;
	if (UVC.f_FuncOn)			DataTemp |= 0x10;
	if (WiFi.f_FuncOn)			DataTemp |= 0x20;	

	if ((EEP.u8_wrBuf[1]  != System.Enum_Status) || 		
		(EEP.u8_wrBuf[2]  != System.Mode)		 || 			
		(EEP.u8_wrBuf[3]  != Fan.Mode)			 || 			
		(EEP.u8_wrBuf[4]  != Tempr.u8_TempCSet)  || 		
		(EEP.u8_wrBuf[5]  != Tempr.u8_ColdCSet)  ||
		(EEP.u8_wrBuf[6]  != Tempr.u8_HeatCSet)  || 	
		(EEP.u8_wrBuf[7]  != Tempr.u8_TempFSet)  || 	
		(EEP.u8_wrBuf[8]  != Tempr.u8_ColdFSet)  || 
		(EEP.u8_wrBuf[9]  != Tempr.u8_HeatFSet)  || 	
		(EEP.u8_wrBuf[10] != DataTemp)) 		
	{		
		Remember.f_DataChange = 1;
		if(u8_lstBuf[1] != System.Enum_Status)
		{
			u8_lstBuf[1] = System.Enum_Status;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[2] != System.Mode)
		{
			u8_lstBuf[2] = System.Mode;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[3] != Fan.Mode)
		{
			u8_lstBuf[3] = Fan.Mode;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[4] != Tempr.u8_TempCSet)
		{
			u8_lstBuf[4] = Tempr.u8_TempCSet;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[5] != Tempr.u8_ColdCSet)
		{
			u8_lstBuf[5] = Tempr.u8_ColdCSet;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[6] != Tempr.u8_HeatCSet)
		{
			u8_lstBuf[6] = Tempr.u8_HeatCSet;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[7] != Tempr.u8_TempFSet)
		{
			u8_lstBuf[7] = Tempr.u8_TempFSet;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[8] != Tempr.u8_ColdFSet)
		{
			u8_lstBuf[8] = Tempr.u8_ColdFSet;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[9] != Tempr.u8_HeatFSet)
		{
			u8_lstBuf[9] = Tempr.u8_HeatFSet;
			Remember.u8_WriteDelay = 0;
		}
		if(u8_lstBuf[10] != DataTemp)
		{
			u8_lstBuf[10] = DataTemp;
			Remember.u8_WriteDelay = 0;
		}
	}

	if(Remember.f_DataChange == 1)
	{
		
		if(++Remember.u8_WriteDelay > 10)
		{
			Remember.u8_WriteDelay = 0;
			P_EEPwren_On(); 					//允许写EE
			Remember_WriteEEFunc(1);
			P_EEPwren_Off();					//关闭允许写EE
			Remember.f_DataChange = 0;
		}
	}
	else
	{
		Remember.u8_WriteDelay = 0;
	}
}

/****************************************************************************************************
Function Name       :void    Remember_EE_Dat_Init(void)
Description         :重新初始化EE
Input               :无
Return              :无
Author              :lcx
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_EE_Dat_Init(void)	//100ms
{
/*
	static U8 u8_Cnt = 0;
	static U8 u8_lstInitCnt = 0;
	//====================================================
	//lcx add 20240516
	//连续收到10次，每次1.5s内，最后一次停留在摄氏度，强制初始化内机EE。	
	//====================================================
	if(++u8_Cnt > 15) 
	{
		u8_Cnt = 0;
		Remember.u8_InitCnt = 0;
	}
	if(u8_lstInitCnt != Remember.u8_InitCnt)
	{
		u8_Cnt = 0;
		u8_lstInitCnt = Remember.u8_InitCnt;
		if(Remember.u8_InitCnt == 10 && System.u8_PowerOn_Count < 250) //上电25s内判断
		{
			Remember.u16_InitKey = 0x5A16;	
			Remember.f_AllDatInit = 1;
			Remember.u8_InitCnt = 0;
		}
		
		if(Remember.u16_InitKey == 0x5A16 && Remember.f_AllDatInit == 1)
		{
			P_EEPwren_On();				//允许写EE
			Remember_ReadEEFunc();		//掉电记忆-读取EE数据功能部分
			Remember_WriteEEPara(0);	//0,读取值不正确按默认值并重新写EE; 1,正确时数据备份
			P_EEPwren_Off();
			Remember.u16_InitKey = 0;	
			Remember.f_AllDatInit = 0;
			Remember.f_DataChange = 0;
			Remember.u8_WriteDelay = 0;
		}	
	}
*/	
}

