/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: FourWay.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/13
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _FOURWAY_H_

#define    _FOURWAY_H_

//===================================================================================================//
//选择FourWay_控制端口
//---------------------------------------------------------------------------------------------------//
#define		FourWay_SigValid						1//FourWay工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_FourWay								PortPin_Read(GPIOA, GPIO_Pin_28)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_FourWay_Hi()							DEFINE_PA28_HI					//例子:DEFINE_P00_HI
#define		P_FourWay_Low()							DEFINE_PA28_LOW					//例子:DEFINE_P00_LOW
#define		P_FourWay_Output()						DEFINE_PA28_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_FourWay_Input()						DEFINE_PA28_INPUT				//例子:DEFINE_P00_INPUT
#define		P_FourWay_Enpull()						DEFINE_PA28_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_FourWay_Dispull()						DEFINE_PA28_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (FourWay_SigValid == 1)
#define		P_FourWay_On()							P_FourWay_Hi()
#define		P_FourWay_Off()							P_FourWay_Low()
#else
#define		P_FourWay_On()							P_FourWay_Low()
#define		P_FourWay_Off()							P_FourWay_Hi()
#endif
//===================================================================================================//

typedef    struct
{
    U8     f_AppOn	  :1;			  //应用打开标志
	U8     f_DrvOn	  :1;			  //驱动打开标志
	U8	   f_ForceDrvOn		:1;		  //强制打开负载标志
	U8     Reserved   :5;			  //预留
	U16    u16_Delay;                 //延时计时
	
}STRUCT_FOURWAY;
extern    STRUCT_FOURWAY    FourWay;
	
/****************************************************************************************************
Function Name       :void    Init_FourWay(void)
Description         :四通阀控制初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_FourWay(void);
/****************************************************************************************************
Function Name       :void    Func_FourWay(void)
Description         :四通阀功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_FourWay(void);

#endif
