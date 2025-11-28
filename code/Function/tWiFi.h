/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: EAHeater.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/18
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _WIFI_H_

#define    _WIFI_H_

//===================================================================================================//
//选择WIFI电源控制端口
//---------------------------------------------------------------------------------------------------//
#define		WiFiPowEn_SigValid						0//WiFiPowEn工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_WiFiPowEn							PortPin_Read(GPIOB, GPIO_Pin_2)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_WiFiPowEn_Hi()						DEFINE_PB2_HI					//例子:DEFINE_P00_HI
#define		P_WiFiPowEn_Low()						DEFINE_PB2_LOW					//例子:DEFINE_P00_LOW
#define		P_WiFiPowEn_Output()					DEFINE_PB2_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_WiFiPowEn_Input()						DEFINE_PB2_INPUT				//例子:DEFINE_P00_INPUT
#define		P_WiFiPowEn_Enpull()					DEFINE_PB2_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_WiFiPowEn_Dispull()					DEFINE_PB2_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (WiFiPowEn_SigValid == 1)
#define		P_WiFiPowEn_On()						P_WiFiPowEn_Hi()
#define		P_WiFiPowEn_Off()						P_WiFiPowEn_Low()
#else
#define		P_WiFiPowEn_On()						P_WiFiPowEn_Low()
#define		P_WiFiPowEn_Off()						P_WiFiPowEn_Hi()
#endif
//===================================================================================================//

