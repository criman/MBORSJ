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

STRUCT_COMPDCFAN    DCFan;         //散热风扇

/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :散热风扇初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_DCFan(void)
{
    P_DCFan_Off();  
    P_DCFan_Output();	
	P_DCFan_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Func_DCFan(void)
Description         :散热风扇功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_DCFan(void)
{
	DCFan.f_AppOn = Comp.f_DrvOn;
	
	
	if (DCFan.f_DrvOn == OFF)
	{
		if (DCFan.f_AppOn == ON)
		{
			//散热风机开启刹那
			DCFan.f_DrvOn = ON;
		}
	}
	else
	{
		if (DCFan.f_AppOn == OFF)
		{
			//散热风机关停刹那
			if (DCFan.u16_Delay == 0)
			{
				DCFan.f_DrvOn = OFF;
			}
		}	
	}
	
	if (DCFan.f_DrvOn)		P_DCFan_On();
	else					P_DCFan_Off();
}
