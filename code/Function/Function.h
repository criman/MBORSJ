/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Function.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/03/06
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _FUNCTION_H_

#define    _FUNCTION_H_ 


//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//引用标准化模块头文件
// 为兼容 PC 上的 gcc 单元测试，显式给出相对路径；在 Keil 下仍可正常使用
#if defined(__GNUC__)
#include    "../Module/Module_EEP24C02_V1.0.0/EEP24C02.h"
#include    "../Module/Module_Ad_ES8H018X_V1.0.0/Ad.h"
#include    "../Module/Module_Switch_V1.0.0/Switch.h"
#include    "../Module/Module_Stepmotor_V1.0.0/Stepmotor.h"
#include    "../Module/Module32_Uart_V1.0.0/Uart.h"
#include    "../Module/Module_Modbus_V1.0.0/modbus.h"
#else
//引用标准化模块头文件（Keil 工程使用相对简单的模块包含）
#include    "EEP24C02.h"
#include    "Ad.h"
#include    "Switch.h"
#include    "Stepmotor.h"
#include    "Uart.h"
#include    "modbus.h"
#endif

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//引用功能相关头文件
#include    "Remember.h"
#include    "Protect.h"
#include    "Defrost.h"
#include    "CommMotDrv.h"
#include    "CommDisp.h"
#include    "CmdIn.h"
#include    "CmdOut.h"
#include    "Comp.h"
#include    "Fan.h"
#include    "Timer.h"
#include    "Tempr.h"
#include    "WaterBox.h"
#include    "FourWay.h"
#include    "WPMotor.h"
#include    "UVC.h"
#include    "ExpValve.h"
#include    "LowPower.h"
#include    "EAHeater.h"
#include    "DCFan.h"
#include    "SyncFan.h"
#include    "SV.h"
#include    "WaterFeedValve.h"
#include    "CirculationPump.h"
#include    "Crank.h"
#include    "tWiFi.h"
#include    "ByPassValve.h"

//#include    "wifi.h"

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//功能相关参数宏定义
#define     C_FUNC_SOFT_VERSION_A        1        //版本号(大)-A
#define     C_FUNC_SOFT_VERSION_B        0        //版本号(小)-B

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

typedef    enum
{
    ENUM_STATUS_INIT,                   //上电初始化
    ENUM_STATUS_OFF,                    //待机
    ENUM_STATUS_ON,                     //工作
    ENUM_STATUS_BUSSCHK,				//商检
	ENUM_STATUS_SELCHK,                 //自检
}ENUM_STATUS;                           //系统状态机

//--------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_SYSMODE_COLD,       //制冷
	ENUM_SYSMODE_HUM,	     //除湿
	ENUM_SYSMODE_FAN,        //送风
	ENUM_SYSMODE_INTE,       //智能
	ENUM_SYSMODE_HEAT,       //制热

}ENUM_SYSMODE;

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
typedef    struct
{
    U8    f_Lock    	      :1;		//童锁
	U8    f_Sense   	      :1;		//随身感
	U8    f_VoltLowPro        :1;		//电压过低保护
	U8    f_CurrentProtect    :1;		//过电流保护
	U8	  f_InOutCommErr	  :1;		//室内外通信故障
	U8    f_OutEEpromErr	  :1;		//室外E方故障
	U8    f_InEEpromErr	  	  :1;		//室内E方故障
	U8    f_T4Limit   	      :1;		//T4限频作用下限频标志
    U8    f_T4LimitOff		  :1;		//T4限频引起停机标志
	U8    f_HumiCSetInitOK	  :1;		//除湿设定值初始化完成标志 //lcx add 20240705
#if defined(__GNUC__)
	U32	  Reserve     		  :22;		//预留（PC gcc 环境下使用 32 位基类型以满足 22bit 位宽）
#else
	U8	  Reserve     		  :22;		//预留（Keil 环境下原有定义）
#endif
	
	ENUM_STATUS     Enum_Status;        //系统状态机
	ENUM_SYSMODE    Mode;				//系统模式
    ENUM_SYSMODE    ModeBak;			//系统模式备份
	
	U8    u8_PowerOn_Count;				//上电计时
	U16   u16_OffCount;					//待机计时
	U16   u16_BussChkCount;				//商检经历计时
	U32   u32_ForceRunCount;			//强力运行时间计时
	U32   u32_SleepCount;				//睡眠持续计时
	U32   u32_SleepTimCount;			//睡眠最长时间(定时时间)计时
//	U16   u16_SenseCount;				//随身感功能连续25分钟没有收到修订值自动退出
	U16	  u16_ACVoltValue;				//系统电压
	U16   u16_DCVoltValue;				//直流电压
	U8    u8_OutDoorCurrentMul8;		//系统室外机电流值(*8)
	U8	  u8_InteFdCount[6];			//智能模式下温度区间功能需求切换防抖计时	
	
}STRUCT_SYSTEM;
extern    STRUCT_SYSTEM        System; //系统相关变量 

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