//---------------------------------------------------------------------------------------------------//
//主机
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    VersionHighA;			//版本号高位A
	U8	  Byte;		
}UNION_WIFIMBYTE1;		    	//第1字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    VersionLowB;			//版本号低位B
	U8	  Byte;		
}UNION_WIFIMBYTE2;		    	//第2字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    Reserve0    	:1;		//bit0:预留
	U8    Reserve1    	:1;		//bit1:预留
	U8    OnOff		  	:1;		//bit2:开关机
	U8    TimerOff	  	:1;		//bit3:普通定时关机
	U8    TimerOn	  	:1;		//bit4:普通定时开机
	U8    Buzzer	  	:1;		//bit5:蜂鸣
	U8    NumDisp	  	:1;		//bit6:数显
	U8	  Economic	  	:1;		//bit7:经济
}STRUCT_WIFIMBYTE3;				//第3字节-结构体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE3    	MasterByte3;		//第3字节结构
	U8	  					Byte;		
}UNION_WIFIMBYTE3;		    					//第3字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_WIFIMMODESET_HEAT = 1,    //制热
	ENUM_WIFIMMODESET_HUMI = 2,    //除湿
	ENUM_WIFIMMODESET_COLD = 3,    //制冷
	ENUM_WIFIMMODESET_FAN  = 7,    //送风
	ENUM_WIFIMMODESET_INTE = 8,    //智能	
}ENUM_WIFIMMODESET;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_WIFIMMODESET    ModeSet    :4;	//设定模式
	U8					 Healthy    :1;	//健康
	U8					 DeMold	    :1;	//防霉
	U8					 Force	    :1;	//强力
	U8					 Reserve7   :1;	//预留
}STRUCT_WIFIMBYTE4;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE4    	MasterByte4;		//第4字节结构
	U8	  					Byte;		
}UNION_WIFIMBYTE4;		    					//第4字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_WIFITEMPSET_32C = 0,
	ENUM_WIFITEMPSET_31C = 1,
	ENUM_WIFITEMPSET_30C = 2,
	ENUM_WIFITEMPSET_29C = 3,
	ENUM_WIFITEMPSET_28C = 4,	
	ENUM_WIFITEMPSET_27C = 5,
	ENUM_WIFITEMPSET_26C = 6,
	ENUM_WIFITEMPSET_25C = 7,
	ENUM_WIFITEMPSET_24C = 8,	
	ENUM_WIFITEMPSET_23C = 9,
	ENUM_WIFITEMPSET_22C = 10,
	ENUM_WIFITEMPSET_21C = 11,
	ENUM_WIFITEMPSET_20C = 12,
	ENUM_WIFITEMPSET_19C = 13,
	ENUM_WIFITEMPSET_18C = 14,	
	ENUM_WIFITEMPSET_17C = 15,
	ENUM_WIFITEMPSET_16C = 16,
	ENUM_WIFITEMPSET_15C = 17,
	ENUM_WIFITEMPSET_14C = 18,	
	ENUM_WIFITEMPSET_13C = 19,	
}ENUM_WIFITEMPSET;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_WIFITEMPSET    TempSet    :5;		//设定温度
	U8					Reserve5   :1;		//预留	
	U8					Reserve6   :1;		//预留	
	U8					Reserve7   :1;		//预留		
}STRUCT_WIFIMBYTE5;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE5    	MasterByte5;		//第5字节结构
	U8	  					Byte;		
}UNION_WIFIMBYTE5;		    					//第5字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_WIFIWINDSPEED_AUTO = 0,		//自动
	ENUM_WIFIWINDSPEED_LOW  = 2,		//低速
	ENUM_WIFIWINDSPEED_MED  = 3,		//中速
	ENUM_WIFIWINDSPEED_HIGH = 5,		//高速
	ENUM_WIFIWINDSPEED_SILENCE = 6,		//静音
}ENUM_WIFIWINDSPEED;
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_WIFIUDSWEEP_DISABLE = 0,		//停止
	ENUM_WIFIUDSWEEP_ENABLE  = 7,		//摇摆
}ENUM_WIFIUDSWEEP;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_WIFIWINDSPEED    WindSpeed    :3;		//风速
	ENUM_WIFIUDSWEEP	  UDSweep	   :3;		//上下风摆
	U8					  Reserve6     :1;		//预留	
	U8					  Reserve7     :1;		//预留		
}STRUCT_WIFIMBYTE6;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE6    	MasterByte6;		//第6字节结构
	U8	  					Byte;		
}UNION_WIFIMBYTE6;		    					//第6字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    BothSweep    		  :1;		//立体送风
	U8	  TempCSetHalf        :1;		//摄氏显示设定温度0.5
	U8	  TempFSetAdd1		  :1;		//华氏显示设定温度加1
	U8	  LRSweep			  :1;		//左右风摆
	U8    TimerOnOffUpdate	  :1;		//普通定时开关设定标志
	U8	  Reserve5     		  :1;		//预留	
	U8	  Reserve6     		  :1;		//预留	
	U8    EAHeater			  :1;		//电加热
}STRUCT_WIFIMBYTE7;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE7    	MasterByte7;		//第7字节结构
	U8	  					Byte;		
}UNION_WIFIMBYTE7;								//第7字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_WIFISENSEWIND_OFF = 0,
	ENUM_WIFISENSEWIND_FINDP = 1,
	ENUM_WIFISENSEWIND_ANTIW = 2,
}ENUM_WIFISENSEWIND;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_WIFISENSEWIND    SenseWind		:2;		//人感送风选择
	U8					  Reserve2		:1;		//预留
	U8					  Reserve3		:1;		//预留
	U8					  Reserve4		:1;		//预留
	U8					  Reserve5		:1;		//预留	
	U8					  Reserve6		:1;		//预留		
	U8					  TempUnit		:1;		//温度单位 0:℃	1:℉
}STRUCT_WIFIMBYTE8;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE8    	MasterByte8;		//第8字节结构
	U8	  					Byte;		
}UNION_WIFIMBYTE8;								//第8字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    InfoAP    :1;    //AP提示
	U8    InfoSA    :1;    //SA提示
	U8    InfoPP    :1;    //PP提示
	U8    Config	:1;	   //配置
	U8    BussChk   :1;	   //商检
	U8    CommErr   :1;	   //串口通讯故障
	U8    OffLine   :1;	   //掉线
	U8    Reset	    :1;	   //复位
}STRUCT_WIFIMBYTE9;	
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE9    	MasterByte9;		//第9字节结构
	U8	  					Byte;		
}UNION_WIFIMBYTE9;								//第9字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TimerOffHour;			//定时关设定时间的小时值
	U8	  Byte;		
}UNION_WIFIMBYTE10;		    	//第10字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TimerOffMinute;		//定时关设定时间的分钟值
	U8	  Byte;		
}UNION_WIFIMBYTE11;		    	//第11字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TimerOnHour;			//定时开设定时间的小时值
	U8	  Byte;		
}UNION_WIFIMBYTE12;		    	//第12字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TimerOnMinute;		//定时开设定时间的分钟值
	U8	  Byte;		
}UNION_WIFIMBYTE13;		    	//第13字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    Reserve0		:1;		//预留
	U8    Reserve1		:1;		//预留
	U8	  Reserve2		:1;		//预留
	U8	  Reserve3		:1;		//预留
	U8	  Reserve4		:1;		//预留
	U8	  Reserve5		:1;		//预留	
	U8	  Reserve6		:1;		//预留		
	U8	  Reserve7		:1;		//预留	
}STRUCT_WIFIMBYTE14;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE14    MasterByte14;		//第14字节结构
	U8	  				  Byte;		
}UNION_WIFIMBYTE14;		    			    //第14字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_SLEEPMODE_NULL   = 0,	  //无睡眠
	ENUM_SLEEPMODE_NORMAL = 1,    //睡眠1(普通)
	ENUM_SLEEPMODE_OLDMAN = 2,    //睡眠2(老人)
	ENUM_SLEEPMODE_KID    = 3,    //睡眠3(小孩)
	ENUM_SLEEPMODE_DEFINE = 4,    //睡眠4(自定义)
}ENUM_SLEEPMODE;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEPMODE    SleepMode    :3;    //睡眠模式选择
	U8	  			  Reserve3	   :1;	  //预留
	U8	  			  Reserve4	   :1;	  //预留
	U8	  			  Reserve5	   :1;	  //预留	
	U8	  			  Reserve6	   :1;	  //预留		
	U8	  			  Reserve7	   :1;	  //预留	
}STRUCT_WIFIMBYTE15;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE15    MasterByte15;		//第15字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE15;		    			    //第15字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_SLEEP_TEMPSET_16C = 16,
	ENUM_SLEEP_TEMPSET_17C = 17,
	ENUM_SLEEP_TEMPSET_18C = 18,
	ENUM_SLEEP_TEMPSET_19C = 19,
	ENUM_SLEEP_TEMPSET_20C = 20,
	ENUM_SLEEP_TEMPSET_21C = 21,
	ENUM_SLEEP_TEMPSET_22C = 22,
	ENUM_SLEEP_TEMPSET_23C = 23,
	ENUM_SLEEP_TEMPSET_24C = 24,
	ENUM_SLEEP_TEMPSET_25C = 25,
	ENUM_SLEEP_TEMPSET_26C = 26,
	ENUM_SLEEP_TEMPSET_27C = 27,
	ENUM_SLEEP_TEMPSET_28C = 28,
	ENUM_SLEEP_TEMPSET_29C = 29,
	ENUM_SLEEP_TEMPSET_30C = 30,
	ENUM_SLEEP_TEMPSET_31C = 31,	
}ENUM_SLEEP_TEMPSET;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep01HTempSet    :5;	//第1个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE16;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE16    MasterByte16;		//第16字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE16;		    				//第16字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep02HTempSet    :5;	//第2个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE17;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE17    MasterByte17;		//第17字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE17;		    				//第17字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep03HTempSet    :5;	//第3个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE18;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE18    MasterByte18;		//第18字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE18;		    				//第18字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep04HTempSet    :5;	//第4个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE19;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE19    MasterByte19;		//第19字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE19;		    				//第19字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep05HTempSet    :5;	//第5个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE20;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE20    MasterByte20;		//第20字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE20;		    				//第20字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep06HTempSet    :5;	//第6个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE21;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE21    MasterByte21;		//第21字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE21;		    				//第21字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep07HTempSet    :5;	//第7个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE22;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE22    MasterByte22;		//第22字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE22;		    				//第22字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep08HTempSet    :5;	//第8个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE23;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE23    MasterByte23;		//第23字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE23;		    				//第23字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep09HTempSet    :5;	//第9个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE24;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE24    MasterByte24;		//第24字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE24;		    				//第24字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep10HTempSet    :5;	//第10个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFIMBYTE25;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE25    MasterByte25;		//第25字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE25;		    				//第25字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    RoomTempChk	      :1;	 //室内温度查看
	U8	  HuminityChk	      :1;	 //湿度查看
	U8	  CompRunTimeChk      :1;    //压缩机运行时间查看
	U8    FilterTimeChk       :1;	 //滤网时间查看
	U8    CompRunTimeClear    :1;    //压缩机时间清零
	U8    FilterTimeClear     :1;	 //滤网时间清零
	U8    Reserve6			  :1;	 //预留
	U8    Reserve7			  :1;	 //预留
}STRUCT_WIFIMBYTE26;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE26    MasterByte26;		//第26字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE26;		    				//第26字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    Comfort     :1;    //舒适
	U8    PumpFunc    :1;	 //水泵功能
	U8    Reserve2	  :1;	 //预留
	U8    Reserve3	  :1;	 //预留
	U8    Reserve4	  :1;	 //预留
	U8    Reserve5	  :1;	 //预留
	U8    Reserve6	  :1;	 //预留
	U8    Reserve7	  :1;	 //预留
}STRUCT_WIFIMBYTE27;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFIMBYTE27    MasterByte27;		//第27字节结构	
	U8	  				  Byte;		
}UNION_WIFIMBYTE27;		    				//第27字节-联合体
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//从机
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    VersionHighA;			//版本号高位A
	U8	  Byte;		
}UNION_WIFISBYTE1;		    	//第1字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    VersionLowB;			//版本号高位B
	U8	  Byte;		
}UNION_WIFISBYTE2;		    	//第2字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_WIFISMODESET_COLD 	   = 1,    //制冷
	ENUM_WIFISMODESET_FAN  	   = 2,    //送风
	ENUM_WIFISMODESET_HUM  	   = 3,    //除湿
	ENUM_WIFISMODESET_HEAT 	   = 4,    //制热
	ENUM_WIFISMODESET_SELSENSE = 5,    //自感
}ENUM_WIFISMODESET;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_WIFISMODESET    ModeSet     :4;    //设定模式
	U8					 OnOff		 :1;    //开关机
	U8					 NumDisp     :1;    //数显
	U8                   Economic    :1;    //经济
	U8					 Force		 :1;	//强力
}STRUCT_WIFISBYTE3;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE3    SlaveByte3;	//第3字节结构	
	U8                   Byte;
}UNION_WIFISBYTE3;						//第3字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_WIFITEMPSET      TempSet      :5;	  //设定温度
	ENUM_WIFIWINDSPEED    WindSpeed    :3;    //设定风速
}STRUCT_WIFISBYTE4;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE4    SlaveByte4;	//第4字节结构	
	U8					 Byte;			
}UNION_WIFISBYTE4;						//第4字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    TempFSetAdd1    :1;    //bit0:    华氏显示设定温度加1
	U8    TempCSetHalf    :1;    //bit1:    摄氏度显示设定温度0.5
	U8    Healthy		  :1;    //bit2:    健康
	U8    DeMold		  :1;    //bit3:    防霉
	U8    BothSweep    	  :1;	 //bit4:    立体送风
    U8    EAHeater        :1;    //bit5:    电加热
	U8    TimerOff        :1;    //bit6:    普通定时关机
	U8    TimerOn         :1;    //bit7:    普通定时开机
}STRUCT_WIFISBYTE5;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE5    SlaveByte5;	//第5字节结构	
	U8					 Byte;			
}UNION_WIFISBYTE5;						//第5字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_WIFISHSFAN_OFF = 0,          //关闭
	ENUM_WIFISHSFAN_HUMANWIND = 1,    //风随人
	ENUM_WIFISHSFAN_ANTIWIND  = 2,    //避风
}ENUM_WIFISHSFAN;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_WIFISHSFAN    HumanSenseFanSet    :2;    //人感送风选择
	U8                 Reserve2			   :1;    //预留
	U8				   HumiChk			   :1;    //湿度检测
	U8				   CleanChk			   :1;    //清洁度检测
	U8                 SweepLR			   :1;    //左右风摆
	U8				   SweepUD			   :1;	  //上下风摆
	U8				   TempUnit			   :1;	  //温度单位
}STRUCT_WIFISBYTE6;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE6    SlaveByte6;	//第6字节结构	
	U8					 Byte;			
}UNION_WIFISBYTE6;						//第6字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TimerOffHour;			//定时关设定时间的小时值
	U8	  Byte;		
}UNION_WIFISBYTE7;		    	//第7字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TimerOffMinute;		//定时关设定时间的分钟值
	U8	  Byte;		
}UNION_WIFISBYTE8;		    	//第8字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TimerOnHour;			//定时开设定时间的小时值
	U8	  Byte;		
}UNION_WIFISBYTE9;		    	//第9字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TimerOnMinute;		//定时开设定时间的分钟值
	U8	  Byte;		
}UNION_WIFISBYTE10;		    	//第10字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    InfoAP    :1;    //AP提示
	U8    InfoSA    :1;    //SA提示
	U8    InfoPP    :1;    //PP提示
	U8    Config	:1;	   //配置
	U8    BussChk   :1;	   //商检
	U8    CommErr   :1;	   //串口通讯故障
	U8    OffLine   :1;	   //掉线
	U8    Reset	    :1;	   //复位
}STRUCT_WIFISBYTE11;	
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE11    SlaveByte11;	//第11字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE11;						//第11字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    TopOutWindCommErr    :1;    //bit0: 顶出风和主板通信故障
	U8    DispCommErr		   :1;	  //bit1: 显示屏和主板通信故障
	U8    Reserve2			   :1;	  //bit2: 预留
	U8	  OutdoorCommErr	   :1;	  //bit3: 室内外通信故障
	U8	  EEPROMErr			   :1;	  //bit4: 内EEPROM故障
	U8	  IndoorFanErr		   :1;	  //bit5: 内风机故障
	U8	  T1Err				   :1;	  //bit6: 内环境温度传感器故障
	U8	  T2Err				   :1;	  //bit7: 内盘管传感器故障
}STRUCT_WIFISBYTE12;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE12    SlaveByte12;	//第12字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE12;						//第12字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    T1ValueMul10High;     //室内环境温度转换值高8位
	U8	  Byte;         	   
}UNION_WIFISBYTE13;				//第13字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    OutWindTempLow     :2;		//bit1-bit0: 室内出风温度转换值低2位
	U8	  T1ValueMul10Low    :2;		//bit3-bit2: 室内环境温度转换值低2位
	U8    T2ValueMul10Low	 :2;		//bit5-bit4: 室内盘管温度转换值低2位
	U8    HumiValueLow		 :2;		//bit7-bit6: 室内湿度转换值低2位
}STRUCT_WIFISBYTE14;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE14    SlaveByte14;	//第14字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE14;						//第14字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_TYPEKT_DPGUA  = 0,    //定频挂机
	ENUM_TYPEKT_BPGUA  = 1,	   //变频挂机
	ENUM_TYPEKT_DPGUI  = 2,	   //定频柜机
	ENUM_TYPEKT_BPGUI  = 3,	   //变频柜机
	ENUM_TYPEKT_DPYDKT = 4,    //定频移动空调
	ENUM_TYPEKT_BPYDKT = 5,    //变频移动空调
}ENUM_TYPEKT;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEPMODE    SleepMode    :3;    //bit2-bit0: 睡眠模式选择
	ENUM_TYPEKT		  Type		   :4;	  //bit6-bit3: 空调机型类别
	U8				  Ready		   :1;	  //bit7	   准备
}STRUCT_WIFISBYTE15;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE15    SlaveByte15;	//第15字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE15;						//第15字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep01HTempSet    :5;	//第1个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE16;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE16    SlaveByte16;	//第16字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE16;						//第16字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep02HTempSet    :5;	//第2个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE17;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE17    SlaveByte17;	//第17字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE17;						//第17字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep03HTempSet    :5;	//第3个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE18;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE18    SlaveByte18;	//第18字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE18;						//第18字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep04HTempSet    :5;	//第4个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE19;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE19    SlaveByte19;	//第19字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE19;						//第19字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep05HTempSet    :5;	//第5个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE20;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE20    SlaveByte20;	//第20字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE20;						//第20字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep06HTempSet    :5;	//第6个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE21;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE21    SlaveByte21;	//第21字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE21;						//第21字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep07HTempSet    :5;	//第7个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE22;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE22    SlaveByte22;	//第22字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE22;						//第22字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep08HTempSet    :5;	//第8个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE23;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE23    SlaveByte23;	//第23字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE23;						//第23字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep09HTempSet    :5;	//第9个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE24;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE24    SlaveByte24;	//第24字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE24;						//第24字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_SLEEP_TEMPSET    Sleep10HTempSet    :5;	//第10个小时的设定温度
	U8					  Reserve			 :1;	//预留
	U8					  TempFSetAdd1       :1;	//华氏显示设定温度加1
	U8					  TempCSetHalf		 :1;	//摄氏显示设定温度0.5
}STRUCT_WIFISBYTE25;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE25    SlaveByte25;	//第25字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE25;						//第25字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    T2ValueMul10High;     //室内盘管温度转换值高8位
	U8    Byte;         	   
}UNION_WIFISBYTE26;				//第26字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    OutWindTempHigh;      //室内出风温度转换值高8位
	U8	  Byte;				   
}UNION_WIFISBYTE27;				//第27字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    HumiValueHigh;		//室内湿度转换值高8位
	U8	  Byte;					
}UNION_WIFISBYTE28;				//第28字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_AIRQUALITY_PERFECT = 0,    //优
	ENUM_AIRQUALITY_GOOD    = 1,	//良
	ENUM_AIRQUALITY_NOTBAD  = 2,	//中
	ENUM_AIRQUALITY_BAD     = 3,    //差
	ENUM_AIRQUALITY_TOOBAD  = 4,	//很差
}ENUM_AIRQUALITY;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_AIRQUALITY    AirQuality    :3;    //空气质量等级(清洁度)
	U8                 Reserve3		 :1;	//预留
	U8                 Reserve4		 :1;	//预留
	U8                 Reserve5		 :1;	//预留
	U8                 Reserve6		 :1;	//预留
	U8                 Reserve7		 :1;	//预留
}STRUCT_WIFISBYTE29;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE29    SlaveByte29;	//第29字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE29;						//第29字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_CTFANLEVEL_OFF  = 0,    //抽头电机:停
	ENUM_CTFANLEVEL_LOW  = 1,    //抽头电机:低
	ENUM_CTFANLEVEL_MED  = 2,    //抽头电机:中
	ENUM_CTFANLEVEL_HIGH = 3,	 //抽头电机:高
}ENUM_CTFANLEVEL;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8                 IndoorFanSpeedDiv10;    //室内风机转速(除以10)
	ENUM_CTFANLEVEL    IndoorFanLevel;		   //抽头电机档位
	U8                 Byte;
}UNION_WIFISBYTE30;							   //第30字节-联合体							
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    T4ValueAdd20;    //室外温度值(实际温度值+20)
	U8    Byte;
}UNION_WIFISBYTE31;							   //第31字节-联合体	
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    T3ValueAdd20;    //室外盘管温度值(实际温度值+20)
	U8    Byte;
}UNION_WIFISBYTE32;							   //第32字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    TpValueAdd20;    					   //室外排气温度值(实际温度值+20)
	U8    Byte;
}UNION_WIFISBYTE33;							   //第33字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8                 OutdoorFanSpeedDiv10;    //室外风机转速(除以10)
	ENUM_CTFANLEVEL    OutdoorFanLevel;		    //抽头电机档位
	U8                 Byte;
}UNION_WIFISBYTE34;							    //第34字节-联合体							
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    CompRealFreq;    //压缩机运行频率
	U8    Byte;
}UNION_WIFISBYTE35;		   //第35字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_COMPLEVEL_OFF = 0,     //停机
	ENUM_COMPLEVEL_1   = 1,	    //1档
	ENUM_COMPLEVEL_2   = 2,	    //2档	
	ENUM_COMPLEVEL_3   = 3,	    //3档
	ENUM_COMPLEVEL_4   = 4,	    //4档		
	ENUM_COMPLEVEL_5   = 5,	    //5档
	ENUM_COMPLEVEL_6   = 6,	    //6档	
	ENUM_COMPLEVEL_7   = 7,	    //7档
	ENUM_COMPLEVEL_8   = 8,	    //8档	
	ENUM_COMPLEVEL_9   = 9,	    //9档
	ENUM_COMPLEVEL_10  = 10,	//10档	
	//以下预留
	ENUM_COMPLEVEL_11  = 11,	//11档
	ENUM_COMPLEVEL_12  = 12,	//12档		
	ENUM_COMPLEVEL_13  = 13,	//13档
	ENUM_COMPLEVEL_14  = 14,	//14档	
	ENUM_COMPLEVEL_15  = 15,    //15档	
}ENUM_COMPLEVEL;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_COMPLEVEL    CompLevel          :4;    //压缩机运行频率档
	U8				  Reserve4	         :1;	//预留
	U8				  Reserve5	         :1;	//预留
	U8				  FourwayOnoff       :1;	//四通阀
	U8				  ElMagValveOnoff    :1;	//电磁阀
}STRUCT_WIFISBYTE36;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE36    SlaveByte36;	//第36字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE36;						//第36字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
    U8    InOutdoorCommErr        :1;    //室内外通信故障
	U8    OutdoorMoudleCommErr    :1;	 //室外模块间通信故障
	U8    T3Err					  :1;    //室外盘管温度传感器故障
	U8    SystemErr				  :1;	 //系统故障(缺氟)
	U8    TypeConfigErr			  :1;	 //机型配置错误
	U8    T4Err					  :1;    //室外环境温度传感器故障
	U8    TpErr					  :1;    //室外排气温度传感器故障
	U8    IPMErr				  :1;    //室外IPM模块故障
}STRUCT_WIFISBYTE37;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE37    SlaveByte37;	//第37字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE37;						//第37字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    OutdoorFanErr    		  :1;    //室外直流风机故障
	U8    OutdoorCurrSensorErr    :1;    //室外电流传感器故障
	U8    OutdoorEEPROMErr		  :1;	 //室外EEPROM故障
	U8    CompTopErr			  :1;	 //室外压缩机壳顶故障
	U8    OutdoorVoltSensorErr    :1;	 //室外电压传感器故障
	U8    AspirationSensorErr	  :1;	 //室外吸气传感器故障
	U8    OutdoorVoltPro		  :1;    //室外电压过高过低保护
	U8    OutdoorCurrPro		  :1;    //室外电流保护
}STRUCT_WIFISBYTE38;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE38    SlaveByte38;	//第38字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE38;						//第38字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    TpHighPro        :1;    //室外排气温度过高保护
	U8    T2ColdPro	       :1;    //室内盘管制冷过冷保护
	U8    T3HeatPro        :1;    //室外盘管制冷过热保护
	U8    T2HeatPro	       :1;    //室内盘管制热过热保护
	U8    T4TempPro        :1;	  //室外环境温度过高过低保护
	U8    CompDrvPro       :1;    //室外压缩机驱动保护
	U8    IPMPro		   :1;    //室外IPM模块保护
	U8    OutdoorFanPro    :1;    //室外直流风机保护
}STRUCT_WIFISBYTE39;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE39    SlaveByte39;	//第39字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE39;						//第39字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    Reserve0      :1;    //预留
	U8	  Reserve1	    :1;	   //预留
	U8    T2Err		    :1;	   //室内盘管温度传感器故障
	U8	  T1Err		    :1;    //室内环境温度传感器故障
	U8    CompDrvErr    :1;    //室外压缩机驱动故障
	U8    Reserve5      :1;    //预留
	U8    PFCPro		:1;    //室外PFC保护
	U8    Reserve7		:1;    //预留
}STRUCT_WIFISBYTE40;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE40    SlaveByte40;	//第40字节结构	
	U8					  Byte;         
}UNION_WIFISBYTE40;						//第40字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    OutdoorVoltADValue;    //室外电压AD值
	U8    Byte;
}UNION_WIFISBYTE41;		   		 //第41字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    OutdoorCurrADValue;    //室外电流AD值
	U8    Byte;
}UNION_WIFISBYTE42;		   		 //第42字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    kWhMul100_L;			 //电量使用20bit的bit7-bit0
	U8    Byte;
}UNION_WIFISBYTE43;		   		 //第43字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    kWhMul100_M;			 //电量使用20bit的bit15-bit8
	U8    Byte;
}UNION_WIFISBYTE44;		   		 //第44字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    kWhMul100_M    :4;    //电量使用20bit的bit19-bit16
	U8	  FeeMul100_L    :4;	//电费使用20bit的bit3-bit0			 
}STRUCT_WIFISBYTE45;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE45    SlaveByte45;	//第45字节结构	
	U8    				  Byte;
}UNION_WIFISBYTE45;		   		 		//第45字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    FeeMul100_M;			 //电费使用20bit的bit11-bit4
	U8    Byte;
}UNION_WIFISBYTE46;		   		 //第46字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    FeeMul100_H;			 //电费使用20bit的bit19-bit12
	U8    Byte;
}UNION_WIFISBYTE47;		   		 //第47字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    kWh_L;			 	 //电量使用16bit的bit7-bit0
	U8    Byte;
}UNION_WIFISBYTE48;		   		 //第48字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    kWh_H;			 	 //电量使用16bit的bit15-bit8
	U8    Byte;
}UNION_WIFISBYTE49;		   		 //第49字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    Fee_L;			 	 //电费使用16bit的bit7-bit0
	U8    Byte;
}UNION_WIFISBYTE50;		   		 //第50字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    Fee_H;			 	 //电费使用16bit的bit15-bit8
	U8    Byte;
}UNION_WIFISBYTE51;		   		 //第51字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    FeeMul1000_L;			 //电费使用16bit的bit7-bit0
	U8    Byte;
}UNION_WIFISBYTE52;		   		 //第52字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    FeeMul1000_H;			 //电费使用16bit的bit15-bit8
	U8    Byte;
}UNION_WIFISBYTE53;		   		 //第53字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    Power_L;			 	 //功率使用16bit的bit7-bit0
	U8    Byte;
}UNION_WIFISBYTE54;		   		 //第54字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    Power_H;			 	 //功率使用16bit的bit15-bit8
	U8    Byte;
}UNION_WIFISBYTE55;		   		 //第55字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    CompFilterRunTime_L;    //压缩机或过滤器运行时间使用16bit的bit7-bit0
	U8    Byte;
}UNION_WIFISBYTE56;		   		  //第56字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	U8    CompFilterRunTime_H;	  //压缩机或过滤器运行时间使用16bit的bit15-bit8
	U8    Byte;
}UNION_WIFISBYTE57;		   		  //第57字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    WaterFullWarning      :1;    //水满报警
	U8    PumpWarning		    :1;    //水泵报警
	U8    FilterWarning		    :1;	   //过滤器报警
	U8	  WaterBoxErrWarning    :1;    //水箱放置错误报警
	U8    WaterBoxWatLess		:1;    //水箱缺水
	U8	  DefrostWarning		:1;	   //除霜报警
	U8	  Reserve6			    :1;	   //预留
	U8    Reserve7			 	:1;	   //预留
}STRUCT_WIFISBYTE58;	
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE58    SlaveByte58;	//第58字节结构	
	U8    				  Byte;
}UNION_WIFISBYTE58;		   		 		//第58字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    CompOnOff        :1;    //压缩机运行		0:停机		1:正在运行
	U8    OutdoorFanLow    :1;    //外风机 			0:高风		1:低风
	U8    PumpOnOff		   :1;	  //水泵			0:关闭		1:开启
	U8	  WPMotorOnOff	   :1;	  //打水电机		0:关闭		1:开启
	U8	  HeatEnable	   :1;	  //是否制热		0:无制热	1:有制热
	U8	  SleepEnable	   :1;	  //是否睡眠		0:无睡眠	1:有睡眠
	U8	  SweepEnable	   :1;	  //是否摇摆		0:无摇摆	1:有摇摆
	U8	  AutoEnable	   :1;	  //是否自动		0:无自动	1:有自动
}STRUCT_WIFISBYTE59;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE59    SlaveByte59;	//第59字节结构	
	U8    				  Byte;
}UNION_WIFISBYTE59;		   		 		//第59字节-联合体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_COMFORT_NULL  = 0,    //无舒适功能
	ENUM_COMFORT_ZONE1 = 1,	   //蓝色区域1
	ENUM_COMFORT_ZONE2 = 2,	   //绿色区域2	
	ENUM_COMFORT_ZONE3 = 3,	   //黄色区域3
}ENUM_COMFORT;
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_TIMECHKDISP_NULL   = 0,    //无查看
	ENUM_TIMECHKDISP_COMP   = 1,	//压缩机时间
	ENUM_TIMECHKDISP_FILTER = 2,	//过滤器时间
	ENUM_TIMECHKDISP_TIMER  = 3,	//定时时间
}ENUM_TIMECHKDISP;
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	ENUM_COMFORT        ComfortStatus    :3;	//舒适功能状态指示
	U8				    Reserve3		 :1;	//预留
	ENUM_TIMECHKDISP    TimeChkDisp      :2;    //计时显示	
	U8				    Reserve6		 :1;	//预留	
	U8				    Reserve7		 :1;	//预留		
}STRUCT_WIFISBYTE60;
//---------------------------------------------------------------------------------------------------//
typedef    union
{
	STRUCT_WIFISBYTE60    SlaveByte60;	//第60字节结构	
	U8    				  Byte;
}UNION_WIFISBYTE60;		   		 		//第60字节-联合体
//---------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//主机
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	UNION_WIFIMBYTE1     Byte1;
	UNION_WIFIMBYTE2     Byte2;	
	UNION_WIFIMBYTE3     Byte3;
	UNION_WIFIMBYTE4	 Byte4;
	UNION_WIFIMBYTE5	 Byte5;
	UNION_WIFIMBYTE6	 Byte6;
	UNION_WIFIMBYTE7	 Byte7;
	UNION_WIFIMBYTE8	 Byte8;
	UNION_WIFIMBYTE9	 Byte9;
	UNION_WIFIMBYTE10	 Byte10;	
	UNION_WIFIMBYTE11	 Byte11;	
	UNION_WIFIMBYTE12	 Byte12;	
	UNION_WIFIMBYTE13	 Byte13;	
	UNION_WIFIMBYTE14	 Byte14;
	UNION_WIFIMBYTE15	 Byte15;
	UNION_WIFIMBYTE16	 Byte16;
	UNION_WIFIMBYTE17	 Byte17;
	UNION_WIFIMBYTE18	 Byte18;	
	UNION_WIFIMBYTE19	 Byte19;	
	UNION_WIFIMBYTE20	 Byte20;	
	UNION_WIFIMBYTE21	 Byte21;
	UNION_WIFIMBYTE22	 Byte22;
	UNION_WIFIMBYTE23	 Byte23;
	UNION_WIFIMBYTE24	 Byte24;
	UNION_WIFIMBYTE25	 Byte25;	
	UNION_WIFIMBYTE26	 Byte26;	
	UNION_WIFIMBYTE27	 Byte27;		
}STRUCT_WIFIMASTER;
//---------------------------------------------------------------------------------------------------//
//从机
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	UNION_WIFISBYTE1     Byte1;
	UNION_WIFISBYTE2	 Byte2;
	UNION_WIFISBYTE3     Byte3;
	UNION_WIFISBYTE4	 Byte4;
	UNION_WIFISBYTE5	 Byte5;
	UNION_WIFISBYTE6	 Byte6;
	UNION_WIFISBYTE7	 Byte7;
	UNION_WIFISBYTE8	 Byte8;
	UNION_WIFISBYTE9	 Byte9;
	UNION_WIFISBYTE10    Byte10;
	UNION_WIFISBYTE11    Byte11;
	UNION_WIFISBYTE12    Byte12;
	UNION_WIFISBYTE13    Byte13;
	UNION_WIFISBYTE14	 Byte14;
	UNION_WIFISBYTE15	 Byte15;
	UNION_WIFISBYTE16	 Byte16;
	UNION_WIFISBYTE17	 Byte17;
	UNION_WIFISBYTE18	 Byte18;
	UNION_WIFISBYTE19	 Byte19;
	UNION_WIFISBYTE20    Byte20;
	UNION_WIFISBYTE21    Byte21;
	UNION_WIFISBYTE22    Byte22;
	UNION_WIFISBYTE23    Byte23;
	UNION_WIFISBYTE24	 Byte24;
	UNION_WIFISBYTE25	 Byte25;
	UNION_WIFISBYTE26	 Byte26;
	UNION_WIFISBYTE27	 Byte27;
	UNION_WIFISBYTE28	 Byte28;
	UNION_WIFISBYTE29	 Byte29;
	UNION_WIFISBYTE30	 Byte30;
	UNION_WIFISBYTE31	 Byte31;
	UNION_WIFISBYTE32	 Byte32;
	UNION_WIFISBYTE33	 Byte33;	
	UNION_WIFISBYTE34	 Byte34;
	UNION_WIFISBYTE35	 Byte35;
	UNION_WIFISBYTE36	 Byte36;
	UNION_WIFISBYTE37	 Byte37;
	UNION_WIFISBYTE38	 Byte38;
	UNION_WIFISBYTE39	 Byte39;
	UNION_WIFISBYTE40	 Byte40;
	UNION_WIFISBYTE41	 Byte41;
	UNION_WIFISBYTE42	 Byte42;	
	UNION_WIFISBYTE43	 Byte43;
	UNION_WIFISBYTE44	 Byte44;
	UNION_WIFISBYTE45	 Byte45;
	UNION_WIFISBYTE46	 Byte46;
	UNION_WIFISBYTE47	 Byte47;
	UNION_WIFISBYTE48	 Byte48;
	UNION_WIFISBYTE49	 Byte49;
	UNION_WIFISBYTE50	 Byte50;
	UNION_WIFISBYTE51	 Byte51;
	UNION_WIFISBYTE52	 Byte52;	
	UNION_WIFISBYTE53	 Byte53;
	UNION_WIFISBYTE54	 Byte54;
	UNION_WIFISBYTE55	 Byte55;
	UNION_WIFISBYTE56	 Byte56;
	UNION_WIFISBYTE57	 Byte57;
	UNION_WIFISBYTE58	 Byte58;
	UNION_WIFISBYTE59	 Byte59;	
	UNION_WIFISBYTE60	 Byte60;	
}STRUCT_WIFISLAVE;
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
	U8    f_OnOff       :1;    //当前开关; 		//BOOL型数据上报;
	U8    f_TempUnit    :1;    //当前温度单位	//BOOL型数据上报;
	U8	  f_Sweep		:1;	   //摇头摆风状态	//BOOL型数据上报;
	U8	  f_Sleep		:1;	   //当前睡眠状态	//BOOL型数据上报;
	U8    f_Force		:1;	   //当前强力状态	//BOOL型数据上报;
}STRUCT_API;
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	//备注:0智能；1制热；2除湿；3制冷；4送风
	ENUM_WSYSMODE_INTE,
	ENUM_WSYSMODE_HEAT,
	ENUM_WSYSMODE_HUMI,
	ENUM_WSYSMODE_COLD,
	ENUM_WSYSMODE_FAN,
}ENUM_WSYSMODE;
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	//备注:0自动，1低速，2中速，3高速，
	ENUM_WFANMODE_AUTO,    //自动风	
	ENUM_WFANMODE_LOW,     //低风	
	ENUM_WFANMODE_MED,     //中风
	ENUM_WFANMODE_HIGH,    //高风
}ENUM_WFANMODE;
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
	ENUM_TWIFISTATUS_NULL,
	ENUM_TWIFISTATUS_CONFIG,
	ENUM_TWIFISTATUS_PP,
	ENUM_TWIFISTATUS_SA,
	ENUM_TWIFISTATUS_AP,
}ENUM_TWIFISTATUS;
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
typedef    struct
{
    U8    f_AppOn    	:1;
	U8    f_DrvOn    	:1;
	U8    f_FuncOn   	:1;			  //功能开关
	U8    f_FuncOnBak   :1;			  //功能开关	
	U8    f_Reset	 	:1;
	U8    Reserve    	:3;
	
	STRUCT_WIFIMASTER   Master;
//	STRUCT_WIFIMASTER   MasterBak;
	STRUCT_WIFISLAVE    Slave;
	
	ENUM_TWIFISTATUS	Enum_Status;
	
	STRUCT_API          Api;
	STRUCT_API			ApiBak;
	U8                  u8_TimerOnOff;
	U8                  u8_TimerOnOffBak;
	ENUM_WSYSMODE		Enum_WSysMode;
	ENUM_WSYSMODE		Enum_WSysModeBak;
	U8					u8_TempCSet;
	U8					u8_TempCSetBak;
	U8					u8_TempFSet;
	U8					u8_TempFSetBak;	
	ENUM_WFANMODE		Enum_WFanMode;
	ENUM_WFANMODE		Enum_WFanModeBak;
	U16					u16_TimerOffMinute;
	U16					u16_TimerOffMinuteBak;
	U16					u16_TimerOnMinute;
	U16					u16_TimerOnMinuteBak;	
	U8					u8_Fault;
	U8					u8_FaultBak;
}STRUCT_WIFI;

