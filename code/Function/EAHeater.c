/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: EAHeater.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/18
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_EAHEATER    EAHeater;         //电辅热

/****************************************************************************************************
Function Name       :void    Init_EAHeater(void)
Description         :电辅热初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_EAHeater(void)
{
    P_EAHeater_Off();  
    P_EAHeater_Output();	
	P_EAHeater_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Func_EAHeater(void)
Description         :电辅热功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_EAHeater(void)
{
	if (EAHeater.f_T2HighRecDelay)
	{
		if (Fan.Outdoor.u16_Count >= 1800)		//3min
		{
			EAHeater.f_T2HighRecDelay = 0;
		}
	}

	if (EAHeater.f_ColdToHeat)
	{
		if (Comp.u32_RunContCount >= 1800)		//3min
		{
			EAHeater.f_ColdToHeat = 0;
		}
	}
	
	if (EAHeater.f_DrvOn == OFF)
	{	
//		if ((EAHeater.f_AppOn == ON) && (Fan.Indoor.f_DrvOn == ON))
		if ((SystemMode.f_Heat == 1) 
		&& (Fan.Indoor.f_DrvOn == 1)
		&& (Fan.Outdoor.f_DrvOn == 1)
		&& (Comp.f_DrvOn == 1)
		&& (T1.s16_ValueMul10 <= 250)
		&& (TempValueMul10(Tempr.u8_HeatCSet) >= T1.s16_ValueMul10 + 30)
		&& (T2.s16_ValueMul10 < 480)
		&& (!EAHeater.u16_Delay)
		&& (!EAHeater.f_T2HighRecDelay)
		&& (EAHeater.f_ColdToHeat == 0))
		{
			EAHeater.f_DrvOn = ON;
		}
	}
	else
	{
//		if ((EAHeater.f_AppOn == OFF) || (Fan.Indoor.f_DrvOn == OFF))
		if ((Fan.Indoor.f_DrvOn == 0)
		|| (T1.s16_ValueMul10 >= 270)
		|| (TempValueMul10(Tempr.u8_HeatCSet) <= T1.s16_ValueMul10 + 10)
		|| (T2.s16_ValueMul10 >= 490)
		|| (Comp.f_DrvOn == 0)
		|| (FourWay.f_DrvOn == 0)
		|| (T1.f_Error || T2.f_Error || T3.f_Error || T4.f_Error || Tp.f_Error))
		{
			EAHeater.f_DrvOn = OFF;
			if (Comp.f_DrvOn == 1)
			{
				EAHeater.u16_Delay = 600;  //1min
			}
			else if (T1.f_Error || T2.f_Error)
			{
				EAHeater.u16_Delay = 0;  	//
			}
		}
	}
	
	if (EAHeater.f_DrvOn)	P_EAHeater_On();
	else					P_EAHeater_Off();
}
