/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: UVC.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_UVC    UVC;         //UV灯

/****************************************************************************************************
Function Name       :void    Init_UVC(void)
Description         :UVC初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_UVC(void)
{
    P_UVC_Off();  
    P_UVC_Output();	
	P_UVC_Dispull();	
}
/****************************************************************************************************
Function Name       :void	TimerUVC_Run(void)
Description         :UVC相关时间计时
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    TimerUVC_Run(void)
{
	if (++UVC.u16_PeriodCount >= C_UVC_PERIOD_COUNT)	//UV周期性运行计时
	{
		UVC.u16_PeriodCount = 0;
	}
}
/****************************************************************************************************
Function Name       :void	Log_UVC(void)
Description         :UVC逻辑处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Log_UVC(void)
{
	if (UVC.f_FuncOn && (WaterBox.f_Full == 0))		UVC.f_AppOn = ON;
	else											UVC.f_AppOn = OFF;
	
	if ((System.Enum_Status == ENUM_STATUS_ON) || (System.Enum_Status == ENUM_STATUS_OFF))  //常规功能
	{
		if ((System.Enum_Status == ENUM_STATUS_ON) && (UVC.f_AppOn == ON) && (Fan.Indoor.f_DrvOn == ON) && (Fan.Indoor.u16_TargetRPM != 0))		//UVC功能开启且风机工作
		{
			if (UVC.u16_PeriodCount < C_UVC_PERIOD_ON)
			{
				UVC.f_DrvOn = ON;	//UV驱动开启
			}
			else
			{
				UVC.f_DrvOn  = OFF;	//UV驱动关闭
			}
		}
		else
		{
			UVC.f_DrvOn  = OFF;		//UV驱动关闭
			
			if (UVC.u16_PeriodCount < C_UVC_PERIOD_ON)	//保证UV杀菌灯需关闭5分钟才能重开
			{
				UVC.u16_PeriodCount = 0;
			}
		}
	}
	else	//初始化或测试状态
	{
		UVC.f_DrvOn = UVC.f_AppOn;
	}
}
/****************************************************************************************************
Function Name       :void	Log_UVC(void)
Description         :UVC驱动处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Drv_UVC(void)
{
	if (UVC.f_DrvOn)	P_UVC_On();
	else				P_UVC_Off();
}
/****************************************************************************************************
Function Name       :void    Func_UVC(void)
Description         :UVC功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_UVC(void)
{
	Log_UVC();
	Drv_UVC();
}
