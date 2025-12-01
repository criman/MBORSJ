/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: CmdOut.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/08/14
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_TX    CmdOutBak;

/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte5_Update(void)
Description         :第5字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte5_Update(void)
{
	//--------------------------------------------------------------------------------------------------//

	if (SystemMode.f_CECSync == 0)//((SystemMode.f_TempCEC == 0) || (SystemMode.f_TempCEC && (Fan.Indoor.u16_Count < (6000 + 6000))))	//首次10分钟(P40)10分钟关(P41)
	{
		if (Fan.ModeCECBak != ENUM_FANMODE_INIT)	  //达温停机后内风机有同步过低风显示的情况
		{
			Fan.Mode = Fan.ModeCECBak;
			Fan.ModeCECBak = ENUM_FANMODE_INIT;
		}
		
		if      (Fan.Mode == ENUM_FANMODE_HIGH)    CommDisp.Tx.Byte5.var.FanSpeed = ENUM_FANSPEED_HIGH;    //高风			
		else if (Fan.Mode == ENUM_FANMODE_MED)	   CommDisp.Tx.Byte5.var.FanSpeed = ENUM_FANSPEED_MED;     //中风
		else if (Fan.Mode == ENUM_FANMODE_LOW)	   CommDisp.Tx.Byte5.var.FanSpeed = ENUM_FANSPEED_LOW;     //低风
		else									   CommDisp.Tx.Byte5.var.FanSpeed = ENUM_FANSPEED_AUTO;    //自动风	
	}
	else
	{
		//达温时风机转速位依据显示风速档位
				
		if ((Fan.Indoor.Level == ENUM_FANLEVEL_HIGH_S) || (Fan.Indoor.Level == ENUM_FANLEVEL_HIGH))	//强力档/高档
		{
			CommDisp.Tx.Byte5.var.FanSpeed = ENUM_FANSPEED_HIGH;    //高风		
		}
		else if (Fan.Indoor.Level == ENUM_FANLEVEL_MED)    //风速中档
		{
			CommDisp.Tx.Byte5.var.FanSpeed = ENUM_FANSPEED_MED;     //中风
		}
		else if ((Fan.Indoor.Level == ENUM_FANLEVEL_LOW) || (Fan.Indoor.Level == ENUM_FANLEVEL_LOW_S))	//风速低档/风速微风档
		{
			CommDisp.Tx.Byte5.var.FanSpeed = ENUM_FANSPEED_LOW;     //低风
		}
		
		if (SystemMode.f_TempCEC == 0)	//达温取消同步显示也取消
		{
			SystemMode.f_CECSync = 0;
		}
	}
	
	//--------------------------------------------------------------------------------------------------//
		
	if (Fan.f_SweepLR)		CommDisp.Tx.Byte5.var.SwLRType = ENUM_SWLRTYPE_ON;		//左右摇头打开	
	else					CommDisp.Tx.Byte5.var.SwLRType = ENUM_SWLRTYPE_OFF;		//左右摇头关闭
 	
	//--------------------------------------------------------------------------------------------------//
	
	if      (System.Mode == ENUM_SYSMODE_HUM)		CommDisp.Tx.Byte5.var.Mode = ENUM_MODE_HUMI;		//除湿
	else if (System.Mode == ENUM_SYSMODE_FAN)		CommDisp.Tx.Byte5.var.Mode = ENUM_MODE_FAN; 		//送风
	else if (System.Mode == ENUM_SYSMODE_INTE)		CommDisp.Tx.Byte5.var.Mode = ENUM_MODE_INTE;		//智能
	else if (System.Mode == ENUM_SYSMODE_HEAT)		CommDisp.Tx.Byte5.var.Mode = ENUM_MODE_HEAT;		//制热
	else											CommDisp.Tx.Byte5.var.Mode = ENUM_MODE_COLD;		//制冷

	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte5.Byte != CommDisp.Tx.Byte5.Byte)
	{
		CmdOutBak.Byte5.Byte = CommDisp.Tx.Byte5.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte6_Update(void)
Description         :第6字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte6_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	if (System.Enum_Status == ENUM_STATUS_SELCHK)	CommDisp.Tx.Byte6.var.SelChk = Enum_ENABLE;
	else											CommDisp.Tx.Byte6.var.SelChk = Enum_DISABLE;

	//--------------------------------------------------------------------------------------------------//
	
	if (System.Enum_Status == ENUM_STATUS_BUSSCHK)	CommDisp.Tx.Byte6.var.BussChk = Enum_ENABLE;
	else											CommDisp.Tx.Byte6.var.BussChk = Enum_DISABLE;
	
	//--------------------------------------------------------------------------------------------------//	

	CommDisp.Tx.Byte6.var.USBModule = Enum_DISABLE;

	//--------------------------------------------------------------------------------------------------//
	
	if (Tempr.f_TempUnit == 0)		CommDisp.Tx.Byte6.var.TempUnit = ENUM_TEMPC;
	else							CommDisp.Tx.Byte6.var.TempUnit = ENUM_TEMPF;
	
	//--------------------------------------------------------------------------------------------------//	

	if (SystemMode.f_Sleep)			
	{	
		CommDisp.Tx.Byte6.var.Sleep = Enum_ENABLE;
	}
	else							
	{
		CommDisp.Tx.Byte6.var.Sleep = Enum_DISABLE;
	}
	
	//--------------------------------------------------------------------------------------------------//	

	if (Timer.f_OffEn || Timer.f_OnEn)			CommDisp.Tx.Byte6.var.Timer = Enum_ENABLE;
	else										CommDisp.Tx.Byte6.var.Timer = Enum_DISABLE;
	
	//--------------------------------------------------------------------------------------------------//	
		
	//蜂鸣(实测主动发1也不会鸣叫)
	 
	
	//--------------------------------------------------------------------------------------------------//	

	if ((System.Enum_Status == ENUM_STATUS_INIT) || (System.Enum_Status == ENUM_STATUS_OFF))
	{
		CommDisp.Tx.Byte6.var.PowerOnOff = Enum_DISABLE;
	}
	else
	{
		CommDisp.Tx.Byte6.var.PowerOnOff = Enum_ENABLE;
	}

	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte6.Byte != CommDisp.Tx.Byte6.Byte)
	{
		CmdOutBak.Byte6.Byte = CommDisp.Tx.Byte6.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte7_Update(void)
Description         :第7字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte7_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	//检查设定值是否在合理范围内
	if ((Tempr.u8_TempCSet < 13) || (Tempr.u8_TempCSet > 32))	//非法范围
	{
		if (SystemMode.f_Heat == 1)	//制热
		{
			Tempr.u8_TempCSet = C_REMEMBER_MODEFUNC_HEATCSET_DFT;
		}
		else	//制冷
		{
			Tempr.u8_TempCSet = C_REMEMBER_MODEFUNC_COLDCSET_DFT;
		}
	}	
	
	//--------------------------------------------------------------------------------------------------//
			
	if (WiFi.Enum_Status == ENUM_TWIFISTATUS_AP)
	{
		if (((Tempr.u8_TempFSet == 88) || (Tempr.u8_TempFSet == 89)) && Tempr.f_TempUnit && (Tempr.f_TempUnitBak != Tempr.f_TempUnit))	//显示板程序问题修正89F对应32℃	
		{					
			CommDisp.Tx.Byte7.TempCSet = 31;	//欺骗显示板不让其蜂鸣(显示板程序89F对应31C)
			
			if (Tempr.u8_TempFSet == 88)
			{
				Tempr.u8_TempCSet = 31;
			}

		}
		else
		{		
			if (SystemMode.f_Sleep == 0)
			{
				CommDisp.Tx.Byte7.TempCSet = Tempr.u8_TempCSet;
			}
			else	//睡眠模式下显示板温度设定值不会变
			{
				CommDisp.Tx.Byte7.TempCSet = Tempr.u8_TempCSetSleep;
			}
			
			
		}
		Tempr.f_TempUnitBak = Tempr.f_TempUnit;
	}
	else
	{
		if (SystemMode.f_Sleep == 0)
		{
			CommDisp.Tx.Byte7.TempCSet = Tempr.u8_TempCSet;
		}
		else	//睡眠模式下显示板温度设定值不会变
		{
			CommDisp.Tx.Byte7.TempCSet = Tempr.u8_TempCSetSleep;
		}	
	}
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte7.Byte != CommDisp.Tx.Byte7.Byte)
	{
		CmdOutBak.Byte7.Byte = CommDisp.Tx.Byte7.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte8_Update(void)
Description         :第8字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte8_Update(void)
{
	CommDisp.Tx.Byte8.TimerPer10Mins = (Timer.u16_Minute+9)/10;
	
	if (CmdOutBak.Byte8.Byte != CommDisp.Tx.Byte8.Byte)
	{
		CmdOutBak.Byte8.Byte = CommDisp.Tx.Byte8.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte9_Update(void)
Description         :第9字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte9_Update(void)
{
	//--------------------------------------------------------------------------------------------------//

	CommDisp.Tx.Byte9.var.ColdType = ENUM_COLDHEAT;		//冷暖机型
	
	//除湿机不适用按默认值	
//	CommDisp.Tx.Byte9.var.CEC = ENUM_DISABLE;
//	CommDisp.Tx.Byte9.var.FilterTime = ENUM_DISABLE;
//	CommDisp.Tx.Byte9.var.Lock = ENUM_DISABLE;
//	
//	CommDisp.Tx.Byte9.var.AtmosLight = ENUM_DISABLE;
//	
//	//--------------------------------------------------------------------------------------------------//
	
	if ((Comp.f_DrvOn == ON) && (Comp.u8_RealHZ > 0))    CommDisp.Tx.Byte9.var.Comp = Enum_ENABLE;
	else					   CommDisp.Tx.Byte9.var.Comp = Enum_DISABLE;
	
//	//--------------------------------------------------------------------------------------------------//
//	
//	if (Pump.f_TypeOn == CF_ENABLE)
//	{
//		if (Pump.f_FuncOn == ON)    	CommDisp.Tx.Byte9.var.Pump = ENUM_ENABLE;
//		else							CommDisp.Tx.Byte9.var.Pump = ENUM_DISABLE;
//		
//		CommDisp.Tx.Byte9.var.Anion = ENUM_DISABLE;
//	}
//	else
//	{
//		if (Anion.f_FuncOn == ON)		CommDisp.Tx.Byte9.var.Anion = ENUM_ENABLE;
//		else							CommDisp.Tx.Byte9.var.Anion = ENUM_DISABLE;
//			
//		CommDisp.Tx.Byte9.var.Pump = ENUM_DISABLE;
//	}
	
	//--------------------------------------------------------------------------------------------------//

	
	if (CmdOutBak.Byte9.Byte != CommDisp.Tx.Byte9.Byte)
	{
		CmdOutBak.Byte9.Byte = CommDisp.Tx.Byte9.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte10_Update(void)
Description         :第10字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte10_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte10.Byte = 0;	//wifi功能暂未开发先发0
	
	if (System.u8_PowerOn_Count >= 85)	//上电8500ms后
	{
		if (WiFi.Enum_Status == ENUM_TWIFISTATUS_AP)
		{
			CommDisp.Tx.Byte10.var.TipsAP = Enum_ENABLE;				//AP提示		(1:可远程控制)
		}
		else if (WiFi.Enum_Status == ENUM_TWIFISTATUS_SA)
		{
			CommDisp.Tx.Byte10.var.TipsSA = Enum_ENABLE;				//SA提示		(1:登录成功)
		}	
		else if (WiFi.Enum_Status == ENUM_TWIFISTATUS_PP)
		{
			CommDisp.Tx.Byte10.var.TipsPP = Enum_ENABLE;				//PP提示		(1:正在登录)
		}
		else if (WiFi.Enum_Status == ENUM_TWIFISTATUS_CONFIG)
		{
			CommDisp.Tx.Byte10.var.Conifg = Enum_ENABLE;				//配置			(1:配置)
		}
	}
	
//	CommDisp.Tx.Byte10.var.BusiChk				//商检			(1:通过)
//	CommDisp.Tx.Byte10.var.UartErr				//串口通讯故障	(1:故障)
//	CommDisp.Tx.Byte10.var.DisConnect			//掉线			(1:掉线)
	
	if (WiFi.f_Reset)
	{
		CommDisp.Tx.Byte10.var.Reset = Enum_ENABLE;				//复位			(1:复位)	
	}
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte10.Byte != CommDisp.Tx.Byte10.Byte)
	{
		CmdOutBak.Byte10.Byte = CommDisp.Tx.Byte10.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte11_Update(void)
Description         :第11字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte11_Update(void)
{
	//--------------------------------------------------------------------------------------------------//

	if (System.u8_PowerOn_Count >= 10)	//上电1s后才判断
	{
		if (WaterBox.f_Full)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_E3_WATERFULL;		//水满保护
		}
		else if (WaterBox.f_WatLow)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_E6_TANKP;			//水箱保护
		}		
		else if (System.f_VoltLowPro)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F5_VOLTLOWPRO;	//欠压保护
		}
		else if (System.f_CurrentProtect)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F4_OVCURRPRO;		//过电流保护
		}
		//else if (Fan.Indoor.f_Error)
		else if (Fan.Indoor.u8_ErrRunTimes >= C_INFAN_ERRORRUN_TIMES)   //LCX ADD 20240622
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_ED_FANINERR;		//室内风机故障
		}
		else if (Fan.Outdoor.f_Error)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_EE_FANOUTERR;		//室外风机故障
		}
//		else if (F_uart4_CommErr)
//		{
//			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_E8_COMMDISP;		//通讯故障
//		}		
		else if (F_uart0_CommErr || System.f_InOutCommErr)
		{		
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_EF_INOUTCOMMERR;	//室内外通讯故障
		}		
		else if (Comp.f_IPMErr)//变频驱动
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F0_COMPIPMERR;	//模块故障
		}
		else if (Comp.f_StartErr)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F7_COMPSTARTERR;	//驱动保护
		}
		else if (Protect.f_WaterFlow)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_E4_PUMP;		//水流开关故障（显示E4）
		}
		else if (Protect.f_HighWaterLevelErr)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F6_HIGHWATERLEVELERR;		//高水位开关故障（显示F6）
		}
		else if (Comp.f_IPMPro)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F6_HIGHWATERLEVELERR;	//模块保护（复用F6代码，但高水位故障优先级更高）
		}
		else if (System.f_InEEpromErr)
		{	
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F2_INEEPROMERR; 	//室内EEPROM故障
		}
		else if (System.f_OutEEpromErr)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F3_OUTEEPROMERR;  //室外EEPROM故障
		}
		//暂无待续---电流传感器故障
		else if (Protect.f_Tp)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_FA_TPPRO;			//排气温度过高保护
		}
		else if (Protect.f_T2Cold)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_FB_T2COLD;		//制冷T2温度过低保护
		}
		else if (Protect.f_MidWaterLevelErr)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_FD_MIDWATERLEVELERR;		//中水位开关故障（显示Fb）
		}
		else if (Protect.f_LowWaterLevelErr)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_FE_LOWWATERLEVELERR;		//低水位开关故障（显示FL）
		}
		else if (Protect.f_T3Cold)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F9_T3COLD;		//制冷T3温度过高保护
		}
		else if ((Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO) || (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO1) ||
				 (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_PRO) || (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_PRO1) || 
				 (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_STOP))
				//把ENUM_TEMPT4COOLZONE_STOP（实际也停机）纳入F8报警。		lcx add 20240620
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_F8_T4PRO;			//室外温度过高、过低保护
		}
		else if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_PRO)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_FC_T2HEAT;		//制热防过热保护
		}
		else if (T2.f_Error)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_E2_TEMPCOIL;		//盘管传感器T2故障
		}
		else if (T3.f_Error)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_EB_TEMPCOIL2;		//盘管传感器T3故障
		}		
		else if (T1.f_Error)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_E1_TEMPROOM;		//室内温度传感器故障
		}
		else if (T4.f_Error)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_EA_TEMPOUTDOOR;		//室外温度传感器故障
		}	
		else if (Tp.f_Error)
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_E7_TEMPEXHAUST;	//排气传感器TP故障
		}		
		else
		{
			CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_NULL;				//无故障
		}
	}
	else
	{
		CommDisp.Tx.Byte11.ErrInfo = ENUM_ERRINFO_NULL;				//无故障
	}
		
