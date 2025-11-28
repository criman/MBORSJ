/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Comp.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/13
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _COMP_H_

#define    _COMP_H_

//===================================================================================================//
//选择压缩机_控制端口
//---------------------------------------------------------------------------------------------------//
#define		Comp_SigValid							1//DCFan工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_Comp								PortPin_Read(GPIOA, GPIO_Pin_31)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_Comp_Hi()								DEFINE_PA31_HI					//例子:DEFINE_P00_HI
#define		P_Comp_Low()							DEFINE_PA31_LOW					//例子:DEFINE_P00_LOW
#define		P_Comp_Output()							DEFINE_PA31_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Comp_Input()							DEFINE_PA31_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Comp_Enpull()							DEFINE_PA31_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_Comp_Dispull()						DEFINE_PA31_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (Comp_SigValid == 1)
#define		P_Comp_On()								P_Comp_Hi()
#define		P_Comp_Off()							P_Comp_Low()
#else
#define		P_Comp_On()								P_Comp_Low()
#define		P_Comp_Off()							P_Comp_Hi()
#endif
//===================================================================================================//

//--------------------------------------------------------------------------------------------------//
//压缩机相关参数宏定义
#define    C_COMP_RUNMINDELAY					1800		//压缩机最小运行时间3分钟
#define    C_COMP_RESTARTDELAY0					400			//压缩机重启需等待最小时间40秒(上电)
#define    C_COMP_RESTARTDELAY					1800		//压缩机重启需等待最小时间3分钟 + 风机延时5秒
#define    C_COMP_BUSSCHK_RESTARTDELAY			600			//压缩机重启需等待最小时间1分钟
#define    C_COMP_STARTINITDELAY        		1800        //压缩机3分钟启动流程


//--------------------------------------------------------------------------------------------------//

typedef    struct
{
    U8    f_AppOn         :1;		//应用标志
	U8    f_DrvOn         :1;		//驱动标志
	U8    f_FourWayAbn    :1;		//四通阀导致压机逼停
	U8    f_IPMPro		  :1;		//IPM模块保护
	U8    f_IPMErr		  :1;		//IPM模块故障
	U8    f_StartErr	  :1;		//启动故障
	U8    f_HeatFirstOn	  :1;		//启动故障
	U8    f_Delay2min     :1;		//压缩机延迟2min

	U8	  f_ForceDrvOn	  :1;		//强制打开负载标志
	U8    f_HavedDrvOn 	  :1;		//上电后开启过标志	
	U8    Reserve    	  :6; 		//预留
	
	U8    u8_RealHZ;                //通信获取压缩机运行实际频率
	U8    u8_TargetSrc;				//启动源频率
	U8    u8_TargetHZ;				//目标频率
	U8    u8_TargetFreq;			//主板期望实际运行频率
	U8    u8_InitIndex;				//起步初始3min启动流程频率档
	U8    u8_Cold_TargetHZ[16];
	U8    u8_Heat_TargetHZ[16];
	
	U16   u16_RunMinDelay;			//压缩机运行最小时间计时
	U8    u8_SelTestDelay;			//性能测试压缩机延迟外风机启动
	U16   u16_RestartDelay;			//压缩机重新启动延时计时
	U8    u8_PowerOnDelay;			//开机延时计时
	U32   u32_RunContCount;			//压缩机连续运行时间计时
	U32   u32_StopContCount;		//压缩机连续运行时间计时
	U16   u16_StartInitDelay;		//压缩机3分钟启动流程计时
	

}STRUCT_COMP;

//--------------------------------------------------------------------------------------------------//

extern    STRUCT_COMP    Comp;

/****************************************************************************************************
Function Name       :void    App_Comp_RunHzInitIndex(void)
Description         :压缩机启动频率档次判断
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_RunHzInitIndex(void);
/****************************************************************************************************
Function Name       :void    App_Comp_T1TSDelta(void)
Description         :T1/TS温差频率控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_Comp_T1TSDelta(void);
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
void    Init_Comp(void);

/****************************************************************************************************
Function Name       :void    Func_Comp(void)
Description         :压缩机功能处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Comp(void);
	
#endif
