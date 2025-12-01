/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Protect.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/23
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_PROTECT    Protect;

/****************************************************************************************************
Function Name       :void    Protect_Tp(void)
Description         :排气温度保护
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_Tp(void)
{
	if (Protect.u16_TpErrCnt)
	{
		if (Protect.u32_TpErr_1HourCnt < 0xFFFFFFFF)
		{
			Protect.u32_TpErr_1HourCnt ++;
		}

		if ((Protect.u32_TpErr_1HourCnt >=180000) 
			&& (Protect.u16_TpErrCnt < 3)
			&& (Protect.f_Tp == 0))
		{
			Protect.u32_TpErr_1HourCnt = 0;
			Protect.u16_TpErrCnt = 0;
		}
	}
	else 
	{
		Protect.u32_TpErr_1HourCnt = 0;
	}
	
	if (Protect.f_Tp == 0)				  //正常
	{
		// 压缩机开启1分钟后检测，连续10s检测到排气温度Td≥110℃（参数P24），则停机保护
		if ((Tp.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P24)) 
			&& (Comp.f_DrvOn) 
			&& (Comp.u32_RunContCount >= 6000))    //压缩机运行1分钟后才检测（6000*10ms=60s=1min）
		{
			if (Protect.u16_TpCount < 0xFFFF)
			{
				Protect.u16_TpCount ++;
			}
			
			if (Protect.u16_TpCount >= 1000)		//10秒
			{
				if (!Protect.f_Tp)
				{
					Protect.u16_TpErrCnt ++;
				}
				
				Protect.f_Tp = 1;		  //排气温度保护生效
			}
		}
		else 
		{
			Protect.u16_TpCount = 0;
			Protect.u16_TpErrRemoveCount = 0;
		}
	}
	else 
	{
		// 当检测到排气温度Td≤85℃（参数P25）时，则退出此保护
		// 如30min内发生三次此故障，则非掉电不可恢复（前两次可自动恢复）
		if ((Protect.u32_TpErr_1HourCnt < 180000) && (Protect.u16_TpErrCnt < 3))
		{
			if (Tp.s16_ValueMul10 <= TempValueMul10(FtyPara.s16P25))    //使用P25参数（85℃）
			{
				if (Protect.u16_TpErrRemoveCount < 0xFFFF)
				{
					Protect.u16_TpErrRemoveCount ++;
				}
				
				if (Protect.u16_TpErrRemoveCount >= 1000)		//10秒
				{
					Protect.f_Tp = 0;		  //排气温度保护恢复
				}
			}
			else 
			{
				Protect.u16_TpCount = 0;
				Protect.u16_TpErrRemoveCount = 0;
			}
		}
	}
}
//{
//	if (Protect.TpStatus == ENUM_PROSTATUS_NORMAL)
//	{		
//		if (Tp.s16_ValueMul10 > TempValueMul10(EEP.u8_rdBuf[126]))		//EE.PARA. C_REMEMBER_PARA11_00;		//90		    //TP0	
//		{
//			Protect.TpStatus = ENUM_PROSTATUS_SLOWUP;
//		}
//	}
//	else if (Protect.TpStatus == ENUM_PROSTATUS_SLOWUP)
//	{		
//		if (Tp.s16_ValueMul10 < TempValueMul10(EEP.u8_rdBuf[126]-1))	//EE.PARA. C_REMEMBER_PARA11_00;		//90		    //TP0	//TP0-delta
//		{
//			Protect.TpStatus = ENUM_PROSTATUS_NORMAL;
//		}
//		else if (Tp.s16_ValueMul10 > TempValueMul10(EEP.u8_rdBuf[127]))	//EE.PARA. C_REMEMBER_PARA11_01;		//95		    //TP1
//		{
//			Protect.TpStatus = ENUM_PROSTATUS_CONT;
//		}
//	}
//	else if (Protect.TpStatus == ENUM_PROSTATUS_CONT)
//	{
//		if (Tp.s16_ValueMul10 < TempValueMul10(EEP.u8_rdBuf[127]-1))	//EE.PARA. C_REMEMBER_PARA11_01;		//95		    //TP1  //TP1-delta
//		{
//			Protect.TpStatus = ENUM_PROSTATUS_SLOWUP;
//		}
//		else if (Tp.s16_ValueMul10 > TempValueMul10(EEP.u8_rdBuf[128]))	//EE.PARA. C_REMEMBER_PARA11_02;		//100		    //TP2
//		{
//			Protect.TpStatus = ENUM_PROSTATUS_SLOWDOWN;
//		}
//	}
//	else if (Protect.TpStatus == ENUM_PROSTATUS_SLOWDOWN)
//	{
//		if (Tp.s16_ValueMul10 < TempValueMul10(EEP.u8_rdBuf[128]-1))    //EE.PARA. C_REMEMBER_PARA11_02;		//100		    //TP2  //TP2-delta
//		{
//			Protect.TpStatus = ENUM_PROSTATUS_CONT;
//		}
//		else if (Tp.s16_ValueMul10 > TempValueMul10(EEP.u8_rdBuf[129]))	//EE.PARA. C_REMEMBER_PARA11_03;		//105		    //TP3
//		{
//			Protect.TpStatus = ENUM_PROSTATUS_FASTDOWN;
//		}
//	}
//	else if (Protect.TpStatus == ENUM_PROSTATUS_FASTDOWN)
//	{
//		if (Tp.s16_ValueMul10 < TempValueMul10(EEP.u8_rdBuf[129]-1))    //EE.PARA. C_REMEMBER_PARA11_03;		//105		    //TP3  //TP3-delta
//		{
//			Protect.TpStatus = ENUM_PROSTATUS_SLOWDOWN;
//		}
//	}
//	
//	//---
//	
//	if (Protect.f_Tp == 0)				  //正常
//	{
//		if (Tp.s16_ValueMul10 >= TempValueMul10(EEP.u8_rdBuf[130]))    //EE.PARA. C_REMEMBER_PARA11_04;		   //110		    //TP4
//		{
//			if (++Protect.u16_TpCount >= 500)
//			{
//				Protect.u16_TpCount = 0;
//				Protect.f_Tp = 1;		  //排气温度保护生效
//				Protect.TpStatus = ENUM_PROSTATUS_PROTECT;
//			}
//		}
//		else
//		{
//			Protect.u16_TpCount = 0;
//		}
//	}
//	else
//	{
//		if (Tp.s16_ValueMul10 <= TempValueMul10(EEP.u8_rdBuf[128]))	  //EE.PARA. C_REMEMBER_PARA11_02;		//100		    //TP2
//		{
//			Protect.f_Tp = 0;			//恢复正常
//			Protect.TpStatus = ENUM_PROSTATUS_NORMAL;
//		}
//	}
//}

/****************************************************************************************************
Function Name       :void    Protect_T2Heat(void)
Description         :制冷室内换气器防冻结
Input               :
Return              :
Author              ：冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_T2Heat(void)
{	
	if ((SystemMode.f_Heat == 1) && (T2.f_Error == 0))
	{
		if (Protect.T2HeatStatus == ENUM_PROSTATUS_NORMAL)
		{
			if (T2.s16_ValueMul10 >= 640)		
			{
				if (++Protect.u16_T2HeatCount >= 200)	//2s
				{
					Protect.u16_T2HeatCount = 0;
					Protect.f_T2Heat = 1;		//T2制冷温度过低保护生效
					Protect.T2HeatStatus = ENUM_PROSTATUS_PROTECT;
				}
			}
			else if (T2.s16_ValueMul10 >= 550)	//55℃
			{
				if (++Protect.u16_T2HeatCount >= 200)	//2s
				{
					Protect.u16_T2HeatCount = 0;
					Protect.T2HeatStatus = ENUM_PROSTATUS_FASTDOWN;
				}
			}
			else
			{
				Protect.u16_T2HeatCount = 0;
			}
		}
		else if (Protect.T2HeatStatus == ENUM_PROSTATUS_FASTDOWN)
		{
			if (T2.s16_ValueMul10 >= 640)		
			{
				if (++Protect.u16_T2HeatCount >= 200)	//5s
				{
					Protect.u16_T2HeatCount = 0;
					Protect.f_T2Heat = 1;		//T2制冷温度过低保护生效
					Protect.T2HeatStatus = ENUM_PROSTATUS_PROTECT;
				}
			}
			else if (T2.s16_ValueMul10 < 530)	//53℃
			{
				if (++Protect.u16_T2HeatCount >= 200)	//2s
				{
					EAHeater.f_T2HighRecDelay = 1;
					Protect.u16_T2HeatCount = 0;
					Protect.f_T2Heat = 0;
					Protect.T2HeatStatus = ENUM_PROSTATUS_NORMAL;
				}
			}
			else
			{
				Protect.u16_T2HeatCount = 0;
			}
		}
		else if (Protect.T2HeatStatus == ENUM_PROSTATUS_PROTECT)
		{
			if (T2.s16_ValueMul10 <500)		
			{
				Protect.f_T2Heat = 0;		//T2制冷温度过低保护生效
				Protect.T2HeatStatus = ENUM_PROSTATUS_NORMAL;
			}
			
			Protect.u16_T2HeatCount = 0;
		}
	}
	else 
	{
		Protect.f_T2Heat = 0;
		Protect.T2HeatStatus = ENUM_PROSTATUS_NORMAL;
	}
}
/****************************************************************************************************
Function Name       :void    Protect_T2Cold(void)
Description         :制冷室内换气器防冻结
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_T2Cold(void)
{	
	S16    s16_TempValue;
	S16    s16_TempValue1;	

	if (SystemMode.f_Cold == 1)
	{
		if (Protect.T2ColdStatus == ENUM_PROSTATUS_NORMAL)
		{
			s16_TempValue = (S8)EEP.u8_rdBuf[135];					//EE.PARA. (U8)C_REMEMBER_PARA12_04;		//14(7℃)		    //T2_COLD4
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);	
			
			if (T2.s16_ValueMul10 < s16_TempValue)		
			{
				Protect.T2ColdStatus = ENUM_PROSTATUS_SLOWUP;
			}
		}
		else if (Protect.T2ColdStatus == ENUM_PROSTATUS_SLOWUP)
		{
			s16_TempValue = (S8)EEP.u8_rdBuf[134];					//EE.PARA. (U8)C_REMEMBER_PARA12_03;		//11(5.5℃)		    //T2_COLD3
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);

			s16_TempValue1 = (S8)EEP.u8_rdBuf[135];					//EE.PARA. (U8)C_REMEMBER_PARA12_04;		//14(7℃)		    //T2_COLD4
			s16_TempValue1 += 2;
			s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1); 
			
			if (T2.s16_ValueMul10 < s16_TempValue)	   				//T2_COLD3  5.5℃
			{
				Protect.T2ColdStatus = ENUM_PROSTATUS_CONT;
			}
			else if (T2.s16_ValueMul10 > s16_TempValue1)			//T2_COLD4 7℃ + Delta	
			{
				Protect.T2ColdStatus = ENUM_PROSTATUS_NORMAL;
			}
		}
		else if (Protect.T2ColdStatus == ENUM_PROSTATUS_CONT)
		{
			s16_TempValue = (S8)EEP.u8_rdBuf[133];					//EE.PARA. (U8)C_REMEMBER_PARA12_02;		//8(4℃)		   		//T2_COLD2
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);			

			s16_TempValue1 = (S8)EEP.u8_rdBuf[134];					//EE.PARA. (U8)C_REMEMBER_PARA12_03;		//11(5.5℃)		    //T2_COLD3
			s16_TempValue1 += 2;
			s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1); 
			
			if (T2.s16_ValueMul10 < s16_TempValue)					//低于 T2_COLD2  4℃
			{
				Protect.T2ColdStatus = ENUM_PROSTATUS_SLOWDOWN;
			}
			else if (T2.s16_ValueMul10 > s16_TempValue1)			//高于 T2_COLD3 5.5℃ + DELTA
			{
				Protect.T2ColdStatus = ENUM_PROSTATUS_SLOWUP;
			}
		}
		else if (Protect.T2ColdStatus == ENUM_PROSTATUS_SLOWDOWN)
		{
			s16_TempValue = (S8)EEP.u8_rdBuf[132];					//EE.PARA. (U8)C_REMEMBER_PARA12_01;		//4(2℃)		   		//T2_COLD1
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);	

			s16_TempValue1 = (S8)EEP.u8_rdBuf[133];					//EE.PARA. (U8)C_REMEMBER_PARA12_02;		//8(4℃)		   		//T2_COLD2
			s16_TempValue1 += 2;
			s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1);			
			
			if (T2.s16_ValueMul10 < s16_TempValue)					//T2_COLD1  2℃
			{
				Protect.T2ColdStatus = ENUM_PROSTATUS_FASTDOWN;
			}
			else if (T2.s16_ValueMul10 > s16_TempValue1)			//T2_COLD2 4℃ + DELTA
			{
				Protect.T2ColdStatus = ENUM_PROSTATUS_CONT;
			}
		}
		else if (Protect.T2ColdStatus == ENUM_PROSTATUS_FASTDOWN)
		{
			s16_TempValue1 = (S8)EEP.u8_rdBuf[132];					//EEP.u8_wrBuf[132] = (U8)C_REMEMBER_PARA12_01;		//4(2℃)		   		//T2_COLD1
			s16_TempValue1 += 2;
			s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1);			
			
			if (T2.s16_ValueMul10 > s16_TempValue1)					//T2_COLD1 2℃ + DELTA
			{
				Protect.T2ColdStatus = ENUM_PROSTATUS_SLOWDOWN;
			}
		}		
		
		//---
		
		if (Protect.f_T2Cold == 0)
		{
			s16_TempValue = (S8)EEP.u8_rdBuf[131];					//EE.PARA. (U8)C_REMEMBER_PARA12_00;		//0(0℃)		   		//T2_COLD0
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
			
			if (T2.s16_ValueMul10 <= s16_TempValue)		
			{
				if (++Protect.u16_T2ColdCount >= 500)	//5s
				{
					Protect.u16_T2ColdCount = 0;
					Protect.f_T2Cold = 1;		//T2制冷温度过低保护生效
					Protect.T2ColdStatus = ENUM_PROSTATUS_PROTECT;
				}
			}
			else
			{
				Protect.u16_T2ColdCount = 0;
			}
		}
		else
		{
			s16_TempValue = (S8)EEP.u8_rdBuf[133];					//EE.PARA. (U8)C_REMEMBER_PARA12_02;		//8(4℃)		   		//T2_COLD2
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
			
			if (T2.s16_ValueMul10 >= s16_TempValue)	
			{
				Protect.f_T2Cold = 0;
				Protect.T2ColdStatus = ENUM_PROSTATUS_NORMAL;
			}
		}
	}
	else
	{
		Protect.f_T2Cold = 0;
		Protect.T2ColdStatus = ENUM_PROSTATUS_NORMAL;
	}
}
/****************************************************************************************************
Function Name       :void    Protect_T3Cold(void)
Description         :制冷室外换气器防过热
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_T3Cold(void)
{		
	S16    s16_TempValue;
	S16    s16_TempValue1;	
	
	if (SystemMode.f_Cold == 1)
	{
		if (Protect.T3ColdStatus == ENUM_PROSTATUS_NORMAL)
		{
			//参数没有负数可能转U8类型
			s16_TempValue = (U8)EEP.u8_rdBuf[136];					//EE.PARA. C_REMEMBER_PARA13_00;		//104(52℃)		 //T3_COOL0	
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
					
			if (T3.s16_ValueMul10 > s16_TempValue)					//T3_COOL0  52℃
			{
				Protect.T3ColdStatus = ENUM_PROSTATUS_SLOWUP;
			}
		}
		else if (Protect.T3ColdStatus == ENUM_PROSTATUS_SLOWUP)
		{
			s16_TempValue = (U8)EEP.u8_rdBuf[136];					//EE.PARA. C_REMEMBER_PARA13_00;		//104(52℃)		   	//T3_COOL0
			s16_TempValue -= 2;
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
			
			s16_TempValue1 = (U8)EEP.u8_rdBuf[137];					//EE.PARA. C_REMEMBER_PARA13_01;		//116(58℃)		   	//T3_COOL1	
			s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1);
			
			if (T3.s16_ValueMul10 < s16_TempValue)					//T3_COOL0 52℃ - DELTA
			{
				Protect.T3ColdStatus = ENUM_PROSTATUS_NORMAL;
			}
			else if (T3.s16_ValueMul10 > s16_TempValue1)			//T3_COOL1  58℃
			{
				Protect.T3ColdStatus = ENUM_PROSTATUS_CONT;
			}
		}
		else if (Protect.T3ColdStatus == ENUM_PROSTATUS_CONT)
		{
			s16_TempValue = (U8)EEP.u8_rdBuf[137];					//EE.PARA. C_REMEMBER_PARA13_01;		//116(58℃)		  //T3_COOL1	
			s16_TempValue -= 2;
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);	

			s16_TempValue1 = (U8)EEP.u8_rdBuf[138];					//EE.PARA. C_REMEMBER_PARA13_02;		//120(60℃)		  //T3_COOL2	
			s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1);			
			
			if (T3.s16_ValueMul10 < s16_TempValue)					//T3_COOL1 58℃ - DELTA
			{
				Protect.T3ColdStatus = ENUM_PROSTATUS_SLOWUP;
			}
			else if (T3.s16_ValueMul10 > s16_TempValue1)			//T3_COOL2 60℃
			{
				Protect.T3ColdStatus = ENUM_PROSTATUS_SLOWDOWN;
			}
		}
		else if (Protect.T3ColdStatus == ENUM_PROSTATUS_SLOWDOWN)
		{
			s16_TempValue = (U8)EEP.u8_rdBuf[138];					//EE.PARA. C_REMEMBER_PARA13_02;		//120(60℃)		  //T3_COOL2
			s16_TempValue -= 2;
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);	

			s16_TempValue1 = (U8)EEP.u8_rdBuf[139];					//EE.PARA. C_REMEMBER_PARA13_03;		//124(62℃)		  //T3_COOL3
			s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1);				
			
			if (T3.s16_ValueMul10 < s16_TempValue)					//T3_COOL2 60℃ - DELTA
			{
				Protect.T3ColdStatus = ENUM_PROSTATUS_CONT;
			}
			else if (T3.s16_ValueMul10 > s16_TempValue1)			//T3_COOL3  62℃
			{
				Protect.T3ColdStatus = ENUM_PROSTATUS_FASTDOWN;
			}
		}
		else if (Protect.T3ColdStatus == ENUM_PROSTATUS_FASTDOWN)
		{
			s16_TempValue = (U8)EEP.u8_rdBuf[139];					//EE.PARA. C_REMEMBER_PARA13_03;		//124(62℃)		 //T3_COOL3
			s16_TempValue -= 2;
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
			
			if (T3.s16_ValueMul10 < s16_TempValue)					//T3_COOL3 62℃ - DELTA
			{
				Protect.T3ColdStatus = ENUM_PROSTATUS_SLOWDOWN;
			}
		}		
		
		//----
		
		if (Protect.f_T3Cold == 0)
		{			
			s16_TempValue = (U8)EEP.u8_rdBuf[140];					//EE.PARA. C_REMEMBER_PARA13_04;		//128(64℃)		//T3_COOL4
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);			
			
			if (T3.s16_ValueMul10 >= s16_TempValue)					//高于 T3_COOL4   64℃
			{
				if (++Protect.u16_T3ColdCount >= 500)
				{
					Protect.u16_T3ColdCount = 0;
					Protect.f_T3Cold = 1;
					Protect.T3ColdStatus = ENUM_PROSTATUS_PROTECT;
				}
			}
			else
			{
				Protect.u16_T3ColdCount = 0;
			}
		}
		else
		{
			s16_TempValue = (U8)EEP.u8_rdBuf[138];					//EE.PARA. C_REMEMBER_PARA13_02;		//120(60℃)		  //T3_COOL2
			s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
			
			if (T3.s16_ValueMul10 <= s16_TempValue)					//低于 T3_COOL2   60℃
			{
				Protect.f_T3Cold = 0;
				Protect.T3ColdStatus = ENUM_PROSTATUS_NORMAL;
			}
		}
	}
	else
	{
		Protect.f_T3Cold = 0;
		Protect.T3ColdStatus = ENUM_PROSTATUS_NORMAL;	
	}
}
/****************************************************************************************************
Function Name       :void    Protect_CurrentCold(void)
Description         :制冷电流过大保护
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_CurrentCold(void)
{
	U8     OutDoorCurrentMul8;		//依据通信接收电流*8的数值
	U16    u16_CurrentValueMul10;	//转换电流*10的数值
	U8     CurrentProValueMul10;    //电流保护阈值*10
	
	OutDoorCurrentMul8 = CommMotDrv.BaseRun.Rx.Byte9.OutDoorCurrentMul8;
	u16_CurrentValueMul10 = TempValueMul10(OutDoorCurrentMul8);
	u16_CurrentValueMul10 >>= 3;	//转换电流*10的数值
	
	if ((T4.f_Error == 1) || (SystemMode.f_Cold == 0))		//故障或非制冷回初始化
	{
		Protect.T4ColdZone = ENUM_T4COLDZONE_INIT;
	}
	
	if (SystemMode.f_Cold == 1)
	{
		//计算制冷T4温度区间
		if (Protect.T4ColdZone == ENUM_T4COLDZONE_INIT)
		{
			if (T4.s16_ValueMul10 >= 460)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL1;
			}
			else if (T4.s16_ValueMul10 >= 420)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL2;
			}
			else if (T4.s16_ValueMul10 >= 380)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL3;
			}	
			else
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL4;
			}
			
			CurrentProValueMul10 = 0xFF;	//初始阶段阈值最大化
		}
		else if (Protect.T4ColdZone == ENUM_T4COLDZONE_COOL1)
		{
			CurrentProValueMul10 = 140;		//ICMAX_AC_COOL1  14A
			
			if (T4.s16_ValueMul10 < 450)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL2;
			}
		}
		else if (Protect.T4ColdZone == ENUM_T4COLDZONE_COOL2)
		{
			CurrentProValueMul10 = 135;		//ICMAX_AC_COOL2  13.5A
			
			if (T4.s16_ValueMul10 < 410)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL3;
			}
			else if (T4.s16_ValueMul10 > 460)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL1;
			}
		}
		else if (Protect.T4ColdZone == ENUM_T4COLDZONE_COOL3)
		{
			CurrentProValueMul10 = 105;		//ICMAX_AC_COOL3  10.5A
			
			if (T4.s16_ValueMul10 < 370)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL4;
			}
			else if (T4.s16_ValueMul10 > 420)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL2;
			}
		}
		else if (Protect.T4ColdZone == ENUM_T4COLDZONE_COOL4)
		{
			CurrentProValueMul10 =  100;		//ICMAX_AC_COOL4  10A
			
			if (T4.s16_ValueMul10 > 380)
			{
				Protect.T4ColdZone = ENUM_T4COLDZONE_COOL3;
			}
		}
		
		//---
		
		if (Protect.CurrColdStatus == ENUM_PROSTATUS_NORMAL)
		{
			if (u16_CurrentValueMul10 > (CurrentProValueMul10 - 20))		//AcCurLimit_A[0] = ICMAX_AC_COOLx - 2A
			{
				Protect.CurrColdStatus = ENUM_PROSTATUS_SLOWUP;
			}
		}
		else if (Protect.CurrColdStatus == ENUM_PROSTATUS_SLOWUP)
		{
			if (u16_CurrentValueMul10 < ((CurrentProValueMul10 - 20) - 5))	//AcCurLimit_A[0] - 0.5A
			{
				Protect.CurrColdStatus = ENUM_PROSTATUS_NORMAL;
			}
			else if (u16_CurrentValueMul10 > (CurrentProValueMul10 - 10))	//AcCurLimit_A[1] = ICMAX_AC_COOLx - 1A
			{
				Protect.CurrColdStatus = ENUM_PROSTATUS_CONT;
			}
		}
		else if (Protect.CurrColdStatus == ENUM_PROSTATUS_CONT)
		{
			if (u16_CurrentValueMul10 < ((CurrentProValueMul10 - 10) - 5))	//AcCurLimit_A[1] - 0.5A
			{
				Protect.CurrColdStatus = ENUM_PROSTATUS_SLOWUP;
			}
			else if (u16_CurrentValueMul10 > CurrentProValueMul10)			//AcCurLimit_A[2] = ICMAX_AC_COOLx 
			{
				Protect.CurrColdStatus = ENUM_PROSTATUS_SLOWDOWN;
			}
		}
		else if (Protect.CurrColdStatus == ENUM_PROSTATUS_SLOWDOWN)
		{
			if (u16_CurrentValueMul10 < (CurrentProValueMul10 - 5))			//AcCurLimit_A[2] - 0.5A
			{
				Protect.CurrColdStatus = ENUM_PROSTATUS_CONT;
			}
			else if (u16_CurrentValueMul10 > (CurrentProValueMul10 + 10))	//AcCurLimit_A[3] = ICMAX_AC_COOLx + 1A
			{
				Protect.CurrColdStatus = ENUM_PROSTATUS_FASTDOWN;
			}
		}
		else if (Protect.CurrColdStatus == ENUM_PROSTATUS_FASTDOWN)
		{
			if (u16_CurrentValueMul10 < ((CurrentProValueMul10 + 10) - 5))	//AcCurLimit_A[3] - 0.5A
			{
				Protect.CurrColdStatus = ENUM_PROSTATUS_SLOWDOWN;
			}
		}
		
		//---
		
		if (Protect.f_CurrCold == 0)
		{
			if (u16_CurrentValueMul10 >= 160)	//超过异常阈值
			{
				Protect.f_CurrCold = 1;
			}
		}
		else	//压缩机停机恢复
		{
			Protect.f_CurrCold = 0;
			Comp.f_AppOn = OFF;
			Protect.CurrColdStatus = ENUM_PROSTATUS_NORMAL;
		}
	}
}
/****************************************************************************************************
Function Name       :void    Protect_CurrentHeat(void)
Description         :制热电流过大保护
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_CurrentHeat(void)
{
	U8     OutDoorCurrentMul8;		//依据通信接收电流*8的数值
	U16    u16_CurrentValueMul10;	//转换电流*10的数值
	U8     CurrentProValueMul10;    //电流保护阈值*10
	
	OutDoorCurrentMul8 = CommMotDrv.BaseRun.Rx.Byte9.OutDoorCurrentMul8;
	u16_CurrentValueMul10 = TempValueMul10(OutDoorCurrentMul8);
	u16_CurrentValueMul10 >>= 3;	//转换电流*10的数值
	
	if ((T4.f_Error == 1) || (SystemMode.f_Heat == 0))		//故障或非制冷回初始化
	{
		Protect.T4HeatZone = ENUM_T4HEATZONE_INIT;
	}
	
	if (SystemMode.f_Heat == 1)
	{
		//计算制热T4温度区间	
		if (Protect.T4HeatZone == ENUM_T4HEATZONE_INIT)
		{
			if (T4.s16_ValueMul10 <= 50)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT1;
			}
			else if (T4.s16_ValueMul10 <= 110)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT2;
			}
			else if (T4.s16_ValueMul10 <= 230)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT3;
			}	
			else
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT4;
			}
			
			CurrentProValueMul10 = 0xFF;	//初始阶段阈值最大化
		}
		else if (Protect.T4HeatZone == ENUM_T4HEATZONE_HOT1)
		{
			CurrentProValueMul10 = 98;		//ICMAX_AC_HOT1  9.8A
			
			if (T4.s16_ValueMul10 > 50)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT2;
			}
		}
		else if (Protect.T4HeatZone == ENUM_T4HEATZONE_HOT2)
		{
			CurrentProValueMul10 = 83;		//ICMAX_AC_HOT2  8.3A
			
			if (T4.s16_ValueMul10 < 40)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT1;
			}
			else if (T4.s16_ValueMul10 > 110)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT3;
			}
		}
		else if (Protect.T4HeatZone == ENUM_T4HEATZONE_HOT3)
		{
			CurrentProValueMul10 = 78;		//ICMAX_AC_HOT3  7.8A
			
			if (T4.s16_ValueMul10 < 100)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT2;
			}
			else if (T4.s16_ValueMul10 > 230)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT4;
			}
		}
		else if (Protect.T4HeatZone == ENUM_T4HEATZONE_HOT4)
		{
			CurrentProValueMul10 = 73;		//ICMAX_AC_HOT4  7.3A
			
			if (T4.s16_ValueMul10 < 220)
			{
				Protect.T4HeatZone = ENUM_T4HEATZONE_HOT3;
			}
		}

		//---
		
		if (Protect.CurrHeatStatus == ENUM_PROSTATUS_NORMAL)
		{
			if (u16_CurrentValueMul10 > (CurrentProValueMul10 - 20))		//AcCurLimit_A[0] = ICMAX_AC_HOTx - 2A
			{
				Protect.CurrHeatStatus = ENUM_PROSTATUS_SLOWUP;
			}
		}
		else if (Protect.CurrHeatStatus == ENUM_PROSTATUS_SLOWUP)
		{
			if (u16_CurrentValueMul10 < ((CurrentProValueMul10 - 20) - 5))	//AcCurLimit_A[0] - 0.5A
			{
				Protect.CurrHeatStatus = ENUM_PROSTATUS_NORMAL;
			}
			else if (u16_CurrentValueMul10 > (CurrentProValueMul10 - 10))	//AcCurLimit_A[1] = ICMAX_AC_HOTx - 1A
			{
				Protect.CurrHeatStatus = ENUM_PROSTATUS_CONT;
			}
		}
		else if (Protect.CurrHeatStatus == ENUM_PROSTATUS_CONT)
		{
			if (u16_CurrentValueMul10 < ((CurrentProValueMul10 - 10) - 5))	//AcCurLimit_A[1] - 0.5A
			{
				Protect.CurrHeatStatus = ENUM_PROSTATUS_SLOWUP;
			}
			else if (u16_CurrentValueMul10 > CurrentProValueMul10)			//AcCurLimit_A[2] = ICMAX_AC_HOTx 
			{
				Protect.CurrHeatStatus = ENUM_PROSTATUS_SLOWDOWN;
			}
		}
		else if (Protect.CurrHeatStatus == ENUM_PROSTATUS_SLOWDOWN)
		{
			if (u16_CurrentValueMul10 < (CurrentProValueMul10 - 5))			//AcCurLimit_A[2] - 0.5A
			{
				Protect.CurrHeatStatus = ENUM_PROSTATUS_CONT;
			}
			else if (u16_CurrentValueMul10 > (CurrentProValueMul10 + 10))	//AcCurLimit_A[3] = ICMAX_AC_HOTx + 1A
			{
				Protect.CurrHeatStatus = ENUM_PROSTATUS_FASTDOWN;
			}
		}
		else if (Protect.CurrHeatStatus == ENUM_PROSTATUS_FASTDOWN)
		{
			if (u16_CurrentValueMul10 < ((CurrentProValueMul10 + 10) - 5))	//AcCurLimit_A[3] - 0.5A
			{
				Protect.CurrHeatStatus = ENUM_PROSTATUS_SLOWDOWN;
			}
		}

		//---
		
		if (Protect.f_CurrHeat == 0)
		{
			if (u16_CurrentValueMul10 >= 170)	//超过异常阈值
			{
				Protect.f_CurrHeat = 1;
			}
		}
		else	//压缩机停机恢复
		{
			Protect.f_CurrHeat = 0;
			Comp.f_AppOn = OFF;
			Protect.CurrHeatStatus = ENUM_PROSTATUS_NORMAL;
		}		
	}
}
/****************************************************************************************************
Function Name       :void    Protect_CompCurr(void)
Description         :室外压缩机电流有效值过大保护
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_CompCurr(void)
{
	if (Protect.u16_CurErrCnt)
	{
		if (Protect.u16_CurErr_1HourCnt < 0xFFFF)
		{
			Protect.u16_CurErr_1HourCnt ++;
		}

		if ((Protect.u16_CurErr_1HourCnt >=36000) 
			&& (Protect.u16_CurErrCnt < 5)
			&& (Protect.f_CompCurr == 0))
		{
			Protect.u16_CurErr_1HourCnt = 0;
			Protect.u16_CurCount = 0;
		}
	}
	else 
	{
		Protect.u16_CurErr_1HourCnt = 0;
	}
	
	if ((Cur.s16_ValueMul10 >= Protect.s16_ErrCur) 		//13A
	&& (Comp.u32_RunContCount >=100))		//10秒
	{
		if (Protect.u16_CurCount < 0xFFFF)
		{
			Protect.u16_CurCount ++;
		}

		if (Protect.u16_CurCount >= 500)		//5秒
		{
			if (Protect.f_CompCurr == 0)
			{
				Protect.u16_CurErrCnt ++;
			}
			Protect.f_CompCurr = 1;
		}
	}
	else 
	{
		if (Protect.u16_CurErrCnt < 5)
		{
			Protect.f_CompCurr = 0;
			Protect.u16_CurCount = 0;
		}
	}
}

//{
//	U8     OutDoorCurrentMul8;		//依据通信接收电流*8的数值
//	U16    u16_CurrentValueMul10;	//转换电流*10的数值
//	U8     CurrentProValueMul10;    //电流保护阈值*10
//	
//	OutDoorCurrentMul8 = 0;//CommMotDrv.BaseRun.Rx.Byte9.OutDoorCurrentMul8;
//	u16_CurrentValueMul10 = TempValueMul10(OutDoorCurrentMul8);
//	u16_CurrentValueMul10 >>= 3;	//转换电流*10的数值
//	
//	//---
//	
//	if (Protect.CompCurrStatus == ENUM_PROSTATUS_NORMAL)
//	{
//		if (u16_CurrentValueMul10 > 80)		//CompCurLimit[0]	8A
//		{
//			Protect.CompCurrStatus = ENUM_PROSTATUS_SLOWUP;
//		}
//	}
//	else if (Protect.CompCurrStatus == ENUM_PROSTATUS_SLOWUP)
//	{
//		if (u16_CurrentValueMul10 < (80-5))		//CompCurLimit[0] - delta
//		{
//			Protect.CompCurrStatus = ENUM_PROSTATUS_NORMAL;
//		}	
//		else if (u16_CurrentValueMul10 > 85)		//CompCurLimit[1]	8.5A
//		{
//			Protect.CompCurrStatus = ENUM_PROSTATUS_CONT;
//		}		
//	}	
//	else if (Protect.CompCurrStatus == ENUM_PROSTATUS_CONT)
//	{
//		if (u16_CurrentValueMul10 < (85-5))		//CompCurLimit[1] - delta
//		{
//			Protect.CompCurrStatus = ENUM_PROSTATUS_SLOWUP;
//		}
//		else if (u16_CurrentValueMul10 > 90)	//CompCurLimit[2]	9A
//		{
//			Protect.CompCurrStatus = ENUM_PROSTATUS_SLOWDOWN;
//		}
//	}	
//	else if (Protect.CompCurrStatus == ENUM_PROSTATUS_SLOWDOWN)
//	{
//		if (u16_CurrentValueMul10 < (90-5))		//CompCurLimit[2] - delta
//		{
//			Protect.CompCurrStatus = ENUM_PROSTATUS_SLOWUP;
//		}
//		else if (u16_CurrentValueMul10 > 100)	//CompCurLimit[3]	10A
//		{
//			Protect.CompCurrStatus = ENUM_PROSTATUS_FASTDOWN;
//		}	
//	}		
//	else if (Protect.CompCurrStatus == ENUM_PROSTATUS_FASTDOWN)
//	{
//		if (u16_CurrentValueMul10 < (100-5))		//CompCurLimit[3] - delta
//		{
//			Protect.CompCurrStatus = ENUM_PROSTATUS_SLOWUP;
//		}		
//	}
//	
//	//---
//	
//	if (Protect.f_CompCurr == 0)
//	{
//		if (CurrentProValueMul10 >= 110)		//CompCurLimit[4]	11A
//		{
//			Protect.f_CompCurr = 1;
//		}
//	}
//	else
//	{
//		Protect.f_CompCurr = 0;
//		Comp.f_AppOn = OFF;	
//		Protect.CompCurrStatus = ENUM_PROSTATUS_NORMAL;
//	}
//}


/****************************************************************************************************
Function Name       :void    Protect_InFan(void)
Description         :内风机失速ED保护
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_InFanErr(void) //内风机失速ED保护
{
	static U16 u16_ErrRunCount = 0;

	/*
		10分钟内出现5次及以上风机故障，则判断风机存在故障，此后风机不再尝试启动，外机按关机处理，
		在故障刚报或者有任何操作时显示面板闪烁3次故障代码Ed，遥控关机或断电可恢复。
	*/
	
	// (CommMotDrv.BaseRun.Rx.Byte11.OutDoorStatus1.f_FanIndoorErr)
	if(Fan.Indoor.f_Error)
	{
		if(++u16_ErrRunCount > 2000) //10ms*2000=20s 约20s重启一次内风机
		{
			u16_ErrRunCount = 0;
			if(Fan.Indoor.f_ErrorDeal == 0) 
			{
				if(Fan.Indoor.u8_ErrRunTimes < C_INFAN_ERRORRUN_TIMES) //
				{
					Fan.Indoor.u8_ErrRunTimes++; //带故障运行次数 lcx add 20240622
					Fan.Indoor.f_ErrorDeal = 1;
				}
			}			
		}
	}
	else
	{
		Fan.Indoor.f_ErrorDeal = 0;
		u16_ErrRunCount = 0;
	}


	if(System.Enum_Status == ENUM_STATUS_INIT || System.Enum_Status == ENUM_STATUS_OFF) //遥控关机或断电可恢复。
	{
		Fan.Indoor.f_ErrorDeal = 0;
		Fan.Indoor.u8_ErrRunTimes = 0;
		u16_ErrRunCount = 0;
	}

	if(Fan.Indoor.u8_ErrRunTimes)
	{
		if(++Fan.Indoor.u16_ErrRunCount > 60000) //每10分钟自减一次
		{
			Fan.Indoor.u16_ErrRunCount = 0;
			if(Fan.Indoor.u8_ErrRunTimes) Fan.Indoor.u8_ErrRunTimes--;
		}
	}
	else
	{
		Fan.Indoor.u16_ErrRunCount = 0;
	}
}
/****************************************************************************************************
Function Name       :void	Protect_LowPressErr(void)
Description         :低压保护
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_LowPressErr(void)
{
	if (Protect.u16_LpErrCnt)
	{
		if (Protect.u32_LpErr_1HourCnt < 0xFFFFFFFF)
		{
			Protect.u32_LpErr_1HourCnt ++;
		}

		// 30分钟内发生三次此故障，则非掉电不可恢复（前两次可自动恢复）
		// 30分钟（180000*10ms=1800s=30min）后清除错误计数
		if ((Protect.u32_LpErr_1HourCnt >=180000) 
			&& (Protect.u16_LpErrCnt < 3)
			&& (Protect.f_LowPress == 0))
		{
			Protect.u32_LpErr_1HourCnt = 0;
			Protect.u16_LpCount = 0;
			Protect.u16_LpErrCnt = 0;		// 30分钟后清除错误计数，允许重新计数
		}
	}
	else 
	{
		Protect.u32_LpErr_1HourCnt = 0;
	}
	
	if (LowPress == 1)
	{
		// 待机时检测低压开关，如断开，则进入低压保护，系统停机保护
		// 运行时：压缩机开启5min（参数P23）后检测低压保护开关，连续10s检测到此开关断开，则对应系统停机保护
		// 待机时：直接检测，使用5秒延时（更快响应）
		if ((System.Enum_Status == ENUM_STATUS_OFF))	// 待机时检测低压开关
		{
			if (Protect.u16_LpCount < 0xFFFF)
			{
				Protect.u16_LpCount ++;
			}

			if (Protect.u16_LpCount >= 500)		//5秒（待机时使用5秒延时）
			{
				if (Protect.f_LowPress == 0)
				{
					Protect.u16_LpErrCnt ++;
				}
				Protect.f_LowPress = 1;
			}
		}
		else if (((Comp.f_DrvOn) && (Comp.u32_RunContCount >= ((U32)FtyPara.u16P23 * 6000)))
		|| Defrost.f_Enable)	// 运行时检测：压缩机开启P23分钟后检测低压保护开关
		{
			if (Protect.u16_LpCount < 0xFFFF)
			{
				Protect.u16_LpCount ++;
			}

			if (Protect.u16_LpCount >= 1000)		//10秒（连续10s检测到此开关断开）
			{
				if (Protect.f_LowPress == 0)
				{
					Protect.u16_LpErrCnt ++;
				}
				Protect.f_LowPress = 1;
			}
		}
		else 
		{
			Protect.u16_LpCount = 0;
		}
	}
	else 
	{
		if (Protect.u16_LpErrCnt < 3)
		{
			Protect.f_LowPress = 0;
			Protect.u16_LpCount = 0;
		}
	}
}

/****************************************************************************************************
Function Name       :void	Protect_HighPressErr(void)
Description         :高压保护
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_HighPressErr(void)
{
	if (Protect.u16_HpErrCnt)
	{
		if (Protect.u32_HpErr_1HourCnt < 0xFFFFFFFF)
		{
			Protect.u32_HpErr_1HourCnt ++;
		}

		// 30分钟内发生三次此故障，则非掉电不可恢复（前两次可自动恢复）
		// 30分钟（180000*10ms=1800s=30min）后清除错误计数
		if ((Protect.u32_HpErr_1HourCnt >=180000) 
			&& (Protect.u16_HpErrCnt < 3)
			&& (Protect.f_HighPress == 0))
		{
			Protect.u32_HpErr_1HourCnt = 0;
			Protect.u16_HpCount = 0;
			Protect.u16_HpErrCnt = 0;		// 30分钟后清除错误计数，允许重新计数
		}
	}
	else 
	{
		Protect.u32_HpErr_1HourCnt = 0;
	}
	
	if (HighPress == 1)
	{
		// 待机时检测高压开关，如断开，则进入高压保护，系统停机保护
		// 运行时：正常制冷状态下，压缩机起动5s检测到高压开关断开，则进入高压保护，停机保护
		if ((System.Enum_Status == ENUM_STATUS_OFF))	// 待机时检测高压开关
		{
			if (Protect.u16_HpCount < 0xFFFF)
			{
				Protect.u16_HpCount ++;
			}

			if (Protect.u16_HpCount >= 500)		//5秒（待机时使用5秒延时）
			{
				if (Protect.f_HighPress == 0)
				{
					Protect.u16_HpErrCnt ++;
				}
				Protect.f_HighPress = 1;
			}
		}
		else if (Comp.f_DrvOn)	// 运行时检测
		{
			// 压缩机起动5秒后开始检测高压开关
			if (Comp.u32_RunContCount >= 500)	// 5秒（500*10ms=5s）
			{
				// 压缩机已运行5秒，检测到高压开关断开，立即进入高压保护
				if (Protect.f_HighPress == 0)
				{
					Protect.u16_HpErrCnt ++;
				}
				Protect.f_HighPress = 1;
			}
			else
			{
				// 压缩机运行未满5秒，屏蔽高压保护
				Protect.f_HighPress = 0;
			}
		}
		else 
		{
			// 压缩机未运行且不在待机状态，清除高压保护
			if (Protect.u16_HpErrCnt < 3)
			{
				Protect.f_HighPress = 0;
				Protect.u16_HpCount = 0;
			}
		}
	}
	else 
	{
		if (Protect.u16_HpErrCnt < 3)
		{
			Protect.f_HighPress = 0;
			Protect.u16_HpCount = 0;
		}
	}
}

/****************************************************************************************************
Function Name       :void	Protect_MidWaterLevelErr(void)
Description         :中水位开关故障检测
Input               :
Return              :
Author              :
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_MidWaterLevelErr(void)
{
	// 判断到高水位接通且中水位断开时且持续时间30秒（参数P28），则判断为中水位开关故障
	// 高水位接通：HighWaterLevel == 0（接通为0）
	// 中水位断开：MidWaterLevel == 1（断开为1）
	if ((HighWaterLevel == 0) && (MidWaterLevel == 1))
	{
		if (Protect.u16_MidWaterLevelErrCnt < 0xFFFF)
		{
			Protect.u16_MidWaterLevelErrCnt ++;
		}

		// 持续时间达到P28*100（P28单位为秒，转换为10ms周期）
		if (Protect.u16_MidWaterLevelErrCnt >= (FtyPara.u16P28 * 100))
		{
			Protect.f_MidWaterLevelErr = 1;		// 中水位开关故障
		}
	}
	else 
	{
		// 故障条件不满足，清除故障和计时
		Protect.f_MidWaterLevelErr = 0;
		Protect.u16_MidWaterLevelErrCnt = 0;
	}
}

/****************************************************************************************************
Function Name       :void	Protect_HighWaterLevelErr(void)
Description         :高水位开关故障检测
Input               :
Return              :
Author              :
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_HighWaterLevelErr(void)
{
	// 在定时补水期间，当补水阀连续运行超过60分钟（参数P29），则判断为高水位开关故障
	// 定时补水期间：WFV.f_Timing == 1
	// 补水阀运行：WFV.f_DrvOn == 1
	if ((WFV.f_Timing == 1) && (WFV.f_DrvOn == 1))
	{
		if (WFV.u32_TimingRunCnt < 0xFFFFFFFF)
		{
			WFV.u32_TimingRunCnt ++;
		}

		// 持续时间达到P29*6000（P29单位为分钟，转换为10ms周期：P29*60*100 = P29*6000）
		// 使用U32类型避免溢出：当P29=60时，60*6000=360000，超出U16范围
		if (WFV.u32_TimingRunCnt >= ((U32)FtyPara.u16P29 * 6000))
		{
			Protect.f_HighWaterLevelErr = 1;		// 高水位开关故障
			// 故障时禁用定时补水，启用自动补水
			WFV.f_Timing = 0;
			WFV.f_Auto = 1;
			WFV.u16_TimingCnt = 0;
			WFV.u32_TimingRunCnt = 0;
		}
	}
	else 
	{
		// 不在定时补水或补水阀未运行，清除计时
		WFV.u32_TimingRunCnt = 0;
	}
	
	// 故障恢复：当故障被清除时（手动或自动清除故障代码），恢复定时补水功能
	// 注意：故障清除由外部控制（线控器手动清除或自动清除），这里只处理恢复逻辑
	if ((Protect.f_HighWaterLevelErr == 0) && (WFV.f_Auto == 1) && (WFV.f_Timing == 0))
	{
		// 故障已清除，且当前是自动补水模式（由故障切换过来的），可以恢复定时补水
		// 但这里不自动恢复，需要外部根据用户设置来决定是否恢复定时补水
		// 如果用户重新开启定时补水，则WFV.f_Timing会被外部设置为1
	}
}

/****************************************************************************************************
Function Name       :void	Protect_LowWaterLevelErr(void)
Description         :低水位开关故障检测
Input               :
Return              :
Author              :
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_LowWaterLevelErr(void)
{
	// 判断到高水位接通且低水位断开、或者中水位接通且低水位断开时且持续时间30秒（参数P28），则判断为低水位开关故障
	// 高水位接通：HighWaterLevel == 0（接通为0）
	// 中水位接通：MidWaterLevel == 0（接通为0）
	// 低水位断开：LowWaterLevel == 1（断开为1）
	if (((HighWaterLevel == 0) && (LowWaterLevel == 1)) || 
		((MidWaterLevel == 0) && (LowWaterLevel == 1)))
	{
		if (Protect.u16_LowWaterLevelErrCnt < 0xFFFF)
		{
			Protect.u16_LowWaterLevelErrCnt ++;
		}

		// 持续时间达到P28*100（P28单位为秒，转换为10ms周期）
		if (Protect.u16_LowWaterLevelErrCnt >= (FtyPara.u16P28 * 100))
		{
			Protect.f_LowWaterLevelErr = 1;		// 低水位开关故障
		}
	}
	else 
	{
		// 故障条件不满足，清除故障和计时
		Protect.f_LowWaterLevelErr = 0;
		Protect.u16_LowWaterLevelErrCnt = 0;
	}
}
//{
////	WaterBox.f_SW1_Full = !F_switch_sw1_old;	//0:代表断开 1:代表短接	
////	WaterBox.f_SW2_Full = !F_switch_sw2_old;	//0:代表断开 1:代表短接
//
//	if (WaterBox.f_SW1_Full == 0)
//	{
//		if (F_switch_sw1_old == 0)
//		{
//			if (++WaterBox.u16_SW1FullCount >= 500)	//持续5s
//			{
//				WaterBox.u16_SW1FullCount = 0;
//				WaterBox.f_SW1_Full = 1;
//			}
//		}
//		else
//		{
//			WaterBox.u16_SW1FullCount = 0;
//		}
//		
//		WaterBox.u16_SW1NormalCount = 0;
//	}
//	else
//	{
//		if (F_switch_sw1_old == 1)
//		{
//			if (++WaterBox.u16_SW1NormalCount >= 500)	//持续5s
//			{
//				WaterBox.u16_SW1NormalCount = 0;
//				WaterBox.f_SW1_Full = 0;
//			}
//		}
//		else
//		{
//			WaterBox.u16_SW1NormalCount = 0;
//		}
//		
//		WaterBox.u16_SW1FullCount = 0;
//	}
//
//	//-----
//	
//	if (WaterBox.f_SW2_Full == 0)
//	{
//		if (F_switch_sw2_old == 0)
//		{
//			if (++WaterBox.u16_SW2FullCount >= 500)	//持续5s
//			{
//				WaterBox.u16_SW2FullCount = 0;
//				//WaterBox.f_SW2_Full = 1;
//			}
//		}
//		else
//		{
//			WaterBox.u16_SW2FullCount = 0;
//		}
//		
//		WaterBox.u16_SW2NormalCount = 0;
//	}
//	else
//	{
//		if (F_switch_sw2_old == 1)
//		{
//			if (++WaterBox.u16_SW2NormalCount >= 500)	//持续5s
//			{
//				WaterBox.u16_SW2NormalCount = 0;
//				WaterBox.f_SW2_Full = 0;
//			}
//		}
//		else
//		{
//			WaterBox.u16_SW2NormalCount = 0;
//		}
//		
//		WaterBox.u16_SW2FullCount = 0;
//	}	
//
//	//-----
//	/*
//	//N款水位保护逻辑 lcx 2024029
//	if (WaterBox.f_SW1_Full && WaterBox.f_SW2_Full)
//	{
//		WaterBox.f_Full = 1;
//		WaterBox.f_WatLow = 0;
//	}
//	else if (WaterBox.f_SW1_Full || WaterBox.f_SW2_Full)
//	{
//		WaterBox.f_Full = 0;
//		WaterBox.f_WatLow = 1;	
//	}
//	else
//	{
//		WaterBox.f_Full = 0;
//		WaterBox.f_WatLow = 0;	
//	}
//	*/
//
//	//M款水位保护逻辑 lcx 2024029
//	if (WaterBox.f_SW1_Full)
//	{
//		WaterBox.f_Full = 1;
//		WaterBox.f_WatLow = 0;
//	}
//	else
//	{
//		WaterBox.f_Full = 0;
//		WaterBox.f_WatLow = 0;	
//	}
//
//	
//}

