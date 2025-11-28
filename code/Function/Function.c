/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Function.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/03/06
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_SYSTEM      	 System;              //系统相关变量 
STRUCT_SYSTEMMODE    SystemMode;
//STRUCT_USERPARA      UserPara; //用户参数
STRUCT_FTYPARA       FtyPara; //工程参数

/****************************************************************************************************
Function Name       :void App_Status_Init(void)
Description         :上电初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Status_Init(void)
{
	P_EEPwren_On();			//允许写EE
	
	
	if (System.u8_PowerOn_Count >= 3)	//上电300ms后
	{
		//读取EE信息,建立掉电记忆逻辑
		Remember_ReadEEFunc();								//掉电记忆-读取EE数据功能部分
		Remember_ReadEEPara();								//掉电记忆-读取EE数据参数部分

		Comp.u8_Cold_TargetHZ[0]  = EEP.u8_rdBuf[42];		//EE.PARA FC0
		Comp.u8_Cold_TargetHZ[1]  = EEP.u8_rdBuf[43];		//EE.PARA FC1
		Comp.u8_Cold_TargetHZ[2]  = EEP.u8_rdBuf[44];		//EE.PARA FC2
		Comp.u8_Cold_TargetHZ[3]  = EEP.u8_rdBuf[45];		//EE.PARA FC3
		Comp.u8_Cold_TargetHZ[4]  = EEP.u8_rdBuf[46];		//EE.PARA FC4
		Comp.u8_Cold_TargetHZ[5]  = EEP.u8_rdBuf[47];		//EE.PARA FC5
		Comp.u8_Cold_TargetHZ[6]  = EEP.u8_rdBuf[48];		//EE.PARA FC6
		Comp.u8_Cold_TargetHZ[7]  = EEP.u8_rdBuf[49];		//EE.PARA FC7
		Comp.u8_Cold_TargetHZ[8]  = EEP.u8_rdBuf[50];		//EE.PARA FC8
		Comp.u8_Cold_TargetHZ[9]  = EEP.u8_rdBuf[51];		//EE.PARA FC9
		Comp.u8_Cold_TargetHZ[10] = EEP.u8_rdBuf[52];		//EE.PARA FC10
		Comp.u8_Cold_TargetHZ[11] = EEP.u8_rdBuf[53];		//EE.PARA FC11
		Comp.u8_Cold_TargetHZ[12] = EEP.u8_rdBuf[54];		//EE.PARA FC12
		Comp.u8_Cold_TargetHZ[13] = EEP.u8_rdBuf[55];		//EE.PARA FC13
		Comp.u8_Cold_TargetHZ[14] = EEP.u8_rdBuf[56];		//EE.PARA FC14
		Comp.u8_Cold_TargetHZ[15] = EEP.u8_rdBuf[57];		//EE.PARA FC15	

		Comp.u8_Heat_TargetHZ[0]  = EEP.u8_rdBuf[58];		//EE.PARA FH0
		Comp.u8_Heat_TargetHZ[1]  = EEP.u8_rdBuf[59];		//EE.PARA FH1
		Comp.u8_Heat_TargetHZ[2]  = EEP.u8_rdBuf[60];		//EE.PARA FH2
		Comp.u8_Heat_TargetHZ[3]  = EEP.u8_rdBuf[61];		//EE.PARA FH3
		Comp.u8_Heat_TargetHZ[4]  = EEP.u8_rdBuf[62];		//EE.PARA FH4
		Comp.u8_Heat_TargetHZ[5]  = EEP.u8_rdBuf[63];		//EE.PARA FH5
		Comp.u8_Heat_TargetHZ[6]  = EEP.u8_rdBuf[64];		//EE.PARA FH6
		Comp.u8_Heat_TargetHZ[7]  = EEP.u8_rdBuf[65];		//EE.PARA FH7
		Comp.u8_Heat_TargetHZ[8]  = EEP.u8_rdBuf[66];		//EE.PARA FH8
		Comp.u8_Heat_TargetHZ[9]  = EEP.u8_rdBuf[67];		//EE.PARA FH9
		Comp.u8_Heat_TargetHZ[10] = EEP.u8_rdBuf[68];		//EE.PARA FH10
		Comp.u8_Heat_TargetHZ[11] = EEP.u8_rdBuf[69];		//EE.PARA FH11
		Comp.u8_Heat_TargetHZ[12] = EEP.u8_rdBuf[70];		//EE.PARA FH12
		Comp.u8_Heat_TargetHZ[13] = EEP.u8_rdBuf[71];		//EE.PARA FH13
		Comp.u8_Heat_TargetHZ[14] = EEP.u8_rdBuf[72];		//EE.PARA FH14
		Comp.u8_Heat_TargetHZ[15] = EEP.u8_rdBuf[73];		//EE.PARA FH15

		
		//在定时和睡眠功能下掉电恢复后待机
		if ((System.Enum_Status == ENUM_STATUS_OFF) || Timer.f_Enable || SystemMode.f_Sleep)
		{	
			Comp.u16_RestartDelay = C_COMP_RESTARTDELAY0;
			System.Enum_Status = ENUM_STATUS_OFF;
			Timer.f_Enable = SystemMode.f_Sleep = 0; //lcx add 20240515
		}
		else
		{
			//其他掉电恢复到掉电前的状态
			Comp.u16_RestartDelay = C_COMP_RESTARTDELAY;		//P20
			System.Enum_Status = ENUM_STATUS_ON;
		}
		
		//相关参数
		TimerPara_Init();
		Defrost_Init();		//化霜相关变量初始化--退出化霜
	}
	
	
}
/****************************************************************************************************
Function Name       :void App_Status_Off(void)
Description         :待机
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	 App_Status_Off(void)
{
	Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_INIT;
	
	//模式标志重新判定
	SystemMode.f_Cold = 0;		
	SystemMode.f_Heat = 0;
	SystemMode.f_Fan = 0;
	SystemMode.f_Auto = 0;	
	
	Comp.f_AppOn = OFF;				//关压缩机
	Fan.Indoor.f_AppOn = OFF;		//关内风机
	Fan.Outdoor.f_AppOn = OFF;		//关外风机
	WPMotor.f_AppOn = OFF;			//关打水电机
	FourWay.f_AppOn = OFF;			//关机需求关闭四通阀
//	EAHeater.f_AppOn = OFF;			//关电加热
	UVC.f_AppOn = OFF;				//关闭UVC
	CirculationPump.f_AppOn = OFF;	//
	Crank.f_AppOn = OFF;
	WFV.f_AppOn = OFF;
	Comp.u16_RunMinDelay = 0;		//关机清0
	
	SystemMode.f_Sleep = 0;
	System.u32_SleepCount = 0;
	System.u32_SleepTimCount = 0;
	
	if (Fan.Indoor.f_DrvOn == OFF)
	{
		Fan.Indoor.u16_RealRPM = 0;
	}
	
	if (Fan.Outdoor.f_DrvOn == OFF)
	{
		Fan.Outdoor.u16_RealRPM = 0;
	}	
}
/****************************************************************************************************
Function Name       :void App_Status_On(void)
Description         :开机
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Status_On(void)
{
	S8    Inte_SleepTempDelta;
	
	//电加热默认关
//	EAHeater.f_AppOn = OFF;
	
	//开机上下风机默认运行
//	Fan.Indoor.f_AppOn = ON;
//	Fan.Outdoor.f_AppOn = ON;
	
	//系统模式
	switch (System.Mode)
	{
		case	ENUM_SYSMODE_COLD:       //制冷
		{		
			Inte_SleepTempDelta = 0;
			Fan.f_InDoorFanTpLow = 0;
			Fan.Indoor.f_ForceLow = 0;
			if (SystemMode.f_Cold == 0)
			{
				SystemMode.f_ConTemp = 0; //lcx add 20240628 转换模式进去，要清除达温停机。重新计时进入条件。
			}

//			if (SystemMode.f_HeatBak == 1)	//制冷切换制热
//			{
//				Comp.f_Delay2min = 1;	//2min
//			}
			
			SystemMode.f_Cold = 1;
			SystemMode.f_Heat = 0;
			SystemMode.f_Fan = 0;
			SystemMode.f_Auto = 0;
			
			if ((SystemMode.f_PerTest == 1) && ((Tempr.u8_TempCSet == 29) || (Tempr.u8_TempCSet == 30)))
			{
				Comp.f_AppOn = ON;
			}	
			else if ((T1.f_Error == 1) || (T2.f_Error == 1) || (T3.f_Error == 1) 
 			|| (T4.f_Error == 1) || (Tp.f_Error == 1))	//传感器故障
			{
				Comp.u16_RunMinDelay = 0;		//故障清0
				Comp.f_AppOn = OFF;
			}		
			else			//正常情况
			{
				if (System.u8_PowerOn_Count >= 10)	//上电1s后才判断
				{
					if (SystemMode.f_TempCEC == 0)
					{
						if ((T5.s16_ValueMul10bc  >= (TempValueMul10(Tempr.u8_TempCSet) + (U8)(FtyPara.u16L2))))
//						&& (Comp.u16_RestartDelay == 0) &&(Fan.Outdoor.u16_Delay == 0))
						{
							if (CirculationPump.u16_RunCnt >= (FtyPara.u16P4 * 10))
							{
								Fan.Outdoor.f_AppOn = ON;
							}
							
							CirculationPump.f_AppOn = ON;
							SystemMode.f_ConTemp = 0;
						}
						else if ((T5.s16_ValueMul10bc <= (TempValueMul10(Tempr.u8_TempCSet)))
						&& (Fan.Outdoor.u16_Delay == 0) 
						&& (Comp.u32_StopContCount >= (FtyPara.u16P3 * 10)))
						{
							Fan.Outdoor.f_AppOn = OFF;
							if (Comp.u32_StopContCount >= (FtyPara.u16P5 * 10))
							{
								CirculationPump.f_AppOn = OFF;
							}
							
							if (T5.s16_ValueMul10bc <= (TempValueMul10(Tempr.u8_TempCSet)))
							{
								SystemMode.f_ConTemp = 1;
							}
						}
						
						if ((Fan.Outdoor.f_AppOn == 0)
						|| (T5.s16_ValueMul10bc <= (TempValueMul10(Tempr.u8_TempCSet))))
						{
							Comp.f_AppOn = OFF;				//关压缩机
						}
						else if (Fan.Outdoor.f_AppOn)
						{
							Comp.f_AppOn = ON;
						}
						else if (Fan.Outdoor.f_AppOn == 0)
						{
							Comp.f_AppOn = OFF;
						}
					}
				}
			}

			
			
//			if ((Comp.f_AppOn) || (T1.f_Error == 1) || (T4.f_Error == 1) || (Tp.f_Error == 1)) 
			if (((!Protect.f_HighPress && !Protect.f_LowPress 
			&& !Protect.f_Tp) && !Protect.f_CompCurr && (Protect.PhaseSeqStatus != ENUM_PROSTATUS_PROTECT))
			||(Protect.f_T2Cold))
			{
				Fan.Indoor.f_AppOn = ON;
			}
			else			   
			{	
				Fan.Indoor.f_AppOn = OFF;
			}
			
//			if ((T4.f_Error == 1) || (Comp.f_DrvOn == OFF)) 	WPMotor.f_AppOn = OFF;
//			else 												WPMotor.f_AppOn = ON;
		}break;
		
		case	ENUM_SYSMODE_HUM:	     //除湿
		{
			Inte_SleepTempDelta = 0;
			
			SystemMode.f_Cold = 1;
			SystemMode.f_Heat = 0;
			SystemMode.f_Fan = 0;
			SystemMode.f_Auto = 0;
			
			if ((T1.f_Error == 1) || (T2.f_Error == 1) || (T3.f_Error == 1) 
			|| (T4.f_Error == 1) || (Tp.f_Error == 1))	//传感器故障
			{
				Comp.u16_RunMinDelay = 0;		//故障清0
				
				if ((T2.f_Error == 1) || (T3.f_Error == 1))
				{
					Comp.f_AppOn = OFF;
				}
				else if (Tp.f_Error == 1)
				{
					if (Tp.u16_ErrCount	< 6000)	//开10min
					{
						Comp.f_AppOn = ON;
					}
					else if (Tp.u16_ErrCount < 9000)
					{
						Comp.f_AppOn = OFF;
					}
					else
					{
						Tp.u16_ErrCount = 0;	//重新新一轮循环
					}				
				}				
				else if ((T1.f_Error == 1) || (T4.f_Error == 1))
				{
					if (T1.f_Error == 1)
					{
						if (T1.u16_ErrCount	< 18000)	//开30min
						{
							Comp.f_AppOn = ON;
							Comp.u8_InitIndex = 8;
							Comp.u8_TargetSrc = Comp.u8_Cold_TargetHZ[Comp.u8_InitIndex];
							Comp.u8_TargetHZ = Comp.u8_TargetSrc;
						}
						else if (T1.u16_ErrCount < 21000)
						{
							Comp.f_AppOn = OFF;
						}
						else
						{
							T1.u16_ErrCount = 0;	//重新新一轮循环
						}
					}
					else if (T4.f_Error == 1)
					{
						if (T4.u16_ErrCount	< 18000)	//开30min
						{
							Comp.f_AppOn = ON;
						}
						else if (T4.u16_ErrCount < 21000)
						{
							Comp.f_AppOn = OFF;
						}
						else
						{
							T4.u16_ErrCount = 0;	//重新新一轮循环
						}					
					}
				}
			}
			else
			{
				if (T1.s16_ValueMul10 >= 180)		//T1≥18℃
				{				
					Comp.f_AppOn = ON;
					SystemMode.f_TempCEC = 0;
					Protect.f_HumiT1Low = 0;
				}
				else if (T1.s16_ValueMul10 <= 160)	//T1≤16℃
				{
					Comp.f_AppOn = OFF;
					SystemMode.f_TempCEC = 1;
					Protect.f_HumiT1Low = 1;
				}
				else //16℃<T1<18℃
				{
					if(Protect.f_HumiT1Low == 1) //lcx add 20240620
					{
						Comp.f_AppOn = OFF;
						SystemMode.f_TempCEC = 1;
					}
				}

				if(System.f_HumiCSetInitOK == 0) //lcx add 
				{
					System.f_HumiCSetInitOK = 1;
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
				
			}


			//除湿模式内风机与压缩机同步运行					 //吴工原始	
			//if (Comp.f_AppOn || Comp.f_DrvOn)  //吴工原始	
			if ((Comp.f_AppOn) || (T1.f_Error == 1) || (T4.f_Error == 1) || (Tp.f_Error == 1))  //lcx add 20240715
			{
				Fan.Indoor.f_AppOn = ON;
			}
			else			   
			{
				Fan.Indoor.f_AppOn = OFF;
			}
			
			if ((T4.f_Error == 1) || (Comp.f_DrvOn == OFF)) 	WPMotor.f_AppOn = OFF;
			else 												WPMotor.f_AppOn = ON;
		}break;
		
		case	ENUM_SYSMODE_FAN:        //送风
		{
			Inte_SleepTempDelta = 0;
			Fan.f_InDoorFanTpLow = 0;
			Fan.Indoor.f_ForceLow = 0;
			Protect.f_T2Cold = 0;
			SystemMode.f_Cold = 0;
			SystemMode.f_Heat = 0;
			SystemMode.f_Fan = 1;
			SystemMode.f_Auto = 0;
			
			SystemMode.f_TempCEC = 0;
			
			Comp.f_AppOn = OFF;
			Comp.u16_RunMinDelay = 0;	//压缩机立即停止 延时清0
			
			Fan.Outdoor.f_AppOn = OFF;   //送风外风机关闭
//			Fan.Outdoor.u16_Delay = 0;	 //外风机立即停止 延时清0				//按照功能书转送风时保持延时

			Fan.Indoor.f_AppOn  = ON;
			Fan.Indoor.u16_Delay = 0;
			WPMotor.f_AppOn = OFF;
		}break;
		
		case	ENUM_SYSMODE_INTE:       //智能
		{		
			//根据当前室温,自动选择运行模式
			
			if ((T1.f_Error == 1) || (T2.f_Error == 1) || (T3.f_Error == 1) || (T4.f_Error == 1) || (Tp.f_Error == 1))
			{
				SystemMode.f_Auto = 0;		//出现故障自动标志清0重新判定 20231128
				SystemMode.f_Cold = 0;
				SystemMode.f_Heat = 0;
				SystemMode.f_Fan = 1;		//T1,T2,T3,T4,Tp故障情况下 智能模式下强制按送风运行	
				
				Comp.f_AppOn = OFF;
				WPMotor.f_AppOn = OFF; 	 	//lcx add 20240713 压机开90s后打水开。只要压缩机关了，打水电机也要关。
				Comp.u16_RunMinDelay = 0;	//故障清0
			}
			else
			{
				if (SystemMode.f_Auto == 0)//首次确认工作在哪个模式
				{
					SystemMode.f_Cold = 0;
					SystemMode.f_Heat = 0;
					SystemMode.f_Fan = 0;				
					
					if (T1.s16_ValueMul10 >= 250)		//P200
					{
						SystemMode.f_Cold = 1;					
					}
					else if (T1.s16_ValueMul10 >= 200)	//P204
					{
						SystemMode.f_Fan = 1;
						Comp.f_AppOn = OFF;
						Comp.u16_RunMinDelay = 0;	//压缩机立即停止 延时清0						
					}
					else if (T1.s16_ValueMul10 >= 190)	//P205
					{
						SystemMode.f_Fan = 0;	
						Comp.f_AppOn = OFF;
						Comp.u16_RunMinDelay = 0;	//压缩机立即停止 延时清0						
					}
					else
					{
						SystemMode.f_Heat = 1;
					}
					
					SystemMode.f_Auto = 1;
				}
				else
				{
					if (SystemMode.f_Cold == 1)
					{
						Comp.f_AppOn = ON;
						FourWay.f_AppOn = OFF;
						
						if (Comp.f_AppOn)  Fan.Indoor.f_AppOn = ON;
						else			   Fan.Indoor.f_AppOn = OFF;						
						
						if ((T4.f_Error == 1) || (Comp.f_DrvOn == OFF)) 	WPMotor.f_AppOn = OFF;
						else 												WPMotor.f_AppOn = ON;
						
						if (SystemMode.f_Sleep)
						{							
							if (System.u32_SleepCount >= 72000)	//2小时
							{
								Inte_SleepTempDelta = 20;				//2℃
							}
							else if (System.u32_SleepCount >= 36000)	//1小时
							{
								Inte_SleepTempDelta = 10;				//1℃
							}
							else
							{
								Inte_SleepTempDelta = 0;
							}							
						}
						else
						{
							Inte_SleepTempDelta = 0;
						}
						
						
						if (T1.s16_ValueMul10 <= (230+Inte_SleepTempDelta))		//P202
						{
							if (++System.u8_InteFdCount[0] >= 100)	//防抖
							{
								System.u8_InteFdCount[0] = 0;
								
								SystemMode.f_Cold = 0;
								SystemMode.f_Fan = 1;
								
								if (T1.s16_ValueMul10 <= (200+Inte_SleepTempDelta))	//P204	温差巨大自动标志清0重新判定 20231212
								{
									SystemMode.f_Auto = 0;
								}
							}
						}
						else
						{
							System.u8_InteFdCount[0] = 0;
						}
						
						System.u8_InteFdCount[1] = 0;
						System.u8_InteFdCount[2] = 0;
						System.u8_InteFdCount[3] = 0;
						System.u8_InteFdCount[4] = 0;
						System.u8_InteFdCount[5] = 0;						
						
					}
					else if (SystemMode.f_Heat == 1)
					{						
						Comp.f_AppOn = ON;
						FourWay.f_AppOn = ON;
						
						WPMotor.f_AppOn = OFF;

						if (Comp.f_AppOn) 
						{	
							if (((Comp.f_DrvOn == OFF) && (T2.s16_ValueMul10 >= 350)) || (Comp.f_DrvOn == ON))
							{
								Fan.Indoor.f_AppOn = ON;
							}
							else
							{				
								Fan.Indoor.f_AppOn = OFF;
							}
									
						}
						else			   
						{	
							if (Fan.Indoor.u16_Delay == 0)	//延时完毕才能关
							{
								Fan.Indoor.f_AppOn = OFF;
							}
						}

						
						if (SystemMode.f_Sleep)	
						{	
							if (System.u32_SleepCount >= 108000)	//3小时
							{
								Inte_SleepTempDelta = -30;				//-3℃
							}								
							else if (System.u32_SleepCount >= 72000)	//2小时
							{
								Inte_SleepTempDelta = -20;				//-2℃
							}
							else if (System.u32_SleepCount >= 36000)	//1小时
							{
								Inte_SleepTempDelta = -10;				//-1℃
							}
							else
							{
								Inte_SleepTempDelta = 0;
							}							
						}
						else
						{
							Inte_SleepTempDelta = 0;
						}						
						
						if (T1.s16_ValueMul10 >= (190+Inte_SleepTempDelta))		//P205
						{
							if (++System.u8_InteFdCount[1] >= 100)
							{
								System.u8_InteFdCount[1] = 0;
								
								//无风
								SystemMode.f_Cold = 0;
								SystemMode.f_Heat = 0;
								SystemMode.f_Fan = 0;
							}
						}
						else
						{
							System.u8_InteFdCount[1] = 0;
						}
						
						System.u8_InteFdCount[0] = 0;
						System.u8_InteFdCount[2] = 0;
						System.u8_InteFdCount[3] = 0;
						System.u8_InteFdCount[4] = 0;
						System.u8_InteFdCount[5] = 0;						
					}
					else//送风或无风
					{
						Comp.f_AppOn = OFF;
						FourWay.f_AppOn = OFF;
						
						WPMotor.f_AppOn = OFF;

						if (SystemMode.f_Sleep)
						{							
							if (System.u32_SleepCount >= 72000)	//2小时
							{
								Inte_SleepTempDelta = 20;				//2℃
							}
							else if (System.u32_SleepCount >= 36000)	//1小时
							{
								Inte_SleepTempDelta = 10;				//1℃
							}
							else
							{
								Inte_SleepTempDelta = 0;
							}							
						}
						else
						{
							Inte_SleepTempDelta = 0;
						}

						
						if (SystemMode.f_Fan == 1)	//送风
						{
							if (T1.s16_ValueMul10 >= (250+Inte_SleepTempDelta))		//P200
							{
								if (++System.u8_InteFdCount[2] >= 100)
								{
									System.u8_InteFdCount[2] = 0;
									
									SystemMode.f_Fan = 0;
									SystemMode.f_Cold = 1;
								}
								
								System.u8_InteFdCount[3] = 0;
							}
							else if (T1.s16_ValueMul10 <= (190/*+Inte_SleepTempDelta*/))		//P205
							{
								if (++System.u8_InteFdCount[3] >= 100)
								{
									System.u8_InteFdCount[3] = 0;
									
									SystemMode.f_Fan = 0;
								}
								
								System.u8_InteFdCount[2] = 0;
							}
							
							System.u8_InteFdCount[4] = 0;
							System.u8_InteFdCount[5] = 0;							
						}
						else	//无风
						{
							if (SystemMode.f_Sleep)	
							{	
								if (System.u32_SleepCount >= 108000)	//3小时
								{
									Inte_SleepTempDelta = -30;				//-3℃
								}								
								else if (System.u32_SleepCount >= 72000)	//2小时
								{
									Inte_SleepTempDelta = -20;				//-2℃
								}
								else if (System.u32_SleepCount >= 36000)	//1小时
								{
									Inte_SleepTempDelta = -10;				//-1℃
								}
								else
								{
									Inte_SleepTempDelta = 0;
								}							
							}
							else
							{
								Inte_SleepTempDelta = 0;
							}							
							
							
							if (T1.s16_ValueMul10 >= (200/*+Inte_SleepTempDelta*/))	//P204
							{
								if (++System.u8_InteFdCount[4] >= 100)
								{
									System.u8_InteFdCount[4] = 0;
									
									SystemMode.f_Fan = 1;
								}
								
								System.u8_InteFdCount[5] = 0;
							}
							else if (T1.s16_ValueMul10 <= (180+Inte_SleepTempDelta))	//P206
							{
								if (++System.u8_InteFdCount[5] >= 100)
								{
									System.u8_InteFdCount[5] = 0;
									
									SystemMode.f_Heat = 1;
								}
								
								System.u8_InteFdCount[4] = 0;
							}
							else
							{
								System.u8_InteFdCount[4] = 0;
								System.u8_InteFdCount[5] = 0;							
							}
							
							System.u8_InteFdCount[2] = 0;
							System.u8_InteFdCount[3] = 0;
						}
						
						System.u8_InteFdCount[0] = 0;
						System.u8_InteFdCount[1] = 0;
					}
				}
			}
		}break;
		
		case	ENUM_SYSMODE_HEAT:       //制热
		{
			Inte_SleepTempDelta = 0;
			Protect.f_T2Cold = 0;
			if (SystemMode.f_Heat == 0)
			{
//				if (T1.f_Error == 0)
//				{
//					if (T1.s16_ValueMul10bc >= (TempValueMul10(Tempr.u8_TempCSet) + 0))
//					{
//						//SystemMode.f_TempCEC = 1;   //lcx del 20240628 转换模式进去，要清除达温停机。重新计时进入条件。							
//					}
//				}	
				SystemMode.f_ConTemp = 0; //lcx add 20240628 转换模式进去，要清除达温停机。重新计时进入条件。
				
			}

//			if ((SystemMode.f_ColdBak == 1)	||(SystemMode.f_FanBak))	//制冷切换制热
//			{
//				Comp.f_Delay2min = 1;	//2min
//				EAHeater.f_ColdToHeat = 1;		//制冷转制热
//			}
			
			SystemMode.f_Cold = 0;
			SystemMode.f_Heat = 1;
			SystemMode.f_Fan = 0;
			SystemMode.f_Auto = 0;
			
			if ((SystemMode.f_PerTest == 1) && (Tempr.u8_TempCSet == 17))
			{
				Comp.f_AppOn = ON;
			}	
			else if ((T1.f_Error == 1) || (T2.f_Error == 1) || (T3.f_Error == 1) 
			|| (T4.f_Error == 1) || (Tp.f_Error == 1))
			{
				Comp.f_AppOn = OFF;
				Comp.u16_RunMinDelay = 0;		//故障清0
			}
			else if (Defrost.u8_Step == 2)
			{
				Comp.f_AppOn = ON;
				Comp.u16_RunMinDelay = 0;		//故障清0
			}
			else
			{		
				if (System.u8_PowerOn_Count >= 10)	//上电1s后才判断
				{
					if (SystemMode.f_TempCEC == 0)
					{
						if ((T5.s16_ValueMul10bc  <= (TempValueMul10(Tempr.u8_TempCSet) - (U8)(FtyPara.u16L2))))
//						&& (Comp.u16_RestartDelay == 0)&& (Fan.Outdoor.u16_Delay == 0))
						{
							
							CirculationPump.f_AppOn = ON;
							if (CirculationPump.u16_RunCnt >= 300)
							{
								Fan.Outdoor.f_AppOn = ON;
							}
						}
						else if (((T5.s16_ValueMul10bc >= (TempValueMul10(Tempr.u8_TempCSet)))
						&& (Comp.u32_StopContCount >= 10))
						|| (Protect.T2HeatStatus != ENUM_PROSTATUS_NORMAL))
						{
							Fan.Outdoor.f_AppOn = OFF;
							if (Comp.u32_StopContCount >= 300)
							{
								CirculationPump.f_AppOn = OFF;
							}
						}
						
//						if ((Comp.f_DrvOn == OFF) || (Fan.Outdoor.f_AppOn == 0))
						if ((Fan.Outdoor.f_AppOn == 0) 
						|| (T5.s16_ValueMul10bc >= (TempValueMul10(Tempr.u8_TempCSet)))) //#test
						{
							Comp.f_AppOn = OFF;				//关压缩机
						}
						else if (Fan.Outdoor.f_AppOn)
						{
							Comp.f_AppOn = ON;
						}
					}
				}
			}

//			if (Comp.f_AppOn) 
			{	
				if ((T2.s16_ValueMul10 < 250)&& (Fan.Indoor.f_ForceLow))
				{
					if (Fan.Indoor.f_AppOn == ON)
					{
						Fan.Indoor.u16_Delay = 150;
					}
					Fan.Indoor.f_AppOn = OFF;
				}
				else if (EAHeater.f_DrvOn == ON)
				{
					Fan.Indoor.f_AppOn = ON;
				}
				else if (Protect.f_HighPress 
				|| Protect.f_LowPress || Protect.f_Tp || Protect.f_CompCurr
				|| (Protect.PhaseSeqStatus == ENUM_PROSTATUS_PROTECT)
				|| !Comp.f_HeatFirstOn)		//T2过低停内风机
				{
					Fan.Indoor.f_AppOn = OFF;
				}
				else 	//TBD 上电首次进入制热时压缩机未开时，风机不能开，待优化
				{
					Fan.Indoor.f_AppOn = ON;
				}
//				else if (Comp.f_DrvOn == ON)
//				{
//					Fan.Indoor.f_AppOn = ON;
//				}
//				else
//				{				
//					Fan.Indoor.f_AppOn = OFF;
//				}
							
			}
//			else			   
//			{	
//				Fan.Indoor.f_AppOn = ON;
//				if (Fan.Indoor.u16_Delay == 0)	//延时完毕才能关
//				{
//					Fan.Indoor.f_AppOn = OFF;
//				}
//			}

				
			FourWay.f_AppOn = ON;
			
			WPMotor.f_AppOn = OFF;		//关打水电机
//			EAHeater.f_AppOn = ON;		//电辅热开启
		}break;
		
		default: break;
	}

	if(System.Mode != ENUM_SYSMODE_HUM) //除湿T1低温保护清除  //lcx add  20240620 Protect.f_HumiT1Low
	{
		Protect.f_HumiT1Low = 0;
	}

	if (System.u8_PowerOn_Count >= 10)	//上电1s后才判断
	{
		if ((T1.f_Error == 0) && (T2.f_Error == 0) && (T3.f_Error == 0) && (T4.f_Error == 0) && (Tp.f_Error == 0))
		{
			if ((SystemMode.f_Cold == 1) || (SystemMode.f_Heat == 1))
			{
				if ((Comp.f_DrvOn == OFF) && (Tempr.T1TSDeltaZone < ENUM_TEMPDELTAZONE_G) && (Tempr.T1TSDeltaZone != ENUM_TEMPDELTAZONE_INIT))
				{
					if ((Protect.T2ColdStatus != ENUM_PROSTATUS_PROTECT) && (Tempr.T2HeatZone != ENUM_TEMPT2HEATZONE_PRO) && 
						(Protect.T3ColdStatus != ENUM_PROSTATUS_PROTECT) && 
						(Tempr.T4CoolZone != ENUM_TEMPT4COOLZONE_STOP) && (Tempr.T4CoolZone != ENUM_TEMPT4COOLZONE_PRO) && (Tempr.T4CoolZone != ENUM_TEMPT4COOLZONE_PRO1) &&
						(Tempr.T4HeatZone != ENUM_TEMPT4HEATZONE_PRO) && (Tempr.T4HeatZone != ENUM_TEMPT4HEATZONE_PRO1) &&
						(Protect.TpStatus != ENUM_PROSTATUS_PROTECT) &&			
						(Protect.CurrColdStatus != ENUM_PROSTATUS_PROTECT) && (Protect.CurrHeatStatus != ENUM_PROSTATUS_PROTECT) &&
						(Protect.CompCurrStatus != ENUM_PROSTATUS_PROTECT) && (Protect.f_HumiT1Low != 1)) //满足开压缩机 //lcx add  20240620 Protect.f_HumiT1Low
					{
						Comp.f_AppOn = ON;
						SystemMode.f_TempCEC = 0;	
					}			
				}
			}
		}
	}
	
	//制冷制热相互切换时停止压缩机
	if ((SystemMode.f_ColdBak != SystemMode.f_Cold) && (SystemMode.f_HeatBak != SystemMode.f_Heat))
	{
		Comp.f_AppOn = OFF;
		Comp.u16_RunMinDelay = 0;
	}
	
	//退出制热需求关闭四通阀
	if (SystemMode.f_HeatBak != SystemMode.f_Heat)	
	{
		if (SystemMode.f_Heat == 0)
		{			
			FourWay.f_AppOn = OFF;
		}
	}
	
	//水满停机
