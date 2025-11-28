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

STRUCT_SV    SV;         //喷液阀

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
void    Init_SV(void)
{
    P_SV_Off();  
    P_SV_Output();	
	P_SV_Dispull();	

}
/****************************************************************************************************
Function Name       :void    Func_SV(void)
Description         :喷液阀功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_SV(void)
{
	if ((Tp.s16_ValueMul10 >= SV.s16_OnTemp) && (Comp.f_DrvOn))		//95℃
	{
		SV.f_AppOn = ON;
	}
	else if ((Tp.s16_ValueMul10 < SV.s16_OffTemp) || (!Comp.f_DrvOn))
	{
		SV.f_AppOn = OFF;
	}
	
	
	if (SV.f_DrvOn == OFF)
	{
		if (SV.f_AppOn == ON)
		{
			//喷液阀开启刹那
			SV.f_DrvOn = ON;
		}
	}
	else
	{
		if (SV.f_AppOn == OFF)
		{
			//喷液阀关停刹那
			if (SV.u16_Delay == 0)
			{
				SV.f_DrvOn = OFF;
			}
		}	
	}
	
	if (SV.f_DrvOn)			P_SV_On();
	else					P_SV_Off();
}
