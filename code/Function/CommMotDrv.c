/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: CommMotDrv.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/08/19
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"


STRUCT_COMMMOTDRV    CommMotDrv;

/****************************************************************************************************
Function Name       :ENUM_MBDXBYTE5    BaseRunTx_Byte5_InDoorRunMode(void)
Description         :当前室内机的运转模式
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte5_InDoorRunMode(void)
{
	UNION_MBTXBYTE5    result;
	
	result.Byte = 0;	//首先清0
	
	//--------------------------------------------------------------------------------------------------//
	
	if ((System.Enum_Status == ENUM_STATUS_INIT) || (System.Enum_Status == ENUM_STATUS_OFF))
	{
		result.InDoorRunMode = ENUM_MBDXBYTE5_OFF;
	}
	else
	{
		if 		(SystemMode.f_Force)				result.InDoorRunMode = ENUM_MBDXBYTE5_FORCECOOL;	//强制制冷
		else if (Defrost.f_Enable)					result.InDoorRunMode = ENUM_MBDXBYTE5_DEFROST;		//化霜
		else
		{
			if 		(System.Mode == ENUM_SYSMODE_COLD)	result.InDoorRunMode = ENUM_MBDXBYTE5_COOL;		//制冷
			else if (System.Mode == ENUM_SYSMODE_HUM)	result.InDoorRunMode = ENUM_MBDXBYTE5_DRY;		//除湿
			else if (System.Mode == ENUM_SYSMODE_FAN)	result.InDoorRunMode = ENUM_MBDXBYTE5_ONLYFAN;	//只送风
			else if (System.Mode == ENUM_SYSMODE_HEAT)	result.InDoorRunMode = ENUM_MBDXBYTE5_HEAT;		//制热
			else if (System.Mode == ENUM_SYSMODE_INTE)  
			{
				if 		(SystemMode.f_Cold == 1)	result.InDoorRunMode = ENUM_MBDXBYTE5_COOL;		//制冷
				else if (SystemMode.f_Heat == 1)	result.InDoorRunMode = ENUM_MBDXBYTE5_HEAT;		//制热
				else 								result.InDoorRunMode = ENUM_MBDXBYTE5_ONLYFAN;	//只送风
			}
		}
		
	}	
		
	return    result.Byte;
}
/****************************************************************************************************
Function Name       :U8    BaseRunTx_Byte6_OutDoorTargetFreq(void)
Description         :要求室外机运转的目标频率(整数部分)
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte6_OutDoorTargetFreq(void)
{
	return    Comp.u8_TargetFreq;

}
/****************************************************************************************************
Function Name       :U8    BaseRunTx_Byte7_OutDoorTargetFreqDotMul60(void)
Description         :要求室外机运转的目标频率(高字节)
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte7_OutDoorTargetFreqDotMul60(void)
{
	S16   temp;
	
	temp = T4.s16_ValueMul10;								//室外环境温度
	
	if (temp < -150)		temp = -150;					//按最低温度-15度进行计算
	if (temp > 1100)		temp = 1100;					//按最高温度110度进行计算
		
//	0.0-0.4->0; 0.5-0.9->0.5	
	if ((temp%10) < 5)		return (((temp/10)<<1)+30);		//不含0.5
	else					return (((temp/10)<<1)+31);		//含0.5

}
/****************************************************************************************************
Function Name       :U8    BaseRunTx_Byte8_InDoorTempSet(void)
Description         :当前室内机的设置温度
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte8_InDoorTempSet(void)
{
	U8  TempSet;  
	
	if (System.Mode == ENUM_SYSMODE_HUM)	TempSet = Tempr.u8_HumiCSet;
	else									TempSet = Tempr.u8_TempCSet;
		
	return ((TempSet<<1)+30);
}
/****************************************************************************************************
Function Name       :U8    BaseRunTx_Byte9_InDoorTemp(void)
Description         :当前室内机的环境温度
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte9_InDoorTemp(void)
{
	S16   temp;
	
	temp = T1.s16_ValueMul10;								//室内环境温度
	
	if (temp < -150)		temp = -150;					//按最低温度-15度进行计算
	if (temp > 1100)		temp = 1100;					//按最高温度110度进行计算
		
//	0.0-0.4->0; 0.5-0.9->0.5	
	if ((temp%10) < 5)		return (((temp/10)<<1)+30);		//不含0.5
	else					return (((temp/10)<<1)+31);		//含0.5

}
/****************************************************************************************************
Function Name       :STRUCT_MBTXBYTE10    BaseRunTx_Byte10_InDoorProtect1(void)
Description         :当前室内机保护状态1
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
STRUCT_MBTXBYTE10    BaseRunTx_Byte10_InDoorProtect1(void)
{
	STRUCT_MBTXBYTE10    temp;

	if(Fan.Indoor.f_ErrorDeal) //带故障运行次数内，报外机清故障重启。 lcx add 20240622
	{
		temp.f_FanSpeed    = 1;           				//风机失速 Ed
	}
	else
	{
		temp.f_FanSpeed    = 0;           				//风机失速 Ed
	}

	temp.f_EEPROM 	   = System.f_InEEpromErr;		//EEPROM故障 F2
//	temp.f_CommDisp    = F_uart4_CommErr;		   	//室内板与显示板通信故障 E8
	temp.f_TempRoom    = T1.f_Error;		   		//T1传感器故障
	temp.f_TempCoil1   = T2.f_Error;		   		//T2传感器故障
	temp.f_TempCoil2   = T3.f_Error;		   		//T3传感器故障	
	temp.f_TempOutDoor = T4.f_Error;	   			//T4传感器故障
	temp.f_TempExhaust = Tp.f_Error;	   			//TP传感器故障
	
	return temp;
}
/****************************************************************************************************
Function Name       :STRUCT_MBTXBYTE11    BaseRunTx_Byte11_InDoorProtect2(void)
Description         :当前室内机保护状态2
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
STRUCT_MBTXBYTE11    BaseRunTx_Byte11_InDoorProtect2(void)
{
	STRUCT_MBTXBYTE11    temp;

	temp.f_AntiCold 		   = Protect.f_T2Cold;        					//防冻结保护(制冷时T2温度过低)
	temp.f_TempCoil2HighTemp   = Protect.f_T3Cold;							//T3高温保护(制冷时T3温度过高)
	temp.f_HumiModule 		   = 0;											//湿度传感器故障(没有填0)
	temp.f_Pump 			   = 0;		    								//水泵保护功能(没有填0)
	temp.f_FDP 				   = 0;		   									//缺氟保护(没有填0)
	temp.f_CommMotDrv 		   = F_uart0_CommErr;							//室内与驱动板通信故障
	temp.f_TempExhaustHighTemp = Protect.f_Tp;								//排气高温保护
	temp.Reserved 			   = 0;		    								//预留
	
	return temp;
}
/****************************************************************************************************
Function Name       :STRUCT_MBTXBYTE11    BaseRunTx_Byte12_InDoorProtect3(void)
Description         :当前室内机保护状态3
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
STRUCT_MBTXBYTE12    BaseRunTx_Byte12_InDoorProtect3(void)
{
	STRUCT_MBTXBYTE12    temp;
	
	temp.Reserved0 = 0;
	
	//排气限频
	if ((Protect.TpStatus != ENUM_PROSTATUS_NORMAL) && (Protect.TpStatus != ENUM_PROSTATUS_PROTECT))				temp.f_ExhaustLimit = 1; 
	else   																											temp.f_ExhaustLimit = 0; 
	
	//盘管1限频
	if ((Protect.T2ColdStatus != ENUM_PROSTATUS_NORMAL) && (Protect.T2ColdStatus != ENUM_PROSTATUS_PROTECT))		temp.f_Coil1Limit = 1;	
	else	    																									temp.f_Coil1Limit = 0;	
	
	//盘管2限频	
	if ((Protect.T3ColdStatus != ENUM_PROSTATUS_NORMAL) && (Protect.T3ColdStatus != ENUM_PROSTATUS_PROTECT))		temp.f_Coil2Limit = 1;	
	else	    																									temp.f_Coil2Limit = 0;	
	
	//T4限频
	if (System.f_T4Limit)		temp.f_T4Limit = 1;
	else						temp.f_T4Limit = 0;
	
	//睡眠标志
	if (SystemMode.f_Sleep == 1)	temp.f_Sleep = 1;
	else							temp.f_Sleep = 0;
	
	//强力标志
	if (SystemMode.f_Force == 1)	temp.f_ForceMode = 1;
	else							temp.f_ForceMode = 0;
	
	return temp;
}
/****************************************************************************************************
Function Name       :U8    BaseRunTx_Byte13_InDoorFanSpeedDiv10(void)
Description         :当前室内风机风速(实际值/10)
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte13_InDoorFanSpeedDiv10(void)
{
	return    (Fan.Indoor.u16_TargetRPM/10);

}
/****************************************************************************************************
Function Name       :U8    BaseRunTx_Byte14_TempCoil1(void)
Description         :当前室内管温温度值1
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte14_TempCoil1(void)
{
	S16   temp;
	
	temp = T2.s16_ValueMul10;								//室内盘管温度
	
	if (temp < -150)		temp = -150;					//按最低温度-15度进行计算
	if (temp > 1100)		temp = 1100;					//按最高温度110度进行计算
		
//	0.0-0.4->0; 0.5-0.9->0.5	
	if ((temp%10) < 5)		return (((temp/10)<<1)+30);		//不含0.5
	else					return (((temp/10)<<1)+31);		//含0.5
}
/****************************************************************************************************
Function Name       :U8    BaseRunTx_Byte15_TempCoil2(void)
Description         :当前室内管温温度值2
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte15_TempCoil2(void)
{
	S16   temp;
	
	temp = T3.s16_ValueMul10;								//室外盘管温度
	
	if (temp < -150)		temp = -150;					//按最低温度-15度进行计算
	if (temp > 1100)		temp = 1100;					//按最高温度110度进行计算
		
//	0.0-0.4->0; 0.5-0.9->0.5	
	if ((temp%10) < 5)		return (((temp/10)<<1)+30);		//不含0.5
	else					return (((temp/10)<<1)+31);		//含0.5
}
/****************************************************************************************************
Function Name       :U8    BaseRunTx_Byte16_TempExhaust(void)
Description         :当前压缩机排气温度
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    BaseRunTx_Byte16_TempExhaust(void)
{
	S8    temp;
	
	if (Tp.f_Error == 0)
	{
		temp = Tp.s8_Value;
		
		if (temp < -29)		temp = -29;		//按最低温度-29度进行计算
		if (temp > 125)		temp = 125;		//按最高温度125度进行计算
		
		return (temp+30);
	}
	else    //排气故障发送0
	{
		return    0;
	}
}
/****************************************************************************************************
Function Name       :STRUCT_MBTXBYTE17    BaseRunTx_Byte17_InDoorStatus(void)
Description         :当前室内机的状态
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
STRUCT_MBTXBYTE17    BaseRunTx_Byte17_InDoorStatus(void)
{
    STRUCT_MBTXBYTE17    temp;
	
	//快检状态/商检标志
	if ((System.Enum_Status == ENUM_STATUS_BUSSCHK) || (System.Enum_Status == ENUM_STATUS_SELCHK))	temp.f_FastChk = 1;					//快检默认无效
	else																							temp.f_FastChk = 0;	
	
	//防霉功能标志
	temp.f_DeMold = Fan.f_DeMold ;

	//通风标志
	if (SystemMode.f_Heat && SystemMode.f_TempCEC && Fan.Indoor.f_DrvOn)		temp.f_Ventilate = 1;
	else																		temp.f_Ventilate = 0;
	
	//压缩机预热标志默认无预热	
	temp.f_CompPre = 0;					
	
	//外风机开关标志
	temp.f_FanOutdoorOn = Fan.Outdoor.f_DrvOn;
	
	if (SystemMode.f_PerTest)
	{
		if (SystemMode.f_Cold && (Tempr.u8_TempCSet == 29))	//最小能力 b5b6b7:011
		{
			temp.f_bit5 = 0;
			temp.f_bit6 = 1;
			temp.f_bit7 = 1;
		}			
		else if ((SystemMode.f_Cold && (Tempr.u8_TempCSet == 30)) || (SystemMode.f_Heat && (Tempr.u8_TempCSet == 17)))	//额定能力 b5b6b7:100
		{
			temp.f_bit5 = 1;
			temp.f_bit6 = 0;
			temp.f_bit7 = 0;
		}	
	}
	else
	{
		temp.f_bit5 = 0;
		temp.f_bit6 = 0;
		temp.f_bit7 = 0;
	}
		
	return    temp;
}
/****************************************************************************************************
Function Name       :void    CommMotDrv_BaseRunTx(void)
Description         :基本运行指令发送数据处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    CommMotDrv_BaseRunTx(void)
{	
	CommMotDrv.BaseRun.Tx.Byte5.Byte = BaseRunTx_Byte5_InDoorRunMode();    									//当前室内机的运转模式
	CommMotDrv.BaseRun.Tx.Byte6.OutDoorTargetFreq = BaseRunTx_Byte6_OutDoorTargetFreq();					//要求室外机运转的目标频率(低字节)
	CommMotDrv.BaseRun.Tx.Byte7.OutDoorTargetFreqDotMul60 = BaseRunTx_Byte7_OutDoorTargetFreqDotMul60();	//要求室外机运转的目标频率(高字节)
	CommMotDrv.BaseRun.Tx.Byte8.InDoorTempSet = BaseRunTx_Byte8_InDoorTempSet();			//当前室内机的设置温度
	CommMotDrv.BaseRun.Tx.Byte9.InDoorTemp = BaseRunTx_Byte9_InDoorTemp();					//当前室内机的环境温度
	CommMotDrv.BaseRun.Tx.Byte10.InDoorProtect1 = BaseRunTx_Byte10_InDoorProtect1();		//当前室内机保护状态1
	CommMotDrv.BaseRun.Tx.Byte11.InDoorProtect2 = BaseRunTx_Byte11_InDoorProtect2();		//当前室内机保护状态2
	CommMotDrv.BaseRun.Tx.Byte12.InDoorProtect3 = BaseRunTx_Byte12_InDoorProtect3();		//当前室内机保护状态3
	CommMotDrv.BaseRun.Tx.Byte13.InDoorFanSpeedDiv10 = BaseRunTx_Byte13_InDoorFanSpeedDiv10();	//当前室内风机风速(实际值/10)
	CommMotDrv.BaseRun.Tx.Byte14.TempCoil1 = BaseRunTx_Byte14_TempCoil1();					//当前室内管温温度值1
	CommMotDrv.BaseRun.Tx.Byte15.TempCoil2 = BaseRunTx_Byte15_TempCoil2();					//当前室内管温温度值2
	CommMotDrv.BaseRun.Tx.Byte16.TempExhaust = BaseRunTx_Byte16_TempExhaust();				//当前压缩机排气温度
	CommMotDrv.BaseRun.Tx.Byte17.InDoorStatus = BaseRunTx_Byte17_InDoorStatus();			//当前室内机的状态
	
}
//===================================================================================================//
//===================================================================================================//
/****************************************************************************************************
Function Name       :void    CommMotDrv_BaseRunRx(void)
Description         :基本运行指令接收数据处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
//-- lhh---//
unsigned char l_outDoorMode = 0;


void    CommMotDrv_BaseRunRx(void)
{
	volatile    ENUM_MBDXBYTE5      OutDoorRunMode;							//当前室外机的运转模式
	volatile    U16				   	InDoorRealRPM;							//室内风机转速  实际值(RPM)
	volatile    U16				  	OutDoorRealRPM;							//室外风机转速  实际值(RPM)
	volatile    U8				  	OutDoorCurrentMul8;						//室外机电流值 实际值乘以8
	volatile    U16				  	OutDoorVolt;							//当前室外机的直流电压有效值 实际值
	volatile    U16					ACVoltValue;							//交流电压值

	
	//当前室外机的运转模式
	OutDoorRunMode = CommMotDrv.BaseRun.Rx.Byte5.OutDoorRunMode;			
	l_outDoorMode = OutDoorRunMode;
	
	
	//当前室外机运转的实际频率
	Comp.u8_RealHZ = CommMotDrv.BaseRun.Rx.Byte6.Byte;
	
	//室内风机转速  实际值(RPM)
	InDoorRealRPM = CommMotDrv.BaseRun.Rx.Byte7.Byte;
	InDoorRealRPM <<= 3;
	InDoorRealRPM += CommMotDrv.BaseRun.Rx.Byte7.Byte<<1;
	Fan.Indoor.u16_RealRPM = InDoorRealRPM;
	
	//室外风机转速  实际值(RPM)
	OutDoorRealRPM = CommMotDrv.BaseRun.Rx.Byte8.OutDoorRealRPMDiv10;
	OutDoorRealRPM <<= 3;
	OutDoorRealRPM += CommMotDrv.BaseRun.Rx.Byte8.OutDoorRealRPMDiv10<<1;
	Fan.Outdoor.u16_RealRPM = OutDoorRealRPM;
	
	//室外机电流值 实际值乘以8
	OutDoorCurrentMul8 = CommMotDrv.BaseRun.Rx.Byte9.OutDoorCurrentMul8;
	System.u8_OutDoorCurrentMul8 = OutDoorCurrentMul8;
	
	//当前室外机的直流电压有效值 实际值
	OutDoorVolt = CommMotDrv.BaseRun.Rx.Byte10.OutDoorVoltDiv2;
	OutDoorVolt <<= 1;
	System.u16_DCVoltValue = OutDoorVolt;
	
	//当前室外机的状态1
	//if (CommMotDrv.BaseRun.Rx.Byte11.Byte)
	{
		//Bit0：电流限频L3
		if (CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_CurrentLimitFreq)			
		{
		
		}
		
		//Bit1：IPM温度限频L4
		if (CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_IPMTempLimitFreq)
		{
		
		}
		
		//Bit2：电压限频L5	
		if (CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_VoltLimitFreq)
		{
		
		}

		//Bit3：IPM模块温度保护
		if ((CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_IPMTempProtect) || (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_CompIPMPro))
		{
			Comp.f_IPMPro = 1;
		}
		else
		{
			Comp.f_IPMPro = 0;
		}

		//Bit4：室外机电流保护	
		if (CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_CurrentProtect)
		{
			System.f_CurrentProtect = 1;
		}
		else
		{
			System.f_CurrentProtect = 0;
		}
		
		//Bit5：通信故障
	    if (CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_CommErr)
		{
			System.f_InOutCommErr = 1;
		}	
		else
		{
			System.f_InOutCommErr = 0;
		}
		
		//Bit6：E方故障系统参数错误	
		if (CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_EEPROMErr)
		{
			System.f_OutEEpromErr = 1;
		}	
		else
		{
			System.f_OutEEpromErr = 0;
		}

		//Bit7：内机风机故障	
		if (CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_FanIndoorErr)
		{
			Fan.Indoor.f_Error = 1;
		}
		else
		{
			Fan.Indoor.f_Error = 0;
		}	
	}
	
	//当前室外机的状态2
	//if (CommMotDrv.BaseRun.Rx.Byte12.Byte)
	{
		//Bit0: PFC模块开关停机
		if (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_PFCSwitchOff)
		{
		
		}
		
		//Bit1: IPM模块温度开路或短路
		if (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_IPMSensorErr)
		{
			Comp.f_IPMErr = 1;
		}
		else
		{
			Comp.f_IPMErr = 0;
		}
		
		//Bit2: 交流电压过低保护	
		if (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_ACVoltLowPro)
		{
		
		}

		
		//Bit3: 高频启动故障	
		if (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_HighFreqStartErr)
		{
		
		}
		
		//Bit4: 压机过电流故障P49	
		if (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_CompOvCurrErr)
		{
		
		}
		
		//Bit5: 压缩机IPM模块保护P0		
		if (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_CompIPMPro)
		{
		
		}
		else
		{
		
		}
		
		//Bit6: 电压过低保护P10		
		if ((CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_VoltLowPro) || (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_ACVoltLowPro))
		{
			System.f_VoltLowPro = 1;
		}
		else
		{
			System.f_VoltLowPro = 0;
		}
		
		//Bit7: 电压过高保护P11		
		if (CommMotDrv.BaseRun.Rx.Byte12.OutDoorStatus2.f_VoltHighPro)
		{
		
		}	
	}
	
	//当前室外机的状态3	
	//if (CommMotDrv.BaseRun.Rx.Byte13.Byte)
	{

		//--------------------------------------------------------------------------------
		/*
		//Bit0：预留	
		//Bit1：压缩机过流P41
		//Bit2: 压缩机启动故障P42
		//Bit3: 压缩机缺相保护P43
		//Bit4: 压缩机零速保护P44
		//Bit5: 电压瞬降保护P45
		//Bit6: 压缩机失速保护P46
		//Bit7: PFC瞬间关断P47
		*/

