/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: SyncFan.h
Description   		: H
Author        		: 冯锐辉
Start Date    		: 2025年7月24日17:49:53
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _SYNCFAN_H_

#define    _SYNCFAN_H_

//===================================================================================================//
//选择电辅热_控制端口
//---------------------------------------------------------------------------------------------------//
#define		SyncFan_SigValid							0//DCFan工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_SyncFan								PortPin_Read(GPIOA, GPIO_Pin_25)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_SyncFan_Hi()							DEFINE_PA25_HI					//例子:DEFINE_P00_HI
#define		P_SyncFan_Low()							DEFINE_PA25_LOW					//例子:DEFINE_P00_LOW
#define		P_SyncFan_Output()						DEFINE_PA25_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_SyncFan_Input()						DEFINE_PA25_INPUT				//例子:DEFINE_P00_INPUT
#define		P_SyncFan_Enpull()						DEFINE_PA25_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_SyncFan_Dispull()						DEFINE_PA25_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (SyncFan_SigValid == 1)
#define		P_SyncFan_On()							P_SyncFan_Hi()
#define		P_SyncFan_Off()							P_SyncFan_Low()
#else
#define		P_SyncFan_On()							P_SyncFan_Low()
#define		P_SyncFan_Off()							P_SyncFan_Hi()
#endif
//===================================================================================================//

#define    C_DCFAN_DELAY        300        //30s

typedef    struct
{
    U8    f_AppOn    :1;
	U8    f_DrvOn    :1;
	U8    Reserve    :6;
	U16	  u16_Delay;
}STRUCT_SYNCFAN;

extern    STRUCT_SYNCFAN    SyncFan;
/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :散热风扇始化
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_SyncFan(void);
/****************************************************************************************************
Function Name       :void    Func_DCFan(void)
Description         :散热风扇功能
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_SyncFan(void);

#endif