extern    STRUCT_WIFI    WiFi;

/****************************************************************************************************
Function Name       :void    Init_WiFiPowEn(void)
Description         :WIFI电源控制初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_WiFiPowEn(void);
/****************************************************************************************************
Function Name       :void    Func_WiFiPowEn(void)
Description         :WIFI电源控制功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_WiFiPowEn(void);
/****************************************************************************************************
Function Name       :void Uart_PutChar(unsigned char dat)
Description         :涂鸦是阻塞式发送，队列式中断接收
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Uart_PutChar(unsigned char dat);
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
/****************************************************************************************************
Function Name       :void App_UartAPI(void)
Description         :底板上报信息
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    App_UartAPI(void);
/****************************************************************************************************
Function Name       :void	App_uartapi_onoff(unsigned char power)
Description         :底板接收模组开关机信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_onoff(unsigned char power);
/****************************************************************************************************
Function Name       :void	App_uartapi_onoff(unsigned char timeronoff)
Description         :底板接收模组定时关/开信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_timeronoff(unsigned char timeronoff);
/****************************************************************************************************
Function Name       :void	App_uartapi_wsysmode(unsigned char wsysmode)
Description         :底板接收模组定时关/开信息处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_wsysmode(unsigned char wsysmode);
/****************************************************************************************************
Function Name       :void	App_uartapi_tempcset(unsigned char tempcset)
Description         :底板接收模组当前温度设定值-℃
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_tempcset(unsigned char tempcset);
/****************************************************************************************************
Function Name       :void	App_uartapi_fanmode(unsigned char fanmode)
Description         :底板接收模组当前风速模式
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_fanmode(unsigned char fanmode);
/****************************************************************************************************
Function Name       :void	App_uartapi_tempunit(unsigned char tempunit)
Description         :底板接收模组温度单位
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_tempunit(unsigned char tempunit);
/****************************************************************************************************
Function Name       :void	App_uartapi_timeroff(unsigned long timeroff)
Description         :底板接收模组定时关剩余分钟
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_timeroff(unsigned long timeroff);
/****************************************************************************************************
Function Name       :void	App_uartapi_timeron(unsigned long timeron)
Description         :底板接收模组定时开剩余分钟
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_timeron(unsigned long timeron);
/****************************************************************************************************
Function Name       :void	App_uartapi_sweep(unsigned char sweep)
Description         :底板接收模组摇头摆风状态
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_sweep(unsigned char sweep);
/****************************************************************************************************
Function Name       :void	App_uartapi_sleep(unsigned char sleep)
Description         :底板接收模组睡眠状态
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_sleep(unsigned char sleep);
/****************************************************************************************************
Function Name       :void	App_uartapi_tempfset(unsigned char tempfset)
Description         :底板接收模组当前温度设定值-℉
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_tempfset(unsigned char tempfset);
/****************************************************************************************************
Function Name       :void	App_uartapi_force(unsigned char force)
Description         :底板接收模组当前强力标志
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_uartapi_force(unsigned char force);

/****************************************************************************************************
Function Name       :void	App_TCLModule_Slave_Info(void)
Description         :TCL协议底板发数据给模组
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_TCLModule_Slave_Info(void);
/****************************************************************************************************
Function Name       :void	App_TCLModule_Master_Info(void)
Description         :TCL协议模组发数据给底板
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_TCLModule_Master_Info(void);
/****************************************************************************************************
Function Name       :U8	App_TCLModule_CtoF(U8 tempcset, U8 Fadd1)
Description         :TCL协议模组温度摄氏度转换华氏度
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8	App_TCLModule_CtoF(U8 tempcset, U8 Fadd1);
/****************************************************************************************************
Function Name       :U8	App_TCLModule_Fadd1(U8 tempfset)
Description         :TCL协议模组温度当前华氏度是否需要加1
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8	App_TCLModule_Fadd1(U8 tempfset);

#endif
