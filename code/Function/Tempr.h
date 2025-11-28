/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Tempr.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _TEMPR_H_

#define    _TEMPR_H_


//--------------------------------------------------------------------------------------------------//
//温度相关参数宏定义
#define    C_TEMP_ROOM_VALUEMIN        -25        //室内温度检测温度最小值
#define    C_TEMP_ROOM_VALUEMAX        70         //室内温度检测温度最大值
#define    C_TEMP_COIL_VALUEMIN        -30        //盘管温度检测温度最小值
#define    C_TEMP_COIL_VALUEMAX        80         //盘管温度检测温度最大值
//--------------------------------------------------------------------------------------------------//

typedef    struct
{
	U8    f_Error			:1;		  //传感器故障
	U16   u16_ErrCount;  		  	  //故障计时
	S8	  s8_ValueRead;		  		  //传感器获知的值
	U8    u8_ValueDotRead;	  		  //传感器获知的值小数部分
	S8	  s8_Value;			  		  //有效范围处理温度值(整数部分)
	S16   s16_ValueMul10;	  		  //温度值带小数点(放大10倍)-(判断区间用)
	S16	  s16_ValueMul10bc;		 	  //修正值(温控算法用)			  
}STRUCT_TEMPRATURE;

//--------------------------------------------------------------------------------------------------//

extern    STRUCT_TEMPRATURE    T1;          //T1-室内温度
extern    STRUCT_TEMPRATURE    T2;          //T2-室内盘管温度
extern    STRUCT_TEMPRATURE    T3;        	//T3-室外盘管温度
extern    STRUCT_TEMPRATURE    T4;		   	//T4-室外温度
extern    STRUCT_TEMPRATURE    Tp;		   	//排气温度
extern    STRUCT_TEMPRATURE    Cur;		   	//排气温度
extern	  STRUCT_TEMPRATURE    TH;		  	//TH-回气温度
extern    STRUCT_TEMPRATURE    T5;		 	//T5-水箱温度
extern    STRUCT_TEMPRATURE    T5I;		  	//T5-进水温度
extern    STRUCT_TEMPRATURE    T5O;		  	//T5-出水温度

//--------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_TEMPDELTAZONE_INIT,        //初始值-不明确区间
	ENUM_TEMPDELTAZONE_A,
	ENUM_TEMPDELTAZONE_B,
	ENUM_TEMPDELTAZONE_C,
	ENUM_TEMPDELTAZONE_D,
	ENUM_TEMPDELTAZONE_E,
	ENUM_TEMPDELTAZONE_F,
	ENUM_TEMPDELTAZONE_G,
	ENUM_TEMPDELTAZONE_H,
	ENUM_TEMPDELTAZONE_I,
	ENUM_TEMPDELTAZONE_J,
	ENUM_TEMPDELTAZONE_K,
}ENUM_TEMPDELTAZONE;

//--------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_TEMPT4COOLZONE_INIT,        //初始值-不明确区间
	ENUM_TEMPT4COOLZONE_PRO,		 //温度过高
	ENUM_TEMPT4COOLZONE_11,
	ENUM_TEMPT4COOLZONE_10,
	ENUM_TEMPT4COOLZONE_9,
	ENUM_TEMPT4COOLZONE_8,
	ENUM_TEMPT4COOLZONE_7,
	ENUM_TEMPT4COOLZONE_6,
	ENUM_TEMPT4COOLZONE_5,
	ENUM_TEMPT4COOLZONE_4,
	ENUM_TEMPT4COOLZONE_3,
	ENUM_TEMPT4COOLZONE_2,
	ENUM_TEMPT4COOLZONE_1,
	ENUM_TEMPT4COOLZONE_0,
	ENUM_TEMPT4COOLZONE_STOP,
	ENUM_TEMPT4COOLZONE_PRO1,		//温度过低
}ENUM_TEMPT4COOLZONE;

