/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: WPMotor.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/13
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_WPMOTOR    WPMotor;         //打水电机

/****************************************************************************************************
Function Name       :void    Init_WPMotor(void)
Description         :打水电机初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_WPMotor(void)
{
    P_WPMotor_Off();  
    P_WPMotor_Output();	
	P_WPMotor_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Log_WPMotor(void)
Description         :打水电机逻辑处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Log_WPMotor(void)
{
	if (WPMotor.f_DrvOn == OFF)
	{
		if ((WPMotor.f_AppOn == ON) && (((T4.f_Error == 0) && (T4.s16_ValueMul10 > 50)) || (System.Enum_Status == ENUM_STATUS_BUSSCHK)) && 
			(Comp.f_DrvOn == ON) && (WPMotor.u16_CompOnDelay == 0))
		{
		
			//打水电机启动瞬间
			WPMotor.f_DrvOn = ON;
		}
	}
	else
	{
		if ((WPMotor.f_AppOn == OFF) || T4.f_Error || (T4.s16_ValueMul10 <= 30) || WPMotor.u16_CompOnDelay)
		{
		
			//打水电机关闭瞬间
			WPMotor.f_DrvOn = OFF;
		}
	}
}
/****************************************************************************************************
Function Name       :void    Drv_WPMotor(void)
Description         :打水电机驱动处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Drv_WPMotor(void)
{
	if (WPMotor.f_DrvOn)	P_WPMotor_On();
	else					P_WPMotor_Off();
}
/****************************************************************************************************
Function Name       :void    Func_WPMotor(void)
Description         :打水电机功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_WPMotor(void)
{
	Log_WPMotor();
	Drv_WPMotor();
}