//		if ((CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) ||  //Bit1：压缩机过流P41
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//			(CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr) || 
//		{
//			Comp.f_StartErr = 1;
//		}
//		else
//		{
//			Comp.f_StartErr = 0;
//		}

		//--------------------------------------------------------------------------------

		
		//Bit1：压缩机过流P41
		if (CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompOvCurr)
		{
		
		}

		//Bit2: 压缩机启动故障P42
		if (CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompStartErr)
		{
			Comp.f_StartErr = 1;
		}
		else
		{
			Comp.f_StartErr = 0;
		}
		
		//Bit3: 压缩机缺相保护P43
		if (CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompPhasePro)
		{
			Comp.f_StartErr = 1;  //缺相保护纳入启动故障（驱动保护F7） lcx add 20240612
		}
		
		//Bit4: 压缩机零速保护P44
		if (CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompZeroSpeedPro)
		{
		
		}
		
		//Bit5: 电压瞬降保护P45
		if (CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_VoltLessQuickPro)
		{
		
		}
		
		//Bit6: 压缩机失速保护P46
		if (CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_CompLostSpeedPro)
		{
		
		}
		
		//Bit7: PFC瞬间关断P47
		if (CommMotDrv.BaseRun.Rx.Byte13.OutDoorStatus3.f_PFCOffQuick)
		{
		
		}
	}
	
	//当前室外机的状态4	
	//if (CommMotDrv.BaseRun.Rx.Byte14.Byte)
	{
		//Bit0: 压机排气高温限频L2	
		if (CommMotDrv.BaseRun.Rx.Byte14.OutDoorStatus4.f_TpHighLimit)
		{
		
		}
		
		//Bit1: 压机排气高温保护P6	
		if (CommMotDrv.BaseRun.Rx.Byte14.OutDoorStatus4.f_TpHighPro)
		{
		
		}
		
		//Bit2: 冷凝器高温限频L1	
		if (CommMotDrv.BaseRun.Rx.Byte14.OutDoorStatus4.f_T3HighLimit)
		{
		
		}
		
		//Bit3: 冷凝器高温保护PA	
		if (CommMotDrv.BaseRun.Rx.Byte14.OutDoorStatus4.f_T3HighPro)
		{
		
		}
	}
	
	
	//当前室外机的状态5
	if (CommMotDrv.BaseRun.Rx.Byte15.Byte)
	{
		//Bit0: 压缩机预热标志
		if (CommMotDrv.BaseRun.Rx.Byte15.OutDoorStatus5.f_CompPreHeat)
		{
		
		}
	}		
			
	//当前室外机的状态6
	Fan.Outdoor.f_Error = 0;
	
	//if (CommMotDrv.BaseRun.Rx.Byte16.Byte)
	{	
		//Bit0: 室外直流风机故障E7
		if (CommMotDrv.BaseRun.Rx.Byte16.OutDoorStatus6.f_FanOutdoorErr)
		{
			Fan.Outdoor.f_Error = 1;
		}
		
		//Bit1: 外风机过流(外置驱动)	
		if (CommMotDrv.BaseRun.Rx.Byte16.OutDoorStatus6.f_FanOutdoorOvCurr)
		{
			Fan.Outdoor.f_Error = 1;
		}
		
		//Bit2: 外风机失速(外置驱动)
		if (CommMotDrv.BaseRun.Rx.Byte16.OutDoorStatus6.f_FanOutdoorLostSpd)
		{
			Fan.Outdoor.f_Error = 1;
		}
		
		//Bit3: 外风机缺相(外置驱动)
		if (CommMotDrv.BaseRun.Rx.Byte16.OutDoorStatus6.f_FanOutdoorLostPhase)
		{
			Fan.Outdoor.f_Error = 1;
		}
		
		//Bit4: 外风机零速(外置驱动)	
		if (CommMotDrv.BaseRun.Rx.Byte16.OutDoorStatus6.f_FanOutdoorZeroSpd)
		{
			Fan.Outdoor.f_Error = 1;
		}
	}			
	
	//第17字节 交流电压实际值-60
	ACVoltValue = CommMotDrv.BaseRun.Rx.Byte17.Byte;
	ACVoltValue += 60;
	System.u16_ACVoltValue = ACVoltValue;
}
/****************************************************************************************************
Function Name       :void    CommMotDrv_ReqSetTx(void)
Description         :查询设置指令发送数据处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    CommMotDrv_ReqSetTx(void)
{
	if(l_contData.cont_Enable == 1)
	{
		//压缩机频率设定（整数部分）
		CommMotDrv.ReqSet.Tx.Byte5.Byte  = l_contData.compHz; 
			
		//室外风机风速设定（低字节）
		CommMotDrv.ReqSet.Tx.Byte6.Byte  = (unsigned char)(l_contData.ourdoor_Wind & 0x00ff);    
		
		//室外风机风速设定（高字节）
		CommMotDrv.ReqSet.Tx.Byte7.Byte  = (unsigned char)((l_contData.ourdoor_Wind & 0xff00)>>8);
			
		//室外电子膨胀阀开度设定（低字节）	
		CommMotDrv.ReqSet.Tx.Byte8.Byte  = 0; 

		//室外电子膨胀阀开度设定（高字节）	
		CommMotDrv.ReqSet.Tx.Byte9.Byte  = 0;

		//四通阀开关设定
		CommMotDrv.ReqSet.Tx.Byte10.Byte  = l_contData.four_is;
		
		//排气目标温度
		CommMotDrv.ReqSet.Tx.Byte11.Byte  = 0;

		//设定强制设定方式
		CommMotDrv.ReqSet.Tx.Byte12.Byte  = ENUM_FORCESET_REQ;
		
		//旁通阀开关设定
		CommMotDrv.ReqSet.Tx.Byte13.Byte  = ENUM_BYPASSVALVESET_OFF;

		//压缩机频率设定（小数部分）
		CommMotDrv.ReqSet.Tx.Byte14.Byte  = 0; 

		//indoor_wind
		CommMotDrv.ReqSet.Tx.Byte15.Byte = (unsigned char)l_contData.indoor_Wind;
		CommMotDrv.ReqSet.Tx.Byte16.Byte = (unsigned char)((l_contData.indoor_Wind & 0xff00)>>8);
		
		CommMotDrv.ReqSet.Tx.Byte17.Byte = 0;
	
	}
	else
	{
	
		//压缩机频率设定（整数部分）
		CommMotDrv.ReqSet.Tx.Byte5.u8_CompFreqSet = 0; 

		//室外风机风速设定（低字节）
		CommMotDrv.ReqSet.Tx.Byte6.u8_OutDoorFanSpeedSetL = 0;    
		
		//室外风机风速设定（高字节）
		CommMotDrv.ReqSet.Tx.Byte7.u8_OutDoorFanSpeedSetH = 0;

		//室外电子膨胀阀开度设定（低字节）	
		CommMotDrv.ReqSet.Tx.Byte8.u8_OutDoorEpsValveSetL = 0; 

		//室外电子膨胀阀开度设定（高字节）	
		CommMotDrv.ReqSet.Tx.Byte9.u8_OutDoorEpsValveSetH = 0;

		//四通阀开关设定
		CommMotDrv.ReqSet.Tx.Byte10.Enum_FourWay = ENUM_FOURWAYVALVE_COMMON;
		
		//排气目标温度
		CommMotDrv.ReqSet.Tx.Byte11.u8_TempExhaustTarget = 0;

		//设定强制设定方式
		CommMotDrv.ReqSet.Tx.Byte12.Enum_ForceSet = ENUM_FORCESET_REQ;
		
		//旁通阀开关设定
		CommMotDrv.ReqSet.Tx.Byte13.Enum_BypassValveSet = ENUM_BYPASSVALVESET_OFF;

		//压缩机频率设定（小数部分）
		CommMotDrv.ReqSet.Tx.Byte14.u8_CompFreqDotSet = 0; 

		//其他预留
		CommMotDrv.ReqSet.Tx.Byte15.Byte = 0;
		CommMotDrv.ReqSet.Tx.Byte16.Byte = 0;
		CommMotDrv.ReqSet.Tx.Byte17.Byte = 0;
	}
}
/****************************************************************************************************
Function Name       :void    CommMotDrv_ReqSetRx(void)
Description         :查询设置指令接收数据处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    CommMotDrv_ReqSetRx(void)
{
	volatile    U16    OutDoorFanSpeed;		//风机转速
    volatile    U16    EpsValveOpenAngle;	//电子膨胀阀开度
	volatile    U16    VoltBusValue;		//母线电压有效值
	volatile    U8     IPMAdValue;			//IPM模块温度AD值
	volatile    U8     CompFreqReal;		//压机实际运行频率（整数部分）
	volatile    U8     CompFreqRealDot;		//压机实际运行频率（小数部分）
	
	//当前室外机状态1
	if (CommMotDrv.ReqSet.Rx.Byte5.Byte)
	{
		//Bit0：室外E方故障E51
		if (CommMotDrv.ReqSet.Rx.Byte5.OutDoorStatus1.f_OutDoorEEPROMErr)
		{
		
		}

		//Bit1：室外T3传感器故障E52
		if (CommMotDrv.ReqSet.Rx.Byte5.OutDoorStatus1.f_OutDoorT3Err)
		{
		
		}

		//Bit2：室外T4传感器故障E51
		if (CommMotDrv.ReqSet.Rx.Byte5.OutDoorStatus1.f_OutDoorT4Err)
		{
		
		}
		
		//Bit3：室外TP传感器故障E54
		if (CommMotDrv.ReqSet.Rx.Byte5.OutDoorStatus1.f_OutDoorTPErr)
		{
		
		}

		//Bit4：模块温度传感器故障E55
		if (CommMotDrv.ReqSet.Rx.Byte5.OutDoorStatus1.f_ModuleTempErr)
		{
		
		}

		//Bit6：室外直流风机故障E7
		if (CommMotDrv.ReqSet.Rx.Byte5.OutDoorStatus1.f_OutDoorFanErr)
		{
		
		}			
	}
	
	//--------------------------------------------------------------------------------------------------//
	
	//当前室外机状态2
	if (CommMotDrv.ReqSet.Rx.Byte6.Byte)
	{
		//Bit1：压缩机过流 P41
		if (CommMotDrv.ReqSet.Rx.Byte6.OutDoorStatus2.f_CompOvCurrent)
		{
		
		}
		
		//Bit2：压机启动故障P42
		if (CommMotDrv.ReqSet.Rx.Byte6.OutDoorStatus2.f_CompStartErr)
		{
		
		}

		//Bit3：压机缺相保护P43
		if (CommMotDrv.ReqSet.Rx.Byte6.OutDoorStatus2.f_CompPhaseProtect)
		{
		
		}

		//Bit4：压机零速保护P44
		if (CommMotDrv.ReqSet.Rx.Byte6.OutDoorStatus2.f_CompZeroProtect)
		{
		
		}			

		//Bit5：电压瞬降保护P45
		if (CommMotDrv.ReqSet.Rx.Byte6.OutDoorStatus2.f_CompVoltLowQProtect)
		{
		
		}			

		//Bit6：压机失速保护P46
		if (CommMotDrv.ReqSet.Rx.Byte6.OutDoorStatus2.f_CompLostSpeedProtect)
		{
		
		}

		//Bit7：PFC瞬间关断P47
		if (CommMotDrv.ReqSet.Rx.Byte6.OutDoorStatus2.f_PFCOffProtect)
		{
		
		}			
	}
	
	//--------------------------------------------------------------------------------------------------//
	
	//当前室外机状态3
	if (CommMotDrv.ReqSet.Rx.Byte7.Byte)
	{	
		//Bit1：压机过电流故障P49
		if (CommMotDrv.ReqSet.Rx.Byte7.OutDoorStatus3.f_CompOvCurrentErr)
		{
		
		}
		
		//Bit2：室外IPM模块保护P0
		if (CommMotDrv.ReqSet.Rx.Byte7.OutDoorStatus3.f_OutDoorIPMProtect)
		{
		
		}

		//Bit3：电压过低保护P10
		if (CommMotDrv.ReqSet.Rx.Byte7.OutDoorStatus3.f_VoltLowProtect)
		{
		
		}

		//Bit4：电压过高保护P11
		if (CommMotDrv.ReqSet.Rx.Byte7.OutDoorStatus3.f_VoltHighProtect)
		{
		
		}

		//Bit5：室外直流侧电压保护
		if (CommMotDrv.ReqSet.Rx.Byte7.OutDoorStatus3.f_OutDoorDCVoltProtect)
		{
		
		}			

		//Bit6：室外电流保护P81	
		if (CommMotDrv.ReqSet.Rx.Byte7.OutDoorStatus3.f_OutDoorCurrentProtect)
		{
		
		}			
	}
	
	//--------------------------------------------------------------------------------------------------//
	
	//当前室外机状态4
	if (CommMotDrv.ReqSet.Rx.Byte8.Byte)
	{
		//Bit0：压机排气高温限频L2
		if (CommMotDrv.ReqSet.Rx.Byte8.OutDoorStatus4.f_CompTPHighFreqLimit)
		{
		
		}

		//Bit1：压机排气高温保护P6
		if (CommMotDrv.ReqSet.Rx.Byte8.OutDoorStatus4.f_CompTPHighProtect)
		{
		
		}

		//Bit2：冷凝器高温限频L1
		if (CommMotDrv.ReqSet.Rx.Byte8.OutDoorStatus4.f_CdsTempHighFreqLimit)
		{
		
		}

		//Bit3：冷凝器高温保护PA
		if (CommMotDrv.ReqSet.Rx.Byte8.OutDoorStatus4.f_CdsTempHighProtect)
		{
		
		}			
	}

	//--------------------------------------------------------------------------------------------------//
	
	//当前室外机状态5
	if (CommMotDrv.ReqSet.Rx.Byte9.Byte)
	{
		//Bit0：电压限频L5
		if (CommMotDrv.ReqSet.Rx.Byte9.OutDoorStatus5.f_VoltFreqLimit)
		{
		
		}

		//Bit1：电流限频、限频停机L3
		if (CommMotDrv.ReqSet.Rx.Byte9.OutDoorStatus5.f_CurrentFreqLimit)
		{
		
		}

		//Bit2：PFC模块开关停机PF
		if (CommMotDrv.ReqSet.Rx.Byte9.OutDoorStatus5.f_PFCSwitchOff)
		{
		
		}

		//Bit3：IPM模块故障限频L6
		if (CommMotDrv.ReqSet.Rx.Byte9.OutDoorStatus5.f_IPMErrFreqLimit)
		{
		
		}			
	}

	//--------------------------------------------------------------------------------------------------//
	
	//当前室外机状态6
	if (CommMotDrv.ReqSet.Rx.Byte10.Byte)
	{
		//Bit0：交流风机室外低风
		if (CommMotDrv.ReqSet.Rx.Byte10.OutDoorStatus6.f_OutDoorACFanLow)
		{
		
		}

		//Bit1：交流风机室外中风
		if (CommMotDrv.ReqSet.Rx.Byte10.OutDoorStatus6.f_OutDoorACFanMed)
		{
		
		}

		//Bit2：交流风机室外高风
		if (CommMotDrv.ReqSet.Rx.Byte10.OutDoorStatus6.f_OutDoorACFanHigh)
		{
		
		}

		//Bit3：四通阀开关状态
		if (CommMotDrv.ReqSet.Rx.Byte10.OutDoorStatus6.f_FourWayOnOff)
		{
		
		}			

		//Bit4：外风机过流（外置驱动）
		if (CommMotDrv.ReqSet.Rx.Byte10.OutDoorStatus6.f_OutDoorFanOvCurrent)
		{
		
		}			

		//Bit5：外风机失速（外置驱动）
		if (CommMotDrv.ReqSet.Rx.Byte10.OutDoorStatus6.f_OutDoorFanLostSpeed)
		{
		
		}

		//Bit6：外风机缺相（外置驱动）
		if (CommMotDrv.ReqSet.Rx.Byte10.OutDoorStatus6.f_OutDoorFanLostPhase)
		{
		
		}			

		//Bit7：外风机零速（外置驱动）
		if (CommMotDrv.ReqSet.Rx.Byte10.OutDoorStatus6.f_OutDoorFanZero)
		{
		
		}			
	}

	//--------------------------------------------------------------------------------------------------//

	//当前室外直流风机转速/8
	OutDoorFanSpeed = CommMotDrv.ReqSet.Rx.Byte11.u8_OutDoorFanSpeedDiv8;			
	OutDoorFanSpeed <<= 3;
	
	//--------------------------------------------------------------------------------------------------//

	//当前室外电子膨胀阀开度/8
	EpsValveOpenAngle = CommMotDrv.ReqSet.Rx.Byte12.u8_EpsValveOpenAngleDiv8;
	EpsValveOpenAngle <<= 3;
	
	//--------------------------------------------------------------------------------------------------//
	
	//母线电压有效值
	VoltBusValue = CommMotDrv.ReqSet.Rx.Byte13.u8_VoltBusValueDiv2;		
	VoltBusValue <<= 1;
	
	//IPM模块温度AD值
	IPMAdValue = CommMotDrv.ReqSet.Rx.Byte15.IPMAdValue;
	
	//压机实际运行频率（整数部分）
	CompFreqReal = CommMotDrv.ReqSet.Rx.Byte16.CompFreqReal;

	//压机实际运行频率（小数部分）
	CompFreqRealDot = CommMotDrv.ReqSet.Rx.Byte17.CompFreqRealDot;		

}
/****************************************************************************************************
Function Name       :void    CommMotDrv_Con(void)
Description         :主控芯片与电机驱动芯片信息通信处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    CommMotDrv_Con(void)
{	
	//TX
	if (CommMotDrv.u8_TXCommand == C_COMMMOTDRV_CMD_BASERUN)		   //基本运行指令
	{
		CommMotDrv.TxBuf.u8_Byte5  = CommMotDrv.BaseRun.Tx.Byte5.Byte;  
		CommMotDrv.TxBuf.u8_Byte6  = CommMotDrv.BaseRun.Tx.Byte6.Byte;  
		CommMotDrv.TxBuf.u8_Byte7  = CommMotDrv.BaseRun.Tx.Byte7.Byte;  
		CommMotDrv.TxBuf.u8_Byte8  = CommMotDrv.BaseRun.Tx.Byte8.Byte;  
		CommMotDrv.TxBuf.u8_Byte9  = CommMotDrv.BaseRun.Tx.Byte9.Byte;  
		CommMotDrv.TxBuf.u8_Byte10 = CommMotDrv.BaseRun.Tx.Byte10.Byte; 
		CommMotDrv.TxBuf.u8_Byte11 = CommMotDrv.BaseRun.Tx.Byte11.Byte;	
		CommMotDrv.TxBuf.u8_Byte12 = CommMotDrv.BaseRun.Tx.Byte12.Byte; 
		CommMotDrv.TxBuf.u8_Byte13 = CommMotDrv.BaseRun.Tx.Byte13.Byte; 
		CommMotDrv.TxBuf.u8_Byte14 = CommMotDrv.BaseRun.Tx.Byte14.Byte; 
		CommMotDrv.TxBuf.u8_Byte15 = CommMotDrv.BaseRun.Tx.Byte15.Byte; 
		CommMotDrv.TxBuf.u8_Byte16 = CommMotDrv.BaseRun.Tx.Byte16.Byte; 
		CommMotDrv.TxBuf.u8_Byte17 = CommMotDrv.BaseRun.Tx.Byte17.Byte; 		
	}
	else														   		//查询、设置命令
	{
		CommMotDrv.TxBuf.u8_Byte5  = CommMotDrv.ReqSet.Tx.Byte5.Byte;
		CommMotDrv.TxBuf.u8_Byte6  = CommMotDrv.ReqSet.Tx.Byte6.Byte;  
		CommMotDrv.TxBuf.u8_Byte7  = CommMotDrv.ReqSet.Tx.Byte7.Byte;  
		CommMotDrv.TxBuf.u8_Byte8  = CommMotDrv.ReqSet.Tx.Byte8.Byte;  
		CommMotDrv.TxBuf.u8_Byte9  = CommMotDrv.ReqSet.Tx.Byte9.Byte;  
		CommMotDrv.TxBuf.u8_Byte10 = CommMotDrv.ReqSet.Tx.Byte10.Byte; 
		CommMotDrv.TxBuf.u8_Byte11 = CommMotDrv.ReqSet.Tx.Byte11.Byte;	
		CommMotDrv.TxBuf.u8_Byte12 = 2;//CommMotDrv.ReqSet.Tx.Byte12.Byte; 
		CommMotDrv.TxBuf.u8_Byte13 = CommMotDrv.ReqSet.Tx.Byte13.Byte; 
		CommMotDrv.TxBuf.u8_Byte14 = CommMotDrv.ReqSet.Tx.Byte14.Byte; 
		CommMotDrv.TxBuf.u8_Byte15 = CommMotDrv.ReqSet.Tx.Byte15.Byte; 
		CommMotDrv.TxBuf.u8_Byte16 = CommMotDrv.ReqSet.Tx.Byte16.Byte; 
		CommMotDrv.TxBuf.u8_Byte17 = CommMotDrv.ReqSet.Tx.Byte17.Byte; 	
	}
	
	//RX
	if (CommMotDrv.u8_RXCommand == C_COMMMOTDRV_CMD_BASERUN)		   //基本运行指令
	{
		CommMotDrv.BaseRun.Rx.Byte5.Byte  = CommMotDrv.RxBuf.u8_Byte5; 
		CommMotDrv.BaseRun.Rx.Byte6.Byte  = CommMotDrv.RxBuf.u8_Byte6; 		
		CommMotDrv.BaseRun.Rx.Byte7.Byte  = CommMotDrv.RxBuf.u8_Byte7; 		
		CommMotDrv.BaseRun.Rx.Byte8.Byte  = CommMotDrv.RxBuf.u8_Byte8; 		
		CommMotDrv.BaseRun.Rx.Byte9.Byte  = CommMotDrv.RxBuf.u8_Byte9; 		
		CommMotDrv.BaseRun.Rx.Byte10.Byte = CommMotDrv.RxBuf.u8_Byte10;		
		CommMotDrv.BaseRun.Rx.Byte11.Byte = CommMotDrv.RxBuf.u8_Byte11;		
		CommMotDrv.BaseRun.Rx.Byte12.Byte = CommMotDrv.RxBuf.u8_Byte12;		
		CommMotDrv.BaseRun.Rx.Byte13.Byte = CommMotDrv.RxBuf.u8_Byte13;		
		CommMotDrv.BaseRun.Rx.Byte14.Byte = CommMotDrv.RxBuf.u8_Byte14;		
		CommMotDrv.BaseRun.Rx.Byte15.Byte = CommMotDrv.RxBuf.u8_Byte15;		
		CommMotDrv.BaseRun.Rx.Byte16.Byte = CommMotDrv.RxBuf.u8_Byte16;		
		CommMotDrv.BaseRun.Rx.Byte17.Byte = CommMotDrv.RxBuf.u8_Byte17;			
	}
	else															   //查询、设置命令
	{	
		CommMotDrv.ReqSet.Rx.Byte5.Byte  = CommMotDrv.RxBuf.u8_Byte5; 
		CommMotDrv.ReqSet.Rx.Byte6.Byte  = CommMotDrv.RxBuf.u8_Byte6; 		
		CommMotDrv.ReqSet.Rx.Byte7.Byte  = CommMotDrv.RxBuf.u8_Byte7; 		
		CommMotDrv.ReqSet.Rx.Byte8.Byte  = CommMotDrv.RxBuf.u8_Byte8; 		
		CommMotDrv.ReqSet.Rx.Byte9.Byte  = CommMotDrv.RxBuf.u8_Byte9; 		
		CommMotDrv.ReqSet.Rx.Byte10.Byte = CommMotDrv.RxBuf.u8_Byte10;		
		CommMotDrv.ReqSet.Rx.Byte11.Byte = CommMotDrv.RxBuf.u8_Byte11;		
		CommMotDrv.ReqSet.Rx.Byte12.Byte = CommMotDrv.RxBuf.u8_Byte12;		
		CommMotDrv.ReqSet.Rx.Byte13.Byte = CommMotDrv.RxBuf.u8_Byte13;		
		CommMotDrv.ReqSet.Rx.Byte14.Byte = CommMotDrv.RxBuf.u8_Byte14;		
		CommMotDrv.ReqSet.Rx.Byte15.Byte = CommMotDrv.RxBuf.u8_Byte15;		
		CommMotDrv.ReqSet.Rx.Byte16.Byte = CommMotDrv.RxBuf.u8_Byte16;		
		CommMotDrv.ReqSet.Rx.Byte17.Byte = CommMotDrv.RxBuf.u8_Byte17;	
	}
}
/****************************************************************************************************
Function Name       :void    CommMotDrv_Con(void)
Description         :主控芯片与电机驱动芯片通信
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    CommMotDrv_InfoCon(void)
{
	/*if (CommMotDrv.u8_TXCommand != C_COMMMOTDRV_CMD_REQSET)		//默认按正常运行指令
	{
		CommMotDrv.u8_TXCommand = C_COMMMOTDRV_CMD_BASERUN;		
	}
	*/

	if(Enum_LowPower != ENUM_LOWPOWER_GO) return;  //lcx add 防止商检报F0

	
	if(l_contData.cont_Enable == 1)
		CommMotDrv.u8_TXCommand = C_COMMMOTDRV_CMD_REQSET;
	else CommMotDrv.u8_TXCommand = C_COMMMOTDRV_CMD_BASERUN;
	
//	CommMotDrv_BaseRunTx();		//基本运行指令发送数据处理
//
//	CommMotDrv_ReqSetTx();		//查询设置指令发送数据处理
//
//	CommMotDrv_Con();			//主控芯片与电机驱动芯片信息通信处理
//	
//	CommMotDrv_BaseRunRx();		//基本运行指令接收数据处理	
//	
//	CommMotDrv_ReqSetRx();		//查询设置指令接收数据处理		
}
