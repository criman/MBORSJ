/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: WaterFeedValve.h
Description   		: H
Author        		: 冯锐辉
Start Date    		: 2025年9月11日09:36:27
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _WATERFEEDVALVE_H_

#define    _WATERFEEDVALVE_H_

//===================================================================================================//
//选择电辅热_控制端口
//---------------------------------------------------------------------------------------------------//
#define		WFV_SigValid						1//WFV工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_WFV								PortPin_Read(GPIOA, GPIO_Pin_26)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_WFV_Hi()							DEFINE_PA26_HI					//例子:DEFINE_P00_HI
#define		P_WFV_Low()							DEFINE_PA26_LOW					//例子:DEFINE_P00_LOW
#define		P_WFV_Output()						DEFINE_PA26_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_WFV_Input()						DEFINE_PA26_INPUT				//例子:DEFINE_P00_INPUT
#define		P_WFV_Enpull()						DEFINE_PA26_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_WFV_Dispull()						DEFINE_PA26_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (WFV_SigValid == 1)
#define		P_WFV_On()							P_WFV_Hi()
#define		P_WFV_Off()							P_WFV_Low()
#else
#define		P_WFV_On()							P_WFV_Low()
#define		P_WFV_Off()							P_WFV_Hi()
#endif
//===================================================================================================//

#define    C_WFV_DELAY        300        //30s

typedef    struct
{
    U8    f_AppOn				:1;
	U8    f_DrvOn				:1;
	U8    f_ForceDrvOn			:1;		//强制打开负载标志
	U8    f_Timing				:1;		//定时补水
	U8    f_Auto				:1;		//自动补水
	U8    f_ManualON			:1;		//手动补水
	U8    f_ManualOFF			:1;		//手动关闭补水
	U8    Reserve    			:1;
	U16	  u16_Delay;
	U16   u16_AutoCnt;					//自动补水计时
	U16   u16_TimingCnt;				//定时补水计时
}STRUCT_WFV;

extern    STRUCT_WFV    WFV;
/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :补水阀始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_WFV(void);
/****************************************************************************************************
Function Name       :void    Func_DCFan(void)
Description         :补水阀功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_WFV(void);

#endif
