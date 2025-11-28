/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: BYPASSVALVE.h
Description   		: H
Author        		: 冯锐辉
Start Date    		: 2025年9月11日09:36:27
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _BYPASSVALVE_H_

#define    _BYPASSVALVE_H_

//===================================================================================================//
//选择电辅热_控制端口
//---------------------------------------------------------------------------------------------------//
#define		BPV_SigValid						1//BPV工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_BPV								PortPin_Read(GPIOA, GPIO_Pin_26)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_BPV_Hi()							DEFINE_PA26_HI					//例子:DEFINE_P00_HI
#define		P_BPV_Low()							DEFINE_PA26_LOW					//例子:DEFINE_P00_LOW
#define		P_BPV_Output()						DEFINE_PA26_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_BPV_Input()						DEFINE_PA26_INPUT				//例子:DEFINE_P00_INPUT
#define		P_BPV_Enpull()						DEFINE_PA26_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_BPV_Dispull()						DEFINE_PA26_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (BPV_SigValid == 1)
#define		P_BPV_On()							P_BPV_Hi()
#define		P_BPV_Off()							P_BPV_Low()
#else
#define		P_BPV_On()							P_BPV_Low()
#define		P_BPV_Off()							P_BPV_Hi()
#endif
//===================================================================================================//

#define    C_BPV_DELAY        300        //30s

typedef    struct
{
    U8    f_AppOn    :1;
	U8    f_DrvOn    :1;
	U8    f_ForceDrvOn    :1;                //强制打开负载标志
	U8    Reserve    :5;
	U16	  u16_Delay;
}STRUCT_BPV;

extern    STRUCT_BPV    BPV;
/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :旁通阀始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_BPV(void);
/****************************************************************************************************
Function Name       :void    Func_DCFan(void)
Description         :旁通阀功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_BPV(void);

#endif
