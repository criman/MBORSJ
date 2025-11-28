/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: SyncFan.c
Description   		: C
Author        		: 冯锐辉
Start Date    		: 2025年7月24日17:49:21
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_SYNCFAN    SyncFan;         //同步风机

/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :同步风机初始化
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_SyncFan(void)
{
    P_SyncFan_Off();  
    P_SyncFan_Output();	
	P_SyncFan_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Func_SyncFan(void)
Description         :同步风机功能
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_SyncFan(void)
{
	SyncFan.f_AppOn = Fan.Indoor.f_DrvOn;
	
	
	if (SyncFan.f_DrvOn == OFF)
	{
		if (SyncFan.f_AppOn == ON)
		{
			//同步风机开启刹那
			SyncFan.f_DrvOn = ON;
		}
	}
	else
	{
		if (SyncFan.f_AppOn == OFF)
		{
			//同步风机关停刹那
			if (SyncFan.u16_Delay == 0)
			{
				SyncFan.f_DrvOn = OFF;
			}
		}	
	}
	
	if (SyncFan.f_DrvOn)		P_SyncFan_On();
	else						P_SyncFan_Off();
}
