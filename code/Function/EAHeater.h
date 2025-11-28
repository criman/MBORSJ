/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: EAHeater.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/18
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _EAHEATER_H_

#define    _EAHEATER_H_

//===================================================================================================//
//选择电辅热_控制端口
//---------------------------------------------------------------------------------------------------//
#define		EAHeater_SigValid						1//EAHeater工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_EAHeater							PortPin_Read(GPIOA, GPIO_Pin_20)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_EAHeater_Hi()							DEFINE_PA20_HI					//例子:DEFINE_P00_HI
#define		P_EAHeater_Low()						DEFINE_PA20_LOW					//例子:DEFINE_P00_LOW
#define		P_EAHeater_Output()						DEFINE_PA20_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_EAHeater_Input()						DEFINE_PA20_INPUT				//例子:DEFINE_P00_INPUT
#define		P_EAHeater_Enpull()						DEFINE_PA20_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_EAHeater_Dispull()					DEFINE_PA20_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (EAHeater_SigValid == 1)
#define		P_EAHeater_On()							P_EAHeater_Hi()
#define		P_EAHeater_Off()						P_EAHeater_Low()
#else
#define		P_EAHeater_On()							P_EAHeater_Low()
#define		P_EAHeater_Off()						P_EAHeater_Hi()
#endif
//===================================================================================================//

typedef    struct
{
    U8    f_AppOn    :1;
	U8    f_DrvOn    :1;
	U8    f_T2HighRecDelay    :1;
	U8    f_ColdToHeat	 :1;		//制冷转制热电辅热处理标志
	U8    Reserve	 :4; 
	U16   u16_Delay;
}STRUCT_EAHEATER;

extern    STRUCT_EAHEATER    EAHeater;
/****************************************************************************************************
Function Name       :void    Init_EAHeater(void)
Description         :打水电机初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_EAHeater(void);
/****************************************************************************************************
Function Name       :void    Func_EAHeater(void)
Description         :电加热功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_EAHeater(void);

#endif
