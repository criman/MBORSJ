/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: UVC.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/13
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _UVC_H_

#define    _UVC_H_

//===================================================================================================//
//选择UVC_控制端口
//---------------------------------------------------------------------------------------------------//
#define		UVC_SigValid						1//UVC工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_UVC								PortPin_Read(GPIOB, GPIO_Pin_12)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_UVC_Hi()							DEFINE_PB12_HI					//例子:DEFINE_P00_HI
#define		P_UVC_Low()							DEFINE_PB12_LOW					//例子:DEFINE_P00_LOW
#define		P_UVC_Output()						DEFINE_PB12_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_UVC_Input()						DEFINE_PB12_INPUT				//例子:DEFINE_P00_INPUT
#define		P_UVC_Enpull()						DEFINE_PB12_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_UVC_Dispull()						DEFINE_PB12_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (UVC_SigValid == 1)
#define		P_UVC_On()							P_UVC_Hi()
#define		P_UVC_Off()							P_UVC_Low()
#else
#define		P_UVC_On()							P_UVC_Low()
#define		P_UVC_Off()							P_UVC_Hi()
#endif
//===================================================================================================//

//===================================================================================================//
//--------------------------------------------------------------------------------------------------//
//UVC相关参数宏定义
#define    C_UVC_PERIOD_ON         				18000        						//UV杀菌灯连续运行30分钟
#define    C_UVC_PERIOD_OFF		  				3000		   						//UV杀菌灯停止5分钟
#define    C_UVC_PERIOD_COUNT	  				(C_UVC_PERIOD_ON+C_UVC_PERIOD_OFF)	//UV灯工作周期
//--------------------------------------------------------------------------------------------------//
typedef    struct
{
    U8     f_AppOn	  	 :1;			  //应用打开标志
	U8     f_DrvOn	  	 :1;			  //驱动打开标志
	U8     f_FuncOn   	 :1;			  //功能开关
	U8     f_FuncOnBak   :1;			  //功能开关
	U8     Reserved0  	 :4;			  //预留
	U16    u16_PeriodCount;        	  	  //工作周期性计时
}STRUCT_UVC;

//--------------------------------------------------------------------------------------------------//

extern    STRUCT_UVC    UVC;         //UV灯

/****************************************************************************************************
Function Name       :void    Init_UVC(void)
Description         :UVC初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_UVC(void);
/****************************************************************************************************
Function Name       :void	TimerUVC_Run(void)
Description         :UVC相关时间计时
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    TimerUVC_Run(void);
/****************************************************************************************************
Function Name       :void    Func_UVC(void)
Description         :UVC功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_UVC(void);

#endif
