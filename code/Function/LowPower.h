/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Tempr.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/18
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _LOWPOWER_H_

#define    _LOWPOWER_H_

//===================================================================================================//
//选择PowEn12V控制端口
//---------------------------------------------------------------------------------------------------//
#define		PowEn12V_SigValid					0//PowEnPTC工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_PowEn12V						PortPin_Read(GPIOA, GPIO_Pin_28)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_PowEn12V_Hi()						DEFINE_PA28_HI					//例子:DEFINE_P00_HI
#define		P_PowEn12V_Low()					DEFINE_PA28_LOW					//例子:DEFINE_P00_LOW
#define		P_PowEn12V_Output()					DEFINE_PA28_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_PowEn12V_Input()					DEFINE_PA28_INPUT				//例子:DEFINE_P00_INPUT
#define		P_PowEn12V_Enpull()					DEFINE_PA28_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_PowEn12V_Dispull()				DEFINE_PA28_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (PowEn12V_SigValid == 1)
#define		P_PowEn12V_On()						P_PowEn12V_Hi()
#define		P_PowEn12V_Off()					P_PowEn12V_Low()
#else
#define		P_PowEn12V_On()						P_PowEn12V_Low()
#define		P_PowEn12V_Off()					P_PowEn12V_Hi()
#endif
//===================================================================================================//

//===================================================================================================//
//选择PowEnPTC控制端口-小继电器-ptc
//---------------------------------------------------------------------------------------------------//
#define		PowEnPTC_SigValid					1//PowEnPTC工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_PowEnPTC						PortPin_Read(GPIOA, GPIO_Pin_14)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_PowEnPTC_Hi()						DEFINE_PA14_HI					//例子:DEFINE_P00_HI
#define		P_PowEnPTC_Low()					DEFINE_PA14_LOW					//例子:DEFINE_P00_LOW
#define		P_PowEnPTC_Output()					DEFINE_PA14_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_PowEnPTC_Input()					DEFINE_PA14_INPUT				//例子:DEFINE_P00_INPUT
#define		P_PowEnPTC_Enpull()					DEFINE_PA14_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_PowEnPTC_Dispull()				DEFINE_PA14_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (PowEnPTC_SigValid == 1)
#define		P_PowEnPTC_On()						P_PowEnPTC_Hi()
#define		P_PowEnPTC_Off()					P_PowEnPTC_Low()
#else
#define		P_PowEnPTC_On()						P_PowEnPTC_Low()
#define		P_PowEnPTC_Off()					P_PowEnPTC_Hi()
#endif
//===================================================================================================//

//===================================================================================================//
//选择PowEnPTCB控制端口-大继电器
//---------------------------------------------------------------------------------------------------//
#define		PowEnPTCB_SigValid					1//PowEnPTCB工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_PowEnPTCB						PortPin_Read(GPIOA, GPIO_Pin_29)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_PowEnPTCB_Hi()					DEFINE_PA29_HI					//例子:DEFINE_P00_HI
#define		P_PowEnPTCB_Low()					DEFINE_PA29_LOW					//例子:DEFINE_P00_LOW
#define		P_PowEnPTCB_Output()				DEFINE_PA29_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_PowEnPTCB_Input()					DEFINE_PA29_INPUT				//例子:DEFINE_P00_INPUT
#define		P_PowEnPTCB_Enpull()				DEFINE_PA29_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_PowEnPTCB_Dispull()				DEFINE_PA29_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (PowEnPTCB_SigValid == 1)
#define		P_PowEnPTCB_On()					P_PowEnPTCB_Hi()
#define		P_PowEnPTCB_Off()					P_PowEnPTCB_Low()
#else
#define		P_PowEnPTCB_On()					P_PowEnPTCB_Low()
#define		P_PowEnPTCB_Off()					P_PowEnPTCB_Hi()
#endif
//===================================================================================================//

typedef    enum
{
	ENUM_LOWPOWER_INIT,		
	ENUM_LOWPOWER_GO,

}ENUM_LOWPOWER;
extern    ENUM_LOWPOWER    Enum_LowPower;

typedef    struct
{
	U8    f_AppOn    :1;
	U8    f_DrvOn    :1;	
	U8    f_InitOk   :1;
	U8    f_FirstOk  :1;
	U8    Reserve    :4;
	U16   u16_Delay;

}STRUCT_LOWPOWER;

extern    STRUCT_LOWPOWER    PowEn12V;
extern    STRUCT_LOWPOWER    PowEnPTC;
extern	  STRUCT_LOWPOWER    PowEnPTCB;

/****************************************************************************************************
Function Name       :void    Init_LowPower(void)
Description         :低功耗控制初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_LowPower(void);
/****************************************************************************************************
Function Name       :void    Func_LowPower(void)
Description         :低功耗控制功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_LowPower(void);

#endif
