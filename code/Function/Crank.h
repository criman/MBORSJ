/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Crank.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/18
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _CRANK_H_

#define    _CRANK_H_

//===================================================================================================//
//选择电辅热_控制端口
//---------------------------------------------------------------------------------------------------//
#define		Crank_SigValid							1//Crank工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_Crank								PortPin_Read(GPIOA, GPIO_Pin_27)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_Crank_Hi()							DEFINE_PA27_HI					//例子:DEFINE_P00_HI
#define		P_Crank_Low()							DEFINE_PA27_LOW					//例子:DEFINE_P00_LOW
#define		P_Crank_Output()						DEFINE_PA27_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Crank_Input()							DEFINE_PA27_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Crank_Enpull()						DEFINE_PA27_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_Crank_Dispull()						DEFINE_PA27_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (Crank_SigValid == 1)
#define		P_Crank_On()							P_Crank_Hi()
#define		P_Crank_Off()							P_Crank_Low()
#else
#define		P_Crank_On()							P_Crank_Low()
#define		P_Crank_Off()							P_Crank_Hi()
#endif
//===================================================================================================//

#define    C_CRANK_DELAY        300        //30s

typedef    struct
{
    U8    f_AppOn    :1;
	U8    f_DrvOn    :1;
	U8    f_ForceDrvOn        :1;                //强制打开负载标志
	U8    Reserve    :5;
	U16	  u16_Delay;
}STRUCT_Crank;

extern    STRUCT_Crank    Crank;
/****************************************************************************************************
Function Name       :void    Init_Crank(void)
Description         :曲轴电加热初始化
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_Crank(void);
/****************************************************************************************************
Function Name       :void    Func_Crank(void)
Description         :曲轴电加热功能
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Crank(void);

#endif
