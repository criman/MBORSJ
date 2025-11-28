/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Fan.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _FAN_H_

#define    _FAN_H_


//===================================================================================================//
//选择内风机高档_控制端口
//---------------------------------------------------------------------------------------------------//
#define		InDoorFanH_SigValid							1//DCFan工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_InDoorFanH								PortPin_Read(GPIOA, GPIO_Pin_28)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_InDoorFanH_Hi()							DEFINE_PA28_HI					//例子:DEFINE_P00_HI
#define		P_InDoorFanH_Low()							DEFINE_PA28_LOW					//例子:DEFINE_P00_LOW
#define		P_InDoorFanH_Output()						DEFINE_PA28_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_InDoorFanH_Input()						DEFINE_PA28_INPUT				//例子:DEFINE_P00_INPUT
#define		P_InDoorFanH_Enpull()						DEFINE_PA28_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_InDoorFanH_Dispull()						DEFINE_PA28_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (InDoorFanH_SigValid == 1)
#define		P_InDoorFanH_On()							P_InDoorFanH_Hi()
#define		P_InDoorFanH_Off()							P_InDoorFanH_Low()
#else
#define		P_InDoorFanH_On()							P_InDoorFanH_Low()
#define		P_InDoorFanH_Off()							P_InDoorFanH_Hi()
#endif

//===================================================================================================//
//选择内风机中档_控制端口
//---------------------------------------------------------------------------------------------------//
#define		InDoorFanM_SigValid							1//DCFan工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_InDoorFanM								PortPin_Read(GPIOA, GPIO_Pin_29)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_InDoorFanM_Hi()							DEFINE_PA29_HI					//例子:DEFINE_P00_HI
#define		P_InDoorFanM_Low()							DEFINE_PA29_LOW					//例子:DEFINE_P00_LOW
#define		P_InDoorFanM_Output()						DEFINE_PA29_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_InDoorFanM_Input()						DEFINE_PA29_INPUT				//例子:DEFINE_P00_INPUT
#define		P_InDoorFanM_Enpull()						DEFINE_PA29_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_InDoorFanM_Dispull()						DEFINE_PA29_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (InDoorFanM_SigValid == 1)
#define		P_InDoorFanM_On()							P_InDoorFanM_Hi()
#define		P_InDoorFanM_Off()							P_InDoorFanM_Low()
#else
#define		P_InDoorFanM_On()							P_InDoorFanM_Low()
#define		P_InDoorFanM_Off()							P_InDoorFanM_Hi()
#endif

//===================================================================================================//
//选择内风机低档_控制端口
//---------------------------------------------------------------------------------------------------//
#define		InDoorFanL_SigValid							1//DCFan工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_InDoorFanL								PortPin_Read(GPIOA, GPIO_Pin_30)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_InDoorFanL_Hi()							DEFINE_PA30_HI					//例子:DEFINE_P00_HI
#define		P_InDoorFanL_Low()							DEFINE_PA30_LOW					//例子:DEFINE_P00_LOW
#define		P_InDoorFanL_Output()						DEFINE_PA30_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_InDoorFanL_Input()						DEFINE_PA30_INPUT				//例子:DEFINE_P00_INPUT
#define		P_InDoorFanL_Enpull()						DEFINE_PA30_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_InDoorFanL_Dispull()						DEFINE_PA30_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (InDoorFanL_SigValid == 1)
#define		P_InDoorFanL_On()							P_InDoorFanL_Hi()
#define		P_InDoorFanL_Off()							P_InDoorFanL_Low()
#else
#define		P_InDoorFanL_On()							P_InDoorFanL_Low()
#define		P_InDoorFanL_Off()							P_InDoorFanL_Hi()
#endif

//===================================================================================================//
//选择内风机低档_控制端口
//---------------------------------------------------------------------------------------------------//
#define		OutDoorFan_SigValid							1//DCFan工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_OutDoorFan								PortPin_Read(GPIOA, GPIO_Pin_29)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_OutDoorFan_Hi()							DEFINE_PA29_HI					//例子:DEFINE_P00_HI
#define		P_OutDoorFan_Low()							DEFINE_PA29_LOW					//例子:DEFINE_P00_LOW
#define		P_OutDoorFan_Output()						DEFINE_PA29_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_OutDoorFan_Input()						DEFINE_PA29_INPUT				//例子:DEFINE_P00_INPUT
#define		P_OutDoorFan_Enpull()						DEFINE_PA29_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_OutDoorFan_Dispull()						DEFINE_PA29_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (OutDoorFan_SigValid == 1)
#define		P_OutDoorFan_On()							P_OutDoorFan_Hi()
#define		P_OutDoorFan_Off()							P_OutDoorFan_Low()
#else
#define		P_OutDoorFan_On()							P_OutDoorFan_Low()
#define		P_OutDoorFan_Off()							P_OutDoorFan_Hi()
#endif