//	if (CommDisp.Tx.Byte11.ErrInfo != ENUM_ERRINFO_NULL)
//	{
//		SystemMode.f_TempCEC = 0;				//故障保护出现,达温标志清除
//	}
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte11.Byte != CommDisp.Tx.Byte11.Byte)
	{
		CmdOutBak.Byte11.Byte = CommDisp.Tx.Byte11.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte12_Update(void)
Description         :第12字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte12_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte12.TempCRoomPlus20 = T1.s8_Value + 20;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte12.Byte != CommDisp.Tx.Byte12.Byte)
	{
		CmdOutBak.Byte12.Byte = CommDisp.Tx.Byte12.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte13_Update(void)
Description         :第13字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte13_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte13.TempCCoilPlus20 = T2.s8_Value + 20;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte13.Byte != CommDisp.Tx.Byte13.Byte)
	{
		CmdOutBak.Byte13.Byte = CommDisp.Tx.Byte13.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte14_Update(void)
Description         :第14字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte14_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte14.Huminity = 50;	//没有湿度检测按50%
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte14.Byte != CommDisp.Tx.Byte14.Byte)
	{
		CmdOutBak.Byte14.Byte = CommDisp.Tx.Byte14.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte15_Update(void)
Description         :第15字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte15_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	//检查设定值是否在合理范围内
	if ((Tempr.u8_TempFSet < 55) || (Tempr.u8_TempFSet > 90))
	{
		if (SystemMode.f_Heat == 1)	//制热
		{
			Tempr.u8_TempFSet = C_REMEMBER_MODEFUNC_HEATFSET_DFT;
		}
		else	//制冷
		{
			Tempr.u8_TempFSet = C_REMEMBER_MODEFUNC_COLDFSET_DFT;
		}
	}		
	
	//--------------------------------------------------------------------------------------------------//
	
	if (SystemMode.f_Sleep == 0)
	{
		CommDisp.Tx.Byte15.TempFSet = Tempr.u8_TempFSet;	
	}
	else	//睡眠模式下显示板温度设定值不会变
	{
		CommDisp.Tx.Byte15.TempFSet = Tempr.u8_TempFSetSleep;
	}
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte15.Byte != CommDisp.Tx.Byte15.Byte)
	{
		CmdOutBak.Byte15.Byte = CommDisp.Tx.Byte15.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte16_Update(void)
Description         :第16字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte16_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte16.Version = C_FUNC_SOFT_VERSION_A;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte16.Byte != CommDisp.Tx.Byte16.Byte)
	{
		CmdOutBak.Byte16.Byte = CommDisp.Tx.Byte16.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte17_Update(void)
Description         :第17字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte17_Update(void)
{

	//--------------------------------------------------------------------------------------------------//
	
//	if (Protect.FDP.f_Disable == CF_DISABLE)	CommDisp.Tx.Byte17.var.FDP = ENUM_ENABLE;
//	else										CommDisp.Tx.Byte17.var.FDP = ENUM_DISABLE;
//	
	//--------------------------------------------------------------------------------------------------//
	//常闭型
	if (WaterBox.f_SW1_Full)	CommDisp.Tx.Byte17.var.WaterSW1 = Enum_ENABLE;	//断开
	else						CommDisp.Tx.Byte17.var.WaterSW1 = Enum_DISABLE;	//闭合

	//--------------------------------------------------------------------------------------------------//
	//常闭型
	if (WaterBox.f_SW2_Full)	CommDisp.Tx.Byte17.var.WaterSW2 = Enum_ENABLE;	//断开
	else						CommDisp.Tx.Byte17.var.WaterSW2 = Enum_DISABLE;	//闭合

//	//--------------------------------------------------------------------------------------------------//
//	
//	//远程定时
//	
//	//--------------------------------------------------------------------------------------------------//
		
	if (WiFi.f_FuncOn == CF_ENABLE)				CommDisp.Tx.Byte17.var.WifiPower = Enum_ENABLE;
	else										CommDisp.Tx.Byte17.var.WifiPower = Enum_DISABLE;
	
//	//--------------------------------------------------------------------------------------------------//

//	//APP按键
//	
//	//--------------------------------------------------------------------------------------------------//

//	if (F_protect_anticold == CF_ENABLE)		CommDisp.Tx.Byte17.var.AntiColdP = ENUM_ENABLE;
//	else										CommDisp.Tx.Byte17.var.AntiColdP = ENUM_DISABLE;

//	//--------------------------------------------------------------------------------------------------//
//	
//	CommDisp.Tx.Byte17.var.Defrost = ENUM_DISABLE;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte17.Byte != CommDisp.Tx.Byte17.Byte)
	{
		CmdOutBak.Byte17.Byte = CommDisp.Tx.Byte17.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte18_Update(void)
Description         :第18字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte18_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
//	if (WorkMode.Mode == ENUM_WORKMODE_FORCE)	CommDisp.Tx.Byte18.var.ForceMode = ENUM_ENABLE;
//	else										CommDisp.Tx.Byte18.var.ForceMode = ENUM_DISABLE;

	//lcx 20240429 add
	if (SystemMode.f_Force == 1)				CommDisp.Tx.Byte18.var.ForceMode = Enum_ENABLE;
	else										CommDisp.Tx.Byte18.var.ForceMode = Enum_DISABLE;


//	
//	//--------------------------------------------------------------------------------------------------//
//	
//	CommDisp.Tx.Byte18.var.SweepUD = ENUM_DISABLE;
//	
//	//--------------------------------------------------------------------------------------------------//
	
//	if (SystemMode.f_Sleep == 1)		CommDisp.Tx.Byte18.var.Silence = ENUM_ENABLE;
//	else								CommDisp.Tx.Byte18.var.Silence = ENUM_DISABLE;

//	//--------------------------------------------------------------------------------------------------//

	CommDisp.Tx.Byte18.var.WifiFunc = Enum_ENABLE;		//有wifi功能
	
//	//--------------------------------------------------------------------------------------------------//

	if (UVC.f_FuncOn == ON)    	CommDisp.Tx.Byte18.var.UVC = Enum_ENABLE;
	else					  	CommDisp.Tx.Byte18.var.UVC = Enum_DISABLE;

//	//--------------------------------------------------------------------------------------------------//

//	CommDisp.Tx.Byte18.var.HighTempP = ENUM_DISABLE;	//默认关闭高温保护

//	//--------------------------------------------------------------------------------------------------//
//	
//	if (Pump.f_TypeOn == CF_ENABLE)		CommDisp.Tx.Byte18.var.LoadType = ENUM_LOADTYPE_PUMP;
//	else								CommDisp.Tx.Byte18.var.LoadType = ENUM_LOADTYPE_ANION;

//	//--------------------------------------------------------------------------------------------------//

	if (Comp.u16_RestartDelay > 0)    CommDisp.Tx.Byte18.var.Comp3Min = Enum_ENABLE;
	else							  CommDisp.Tx.Byte18.var.Comp3Min = Enum_DISABLE;

	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte18.Byte != CommDisp.Tx.Byte18.Byte)
	{
		CmdOutBak.Byte18.Byte = CommDisp.Tx.Byte18.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte19_Update(void)
Description         :第19字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte19_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte19.TempCExhaustPlus20 = Tp.s8_Value + 20;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte19.Byte != CommDisp.Tx.Byte19.Byte)
	{
		CmdOutBak.Byte19.Byte = CommDisp.Tx.Byte19.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte20_Update(void)
Description         :第20字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte20_Update(void)
{
	U32    temp;
	
	//--------------------------------------------------------------------------------------------------//
	
	temp = Comp.u32_RunContCount/600; 				//连续运行分钟
	if (temp > 0xFFFF)	temp = 0xFFFF;
	temp >>= 8;										//取高8位
	CommDisp.Tx.Byte20.CompRunContTimeH = temp;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte20.Byte != CommDisp.Tx.Byte20.Byte)
	{
		CmdOutBak.Byte20.Byte = CommDisp.Tx.Byte20.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte21_Update(void)
Description         :第21字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte21_Update(void)
{
	U32    temp;
	
	//--------------------------------------------------------------------------------------------------//
	
	temp = Comp.u32_RunContCount/600; 				//连续运行分钟
	if (temp > 0xFFFF)	temp = 0xFFFF;
	temp &= 0xFF;									//取低8位
	CommDisp.Tx.Byte21.CompRunContTimeL = temp;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte21.Byte != CommDisp.Tx.Byte21.Byte)
	{
		CmdOutBak.Byte21.Byte = CommDisp.Tx.Byte21.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte22_Update(void)
Description         :第22字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte22_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte22.TempCRoomOutPlus20 = T4.s8_Value + 20;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte22.Byte != CommDisp.Tx.Byte22.Byte)
	{
		CmdOutBak.Byte22.Byte = CommDisp.Tx.Byte22.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte23_Update(void)
Description         :第23字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte23_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte23.TempCCoilOutPlus20 = T3.s8_Value + 20;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte23.Byte != CommDisp.Tx.Byte23.Byte)
	{
		CmdOutBak.Byte23.Byte = CommDisp.Tx.Byte23.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte24_Update(void)
Description         :第24字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte24_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte24.InDoorFanSpeedDiv10 = Fan.Indoor.u16_RealRPM/10;
	
	//--------------------------------------------------------------------------------------------------//
	
	
	if (CmdOutBak.Byte24.Byte != CommDisp.Tx.Byte24.Byte)
	{
		CmdOutBak.Byte24.Byte = CommDisp.Tx.Byte24.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte25_Update(void)
Description         :第25字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte25_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte25.OutDoorFanSpeedDiv10 = Fan.Outdoor.u16_RealRPM/10;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte25.Byte != CommDisp.Tx.Byte25.Byte)
	{
		CmdOutBak.Byte25.Byte = CommDisp.Tx.Byte25.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte26_Update(void)
Description         :第26字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte26_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
	CommDisp.Tx.Byte26.CompRunFreq = Comp.u8_RealHZ;
	
	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte26.Byte != CommDisp.Tx.Byte26.Byte)
	{
		CmdOutBak.Byte26.Byte = CommDisp.Tx.Byte26.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte27_Update(void)
Description         :第27字节信息发送处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte27_Update(void)
{
	//--------------------------------------------------------------------------------------------------//
	
//	CommDisp.Tx.Byte27.var.DeWatering = ENUM_DISABLE;
//	
//	//--------------------------------------------------------------------------------------------------//

//	CommDisp.Tx.Byte27.var.DispStatus = ENUM_DISPSTATUS_NORMAL;		//显示正常状态
//	
//	//--------------------------------------------------------------------------------------------------//

//	CommDisp.Tx.Byte27.var.ECO = ENUM_DISABLE;

//	//--------------------------------------------------------------------------------------------------//

//	CommDisp.Tx.Byte27.var.Lighting = ENUM_DISABLE;

//	//--------------------------------------------------------------------------------------------------//

	if (Fan.f_DeMold)    CommDisp.Tx.Byte27.var.DeMold = Enum_ENABLE;
	else				 CommDisp.Tx.Byte27.var.DeMold = Enum_DISABLE;

	//--------------------------------------------------------------------------------------------------//
	
	if (CmdOutBak.Byte27.Byte != CommDisp.Tx.Byte27.Byte)
	{
		CmdOutBak.Byte27.Byte = CommDisp.Tx.Byte27.Byte;
		CommDisp.f_Ack_InfoChg = CF_ENABLE;	//有更新
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoardCommandUpdate(void)
Description         :更新信息发送给显示板
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoardCommandUpdate(void)
{
	
	DisplayBoard_Byte5_Update();		//第5字节信息处理	
	
	DisplayBoard_Byte6_Update();		//第6字节信息处理	
	
	DisplayBoard_Byte7_Update();		//第7字节信息处理	
	
	DisplayBoard_Byte8_Update();		//第8字节信息处理	

	DisplayBoard_Byte9_Update();		//第9字节信息处理	
	
	DisplayBoard_Byte10_Update();		//第10字节信息处理	
	
	DisplayBoard_Byte11_Update();		//第11字节信息处理	
	
	DisplayBoard_Byte12_Update();		//第12字节信息处理	

	DisplayBoard_Byte13_Update();		//第13字节信息处理	
	
	DisplayBoard_Byte14_Update();		//第14字节信息处理	
	
	DisplayBoard_Byte15_Update();		//第15字节信息处理	
	
	DisplayBoard_Byte16_Update();		//第16字节信息处理	
	
	DisplayBoard_Byte17_Update();		//第17字节信息处理	
	
	DisplayBoard_Byte18_Update();		//第18字节信息处理	

	DisplayBoard_Byte19_Update();		//第19字节信息处理	

	DisplayBoard_Byte20_Update();		//第20字节信息处理	
	
	DisplayBoard_Byte21_Update();		//第21字节信息处理	
	
	DisplayBoard_Byte22_Update();		//第22字节信息处理	

	DisplayBoard_Byte23_Update();		//第23字节信息处理	
	
	DisplayBoard_Byte24_Update();		//第24字节信息处理	
	
	DisplayBoard_Byte25_Update();		//第25字节信息处理	
	
	DisplayBoard_Byte26_Update();		//第26字节信息处理	
	
	DisplayBoard_Byte27_Update();		//第27字节信息处理	
	

	//1.主机发01,从机回01,表示无设定,主机继续发01;
	//2.主机发01,从机回02,表示有设定,主机解析设定命令,然后主机发02,从机收到后回01,主机继续发01;
	//3.如果主机发02后从机没有回,主机继续发02;
	//4.如果主机发02后从机回的是02,表示有设定,主机解析设定命令,然后主机发02;
	//5.如果主机发02后从机回的不是01也不是02而是其他值,但数据校验正确认为从机已处理,主机继续发01;
	

	
	if (CommDisp.f_Ack == CF_DISABLE)
	{		
		if (CommDisp.f_Ack_InfoChg || CommDisp.f_Ack_RecChg)	//3.	//2.
		{
			CommDisp.f_Ack = CF_ENABLE;
			CommDisp.u8_AckDelay = 200;
		}
	}
	else
	{
		if ((CommDisp.Rx.Byte4.var.DataType == ENUM_DATATYPE_COMMAND_ENABLE) || (CommDisp.Rx.Byte4.var.DataType != ENUM_DATATYPE_COMMAND_DISABLE))
		{
			if 		(CommDisp.f_Ack_InfoChg)		CommDisp.f_Ack_InfoChg = CF_DISABLE;
			else if (CommDisp.f_Ack_RecChg)			CommDisp.f_Ack_RecChg = CF_DISABLE;			
		}
		else
		{
			if (CommDisp.u8_AckDelay == 0)
			{
				CommDisp.f_Ack_InfoChg = CF_DISABLE;
				CommDisp.f_Ack_RecChg = CF_DISABLE;					
				CommDisp.f_Ack = CF_DISABLE;
				
			}
			else
			{
				CommDisp.u8_AckDelay -= 1;
			}
		}		
	}	
	
	if (CommDisp.f_Ack == CF_ENABLE)
	{
		CommDisp.Tx.Byte4.var.DataType = ENUM_DATATYPE_COMMAND_ENABLE;
	}
	else
	{
		CommDisp.Tx.Byte4.var.DataType = ENUM_DATATYPE_COMMAND_DISABLE;	
	}	
	
	CommDisp.Tx.Byte4.var.MachineType = ENUM_MACHINETYPE_YDKT;	//固定机型：移动空调
	
	CmdOutBak.Byte4.Byte = CommDisp.Tx.Byte4.Byte;
}
