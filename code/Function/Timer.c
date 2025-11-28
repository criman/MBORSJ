/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Timer.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_TIMER    Timer;

/****************************************************************************************************
Function Name       :void    TimerPara_Init(void)
Description         :定时相关变量清除
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    TimerPara_Init(void)
{
	memset(&Timer, 0, sizeof(STRUCT_TIMER));	//结构体成员清0
}
/****************************************************************************************************
Function Name       :void Timer_Run(void)
Description         :常规定时计时
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Timer_Run(void)
{
	if (Timer.f_OffEn || Timer.f_OnEn)
	{
		Timer.f_Enable = 1;
		
		if (Timer.u16_SecDiv10Remain > 0) 
		{
			Timer.u16_SecDiv10Remain -= 1;
			
			if ((Timer.u16_SecDiv10Remain == 0) && (Timer.u16_Minute == 0))
			{
				//定时结束

				if (Timer.f_OffEn == CF_ENABLE)	DisplayBoardTurnOff();    //关机处理
					
				if (Timer.f_OnEn == CF_ENABLE)	DisplayBoardTurnOn();     //开机处理
							
			}			
		}
		else
		{
			if (Timer.u16_Minute > 0)
			{
				Timer.u16_Minute -= 1;
				Timer.u16_SecDiv10Remain = 599;				
			}
		}
		
	}
	else
	{
		Timer.f_Enable = 0;
	}
}
