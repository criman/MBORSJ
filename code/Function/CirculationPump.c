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

#if defined(UNIT_TEST)
    // 在测试环境中，全局变量在 test_compat.c 中定义
    extern STRUCT_CIRCULATIONPUMP CirculationPump;
#else
    STRUCT_CIRCULATIONPUMP    CirculationPump;         //循环泵
#endif

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
		/* 修复：上电初始化时，Comp.u32_StopContCount初始值为0，会导致bStopSeqKeepOn误判
		 * 增加系统状态判断，只有在非初始化状态且Comp.u32_StopContCount大于0时才判断保持开启
		 * 这样可以区分"上电初始状态"和"压缩机停止后的保持开启状态"
		 */
		U8 bPowerOnInit = (System.Enum_Status == ENUM_STATUS_INIT) || (System.u8_PowerOn_Count < 30);
		/* 修复：bStopSeqKeepOn需要增加Comp.f_HavedDrvOn判断
		 * 只有压缩机曾经运行过(f_HavedDrvOn==1)，停机后才需要保持循环泵开启
		 * 避免开机命令下发但未满足开机条件时误开循环泵
		 */
		U8 bStopSeqKeepOn = bCompStopped && (Comp.u32_StopContCount < u32StopDelay) 
			&& !bPowerOnInit && (Comp.u32_StopContCount > 0) && (Comp.f_HavedDrvOn == 1);
		/* 修复：bStopSeqAllowOff需要排除"正在启动"的情况
		 * 当循环泵已经在运行时(f_DrvOn==ON)，不应关闭
		 * 当循环泵请求开启时(f_AppOn==ON)，不应关闭
		 */
		U8 bStopSeqAllowOff = bCompStopped && (Comp.u32_StopContCount >= u32StopDelay) 
			&& (Fan.Outdoor.f_DrvOn == 0) && (CirculationPump.f_AppOn == OFF) 
			&& (CirculationPump.f_DrvOn == OFF);
		
		/* 修复：EEV初始化完成前不允许开启循环泵
		 * StepMotor.var.u8_status >= ENUM_STEPMOTOR_STATUS_RUN 表示EEV已完成复位
		 */
		U8 bEEVReady = (StepMotor.var.u8_status >= ENUM_STEPMOTOR_STATUS_RUN);
		
		/* 关闭顺序优先：一旦满足"允许关闭"的条件，应立即关闭循环泵，
		 * 其优先级高于常规保持开启的逻辑。
		 */
		if (bStopSeqAllowOff)
		{
			CirculationPump.f_AppOn = OFF;
		}
		else if ((((CirculationPump.f_AppOn == 1)
		&& (Comp.u16_RestartDelay <= 900 )
		&& (Comp.u8_SelTestDelay <= 900)
		&& (Comp.u8_PowerOnDelay <= 900))
		|| (Defrost.f_Enable)
		|| bStopSeqKeepOn)
		&& bEEVReady)	//EEV初始化完成后才允许开启
		{
			CirculationPump.f_AppOn = ON;
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
