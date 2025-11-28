/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: DCFan.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/12/14
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_WFV    WFV;         //补水泵

/****************************************************************************************************
Function Name       :void    Init_WFV(void)
Description         :补水泵初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_WFV(void)
{
    P_WFV_Off();  
    P_WFV_Output();	
	P_WFV_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Func_WFV(void)
Description         :补水阀功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_WFV(void)
{
//	WFV.f_AppOn = Comp.f_DrvOn;
//	if ((LowWaterLevel == 0) &&	(System.Enum_Status == ENUM_STATUS_ON))
//	{
//		WFV.f_AppOn = 1; 
//	}
//	else 
//	{
//		WFV.f_AppOn = 0; 
//	}

	if (WFV.f_ManualOFF)
	{
		WFV.f_AppOn = OFF;
	}
	else if (WFV.f_ManualON)
	{
		if (HighWaterLevel)
		{
			WFV.f_AppOn = ON;
		}
		else 
		{
			WFV.f_AppOn = OFF;
			WFV.f_ManualON = 0;
		}
	}
	else if (WFV.f_Timing)
	{
		if (HighWaterLevel)			// 高水位断开，开始计时准备补水
		{
			if (WFV.u16_TimingCnt < (FtyPara.u16P9 * 6000))
			{
				WFV.u16_TimingCnt ++;
			}

			if (WFV.u16_TimingCnt >= (FtyPara.u16P9 * 6000))
			{
				WFV.f_AppOn = ON;	// 延时到达，启动补水阀
			}
			else
			{
				WFV.f_AppOn = OFF;	// 延时未到，保持关闭
			}
		}
		else						// 高水位接通，立即关闭并复位计时
		{
			WFV.u16_TimingCnt = 0;
			WFV.f_AppOn = OFF;
		}
	}
	else if (WFV.f_Auto)
	{
		U16 u16StartCnt = (U16)(FtyPara.u16P10 * 6000);
		U16 u16StopCnt  = (U16)(FtyPara.u16P11 * 6000);
		U8  u8LowOpen   = (LowWaterLevel ? 1 : 0);		// 1: 低水位断开
		U8  u8HighClose = (HighWaterLevel == 0);		// 0: 高水位接通

		if (u8LowOpen)
		{
			// 低水位断开，延时 P10 后才启动补水
			if (WFV.f_AppOn == OFF)
			{
				if (WFV.u16_AutoCnt < u16StartCnt)
				{
					WFV.u16_AutoCnt ++;
				}
				else
				{
					WFV.f_AppOn = ON;		// 延时到达，启动补水
					WFV.u16_AutoCnt = 0;	// 切换到补水状态后，计时用于后续关阀
				}
			}
			else
			{
				// 已在补水中，保持运行直到低水位接通
				WFV.u16_AutoCnt = 0;
			}
		}
		else	// 低水位已接通
		{
			if (WFV.f_AppOn == ON)
			{
				if (u8HighClose)
				{
					// 高水位先到，立即停止自动补水
					WFV.f_AppOn = OFF;
					WFV.u16_AutoCnt = 0;
				}
				else
				{
					// 低水位刚接通，延时 P11 后停止
					if (WFV.u16_AutoCnt < u16StopCnt)
					{
						WFV.u16_AutoCnt ++;
					}
					else
					{
						WFV.f_AppOn = OFF;
						WFV.u16_AutoCnt = 0;
					}
				}
			}
			else
			{
				// 未在补水，保持计时清零
				WFV.u16_AutoCnt = 0;
			}
		}
	}

	if (WFV.f_Timing == 0)		//保证刚进入定时补水时，高水位开关断开即开补水阀
	{
		WFV.u16_TimingCnt = FtyPara.u16P9 * 6000;
	}

	if (WFV.f_Auto == 0)
	{
		WFV.u16_AutoCnt = 0;
	}
	
	if (WFV.f_DrvOn == OFF)
	{
		if (WFV.f_AppOn == ON)
		{
			//散热风机开启刹那
			WFV.f_DrvOn = ON;
		}
	}
	else
	{
		if (WFV.f_AppOn == OFF)
		{
			//补水阀刹那
			if (WFV.u16_Delay == 0)
			{
				WFV.f_DrvOn = OFF;
			}
		}	
	}
	
	if ((WFV.f_DrvOn) || (WFV.f_ForceDrvOn))
	{
		P_WFV_On();
	}
	else
	{
		P_WFV_Off();
	}
}
