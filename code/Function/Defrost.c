/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Defrost.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/20
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"


STRUCT_DEFROST    Defrost;

/****************************************************************************************************
Function Name       :void    Defrost_Init(void)
Description         :化霜功能初始化
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Defrost_Init(void)
{
	memset(&Defrost, 0, sizeof(STRUCT_DEFROST));	//结构体成员清0
}
/****************************************************************************************************
Function Name       :void    Defrost_Con(void)
Description         :化霜功能处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Defrost_Con(void)
{
	S16    s16_TempValue;
	S16    s16_TempValue1;
	
	if (System.Enum_Status == ENUM_STATUS_ON)
	{	
		if (Defrost.f_Enable == 0)		//未进入化霜
		{
			if (Defrost.f_T30Found == 0)	//未找到T30
			{
				if (SystemMode.f_Heat) 
				{
					if (Defrost.u16_FindT30_Count < 3000)	//5分钟之前
					{
						Defrost.s16_T30Mul10 = T3.s16_ValueMul10;
					}
					else if (Defrost.u16_FindT30_Count < 4200)	//5分钟到7分钟之间
					{
						if (Defrost.s16_T30Mul10 > T3.s16_ValueMul10)
						{
							Defrost.s16_T30Mul10 = T3.s16_ValueMul10;	//更新最小值
						}
					}
					else
					{
						Defrost.f_T30Found = 1; 	//找到T30
					}					
				}

			}
			else	//已找到T30
			{
				//进入条件一
				if (Defrost.u16_HeatRun_Count >= 9000 && Comp.f_AppOn && Comp.f_DrvOn) 		//15min
				{
					s16_TempValue = (S8)EEP.u8_rdBuf[117];					//EE.PARA. (U8)C_REMEMBER_PARA09_00;		//-10(-5℃)		   	//TDFI1	
					s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
					
					if (T3.s16_ValueMul10 < s16_TempValue)	
					{
						s16_TempValue1 = (S8)EEP.u8_rdBuf[118];				//EE.PARA. (U8)C_REMEMBER_PARA09_01;	   //4(2℃)		   		//DELTA_TDF1
						s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1);
						
						if ((Defrost.s16_T30Mul10 - T3.s16_ValueMul10) >= s16_TempValue1)
						{
							if(Comp.f_AppOn && Comp.f_DrvOn) Defrost.f_Enable = 1;		//进入化霜   //增加压缩机开时才判断 lcx add
						}
					}
				}
				
				//进入条件二
				if (Defrost.u16_HeatRun_Count >= 12000)		//20min
				{
					s16_TempValue = (S8)EEP.u8_rdBuf[119];					//EE.PARA. (U8)C_REMEMBER_PARA09_02;		//-6(-3℃)		   //TDFI2	
					s16_TempValue = (TempValueMul10(s16_TempValue)>>1);			
					
					if (T3.s16_ValueMul10 < s16_TempValue)
					{
						s16_TempValue1 = (S8)EEP.u8_rdBuf[120];				//EE.PARA. (U8)C_REMEMBER_PARA09_03;	   //5(2.5℃)		  //DELTA_TDF2	
						s16_TempValue1 = (TempValueMul10(s16_TempValue1)>>1);						
						
						if ((Defrost.s16_T30Mul10 - T3.s16_ValueMul10) >= s16_TempValue1)
						{
							if(Comp.f_AppOn && Comp.f_DrvOn) Defrost.f_Enable = 1;		//进入化霜   //增加压缩机开时才判断 lcx add
						}						
					}
				}
				
				//进入条件三//增加压缩机开时才判断 lcx add
				if (T4.s16_ValueMul10 >= -150) //T4.s16_ValueMul10 = 0X00000058=88
				{
					if (Defrost.u16_HeatRun_Count >= 6000)		//10min
					{	
						s16_TempValue = (S8)EEP.u8_rdBuf[121];				//EE.PARA. (U8)C_REMEMBER_PARA09_04;	  //-30(-15℃)		//TDFI3	
						s16_TempValue = (TempValueMul10(s16_TempValue)>>1);

						if (T3.s16_ValueMul10 < s16_TempValue)		
						{
							if (Defrost.u16_DefCase3_Count >= 1800)	//3min
							{
								if(Comp.f_AppOn && Comp.f_DrvOn) //增加压缩机开时才判断 lcx add
								{
									Defrost.u16_DefCase3_Count = 0;
									Defrost.f_Enable = 1;	//进入化霜
								}
							}
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
				
				//进入条件四
				if (Defrost.u16_HeatRun_Count >= 36000)		//60min
				{
					s16_TempValue = (S8)EEP.u8_rdBuf[122];					//EE.PARA. (U8)C_REMEMBER_PARA09_05;		//-2(-1℃)		   	//TDFI4	
					s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
					
					if (T3.s16_ValueMul10 < s16_TempValue)			
					{
						if(Comp.f_AppOn && Comp.f_DrvOn) //增加压缩机开时才判断 lcx add
						{
							Defrost.f_Enable = 1;	//进入化霜
						}
					}
				}
			}
			
			Defrost.u16_Defrosting_Count = 0;
			Defrost.u8_Step = 0;
			Defrost.u16_Step_Delay = 500;	//化霜首个步骤经历50s
		}
		else							//进入化霜
		{		
			//退出判断
			
			if (T4.s16_ValueMul10 >= -180)		//外环温度大于等于-18℃
			{		
				//退出条件一
				s16_TempValue = (S8)EEP.u8_rdBuf[123];						//EE.PARA. (U8)C_REMEMBER_PARA09_06;		//30(15℃)		   //TDFE1	
				s16_TempValue = (TempValueMul10(s16_TempValue)>>1);			
				
				if (T3.s16_ValueMul10 > s16_TempValue)	//室外热交换温度高于15℃	
				{
					Defrost.f_Quit = 1;		//满足退出
				}
				
				//退出条件二
				s16_TempValue = (S8)EEP.u8_rdBuf[124];					    //EE.PARA. (U8)C_REMEMBER_PARA09_07;		//16(8℃)		  //TDFE2	
				s16_TempValue = (TempValueMul10(s16_TempValue)>>1);				
				
				if (T3.s16_ValueMul10 > s16_TempValue)		
				{
					if (Defrost.u16_DefQCase2_Count >= 800)	//持续80s
					{
						Defrost.f_Quit = 1;		//满足退出
					}
				}
				else
				{
					Defrost.u16_DefQCase2_Count = 0;
				}
			}

					
			//退出条件三
			if (Defrost.u16_Defrosting_Count >= 6000)		//化霜过程最长10min
			{
				Defrost.f_Quit = 1;		//满足退出
			}


			if (Protect.f_HighPress)		
			{
				if (Defrost.f_Quit == 0)
				{
					if (Protect.u16_HpErrCnt)
					{
						Protect.u16_HpErrCnt --;
					}
				}
				Defrost.f_Quit = 1;		//满足退出
			}
			
			//----------------------------------------
			
			//化霜期间负载工作时序
			if (Defrost.u8_Step == 0)
			{
				Comp.f_AppOn = OFF;
				Comp.u16_RunMinDelay = 0;
				FourWay.f_AppOn = ON;
				//电子膨胀阀正常
				Fan.Outdoor.f_AppOn = ON;
				
				if (Defrost.u16_Step_Delay == 0)
				{
					Comp.u16_RestartDelay = 100;	//压缩机同理10s后启动
					Defrost.u16_Step_Delay = 100;    //第二阶段经历10s
					Defrost.u8_Step += 1;
				}
			}
			else if (Defrost.u8_Step == 1)
			{
				Comp.f_AppOn = OFF;
				Comp.u16_RunMinDelay = 0;
				FourWay.f_AppOn = OFF;	
				//电子膨胀阀开度500
				Fan.Outdoor.f_AppOn = OFF;
				
				if (Defrost.u16_Step_Delay == 0)
				{
					Comp.u16_RestartDelay = 0;
					Defrost.u16_Defrosting_Count = 0;
					Defrost.u16_Step_Delay = 6000;    //第三阶段经历10分钟(最长)
					Defrost.u8_Step += 1;
				}			
			}
			else if (Defrost.u8_Step == 2)
			{
//				Comp.f_AppOn = ON;
				
				FourWay.f_AppOn = OFF;	
				//电子膨胀阀开度500	
				Fan.Outdoor.f_AppOn = OFF;	

				if ((Defrost.u16_Step_Delay == 0) || Defrost.f_Quit) //可以调节T3退出化霜
				{
					Defrost.u16_Step_Delay = 1200;    //第四阶段经历2min
					Defrost.u8_Step += 1;				
				}	
			}
			else if (Defrost.u8_Step == 3)
			{
				Comp.f_AppOn = OFF;
				Comp.u16_RunMinDelay = 0;
				FourWay.f_AppOn = OFF;	
				//电子膨胀阀开度500	
				Fan.Outdoor.f_AppOn = OFF; //lcx 20240606 ON->OFF; //调节T3退出化霜后，外风机不能马上开，要等3分钟。
				
				
				if (Defrost.u16_Step_Delay == 0)
				{
					Defrost.u16_Step_Delay = 600;    //第五阶段经历60s
					Defrost.u8_Step += 1;				
				}			
			}
			else if (Defrost.u8_Step == 4)
			{
				Comp.f_AppOn = OFF;
				Comp.u16_RunMinDelay = 0;
				FourWay.f_AppOn = ON;
				//电子膨胀阀正常
				Fan.Outdoor.f_AppOn = OFF; //lcx 20240716 ON->OFF; //调节T3退出化霜后，外风机不能马上开，要等3分钟。
				
				if (Defrost.u16_Step_Delay == 0)
				{
					Defrost.u8_Step += 1;
				}
			}
			else
			{
				Comp.u16_RestartDelay = 0;	//15s延时完毕后压缩机延时清0(压缩机需立即开启)
				Defrost_Init();		//化霜相关变量初始化--退出化霜
			}		
		}
	}
}






