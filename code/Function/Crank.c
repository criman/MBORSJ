/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Crank.c
Description   		: C
Author        		: 冯锐辉
Start Date    		: 2025年9月11日11:32:53
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_Crank    Crank;         //曲轴电加热

/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :曲轴电加热初始化
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_Crank(void)
{
    P_Crank_Off();  
    P_Crank_Output();	
	P_Crank_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Func_Crank(void)
Description         :曲轴电加热功能
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Crank(void)
{
//	Crank.f_AppOn = Comp.f_DrvOn;
	if ((Comp.f_DrvOn == OFF) 
	&& (T4.s16_ValueMul10 < 80) 
	&&(System.Enum_Status == ENUM_STATUS_ON))
	{
		Crank.f_AppOn = ON;
	}
	else if ((Comp.f_DrvOn == ON) 
	|| (T4.s16_ValueMul10 > 80) 
	|| (System.Enum_Status == ENUM_STATUS_OFF))
	{
		Crank.f_AppOn = OFF;
	}
	
	if (Crank.f_DrvOn == OFF)
	{
		if (Crank.f_AppOn == ON)
		{
			//曲轴电加热开启刹那
			Crank.f_DrvOn = ON;
		}
	}
	else
	{
		if (Crank.f_AppOn == OFF)
		{
			//曲轴电加热关停刹那
			if (Crank.u16_Delay == 0)
			{
				Crank.f_DrvOn = OFF;
			}
		}	
	}
	
	if ((Crank.f_DrvOn) || (Crank.f_ForceDrvOn))		
	{
		P_Crank_On();
	}
	else					
	{
		P_Crank_Off();
	}
}
