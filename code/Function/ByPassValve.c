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

STRUCT_BPV    BPV;         //旁通泵

/****************************************************************************************************
Function Name       :void    Init_BPV(void)
Description         :旁通泵初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_BPV(void)
{
    P_BPV_Off();  
    P_BPV_Output();	
	P_BPV_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Func_BPV(void)
Description         :旁通阀功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_BPV(void)
{
//	BPV.f_AppOn = Comp.f_DrvOn;
	if ((Tp.s16_ValueMul10 <= TempValueMul10(FtyPara.s16P21))
	|| (T5.s16_ValueMul10 <= TempValueMul10(FtyPara.s16P22))
	|| (Comp.f_DrvOn == 0))
	{
		BPV.f_AppOn = 0; 
	}
	else if ((Comp.f_DrvOn == 1) 
	&& (((T4.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P17))
	&& (T5.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P18))
	&& (Tp.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P19)))
	|| (Tp.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P20))))
	{
		BPV.f_AppOn = 1; 
	}
	
	
	if (BPV.f_DrvOn == OFF)
	{
		if (BPV.f_AppOn == ON)
		{
			//旁通阀开启刹那
			BPV.f_DrvOn = ON;
		}
	}
	else
	{
		if (BPV.f_AppOn == OFF)
		{
			//旁通阀刹那
			if (BPV.u16_Delay == 0)
			{
				BPV.f_DrvOn = OFF;
			}
		}	
	}
	
	if ((BPV.f_DrvOn) || (BPV.f_ForceDrvOn))
	{
		P_BPV_On();
	}
	else
	{
		P_BPV_Off();
	}
}
