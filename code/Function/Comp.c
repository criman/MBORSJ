/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Comp.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/13
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_COMP    Comp;

/****************************************************************************************************
Function Name       :void    Init_Comp(void)
Description         :压缩机初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_Comp(void)
{
    P_Comp_Off();  
    P_Comp_Output();	
	P_Comp_Dispull();	
}


/****************************************************************************************************
Function Name       :void    App_Comp_RunHzInitIndex(void)
Description         :压缩机启动频率档次判断
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_RunHzInitIndex(void)
{
	S16  s16_TempSetMul10;	//设定值乘以10
	
	if (System.Mode == ENUM_SYSMODE_HUM)	//除湿按设定值T1-2℃
	{
		s16_TempSetMul10 = TempValueMul10(Tempr.u8_HumiCSet);
	}
	else
	{
		s16_TempSetMul10 = TempValueMul10(Tempr.u8_TempCSet);
	}
	
	if (SystemMode.f_Heat == 1)		//制热
	{
		if (Defrost.f_Enable == 0)	//非化霜情况
		{
			if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc + 35))
			{
				Comp.u8_InitIndex = 15;		//EE:START_HF_A→FH15
			}
			else if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc + 30))
			{
				Comp.u8_InitIndex = 14;		//EE:START_HF_B→FH14
			}
			else if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc + 25))
			{
				Comp.u8_InitIndex = 12;		//EE:START_HF_C→FH12
			}
			else if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc + 20))
			{
				Comp.u8_InitIndex = 10;		//EE:START_HF_D→FH10
			}	
			else if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc + 15))
			{
				Comp.u8_InitIndex = 8;		//EE:START_HF_E→FH8
			}
			else if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc + 10))
			{
				Comp.u8_InitIndex = 7;		//EE:START_HF_F→FH7
			}
			else if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc + 5))
			{
				Comp.u8_InitIndex = 5;		//EE:START_HF_G→FH5
			}
			else if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc + 0))
			{
				Comp.u8_InitIndex = 0;		//EE:START_HF_H→FH0
			}
			else if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc - 5))
			{
				Comp.u8_InitIndex = 0;		//EE:START_HF_I→FH0
			}
			else //if (s16_TempSetMul10 >= (T1.s16_ValueMul10bc - 10))
			{
				Comp.u8_InitIndex = 0;		//EE:START_HF_J→FH0
			}
		}
		else
		{
			//EE.PARA. C_REMEMBER_PARA10_00;		//10		    //化霜过程最大运行频率档位
			if ((EEP.u8_rdBuf[125] > 0) && (EEP.u8_rdBuf[125] <= 15))	//合理范围	
			{
				Comp.u8_InitIndex = EEP.u8_rdBuf[125];
			}
			else
			{
				//异常给定常数
				Comp.u8_InitIndex = 10;
			}
		}
	}
	else if (SystemMode.f_Cold)		//制冷
	{
		if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 + 35))
		{
			Comp.u8_InitIndex = 15;		//EE:START_CF_A→FC15
		}
		else if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 + 30))
		{
			Comp.u8_InitIndex = 13;		//EE:START_CF_B→FC13
		}
		else if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 + 25))
		{
			Comp.u8_InitIndex = 11;		//EE:START_CF_C→FC11
		}
		else if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 + 20))
		{
			Comp.u8_InitIndex = 9;		//EE:START_CF_D→FC9
		}
		else if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 + 15))
		{
			Comp.u8_InitIndex = 7;		//EE:START_CF_E→FC7
		}
		else if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 + 10))
		{
			Comp.u8_InitIndex = 6;		//EE:START_CF_F→FC6
		}
		else if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 + 5))
		{
			Comp.u8_InitIndex = 4;		//EE:START_CF_G→FC4
		}
		else if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 + 0))
		{
			Comp.u8_InitIndex = 0;		//EE:START_CF_H→FC0
		}
		else if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 - 5))
		{
			Comp.u8_InitIndex = 0;		//EE:START_CF_I→FC0
		}
		else	//if (T1.s16_ValueMul10bc >= (s16_TempSetMul10 - 10))
		{
			Comp.u8_InitIndex = 0;		//EE:START_CF_J→FC0
		}
	}
	
	//20231122
	if (SystemMode.f_Cold == 1)
	{
		if (System.Mode == ENUM_SYSMODE_HUM)
		{
			Comp.u8_InitIndex = 8;	//20231122 除湿 频率FC8
		}
		
		Comp.u8_TargetSrc = Comp.u8_Cold_TargetHZ[Comp.u8_InitIndex];
	}
	else if (SystemMode.f_Heat == 1)
	{
		Comp.u8_TargetSrc = Comp.u8_Heat_TargetHZ[Comp.u8_InitIndex];
	}
	else
	{
		Comp.u8_TargetSrc = 0;
	}
	
	Comp.u8_TargetHZ = Comp.u8_TargetSrc;
	Comp.u8_TargetFreq = Comp.u8_TargetHZ;	
}
/****************************************************************************************************
Function Name       :void    App_Comp_T1TSDelta(void)
Description         :T1/TS温差频率控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_T1TSDelta(void)
{
	S16  s16_TempSetMul10;	//设定值乘以10
	
	if (System.Mode == ENUM_SYSMODE_HUM)	//除湿按设定值进入除湿时的ST=T1-2
	{
		s16_TempSetMul10 = TempValueMul10(Tempr.u8_HumiCSet);
	}
	else
	{
		s16_TempSetMul10 = TempValueMul10(Tempr.u8_TempCSet);	//*10
	}
	
	if (Comp.u16_StartInitDelay == 0)						//启动目标频率结束
	{
		if (SystemMode.f_ConTemp == 0)						//非恒温状态下,判定何时进入恒温
		{				
			if (SystemMode.f_Cold == 1)						//制冷时
			{					
				if (T1.s16_ValueMul10bc < s16_TempSetMul10)	//室内温度低于用户设定温度	
				{
					SystemMode.f_ConTemp = 1;				//进入恒温
				}
			}
			else if (SystemMode.f_Heat == 1)				//制热时
			{
				if (T1.s16_ValueMul10bc > s16_TempSetMul10)	//室内温度高于用户设定温度
				{
					SystemMode.f_ConTemp = 1;				//进入恒温
				}				
			}
			
			Tempr.u16_T1TSDeltaCount = 0;					//重新计时
			Tempr.u16_RoughCount = 0;						//重新计时
			Tempr.u16_RoughEnCount = 0;						//重新计时
			
			Comp.u8_TargetHZ = Comp.u8_TargetSrc;
		}
		else												//恒温进行中,判定何时退出恒温
		{
			if (SystemMode.f_RoughCon == 0)					//精细调节
			{
				if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_J)	//J区间
				{
					if (Tempr.u16_T1TSDeltaCount >= 1200)			//每隔2分钟
					{
						Tempr.u16_T1TSDeltaCount = 0;
						Comp.u8_TargetHZ = Comp.u8_TargetFreq;					
						Comp.u8_TargetHZ -= 1;		//下降1Hz
					}
				}
				else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_I)	//I区间
				{
					if (Tempr.u16_T1TSDeltaCount >= 3000)			//每隔5分钟
					{
						Tempr.u16_T1TSDeltaCount = 0;
						Comp.u8_TargetHZ = Comp.u8_TargetFreq;						
						Comp.u8_TargetHZ -= 1;		//下降1Hz
					}					
				}
				else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_F)	//F区间
				{
					if (Tempr.u16_T1TSDeltaCount >= 3000)			//每隔5分钟
					{
						Tempr.u16_T1TSDeltaCount = 0;
						Comp.u8_TargetHZ = Comp.u8_TargetFreq;						
						Comp.u8_TargetHZ += 1;		//上升1Hz
					}					
				}
				else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_E)	//E区间
				{
					if (Tempr.u16_T1TSDeltaCount >= 1200)			//每隔2分钟
					{
						Tempr.u16_T1TSDeltaCount = 0;
						Comp.u8_TargetHZ = Comp.u8_TargetFreq;					
						Comp.u8_TargetHZ += 1;		//上升1Hz
					}					
				}
				else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_K)	//K区间
				{
					if ((Tempr.u16_T1TSDeltaCount % 1200) == 1199)		//每2分钟下降3HZ(第1个分钟下降1HZ，第2个分钟下降2HZ)
					{
						Tempr.u16_T1TSDeltaCount += 1;  				//避免连续响应
						Comp.u8_TargetHZ = Comp.u8_TargetFreq;						
						Comp.u8_TargetHZ -= 2;		//下降2Hz
					}
					else if ((Tempr.u16_T1TSDeltaCount % 600) == 599)	//每1分钟下降1HZ
					{
						Tempr.u16_T1TSDeltaCount += 1;  				//避免连续响应
						Comp.u8_TargetHZ = Comp.u8_TargetFreq;						
						Comp.u8_TargetHZ -= 1;		//下降1Hz
					}
					 
								
					//5.2.2.4制冷达设定温度后控制逻辑	
			
					if (SystemMode.f_Cold == 1) //&& (!(SystemMode.f_Force && (System.u32_ForceRunCount < 72000))) && (!SystemMode.f_Sleep))	//制冷模式,不包含强力、睡眠功能
//					if (SystemMode.f_Cold == 1 && (!(SystemMode.f_Force && (System.u32_ForceRunCount < 72000))) && (!SystemMode.f_Sleep))	//制冷模式,不包含强力、睡眠功能 lcx add 20240617
					{		
						if ((Tempr.u16_T1TSDeltaCount >= 9000) || ((Tempr.u16_ZoneKT1Mul10 - T1.s16_ValueMul10bc) >= 10))	//超过15分钟或者室内温度下降超过1℃压缩机立即停机
						{
							//达温停压缩机
							Comp.f_AppOn = OFF;
							if (T1.f_Error == 0)
							{
								SystemMode.f_TempCEC = 1;
							}
						}
					}
					
					//制热达设定温度
					if (SystemMode.f_Heat == 1) //&& (!(SystemMode.f_Force &&(System.u32_ForceRunCount < 72000))) && (!SystemMode.f_Sleep))	//制热模式,不包含强力、睡眠功能
					{		
						if ((Tempr.u16_T1TSDeltaCount >= 18000) || ((T1.s16_ValueMul10bc - Tempr.u16_ZoneKT1Mul10) >= 10))	//超过15->30分钟或者室内温度下降超过1℃压缩机立即停机
						{
							//达温停压缩机
							Comp.f_AppOn = OFF;
							if (T1.f_Error == 0)
							{
								SystemMode.f_TempCEC = 1;
							}
						}
					}					
				}
				
				
				//判断是否进入粗略调节
				if (Tempr.u16_RoughEnCount < 18000)						//30分钟后不再检测判断
				{
					if (Tempr.T1TSDeltaZone >= ENUM_TEMPDELTAZONE_I)	//30分钟内进入温差区间I以下
					{
						Tempr.u16_RoughCount = 0;
						SystemMode.f_RoughCon = 1;						//进入粗略调节环节
					}
				}
			}
			else														//粗略调节
			{
				if ((Tempr.u16_RoughCount % 1800) == 1799)				//每3分钟降频3HZ
				{
					Tempr.u16_RoughCount = 0;
					Comp.u8_TargetHZ = Comp.u8_TargetFreq;
					Comp.u8_TargetHZ -= 3;
				}
				
//				if ((!(SystemMode.f_Force &&(System.u32_ForceRunCount < 72000))) && (!SystemMode.f_Sleep))	//制冷模式,不包含强力、睡眠功能
//				{
					if (SystemMode.f_Cold == 1) 
					{		
						if (System.Mode == ENUM_SYSMODE_HUM)	     //除湿
						{
							if (TempValueMul10(Tempr.u8_HumiCSet) >= (T1.s16_ValueMul10bc+20)) 	//达温补偿2℃	
							{
								//达温停压缩机
								Comp.f_AppOn = OFF;
								if (T1.f_Error == 0)
								{
									SystemMode.f_TempCEC = 1;
								}
							}					
						}
						else	//制冷
						{
							if (TempValueMul10(Tempr.u8_TempCSet) >= (T1.s16_ValueMul10bc+20)) 	//达温补偿2℃
							{
								//达温停压缩机
								Comp.f_AppOn = OFF;
								if (T1.f_Error == 0)
								{
									SystemMode.f_TempCEC = 1;
								}
							}
						}
					}
					else if (SystemMode.f_Heat == 1)	//制热
					{
						if (TempValueMul10(Tempr.u8_TempCSet) <= (T1.s16_ValueMul10bc-20)) 	//达温补偿2℃
						{
							//达温停压缩机
							Comp.f_AppOn = OFF;
							if (T1.f_Error == 0)
							{
								SystemMode.f_TempCEC = 1;
							}
						}					
					}						
//				}				
				
				
				//粗略调节退出条件
				if ((Tempr.T1TSDeltaZone >= ENUM_TEMPDELTAZONE_A) && (Tempr.T1TSDeltaZone <= ENUM_TEMPDELTAZONE_G))	//恢复至G区
				{
					SystemMode.f_RoughCon = 0;						//退出粗略调节环节
					Tempr.u16_RoughEnCount = 18000;					//不再进入粗略调节(除非退出恒温后再进入恒温)
				}
			}
			
			
			//温差等级在ABCD内退出恒温控制
			if ((Tempr.T1TSDeltaZone >= ENUM_TEMPDELTAZONE_A) && (Tempr.T1TSDeltaZone <= ENUM_TEMPDELTAZONE_D))	
			{
				SystemMode.f_ConTemp = 0;
				SystemMode.f_RoughCon = 0;

				Comp.u8_TargetHZ = Comp.u8_TargetSrc;	//回到A-D区间重新计时起始频率
			}
		}
					
	}
	else
	{
		if (SystemMode.f_Cold == 1)
		{
			if (System.Mode == ENUM_SYSMODE_HUM)
			{
				Comp.u8_TargetSrc = Comp.u8_Cold_TargetHZ[8];	//20231122 除湿 频率FC8
			}
			else
			{
				Comp.u8_TargetSrc = Comp.u8_Cold_TargetHZ[Comp.u8_InitIndex];
			}
		}
		else if (SystemMode.f_Heat == 1)
		{
			Comp.u8_TargetSrc = Comp.u8_Heat_TargetHZ[Comp.u8_InitIndex];
		}
		else
		{
			Comp.u8_TargetSrc = 0;
		}
		
		Comp.u8_TargetHZ = Comp.u8_TargetSrc;		
	}
}
/****************************************************************************************************
Function Name       :void    App_Comp_InDoorFan(void)
Description         :室内风速对压缩机运行频率的控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_InDoorFan(void)
{
	U8    u8_LimitFreqMax;	//限频最高频率	
	
	if (SystemMode.f_Cold == 1)		//制冷
	{
		if (Fan.Indoor.Level == ENUM_FANLEVEL_HIGH_S) 	//内风机强力风
		{
			//EE.PARA. C_REMEMBER_PARA06_00;	    //10	        //室内风机超高风时-E_
			if ((EEP.u8_rdBuf[100] > 0) && (EEP.u8_rdBuf[100] <= 15)) 	//合理范围内
			{
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[EEP.u8_rdBuf[100]];
			}
			else
			{
				//异常给定常数
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[10];	
			}
		}
		else if  (Fan.Indoor.Level == ENUM_FANLEVEL_HIGH)	//内风机高风
		{
			//EE.PARA. C_REMEMBER_PARA06_01;       //10	        //室内风机高风时-E_			
			if ((EEP.u8_rdBuf[101] > 0) && (EEP.u8_rdBuf[101] <= 15)) 	//合理范围内
			{
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[EEP.u8_rdBuf[101]];
			}
			else
			{
				//异常给定常数
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[10];	
			}		
		}
		else if (Fan.Indoor.Level == ENUM_FANLEVEL_MED)	 //内风机中档
		{
			//EE.PARA. C_REMEMBER_PARA06_02;       //8	       	    //室内风机中风时-E_
			if ((EEP.u8_rdBuf[102] > 0) && (EEP.u8_rdBuf[102] <= 15)) 	//合理范围内
			{
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[EEP.u8_rdBuf[102]];
			}
			else
			{
				//异常给定常数
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[8];	
			}				
		}
		else if (Fan.Indoor.Level == ENUM_FANLEVEL_LOW)	 //内风机中档和低档
		{
			if (System.Mode == ENUM_SYSMODE_HUM)
			{
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[8];		//除湿内风机低风档固定限频FC8,不在E方开放
			}
			else
			{
				//EE.PARA C_REMEMBER_PARA06_03;       //8	            //室内风机低风时-E_
				if ((EEP.u8_rdBuf[103] > 0) && (EEP.u8_rdBuf[103] <= 15)) 	//合理范围内
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[EEP.u8_rdBuf[103]];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[8];	
				}					
			}
		}
		else	//微风档
		{
			//EE.PARA. C_REMEMBER_PARA06_04;       //6	            //室内风机微风时-E_	
			if ((EEP.u8_rdBuf[104] > 0) && (EEP.u8_rdBuf[104] <= 15)) 	//合理范围内
			{				
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[EEP.u8_rdBuf[104]];
			}
			else
			{
				//异常给定常数
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[6];	
			}				
		}
		
		//制冷内风机档位限频
		if ((Comp.u8_TargetFreq > u8_LimitFreqMax) && (u8_LimitFreqMax != 0))			//MAX
		{
			Comp.u8_TargetFreq = u8_LimitFreqMax;
		}		
	}
	else if (SystemMode.f_Heat == 1)
	{
		//见函数 App_Comp_T2Heat
		;
	}
}
/****************************************************************************************************
Function Name       :void    App_Comp_T4(void)
Description         :室外温度对压缩机运行频率的控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_T4(void)
{
	U8    u8_LimitFreqMax;	//限频最高频率
	U8    u8_EEP_rdPara;
	
	if (Defrost.f_Enable == 0)		//化霜不受室外温度的限频控制
	{
		if (SystemMode.f_Cold == 1)
		{
			if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_11)
			{
				//EE.PARA. C_REMEMBER_PARA04_11;		//3		   		//55℃≤T	
				u8_EEP_rdPara = EEP.u8_rdBuf[85];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[2];		//FC2	
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_10)
			{
				//EE.PARA. C_REMEMBER_PARA04_10;		//3		   		//50℃≤T＜55℃
				u8_EEP_rdPara = EEP.u8_rdBuf[84];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];	
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[2];		//FC2
				}
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_9)
			{				
				//EE.PARA. C_REMEMBER_PARA04_09;		//3		   	 	//45℃≤T＜50℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[83];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[6];		//EE:FC6
				}											
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_8)
			{
				//EE.PARA. C_REMEMBER_PARA04_08;		//3		   		//40℃≤T＜45℃		
				u8_EEP_rdPara = EEP.u8_rdBuf[82];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[8];		//EE:FC8	
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_7)
			{
				//EE.PARA. C_REMEMBER_PARA04_07;		//10		    //33℃≤T＜40℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[81];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[10];	//EE:FC10	
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_6)
			{
				//EE.PARA. C_REMEMBER_PARA04_06;		//10		    //30℃≤T＜33℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[80];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[8];		//EE:FC8
				}
						
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_5)
			{
				//EE.PARA. C_REMEMBER_PARA04_05;		//10		    //25℃≤T＜30℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[79];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[6];		//EE:FC6
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_4)
			{
				//EE.PARA. C_REMEMBER_PARA04_04;		//9		   		//20℃≤T＜25℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[78];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[5];		//EE:FC5
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_3)
			{
				//EE.PARA. C_REMEMBER_PARA04_03;		//8		   		//15℃≤T＜20℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[77];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[4];		//EE:FC4	
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_2)
			{
				//EE.PARA. C_REMEMBER_PARA04_02;		//6		   		//10℃≤T＜15℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[76];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[3];		//EE:FC3
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_1)
			{
				//EE.PARA. C_REMEMBER_PARA04_01;		//4		   		//0℃≤T＜10℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[75];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[2];		//EE:FC2
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_0)
			{
				//EE.PARA. C_REMEMBER_PARA04_00;		//3		   		//T＜0℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[74];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[2];		//EE:FC2	
				}					
			}
			else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_STOP)
			{
				u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[0];		//EE:FC0	
				
				//指示保护代码
				//保护代码高于T4_COOL0时恢复
			}
			


			//外环温小于17℃最小频率不能低于30HZ
			if (SystemMode.f_PerTest == 0)
			{
				if (T4.s16_ValueMul10 < 170)
				{
					if (Comp.u8_TargetFreq < 30)
					{
						Comp.u8_TargetFreq = 30;
					}
					
					if (Comp.u8_TargetHZ < 30)
					{
						Comp.u8_TargetHZ = 30;
					}					
				}
			}
		}
		else if (SystemMode.f_Heat == 1)	//制热
		{
			if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_0)
			{
				//EE.PARA C_REMEMBER_PARA05_00;        //10	        //T＜-19℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[86];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];
				}					
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_1)
			{
				//EE.PARA C_REMEMBER_PARA05_01;        //10	        //-19℃≤T＜-10℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[87];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];
				}
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_2)
			{
				//EE.PARA. C_REMEMBER_PARA05_02;        //10	        //-10℃≤T＜-7℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[88];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}				
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];
				}					
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_3)
			{
				//EE.PARA. C_REMEMBER_PARA05_03;        //10	        //-7℃≤T＜-3℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[89];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];
				}					
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_4)
			{
				//EE.PARA. C_REMEMBER_PARA05_04;        //10	        //-3℃≤T＜-1℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[90];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];
				}					
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_5)
			{
				//EE.PARA. C_REMEMBER_PARA05_05;        //10	        //1℃≤T＜4℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[91];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}				
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];
				}					
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_6)
			{
				//EE.PARA. C_REMEMBER_PARA05_06;        //10	        //4℃≤T＜7℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[92];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}					
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];	
				}
			}	
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_7)
			{
				//EE.PARA. C_REMEMBER_PARA05_07;        //10	        //7℃≤T＜10℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[93];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}				
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[9];	
				}					
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_8)
			{
				//EE.PARA. C_REMEMBER_PARA05_08;        //10	        //10℃≤T＜13℃
				u8_EEP_rdPara = EEP.u8_rdBuf[94];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[8];
				}					
			}	
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_9)
			{
				//EE.PARA. C_REMEMBER_PARA05_09;        //10	        //13℃≤T＜16℃
				u8_EEP_rdPara = EEP.u8_rdBuf[95];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[8];		
				}
			}	
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_10)
			{
				//EE.PARA. C_REMEMBER_PARA05_10;        //10	        //16℃≤T＜19℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[96];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}				
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[8];		
				}
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_11)
			{
				//EE.PARA. C_REMEMBER_PARA05_11;        //9	       	    //19℃≤T＜22℃
				u8_EEP_rdPara = EEP.u8_rdBuf[97];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[7];	
				}					
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_12)
			{
				//EE.PARA. C_REMEMBER_PARA05_12;        //7	       	    //22℃≤T＜25℃
				u8_EEP_rdPara = EEP.u8_rdBuf[98];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[6];	
				}					
			}
			else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_13)
			{
				//EE.PARA. C_REMEMBER_PARA05_13;        //5	       	    //25℃≤T＜28℃	
				u8_EEP_rdPara = EEP.u8_rdBuf[99];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}				
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[5];		
				}
			}
			else
			{
				//EE.PARA. C_REMEMBER_PARA05_13;        //3	       	    //28℃≤T
				u8_EEP_rdPara = EEP.u8_rdBuf[99];
				
				if (u8_EEP_rdPara < 16)
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
				}				
				else
				{
					//异常给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[0];		
				}				
			}
			
			if ((Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO) || (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO1))	//保护
			{
				//压缩机不能运行并指示保护代码F8
				Comp.f_AppOn = OFF;
				Comp.u16_RunMinDelay = 0;

			}			
		}
			
		if (((SystemMode.f_Cold == 1) && (Tempr.T4CoolZone != ENUM_TEMPT4COOLZONE_INIT))|| 
			((SystemMode.f_Heat == 1) && (Tempr.T4HeatZone != ENUM_TEMPT4HEATZONE_INIT)))
		{
			//制冷制热T4温度限频
			if ((Comp.u8_TargetFreq > u8_LimitFreqMax) && (u8_LimitFreqMax != 0))				//MAX
			{
				Comp.u8_TargetFreq = u8_LimitFreqMax;
				System.f_T4Limit = 1;
				System.f_T4LimitOff = 0;
			}
			else
			{		
				if (u8_LimitFreqMax == 0)			//参数填0停机
				{
					Comp.f_AppOn = OFF;
					Comp.u16_RunMinDelay = 0;			
					System.f_T4Limit = 1;
					System.f_T4LimitOff = 1;
				}
				else
				{
					System.f_T4Limit = 0;
					System.f_T4LimitOff = 0;
				}
			}
		}
	}	
}
/****************************************************************************************************
Function Name       :void    App_Comp_T4_OffJudge(void)
Description         :室外温度对压缩机停机标志清除
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_T4_OffJudge(void)
{
	U8    u8_EEP_rdPara = 0;
	U8    u8_LimitFreqMax;
	

	if (SystemMode.f_Cold)				//制冷
	{
		if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_11)
		{
			//EE.PARA. C_REMEMBER_PARA04_11;		//3		   		//55℃≤T	
			u8_EEP_rdPara = EEP.u8_rdBuf[85];
								
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_10)
		{
			//EE.PARA. C_REMEMBER_PARA04_10;		//3		   		//50℃≤T＜55℃
			u8_EEP_rdPara = EEP.u8_rdBuf[84];
			
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_9)
		{				
			//EE.PARA. C_REMEMBER_PARA04_09;		//3		   	 	//45℃≤T＜50℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[83];
										
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_8)
		{
			//EE.PARA. C_REMEMBER_PARA04_08;		//3		   		//40℃≤T＜45℃		
			u8_EEP_rdPara = EEP.u8_rdBuf[82];
				
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_7)
		{
			//EE.PARA. C_REMEMBER_PARA04_07;		//10		    //33℃≤T＜40℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[81];
								
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_6)
		{
			//EE.PARA. C_REMEMBER_PARA04_06;		//10		    //30℃≤T＜33℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[80];
					
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_5)
		{
			//EE.PARA. C_REMEMBER_PARA04_05;		//10		    //25℃≤T＜30℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[79];
								
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_4)
		{
			//EE.PARA. C_REMEMBER_PARA04_04;		//9		   		//20℃≤T＜25℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[78];
								
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_3)
		{
			//EE.PARA. C_REMEMBER_PARA04_03;		//8		   		//15℃≤T＜20℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[77];
								
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_2)
		{
			//EE.PARA. C_REMEMBER_PARA04_02;		//6		   		//10℃≤T＜15℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[76];
								
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_1)
		{
			//EE.PARA. C_REMEMBER_PARA04_01;		//4		   		//0℃≤T＜10℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[75];
								
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_0)
		{
			//EE.PARA. C_REMEMBER_PARA04_00;		//3		   		//T＜0℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[74];
								
		}

		//频率不为0,标志清除
		if ((u8_EEP_rdPara > 0) && (u8_EEP_rdPara < 16))
		{
			u8_LimitFreqMax = Comp.u8_Cold_TargetHZ[u8_EEP_rdPara];
			
			if (u8_LimitFreqMax > 0)
			{
				System.f_T4LimitOff = 0;
			}
			else
			{
				System.f_T4LimitOff = 1;
			}
		}
		else if (u8_EEP_rdPara == 0)
		{
			System.f_T4LimitOff = 1;
		}
	}
	else if (SystemMode.f_Heat)			//制热
	{
		if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_0)
		{
			//EE.PARA C_REMEMBER_PARA05_00;        //10	        //T＜-10℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[86];
								
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_1)
		{
			//EE.PARA C_REMEMBER_PARA05_00;        //10	        //T＜-10℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[86];
			
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_2)
		{
			//EE.PARA. C_REMEMBER_PARA05_01;        //10	        //-10℃≤T＜-7℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[87];
								
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_3)
		{
			//EE.PARA. C_REMEMBER_PARA05_02;        //10	        //-7℃≤T＜-3℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[88];
								
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_4)
		{
			//EE.PARA. C_REMEMBER_PARA05_03;        //10	        //-3℃≤T＜-1℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[89];
								
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_5)
		{
			//EE.PARA. C_REMEMBER_PARA05_04;        //10	        //1℃≤T＜4℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[90];
								
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_6)
		{
			//EE.PARA. C_REMEMBER_PARA05_05;        //10	        //4℃≤T＜7℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[91];
			
		}	
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_7)
		{
			//EE.PARA. C_REMEMBER_PARA05_06;        //10	        //7℃≤T＜10℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[92];
								
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_8)
		{
			//EE.PARA. C_REMEMBER_PARA05_07;        //10	        //10℃≤T＜13℃
			u8_EEP_rdPara = EEP.u8_rdBuf[93];
								
		}	
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_9)
		{
			//EE.PARA. C_REMEMBER_PARA05_08;        //10	        //13℃≤T＜16℃
			u8_EEP_rdPara = EEP.u8_rdBuf[94];
			
		}	
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_10)
		{
			//EE.PARA. C_REMEMBER_PARA05_09;        //10	        //16℃≤T＜19℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[95];
			
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_11)
		{
			//EE.PARA. C_REMEMBER_PARA05_10;        //9	       	    //19℃≤T＜22℃
			u8_EEP_rdPara = EEP.u8_rdBuf[96];
								
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_12)
		{
			//EE.PARA. C_REMEMBER_PARA05_11;        //7	       	    //22℃≤T＜25℃
			u8_EEP_rdPara = EEP.u8_rdBuf[97];
								
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_13)
		{
			//EE.PARA. C_REMEMBER_PARA05_12;        //5	       	    //25℃≤T＜28℃	
			u8_EEP_rdPara = EEP.u8_rdBuf[98];
			
		}
		else
		{
			//EE.PARA. C_REMEMBER_PARA05_13;        //3	       	    //28℃≤T
			u8_EEP_rdPara = EEP.u8_rdBuf[99];
							
		}

		//频率不为0,标志清除
		if ((u8_EEP_rdPara > 0) && (u8_EEP_rdPara < 16))
		{
			u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[u8_EEP_rdPara];
			
			if (u8_LimitFreqMax > 0)
			{
				System.f_T4LimitOff = 0;
			}
			else
			{
				System.f_T4LimitOff = 1;
			}
		}
		else if (u8_EEP_rdPara == 0)
		{
			System.f_T4LimitOff = 1;
		}			
	}
	
}
/****************************************************************************************************
Function Name       :void    App_Comp_T2Heat(void)
Description         :制热运行室内风速对压缩机频率运行控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_T2Heat(void)
{
	U8    u8_LimitFreqMax;	//限频最高频率

	if (SystemMode.f_Heat == 1)
	{
		if (SystemMode.f_T2HeatLimit == 0)
		{
			if ((T2.s16_ValueMul10 > 450) && (T4.s16_ValueMul10 >= 0))	//进入条件：室内管温度大于45℃且外环温大于等于0℃
			{
				SystemMode.f_T2HeatLimit = 1;
			}
		}
		else
		{
			if (Fan.Indoor.Level == ENUM_FANLEVEL_HIGH_S) 
			{
				//EE.PARA. C_REMEMBER_PARA07_00;		//10	        //室内风机高风时-E_	
				if ((EEP.u8_rdBuf[105] > 0) && (EEP.u8_rdBuf[105] <= 15))
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[EEP.u8_rdBuf[105]];
				}
				else
				{
					//异常时给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];	
				}
			}
			else if (Fan.Indoor.Level == ENUM_FANLEVEL_HIGH)
			{
				//EE.PARA. C_REMEMBER_PARA07_00;		//10	        //室内风机高风时-E_	
				if ((EEP.u8_rdBuf[105] > 0) && (EEP.u8_rdBuf[105] <= 15))
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[EEP.u8_rdBuf[105]];
				}
				else
				{
					//异常时给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[10];	
				}			
			}
			else if (Fan.Indoor.Level == ENUM_FANLEVEL_MED)
			{
				//EE.PARA. C_REMEMBER_PARA07_01;		//8	       		//室内风机中风时-E_
				if ((EEP.u8_rdBuf[106] > 0) && (EEP.u8_rdBuf[106] <= 15))
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[EEP.u8_rdBuf[106]];
				}
				else
				{
					//异常时给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[8];	
				}
			}
			else if (Fan.Indoor.Level == ENUM_FANLEVEL_LOW)
			{
				//EE.PARA. C_REMEMBER_PARA07_02;		//8	       		//室内风机低风时-E_
				if ((EEP.u8_rdBuf[107] > 0) && (EEP.u8_rdBuf[107] <= 15))
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[EEP.u8_rdBuf[107]];
				}
				else
				{
					//异常时给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[8];	
				}					
			}
			else //if (Fan.Indoor.Level == ENUM_FANLEVEL_LOW_S) 
			{
				//EE.PARA. C_REMEMBER_PARA07_03;		//6	       		//室内风机微风时-E_
				if ((EEP.u8_rdBuf[108] > 0) && (EEP.u8_rdBuf[108] <= 15))
				{
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[EEP.u8_rdBuf[108]];
				}
				else
				{
					//异常时给定常数
					u8_LimitFreqMax = Comp.u8_Heat_TargetHZ[6];	
				}					
			}
			
			//制热运行室内风速对压缩机限频
			if ((Comp.u8_TargetFreq > u8_LimitFreqMax) && (u8_LimitFreqMax != 0))		//MAX
			{
				Comp.u8_TargetFreq = u8_LimitFreqMax;
			}
			
			if ((T2.s16_ValueMul10 < 430) && (T4.s16_ValueMul10 > 30)) //退出条件：室内管温度小于43℃且外环温大于3℃
			{
				SystemMode.f_T2HeatLimit = 0;
			}
		}
	}
	else
	{
		SystemMode.f_T2HeatLimit = 0;
	}
}
/****************************************************************************************************
Function Name       :void    App_Comp_ForceFun(void)
Description         :强力模式下的压缩机频率控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_ForceFun(void)
{
	if (SystemMode.f_Force)
	{
		if (System.u32_ForceRunCount < 36000)	//1小时内按最高频率运行
		{
			Comp.u8_TargetFreq = Comp.u8_Cold_TargetHZ[15];		//FC15
		}
		else 	//2小时内最高按FC14频率运行
		{
			Comp.u8_TargetFreq = Comp.u8_Cold_TargetHZ[14];		//FC14
			if (System.u32_ForceRunCount >= 72000)	//2小时外退出强劲 //lcx add 20240625
			{
				SystemMode.f_Force = 0;
			}
		}

		//lcx 20240625规格书更新：
		//9.4.5 在强力模式运行2小时内，强力模式达温停机有效（达温停压机，上风机一直以强力风运行，不执行停10开1达温逻辑），达温停机后仅外机处理退出强力模式运行，显示不退出强力模式。
		/*
		if (SystemMode.f_TempCEC == 1)	//达温退出
		{
			SystemMode.f_Force = 0;
		}
		*/
	}
}
/****************************************************************************************************
Function Name       :void    App_Comp_Sleep(void)
Description         :睡眠模式下的压缩机频率控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_Sleep(void)
{
	if (Defrost.f_Enable == 0)//化霜时除外	20231227
	{
		if (SystemMode.f_Sleep)
		{
			if (SystemMode.f_Cold == 1)
			{
				//制冷睡眠限频
				if (Comp.u8_TargetFreq > Comp.u8_Cold_TargetHZ[1])
				{
					Comp.u8_TargetFreq = Comp.u8_Cold_TargetHZ[1];	//FC1
				}
			}
			else if (SystemMode.f_Heat == 1)
			{
				//制热睡眠限频
				if (Comp.u8_TargetFreq > Comp.u8_Heat_TargetHZ[1])
				{
					Comp.u8_TargetFreq = Comp.u8_Heat_TargetHZ[1];	//FH1
				}		
			}
		}
	}
}
/****************************************************************************************************
Function Name       :void    App_Comp_PerTest(void)
Description         :性能测试模式下压缩机频率控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_PerTest(void)
{
	if (Defrost.f_Enable == 0)//化霜时除外	20231227
	{
		if (SystemMode.f_PerTest == 1)
		{
			if (SystemMode.f_Cold == 1)
			{
				if (Tempr.u8_TempCSet == 30)	//额定制冷
				{
					//EE.PARA. C_REMEMBER_PARA15_00;		//10		   //额定制冷压机运行档位
					if ((EEP.u8_rdBuf[142] > 0) && (EEP.u8_rdBuf[142] < 16))
					{
						Comp.u8_TargetHZ = Comp.u8_Cold_TargetHZ[EEP.u8_rdBuf[142]];
					}
					else	//超出范围按最大频率
					{
						Comp.u8_TargetHZ = Comp.u8_Cold_TargetHZ[15];
					}
								
				}
				else if (Tempr.u8_TempCSet == 29)	//最小制冷
				{
					//EE.PARA. C_REMEMBER_PARA15_01;		//1		       //最小制冷压机运行档位				
					if ((EEP.u8_rdBuf[143] > 0) && (EEP.u8_rdBuf[143] < 16))
					{
						Comp.u8_TargetHZ = Comp.u8_Cold_TargetHZ[EEP.u8_rdBuf[143]];
					}
					else	//超出范围按最小频率
					{
						Comp.u8_TargetHZ = Comp.u8_Cold_TargetHZ[1];
					}
					
					if (Comp.u8_TargetHZ > 25)	Comp.u8_TargetHZ = 25;
				}
			}
			else if (SystemMode.f_Heat == 1)
			{
				if (Tempr.u8_TempCSet == 17)
				{
					//EE.PARA. C_REMEMBER_PARA15_02;		//10		   //额定制热压机运行档位					
					if ((EEP.u8_rdBuf[144] > 0) && (EEP.u8_rdBuf[144] < 16))
					{
						Comp.u8_TargetHZ = Comp.u8_Heat_TargetHZ[EEP.u8_rdBuf[144]];
					}
					else	//超出范围按最大频率
					{
						Comp.u8_TargetHZ = Comp.u8_Heat_TargetHZ[15];
					}
				}
			}
		}
	}
}
/****************************************************************************************************
Function Name       :void    App_Comp_AntiDew(void)
Description         :防凝露压缩机限频控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_AntiDew(void)	
{
	if (SystemMode.f_AntiDew == 1)	//防凝露生效时压缩机最大运行不超过FC4
	{
		if (Comp.u8_TargetFreq > Comp.u8_Cold_TargetHZ[4])	//FC4
		{
			Comp.u8_TargetFreq = Comp.u8_Cold_TargetHZ[4];
		}
	}
}	
/****************************************************************************************************
Function Name       :void    App_Comp_WatFull(void)
Description         :水满情况下压缩机频率控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_WatFull(void)
{
	if (WaterBox.f_Full == 1)
	{		
		Comp.f_AppOn = OFF;
		
	}
	else if (WaterBox.f_WatLow == 1)
	{
		//低水位限频
		if (Comp.u8_TargetFreq > 40)
		{
			Comp.u8_TargetFreq = 40;
		}
	}
}
/****************************************************************************************************
Function Name       :void    App_Comp_ProCon(void)
Description         :保护情况下压缩机频率处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_ProCon(void)
{
	if ((Protect.TpStatus == ENUM_PROSTATUS_NORMAL) && (Protect.T2ColdStatus == ENUM_PROSTATUS_NORMAL) && 
		(Protect.T3ColdStatus == ENUM_PROSTATUS_NORMAL) && (Protect.CurrColdStatus == ENUM_PROSTATUS_NORMAL) &&
		(Protect.CurrHeatStatus == ENUM_PROSTATUS_NORMAL) && (Protect.CompCurrStatus == ENUM_PROSTATUS_NORMAL) &&
		(Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_OK))	//正常情况没有保护情况下直接赋值
	{
		Protect.SystemStatus = ENUM_PROSTATUS_NORMAL;
		
		if ((SystemMode.f_PerTest == 0) && (T1.f_Error == 0))	//非性能测试且T1无故障
		{
			App_Comp_T1TSDelta();		//T1/TS温差频率控制
		}
		
		Comp.u8_TargetFreq = Comp.u8_TargetHZ;
		Protect.u16_CompHzLimitCount = 0;
		
		App_Comp_ForceFun();		//强力模式下的压缩机频率控制	
		App_Comp_InDoorFan();		//室内风速对压缩机运行频率的控制
		App_Comp_T4();				//室外温度对压缩机运行频率的控制
		App_Comp_T2Heat();			//制热运行室内风速对压缩机频率运行控制		
		App_Comp_Sleep();			//睡眠模式下的压缩机频率控制
		App_Comp_PerTest();			//性能测试模式下压缩机频率控制
		App_Comp_AntiDew();			//防凝露压缩机限频控制
		App_Comp_WatFull();		    //水满情况下压缩机频率控制		
	}	
	else	//存在保护情况
	{
		if ((Protect.TpStatus == ENUM_PROSTATUS_FASTDOWN) || (Protect.T2ColdStatus == ENUM_PROSTATUS_FASTDOWN) || 
			(Protect.T3ColdStatus == ENUM_PROSTATUS_FASTDOWN) || (Protect.CurrColdStatus == ENUM_PROSTATUS_FASTDOWN) ||
			(Protect.CurrHeatStatus == ENUM_PROSTATUS_FASTDOWN) || (Protect.CompCurrStatus == ENUM_PROSTATUS_FASTDOWN) ||
			(Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_FASTDOWN))			//存在频率快速降频的情况	
		{		
			if ((Protect.SystemStatus == ENUM_PROSTATUS_NORMAL) || (Protect.SystemStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.SystemStatus == ENUM_PROSTATUS_CONT))
			{
				//出现限频刹那, 目标频率根据实际频率修正
				Comp.u8_TargetHZ = Comp.u8_RealHZ;			
				Comp.u8_TargetFreq = Comp.u8_TargetHZ;
			}			
			
			
			//每1秒下降1HZ(全部)
			if (++Protect.u16_CompHzLimitCount >= 100)		//1s
			{
				Protect.u16_CompHzLimitCount = 0;
				Comp.u8_TargetHZ -= 1;
				Comp.u8_TargetFreq = Comp.u8_TargetHZ;
			}
									
			Protect.SystemStatus = ENUM_PROSTATUS_FASTDOWN;
		}		
		else if ((Protect.TpStatus == ENUM_PROSTATUS_SLOWDOWN) || (Protect.T2ColdStatus == ENUM_PROSTATUS_SLOWDOWN) || 
				 (Protect.T3ColdStatus == ENUM_PROSTATUS_SLOWDOWN) || (Protect.CurrColdStatus == ENUM_PROSTATUS_SLOWDOWN) ||
				 (Protect.CurrHeatStatus == ENUM_PROSTATUS_SLOWDOWN) || (Protect.CompCurrStatus == ENUM_PROSTATUS_SLOWDOWN) ||
				 (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_SLOWDOWN))	//存在频率慢速降频的情况		
		{
			if ((Protect.SystemStatus == ENUM_PROSTATUS_NORMAL) || (Protect.SystemStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.SystemStatus == ENUM_PROSTATUS_CONT))
			{
				//出现限频刹那, 目标频率根据实际频率修正
				Comp.u8_TargetHZ = Comp.u8_RealHZ;			
				Comp.u8_TargetFreq = Comp.u8_TargetHZ;
			}			
			
			
			if ((Protect.TpStatus == ENUM_PROSTATUS_SLOWDOWN) || (Protect.T2ColdStatus == ENUM_PROSTATUS_SLOWDOWN) || (Protect.T3ColdStatus == ENUM_PROSTATUS_SLOWDOWN))
			{
				if (++Protect.u16_CompHzLimitCount >= 1000)		//10s
				{
					Protect.u16_CompHzLimitCount = 0;
					Comp.u8_TargetHZ -= 1;
					Comp.u8_TargetFreq = Comp.u8_TargetHZ;
				}			
			}
			else if ((Protect.CurrColdStatus == ENUM_PROSTATUS_SLOWDOWN) || (Protect.CurrHeatStatus == ENUM_PROSTATUS_SLOWDOWN) || (Protect.CompCurrStatus == ENUM_PROSTATUS_SLOWDOWN))
			{
				if (++Protect.u16_CompHzLimitCount >= 500)		//5s
				{
					Protect.u16_CompHzLimitCount = 0;
					Comp.u8_TargetHZ -= 1;
					Comp.u8_TargetFreq = Comp.u8_TargetHZ;
				}			
			}
			else if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_SLOWDOWN)
			{
				if (++Protect.u16_CompHzLimitCount >= 3000)		//30s
				{
					Protect.u16_CompHzLimitCount = 0;
					Comp.u8_TargetHZ -= 1;
					Comp.u8_TargetFreq = Comp.u8_TargetHZ;
				}			
			}
			
			Protect.SystemStatus = ENUM_PROSTATUS_SLOWDOWN;
			
		}
		else if ((Protect.TpStatus == ENUM_PROSTATUS_CONT) || (Protect.T2ColdStatus == ENUM_PROSTATUS_CONT) || 
				 (Protect.T3ColdStatus == ENUM_PROSTATUS_CONT) || (Protect.CurrColdStatus == ENUM_PROSTATUS_CONT) ||
				 (Protect.CurrHeatStatus == ENUM_PROSTATUS_CONT) || (Protect.CompCurrStatus == ENUM_PROSTATUS_CONT) ||
		         (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_CON))			//存在频率保持的情况
		{
			App_Comp_ForceFun();		//强力模式下的压缩机频率控制	
			App_Comp_InDoorFan();		//室内风速对压缩机运行频率的控制
			App_Comp_T4();				//室外温度对压缩机运行频率的控制
			App_Comp_T2Heat();			//制热运行室内风速对压缩机频率运行控制		
			App_Comp_Sleep();			//睡眠模式下的压缩机频率控制
			App_Comp_PerTest();			//性能测试模式下压缩机频率控制
			App_Comp_AntiDew();			//防凝露压缩机限频控制
			App_Comp_WatFull();		    //水满情况下压缩机频率控制	
			
			Protect.SystemStatus = ENUM_PROSTATUS_CONT;
		}
		else if ((Protect.TpStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.T2ColdStatus == ENUM_PROSTATUS_SLOWUP) || 
				 (Protect.T3ColdStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.CurrColdStatus == ENUM_PROSTATUS_SLOWUP) ||
				 (Protect.CurrHeatStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.CompCurrStatus == ENUM_PROSTATUS_SLOWUP) ||
		         (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_SLOWUP))		//存在频率慢升的情况
		{
			if ((Protect.TpStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.T2ColdStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.T3ColdStatus == ENUM_PROSTATUS_SLOWUP) || (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_SLOWUP))
			{
				if (++Protect.u16_CompHzLimitCount >= 3000)		//30s
				{
					Protect.u16_CompHzLimitCount = 0;
					
					if (Comp.u8_TargetHZ < Comp.u8_TargetSrc)
					{
						Comp.u8_TargetHZ += 1;			
						Comp.u8_TargetFreq = Comp.u8_TargetHZ;
					}
				}			
			}
			else if ((Protect.CurrColdStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.CurrHeatStatus == ENUM_PROSTATUS_SLOWUP) || (Protect.CompCurrStatus == ENUM_PROSTATUS_SLOWUP))
			{
				if (++Protect.u16_CompHzLimitCount >= 1000)		//10s
				{
					Protect.u16_CompHzLimitCount = 0;

					if (Comp.u8_TargetHZ < Comp.u8_TargetSrc)
					{
						Comp.u8_TargetHZ += 1;			
						Comp.u8_TargetFreq = Comp.u8_TargetHZ;
					}				
				}				
			}
			
			App_Comp_ForceFun();		//强力模式下的压缩机频率控制	
			App_Comp_InDoorFan();		//室内风速对压缩机运行频率的控制
			App_Comp_T4();				//室外温度对压缩机运行频率的控制
			App_Comp_T2Heat();			//制热运行室内风速对压缩机频率运行控制		
			App_Comp_Sleep();			//睡眠模式下的压缩机频率控制
			App_Comp_PerTest();			//性能测试模式下压缩机频率控制
			App_Comp_AntiDew();			//防凝露压缩机限频控制
			App_Comp_WatFull();		    //水满情况下压缩机频率控制				
			
			Protect.SystemStatus = ENUM_PROSTATUS_SLOWUP;
			
		}	
		else
		{
			Protect.SystemStatus = ENUM_PROSTATUS_PROTECT;		
		}
		
	}
		
}
/****************************************************************************************************
Function Name       :void    Log_Comp(void)
Description         :压缩机逻辑处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Log_Comp(void)
//{
//	if ((Protect.TpStatus == ENUM_PROSTATUS_PROTECT)	
//	|| (Protect.T2ColdStatus == ENUM_PROSTATUS_PROTECT)
//	|| (Protect.T2HeatStatus == ENUM_PROSTATUS_PROTECT)
//	|| (Protect.T3ColdStatus == ENUM_PROSTATUS_PROTECT)
//	|| (Protect.CurrColdStatus == ENUM_PROSTATUS_PROTECT)
//	|| (Protect.CurrHeatStatus == ENUM_PROSTATUS_PROTECT)
//	|| (T1.f_Error == 1) || (T2.f_Error == 1) || (T3.f_Error == 1) 
// 	|| (T4.f_Error == 1) || (Tp.f_Error == 1))
//	)	
//	{//故障或保护停压缩机
//		Comp.f_AppOn = OFF;
//		Comp.u8_PowerOnDelay = 0;
//		Comp.u16_RestartDelay = 0;
//	}
//	else if (Defrost.f_Enable)	//化霜
//	{
//		
//	}
//	else if ((SystemMode.f_PerTest == 1) && ((Tempr.u8_TempCSet == 29) || (Tempr.u8_TempCSet == 30)))	//能力测试 
//	{
//		Comp.f_AppOn = ON;	
//	}
//	else    	//正常工况
//	{
//		if (SystemMode.f_Cold == 1)  //后续补充除湿状态
//		{
//			
//		}
//		else if (SystemMode.f_Heat == 1)
//		{
//
//		}
//		else 
//		{
//			Comp.f_AppOn = 0;
//		}
//	}
//}
{
	if (Comp.f_DrvOn == OFF)
	{
		if (((Protect.T2ColdStatus != ENUM_PROSTATUS_PROTECT) && //(Tempr.T2HeatZone != ENUM_TEMPT2HEATZONE_PRO) && 
			(Protect.T3ColdStatus != ENUM_PROSTATUS_PROTECT) && 
//			(Tempr.T4CoolZone != ENUM_TEMPT4COOLZONE_STOP) && (Tempr.T4CoolZone != ENUM_TEMPT4COOLZONE_PRO) && (Tempr.T4CoolZone != ENUM_TEMPT4COOLZONE_PRO1) &&
//			(Tempr.T4HeatZone != ENUM_TEMPT4HEATZONE_PRO) && (Tempr.T4HeatZone != ENUM_TEMPT4HEATZONE_PRO1) &&
			(Protect.TpStatus != ENUM_PROSTATUS_PROTECT) &&			
			(Protect.CurrColdStatus != ENUM_PROSTATUS_PROTECT) && (Protect.CurrHeatStatus != ENUM_PROSTATUS_PROTECT) &&
			(Protect.CompCurrStatus != ENUM_PROSTATUS_PROTECT) && (System.f_T4LimitOff == 0) &&
			(Comp.f_IPMPro == 0) && (Comp.f_IPMErr == 0) && (Comp.f_StartErr == 0) && (System.f_CurrentProtect == 0) &&			
			(System.f_VoltLowPro == 0) && (Fan.Indoor.f_Error == 0) && (Fan.Outdoor.f_Error == 0)
			&&(Protect.T2HeatStatus != ENUM_PROSTATUS_PROTECT)) 
			||(System.Enum_Status == ENUM_STATUS_BUSSCHK))//满足开压缩机		
		{		
			if ((SystemMode.f_Heat == 1) && (Comp.f_AppOn == ON) && (FourWay.f_DrvOn == OFF)) //制热压缩机开启前先保证四通阀打开
			{
				if (Defrost.f_Enable == 0)				//非化霜情况下
				{
					if (Comp.u16_RestartDelay < 50)
					{
						Comp.u16_RestartDelay = 50;
					}
				}
			}
			
			if ((Comp.f_AppOn == ON) 
			&& (Comp.u16_RestartDelay == 0) 
			&& (Comp.u8_SelTestDelay == 0) 
			&& (Comp.u8_PowerOnDelay == 0) 
			&& (WaterBox.f_Full == 0)
			&& ((Fan.Outdoor.u16_Count >= (FtyPara.u16P2 * 10)) || Defrost.f_Enable))		//外风机运行5秒
			{
				//启动刹那
				App_Comp_RunHzInitIndex();							//压缩机启动频率档次判断
				
				SystemMode.f_ConTemp = 0;
				SystemMode.f_RoughCon = 0;
				SystemMode.f_TempCEC = 0;							//压缩机再次启动,达温标志清除									
				Comp.u16_StartInitDelay = C_COMP_STARTINITDELAY;	//压缩机3分钟启动流程
				Comp.u16_RunMinDelay = FtyPara.u16P1*600;// C_COMP_RUNMINDELAY;			//压缩机最小运行时间3分钟
				WPMotor.u16_CompOnDelay = 900;						//打水电机延时压缩机启动后90s启动
				//Defrost.u16_FindT30_Count = 0;					//化霜功能制热时重新计时寻找T30时间 lcx del 20240715 开关机不清除T30时间，
				//转换模式时已执行 Defrost_Init(); //化霜相关变量初始化
				T1.u16_ErrCount = 0;								//启动重新计时
				T4.u16_ErrCount = 0;								//启动重新计时
				Tp.u16_ErrCount = 0;								//启动重新计时
				Tempr.u16_T1TSDeltaCount = 0;						//启动重新计时
				
				
				if ((SystemMode.f_Heat == 1) && (FourWay.f_DrvOn == ON))
				{
					if (T2.s16_ValueMul10 < 350)		//IPT低于35℃
					{
						Fan.Indoor.u16_Delay = 200;//EE. (P24)	制热上风机延时压缩机启动后20s启动
					}
					Comp.f_HeatFirstOn = 1;
				}

				
				Comp.f_DrvOn = ON;		//压缩机启动
			}
		}
	}
	else
	{
		if (((Comp.f_AppOn == OFF) && (Comp.u16_RunMinDelay == 0)) || WaterBox.f_Full || 		 			
			((((Protect.T2ColdStatus == ENUM_PROSTATUS_PROTECT) || //(Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_PRO) || 
			(Protect.T3ColdStatus == ENUM_PROSTATUS_PROTECT) || 
//			(Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_STOP) || (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_PRO) || (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_PRO1) ||
//			(Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO) || (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO1) ||
			(Protect.TpStatus == ENUM_PROSTATUS_PROTECT) ||			
			(Protect.CurrColdStatus == ENUM_PROSTATUS_PROTECT) || (Protect.CurrHeatStatus == ENUM_PROSTATUS_PROTECT) ||
			(Protect.CompCurrStatus == ENUM_PROSTATUS_PROTECT)) || System.f_T4LimitOff ||
			Comp.f_IPMPro || Comp.f_IPMErr || Comp.f_StartErr || System.f_CurrentProtect || System.f_VoltLowPro ||
			Fan.Indoor.f_Error || Fan.Outdoor.f_Error || (Protect.T2HeatStatus == ENUM_PROSTATUS_PROTECT)) && (System.Enum_Status != ENUM_STATUS_BUSSCHK)))	
		{
			//关停刹那
			if (System.Enum_Status != ENUM_STATUS_BUSSCHK)
			{
				if ((T4.f_Error == 0) && (Tp.f_Error == 0) && (T4.s16_ValueMul10 > 500) && (Tp.s16_ValueMul10 > 700))		//室外温度超50℃且排气温度超70℃
				{
					//EE.PARA. C_REMEMBER_PARA14_00;		//10(min)		  	//高负荷启停待机时间
					Comp.u16_RestartDelay = TempValueMul10(EEP.u8_rdBuf[141]);
					Comp.u16_RestartDelay = TempValueMul10(Comp.u16_RestartDelay);	
					Comp.u16_RestartDelay = (Comp.u16_RestartDelay<<2) + (Comp.u16_RestartDelay<<1);
				}
				else
				{
					Comp.u16_RestartDelay = C_COMP_RESTARTDELAY;		//压缩机重启需等待最小时间3分钟
				}
			}
			else
			{
				Comp.u16_RestartDelay = C_COMP_BUSSCHK_RESTARTDELAY;	//商检情况等待1分钟	
			}
			
			Fan.Indoor.u16_Count = 0;							//达温停机上风机循环开停计时重新计时

			
			if (SystemMode.f_HeatBak == 1)
			{
//				if (T2.s16_ValueMul10 > 300)	
//				{
//					Fan.Indoor.u16_Delay = 200;		//(P26) 压缩机停止后20s上风机关闭(吹余热)
//					
//					if (T2.s16_ValueMul10 < 300)	//30℃＜IPT＜35℃
//					{
//						Fan.Indoor.f_ForceLow = 1;	//强制低风
//						if (T2.s16_ValueMul10 < 250)
//						{
//							if (Fan.Indoor.f_AppOn)
//							{
//								Fan.Indoor.f_AppOn = OFF; //去到OFF后，要在后面控制Fan.Indoor.f_ForceLow
//								Fan.Indoor.u16_Delay = 150; //延时15s，直接关掉，防止冷风
//							}
//						}
//					}				
//				}
//				else 
//				{
//					Fan.Indoor.u16_Delay = 0;
//				}
				
				Fan.Outdoor.u16_Delay = 0;			//制热外风机立即停
				Fan.Outdoor.u16_Delay = 50;			//外风机延时5s后关闭
			}
			else
			{
				Fan.Indoor.u16_Delay = 0;
//				Fan.Outdoor.u16_Delay = 300;		//外风机延时30s后关闭
				Fan.Outdoor.u16_Delay = 50;			//外风机延时5s后关闭
			}

			
			if (System.Enum_Status != ENUM_STATUS_BUSSCHK)
			{
				FourWay.u16_Delay = 1250;			//压缩机关机2分钟后关闭四通阀(除霜除外)
			}
			else
			{
				FourWay.u16_Delay = 300;			//商检四通阀延时30s关闭
			}
			
			DCFan.u16_Delay = C_DCFAN_DELAY;			//散热风扇延时关闭
			
			Comp.f_DrvOn = OFF;			//压缩机关停
		}
	} 
}
/****************************************************************************************************
Function Name       :void    Drv_Comp(void)
Description         :压缩机驱动处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Drv_Comp(void)
//{
//	Comp.f_DrvOn = Comp.f_AppOn;
//	
//	if ((Comp.f_DrvOn == 1) 
//	&& (Comp.u8_PowerOnDelay == 0)
//	&& (Comp.u16_RestartDelay == 0))
//	{	
//		P_Comp_On();	
//	}
//	else if ((Comp.f_DrvOn == 0) 
//	&& (Comp.u16_RunMinDelay))
//	{
//		P_Comp_Off();
//	}
//}
{
	if ((Comp.f_DrvOn == 1) || (Comp.f_ForceDrvOn == 1))
	{
		P_Comp_On();		
	}
	else 
	{
		P_Comp_Off();
	}
}

//{	
//	U8 CompFreqMin;
//	U8 CompFreqMax;
//	
//	if (Comp.f_DrvOn == 1)
//	{
//		if (System.Enum_Status != ENUM_STATUS_BUSSCHK)
//		{
//			App_Comp_ProCon();			//保护情况下压缩机频率处理			
//				
//			if (Defrost.f_Enable)
//			{
//				EE.PARA. C_REMEMBER_PARA10_00;		//10		    //化霜过程最大运行频率档位
//				if ((EEP.u8_rdBuf[125] > 0) && (EEP.u8_rdBuf[125] <= 15))	//合理范围
//				{
//					if (Comp.u8_TargetFreq > Comp.u8_Heat_TargetHZ[EEP.u8_rdBuf[125]])	
//					{
//						Comp.u8_TargetFreq = Comp.u8_Heat_TargetHZ[EEP.u8_rdBuf[125]];
//					}
//				}
//				else
//				{
//					if (Comp.u8_TargetFreq > Comp.u8_Heat_TargetHZ[10])	
//					{
//						Comp.u8_TargetFreq = Comp.u8_Heat_TargetHZ[10];
//					}				
//				}
//			}
//			else if (SystemMode.f_PerTest == 1)		//额定/最小 测试模式不受限频
//			{
//				if ((SystemMode.f_Cold == 1) && ((Tempr.u8_TempCSet == 30) || (Tempr.u8_TempCSet == 29)))	//额定制冷/最小制冷
//				{
//					Comp.u8_TargetFreq = Comp.u8_TargetHZ;
//				}
//				else if ((SystemMode.f_Heat == 1) && (Tempr.u8_TempCSet == 17))	//额定制热
//				{
//					Comp.u8_TargetFreq = Comp.u8_TargetHZ;
//				}
//					
//			}
//		}
//		else	//商检直接赋值
//		{
//			Comp.u8_TargetFreq = Comp.u8_TargetHZ;
//		}
//		
//		保证运行频率在合理范围内	
//		if (SystemMode.f_Cold)
//		{
//			CompFreqMin = Comp.u8_Cold_TargetHZ[1];
//			
//			if 	(System.Enum_Status == ENUM_STATUS_BUSSCHK)		CompFreqMax = 60;
//			else												CompFreqMax = Comp.u8_Cold_TargetHZ[15];
//				
//			if (Comp.u8_TargetFreq  > CompFreqMax)
//			{
//				Comp.u8_TargetFreq  = CompFreqMax;
//			}
//			
//			if (Comp.u8_TargetFreq  < CompFreqMin)
//			{
//				Comp.u8_TargetFreq  = CompFreqMin;
//			}
//			
//			
//			if (Comp.u8_TargetHZ > CompFreqMax)
//			{
//				Comp.u8_TargetHZ = CompFreqMax;
//			}
//			
//			if (Comp.u8_TargetHZ < CompFreqMin)
//			{
//				Comp.u8_TargetHZ = CompFreqMin;
//			}
//		}		
//		else if (SystemMode.f_Heat)
//		{			
//			if (Comp.u8_TargetFreq  > Comp.u8_Heat_TargetHZ[15])
//			{
//				Comp.u8_TargetFreq  = Comp.u8_Heat_TargetHZ[15];
//			}
//			
//			if (Comp.u8_TargetFreq  < Comp.u8_Heat_TargetHZ[1])
//			{
//				Comp.u8_TargetFreq  = Comp.u8_Heat_TargetHZ[1];
//			}
//
//			
//			if (Comp.u8_TargetHZ > Comp.u8_Heat_TargetHZ[15])
//			{
//				Comp.u8_TargetHZ = Comp.u8_Heat_TargetHZ[15];
//			}
//			
//			if (Comp.u8_TargetHZ < Comp.u8_Heat_TargetHZ[1])
//			{
//				Comp.u8_TargetHZ = Comp.u8_Heat_TargetHZ[1];
//			}
//		}
//
//			
//			
//	}
//	else
//	{
//		App_Comp_T4_OffJudge();					//判断T4限频停机标志清除恢复或生效	
//		
//		Comp.u8_TargetHZ = 0;					//停机	
//		Comp.u8_TargetFreq = 0;					//停机
//	}
//}
/****************************************************************************************************
Function Name       :void    Func_Comp(void)
Description         :压缩机功能处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Comp(void)
{
	if (Comp.f_FourWayAbn == 1)
	{
		Comp.f_FourWayAbn = 0;
		Comp.f_AppOn = OFF;
		Comp.u16_RunMinDelay = 0;
	}
	
	Log_Comp();
	Drv_Comp();
}
