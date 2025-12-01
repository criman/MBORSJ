/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: DCFan.h
Description   		: H
Author        		: 冯锐辉
Start Date    		: 2025年9月11日10:07:37
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _CIRCULATIONPUMP_H_

#define    _CIRCULATIONPUMP_H_

//===================================================================================================//
//选择循环泵_控制端口
//---------------------------------------------------------------------------------------------------//
#define		CirculationPump_SigValid						1//CirculationPump工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_CirculationPump								PortPin_Read(GPIOA, GPIO_Pin_30)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_CirculationPump_Hi()							DEFINE_PA30_HI					//例子:DEFINE_P00_HI
#define		P_CirculationPump_Low()							DEFINE_PA30_LOW					//例子:DEFINE_P00_LOW
#define		P_CirculationPump_Output()						DEFINE_PA30_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_CirculationPump_Input()						DEFINE_PA30_INPUT				//例子:DEFINE_P00_INPUT
#define		P_CirculationPump_Enpull()						DEFINE_PA30_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_CirculationPump_Dispull()						DEFINE_PA30_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (CirculationPump_SigValid == 1)
#define		P_CirculationPump_On()							P_CirculationPump_Hi()
#define		P_CirculationPump_Off()							P_CirculationPump_Low()
#else
#define		P_CirculationPump_On()							P_CirculationPump_Low()
#define		P_CirculationPump_Off()							P_CirculationPump_Hi()
#endif
//===================================================================================================//

#define    C_CirculationPump_DELAY        300        //30s

typedef    struct
{
    U8    f_AppOn    :1;
	U8    f_DrvOn    :1;
	U8    f_ForceDrvOn  :1;
	U8    Reserve    :5;
	U16	  u16_Delay;
	U16   u16_RunCnt;		//运行计时2025年9月25日15:48:29
	U16   u16_StopCnt;		//运行计时2025年9月25日15:48:29
}STRUCT_CIRCULATIONPUMP;

extern    STRUCT_CIRCULATIONPUMP    CirculationPump;
/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :循环泵初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_CirculationPump(void);
/****************************************************************************************************
Function Name       :void    Func_DCFan(void)
Description         :循环泵功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_CirculationPump(void);

#endif