/****************************************************************************************************
Function Name       :void	InitPhaseSequence(void)
Description         :相序检测入口端口初始化
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    InitPhaseSequence(void)
{
	//A相
	#if (PhaseASigValid == 0)		    //低电平有效
    P_PhaseA_Hi();  
    P_PhaseA_Input();	
	P_PhaseA_Enpull();
    #else							    //高电平有效
    P_PhaseA_Low();	
    P_PhaseA_Input();
    P_PhaseA_Dispull();
    #endif


	//B相
	#if (PhaseBSigValid == 0)		    //低电平有效
    P_PhaseB_Hi();  
    P_PhaseB_Input();	
	P_PhaseB_Enpull();
    #else							    //高电平有效
    P_PhaseB_Low();	
    P_PhaseB_Input();
    P_PhaseB_Dispull();
    #endif

	//C相
	#if (PhaseCSigValid == 0)		    //低电平有效
    P_PhaseC_Hi();  
    P_PhaseC_Input();	
	P_PhaseC_Enpull();
    #else							    //高电平有效
    P_PhaseC_Low();	
    P_PhaseC_Input();
    P_PhaseC_Dispull();
    #endif
}

/****************************************************************************************************
Function Name       :void	Protect_HighPressErr(void)
Description         :相位检测
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    PhaseSequenceCheck(void)
{
//	if (Comp.f_DrvOn)
	if (1)
	{
 		if ((Pin_phaseA == 1) && (Protect.f_PhaseA_bak == 0))
		{
			if ((Protect.u16_PhaseABCnt > Protect.u16_PhaseBCCnt)
			&&  (Protect.u16_PhaseABCnt > Protect.u16_PhaseCACnt)
			&&  (Protect.u16_PhaseBCCnt > Protect.u16_PhaseCACnt))
			{
				Protect.u16_PhaseSeqErrCnt = 0;
			}
			else 
			{
				Protect.u16_PhaseSeqErrCnt ++;
			}
			
			Protect.u16_PhaseABCnt = 0;
		}

		if ((Pin_phaseB == 1) && (Protect.f_PhaseB_bak == 0))
		{
			if ((Protect.u16_PhaseBCCnt > Protect.u16_PhaseCACnt)
			&&  (Protect.u16_PhaseBCCnt > Protect.u16_PhaseABCnt)
			&&  (Protect.u16_PhaseCACnt > Protect.u16_PhaseABCnt))
			{
				Protect.u16_PhaseSeqErrCnt = 0;
			}
			else 
			{
				Protect.u16_PhaseSeqErrCnt ++;
			}
			Protect.u16_PhaseBCCnt = 0;
		}

		if ((Pin_phaseC == 1) && (Protect.f_PhaseC_bak == 0))
		{
			if ((Protect.u16_PhaseCACnt > Protect.u16_PhaseABCnt)
			&&  (Protect.u16_PhaseCACnt > Protect.u16_PhaseBCCnt)
			&&  (Protect.u16_PhaseABCnt > Protect.u16_PhaseBCCnt))
			{
				Protect.u16_PhaseSeqErrCnt = 0;
			}
			else 
			{
				Protect.u16_PhaseSeqErrCnt ++;
			}
			Protect.u16_PhaseCACnt = 0;
		}
	
		if (Protect.u16_PhaseABCnt < 0xFFFF)
		{
			Protect.u16_PhaseABCnt++;
		}

		if (Protect.u16_PhaseBCCnt < 0xFFFF)
		{
			Protect.u16_PhaseBCCnt++;
		}
	
		if (Protect.u16_PhaseCACnt < 0xFFFF)
		{
			Protect.u16_PhaseCACnt++;
		}
	}
	else 
	{
		Protect.u16_PhaseABCnt = 0;
		Protect.u16_PhaseBCCnt = 0;
		Protect.u16_PhaseCACnt = 0;
		Protect.u16_PhaseSeqErrCnt = 0;
	}
	Protect.f_PhaseA_bak = Pin_phaseA;
	Protect.f_PhaseB_bak = Pin_phaseB;
	Protect.f_PhaseC_bak = Pin_phaseC;
}

/****************************************************************************************************
Function Name       :void	Protect_HighPressErr(void)
Description         :错相保护
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_PhaseSequenceErr(void)
{
	if (Protect.PhaseSeqStatus == ENUM_PROSTATUS_NORMAL)
	{
		if (Protect.u16_PhaseSeqErrCnt  >= 10)
		{
			Protect.PhaseSeqStatus = ENUM_PROSTATUS_PROTECT;
		}
	}
}
/****************************************************************************************************
Function Name       :void	Protect_HighPressErr(void)
Description         :水流开关故障
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Protect_WaterFlowErr(void)
{
	// 系统请求开机，先开启循环水泵；循环水泵启动运行20秒（参数P6）后，若连续15秒（参数P7）检测到水流开关信号断开，则停止所有负载并报警、故障不可恢复
	// 故障不可恢复，需按开关键关机或者断电后重新上电才能清除水流开关故障
	if ((System.Enum_Status == ENUM_STATUS_INIT) || (System.Enum_Status == ENUM_STATUS_OFF))
	{
		// 系统初始化或关机时，清除水流开关故障
		Protect.f_WaterFlow = 0;
		Protect.u16_WaterFlowCnt = 0;
	}
	else if (CirculationPump.f_DrvOn)		//循环泵运行
	{
		if (CirculationPump.u16_RunCnt >= (FtyPara.u16P6 * 100))	//循环水泵启动运行P6秒后（P6单位为秒，转换为10ms周期：P6*100）
		{
			if (WaterFlow == 1)		//水流开关信号断开
			{
				if (Protect.u16_WaterFlowCnt < 0xFFFF)
				{
					Protect.u16_WaterFlowCnt++;
				}
				// 连续15秒（参数P7）检测到水流开关信号断开
				if (Protect.u16_WaterFlowCnt >= (FtyPara.u16P7 * 100))		//P7单位为秒，转换为10ms周期：P7*100
				{
					Protect.f_WaterFlow = 1;		//水流开关故障，故障不可恢复
				}
			}
			else 
			{
				// 水流开关信号接通，清除计数
				Protect.u16_WaterFlowCnt = 0;
			}
		}
		else 
		{
			// 循环泵运行未满P6秒，清除计数
			Protect.u16_WaterFlowCnt = 0;
		}
	}
	else 
	{
		// 循环泵未运行，不清除故障（保持故障状态，除非系统初始化或关机）
		// 不清除Protect.f_WaterFlow，保持故障状态
	}
}

/****************************************************************************************************
Function Name       :void    Func_Protect(void)
Description         :保护功能处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Protect(void)
{
	Protect_Tp();			//Tp排气温度保护
//	Protect_T2Cold();		//T2制冷室内盘管防冻结
//	Protect_T3Cold();		//T3制冷室外盘管防过热
//	Protect_CurrentCold();	//制冷电流过大保护
//	Protect_CurrentHeat();	//制热电流过大保护
	Protect_CompCurr();		//室外压缩机电流有效值过大保护
//	Protect_InFanErr(); 	//内风机失速ED保护 lcx add 20240622
	Protect_HighPressErr();	//高压保护		
	Protect_LowPressErr();	//低压保护
	Protect_T2Heat();       //T2制热室内盘管过热保护
	Protect_PhaseSequenceErr();	//错相保护
	Protect_WaterFlowErr();		//水流开关保护
	Protect_MidWaterLevelErr();	//中水位开关故障检测
	Protect_HighWaterLevelErr();	//高水位开关故障检测
	Protect_LowWaterLevelErr();	//低水位开关故障检测
	
	// 当出现中水位或低水位故障时，整机停止（参考高低压保护处理）
	// 仅出现高水位开关故障时，机组正常运行，定时补水功能失效且执行自动补水功能
	if (Protect.f_Tp || Protect.f_T2Cold || Protect.f_T3Cold 
	|| Protect.f_CurrCold || Protect.f_CurrHeat || Protect.f_CompCurr
	|| Protect.f_HighPress || Protect.f_LowPress || Protect.PhaseSeqStatus
	|| Protect.f_WaterFlow || Protect.f_MidWaterLevelErr || Protect.f_LowWaterLevelErr)
	{
		Protect.f_Enable = 1;
	}
	else
	{
		Protect.f_Enable = 0;
	}
	
	if (CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_NULL)
	{
		SystemMode.f_Error = 0;
	}
	else
	{
		SystemMode.f_Error = 1;
	}
}
