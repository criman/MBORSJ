/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Protect.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/23
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _PROTECT_H_

#define    _PROTECT_H_


#define C_INFAN_ERRORRUN_TIMES 5 //带故障运行次数 lcx add 20240622
//===================================================================================================//
//选择A相输入端口
//---------------------------------------------------------------------------------------------------//
#define		PhaseASigValid						1//SWITCH1开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_phaseA							PortPin_Read(GPIOA, GPIO_Pin_0)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_PhaseA_Hi()						DEFINE_PA0_HI					//例子:DEFINE_P00_HI
#define		P_PhaseA_Low()						DEFINE_PA0_LOW					//例子:DEFINE_P00_LOW
#define		P_PhaseA_Output()					DEFINE_PA0_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_PhaseA_Input()					DEFINE_PA0_INPUT				//例子:DEFINE_P00_INPUT
#define		P_PhaseA_Enpull()					DEFINE_PA0_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_PhaseA_Dispull()					DEFINE_PA0_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//===================================================================================================//
//选择B相输入端口
//---------------------------------------------------------------------------------------------------//
#define		PhaseBSigValid						1//SWITCH1开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_phaseB							PortPin_Read(GPIOA, GPIO_Pin_1)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_PhaseB_Hi()						DEFINE_PA1_HI					//例子:DEFINE_P00_HI
#define		P_PhaseB_Low()						DEFINE_PA1_LOW					//例子:DEFINE_P00_LOW
#define		P_PhaseB_Output()					DEFINE_PA1_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_PhaseB_Input()					DEFINE_PA1_INPUT				//例子:DEFINE_P00_INPUT
#define		P_PhaseB_Enpull()					DEFINE_PA1_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_PhaseB_Dispull()					DEFINE_PA1_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//===================================================================================================//
//选择C相输入端口
//---------------------------------------------------------------------------------------------------//
#define		PhaseCSigValid						1//SWITCH1开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_phaseC							PortPin_Read(GPIOA, GPIO_Pin_2)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_PhaseC_Hi()						DEFINE_PA2_HI					//例子:DEFINE_P00_HI
#define		P_PhaseC_Low()						DEFINE_PA2_LOW					//例子:DEFINE_P00_LOW
#define		P_PhaseC_Output()					DEFINE_PA2_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_PhaseC_Input()					DEFINE_PA2_INPUT				//例子:DEFINE_P00_INPUT
#define		P_PhaseC_Enpull()					DEFINE_PA2_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_PhaseC_Dispull()					DEFINE_PA2_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//

//-----------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_PROSTATUS_NORMAL,
	ENUM_PROSTATUS_SLOWUP,
	ENUM_PROSTATUS_CONT,
	ENUM_PROSTATUS_SLOWDOWN,
	ENUM_PROSTATUS_FASTDOWN,
	ENUM_PROSTATUS_PROTECT,
}ENUM_PROSTATUS;

//-----------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_T4COLDZONE_INIT,
	ENUM_T4COLDZONE_COOL1,
	ENUM_T4COLDZONE_COOL2,
	ENUM_T4COLDZONE_COOL3,
	ENUM_T4COLDZONE_COOL4,
}ENUM_T4COLDZONE;

//-----------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_T4HEATZONE_INIT,
	ENUM_T4HEATZONE_HOT1,
	ENUM_T4HEATZONE_HOT2,
	ENUM_T4HEATZONE_HOT3,
	ENUM_T4HEATZONE_HOT4,
}ENUM_T4HEATZONE;

//-----------------------------------------------------------------------------------------------------//

