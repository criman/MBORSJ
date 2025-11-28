/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: WPMotor.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _WPMOTOR_H_

#define    _WPMOTOR_H_

//===================================================================================================//
//选择打水电机_控制端口
//---------------------------------------------------------------------------------------------------//
#define		WPMotor_SigValid						1//WPMotor工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_WPMotor								PortPin_Read(GPIOA, GPIO_Pin_2)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_WPMotor_Hi()							DEFINE_PA2_HI					//例子:DEFINE_P00_HI
#define		P_WPMotor_Low()							DEFINE_PA2_LOW					//例子:DEFINE_P00_LOW
#define		P_WPMotor_Output()						DEFINE_PA2_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_WPMotor_Input()						DEFINE_PA2_INPUT				//例子:DEFINE_P00_INPUT
#define		P_WPMotor_Enpull()						DEFINE_PA2_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_WPMotor_Dispull()						DEFINE_PA2_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (WPMotor_SigValid == 1)
#define		P_WPMotor_On()							P_WPMotor_Hi()
#define		P_WPMotor_Off()							P_WPMotor_Low()
#else
#define		P_WPMotor_On()							P_WPMotor_Low()
#define		P_WPMotor_Off()							P_WPMotor_Hi()
#endif
//===================================================================================================//

typedef    struct
{
    U8    f_AppOn    :1;
	U8    f_DrvOn    :1;
	U8    Reserve    :6;
	U16   u16_CompOnDelay;	//压缩机启动90s后
}STRUCT_WPMOTOR;

extern    STRUCT_WPMOTOR    WPMotor;
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
void    Init_WPMotor(void);
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
void    Func_WPMotor(void);

#endif