typedef    struct
{
    U8    f_Cold       	   :1;		//制冷状态		0:退出  1：进入
	U8    f_Heat       	   :1;		//制热状态		0:退出  1：进入
    U8    f_ColdBak        :1;		//制冷状态		0:退出  1：进入
	U8    f_HeatBak        :1;		//制热状态		0:退出  1：进入	
	U8    f_Fan			   :1;		//送风状态      0:无风  1：送风
	U8    f_FanBak		   :1;		//送风状态      0:无风  1：送风
	U8    f_Auto           :1;		//自动状态      0:退出  1: 进入
	U8    f_Sleep	   	   :1;		//睡眠状态		0:退出  1：进入
	U8    f_Force	   	   :1;		//强力状态      0:退出  1：进入
	U8    f_ConTemp    	   :1;		//恒温状态		0:退出  1：进入
	U8    f_RoughCon   	   :1;		//粗略控制      0:精细  1：粗略
	U8    f_TempCEC	   	   :1;		//CEC达温       0:无    1：达温
	U8    f_CECSync		   :1;		//CEC达温       0:退出	1：达温风机循环启停同步显示档位
	U8    f_T2HeatLimit    :1;		//制热T2限频    0:退出  1：进入
	U8    f_AntiDew		   :1;		//防凝露        0:无效  1：生效
	U8	  f_AntiDewMark	   :1;		//防凝露		0:未曾	1：已进入不能再重复进入
	U8    f_PerTest		   :1;		//能力测试		0:退出  1: 进入
	U8    f_Error		   :1;		//故障

}
STRUCT_SYSTEMMODE;

extern    STRUCT_SYSTEMMODE    SystemMode;

//typedef    struct
//{
//	//设置代码					参数名称							调整范围			初始值
//	uint16_t s16L2;		//	压机启动与设定温度回差设置 					2℃～18℃			6℃
//	uint16_t u16L3;		//	制热设定温度							20℃～参数F1		45℃
//	uint16_t u16L4;		//	制冷设定温度							7℃～50℃			20℃
//	uint16_t u16L5;		//	允许电热开启环境温度						0℃～35℃			5℃
//	uint16_t u16L6;		//	回水设定温度							20℃～50℃			42℃
//	uint16_t u16L7;		//	回水设定温度回差						2℃～15℃			3℃
//	uint16_t u16L8;		//	允许补水温度							20℃～80℃			65℃
//	uint16_t u16L9;		//	太阳能补水温度（预留）						50℃～75℃			60℃
//	uint16_t u16L10;	// 	压缩机电流 							0～40A 			20（0为不检测）
//}STRUCT_USERPARA;
//extern    STRUCT_USERPARA        UserPara; //用户参数 


