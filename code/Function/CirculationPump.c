/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: DCFan.c
Description   		: C
Author        		: 冯锐辉
Start Date    		: 2025年9月11日10:09:58
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_CIRCULATIONPUMP    CirculationPump;         //循环泵

/* 在 PC / UNIT_TEST 环境下，将循环泵的硬件操作改为由外部函数提供，
 * 便于在单元测试中用模拟函数替代真实 GPIO 操作。
 */
#if defined(UNIT_TEST)
#ifdef P_CirculationPump_On
#undef P_CirculationPump_On
#endif
#ifdef P_CirculationPump_Off
#undef P_CirculationPump_Off
#endif
#ifdef P_CirculationPump_Output
#undef P_CirculationPump_Output
#endif
#ifdef P_CirculationPump_Dispull
#undef P_CirculationPump_Dispull
#endif

extern void P_CirculationPump_On(void);
extern void P_CirculationPump_Off(void);
extern void P_CirculationPump_Output(void);
extern void P_CirculationPump_Dispull(void);
#endif

/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :循环初始化
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_CirculationPump(void)
{
    P_CirculationPump_Off();  
    P_CirculationPump_Output();	
	P_CirculationPump_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Func_CirculationPump(void)
Description         :循环泵功能
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_CirculationPump(void)
{
//	CirculationPump.f_AppOn = Comp.f_DrvOn;
	{
		U32 u32StopDelay = (U32)(FtyPara.u16P3 + FtyPara.u16P5) * 10U;
		U8 bCompStopped = (Comp.f_DrvOn == 0);
		U8 bStopSeqKeepOn = bCompStopped && (Comp.u32_StopContCount < u32StopDelay);
		U8 bStopSeqAllowOff = bCompStopped && (Comp.u32_StopContCount >= u32StopDelay) && (Fan.Outdoor.f_DrvOn == 0);

		if (((CirculationPump.f_AppOn == 1)
		&& (Comp.u16_RestartDelay <= 900 )
		&& (Comp.u8_SelTestDelay <= 900)
		&& (Comp.u8_PowerOnDelay <= 900))
		|| (Defrost.f_Enable)
		|| bStopSeqKeepOn)
		{
			CirculationPump.f_AppOn = ON;
		}
		else if (bStopSeqAllowOff)
		{
			CirculationPump.f_AppOn = OFF;
		}
	}

	
	if (CirculationPump.f_DrvOn == OFF)
	{
		if (CirculationPump.f_AppOn == ON)
		{
			//循环泵开启刹那
			CirculationPump.f_DrvOn = ON;
		}
	}
	else
	{
		if (CirculationPump.f_AppOn == OFF)
		{
			//循环泵关停刹那
			if (CirculationPump.u16_Delay == 0)
			{
				CirculationPump.f_DrvOn = OFF;
			}
		}	
	}
	
	if ((CirculationPump.f_DrvOn) || (CirculationPump.f_ForceDrvOn == 1))		
	{
		P_CirculationPump_On();
	}
	else								
	{
		P_CirculationPump_Off();
	}
}
