/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: DCFan.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/18
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _SV_H_

#define    _SV_H_

//===================================================================================================//
//选择电辅热_控制端口
//---------------------------------------------------------------------------------------------------//
#define		SV_SigValid							1//DCFan工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_SV								PortPin_Read(GPIOA, GPIO_Pin_31)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_SV_Hi()							DEFINE_PA31_HI					//例子:DEFINE_P00_HI
#define		P_SV_Low()							DEFINE_PA31_LOW					//例子:DEFINE_P00_LOW
#define		P_SV_Output()						DEFINE_PA31_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_SV_Input()						DEFINE_PA31_INPUT				//例子:DEFINE_P00_INPUT
#define		P_SV_Enpull()						DEFINE_PA31_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_SV_Dispull()						DEFINE_PA31_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (SV_SigValid == 1)
#define		P_SV_On()							P_SV_Hi()
#define		P_SV_Off()							P_SV_Low()
#else
#define		P_SV_On()							P_SV_Low()
#define		P_SV_Off()							P_SV_Hi()
#endif
//===================================================================================================//

#define    C_SV_DELAY        300        //30s

typedef    struct
{
    U8    f_AppOn    :1;
	U8    f_DrvOn    :1;
	U8    Reserve    :6;
	U16	  u16_Delay;
	S16	  s16_OnTemp;		//开启温度
	S16	  s16_OffTemp;		//关闭温度
}STRUCT_SV;

extern    STRUCT_SV    SV;
/****************************************************************************************************
Function Name       :void    Init_DCFan(void)
Description         :散热风扇始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_SV(void);
/****************************************************************************************************
Function Name       :void    Func_DCFan(void)
Description         :散热风扇功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_SV(void);

#endif