//--------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_TEMPT4HEATZONE_INIT,        //初始值-不明确区间
	ENUM_TEMPT4HEATZONE_PRO,
	ENUM_TEMPT4HEATZONE_13,
	ENUM_TEMPT4HEATZONE_12,
	ENUM_TEMPT4HEATZONE_11,
	ENUM_TEMPT4HEATZONE_10,
	ENUM_TEMPT4HEATZONE_9,
	ENUM_TEMPT4HEATZONE_8,
	ENUM_TEMPT4HEATZONE_7,
	ENUM_TEMPT4HEATZONE_6,
	ENUM_TEMPT4HEATZONE_5,
	ENUM_TEMPT4HEATZONE_4,
	ENUM_TEMPT4HEATZONE_3,
	ENUM_TEMPT4HEATZONE_2,
	ENUM_TEMPT4HEATZONE_1,
	ENUM_TEMPT4HEATZONE_0,
	ENUM_TEMPT4HEATZONE_PRO1,
}ENUM_TEMPT4HEATZONE;
#define C_TEMPT4HEAT_PRO1  60 //规格书要求6度（60）。图表上-26度（-260） //lcx add
//--------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_TEMPT2HEATZONE_INIT,
	ENUM_TEMPT2HEATZONE_PRO,		//保护
	ENUM_TEMPT2HEATZONE_FASTDOWN,	//快速限频
	ENUM_TEMPT2HEATZONE_SLOWDOWN,	//慢速限频
	ENUM_TEMPT2HEATZONE_CON,		//频率保持
	ENUM_TEMPT2HEATZONE_SLOWUP,		//频率慢升
	ENUM_TEMPT2HEATZONE_OK,			//正常控制
}ENUM_TEMPT2HEATZONE;

//--------------------------------------------------------------------------------------------------//

typedef    struct
{
    U8    f_TempUnit    :1; //温控单位 0:℃	1:℉
	U8    f_TempUnitBak :1;
	U8    Reserve       :6; //预留
	U8    u8_TempCSet;		//温控-设定值		-单位1℃
    U8    u8_TempFSet;		//温控-设定值		-单位1℉
    U8    u8_ColdCSet;		//制冷模式-设定值	-单位1℃
	U8    u8_ColdFSet;		//制冷模式-设定值	-单位1℉
	U8    u8_HeatCSet;		//制热模式-设定值	-单位1℃
	U8    u8_HeatFSet;		//制热模式-设定值	-单位1℉		
	U8    u8_HumiCSet;		//除湿模式-设定值	-单位1℃
	U8    u8_TempSense;		//随身感温度
	U8	  u8_TempCSetSleep;			//记录进入睡眠模式时设定温度 -单位1℃
	U8	  u8_TempFSetSleep;			//记录进入睡眠模式时设定温度 -单位1℉		
	
	ENUM_TEMPDELTAZONE    T1TSDeltaZone;		//温差等级
	ENUM_TEMPDELTAZONE    T1TSDeltaZoneBak;		//温差等级备份
	S16    u16_ZoneKT1Mul10;					//到达K区间时T1温度(10倍)
	U16    u16_T1TSDeltaCount;					//温差区间维持时间计时
	U16    u16_RoughEnCount;					//是否进入粗略调节计时
	U16    u16_RoughCount;						//粗略调节时间计时
	U16    u16_T2ProCount;						//T2过热保护计时
	
	ENUM_TEMPT4COOLZONE   T4CoolZone;			//制冷T4限频温区
	ENUM_TEMPT4HEATZONE   T4HeatZone;			//制热T4限频温区
	ENUM_TEMPT2HEATZONE	  T2HeatZone;			//制热T2限频温区
	

}STRUCT_TEMPR;
extern    STRUCT_TEMPR    Tempr;	//温控变量

/****************************************************************************************************
Function Name       :S16    TempValueMul10(S16 TempValue)
Description         :温度值乘以10倍
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
S16    TempValueMul10(S16 TempValue);
/****************************************************************************************************
Function Name       :void	Func_Temprature(void)
Description         :温度处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_Temprature(void);

#endif
