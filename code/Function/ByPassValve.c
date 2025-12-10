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

#if defined(UNIT_TEST)
    // 在测试环境中，全局变量在 test_compat.c 中定义
    extern STRUCT_BPV BPV;
#else
    STRUCT_BPV    BPV;         //旁通泵
#endif

/* 在 PC / UNIT_TEST 环境下，将旁通阀的硬件操作改为由外部函数提供
 * 这样可以在单元测试中用模拟函数替代真实 GPIO 操作，避免链接到底层驱动。
 */
#if defined(UNIT_TEST)
#ifdef P_BPV_On
#undef P_BPV_On
#endif
#ifdef P_BPV_Off
#undef P_BPV_Off
#endif
#ifdef P_BPV_Output
#undef P_BPV_Output
#endif
#ifdef P_BPV_Dispull
#undef P_BPV_Dispull
#endif

extern void P_BPV_On(void);
extern void P_BPV_Off(void);
extern void P_BPV_Output(void);
extern void P_BPV_Dispull(void);
#endif

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
	// 压机开，当检测到环境温度Tair≥50℃（参数P17）且水箱温度Tw≥45℃（参数P18）且排气温度Td≥95℃（参数P19）时，开启旁通阀
	// 开启条件：压机开 且 ((Tair≥P17 且 Tw≥P18 且 Td≥P19) 或 Td≥P20)
	if ((Comp.f_DrvOn == 1) 
	&& (((T4.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P17))
	&& (T5.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P18))
	&& (Tp.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P19)))
	|| (Tp.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P20))))
	{
		BPV.f_AppOn = 1; 
	}
	// 关闭条件：压机关闭 或 Td≤P21 或 Tw≤P22
	else if ((Comp.f_DrvOn == 0)
	|| (Tp.s16_ValueMul10 <= TempValueMul10(FtyPara.s16P21))
	|| (T5.s16_ValueMul10 <= TempValueMul10(FtyPara.s16P22)))
	{
		BPV.f_AppOn = 0; 
	}
	// 如果关闭条件和开启条件都不满足，保持当前状态（不更新BPV.f_AppOn）
	
	
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