//	if (WaterBox.f_Full)
	//高压低压保护停机
	if (Protect.f_HighPress || Protect.f_LowPress || Protect.f_Tp
	||Protect.f_CompCurr || (Protect.PhaseSeqStatus == ENUM_PROSTATUS_PROTECT)
	||Protect.f_WaterFlow)
	{
		Comp.f_AppOn = OFF;				//关压缩机
		Fan.Indoor.f_AppOn = OFF;		//关内风机（规格书描述水满故障负载全关）
		Fan.Outdoor.f_AppOn = OFF;		//关外风机
		WPMotor.f_AppOn = OFF;			//关打水电机
		FourWay.f_AppOn = OFF;			//关机需求关闭四通阀
		EAHeater.f_AppOn = OFF;			//关电加热
		UVC.f_AppOn = OFF;				//关闭UVC	
		SV.f_AppOn	= OFF;				//关闭喷液阀
		SyncFan.f_AppOn = OFF;			//关闭同步电机
		CirculationPump.f_AppOn = OFF;	//
		Crank.f_AppOn = OFF;
		WFV.f_AppOn = OFF;
		Comp.u16_RunMinDelay = 0;		//停机清0		

		//--------------------------------------------------------------------------
		//lcx add 20240704
		SystemMode.f_TempCEC = 0;		//退出达温停机
		SystemMode.f_ConTemp = 0;		//重新判定何时进入恒温
		SystemMode.f_RoughCon = 0;		//重新默认从精细调节开始

		Tempr.u16_T1TSDeltaCount = 0;	//重新计时
		Tempr.u16_RoughCount = 0;		//重新计时
		Tempr.u16_RoughEnCount = 0; 	//重新计时	
		//--------------------------------------------------------------------------
	}
	
	SystemMode.f_ColdBak = SystemMode.f_Cold;
	SystemMode.f_FanBak = SystemMode.f_Fan;
	if ((SystemMode.f_HeatBak != SystemMode.f_Heat) && (SystemMode.f_Heat == 0))
	{
		Defrost_Init();										//化霜相关变量初始化
	}
	SystemMode.f_HeatBak = SystemMode.f_Heat;	
		
}
/****************************************************************************************************
Function Name       :void App_Status_BussCheck(void)
Description         :商检
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Status_BussCheck(void)
{
	//商检上下风机默认运行
	Fan.Indoor.f_AppOn = ON;
	Fan.Outdoor.f_AppOn = ON;

	//模式确定
	if (System.Mode == ENUM_SYSMODE_COLD)
	{
		SystemMode.f_Cold = 1;
		SystemMode.f_Heat = 0;
	}
	else
	{
		SystemMode.f_Cold = 0;
		SystemMode.f_Heat = 1;	
	}
	

	if (SystemMode.f_Cold == 1)
	{
		Comp.u8_TargetHZ = 60;	//60HZ
		
		FourWay.f_AppOn = OFF;	//四通阀控制关闭
		
		if (Comp.f_DrvOn == ON)	
		{
			WPMotor.f_AppOn = ON;	//打水电机打开
		}
		else
		{
			WPMotor.f_AppOn = OFF;	//打水电机关闭	
		}
		
		WPMotor.u16_CompOnDelay = 0;//打水电机立即工作
		
//		EAHeater.f_AppOn = OFF;		//电辅热关闭
	}
	else if (SystemMode.f_Heat == 1)
	{
		Comp.u8_TargetHZ = 50;	//50HZ
		
		FourWay.f_AppOn = ON;	//四通阀控制打开
		WPMotor.f_AppOn = OFF;	//打水电机关闭	
		
//		EAHeater.f_AppOn = ON;		//热泵开启
	}
	
	//压缩机控制
	if ((SystemMode.f_ColdBak != SystemMode.f_Cold) || (SystemMode.f_HeatBak != SystemMode.f_Heat))	//切换模式需关压缩机
	{
		Comp.f_AppOn = OFF;
	}
	else
	{
		Comp.f_AppOn = ON;
	}
    Comp.u16_RunMinDelay = 0;	//没有最小运行时间
	

	UVC.f_FuncOn = ON;
	UVC.f_AppOn = ON;
	WiFi.f_FuncOn = ON;
	WiFi.f_AppOn = ON;


	SystemMode.f_ColdBak = SystemMode.f_Cold;
	SystemMode.f_HeatBak = SystemMode.f_Heat;	
	
	if (System.u16_BussChkCount >= 18000)	//30min
	{
		System.u16_BussChkCount = 0;
		DisplayBoardTurnOff();
	}
}
/****************************************************************************************************
Function Name       :void App_Status_SelCheck(void)
Description         :自检
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Status_SelCheck(void)
{

    
}
/****************************************************************************************************
Function Name       :void App_Event_10ms(void)
Description         :10ms运行一次函数
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Event_10ms(void)
{


}
/****************************************************************************************************
Function Name       :void App_Event_100ms(void)
Description         :100ms运行一次函数
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Event_100ms(void)
{
	Timer_Run();
	TimerUVC_Run();
	
	if (Comp.u16_RestartDelay > 0)					Comp.u16_RestartDelay -= 1;	
	
//	if (((StepMotor.var.u8_status >= ENUM_STEPMOTOR_STATUS_RUN) && (StepMotor.var.u8_run >= ENUM_STEPMOTOR_POSITION_ONOK)) ||	//等待摆风口打开 
//		(System.Enum_Status == ENUM_STATUS_OFF))//或待机
//	{
		if (Fan.Indoor.u16_Delay > 0)				Fan.Indoor.u16_Delay -= 1;		
//	}	

	//四通阀
	if ((Comp.f_DrvOn != FourWay.f_DrvOn) || ((SystemMode.f_Cold == 0) && (SystemMode.f_Heat == 0)))
	{
		if (FourWay.u16_Delay > 0)					FourWay.u16_Delay -= 1;
	}
	
	//散热风扇
	if (DCFan.u16_Delay > 0)   						DCFan.u16_Delay -= 1;
	
	if (System.u8_PowerOn_Count < 0xFF)				System.u8_PowerOn_Count += 1;
			
//	if (++System.u16_SenseCount >= 15000)	//连续25分钟没有接收到随身感纠正值自动退出随身感功能
//	{
//		System.u16_SenseCount = 0;
//		System.f_Sense = 0;
//		Tempr.u8_TempSense = 0;
//	}	
	
	if (System.Enum_Status == ENUM_STATUS_ON)
	{
		if (Tempr.u16_T1TSDeltaCount < 0xFFFF)		Tempr.u16_T1TSDeltaCount += 1;
		
		if (Tempr.u16_RoughEnCount < 0xFFFF)		Tempr.u16_RoughEnCount += 1;
		
		if (Tempr.u16_RoughCount < 0xFFFF)			Tempr.u16_RoughCount += 1;
		
		if (Swing.u16_AntiDewCount < 0xFFFF)		Swing.u16_AntiDewCount += 1;				
		
		if (Fan.Outdoor.u16_Delay > 0)				Fan.Outdoor.u16_Delay -= 1;
		
		if (Comp.u8_PowerOnDelay > 0)				Comp.u8_PowerOnDelay -= 1;

		if (SystemMode.f_Heat == 1)
		{
			if (Comp.f_AppOn == 1 && Comp.f_DrvOn == 1) Defrost.f_CompHasRun = 1; //lcx add 进入制热后，记录压机运行过标志
			
			if (Defrost.f_Enable == 0)
			{
				//转换模式时已执行 Defrost_Init(); //化霜相关变量初始化
				if(Defrost.f_CompHasRun == 1) //增加【压缩机开启后开始计时，中途不管有没有达温停机，故障停机，开关机】这个条件  lcx add 20240711
				{			
					if (Defrost.u16_FindT30_Count < 0xFFFF)		Defrost.u16_FindT30_Count += 1;
					if (Defrost.u16_HeatRun_Count < 0xFFFF) 	Defrost.u16_HeatRun_Count += 1;
				}

				if (Defrost.f_T30Found) //找到T30后u16_DefCase3_Count才开始计时  //lcx add 20240618
				{
					if(Comp.f_AppOn && Comp.f_DrvOn) //增加压缩机连续开计时 lcx add
					{
						if (Defrost.u16_DefCase3_Count < 0xFFFF)	Defrost.u16_DefCase3_Count += 1;
					}
					else
					{
						Defrost.u16_DefCase3_Count = 0;
					}
				}
				else
				{
					Defrost.u16_DefCase3_Count = 0;
				}
				
			}
			else
			{
				if (!((Comp.f_DrvOn == OFF) && (Defrost.u8_Step == 2))) 
				{//化霜过程中压缩机停机不计时
					if (Defrost.u16_DefQCase2_Count < 0xFFFF)	Defrost.u16_DefQCase2_Count += 1;
					
					if (Defrost.u16_Defrosting_Count < 0xFFFF)	Defrost.u16_Defrosting_Count += 1;
					
					if (Defrost.u16_Step_Delay > 0)				Defrost.u16_Step_Delay -= 1;
				}
			}
		}
		
//		if (SystemMode.f_Sleep == 1)	//睡眠
//		{
//			if (System.u32_SleepCount < 0xFFFFFFFF)	//最大计时0xFFFFFFFF小时
//			{
//				System.u32_SleepCount += 1;
//								
//				//睡眠情况调整设定值
//				if ((SystemMode.f_Heat == 1) || ((SystemMode.f_Fan == 0) && (SystemMode.f_Heat == 0) && (SystemMode.f_Cold == 0)))		//制热/无风
//				{
//					if (System.u32_SleepCount <= 108000)		//108000睡眠制热3小时内有变化
//					{
//						if (System.u32_SleepCount == 108000)		//108000睡眠制热3小时设定值减少3℃
//						{
//							if (Tempr.u8_TempCSet > 13)
//							{
//								Tempr.u8_TempCSet -= 1;
//							}
//						}
//						else if (System.u32_SleepCount == 72000)	//72000睡眠制热2小时设定值减少2℃
//						{
//							if (Tempr.u8_TempCSet > 13)
//							{
//								Tempr.u8_TempCSet -= 1;
//							}
//						}
//						else if (System.u32_SleepCount == 36000)	//36000睡眠制热1小时设定值减少1℃
//						{
//							if (Tempr.u8_TempCSet > 13)
//							{
//								Tempr.u8_TempCSet -= 1;
//							}
//						}
//						
//					}					
//				}
//				else if ((SystemMode.f_Cold == 1) || (SystemMode.f_Fan == 1))	//制冷/送风
//				{
//					if (System.u32_SleepCount <= 72000)		//睡眠制冷2小时内有变?
//					{
//						if (System.u32_SleepCount == 72000)			//睡眠制冷2小时设定值增加2℃
//						{
//							if (System.Mode == ENUM_SYSMODE_HUM)
//							{	
//								if (Tempr.u8_HumiCSet < 32)
//								{
//									Tempr.u8_HumiCSet += 1;
//								}
//							}
//							else
//							{
//								if (Tempr.u8_TempCSet < 32)
//								{
//									Tempr.u8_TempCSet += 1;
//								}
//							}							
//						}
//						else if (System.u32_SleepCount == 36000)	//睡眠制冷1小时设定值增加1℃
//						{
//							if (System.Mode == ENUM_SYSMODE_HUM)
//							{	
//								if (Tempr.u8_HumiCSet < 32)
//								{
//									Tempr.u8_HumiCSet += 1;
//								}
//							}
//							else
//							{
//								if (Tempr.u8_TempCSet < 32)
//								{
//									Tempr.u8_TempCSet += 1;
//								}
//							}
//						}
//					}					
//				}				
//				
//			}
//					
//			if (++System.u32_SleepTimCount >= 288000)	//睡眠最长运行8小时后
//			{
//				System.u32_SleepTimCount = 0;
//				
//				Tempr.u8_TempCSet = Tempr.u8_TempCSetSleep;
//				Tempr.u8_TempFSet = Tempr.u8_TempFSetSleep;
//				Tempr.u8_TempCSetSleep = 0;
//				Tempr.u8_TempFSetSleep = 0;					
//				
//				DisplayBoardTurnOff();//关机
//				
//			}	
//		}
		
		
		//压缩机
		if (Comp.f_DrvOn)
		{			
			if (Comp.u16_RunMinDelay > 0)			Comp.u16_RunMinDelay -= 1;			
			
			if (WPMotor.u16_CompOnDelay > 0)		WPMotor.u16_CompOnDelay -= 1;
				
			if (Comp.u16_StartInitDelay > 0)		//3分钟启动过程	
			{
				Comp.u16_StartInitDelay  -= 1;
				if (Comp.u16_StartInitDelay == 0)
				{
					SystemMode.f_ConTemp = 0;		//重新判定何时进入恒温
					SystemMode.f_RoughCon = 0;		//重新默认从精细调节开始
				}
			}
			if (Comp.u32_RunContCount < 0xFFFFFFFF)
			{
				Comp.u32_RunContCount ++;
			}
			Comp.u32_StopContCount = 0;
		}
		else 
		{
			Comp.u32_RunContCount = 0;
			if (Comp.u32_StopContCount < 0xFFFFFFFF)
			{
				Comp.u32_StopContCount ++;
			}
		}

		
		//内风机
		if ((Fan.Indoor.f_DrvOn == ON) && (SystemMode.f_TempCEC == 0) && (T1.f_Error == 0) && (T2.f_Error == 0) && (T3.f_Error == 0) && (T4.f_Error == 0) && (Tp.f_Error == 0))
		{
			Fan.Indoor.u16_Count = 0;
		}
		else
		{
			if (Fan.Indoor.u16_Count < 0xFFFF)		Fan.Indoor.u16_Count += 1;
		}
		
		//外风机
		if (Fan.Outdoor.f_DrvOn == ON)
		{
			if (Comp.u8_SelTestDelay > 0)		Comp.u8_SelTestDelay -= 1;
		}

		if (Fan.Outdoor.f_DrvOn == OFF)
		{
			Fan.Outdoor.u16_Count = 0;
		}
		else
		{
			if (Fan.Outdoor.u16_Count < 0xFFFF)		Fan.Outdoor.u16_Count += 1;
		}
		
		if (SystemMode.f_Force)
		{
			if (System.u32_ForceRunCount < 72000)	//2小时
			{
				System.u32_ForceRunCount += 1;
			}
		}
		
	}
	else if (System.Enum_Status == ENUM_STATUS_OFF)
	{
		
		if (Fan.Outdoor.u16_Delay > 0)				Fan.Outdoor.u16_Delay -= 1;
		
		if (System.u16_OffCount < 0xFFFF)
		{
			System.u16_OffCount += 1;
		}
	}
	else if (System.Enum_Status == ENUM_STATUS_BUSSCHK)
	{
		if (System.u16_BussChkCount < 0xFFFF)
		{
			System.u16_BussChkCount += 1;
		}
	}

	if (CirculationPump.f_DrvOn)
	{
		CirculationPump.u16_StopCnt = 0;
		if (CirculationPump.u16_RunCnt < 0xFFFF)
		{
			CirculationPump.u16_RunCnt += 1;
		}
	}	
	else 
	{
		CirculationPump.u16_RunCnt = 0;
		if (CirculationPump.u16_StopCnt < 0xFFFF)
		{
			CirculationPump.u16_StopCnt += 1;
		}
	}

	
	if (EAHeater.u16_Delay > 0) 
	{
		EAHeater.u16_Delay --;
	}

	
	
	if (T1.f_Error == 1)
	{
		if (T1.u16_ErrCount < 0xFFFF)
		{
			T1.u16_ErrCount += 1;
		}
	}
	else
	{
		T1.u16_ErrCount = 0;
	}
	
	if (T2.f_Error == 1)
	{
		if (T2.u16_ErrCount < 0xFFFF)
		{
			T2.u16_ErrCount += 1;
		}
	}
	else
	{
		T2.u16_ErrCount = 0;
	}	
	
	if (T3.f_Error == 1)
	{
		if (T3.u16_ErrCount < 0xFFFF)
		{
			T3.u16_ErrCount += 1;
		}
	}
	else
	{
		T3.u16_ErrCount = 0;
	}	

	if (T4.f_Error == 1)
	{
		if (T4.u16_ErrCount < 0xFFFF)
		{
			T4.u16_ErrCount += 1;
		}
	}
	else
	{
		T4.u16_ErrCount = 0;
	}	
	
	if (Tp.f_Error == 1)
	{
		if (Tp.u16_ErrCount < 0xFFFF)
		{
			Tp.u16_ErrCount += 1;
		}
	}
	else
	{
		Tp.u16_ErrCount = 0;
	}	
}
/****************************************************************************************************
Function Name       :void HumiCSetInit(void)
Description         :功能函数
Input               :无
Return              :无
Author              :lcx
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	Func_HumiCSetInit(void)
{
	//lcx add 20240517 //上电后Tempr.u8_HumiCSet = 0，要重新设定湿度。
	//lcx add 20240705 //调整T1然后关机。开关机后Tempr.u8_HumiCSet 停留在上第一次进除湿的值，要重新设定湿度。	
	if(System.Enum_Status != ENUM_STATUS_ON || System.Mode != ENUM_SYSMODE_HUM || Tempr.u8_HumiCSet == 0)
	{
		System.f_HumiCSetInitOK = 0;
	}
}
/****************************************************************************************************
Function Name       :void App_Function(void)
Description         :功能函数
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Function(void)
{
//	Func_LowPower();	//低功耗处理
    //P_PowEn12V_On();	
	Func_Temprature();	//温度
//	Func_WaterBox();	//水箱
	Func_Protect();		//保护功能处理
//	Func_HumiCSetInit(); //除湿初值处理 lcx add
	

    switch (System.Enum_Status)
    {
        case	ENUM_STATUS_INIT	:	App_Status_Init();		break;	//上电初始化
        case	ENUM_STATUS_OFF		:	App_Status_Off();		break;	//待机
        case	ENUM_STATUS_ON		:	App_Status_On();		break;	//开机
		case	ENUM_STATUS_BUSSCHK	:	App_Status_BussCheck();	break;	//自检
        case	ENUM_STATUS_SELCHK	:	App_Status_SelCheck();	break;	//自检

        default: break;
    }    

	Defrost_Con();		//化霜功能处理
	
//	Func_WPMotor();		//打水电机
//	Func_UVC();			//UVC	
//	Func_EAHeater();	//电辅热
//	Func_WiFiPowEn();	//WiFi电源控制
	
	Func_Comp();		//压缩机控制
	Func_Fan();			//风机控制
//	Func_DCFan();		//散热风扇控制
	Func_FourWay();		//四通阀
	
//	Swing_AntiDew();	//防凝露功能
	//美博空调
//	Func_SyncFan();
//	Func_SV();
	//美博空调

	//美博热水机
	Func_Crank();		//曲轴电加热
	Func_CirculationPump();			//循环泵
	Func_WFV();			//补水阀
	//美博热水机

}