//-----------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_FANMODE_INIT,	  //初始化不确定
	ENUM_FANMODE_HIGH,    //高风
	ENUM_FANMODE_MED,     //中风
	ENUM_FANMODE_LOW,     //低风
	ENUM_FANMODE_AUTO,    //自动风
}ENUM_FANMODE;

//-----------------------------------------------------------------------------------------------------//

typedef    enum
{
    ENUM_FANLEVEL_INIT,   //初始化不确定风速档位
	ENUM_FANLEVEL_LOW_S,  //风速微风档
	ENUM_FANLEVEL_LOW,    //风速低档
	ENUM_FANLEVEL_MED,    //风速中档
	ENUM_FANLEVEL_HIGH,   //风速高档
	ENUM_FANLEVEL_HIGH_S, //风速强力档
}ENUM_FANLEVEL;

typedef    enum
{
    ENUM_FANSETMB_INIT,   				//初始化
    ENUM_FANSETMB_SPEEDSETRANGE,  		//速度命令范围设置
	ENUM_FANSETMB_ONSPEEDSET,  			//速度命令设置
	ENUM_FANSETMB_ONSPEEDSETCHECK,  	//速度命令设置查询
	ENUM_FANSETMB_ONSET,    			//开机命令设置
	ENUM_FANSETMB_RUNCHECK,   			//运行时查询
	ENUM_FANSETMB_RUNCHECKERR,  		//运行时检测错误
	ENUM_FANSETMB_RUNSPEEDSET,  		//运行时改变风速
	ENUM_FANSETMB_OFFSET,    			//关机命令设置
	ENUM_FANSETMB_OFFCHECK,   		//关机时查询
}ENUM_FANSETMB;

//-----------------------------------------------------------------------------------------------------//

typedef    struct
{
	U8               f_AppOn    :1;
	U8               f_DrvOn    :1;
	U8               f_ForceLow :1;
	U8				 f_Error	:1;
	U8				 f_ErrorDeal:1; //某次内机故障处理完成，允许回复外机清故障码	    lcx add 20240622
	U8               f_EnableMASet	:1;		//0风机自动风速/1风机手动风速
	U8               f_FanType		:1;		//0风机继电器输出/1风机板输出
	U8	  			 f_ForceDrvOn	:1;		//强制打开负载标志
	
	ENUM_FANLEVEL    Level;            //风速档位
	ENUM_FANSETMB    SetMBStatus;	   //调速板modbus设置状态机
	U16              u16_TargetRPM;    //目标转速
	U16              u16_MATargetRPM;    //手动目标转速
	U16 			 u16_RealRPM;	   //实际转速
	U16              u16_Delay;		   //延时计时
	U16              u16_Count;		   //工作计时
	U16              u16_ErrRunCount;  //带故障运行计时 lcx add 20240622
	U8               u8_ErrRunTimes;   //带故障运行次数 lcx add 20240622
	
}STRUCT_DCFAN;

//-----------------------------------------------------------------------------------------------------//

typedef    struct
{
	U8              f_SweepLR    	   :1;	//左右摇头
	U8              f_SweepLRChkBak    :1;	//左右摇头-商检检测备份
	U8              f_DeMold	 	   :1;	//除霉
	U8              u2_AutoInitFdCount :2;	//防抖
	U8				f_InDoorFanTpLow   :1;	//
	U8				Reserved		   :2;
	ENUM_FANMODE    Mode;					//风速模式
	ENUM_FANMODE    ModeBak;				//风速模式备份
	ENUM_FANMODE	ModeCECBak;		    	//达温时刻风速模式备份
	STRUCT_DCFAN    Indoor;					//内风机(上风机)
	STRUCT_DCFAN    Outdoor;				//外风机(下风机)
}STRUCT_FAN;

//-----------------------------------------------------------------------------------------------------//

extern    STRUCT_FAN    Fan;

/****************************************************************************************************
Function Name       :void    InDoorFanH_DriveOn(void)
Description         :内风机高风驱动
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    InDoorFanH_DriveOn(void);

/****************************************************************************************************
Function Name       :void    InDoorFanM_DriveOn(void)
Description         :内风机中风驱动
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    InDoorFanM_DriveOn(void);

/****************************************************************************************************
Function Name       :void    InDoorFanM_DriveOn(void)
Description         :内风机低风驱动
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    InDoorFanL_DriveOn(void);

/****************************************************************************************************
Function Name       :void    InDoorFan_DriveOff(void)
Description         :内风机关闭
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    InDoorFan_DriveOff(void);


/****************************************************************************************************
Function Name       :void    Init_InDoorFan(void)
Description         :室内风机初始化
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_InDoorFan(void);

/****************************************************************************************************
Function Name       :void    Init_InDoorFan(void)
Description         :室外风机初始化
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_OutDoorFan(void);


/****************************************************************************************************
Function Name       :void    Func_Fan(void)
Description         :风机功能处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Fan(void);

#endif