//typedef    struct
//{
//	//参数号				参数名称（定义）					设定范围			默认值			备注
//	uint16_t u16H2;		//低温停机保护设定温 				-30℃～0℃			-10℃	
//	uint16_t u16H3;		//除霜周期设定					20min～90min		55min	
//	uint16_t u16H4;		//除霜进入盘管温度设定				-15℃～-1℃		-3℃	
//	uint16_t u16H5;		//最长除霜时间设定					5min～20min		12min	
//	uint16_t u16H6;		//除霜退出温设定					1℃～40℃			25℃	
//	uint16_t u16H7;		//进入除霜环境与盘管温度差				0℃～15℃			0℃	
//	uint16_t u16H8;		//可进入除霜环境温度 				0～20℃			10℃	
//	uint16_t u16P1;		//电子膨胀阀动作周期设定				20s～90s			30s 
//	int16_t  s16P2;		//目标过热度设定					-5℃～10℃			1℃	
//	int16_t  s16P3;		//膨胀阀调节时允许排气温度				60℃～115℃		88℃			显示为70℃～125℃
//	uint16_t u16P4;		//除霜电子膨胀阀开度设定				2～45			45			步数为显示值*10
//	uint16_t u16P5;		//电子膨胀阀最小开度设定				5～20			10			步数为显示值*10
//	uint16_t u16P6;		//电子膨胀阀手动自动选择				0/1 			1			0：手动/1：自动
//	uint16_t u16P7;		//电子膨胀阀手动步数 				2～50			40	
//	uint16_t u16F1;		//水箱设定温上限					20℃～60℃			48℃	
//	uint16_t u16F2;		//电加热时，循环泵选择				0/1 			0			0：不用，1：用
//	uint16_t u16F3;		//水箱温度与显示温度偏差设定 -5℃～15℃						1℃	
//	uint16_t u16F4;		//水流开关安装选择（预留）				0～1				0	
//	uint16_t u16F5;		//水泵模式选择（泳池机有效） 0/1 						1			0：恒温停机开水泵，1：恒温停机不开水泵
//	uint16_t u16F6;		//制冷水箱设定温下限 				7-15℃ 			7℃	
//	uint16_t u16F7;		//预留（仅四系统有效）
//	uint16_t u16F8;		//限时锁机时间					0～99			0			显示数以“周”为计时单位。“0”为没限时功能。（设备生产商可设定）
//	uint16_t u16F9;		//预留（仅四系统有效）			
//	uint16_t u16F10;	//预留（仅四系统有效）			
//	uint16_t u16F11;	//预留（仅四系统有效）			
//}STRUCT_FTYPARA;
typedef    struct
{
	//参数号				参数名称（定义）					设定范围			默认值			备注
	uint16_t	u16P1;	//	压缩机启动后最小运行时间	|	3-6min	|	6min	|	
	uint16_t	u16P2;	//	风机运行后延时开启压缩机的时间	|	10-20s	|	15s |	
	uint16_t	u16P3;	//	压缩机关闭后延时关闭风机的时间	|	10-20s	|	15s |	
	uint16_t	u16P4;	//	水泵启动后延时开启风机的时间	|	30-60s	|	40s |	
	uint16_t	u16P5;	//	风机关闭后延时关闭循环水泵的时间	|	10-20s	|	15s |	
	uint16_t	u16P6;	//	水泵启动后开始检测水流开关的时间	|	10-30s	|	20s |	
	uint16_t	u16P7;	//	水流开关信号断开持续时间	|	10-20s	|	15s |	
	uint16_t	u16P8;	//	循环水泵防生锈卡死的运行时间	|	3-8min	|	5min	|	
	uint16_t	u16P9;	//	定时补水延时开启补水阀时间 |	1-5min	|	3min	|	
	uint16_t	u16P10;	//	自动补水延时开启补水阀时间 |	0-2min	|	1min	|	
	uint16_t	u16P11;	//	自动补水延时关闭补水阀时间 |	1-5min	|	3min	|	
	uint16_t	u16P12;	//	手动开启或者手动关闭补水的按键时间 |	5-10s	|	5s	|	
	uint16_t 	u16P13;	//	压缩机停机时电子膨胀阀开度 |	100-300P	|	160P	|	
	uint16_t	u16P14;	//	电子膨胀阀动作周期 |	20～60s	|	30s |	
	int16_t 	s16P15;	//	目标过热度补偿设定 |	0～20℃	|	5℃	|	
	int16_t 	s16P16;	//	膨胀阀调节时允许排气温度	|	60～115℃ |	100℃	|	
	int16_t 	s16P17;	//	旁通阀开启条件之一的环境温度值	|	48-52℃	|	50℃	|	
	int16_t 	s16P18;	//	旁通阀开启条件之二的水箱温度值	|	43-47℃	|	45℃	|	
	int16_t 	s16P19;	//	旁通阀开启条件之三的排气温度值	|	90-100℃	|	90℃95℃?	|	
	int16_t 	s16P20;	//	旁通阀开启条件之四的排气温度值	|	100-110℃	|	105℃103℃?	|	
	int16_t 	s16P21;	//	旁通阀关闭条件之一的排气温度值	|	80-90℃?	|	70℃85℃?	|	
	int16_t 	s16P22;	//	旁通阀关闭条件之二的水箱温度值	|	30-40℃	|	30℃	|	
	uint16_t	u16P23;	//	压缩机启动后屏蔽低压保护的时间	|	4-6min	|	5min	|	
	int16_t 	s16P24;	//	排气温度过高保护的限定值	|	105-120℃	|	110℃	|	
	int16_t 	s16P25;	//	排气温度过高保护的退出值	|	75-95℃	|	85℃	|	
	int16_t 	s16P26;	//	防冻保护条件之一的环境温度值	|	2-5℃	|	3℃	|	
	int16_t 	s16P27;	//	防冻保护条件之二的水箱温度值	|	5-10℃ |	7℃	|	
	uint16_t	u16P28;	//	防冻保护条件之三的时间持续值	|	20-60s	|	30s |	
	uint16_t	u16P29;	//	定时补水期间补水阀持续补水时长	|	10-240min	|	60min	|	
	uint16_t	u16F1;	//	制冷水箱设定温度下限值	|	5-20℃ |	15℃	|	
	uint16_t	u16F2;	//	制冷水箱设定温度上限值	|	30-40℃	|	35℃	|	
	uint16_t	u16F3;	//	水流开关安装配置选择	|	0～1	|	0	|	0无（屏蔽）/1有
	int16_t 	s16F4;	//	水箱感温包温度补偿值	|	-5-10℃	|	0℃	|	根据15米长度测定
	uint16_t	u16L1;	//	水泵连续停机时间	|	12~36H	|	24	|默认值24H，步长1H
	uint16_t 	u16L2;	//	启动温差	|	2~10℃	|	5℃	|	默认5℃，步长1℃
}STRUCT_FTYPARA;

extern    STRUCT_FTYPARA        FtyPara; //工程参数 

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

/****************************************************************************************************
Function Name       :void App_Event_10ms(void)
Description         :10ms运行一次函数
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Event_10ms(void);
/****************************************************************************************************
Function Name       :void App_Event_100ms(void)
Description         :100ms运行一次函数
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Event_100ms(void);
/****************************************************************************************************
Function Name       :void App_Function(void)
Description         :功能函数
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void 	App_Function(void);

#endif
