/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Tempr.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_TEMPRATURE    T1;          //T1-室内温度
STRUCT_TEMPRATURE    T2;          //T2-室内盘管温度
STRUCT_TEMPRATURE    T3;          //T3-室外盘管温度
STRUCT_TEMPRATURE    T4;		  //T4-室外温度
STRUCT_TEMPRATURE    Tp;		  //排气温度
STRUCT_TEMPRATURE    Cur;		  //电流温度
STRUCT_TEMPRATURE    TH;		  //TH-回气温度
STRUCT_TEMPRATURE    T5;		  //T5-水箱温度
STRUCT_TEMPRATURE    T5I;		  //T5-进水温度
STRUCT_TEMPRATURE    T5O;		  //T5-出水温度


STRUCT_TEMPR    Tempr;			  //温控变量

/****************************************************************************************************
Function Name       :S16    TempValueMul10(S16 TempValue)
Description         :温度值乘以10倍
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
S16    TempValueMul10(S16 TempValue)
{
	S16  result;
	S16  temp;
	
	result = TempValue;
	temp = TempValue;
	
	result <<= 3;
	temp <<= 1;
	result += temp;
	
	return    result;
}
/****************************************************************************************************
Function Name       :S8    TempValueRounding(S16 TempMul10Value)
Description         :温度值四舍五入
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
S8    TempValueRounding(S16 TempMul10Value)
{
	S16    temp;
	S8     result;
	
	temp = TempMul10Value;
	
	if (temp >= 0)	//正数处理
	{
		result = temp%10;
		
		if (result >= 5)
		{
			result = TempMul10Value/10;
			result += 1;
		}
		else
		{
			result = TempMul10Value/10;
		}
	}
	else
	{
		temp = 0 - temp;
		result = temp%10;
		
		if (result >= 5)
		{
			result = TempMul10Value/10;
			result -= 1;
		}
		else
		{
			result = TempMul10Value/10;
		}		
	}
	
	return    result;
}
/****************************************************************************************************
Function Name       :void	TempValueCon(void)
Description         :温度值处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    TempValueCon(void)
{
	S16    s16_temp;
	
	//T1
	if (System.f_Sense == 0)						//随身感无效按实际T1值为室内温度
	{
		if (T1.f_Error == 0)							//传感器正常
		{
			s16_temp = T1.s8_ValueRead;
			
			T1.s16_ValueMul10 = TempValueMul10(s16_temp);
			T1.s16_ValueMul10 += T1.u8_ValueDotRead;
			
			if (SystemMode.f_Heat == 1)	//制热补偿1℃	//Tr-1
			{
				s16_temp -= 1;	//T1_OFFSET_HOT
			}
			
			s16_temp = TempValueMul10(s16_temp);		//*10
			T1.s16_ValueMul10bc = s16_temp + T1.u8_ValueDotRead;
			
			
			T1.s8_Value = TempValueRounding(T1.s16_ValueMul10);
		}
	}
	else	//随身感有效室内温度值按随身感温度进行控温(随身感制热不用补偿)
	{
		s16_temp = Tempr.u8_TempSense;
		s16_temp = TempValueMul10(s16_temp);		//*10
		T1.s16_ValueMul10 = s16_temp + 0;//T1.u8_ValueDotRead;
		T1.s16_ValueMul10bc = T1.s16_ValueMul10;
		
		T1.s8_Value = TempValueRounding(T1.s16_ValueMul10);			
	}
	
	//T2
	if (T2.f_Error == 0)							//传感器正常
	{
		s16_temp = T2.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		T2.s16_ValueMul10 = s16_temp + T2.u8_ValueDotRead;
		T2.s8_Value = TempValueRounding(T2.s16_ValueMul10);	
	}

	//T3
	if (T3.f_Error == 0)							//传感器正常
	{
		s16_temp = T3.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		T3.s16_ValueMul10 = s16_temp + T3.u8_ValueDotRead;
		T3.s8_Value = TempValueRounding(T3.s16_ValueMul10);			
	}	
	
	if (TH.f_Error == 0)							//传感器正常
	{
		s16_temp = TH.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		TH.s16_ValueMul10 = s16_temp + TH.u8_ValueDotRead;
		TH.s8_Value = TempValueRounding(TH.s16_ValueMul10);			
	}	
	
	//T4
	if (T4.f_Error == 0)							//传感器正常
	{
		s16_temp = T4.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		T4.s16_ValueMul10 = s16_temp + T4.u8_ValueDotRead;
		T4.s8_Value = TempValueRounding(T4.s16_ValueMul10);			
	}

	//Tp
	if (Tp.f_Error == 0)							//传感器正常
	{
		s16_temp = Tp.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		Tp.s16_ValueMul10 = s16_temp + Tp.u8_ValueDotRead;
		Tp.s8_Value = TempValueRounding(Tp.s16_ValueMul10);		
	}	

	if (Cur.f_Error == 0)							//传感器正常
	{
		s16_temp = Cur.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		Cur.s16_ValueMul10 = s16_temp + Cur.u8_ValueDotRead;
		Cur.s8_Value = TempValueRounding(Cur.s16_ValueMul10);		
	}

	//T5
	if (T5.f_Error == 0)							//传感器正常
	{
		s16_temp = T5.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		T5.s16_ValueMul10 = s16_temp + T5.u8_ValueDotRead;
		T5.s16_ValueMul10bc	= T5.s16_ValueMul10 + FtyPara.s16F4;	//温控计算值
		T5.s8_Value = TempValueRounding(T5.s16_ValueMul10);		
	}

	//T5I
	if (T5I.f_Error == 0)							//传感器正常
	{
		s16_temp = T5I.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		T5I.s16_ValueMul10 = s16_temp + T5I.u8_ValueDotRead;
		T5I.s8_Value = TempValueRounding(T5I.s16_ValueMul10);		
	}

	//T5O
	if (T5O.f_Error == 0)							//传感器正常
	{
		s16_temp = T5O.s8_ValueRead;
		
		s16_temp = TempValueMul10(s16_temp);		//*10
		T5O.s16_ValueMul10 = s16_temp + T5O.u8_ValueDotRead;
		T5O.s8_Value = TempValueRounding(T5O.s16_ValueMul10);		
	}

}
/****************************************************************************************************
Function Name       :void	TempT1TSDeltaZone(void)
Description         :T1-TS/TS-T1温差温区
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void  TempT1TSDeltaZone(void)
{
	S16    TempDelta;
	U8     TempSet;
	
	if (System.Mode == ENUM_SYSMODE_HUM)	TempSet = Tempr.u8_HumiCSet;
	else									TempSet = Tempr.u8_TempCSet;
	
	TempDelta = TempValueMul10(TempSet);
	
	if (SystemMode.f_Heat == 1)		//制热
	{
		//TS-T1(带补偿)
		TempDelta -= T1.s16_ValueMul10bc;		
					
		if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_INIT)		//初始值先确定首值
		{
			if (TempDelta >= 33)	//温差3.3℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_A;
			}
			else if (TempDelta >= 28)	//温差2.8℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_B;
			}
			else if (TempDelta >= 23)	//温差2.3℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_C;
			}
			else if (TempDelta >= 18)	//温差1.8℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_D;
			}	
			else if (TempDelta >= 13)	//温差1.3℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_E;
			}	
			else if (TempDelta >= 8)	//温差0.8℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_F;
			}	
			else if (TempDelta >= 3)	//温差0.3℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_G;
			}
			else if (TempDelta >= -2)	//温差-0.2℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_H;
			}
			else if (TempDelta >= -7)	//温差-0.7℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_I;
			}
			else if (TempDelta >= -12)	//温差-1.2℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_J;
			}
			else
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_K;
			}
		}				
	}
	else if (SystemMode.f_Cold == 1)		//制冷
	{
		TempDelta = T1.s16_ValueMul10bc - TempDelta;		//T1(带补偿)-TS
		
		if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_INIT)		//初始值先确定首值
		{
			if (TempDelta >= 30)	//温差3.0℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_A;
			}
			else if (TempDelta >= 25)	//温差2.5℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_B;
			}
			else if (TempDelta >= 20)	//温差2.0℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_C;
			}
			else if (TempDelta >= 15)	//温差1.5℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_D;
			}	
			else if (TempDelta >= 10)	//温差1.0℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_E;
			}	
			else if (TempDelta >= 5)	//温差0.5℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_F;
			}	
			else if (TempDelta >= 0)	//温差0.0℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_G;
			}
			else if (TempDelta >= -5)	//温差-0.5℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_H;
			}
			else if (TempDelta >= -10)	//温差-1.0℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_I;
			}
			else if (TempDelta >= -15)	//温差-1.5℃
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_J;
			}
			else
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_K;
			}
		}				
	}
	
	if ((SystemMode.f_Cold == 1) || (SystemMode.f_Heat == 1))		//制冷制热才判定区间
	{
		if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_A)
		{
			if (TempDelta < 30)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_B;
			}
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_B)
		{
			if (TempDelta < 25)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_C;
			}
			else if (TempDelta > 33)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_A;
			}
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_C)
		{
			if (TempDelta < 20)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_D;
			}
			else if (TempDelta > 28)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_B;
			}	
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_D)
		{
			if (TempDelta < 15)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_E;
			}
			else if (TempDelta > 23)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_C;
			}		
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_E)
		{
			if (TempDelta < 10)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_F;
			}
			else if (TempDelta > 18)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_D;
			}	
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_F)
		{
			if (TempDelta < 5)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_G;
			}
			else if (TempDelta > 13)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_E;
			}	
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_G)
		{
			if (TempDelta < 0)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_H;
			}
			else if (TempDelta > 8)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_F;
			}			
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_H)
		{
			if (TempDelta < -5)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_I;
			}
			else if (TempDelta > 3)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_G;
			}		
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_I)
		{
			if (TempDelta < -10)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_J;
			}
			else if (TempDelta > -2)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_H;
			}	
		}
		else if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_J)
		{
			if (TempDelta < -15)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_K;
			}
			else if (TempDelta > -7)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_I;
			}	
		}	
		else //if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_K)
		{
			if (TempDelta > -12)
			{
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_J;
			}	
		}

		if (Tempr.T1TSDeltaZoneBak != Tempr.T1TSDeltaZone)	//发生变化时重新计时
		{
			Tempr.u16_T1TSDeltaCount = 0;
			
			if (Tempr.T1TSDeltaZone == ENUM_TEMPDELTAZONE_K)	//到达K区间记录室内温度
			{
				Tempr.u16_ZoneKT1Mul10 = T1.s16_ValueMul10bc;
			}
			
			if (Tempr.T1TSDeltaZoneBak > ENUM_TEMPDELTAZONE_D)	//区间从D区间以外回到A-D重新计算起始频率
			{
				if ((Tempr.T1TSDeltaZone >= ENUM_TEMPDELTAZONE_A) && (Tempr.T1TSDeltaZone <= ENUM_TEMPDELTAZONE_D))	
				{
					App_Comp_RunHzInitIndex();				//20231130
				}				
			}
			else
			{
				if (Tempr.T1TSDeltaZone < Tempr.T1TSDeltaZoneBak)	//A-D区间之内发生温差上升的
				{
					App_Comp_RunHzInitIndex();				//20231214
				}
			}
		}
	}
	
	Tempr.T1TSDeltaZoneBak = Tempr.T1TSDeltaZone;		//备份更新
}
/****************************************************************************************************
Function Name       :void	TempT4CoolZone(void)
Description         :制冷时室外温度区间
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void  TempT4CoolZone(void)
{
	if (SystemMode.f_Cold == 1)
	{
		if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_INIT)
		{
			if (T4.s16_ValueMul10 > 600)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_PRO;
			}
			else if (T4.s16_ValueMul10 >= 550)		//T4_COOL10
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_11;
			}
			else if (T4.s16_ValueMul10 >= 500)	//T4_COOL9
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_10;
			}
			else if (T4.s16_ValueMul10 >= 450)	//T4_COOL8
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_9;
			}
			else if (T4.s16_ValueMul10 >= 400)	//T4_COOL7
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_8;
			}
			else if (T4.s16_ValueMul10 >= 330)	//T4_COOL6
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_7;
			}
			else if (T4.s16_ValueMul10 >= 300)	//T4_COOL5
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_6;
			}
			else if (T4.s16_ValueMul10 >= 250)	//T4_COOL4
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_5;
			}
			else if (T4.s16_ValueMul10 >= 200)	//T4_COOL3
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_4;
			}
			else if (T4.s16_ValueMul10 >= 150)	//T4_COOL2
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_3;
			}
			else if (T4.s16_ValueMul10 >= 100)	//T4_COOL1
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_2;
			}
			else if (T4.s16_ValueMul10 >= 0)	//T4_COOL0
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_1;
			}
			else if (T4.s16_ValueMul10 >= -60)	//T4_COOLSTOP1
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_0;
			}
			else if (T4.s16_ValueMul10 < -80)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_PRO1;
			}
			else	//T4_FC_MAX_STOP
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_STOP;
			}
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_PRO)
		{
			if (T4.s16_ValueMul10 < 590)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_INIT;
			}
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_11)
		{
			if (T4.s16_ValueMul10 > 600)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_PRO;
			}			
			else if (T4.s16_ValueMul10 < 540)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_10;
			}
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_10)
		{
			if (T4.s16_ValueMul10 < 490)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_9;
			}
			else if (T4.s16_ValueMul10 > 550)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_11;
			}
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_9)
		{
			if (T4.s16_ValueMul10 < 440)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_8;
			}
			else if (T4.s16_ValueMul10 > 500)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_10;
			}	
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_8)
		{
			if (T4.s16_ValueMul10 < 390)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_7;
			}
			else if (T4.s16_ValueMul10 > 450)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_9;
			}	
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_7)
		{
			if (T4.s16_ValueMul10 < 320)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_6;
			}
			else if (T4.s16_ValueMul10 > 400)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_8;
			}	
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_6)
		{
			if (T4.s16_ValueMul10 < 290)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_5;
			}
			else if (T4.s16_ValueMul10 > 330)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_7;
			}	
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_5)
		{
			if (T4.s16_ValueMul10 < 240)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_4;
			}
			else if (T4.s16_ValueMul10 > 300)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_6;
			}	
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_4)
		{
			if (T4.s16_ValueMul10 < 190)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_3;
			}
			else if (T4.s16_ValueMul10 > 250)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_5;
			}	
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_3)
		{
			if (T4.s16_ValueMul10 < 140)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_2;
			}
			else if (T4.s16_ValueMul10 > 200)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_4;
			}		
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_2)
		{
			if (T4.s16_ValueMul10 < 90)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_1;
			}
			else if (T4.s16_ValueMul10 > 150)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_3;
			}	
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_1)
		{
			if (T4.s16_ValueMul10 < -10)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_0;
			}
			else if (T4.s16_ValueMul10 > 100)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_2;
			}	
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_0)
		{
			if (T4.s16_ValueMul10 < -80)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_STOP;
			}
			else if (T4.s16_ValueMul10 > 0)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_1;
			}		
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_STOP)
		{
			if (T4.s16_ValueMul10 > -60)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_0;
			}
			else if (T4.s16_ValueMul10 < -80)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_PRO1;
			}
		}
		else if (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_PRO1)
		{
			if (T4.s16_ValueMul10 > -70)
			{
				Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_INIT;
			}
		}
	}
	else
	{
		Tempr.T4CoolZone = ENUM_TEMPT4COOLZONE_INIT;
	}
}
/****************************************************************************************************
Function Name       :void	TempT4CoolZone(void)
Description         :制热时室外温度区间
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    TempT4HeatZone(void)
{
	if (SystemMode.f_Heat == 1)
	{
		if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_INIT)
		{
			//陈工 Kerwin TCL德龙 移动空调：2024-4-08 改成35℃，30℃跳机满足不了性能需求
			if (T4.s16_ValueMul10 >= 350)	//T4_HOT13(28℃)-->T4_HOT13(30℃) lcx 20240329 规格书文字描述30   //300->350
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_PRO;
			}
			else if (T4.s16_ValueMul10 >= 250)	//T4_HOT12(25℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_13;
			}
			else if (T4.s16_ValueMul10 >= 220)	//T4_HOT11(22℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_12;
			}	
			else if (T4.s16_ValueMul10 >= 190)	//T4_HOT10(19℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_11;
			}
			else if (T4.s16_ValueMul10 >= 160)	//T4_HOT9(16℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_10;
			}
			else if (T4.s16_ValueMul10 >= 130)	//T4_HOT8(13℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_9;
			}	
			else if (T4.s16_ValueMul10 >= 100)	//T4_HOT7(10℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_8;
			}
			else if (T4.s16_ValueMul10 >= 70)	//T4_HOT6(7℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_7;
			}	
			else if (T4.s16_ValueMul10 >= 40)	//T4_HOT5(4℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_6;
			}	
			else if (T4.s16_ValueMul10 >= 10)	//T4_HOT4(1℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_5;
			}
			else if (T4.s16_ValueMul10 >= -30)	//T4_HOT3(-3℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_4;
			}	
			else if (T4.s16_ValueMul10 >= -70)	//T4_HOT2(-7℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_3;
			}
			else if (T4.s16_ValueMul10 >= -100)	//T4_HOT1(-10℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_2;
			}
			else if (T4.s16_ValueMul10 >= -190)	//T4_HOT0(-19℃)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_1;
			}
			else
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_0;
			}
			
			
			if (T4.s16_ValueMul10 < C_TEMPT4HEAT_PRO1)//60)
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_PRO1;
			}
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO1)
		{
			if (T4.s16_ValueMul10 > C_TEMPT4HEAT_PRO1)//规格书要求6度（60）。图表上-26度（-260）
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_INIT;	//恢复
			}
		}
		else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO) //
		{
			//if (T4.s16_ValueMul10 < 260)//120)
			if (T4.s16_ValueMul10 < 340)//120) //260>290 cx 20240329 规格书文字描述30-1度是恢复  //290->340
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_INIT;//8;
			}		
		}
		else
		{
			if (T4.s16_ValueMul10 < C_TEMPT4HEAT_PRO1)//规格书要求6度（60）。图表上-26度（-260）
			{
				Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_PRO1;
			}
			else
			{
				if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_13)
				{
					if (T4.s16_ValueMul10 < 240)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_12;
					}
					
					if (T4.s16_ValueMul10 >= 350)	//T4_HOT13(28℃)-->T4_HOT13(30℃) lcx 20240329 //300->350
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_PRO;
					}
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_12)
				{
					if (T4.s16_ValueMul10 < 210)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_11;
					}

					if (T4.s16_ValueMul10 > 250)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_13;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_11)
				{
					if (T4.s16_ValueMul10 < 180)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_10;
					}

					if (T4.s16_ValueMul10 > 220)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_12;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_10)
				{
					if (T4.s16_ValueMul10 < 150)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_9;
					}

					if (T4.s16_ValueMul10 > 190)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_11;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_9)
				{
					if (T4.s16_ValueMul10 < 120)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_8;
					}

					if (T4.s16_ValueMul10 > 160)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_10;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_8)
				{
					if (T4.s16_ValueMul10 < 90)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_7;
					}

					if (T4.s16_ValueMul10 > 130)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_9;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_7)
				{
					if (T4.s16_ValueMul10 < 60)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_6;
					}

					if (T4.s16_ValueMul10 > 100)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_8;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_6)
				{
					if (T4.s16_ValueMul10 < 30)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_5;
					}

					if (T4.s16_ValueMul10 > 70)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_7;
					}				
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_5)
				{
					if (T4.s16_ValueMul10 < 0)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_4;
					}

					if (T4.s16_ValueMul10 > 40)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_6;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_4)
				{
					if (T4.s16_ValueMul10 < -40)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_3;
					}

					if (T4.s16_ValueMul10 > 10)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_5;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_3)
				{
					if (T4.s16_ValueMul10 < -80)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_2;
					}

					if (T4.s16_ValueMul10 > -30)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_4;
					}			
				}
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_2)
				{
					if (T4.s16_ValueMul10 < -110)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_1;
					}

					if (T4.s16_ValueMul10 > -70)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_3;
					}				
				}	
				else if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_1)
				{
					if (T4.s16_ValueMul10 < -200)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_0;
					}

					if (T4.s16_ValueMul10 > -100)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_2;
					}				
				}	
				else //if (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_0)
				{
					if (T4.s16_ValueMul10 > -190)
					{
						Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_1;
					}			
				}
			}
		}			
	}
	else
	{
		Tempr.T4HeatZone = ENUM_TEMPT4HEATZONE_INIT;
	}
}
/****************************************************************************************************
Function Name       :void	TempT2HeatZone(void)
Description         :T2制热温区
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
//S8	  s8_TempDelta;
//S8	  s8_EE;

void    TempT2HeatZone(void)
{
	S8    s8_TempDelta;
	S8    s8_EE;
	
	if (SystemMode.f_Heat == 1)
	{		
		s8_TempDelta = 0;		//按原值
		
		if 	(Fan.Indoor.Level == ENUM_FANLEVEL_MED)		
		{	
			//EE.PARA. (U8)C_REMEMBER_PARA08_00;		//-2	        //室内风速中风时温度矫正	
			s8_EE = (S8)EEP.u8_rdBuf[109];
			s8_EE = TempValueMul10(s8_EE);	//*10
			s8_TempDelta += s8_EE;		
		}
		else if (Fan.Indoor.Level == ENUM_FANLEVEL_LOW)		
		{	
			//EE.PARA. (U8)C_REMEMBER_PARA08_01;		//-3	        //室内风速低风时温度矫正	
			s8_EE = (S8)EEP.u8_rdBuf[110];
			s8_EE = TempValueMul10(s8_EE);	//*10			
			s8_TempDelta += s8_EE;	
		}
		else if (Fan.Indoor.Level == ENUM_FANLEVEL_LOW_S)	
		{	
			//EE.PARA. (U8)C_REMEMBER_PARA08_02;		//-4	        //室内风速微风时温度矫正
			s8_EE = (S8)EEP.u8_rdBuf[111];
			s8_EE = TempValueMul10(s8_EE);	//*10			
			s8_TempDelta += s8_EE;		
		}
		else
		{	
			s8_TempDelta = 0;		//按原值
		}
		
		if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_INIT)
		{
			if (T2.s16_ValueMul10 >= (TempValueMul10(EEP.u8_rdBuf[115]) + s8_TempDelta))		//EE.PARA. (U8)C_REMEMBER_PARA08_06;		//64	        //T2_HEAT3
			{
				Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_FASTDOWN;	//快速限频
			}
			else if (T2.s16_ValueMul10 >= (TempValueMul10(EEP.u8_rdBuf[114]) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_05;		//62	        //T2_HEAT2
			{
				Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_SLOWDOWN;	//慢速限频
			}
			else if (T2.s16_ValueMul10 >= (TempValueMul10(EEP.u8_rdBuf[113]) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_04;		//58	        //T2_HEAT1
			{
				Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_CON;			//频率保持
			}			
			else if (T2.s16_ValueMul10 >= (TempValueMul10(EEP.u8_rdBuf[112]) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_03;		//52	        //T2_HEAT0	
			{
				Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_SLOWUP;		//频率慢升
			}
			else
			{
				Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_OK;			//正常控制
			}
		}
		else
		{
			if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_PRO)
			{
				//保护取消条件
				if (T2.s16_ValueMul10 <= (TempValueMul10(EEP.u8_rdBuf[114]) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_05;		//62	(T2_HEAT2)
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_INIT;
				}
			}
			else if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_FASTDOWN)
			{
				if (T2.s16_ValueMul10 < (TempValueMul10(EEP.u8_rdBuf[115]-1) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_06 		//64	(T2_HEAT3-delta)
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_SLOWDOWN;	//慢速限频
				}				
			}
			else if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_SLOWDOWN)
			{
				if (T2.s16_ValueMul10 < (TempValueMul10(EEP.u8_rdBuf[114]-1) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_05;		//62	(T2_HEAT2-delta)
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_CON;			//频率保持
				}
				else if (T2.s16_ValueMul10 > (TempValueMul10(EEP.u8_rdBuf[115]) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_06 		//64 (T2_HEAT3)
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_FASTDOWN;	//快速限频
				}
			}
			else if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_CON)
			{
				if (T2.s16_ValueMul10 < (TempValueMul10(EEP.u8_rdBuf[113]-1) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_04;		//58    (T2_HEAT1-delta)
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_SLOWUP;		//频率慢升
				}
				else if (T2.s16_ValueMul10 > (TempValueMul10(EEP.u8_rdBuf[114]) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_05;	//62    (T2_HEAT2) 
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_SLOWDOWN;	//慢速限频
				}			
			}
			else if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_SLOWUP)
			{
				if (T2.s16_ValueMul10 < (TempValueMul10(EEP.u8_rdBuf[112]-1) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_03;		//52    (T2_HEAT0-delta)
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_OK;		//正常控制
				}
				else if (T2.s16_ValueMul10 > (TempValueMul10(EEP.u8_rdBuf[113]) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_04;		//58  (T2_HEAT1)
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_CON;		//频率保持
				}			
			}
			else	//OK
			{
				if (T2.s16_ValueMul10 > (TempValueMul10(EEP.u8_rdBuf[112]) + s8_TempDelta))	//EE.PARA. (U8)C_REMEMBER_PARA08_03;		//52  (T2_HEAT0)
				{
					Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_SLOWUP;		//频率慢升
				}			
			}
		}
				
		if (T2.s16_ValueMul10 >= (TempValueMul10(EEP.u8_rdBuf[116]) + s8_TempDelta))		//EE.PARA. (U8)C_REMEMBER_PARA08_07;		//66	        //T2_HEAT4
		{
			if (++Tempr.u16_T2ProCount >= 500)				//维持5s
			{
				Tempr.u16_T2ProCount = 0;
				Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_PRO;		//保护
			}
		}
		else
		{
			Tempr.u16_T2ProCount = 0;
		}
	}
	else
	{
		Tempr.T2HeatZone = ENUM_TEMPT2HEATZONE_OK;
	}
}
/****************************************************************************************************
Function Name       :void	Func_Temprature(void)
Description         :温度处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Temprature(void)
{
	TempValueCon();			//温度值处理
	TempT1TSDeltaZone();	//T1-TS温差区间
	TempT4CoolZone();		//T4制冷温区
	TempT4HeatZone();		//T4制热温区
	TempT2HeatZone();		//T2制热温区
}
