/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: CmdIn.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/08/14
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_RX    CmdInBak;

/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte5_Con(void)
Description         :第5字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte5_Con(void)
{
	if (CmdInBak.Byte5.Byte != CommDisp.Rx.Byte5.Byte)						//第5字节发生变化
	{
		if (CmdInBak.Byte5.var.FanSpeed != CommDisp.Rx.Byte5.var.FanSpeed)	//风速模式发送变化
		{	
			switch (CommDisp.Rx.Byte5.var.FanSpeed)
			{
				case	ENUM_FANSPEED_AUTO	 : Fan.Mode = ENUM_FANMODE_AUTO; break;			//自动风
				case	ENUM_FANSPEED_LOW    : Fan.Mode = ENUM_FANMODE_LOW;  break;			//低风
				case	ENUM_FANSPEED_MED    : Fan.Mode = ENUM_FANMODE_MED;  break;			//中风
				case	ENUM_FANSPEED_HIGH   : Fan.Mode = ENUM_FANMODE_HIGH; break;			//高风
				case	ENUM_FANSPEED_SILENCE: Fan.Mode = ENUM_FANMODE_LOW;  break;			//静音	

				default: break;
			}
			
			//add code...//风速模式变化相关参数处理
			SystemMode.f_TempCEC = 0;					//操作风速,达温标志清除
			SystemMode.f_Sleep = 0;						//操作风速,退出睡眠
			Fan.u2_AutoInitFdCount = 0;
			SystemMode.f_Force = 0;//强力模式关闭
		}
		
		if (CmdInBak.Byte5.var.SwLRType != CommDisp.Rx.Byte5.var.SwLRType)
		{
			if (CommDisp.Rx.Byte6.var.BussChk == ENUM_ENABLE)		//进入商检
			{			
				Fan.f_SweepLRChkBak = Fan.f_SweepLR;				//进入商检前记录摇头开关状态
			}
			
			if (CommDisp.Rx.Byte5.var.SwLRType == ENUM_ENABLE)    Fan.f_SweepLR = 1;		//左右摇头工作
			else												  Fan.f_SweepLR = 0;		//左右摇头停止工作
		
			//add code...//摇头状态变化相关参数处理
			//lcx add 20240622定时键、摆风键和数显按键，不退出强力
			//SystemMode.f_Force = 0;//强力模式关闭  
		}
		
		if (CmdInBak.Byte5.var.Mode != CommDisp.Rx.Byte5.var.Mode)
		{
			if      (CommDisp.Rx.Byte5.var.Mode == ENUM_MODE_HEAT)			System.Mode = ENUM_SYSMODE_HEAT;		//制热
			else if (CommDisp.Rx.Byte5.var.Mode == ENUM_MODE_HUMI)     		System.Mode = ENUM_SYSMODE_HUM;			//除湿
			else if (CommDisp.Rx.Byte5.var.Mode == ENUM_MODE_FAN)	        System.Mode = ENUM_SYSMODE_FAN;  		//送风
			else if (CommDisp.Rx.Byte5.var.Mode == ENUM_MODE_INTE)      	System.Mode = ENUM_SYSMODE_INTE;        //智能 		
			else                                                   			System.Mode = ENUM_SYSMODE_COLD;		//制冷(默认)	
			
			//add code...//工作模式状态变化相关参数处理

			
			Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_INIT;		//操作模式,重新计算温差区域
			Tempr.T1TSDeltaZoneBak = ENUM_TEMPDELTAZONE_INIT;	//操作模式,重新计算温差区域
			
			//模式标志重新判定
			SystemMode.f_Cold = 0;		
			SystemMode.f_Heat = 0;
			SystemMode.f_Fan = 0;
			SystemMode.f_Auto = 0;
			
			SystemMode.f_TempCEC = 0;							//操作模式,达温标志清除			
			SystemMode.f_Sleep = 0;								//操作模式,退出睡眠
			SystemMode.f_Force = 0;//强力模式关闭

			SystemMode.f_ConTemp = 0; //lcx add 20240704 转换模式进去，要清除达温停机。重新计时进入条件。
			
			if (System.Mode == ENUM_SYSMODE_HUM)
			{
				//进入除湿模式计算设定温度:    ST = T1 - 2
				if (T1.s8_Value < 18)
				{				
					Tempr.u8_HumiCSet = 16;	//最低
				}
				else if (T1.s8_Value > 34)
				{
					Tempr.u8_HumiCSet = 32;	//最高
				}
				else
				{
					Tempr.u8_HumiCSet = T1.s8_Value - 2;
				}
			}
			else
			{
				Tempr.u8_HumiCSet = 24;	//默认
			}
		}
		
		CmdInBak.Byte5.Byte = CommDisp.Rx.Byte5.Byte;
	}	
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte6_Con(void)
Description         :第6字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte6_Con(void)
{
	if (CmdInBak.Byte6.Byte != CommDisp.Rx.Byte6.Byte)						//第6字节发生变化
	{
		if (CmdInBak.Byte6.var.SelChk != CommDisp.Rx.Byte6.var.SelChk)
		{
			if (CommDisp.Rx.Byte6.var.SelChk == ENUM_ENABLE)		//进入自检/厂测
			{
				
				if (CommDisp.Rx.Byte6.var.PowerOnOff == ENUM_ENABLE)	//主板自检
				{
//					F_func_selchk_disp = CF_DISABLE;
//					F_func_selchk_pow = CF_ENABLE;
				}
				else													//显示板自检
				{
//					F_func_selchk_disp = CF_ENABLE;
//					F_func_selchk_pow = CF_DISABLE;
				}
				
				System.Enum_Status = ENUM_STATUS_SELCHK;			//进入自检
				
			}
			else													//退出自检/厂测
			{
				if (System.Enum_Status == ENUM_STATUS_SELCHK)
				{
					System.Enum_Status = ENUM_STATUS_OFF;
				}
			}
			
			//add code...//状态变化相关参数处理
//			System.u8_SelChk_Step = 0;
//			System.u16_SelChk_Count = 0;
		}
		
		if (CmdInBak.Byte6.var.BussChk != CommDisp.Rx.Byte6.var.BussChk)
		{
			if (CommDisp.Rx.Byte6.var.BussChk == ENUM_ENABLE)		//进入商检
			{		
				System.Enum_Status = ENUM_STATUS_BUSSCHK;
				
				System.Mode = ENUM_SYSMODE_COLD;					//确保商检默认在制冷模式				
				CommDisp.Rx.Byte5.var.Mode = ENUM_MODE_COLD;		//制冷
				CommDisp.Tx.Byte5.var.Mode = ENUM_MODE_COLD;		//制冷
				
				Tempr.u8_TempCSet = 18;								//确保商检默认设定18℃
				CommDisp.Rx.Byte7.TempCSet = 18;					//设定温度值
				CommDisp.Tx.Byte7.TempCSet = 18;					//设定温度值
				
				Fan.Mode = ENUM_FANMODE_HIGH;						//确保商检默认高风
				CommDisp.Rx.Byte5.var.FanSpeed = ENUM_FANSPEED_HIGH;//高风
				CommDisp.Tx.Byte5.var.FanSpeed = ENUM_FANSPEED_HIGH;//高风
				
				Comp.u8_PowerOnDelay = 0;							//无需等待上电延迟
				Comp.u16_RestartDelay = 50;							//无3分钟保护
			}
			else													//退出商检
			{
				if (System.Enum_Status == ENUM_STATUS_BUSSCHK)
				{
					Fan.f_SweepLR = Fan.f_SweepLRChkBak;
					Fan.f_SweepLRChkBak = 0;
					CommDisp.Tx.Byte5.var.SwLRType = (ENUM_SWLRTYPE)Fan.f_SweepLR;
					CommDisp.Rx.Byte5.var.SwLRType = (ENUM_SWLRTYPE)Fan.f_SweepLR;
					if (Fan.f_SweepLR == 0)	//原来状态是没有开启摇头需恢复到原来默认打开角度
					{
						StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ON;
						Swing.u16_anglebak = C_STEPMOTOR_ANGLE_DEFAULT;
					}
								
					UVC.f_FuncOn = UVC.f_FuncOnBak;
					UVC.f_FuncOnBak = 0;
					CommDisp.Tx.Byte18.var.UVC = (ENUM_FLAG)UVC.f_FuncOn;
					CommDisp.Rx.Byte11.var.UVC = (ENUM_FLAG)UVC.f_FuncOn;
								
					WiFi.f_FuncOn = WiFi.f_FuncOnBak;
					WiFi.f_FuncOnBak = 0;
					CommDisp.Tx.Byte17.var.WifiPower = (ENUM_FLAG)WiFi.f_FuncOn;
					CommDisp.Rx.Byte11.var.WifiPower = (ENUM_FLAG)WiFi.f_FuncOn;
					
					System.Enum_Status = ENUM_STATUS_ON;
				}					
			}
			
			//add code...//状态变化相关参数处理
			System.u16_BussChkCount = 0;
		}
		
		if (CmdInBak.Byte6.var.USBModule != CommDisp.Rx.Byte6.var.USBModule)
		{
			if (CommDisp.Rx.Byte6.var.USBModule == ENUM_ENABLE)		;//开启USB模块
			else													;//关闭USB模块
			
			//add code...//状态变化相关参数处理
		}	

		if (CmdInBak.Byte6.var.TempUnit != CommDisp.Rx.Byte6.var.TempUnit)
		{
			if (CommDisp.Rx.Byte6.var.TempUnit == ENUM_TEMPC)		Tempr.f_TempUnit = 0;//摄氏度
			else													Tempr.f_TempUnit = 1;//华氏度
			
			//add code...//状态变化相关参数处理
			//====================================================
			//lcx add 20240516 debug
			//上电25s内，连续收到10次，每次1.5s内，强制初始化内机EE。
			Remember.u8_InitCnt++;
			//====================================================
			//lcx add 20240622定时键、摆风键和数显按键，不退出强力
			//SystemMode.f_Force = 0;//强力模式关闭 	
		}

		if (CmdInBak.Byte6.var.Sleep != CommDisp.Rx.Byte6.var.Sleep)
		{
			if (CommDisp.Rx.Byte6.var.Sleep == ENUM_ENABLE)			
			{
				SystemMode.f_Sleep = 1;								//开启睡眠		
		
				//睡眠模式下记录
				Tempr.u8_TempCSetSleep = CommDisp.Rx.Byte7.Byte;		//设定温度值
				Tempr.u8_TempFSetSleep = CommDisp.Rx.Byte10.Byte;		//设定温度华氏								
			}
			else													
			{
				SystemMode.f_Sleep = 0;								//关闭睡眠
				
				//退出睡眠模式下记录退出
				Tempr.u8_TempCSet = Tempr.u8_TempCSetSleep;				
				Tempr.u8_TempFSet = Tempr.u8_TempFSetSleep;				
				Tempr.u8_TempCSetSleep = 0;
				Tempr.u8_TempFSetSleep = 0;				
			}
			
			//add code...//状态变化相关参数处理
			SystemMode.f_TempCEC = 0;				//操作睡眠,达温标志清除
			System.u32_SleepCount = 0;				//睡眠持续时间重新计时
			System.u32_SleepTimCount = 0;			//睡眠定时时间重新计时
			Fan.ModeBak = ENUM_FANMODE_INIT;		//风速重新判定
			SystemMode.f_Force = 0;//强力模式关闭
		}

		if (CmdInBak.Byte6.var.Timer != CommDisp.Rx.Byte6.var.Timer)
		{
			if (CommDisp.Rx.Byte6.var.Timer == ENUM_ENABLE)			
			{
				//开启定时
				if ((System.Enum_Status == ENUM_STATUS_INIT) || (System.Enum_Status == ENUM_STATUS_OFF))
				{
					Timer.f_OnEn = 1;
					Timer.f_OffEn = 0;
				}
				else
				{
					Timer.f_OnEn = 0;
					Timer.f_OffEn = 1;				
				}
			}
			else													
			{	
				//关闭定时
				Timer.f_OnEn = 0;
				Timer.f_OffEn = 0;
			}
			
			//add code...//状态变化相关参数处理
			//lcx add 20240622定时键、摆风键和数显按键，不退出强力
			//SystemMode.f_Force = 0;//强力模式关闭  
		}

		if (CmdInBak.Byte6.var.Buzzer != CommDisp.Rx.Byte6.var.Buzzer)
		{
			if (CommDisp.Rx.Byte6.var.Buzzer == ENUM_ENABLE)		;//开启蜂鸣
			else													;//关闭蜂鸣
			
			//add code...//状态变化相关参数处理
		}

		if (CmdInBak.Byte6.var.PowerOnOff != CommDisp.Rx.Byte6.var.PowerOnOff)
		{
			if ((CommDisp.Rx.Byte6.var.SelChk == ENUM_DISABLE) && (CommDisp.Rx.Byte6.var.BussChk == ENUM_DISABLE))	//非自检且非商检情况下才操作开关机
			{
				if (CommDisp.Rx.Byte6.var.PowerOnOff == ENUM_ENABLE)	
				{
					DisplayBoardTurnOn(); //开机处理
				}
				else													
				{
//					if (Fan.f_DeMold == CF_DISABLE)		//没有除霉功能时直接关风机
//					{
//						Fan.u16_DeMoldDelay = 0;
//					}
//					else
//					{
//						if (Fan.u16_DeMoldDelay == 0)
//						{
//							Fan.u16_DeMoldDelay = C_FAN_DEMOLDDELAY;
//						}
//						else
//						{
//							Fan.u16_DeMoldDelay = 0;
//							Fan.f_DeMold = CF_DISABLE;
//						}
//					}
					DisplayBoardTurnOff();      		//关机处理
				}

				//--------------------------------------------------------------------------
				//lcx add 20240704
				SystemMode.f_TempCEC = 0;		//退出达温停机
				SystemMode.f_ConTemp = 0;		//重新判定何时进入恒温
				SystemMode.f_RoughCon = 0;		//重新默认从精细调节开始
				
				Tempr.u16_T1TSDeltaCount = 0;	//重新计时
				Tempr.u16_RoughCount = 0;		//重新计时
				Tempr.u16_RoughEnCount = 0; 	//重新计时	
				//Fan.Indoor.u16_Count = 0; 	//重新计时	
				//--------------------------------------------------------------------------	
			}
			//状态变化相关参数处理

		}

		CmdInBak.Byte6.Byte = CommDisp.Rx.Byte6.Byte;
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte7_Con(void)
Description         :第7字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte7_Con(void)
{
	if (CmdInBak.Byte7.Byte != CommDisp.Rx.Byte7.Byte)						//第7字节发生变化
	{
		Tempr.u8_TempCSet = CommDisp.Rx.Byte7.Byte;			//设定温度值
		
		if (SystemMode.f_Sleep)
		{
			Tempr.u8_TempCSetSleep = Tempr.u8_TempCSet;
		}
		
		//add code...//状态变化相关参数处理
		if (System.Mode == ENUM_SYSMODE_COLD)
		{
			Tempr.u8_ColdCSet = Tempr.u8_TempCSet;
		}
		
		if (System.Mode == ENUM_SYSMODE_HEAT)
		{
			Tempr.u8_HeatCSet = Tempr.u8_TempCSet;
		}
		
		System.u32_SleepCount = 0;
		SystemMode.f_Force = 0;//强力模式关闭
		
		CmdInBak.Byte7.Byte = CommDisp.Rx.Byte7.Byte;
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte8_Con(void)
Description         :第8字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte8_Con(void)
{
	U8    temp;
	
	if (CmdInBak.Byte8.Byte != CommDisp.Rx.Byte8.Byte)						//第8字节发生变化
	{
		temp = CommDisp.Rx.Byte8.Byte;
		
		Timer.u16_Minute = temp<<3;
		Timer.u16_Minute += temp<<1;
		
		//状态变化相关参数处理
		Timer.u16_SecDiv10Remain = 0;
		
		if (Timer.u16_Minute > 0)
		{
			if (System.Enum_Status == ENUM_STATUS_ON)		//开机时定时关有效	
			{	
				Timer.f_OffEn = 1;
				Timer.f_OnEn  = 0;
			}
			else											//关机时定时开有效	
			{
				Timer.f_OffEn = 0;
				Timer.f_OnEn  = 1;		
			}
		}
		else
		{
			Timer.f_OffEn = 0;
			Timer.f_OnEn  = 0;	
		}
		
		CmdInBak.Byte8.Byte = CommDisp.Rx.Byte8.Byte;		
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte9_Con(void)
Description         :第9字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte9_Con(void)
{
	if (CmdInBak.Byte9.Byte != CommDisp.Rx.Byte9.Byte)						//第9字节发生变化
	{
//		if (CmdInBak.Byte9.var.ColdType != CommDisp.Rx.Byte9.var.ColdType)
//		{
//			if (CommDisp.Rx.Byte9.var.ColdType == ENUM_COLDONLY)		;//单冷
//			else														;//冷暖
//			
//			//add code...//状态变化相关参数处理
//		}

		if (CmdInBak.Byte9.var.WifiReset != CommDisp.Rx.Byte9.var.WifiReset)
		{
			if (CommDisp.Rx.Byte9.var.WifiReset == ENUM_ENABLE)			WiFi.f_Reset = 1;//WIFI复位
			else														WiFi.f_Reset = 0;;//无动作
			
			//add code...//状态变化相关参数处理
		}

//		if (CmdInBak.Byte9.var.CEC != CommDisp.Rx.Byte9.var.CEC)
//		{
//			if (CommDisp.Rx.Byte9.var.CEC == ENUM_ENABLE)				;//CEC达温
//			else														;//无
//			
//			//add code...//状态变化相关参数处理
//		}

//		if (CmdInBak.Byte9.var.FilterReset != CommDisp.Rx.Byte9.var.FilterReset)
//		{
//			if (CommDisp.Rx.Byte9.var.FilterReset == ENUM_ENABLE)		;//滤网复位
//			else														;//无
//			
//			//add code...//状态变化相关参数处理
//		}

//		if (CmdInBak.Byte9.var.Pump != CommDisp.Rx.Byte9.var.Pump)
//		{
//			if (CommDisp.Rx.Byte9.var.Pump == ENUM_ENABLE)				Pump.f_FuncOn = CF_ENABLE;  //水泵功能开启
//			else														Pump.f_FuncOn = CF_DISABLE; //水泵功能关闭
//			
//			//add code...//状态变化相关参数处理
//		}

//		if (CmdInBak.Byte9.var.Anion != CommDisp.Rx.Byte9.var.Anion)
//		{
//			if (CommDisp.Rx.Byte9.var.Anion == ENUM_ENABLE)				Anion.f_FuncOn = CF_ENABLE;  //负离子开启
//			else														Anion.f_FuncOn = CF_DISABLE; //负离子关闭
//			
//			//add code...//状态变化相关参数处理
//		}

		if (CmdInBak.Byte9.var.Lock != CommDisp.Rx.Byte9.var.Lock)
		{
			if (CommDisp.Rx.Byte9.var.Lock == ENUM_ENABLE)				System.f_Lock = 1;//童锁开启
			else														System.f_Lock = 0;//童锁关闭
			
			//add code...//状态变化相关参数处理
		}

//		if (CmdInBak.Byte9.var.AtmosLight != CommDisp.Rx.Byte9.var.AtmosLight)
//		{
//			if (CommDisp.Rx.Byte9.var.AtmosLight == ENUM_ENABLE)		;//氛围灯开启
//			else														;//氛围灯关闭
//			
//			//add code...//状态变化相关参数处理
//		}

		CmdInBak.Byte9.Byte = CommDisp.Rx.Byte9.Byte;		
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte10_Con(void)
Description         :第10字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte10_Con(void)
{

	
	if (CmdInBak.Byte10.Byte != CommDisp.Rx.Byte10.Byte)	//第10字节发生变化
	{
		Tempr.u8_TempFSet = CommDisp.Rx.Byte10.Byte;		//设定温度华氏
		
		//显示板程序问题修正89F对应32℃
		if (WiFi.Enum_Status == ENUM_TWIFISTATUS_AP)
		{
			if (Tempr.u8_TempFSet == 89)
			{
				Tempr.u8_TempCSet = 32;
				
				if (SystemMode.f_Sleep)
				{
					Tempr.u8_TempCSetSleep = Tempr.u8_TempCSet;
				}
				
				if (System.Mode == ENUM_SYSMODE_COLD)
				{
					Tempr.u8_ColdCSet = Tempr.u8_TempCSet;
				}
				
				if (System.Mode == ENUM_SYSMODE_HEAT)
				{
					Tempr.u8_HeatCSet = Tempr.u8_TempCSet;
				}
			}
		}
		
		if (SystemMode.f_Sleep)
		{
			Tempr.u8_TempFSetSleep = Tempr.u8_TempFSet;
		}

		//add code...//状态变化相关参数处理
		
		if (System.Mode == ENUM_SYSMODE_COLD)
		{
			Tempr.u8_ColdFSet =	Tempr.u8_TempFSet;
		}

		if (System.Mode == ENUM_SYSMODE_HEAT)
		{
			Tempr.u8_HeatFSet =	Tempr.u8_TempFSet;	
		}
		
		System.u32_SleepCount = 0;
		SystemMode.f_Force = 0;//强力模式关闭
		
		CmdInBak.Byte10.Byte = CommDisp.Rx.Byte10.Byte;
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte11_Con(void)
Description         :第11字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte11_Con(void)
{
	if (CmdInBak.Byte11.Byte != CommDisp.Rx.Byte11.Byte)				//第11字节发生变化
	{
//		if (CmdInBak.Byte11.var.FDP != CommDisp.Rx.Byte11.var.FDP)
//		{
//			if (CommDisp.Rx.Byte11.var.FDP == ENUM_ENABLE)				Protect.FDP.f_Disable = CF_DISABLE;//缺氟保护开启
//			else														Protect.FDP.f_Disable = CF_ENABLE; //缺氟保护关闭
//			
//			//add code...//状态变化相关参数处理
//		} 
//		
		if (CmdInBak.Byte11.var.Sense != CommDisp.Rx.Byte11.var.Sense)
		{
			if (CommDisp.Rx.Byte11.var.Sense == ENUM_ENABLE)			System.f_Sense = 1;//随身感开启
			else														System.f_Sense = 0;//随身感关闭
			
			//add code...//状态变化相关参数处理
			if (System.f_Sense)		Tempr.u8_TempSense = CommDisp.Rx.Byte13.Byte;
			else					Tempr.u8_TempSense = 0;
			
//			System.u16_SenseCount = 0;
		} 		
		
		if (CmdInBak.Byte11.var.UVC != CommDisp.Rx.Byte11.var.UVC)
		{
			if (CommDisp.Rx.Byte6.var.BussChk == ENUM_ENABLE)		//进入商检
			{				
				UVC.f_FuncOnBak = UVC.f_FuncOn; 					//进入商检前记录UVC开关状态					
			}
			
			if (CommDisp.Rx.Byte11.var.UVC == ENUM_ENABLE)				UVC.f_FuncOn = CF_ENABLE;     //UVC功能开启
			else														UVC.f_FuncOn = CF_DISABLE;    //UVC功能关闭
			
			//add code...//状态变化相关参数处理
		}		
		
//		if (CmdInBak.Byte11.var.RemoteTimer != CommDisp.Rx.Byte11.var.RemoteTimer)
//		{
//			if (CommDisp.Rx.Byte11.var.RemoteTimer == ENUM_ENABLE)		;//远程定时开启
//			else														;//远程定时关闭
//			
//			//add code...//状态变化相关参数处理
//		}			
//		
		if (CmdInBak.Byte11.var.WifiPower != CommDisp.Rx.Byte11.var.WifiPower)
		{
			if (CommDisp.Rx.Byte6.var.BussChk == ENUM_ENABLE)		//进入商检
			{				
				WiFi.f_FuncOnBak = WiFi.f_FuncOn; 					//进入商检前记录wifi电源开关状态					
			}			
			
			
			if (CommDisp.Rx.Byte11.var.WifiPower == ENUM_ENABLE)		WiFi.f_FuncOn = CF_ENABLE;	//wifi电源开启
			else														WiFi.f_FuncOn = CF_DISABLE;	//wifi电源关闭
			
			//add code...//状态变化相关参数处理
//			if (WiFi.f_AppOn == CF_ENABLE)
//			{
//				mcu_set_wifi_mode(SMART_CONFIG);
//			}

		}	

//		if (CmdInBak.Byte11.var.Silence != CommDisp.Rx.Byte11.var.Silence)
//		{
//			if (CommDisp.Rx.Byte11.var.Silence == ENUM_ENABLE)			;//静音开启
//			else														;//静音关闭
//			
//			//add code...//状态变化相关参数处理
//		}			
//		
//		if (CmdInBak.Byte11.var.SweepUD != CommDisp.Rx.Byte11.var.SweepUD)
//		{
//			if (CommDisp.Rx.Byte11.var.SweepUD == ENUM_ENABLE)			;//上下摆风开启
//			else														;//上下摆风关闭
//			
//			//add code...//状态变化相关参数处理
//		}

		if (CmdInBak.Byte11.var.PerfTest != CommDisp.Rx.Byte11.var.PerfTest)
		{
			if (CommDisp.Rx.Byte11.var.PerfTest == ENUM_ENABLE)			SystemMode.f_PerTest = 1;//性能测试开启
			else														SystemMode.f_PerTest = 0;//性能测试关闭
			
			//add code...//状态变化相关参数处理
			if (SystemMode.f_PerTest == 0)
			{
				Comp.u8_SelTestDelay = 0;
			}

			//lcx add
			if (SystemMode.f_PerTest == 1)
			{
				Fan.f_SweepLR = 0;	
				Swing.f_PrefTestSetMaxAngle = 1;
			}			
			
		}
		
		CmdInBak.Byte11.Byte = CommDisp.Rx.Byte11.Byte;
		
	}
	
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte12_Con(void)
Description         :第12字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte12_Con(void)
{
	volatile    U8    temp;
	
	if (CmdInBak.Byte12.Byte != CommDisp.Rx.Byte12.Byte)	//第12字节发生变化
	{
		temp = CommDisp.Rx.Byte12.Byte;						//商检步骤
		
		//add code...//状态变化相关参数处理
		
		CmdInBak.Byte12.Byte = CommDisp.Rx.Byte12.Byte;
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte13_Con(void)
Description         :第13字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte13_Con(void)
{
	
	if (CmdInBak.Byte13.Byte != CommDisp.Rx.Byte13.Byte)	//第13字节发生变化
	{
		Tempr.u8_TempSense = CommDisp.Rx.Byte13.Byte;						//随身感温度
		
		//add code...//状态变化相关参数处理
//		if (Tempr.u8_TempSense > 0)
//		{
//			System.f_Sense = 1;
//		}
//		else
//		{
//			System.f_Sense = 0;		
//		}
		
		CmdInBak.Byte13.Byte = CommDisp.Rx.Byte13.Byte;
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte14_Con(void)
Description         :第14字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte14_Con(void)
{
	if (CmdInBak.Byte14.Byte != CommDisp.Rx.Byte14.Byte)				//第14字节发生变化
	{
//		if (CmdInBak.Byte14.var.ECO != CommDisp.Rx.Byte14.var.ECO)
//		{
//			if (CommDisp.Rx.Byte14.var.ECO == ENUM_ENABLE)				;//ECO开启
//			else														;//ECO关闭
//			
//			//add code...//状态变化相关参数处理
//		} 	
//		
//		if (CmdInBak.Byte14.var.Pannel != CommDisp.Rx.Byte14.var.Pannel)
//		{
//			if      (CommDisp.Rx.Byte14.var.Pannel == ENUM_PANNEL_B)			;//B面板
//			else if (CommDisp.Rx.Byte14.var.Pannel == ENUM_PANNEL_C)			;//C面板
//			else																;//其他
//			
//			//add code...//状态变化相关参数处理
//		} 

//		if (CmdInBak.Byte14.var.DeWater != CommDisp.Rx.Byte14.var.DeWater)
//		{
//			if (CommDisp.Rx.Byte14.var.DeWater == ENUM_ENABLE)			;//除水标志开启
//			else														;//除水标志关闭
//			
//			//add code...//状态变化相关参数处理
//		}

		if (CmdInBak.Byte14.var.DeMoldFunc != CommDisp.Rx.Byte14.var.DeMoldFunc)
		{
			if (CommDisp.Rx.Byte14.var.DeMoldFunc == ENUM_ENABLE)
			{				
//				if (Fan.f_DeMold == CF_DISABLE)
//				{
//					Fan.u16_DeMoldDelay = C_FAN_DEMOLDDELAY;
//				}
				Fan.f_DeMold = CF_ENABLE;     //除霉功能开启
			}
			else														
			{	
				Fan.f_DeMold = CF_DISABLE;    //除霉功能关闭
//				Fan.u16_DeMoldDelay = 0;
			}
			//add code...//状态变化相关参数处理
		}

//		if (CmdInBak.Byte14.var.DispStatus != CommDisp.Rx.Byte14.var.DispStatus)
//		{
//			if      (CommDisp.Rx.Byte14.var.DispStatus == ENUM_DISPSTATUS_OFF)		;//熄屏
//			else if (CommDisp.Rx.Byte14.var.DispStatus == ENUM_DISPSTATUS_HALF)		;//半亮显示
//			else																	;//正常显示								
//	
//			//add code...//状态变化相关参数处理
//		}
		
		CmdInBak.Byte14.Byte = CommDisp.Rx.Byte14.Byte;
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoard_Byte15_Con(void)
Description         :第15字节信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoard_Byte15_Con(void)
{
	if (CmdInBak.Byte15.Byte != CommDisp.Rx.Byte15.Byte)				//第15字节发生变化
	{
		if (CmdInBak.Byte15.var.PlatForm != CommDisp.Rx.Byte15.var.PlatForm)
		{
			switch (CommDisp.Rx.Byte15.var.PlatForm)					//各平台机型
			{
				case	ENUM_PLATFORM_L		: break;    
				case	ENUM_PLATFORM_M     : break;
				case	ENUM_PLATFORM_N     : break;
				case	ENUM_PLATFORM_K     : break;
				case	ENUM_PLATFORM_KP    : break;
				case	ENUM_PLATFORM_KN    : break;
				case	ENUM_PLATFORM_KA    : break;
				case	ENUM_PLATFORM_R_RP 	: break;

				default: break;
			}
		}
		
		if (CmdInBak.Byte15.var.AutoMode != CommDisp.Rx.Byte15.var.AutoMode)
		{
			if (CommDisp.Rx.Byte15.var.AutoMode == ENUM_ENABLE)			;//有自动模式
			else														;//无自动模式
		}
		
		if (CmdInBak.Byte15.var.ForceMode != CommDisp.Rx.Byte15.var.ForceMode)
		{
			if (CommDisp.Rx.Byte15.var.ForceMode == ENUM_ENABLE)		SystemMode.f_Force = 1;//强力模式开启
			else														SystemMode.f_Force = 0;//强力模式关闭
			
			SystemMode.f_TempCEC = 0;				//操作强力模式,达温标志清除
			System.u32_ForceRunCount = 0;
		}		

		if (CmdInBak.Byte15.var.Lighting != CommDisp.Rx.Byte15.var.Lighting)
		{
			if (CommDisp.Rx.Byte15.var.Lighting == ENUM_ENABLE)			;//灯光标志开启
			else														;//灯光标志关闭
		}
		
		CmdInBak.Byte15.Byte = CommDisp.Rx.Byte15.Byte;
	}
}
/****************************************************************************************************
Function Name       :void	DisplayBoardCommandCheck(void)
Description         :判定显示板有命令送达
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoardCommandCheck(void)
{
	static U8  U8_CmdChkCount;
	
	
	CmdInBak.Byte4.Byte = CommDisp.Rx.Byte4.Byte;				
	if ((CommDisp.Rx.Byte4.var.MachineType == ENUM_MACHINETYPE_YDKT) 
		&& (CommDisp.Rx.Byte4.var.DataType != ENUM_DATATYPE_COMMAND_DISABLE))   //移动空调机型且有命令时
	//进入性能测试时，显示有时候发送过来第四字节的数据类型是 0001: 无命令。 lcx add 20240425
//	if ((CommDisp.Rx.Byte4.var.MachineType == ENUM_MACHINETYPE_YDKT) 
//		&& (CommDisp.Rx.Byte4.var.DataType != ENUM_DATATYPE_COMMAND_DISABLE || (CommDisp.Rx.Byte11.var.PerfTest && !SystemMode.f_PerTest)))   //移动空调机型且有命令时		
	{		
		CommDisp.f_Ack_RecChg = CF_ENABLE;	//接收有设定
		
		DisplayBoard_Byte5_Con();		//第5字节信息处理
		
		DisplayBoard_Byte6_Con();		//第6字节信息处理
		
		DisplayBoard_Byte7_Con();		//第7字节信息处理
		
		DisplayBoard_Byte8_Con();		//第8字节信息处理
		
		DisplayBoard_Byte9_Con();		//第9字节信息处理
		
		DisplayBoard_Byte10_Con();		//第10字节信息处理
		
		DisplayBoard_Byte11_Con();		//第11字节信息处理
		
		DisplayBoard_Byte12_Con();		//第12字节信息处理
		
		DisplayBoard_Byte13_Con();		//第13字节信息处理
		
		DisplayBoard_Byte14_Con();		//第14字节信息处理
		
		DisplayBoard_Byte15_Con();		//第15字节信息处理
				
	}
	else
	{
		if (++U8_CmdChkCount >= 25)		//0.25s
		{
			U8_CmdChkCount = 0;
			CommDisp.f_CmdInBakSync = 0;	//重新同步显示板标志备份
		}
	}

	//需要一次与备份同步
	if ((CommDisp.f_CmdInBakSync == 0) && (System.u8_PowerOn_Count >= 3))	//上电300ms后
	{
		CommDisp.f_CmdInBakSync = 1;
		
		CmdInBak.Byte4.Byte = CommDisp.Rx.Byte4.Byte;
		CmdInBak.Byte5.Byte = CommDisp.Rx.Byte5.Byte;
		CmdInBak.Byte6.Byte = CommDisp.Rx.Byte6.Byte;
		CmdInBak.Byte7.Byte = CommDisp.Rx.Byte7.Byte;
		CmdInBak.Byte8.Byte = CommDisp.Rx.Byte8.Byte;
		CmdInBak.Byte9.Byte = CommDisp.Rx.Byte9.Byte;
		CmdInBak.Byte10.Byte = CommDisp.Rx.Byte10.Byte;
		CmdInBak.Byte11.Byte = CommDisp.Rx.Byte11.Byte;
		CmdInBak.Byte12.Byte = CommDisp.Rx.Byte12.Byte;
		CmdInBak.Byte13.Byte = CommDisp.Rx.Byte13.Byte;
		CmdInBak.Byte14.Byte = CommDisp.Rx.Byte14.Byte;
		CmdInBak.Byte15.Byte = CommDisp.Rx.Byte15.Byte;
		
		if (CommDisp.Rx.Byte9.var.WifiReset == ENUM_ENABLE)			WiFi.f_Reset = 1;//WIFI复位
		else														WiFi.f_Reset = 0;;//无动作

		Tempr.f_TempUnitBak = Tempr.f_TempUnit;
		
	}		
}
/****************************************************************************************************
Function Name       :void	DisplayBoardTurnOff(void)
Description         :关机处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoardTurnOff(void)
{
	TimerPara_Init();						//定时全参数初始化清0
	
	SystemMode.f_TempCEC = 0;				//开关机,达温标志清除
	SystemMode.f_PerTest = 0;				//关机退出性能测试
	SystemMode.f_Force = 0;					//关机退出强力模式
	SystemMode.f_AntiDewMark = 0;			//关机清除防凝露不能重复进入标志	
	
	CmdInBak.Byte6.var.PowerOnOff = Enum_DISABLE;		//同步显示板开关机标志位为关机

	if (System.Enum_Status == ENUM_STATUS_BUSSCHK)	//从商检状态关机
	{
		Fan.f_SweepLR = Fan.f_SweepLRChkBak;
		Fan.f_SweepLRChkBak = 0;
		CommDisp.Tx.Byte5.var.SwLRType = (ENUM_SWLRTYPE)Fan.f_SweepLR;
		CommDisp.Rx.Byte5.var.SwLRType = (ENUM_SWLRTYPE)Fan.f_SweepLR;
		if (Fan.f_SweepLR == 0)	//原来状态是没有开启摇头需恢复到原来默认打开角度
		{
			StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ON;
			Swing.u16_anglebak = C_STEPMOTOR_ANGLE_DEFAULT;
		}
					
		UVC.f_FuncOn = UVC.f_FuncOnBak;
		UVC.f_FuncOnBak = 0;
		CommDisp.Tx.Byte18.var.UVC = (ENUM_FLAG)UVC.f_FuncOn;
		CommDisp.Rx.Byte11.var.UVC = (ENUM_FLAG)UVC.f_FuncOn;
					
		WiFi.f_FuncOn = WiFi.f_FuncOnBak;
		WiFi.f_FuncOnBak = 0;
		CommDisp.Tx.Byte17.var.WifiPower = (ENUM_FLAG)WiFi.f_FuncOn;
		CommDisp.Rx.Byte11.var.WifiPower = (ENUM_FLAG)WiFi.f_FuncOn;
		
	}
	
	System.Enum_Status = ENUM_STATUS_OFF;
	
	
}
/****************************************************************************************************
Function Name       :void	DisplayBoardTurnOn(void)
Description         :开机处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoardTurnOn(void)
{
	TimerPara_Init();						//定时全参数初始化清0
	
	SystemMode.f_TempCEC = 0;				//开关机,达温标志清除
	SystemMode.f_Force = 0;					//开关机,退出强力模式 lcx add 20240715
	Fan.Indoor.u16_Delay = 30;				//收到开机指令摆风打开后上风机延时3s
	
	Comp.u8_PowerOnDelay = 50;				//开机后5s才开压缩机
	
//	Fan.u16_VentilateDelay = C_FAN_VENTILATEDELAY;        //通风逻辑开机风机运行最多3min
	
	T1.u16_ErrCount = 0;
	T2.u16_ErrCount = 0;
	T3.u16_ErrCount = 0;
	T4.u16_ErrCount = 0;
	
//	if (WiFi.Enum_Status == ENUM_TWIFISTATUS_AP)
//	{
//		if (Tempr.u8_TempFSet == 89)	//应对显示板程序问题
//		{
//			Tempr.u8_TempCSet = 32;
//		}	
//	}
	
	System.Enum_Status = ENUM_STATUS_ON;  				  //开机
}