typedef    struct
{
	U8    f_Enable    :1;		//保护总标志位
	U8    f_Tp		  :1;		//排气温度保护
	U8    f_T2Cold    :1;		//制冷T2温度防冻结保护
	U8    f_T3Cold    :1;		//制冷T3温度防过热保护
	U8    f_CurrCold  :1;		//制冷电流过大保护
	U8    f_CurrHeat  :1;		//制热电流过大保护
	U8    f_CompCurr  :1;		//压缩机电流过大保护
	U8    f_HumiT1Low :1;		//除湿模式T1过低保护
	
	U8    f_HighPress :1;		//高压保护
	U8    f_LowPress  :1;		//低压保护
	U8    f_T2Heat    :1;		//制热T2温度过高保护
	U8    f_PhaseA_bak:1;		//A相电平上次的值备份
	U8    f_PhaseB_bak:1;		//B相电平上次的值备份
	U8    f_PhaseC_bak:1;		//C相电平上次的值备份
	U8    f_WaterFlow :1;		//水流开关保护
	U8    Reserve	  :1;		//预留
	
	ENUM_PROSTATUS    TpStatus;			//排气保护阶段
	ENUM_PROSTATUS	  T2ColdStatus;		//制冷T2防冻结保护阶段
	ENUM_PROSTATUS	  T2HeatStatus;		//制热T2过热保护阶段
	ENUM_PROSTATUS	  T3ColdStatus;		//制冷T3过热保护阶段
	ENUM_T4COLDZONE   T4ColdZone;		//制冷T4温度区间
	ENUM_PROSTATUS	  CurrColdStatus;	//制冷电流过大保护阶段
	ENUM_T4HEATZONE	  T4HeatZone;		//制热电流过大保护阶段
	ENUM_PROSTATUS	  CurrHeatStatus;	//制热电流过大保护阶段
	ENUM_PROSTATUS	  CompCurrStatus;	//压缩机有效电流过大保护阶段
	ENUM_PROSTATUS	  PhaseSeqStatus;	//压缩机有效电流过大保护阶段
	ENUM_PROSTATUS	  SystemStatus;		//系统整体保护阶段
	
	U16   u16_TpCount;			//持续时间计时
	U16   u16_TpErrRemoveCount;	//持续时间计时
	U16   u16_T2ColdCount;		//持续时间计时
	U16   u16_T2HeatCount;		//持续时间计时
	U16   u16_T3ColdCount;		//持续时间计时
	U16   u16_HpCount;			//持续时间计时
	U16   u16_LpCount;			//持续时间计时
	U16   u16_CurCount;			//持续时间计时
	U16   u16_TpErrCnt;			//排气温度过高故障累计次数
	U16   u16_HpErrCnt;			//高压故障累计次数
	U16   u16_LpErrCnt;			//低压故障累计次数
	U16   u16_CurErrCnt;		//过流故障累计次数
	U16   u16_PhaseSeqErrCnt;	//错相故障累计次数
	U16   u16_TpErr_1HourCnt;	//排气故障首次触发后计时
	U16   u16_HpErr_1HourCnt;	//高压故障首次触发后计时
	U16   u16_LpErr_1HourCnt;	//低压故障首次触发后计时
	U16   u16_CurErr_1HourCnt;	//过流故障首次触发后计时
	U16   u16_CompHzLimitCount;  //限频频率计时
	U16   u16_PhaseABCnt;  		//AB相的计时
	U16   u16_PhaseBCCnt;  		//BC相的计时
	U16   u16_PhaseCACnt;  		//CA相的计时
	S16   s16_ErrCur;			//过流故障动作值
	U16   u16_WaterFlowCnt;  	//水流开关计时
}STRUCT_PROTECT;

//-----------------------------------------------------------------------------------------------------//

extern    STRUCT_PROTECT    Protect;

/****************************************************************************************************
Function Name       :void    Func_Protect(void)
Description         :保护功能处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Protect(void);
/****************************************************************************************************
Function Name       :void	InitPhaseSequence(void)
Description         :相序检测入口端口初始化
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    InitPhaseSequence(void);
/****************************************************************************************************
Function Name       :void	Protect_HighPressErr(void)
Description         :相位检测
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    PhaseSequenceCheck(void);

#endif
