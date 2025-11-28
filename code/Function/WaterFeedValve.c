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
		if (WFV.u16_TimingCnt < 0xFFFF)
		{
			WFV.u16_TimingCnt ++;
		}
		
		if ((HighWaterLevel) && (WFV.u16_TimingCnt >= (FtyPara.u16P9 * 6000)))
		{
			WFV.f_AppOn = ON;
		}
		else 
		{
			if (WFV.f_AppOn == ON)
			{
				WFV.u16_TimingCnt = 0;
			}
			WFV.f_AppOn = OFF;
		}
	}
	else if (WFV.f_Auto)
	{
		if (WFV.u16_AutoCnt < 0xFFFF)
		{
			WFV.u16_AutoCnt ++;
		}
		if (LowWaterLevel == 1)
		{
			if (WFV.u16_AutoCnt >= (FtyPara.u16P10 * 6000))
			{
				WFV.f_AppOn = ON;
			}
		}
		else 
		{
			if (LowWaterLevel)
			{
				WFV.u16_AutoCnt = 0;
			}
			

			if ((WFV.u16_AutoCnt >= (FtyPara.u16P11 * 6000))
			|| (HighWaterLevel == 0))
			{
				WFV.f_AppOn = OFF;
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
