/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: WiFi.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/18
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_WIFI    WiFi;         //WiFi

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
void    Init_WiFiPowEn(void)
{
    P_WiFiPowEn_Off();  
    P_WiFiPowEn_Output();	
	P_WiFiPowEn_Dispull();	
}
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
void    Func_WiFiPowEn(void)
{
	if (WiFi.f_FuncOn)	WiFi.f_AppOn = ON;
	else				WiFi.f_AppOn = OFF;
	
	
	WiFi.f_DrvOn = WiFi.f_AppOn;
	
	if (WiFi.f_DrvOn)		
	{
		P_WiFiPowEn_On();
	}
	else					
	{	
		P_WiFiPowEn_Off();
		
		//wifi断电通信异常变量全清0
#if defined		UART2_ENABLE
		Uart2.u16_AbnormalCount = 0;				 //收到完整数据，清零通讯超时计数
		Uart2.u16_ErrCount = 0; 

		F_uart2_TimeOut = CF_DISABLE;                //通讯正常
		F_uart2_CommErr = CF_DISABLE;
#endif 		 		

		WiFi.Enum_Status = ENUM_TWIFISTATUS_NULL;		
	}
}
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
void	Uart_PutChar(unsigned char dat)
{
#if defined		UART2_ENABLE	
	U8_Uart2_TxBuf[Uart2.u8_TxNum] = dat;
	Uart2.u8_TxNum++;
	if (Uart2.Enum_TxState == ENUM_TXSTATE_IDLE)	F_uart2_TxReady = CF_ENABLE;
#endif
}
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
#if 0
/****************************************************************************************************
Function Name       :void App_McuAPI_Update(void)
Description         :底板信息有更新时上报
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_McuAPI_Update(void)
{
	//开关机信息有更新
	if (WiFi.ApiBak.f_OnOff != WiFi.Api.f_OnOff)									
	{		
		WiFi.ApiBak.f_OnOff = WiFi.Api.f_OnOff;
		mcu_dp_bool_update(DPID_SWITCH_ON, WiFi.Api.f_OnOff);
	}
	
	//定时关/开信息有更新
	if (WiFi.u8_TimerOnOffBak != WiFi.u8_TimerOnOff)
	{
		WiFi.u8_TimerOnOffBak = WiFi.u8_TimerOnOff;
		mcu_dp_fault_update(DPID_TIMER_FUNC,WiFi.u8_TimerOnOff); 
		
	}
	
	//系统模式信息有更新
	if (WiFi.Enum_WSysModeBak != WiFi.Enum_WSysMode)
	{
			
		WiFi.Enum_WSysModeBak = WiFi.Enum_WSysMode;
		mcu_dp_enum_update(DPID_SET_MODE, WiFi.Enum_WSysMode);
	}
	
	//当前温度设定值-℃信息有更新
	if (WiFi.u8_TempCSetBak != WiFi.u8_TempCSet)
	{
		WiFi.u8_TempCSetBak = WiFi.u8_TempCSet;
		mcu_dp_value_update(DPID_SET_TEMPER, WiFi.u8_TempCSet); //VALUE型数据上报;
	}
	
	//当前风速信息有更新
	if (WiFi.Enum_WFanModeBak != WiFi.Enum_WFanMode)
	{
		WiFi.Enum_WFanModeBak = WiFi.Enum_WFanMode;
		mcu_dp_enum_update(DPID_WIND_SPEED, WiFi.Enum_WFanMode);
	}
	
	//当前温度单位信息有更新
	if (WiFi.ApiBak.f_TempUnit != WiFi.Api.f_TempUnit)
	{
		WiFi.ApiBak.f_TempUnit = WiFi.Api.f_TempUnit;
		mcu_dp_bool_update(DPID_C_F_CHANGE,WiFi.Api.f_TempUnit);
	}
	
	//当前定时关剩余分钟信息有更新
	if (WiFi.u16_TimerOffMinuteBak != WiFi.u16_TimerOffMinute)
	{
		WiFi.u16_TimerOffMinuteBak = WiFi.u16_TimerOffMinute;
		mcu_dp_value_update(DPID_OFF_TIMER_MIN,WiFi.u16_TimerOffMinute); 
	}

	//当前定时开剩余分钟信息有更新
	if (WiFi.u16_TimerOnMinuteBak != WiFi.u16_TimerOnMinute)
	{
		WiFi.u16_TimerOnMinuteBak = WiFi.u16_TimerOnMinute;
		mcu_dp_value_update(DPID_ON_TIMER_MIN,WiFi.u16_TimerOnMinute); 
	}

	//当前故障保护信息有更新
	if (WiFi.u8_FaultBak != WiFi.u8_Fault)
	{
		WiFi.u8_FaultBak = WiFi.u8_Fault;
		mcu_dp_fault_update(DPID_FAULT, WiFi.u8_Fault); 
	}
	
	//当前摇头摆风信息有更新
	if (WiFi.ApiBak.f_Sweep != WiFi.Api.f_Sweep)
	{
		WiFi.ApiBak.f_Sweep = WiFi.Api.f_Sweep;
		mcu_dp_bool_update(DPID_WIND, WiFi.Api.f_Sweep);
	}
	
	//当前睡眠标志信息有更新
	if (WiFi.ApiBak.f_Sleep != WiFi.Api.f_Sleep)
	{
		WiFi.ApiBak.f_Sleep = WiFi.Api.f_Sleep;
		mcu_dp_bool_update(DPID_SLEEP_FUNC, WiFi.Api.f_Sleep);
	}
	
	//当前温度设定值-℉信息有更新
	if (WiFi.u8_TempFSetBak != WiFi.u8_TempFSet)
	{
		WiFi.u8_TempFSetBak = WiFi.u8_TempFSet;
		mcu_dp_value_update(DPID_F_TEMPER, WiFi.u8_TempFSet); //VALUE型数据上报;
	}
	
	//当前强力标志信息有更新
	if (WiFi.ApiBak.f_Force != WiFi.Api.f_Force)
	{
		WiFi.ApiBak.f_Force = WiFi.Api.f_Force;
		mcu_dp_bool_update(DPID_FORCE, WiFi.Api.f_Force);
	}
	
}
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
void    App_UartAPI(void)
{
	//更新底板上报信息 开关机信息
	if (System.Enum_Status == ENUM_STATUS_ON)			
	{
		WiFi.Api.f_OnOff = 1;
	}
	else
	{
		WiFi.Api.f_OnOff = 0;
	}
	
	//更新底板上报信息 定时关/开信息	
	if (Timer.f_Enable)
	{
		if (Timer.f_OffEn)
		{
			WiFi.u8_TimerOnOff = 1;
		}
		else if (Timer.f_OnEn)
		{
			WiFi.u8_TimerOnOff = 2;
		}
		else
		{
			WiFi.u8_TimerOnOff = 0;
		}
	}
	else
	{
		WiFi.u8_TimerOnOff = 0;
	}
	
	
	//更新底板上报信息 系统模式信息
	if (System.Mode == ENUM_SYSMODE_COLD)			 //制冷
	{
		WiFi.Enum_WSysMode = ENUM_WSYSMODE_COLD;
	}       
	else if (System.Mode == ENUM_SYSMODE_HUM)	     //除湿
	{
		WiFi.Enum_WSysMode = ENUM_WSYSMODE_HUMI;
	}	
	else if (System.Mode == ENUM_SYSMODE_FAN)        //送风
	{
		WiFi.Enum_WSysMode = ENUM_WSYSMODE_FAN;	
	}
	else if (System.Mode == ENUM_SYSMODE_INTE)       //智能
	{
		WiFi.Enum_WSysMode = ENUM_WSYSMODE_INTE;	
	}
	else if (System.Mode == ENUM_SYSMODE_HEAT)       //制热	
	{
		WiFi.Enum_WSysMode = ENUM_WSYSMODE_HEAT;	
	}

	//更新底板上报信息 当前温度设定值-℃
	WiFi.u8_TempCSet = Tempr.u8_TempCSet;
	
	//更新底板上报信息 当前风速模式   	
	if (Fan.Mode == ENUM_FANMODE_HIGH)			//高风
	{
		WiFi.Enum_WFanMode = ENUM_WFANMODE_HIGH;
	}
	else if (Fan.Mode == ENUM_FANMODE_MED)		//中风
	{
		WiFi.Enum_WFanMode = ENUM_WFANMODE_MED;
	}
	else if (Fan.Mode == ENUM_FANMODE_LOW)     //低风
	{
		WiFi.Enum_WFanMode = ENUM_WFANMODE_LOW;
	}
	else if (Fan.Mode == ENUM_FANMODE_AUTO)    //自动风	
	{
		WiFi.Enum_WFanMode = ENUM_WFANMODE_AUTO;
	}
	
	//更新底板上报信息 当前温度单位	
	WiFi.Api.f_TempUnit = Tempr.f_TempUnit;
	
	//更新底板上报信息 当前定时关剩余分钟
	if (Timer.f_Enable && Timer.f_OffEn)
	{
		WiFi.u16_TimerOffMinute = Timer.u16_Minute;
	}
	else
	{
		WiFi.u16_TimerOffMinute = 0;
	}
	
	//更新底板上报信息 当前定时开剩余分钟
	if (Timer.f_Enable && Timer.f_OnEn)
	{
		WiFi.u16_TimerOnMinute = Timer.u16_Minute;
	}
	else
	{
		WiFi.u16_TimerOnMinute = 0;
	}

	//更新底板上报信息 当前故障保护信息
	WiFi.u8_Fault = CommDisp.Tx.Byte11.ErrInfo;
	
	//更新底板上报信息 摇头摆风信息
	WiFi.Api.f_Sweep = Fan.f_SweepLR;
	
	//更新底板上报信息 睡眠状态信息
	WiFi.Api.f_Sleep = SystemMode.f_Sleep;
	
	//更新底板上报信息 设定温度值华氏信息
	WiFi.u8_TempFSet = Tempr.u8_TempFSet;
	
	//更新底板上报信息
	WiFi.Api.f_Force = SystemMode.f_Force;
	
	
	App_McuAPI_Update();			//底板信息有更新时上报	
}
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
void	App_uartapi_onoff(unsigned char power)
{
	if (power == 0)		//APP需求关机
	{
		if (System.Enum_Status == ENUM_STATUS_ON)
		{
			DisplayBoardTurnOff();      		//关机处理
		}
	}
	else				//APP需求开机
	{
		if (System.Enum_Status == ENUM_STATUS_OFF)
		{
			DisplayBoardTurnOn(); 				//开机处理
		}	
	}
}
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
void	App_uartapi_timeronoff(unsigned char timeronoff)
{
	if (timeronoff == 1)		//定时关
	{
		if ((Timer.f_Enable == 0) || (Timer.f_OffEn == 0))
		{
			Timer.f_Enable = 1;
			Timer.f_OffEn = 1;
			Timer.f_OnEn = 0;
		}
	}
	else if (timeronoff == 2)	//定时开
	{
		if ((Timer.f_Enable == 0) || (Timer.f_OnEn == 0))
		{
			Timer.f_Enable = 1;
			Timer.f_OnEn = 1;
			Timer.f_OffEn = 0;
		}	
	}
	else						//无定时
	{
		if (Timer.f_Enable || Timer.f_OffEn || Timer.f_OnEn)
		{
			Timer.f_Enable = 0;
			Timer.f_OffEn = 0;
			Timer.f_OnEn = 0;		
		}
	}
}
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
void	App_uartapi_wsysmode(unsigned char wsysmode)
{
	//备注:0智能；1制热；2除湿；3制冷；4送风
		
	switch (wsysmode)
	{
		case	ENUM_WSYSMODE_INTE: System.Mode = ENUM_SYSMODE_INTE; break;
		case	ENUM_WSYSMODE_HEAT: System.Mode = ENUM_SYSMODE_HEAT; break;
		case	ENUM_WSYSMODE_HUMI: System.Mode = ENUM_SYSMODE_HUM;  break;
		case	ENUM_WSYSMODE_COLD: System.Mode = ENUM_SYSMODE_COLD; break;
		case	ENUM_WSYSMODE_FAN:  System.Mode = ENUM_SYSMODE_FAN;  break;

		default: break;
	}
	
	if (System.ModeBak != System.Mode)
	{
		Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_INIT;		//操作模式,重新计算温差区域
		Tempr.T1TSDeltaZoneBak = ENUM_TEMPDELTAZONE_INIT;	//操作模式,重新计算温差区域
		
		//模式标志重新判定
		SystemMode.f_Cold = 0;		
		SystemMode.f_Heat = 0;
		SystemMode.f_Fan = 0;
		SystemMode.f_Auto = 0;
		
		SystemMode.f_TempCEC = 0;							//操作模式,达温标志清除			
		SystemMode.f_Sleep = 0;								//操作模式,退出睡眠
		
		if (System.Mode == ENUM_SYSMODE_HUM)
		{
			//进入除湿模式计算设定温度:    ST = T1 - 2
			if (T1.s8_Value < 18)
			{				
				Tempr.u8_HumiCSet = 16;	//最低
			}
			else if (T1.s8_Value > 34)
			{
				Tempr.u8_HumiCSet = 32;	//最高
			}
			else
			{
				Tempr.u8_HumiCSet = T1.s8_Value - 2;
			}
		}
		else
		{
			Tempr.u8_HumiCSet = 24;	//默认
		}
		
		System.ModeBak = System.Mode;
	}		
}
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
void	App_uartapi_tempcset(unsigned char tempcset)
{
	if (Tempr.u8_TempCSet != tempcset)
	{	
		Tempr.u8_TempCSet = tempcset;
		
		if (SystemMode.f_Sleep)
		{
			Tempr.u8_TempCSetSleep = Tempr.u8_TempCSet;
		}
		
		//add code...//状态变化相关参数处理
		if (System.Mode == ENUM_SYSMODE_COLD)
		{
			Tempr.u8_ColdCSet = Tempr.u8_TempCSet;
		}
		
		if (System.Mode == ENUM_SYSMODE_HEAT)
		{
			Tempr.u8_HeatCSet = Tempr.u8_TempCSet;
		}
		
		System.u32_SleepCount = 0;	
	}
}
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
void	App_uartapi_fanmode(unsigned char fanmode)
{	
	switch (fanmode)
	{
		case	ENUM_WFANMODE_AUTO: Fan.Mode = ENUM_FANMODE_AUTO; break;   //自动风	
		case	ENUM_WFANMODE_LOW:  Fan.Mode = ENUM_FANMODE_LOW;  break;   //低风	
		case	ENUM_WFANMODE_MED:  Fan.Mode = ENUM_FANMODE_MED;  break;   //中风
		case	ENUM_WFANMODE_HIGH: Fan.Mode = ENUM_FANMODE_HIGH; break;   //高风
			
		default: break;
	}
	
	if (Fan.ModeBak != Fan.Mode)
	{
		Fan.ModeBak = Fan.Mode;
		
		SystemMode.f_TempCEC = 0;					//操作风速,达温标志清除
		SystemMode.f_Sleep = 0;						//操作风速,退出睡眠
	}
}
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
void	App_uartapi_tempunit(unsigned char tempunit)
{
	if (tempunit == 0)
	{
		Tempr.f_TempUnit = 0;//摄氏度
	}
	else
	{
		Tempr.f_TempUnit = 1;//华氏度
	}
}
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
void	App_uartapi_timeroff(unsigned long timeroff)
{
	if (timeroff > 0)
	{
		Timer.u16_SecDiv10Remain = 0;
		Timer.u16_Minute = (U16)timeroff;
		Timer.f_OffEn = 1;
		Timer.f_Enable = 1;
	}
	else
	{
		Timer.u16_SecDiv10Remain = 0;
		Timer.u16_Minute = 0;
		Timer.f_OffEn = 0;
		Timer.f_Enable = 0;	
	}
}
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
void	App_uartapi_timeron(unsigned long timeron)
{
	if (timeron > 0)
	{
		Timer.u16_SecDiv10Remain = 0;
		Timer.u16_Minute = (U16)timeron;
		Timer.f_OnEn = 1;
		Timer.f_Enable = 1;
	}
	else
	{
		Timer.u16_SecDiv10Remain = 0;
		Timer.u16_Minute = 0;
		Timer.f_OnEn = 0;
		Timer.f_Enable = 0;	
	}
}
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
void	App_uartapi_sweep(unsigned char sweep)
{
	if (sweep == 0)
	{
		Fan.f_SweepLR = 0;
	}
	else
	{
		Fan.f_SweepLR = 1;
	}
}
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
void	App_uartapi_sleep(unsigned char sleep)
{
	if (sleep == 0)
	{
		SystemMode.f_Sleep = 0;
	}
	else
	{
		SystemMode.f_Sleep = 1;
	}
}
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
void	App_uartapi_tempfset(unsigned char tempfset)
{
	if (Tempr.u8_TempFSet != tempfset)
	{	
		Tempr.u8_TempFSet = tempfset;
		
		//控制逻辑仍使用摄氏度单位进行温控
		if (SystemMode.f_Sleep)
		{
			Tempr.u8_TempCSetSleep = Tempr.u8_TempCSet;
		}
		
		//add code...//状态变化相关参数处理
		if (System.Mode == ENUM_SYSMODE_COLD)
		{
			Tempr.u8_ColdCSet = Tempr.u8_TempCSet;
		}
		
		if (System.Mode == ENUM_SYSMODE_HEAT)
		{
			Tempr.u8_HeatCSet = Tempr.u8_TempCSet;
		}
		
		System.u32_SleepCount = 0;	
	}
}
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
void	App_uartapi_force(unsigned char force)
{
	if (force == 0)
	{
		SystemMode.f_Force = 0;
	}
	else
	{
		SystemMode.f_Force = 1;
	}
}
#endif

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
void	App_TCLModule_Slave_Info(void) //主控发送给WIFI
{
	S16    s16_temp;
	U8	   u8_temp;
	static U8 Add1 = 0;	//LCX ADD
	static U8 u8_TempFSetBak = 0;

	//------------------------------------------------------------------------------------------//
	//第1字节-版本号高位A
	WiFi.Slave.Byte1.VersionHighA = C_FUNC_SOFT_VERSION_A;
	
	//------------------------------------------------------------------------------------------//
	//第2字节-版本号低位B
	WiFi.Slave.Byte2.VersionLowB = C_FUNC_SOFT_VERSION_B;
	
	//------------------------------------------------------------------------------------------//
	//第3字节
	//设定模式
	switch (System.Mode)
	{
		case	ENUM_SYSMODE_COLD: WiFi.Slave.Byte3.SlaveByte3.ModeSet = ENUM_WIFISMODESET_COLD; 	 break;		//制冷
		case	ENUM_SYSMODE_HUM:  WiFi.Slave.Byte3.SlaveByte3.ModeSet = ENUM_WIFISMODESET_HUM;  	 break;  	//除湿
		case	ENUM_SYSMODE_FAN:  WiFi.Slave.Byte3.SlaveByte3.ModeSet = ENUM_WIFISMODESET_FAN;  	 break;    	//送风
		case	ENUM_SYSMODE_INTE: WiFi.Slave.Byte3.SlaveByte3.ModeSet = ENUM_WIFISMODESET_SELSENSE; break; 	//智能
		case	ENUM_SYSMODE_HEAT: WiFi.Slave.Byte3.SlaveByte3.ModeSet = ENUM_WIFISMODESET_HEAT; 	 break; 	//制热	
		
		default: break;
	}		
	
	//开关机
	if ((System.Enum_Status == ENUM_STATUS_INIT) || (System.Enum_Status == ENUM_STATUS_OFF))
	{
		WiFi.Slave.Byte3.SlaveByte3.OnOff = 0;
	}
	else
	{
		WiFi.Slave.Byte3.SlaveByte3.OnOff = 1;
	}
		
	//数显
	WiFi.Slave.Byte3.SlaveByte3.NumDisp = 0; 
		
	//经济 
	WiFi.Slave.Byte3.SlaveByte3.Economic = 0;	
   
	//强力
	WiFi.Slave.Byte3.SlaveByte3.Force = SystemMode.f_Force;

	//------------------------------------------------------------------------------------------//
	//第4字节
	//设定温度
	if ((Tempr.u8_TempCSet >= 13) && (Tempr.u8_TempCSet <= 32))
	{
		WiFi.Slave.Byte4.SlaveByte4.TempSet = (ENUM_WIFITEMPSET)(32 - Tempr.u8_TempCSet);
	}
	else
	{
		WiFi.Slave.Byte4.SlaveByte4.TempSet = (ENUM_WIFITEMPSET)8;	//默认设定值24℃
	}
		  
	//设定风速	
	if      (Fan.Mode == ENUM_FANMODE_AUTO)    WiFi.Slave.Byte4.SlaveByte4.WindSpeed = ENUM_WIFIWINDSPEED_AUTO;		//自动  
	else if (Fan.Mode == ENUM_FANMODE_HIGH)    WiFi.Slave.Byte4.SlaveByte4.WindSpeed = ENUM_WIFIWINDSPEED_HIGH;		//高速 		
	else if (Fan.Mode == ENUM_FANMODE_MED)	   WiFi.Slave.Byte4.SlaveByte4.WindSpeed = ENUM_WIFIWINDSPEED_MED;		//中速
	else
	{
//		if (SystemMode.f_Sleep)		WiFi.Slave.Byte4.SlaveByte4.WindSpeed = ENUM_WIFIWINDSPEED_SILENCE;		//静音	
//		else						WiFi.Slave.Byte4.SlaveByte4.WindSpeed = ENUM_WIFIWINDSPEED_LOW;			//低速
		
		WiFi.Slave.Byte4.SlaveByte4.WindSpeed = ENUM_WIFIWINDSPEED_LOW;			//低速
	}
	if (System.Mode == ENUM_SYSMODE_HUM)  	WiFi.Slave.Byte4.SlaveByte4.WindSpeed = ENUM_WIFIWINDSPEED_AUTO; 	//APP要显示自动风 lcx add 20240715
	if (SystemMode.f_Sleep) 				WiFi.Slave.Byte4.SlaveByte4.WindSpeed = ENUM_WIFIWINDSPEED_LOW; 	//睡眠微风（显示低风）放最后优先。  lcx add 20240715	

	//------------------------------------------------------------------------------------------//
	//第5字节
	
	if(Tempr.u8_TempFSet != u8_TempFSetBak) //lcx add
	{
		if(Tempr.u8_TempFSet > u8_TempFSetBak) Add1 = 1;
		else Add1 = 0;
		u8_TempFSetBak = Tempr.u8_TempFSet;
	}
	if(Add1 == 1)
	{
		WiFi.Slave.Byte5.SlaveByte5.TempFSetAdd1 = App_TCLModule_Fadd1(Tempr.u8_TempFSet); //bit0:    华氏显示设定温度加1
	}	
	else
	{
		WiFi.Slave.Byte5.SlaveByte5.TempFSetAdd1 = 0; //减温度时不加1
	}
	WiFi.Slave.Byte5.SlaveByte5.TempCSetHalf = 0;    			 //bit1:    摄氏度显示设定温度0.5
	WiFi.Slave.Byte5.SlaveByte5.Healthy		 = 0;    			 //bit2:    健康
	WiFi.Slave.Byte5.SlaveByte5.DeMold		 = Fan.f_DeMold;     //bit3:    防霉
	WiFi.Slave.Byte5.SlaveByte5.BothSweep    = 0;	 			 //bit4:    立体送风
    WiFi.Slave.Byte5.SlaveByte5.EAHeater     = 0;    			 //bit5:    电加热
	WiFi.Slave.Byte5.SlaveByte5.TimerOff     = Timer.f_OffEn;    //bit6:    普通定时关机
	WiFi.Slave.Byte5.SlaveByte5.TimerOn      = Timer.f_OnEn;     //bit7:    普通定时开机
	
	//------------------------------------------------------------------------------------------//
	//第6字节	
	WiFi.Slave.Byte6.SlaveByte6.HumanSenseFanSet = ENUM_WIFISHSFAN_OFF; 	//人感送风选择
	WiFi.Slave.Byte6.SlaveByte6.Reserve2 		 = 0;	 					//预留
	WiFi.Slave.Byte6.SlaveByte6.HumiChk	 		 = 0;    					//湿度检测
	WiFi.Slave.Byte6.SlaveByte6.CleanChk 		 = 0;    					//清洁度检测
	WiFi.Slave.Byte6.SlaveByte6.SweepLR	 		 = Fan.f_SweepLR;	 		//左右风摆
	WiFi.Slave.Byte6.SlaveByte6.SweepUD	 		 = Fan.f_SweepLR;	 		//上下风摆
	WiFi.Slave.Byte6.SlaveByte6.TempUnit 		 = Tempr.f_TempUnit;		//温度单位

	//------------------------------------------------------------------------------------------//
	//第7字节
	if (Timer.f_Enable && Timer.f_OffEn)
	{
		WiFi.Slave.Byte7.TimerOffHour = Timer.u16_Minute/60;
	}
	else
	{
		WiFi.Slave.Byte7.TimerOffHour = 0;
	}
	
	//------------------------------------------------------------------------------------------//
	//第8字节
	if (Timer.f_Enable && Timer.f_OffEn)
	{
		WiFi.Slave.Byte8.TimerOffMinute = Timer.u16_Minute%60;
	}
	else
	{
		WiFi.Slave.Byte8.TimerOffMinute = 0;
	}	
	
	//------------------------------------------------------------------------------------------//
	//第9字节
	if (Timer.f_Enable && Timer.f_OnEn)
	{
		WiFi.Slave.Byte9.TimerOnHour = Timer.u16_Minute/60;
	}
	else
	{
		WiFi.Slave.Byte9.TimerOnHour = 0;
	}
	
	//------------------------------------------------------------------------------------------//
	//第10字节
	if (Timer.f_Enable && Timer.f_OnEn)
	{
		WiFi.Slave.Byte10.TimerOnMinute = Timer.u16_Minute%60;
	}
	else
	{
		WiFi.Slave.Byte10.TimerOnMinute = 0;
	}

	//------------------------------------------------------------------------------------------//
	//第11字节
	WiFi.Slave.Byte11.Byte = 0;

	if 		(WiFi.Enum_Status == ENUM_TWIFISTATUS_AP)		WiFi.Slave.Byte11.SlaveByte11.InfoAP = 1;    //AP提示
	else if (WiFi.Enum_Status == ENUM_TWIFISTATUS_SA)		WiFi.Slave.Byte11.SlaveByte11.InfoSA = 1;	 //SA提示
    else if (WiFi.Enum_Status == ENUM_TWIFISTATUS_PP) 		WiFi.Slave.Byte11.SlaveByte11.InfoPP = 1;    //PP提示
	else if (WiFi.Enum_Status == ENUM_TWIFISTATUS_CONFIG)	WiFi.Slave.Byte11.SlaveByte11.Config = 1;	 //配置
	
	WiFi.Slave.Byte11.SlaveByte11.BussChk = 0;	   		   //商检
	WiFi.Slave.Byte11.SlaveByte11.CommErr = 0;	   		   //串口通讯故障
	WiFi.Slave.Byte11.SlaveByte11.OffLine = 0;	   		   //掉线
	WiFi.Slave.Byte11.SlaveByte11.Reset = WiFi.f_Reset;	   //复位

	//------------------------------------------------------------------------------------------//
	//第12字节
	WiFi.Slave.Byte12.Byte = 0;
	
	WiFi.Slave.Byte12.SlaveByte12.TopOutWindCommErr = 0;    //bit0: 顶出风和主板通信故障
	
//	if (F_uart4_CommErr)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_E8_COMMDISP)
//	{
//		WiFi.Slave.Byte12.SlaveByte12.DispCommErr = 1;		//bit1: 显示屏和主板通信故障
//	}
		
	WiFi.Slave.Byte12.SlaveByte12.Reserve2			= 0;	//bit2: 预留
	
	if (F_uart0_CommErr || System.f_InOutCommErr)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_EF_INOUTCOMMERR)
	{
		WiFi.Slave.Byte12.SlaveByte12.OutdoorCommErr = 1;	//bit3: 室内外通信故障
	}
	
	if (System.f_InEEpromErr)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F2_INEEPROMERR)
	{
		WiFi.Slave.Byte12.SlaveByte12.EEPROMErr = 1;		//bit4: 内EEPROM故障
	}
	
	if (Fan.Indoor.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_ED_FANINERR)
	{
		WiFi.Slave.Byte12.SlaveByte12.IndoorFanErr = 1;		//bit5: 内风机故障
	}
	
	if (T1.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_E1_TEMPROOM)
	{
		WiFi.Slave.Byte12.SlaveByte12.T1Err = 1;			//bit6: 内环境温度传感器故障
	}
	
	if (T2.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_E2_TEMPCOIL)
	{
		WiFi.Slave.Byte12.SlaveByte12.T2Err = 1;			//bit7: 内盘管传感器故障	
	}
	
	//------------------------------------------------------------------------------------------//
	//第13字节	
	s16_temp = T1.s16_ValueMul10;
	if (s16_temp > 800)		s16_temp = 800;
	if (s16_temp < -200)	s16_temp = -200;
	s16_temp += 200;
	WiFi.Slave.Byte13.T1ValueMul10High = s16_temp >> 2;
		
	//------------------------------------------------------------------------------------------//
	//第14字节
	WiFi.Slave.Byte14.SlaveByte14.T1ValueMul10Low = s16_temp & 0x03;
	WiFi.Slave.Byte14.SlaveByte14.OutWindTempLow = 0;
	WiFi.Slave.Byte14.SlaveByte14.HumiValueLow = 0;
	
	s16_temp = T2.s16_ValueMul10;
	if (s16_temp > 800)		s16_temp = 800;
	if (s16_temp < -200)	s16_temp = -200;
	s16_temp += 200;	
	WiFi.Slave.Byte14.SlaveByte14.T2ValueMul10Low = s16_temp & 0x03;
	
	//------------------------------------------------------------------------------------------//
	//第26字节
	WiFi.Slave.Byte26.T2ValueMul10High = s16_temp >> 2;

	//------------------------------------------------------------------------------------------//
	//第15字节
	//睡眠模式选择
	if (SystemMode.f_Sleep)
	{
		WiFi.Slave.Byte15.SlaveByte15.SleepMode = ENUM_SLEEPMODE_NORMAL;
	}
	else
	{
		WiFi.Slave.Byte15.SlaveByte15.SleepMode = ENUM_SLEEPMODE_NULL;
	}
	
	//空调机型类别
	WiFi.Slave.Byte15.SlaveByte15.Type = ENUM_TYPEKT_BPYDKT;
	
	//bit7 ready表示变频机型数据准备状态，此位为1表示第31~42字节数据有效，否则无效
	WiFi.Slave.Byte15.SlaveByte15.Ready = 1;

	//------------------------------------------------------------------------------------------//	
	//第16字节
	WiFi.Slave.Byte16.Byte = 0;
	
	//WiFi.Slave.Byte16.SlaveByte16.TempFSetAdd1 = App_TCLModule_Fadd1(Tempr.u8_TempFSet);
	if(Add1 == 1) //lcx add
	{
		WiFi.Slave.Byte5.SlaveByte5.TempFSetAdd1 = App_TCLModule_Fadd1(Tempr.u8_TempFSet); //bit0:    华氏显示设定温度加1
	}	
	else
	{
		WiFi.Slave.Byte5.SlaveByte5.TempFSetAdd1 = 0; //减温度时不加1
	}

	if (SystemMode.f_Sleep)
	{
		u8_temp = Tempr.u8_TempCSetSleep;
		
		if (SystemMode.f_Cold == 1)
		{
			u8_temp += 1;
			if (u8_temp > 31)	u8_temp = 31;
			
		}		
		else if (SystemMode.f_Heat == 1)
		{
			u8_temp -= 1;
			if (u8_temp < 16)	u8_temp = 16;		
		}

		WiFi.Slave.Byte16.SlaveByte16.Sleep01HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;		

	}

	//------------------------------------------------------------------------------------------//		
	//第17字节
	WiFi.Slave.Byte17.Byte = 0;	
	
	if (SystemMode.f_Sleep)
	{
		u8_temp = Tempr.u8_TempCSetSleep;
		
		if (SystemMode.f_Cold == 1)
		{
			u8_temp += 2;
			if (u8_temp > 31)	u8_temp = 31;
			
		}		
		else if (SystemMode.f_Heat == 1)
		{
			u8_temp -= 2;
			if (u8_temp < 16)	u8_temp = 16;		
		}

		WiFi.Slave.Byte17.SlaveByte17.Sleep02HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;		

	}

	//------------------------------------------------------------------------------------------//		
	//第18字节-第25字节	
	WiFi.Slave.Byte18.Byte = 0;	
	WiFi.Slave.Byte19.Byte = 0;
	WiFi.Slave.Byte20.Byte = 0;
	WiFi.Slave.Byte21.Byte = 0;	
	WiFi.Slave.Byte22.Byte = 0;
	WiFi.Slave.Byte23.Byte = 0;	
	WiFi.Slave.Byte24.Byte = 0;	
	WiFi.Slave.Byte25.Byte = 0;
	
	if (SystemMode.f_Sleep)
	{
		u8_temp = Tempr.u8_TempCSetSleep;
		
		if (SystemMode.f_Cold == 1)
		{
			u8_temp += 2;
			if (u8_temp > 31)	u8_temp = 31;
			
		}		
		else if (SystemMode.f_Heat == 1)
		{
			u8_temp -= 3;
			if (u8_temp < 16)	u8_temp = 16;		
		}

		WiFi.Slave.Byte18.SlaveByte18.Sleep03HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;		
		WiFi.Slave.Byte19.SlaveByte19.Sleep04HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;
		WiFi.Slave.Byte20.SlaveByte20.Sleep05HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;
		WiFi.Slave.Byte21.SlaveByte21.Sleep06HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;
		WiFi.Slave.Byte22.SlaveByte22.Sleep07HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;		
		WiFi.Slave.Byte23.SlaveByte23.Sleep08HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;
		WiFi.Slave.Byte24.SlaveByte24.Sleep09HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;
		WiFi.Slave.Byte25.SlaveByte25.Sleep10HTempSet = (ENUM_SLEEP_TEMPSET)u8_temp;		
	}

	//------------------------------------------------------------------------------------------//		
	//第27字节
	WiFi.Slave.Byte27.OutWindTempHigh = 0;	//室内出风温度转换高8位
	
	//------------------------------------------------------------------------------------------//		
	//第28字节
	WiFi.Slave.Byte28.HumiValueHigh = 0;	//室内湿度转换值高8位
	
	//------------------------------------------------------------------------------------------//		
	//第29字节	
	WiFi.Slave.Byte29.Byte = 0;				//空气质量
	
	//------------------------------------------------------------------------------------------//		
	//第30字节	
	//室内风机转速
	WiFi.Slave.Byte30.IndoorFanSpeedDiv10 = Fan.Indoor.u16_RealRPM/10;

	//------------------------------------------------------------------------------------------//		
	//第31字节
	//T4温度转换值
	s16_temp = T4.s16_ValueMul10;
	s16_temp /= 10;
	if (s16_temp > 80)		s16_temp = 80;
	if (s16_temp < -20)		s16_temp = -20;
	s16_temp += 20;
	
	WiFi.Slave.Byte31.T4ValueAdd20 = s16_temp;	
	
	//------------------------------------------------------------------------------------------//		
	//第32字节
	//T3温度转换值
	s16_temp = T3.s16_ValueMul10;
	s16_temp /= 10;
	if (s16_temp > 80)		s16_temp = 80;
	if (s16_temp < -20)		s16_temp = -20;
	s16_temp += 20;
	
	WiFi.Slave.Byte32.T3ValueAdd20 = s16_temp;		
	
	//------------------------------------------------------------------------------------------//		
	//第33字节
	//Tp温度转换值
	s16_temp = Tp.s16_ValueMul10;
	s16_temp /= 10;
	if (s16_temp > 80)		s16_temp = 80;
	if (s16_temp < -20)		s16_temp = -20;
	s16_temp += 20;
	
	WiFi.Slave.Byte33.TpValueAdd20 = s16_temp;

	//------------------------------------------------------------------------------------------//		
	//第34字节	
	//室外风机转速
	WiFi.Slave.Byte34.OutdoorFanSpeedDiv10 = Fan.Outdoor.u16_RealRPM/10;
	
	//------------------------------------------------------------------------------------------//		
	//第35字节	
	//压缩机运行频率
	WiFi.Slave.Byte35.CompRealFreq = Comp.u8_RealHZ;
	
	//------------------------------------------------------------------------------------------//		
	//第36字节		
	//压缩机运行频率档
	if (Comp.u8_RealHZ == 0)	WiFi.Slave.Byte36.SlaveByte36.CompLevel = ENUM_COMPLEVEL_OFF;	//待定******
	else						WiFi.Slave.Byte36.SlaveByte36.CompLevel = ENUM_COMPLEVEL_15;
	//四通阀
	WiFi.Slave.Byte36.SlaveByte36.FourwayOnoff = FourWay.f_DrvOn;
	
	//电磁阀
	WiFi.Slave.Byte36.SlaveByte36.ElMagValveOnoff = 0;
	
	//------------------------------------------------------------------------------------------//		
	//第37字节
	//故障信息
	WiFi.Slave.Byte37.Byte = 0;
	
	if (F_uart0_CommErr || System.f_InOutCommErr)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_EF_INOUTCOMMERR)
	{
		WiFi.Slave.Byte37.SlaveByte37.InOutdoorCommErr = 1;  //室内外通信故障
	}
		
	WiFi.Slave.Byte37.SlaveByte37.OutdoorMoudleCommErr = 0;	 //室外模块间通信故障
	
	if (T3.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_EB_TEMPCOIL2)
	{
		WiFi.Slave.Byte37.SlaveByte37.T3Err			   = 1;  //室外盘管温度传感器故障
	}
		
	WiFi.Slave.Byte37.SlaveByte37.SystemErr			   = 0;	 //系统故障(缺氟)
		
	WiFi.Slave.Byte37.SlaveByte37.TypeConfigErr		   = 0;	 //机型配置错误
	
	if (T4.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_EA_TEMPOUTDOOR)
	{
		WiFi.Slave.Byte37.SlaveByte37.T4Err			   = 1;  //室外环境温度传感器故障
	}
	
	if (Tp.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_E7_TEMPEXHAUST)
	{
		WiFi.Slave.Byte37.SlaveByte37.TpErr			   = 1;  //室外排气温度传感器故障
	}
	
	if (Comp.f_IPMErr)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F0_COMPIPMERR)
	{
		WiFi.Slave.Byte37.SlaveByte37.IPMErr		   = 1;  //室外IPM模块故障
	}

	//------------------------------------------------------------------------------------------//		
	//第38字节
	//故障/保护信息
	WiFi.Slave.Byte38.Byte = 0;
	
	if (Fan.Outdoor.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_EE_FANOUTERR)
	{
		WiFi.Slave.Byte38.SlaveByte38.OutdoorFanErr    	   = 1;  //室外直流风机故障
	}
	
	if (CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F1_CURRSENSERR)	//
	{
		WiFi.Slave.Byte38.SlaveByte38.OutdoorCurrSensorErr = 1;  //室外电流传感器故障
	}
	
	if (System.f_OutEEpromErr)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F3_OUTEEPROMERR)
	{
		WiFi.Slave.Byte38.SlaveByte38.OutdoorEEPROMErr	   = 1;	 //室外EEPROM故障
	}
	
	WiFi.Slave.Byte38.SlaveByte38.CompTopErr		   	   = 0;	 //室外压缩机壳顶故障
	
	WiFi.Slave.Byte38.SlaveByte38.OutdoorVoltSensorErr 	   = 0;	 //室外电压传感器故障
	
	WiFi.Slave.Byte38.SlaveByte38.AspirationSensorErr  	   = 0;	 //室外吸气传感器故障
	
	if (System.f_VoltLowPro)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F5_VOLTLOWPRO)
	{
		WiFi.Slave.Byte38.SlaveByte38.OutdoorVoltPro	   = 1;  //室外电压过高过低保护
	}
	
	if (System.f_CurrentProtect)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F4_OVCURRPRO)
	{
		WiFi.Slave.Byte38.SlaveByte38.OutdoorCurrPro	   = 1;  //室外电流保护
	}

	//------------------------------------------------------------------------------------------//		
	//第39字节
	//保护信息
	WiFi.Slave.Byte39.Byte = 0;
	
	if (Protect.f_Tp)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_FA_TPPRO)
	{
		WiFi.Slave.Byte39.SlaveByte39.TpHighPro     = 1;    //室外排气温度过高保护
	}
	
	if (Protect.f_T2Cold)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_FB_T2COLD)
	{
		WiFi.Slave.Byte39.SlaveByte39.T2ColdPro	    = 1;    //室内盘管制冷过冷保护
	}
	
	if (Protect.f_T3Cold)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F9_T3COLD)
	{
		WiFi.Slave.Byte39.SlaveByte39.T3HeatPro     = 1;    //室外盘管制冷过热保护
	}
	
	if (Tempr.T2HeatZone == ENUM_TEMPT2HEATZONE_PRO)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_FC_T2HEAT)
	{
		WiFi.Slave.Byte39.SlaveByte39.T2HeatPro	    = 1;    //室内盘管制热过热保护
	}
	
	if ((Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO) || (Tempr.T4HeatZone == ENUM_TEMPT4HEATZONE_PRO1) ||
		(Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_PRO) || (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_PRO1) ||
		 (Tempr.T4CoolZone == ENUM_TEMPT4COOLZONE_STOP))
	//把ENUM_TEMPT4COOLZONE_STOP（实际也停机）纳入F8报警。 	 		lcx add 20240620	
	{//	if (CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F8_T4PRO)
		WiFi.Slave.Byte39.SlaveByte39.T4TempPro     = 1;	//室外环境温度过高过低保护
	}
	
	if (Comp.f_StartErr)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F7_COMPSTARTERR)
	{
		WiFi.Slave.Byte39.SlaveByte39.CompDrvPro    = 1;    //室外压缩机驱动保护
	}
	
	if (Comp.f_IPMPro)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_F6_COMPIPMPRO)
	{
		WiFi.Slave.Byte39.SlaveByte39.IPMPro		= 1;    //室外IPM模块保护
	}
		
	WiFi.Slave.Byte39.SlaveByte39.OutdoorFanPro     = 0;    //室外直流风机保护	


	//------------------------------------------------------------------------------------------//		
	//第40字节
	//故障-保护信息
	WiFi.Slave.Byte40.Byte = 0;

	if (T2.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_E2_TEMPCOIL)
	{
		WiFi.Slave.Byte40.SlaveByte40.T2Err 	 = 1;	//室内盘管温度传感器故障
	}
	
	if (T1.f_Error)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_E1_TEMPROOM)
	{
		WiFi.Slave.Byte40.SlaveByte40.T1Err		 = 1;   //室内环境温度传感器故障
	}
	
	if (Comp.f_StartErr)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_EC_STARTERR)	//
	{
		WiFi.Slave.Byte40.SlaveByte40.CompDrvErr = 1;   //室外压缩机驱动故障
	}
	
	if (CommMotDrv.ReqSet.Rx.Byte9.OutDoorStatus5.f_PFCSwitchOff)
	{
		WiFi.Slave.Byte40.SlaveByte40.PFCPro	 = 1;   //室外PFC保护
	}
	
	//------------------------------------------------------------------------------------------//		
	//第41字节
	//室外电压AD值
	WiFi.Slave.Byte41.Byte = 0xFF;	

	//------------------------------------------------------------------------------------------//		
	//第42字节
	//室外电流AD值
	WiFi.Slave.Byte42.Byte = 0xFF;	
	
	//------------------------------------------------------------------------------------------//		
	//第43,44,45字节
	//本次运行电量（45字节Bit3-Bit0）
	WiFi.Slave.Byte43.Byte = 0xFF;
	WiFi.Slave.Byte44.Byte = 0xFF;		
	WiFi.Slave.Byte45.Byte = 0xFF;

	//------------------------------------------------------------------------------------------//		
	//第46,47字节
	//本次运行电费（45字节Bit7-Bit4）	
	WiFi.Slave.Byte46.Byte = 0xFF;		
	WiFi.Slave.Byte47.Byte = 0xFF;	

	//------------------------------------------------------------------------------------------//		
	//第48,49字节
	//累计运行电量
	WiFi.Slave.Byte48.Byte = 0xFF;	
	WiFi.Slave.Byte49.Byte = 0xFF;	

	//------------------------------------------------------------------------------------------//		
	//第50,51字节
	//累计运行电量
	WiFi.Slave.Byte50.Byte = 0xFF;		
	WiFi.Slave.Byte51.Byte = 0xFF;	
	
	//------------------------------------------------------------------------------------------//		
	//第52,53字节
	//电费单价
	WiFi.Slave.Byte52.Byte = 0xFF;		
	WiFi.Slave.Byte53.Byte = 0xFF;

	//------------------------------------------------------------------------------------------//		
	//第54,55字节
	//运行功率
	WiFi.Slave.Byte54.Byte = 0xFF;
	WiFi.Slave.Byte55.Byte = 0xFF;	

	//------------------------------------------------------------------------------------------//		
	//第56,57字节
	//压缩机运行时间或过滤器时间已使用时间
	WiFi.Slave.Byte56.Byte = 0xFF;	
	WiFi.Slave.Byte57.Byte = 0xFF;	

	//------------------------------------------------------------------------------------------//		
	//第58字节
	//故障保护除霜等
	WiFi.Slave.Byte58.Byte = 0;
	
	if (WaterBox.f_Full)//(CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_E3_WATERFULL)
	{
		WiFi.Slave.Byte58.SlaveByte58.WaterFullWarning   = 1;    //水满报警
	}
	
	if (CommDisp.Tx.Byte11.ErrInfo == ENUM_ERRINFO_E4_PUMP)	//*但本机型无水泵*
	{
		WiFi.Slave.Byte58.SlaveByte58.PumpWarning	     = 1;    //水泵报警
	}
	
	WiFi.Slave.Byte58.SlaveByte58.FilterWarning	     = 0;	 //过滤器报警
	
	WiFi.Slave.Byte58.SlaveByte58.WaterBoxErrWarning = 0;    //水箱放置错误报警
	
	WiFi.Slave.Byte58.SlaveByte58.WaterBoxWatLess    = 0;    //水箱缺水
	
	if (Defrost.f_Enable)
	{
		WiFi.Slave.Byte58.SlaveByte58.DefrostWarning	 = 1;	 //除霜报警
	}
	
	//------------------------------------------------------------------------------------------//		
	//第59字节
	//负载/功能
	WiFi.Slave.Byte59.Byte = 0;
	
	WiFi.Slave.Byte59.SlaveByte59.CompOnOff     = Comp.f_DrvOn;    	//压缩机运行		0:停机		1:正在运行
	
	if (Fan.Outdoor.u16_RealRPM > 800)
	{
		WiFi.Slave.Byte59.SlaveByte59.OutdoorFanLow = 0; 
	}
	else
	{
		WiFi.Slave.Byte59.SlaveByte59.OutdoorFanLow = 1;    //外风机 		0:高风		1:低风
	}
	
	WiFi.Slave.Byte59.SlaveByte59.PumpOnOff		= 0;	//水泵			0:关闭		1:开启
	
	WiFi.Slave.Byte59.SlaveByte59.WPMotorOnOff	= WPMotor.f_DrvOn;	//打水电机		0:关闭		1:开启
	
	//固有功能
	WiFi.Slave.Byte59.SlaveByte59.HeatEnable	= 1;	//是否制热		0:无制热	    1:有制热
	WiFi.Slave.Byte59.SlaveByte59.SleepEnable	= 1;	//是否睡眠		0:无睡眠	    1:有睡眠
	WiFi.Slave.Byte59.SlaveByte59.SweepEnable	= 1;	//是否摇摆		0:无摇摆	    1:有摇摆
	WiFi.Slave.Byte59.SlaveByte59.AutoEnable	= 1;	//是否自动		0:无自动	    1:有自动	
	
	//------------------------------------------------------------------------------------------//		
	//第60字节
	//舒适功能/计时显示
	WiFi.Slave.Byte60.Byte = 0;
	
}
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
void	App_TCLModule_Master_Info(void) //WIFI发送给主控
{
	U8 temp;
	
	//存差异即有APP操作更新
	//第1字节
//	if (WiFi.MasterBak.Byte1.Byte != WiFi.Master.Byte1.Byte)
//	{
//		;
//	}
	
	//第2字节
//	if (WiFi.MasterBak.Byte2.Byte != WiFi.Master.Byte2.Byte)
//	{
//		;
//	}

	//第3字节
	if (WiFi.Master.Byte3.MasterByte3.Buzzer)	//蜂鸣标志有效即有APP操作更新
	{
		if (System.Enum_Status == ENUM_STATUS_BUSSCHK)	//商检时接收到APP操作退出商检
		{
			Fan.f_SweepLR = Fan.f_SweepLRChkBak;
			Fan.f_SweepLRChkBak = 0;
			CommDisp.Tx.Byte5.var.SwLRType = (ENUM_SWLRTYPE)Fan.f_SweepLR;
			CommDisp.Rx.Byte5.var.SwLRType = (ENUM_SWLRTYPE)Fan.f_SweepLR;
			if (Fan.f_SweepLR == 0)	//原来状态是没有开启摇头需恢复到原来默认打开角度
			{
				StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ON;
				Swing.u16_anglebak = C_STEPMOTOR_ANGLE_DEFAULT;
			}
						
			UVC.f_FuncOn = UVC.f_FuncOnBak;
			UVC.f_FuncOnBak = 0;
			CommDisp.Tx.Byte18.var.UVC = (ENUM_FLAG)UVC.f_FuncOn;
			CommDisp.Rx.Byte11.var.UVC = (ENUM_FLAG)UVC.f_FuncOn;
						
			WiFi.f_FuncOn = WiFi.f_FuncOnBak;
			WiFi.f_FuncOnBak = 0;
			CommDisp.Tx.Byte17.var.WifiPower = (ENUM_FLAG)WiFi.f_FuncOn;
			CommDisp.Rx.Byte11.var.WifiPower = (ENUM_FLAG)WiFi.f_FuncOn;
			
			System.Enum_Status = ENUM_STATUS_ON;
		}
		
		
		
//		if (WiFi.MasterBak.Byte3.Byte != WiFi.Master.Byte3.Byte)
//		{		
			if (WiFi.Master.Byte3.MasterByte3.OnOff)	
			{
				if (System.Enum_Status == ENUM_STATUS_OFF)
				{
					DisplayBoardTurnOn();	//开机
					
				}
			}
			else										
			{	
				if (System.Enum_Status == ENUM_STATUS_ON)
				{
					DisplayBoardTurnOff();	//关机
				}
			}
			
//		}
		
		//第4字节
//		if (WiFi.MasterBak.Byte4.Byte != WiFi.Master.Byte4.Byte)
//		{		
			temp = 0;
			
			switch (WiFi.Master.Byte4.MasterByte4.ModeSet)
			{
				case	ENUM_WIFIMMODESET_HEAT:    //制热
				{
					if (System.Mode != ENUM_SYSMODE_HEAT)
					{
						System.Mode = ENUM_SYSMODE_HEAT;		//制热
						temp = 1;
					}
				}break;
				
				case	ENUM_WIFIMMODESET_HUMI:    //除湿
				{
					if (System.Mode != ENUM_SYSMODE_HUM)
					{
						System.Mode = ENUM_SYSMODE_HUM;			//除湿
						temp = 1;
					}						
				}break;
				
				case	ENUM_WIFIMMODESET_COLD:    //制冷
				{
					if (System.Mode != ENUM_SYSMODE_COLD)
					{
						System.Mode = ENUM_SYSMODE_COLD;		//制冷	
						temp = 1;
					}						
				}break;
				
				case	ENUM_WIFIMMODESET_INTE:    //智能
				{
					if (System.Mode != ENUM_SYSMODE_INTE) 
					{
						System.Mode = ENUM_SYSMODE_INTE;        //智能 
						temp = 1;
					}
				}break;
				
				case	ENUM_WIFIMMODESET_FAN :    //送风
				{
					if (System.Mode != ENUM_SYSMODE_FAN)
					{
						System.Mode = ENUM_SYSMODE_FAN;  		//送风
						temp = 1;
					}
				}break;
				
				default: break;
			
			}
			
			if (temp)
			{
				
				Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_INIT;		//操作模式,重新计算温差区域
				Tempr.T1TSDeltaZoneBak = ENUM_TEMPDELTAZONE_INIT;	//操作模式,重新计算温差区域
				
				//模式标志重新判定
				SystemMode.f_Cold = 0;		
				SystemMode.f_Heat = 0;
				SystemMode.f_Fan = 0;
				SystemMode.f_Auto = 0;
				
				SystemMode.f_TempCEC = 0;							//操作模式,达温标志清除			
				SystemMode.f_Sleep = 0;								//操作模式,退出睡眠
				SystemMode.f_Force = 0;								//操作模式,退出强力模式 lcx add 20240715
				if (System.Mode == ENUM_SYSMODE_HUM)
				{
					//进入除湿模式计算设定温度:    ST = T1 - 2
					if (T1.s8_Value < 18)
					{				
						Tempr.u8_HumiCSet = 16;	//最低
					}
					else if (T1.s8_Value > 34)
					{
						Tempr.u8_HumiCSet = 32;	//最高
					}
					else
					{
						Tempr.u8_HumiCSet = T1.s8_Value - 2;
					}
				}
				else
				{
					Tempr.u8_HumiCSet = 24;	//默认
				}
			}			
			
			
//		}
		
//		//第5字节	
//		if (WiFi.MasterBak.Byte5.Byte != WiFi.Master.Byte5.Byte)
//		{
			temp = 32 - WiFi.Master.Byte5.MasterByte5.TempSet;
			
			if(temp != Tempr.u8_TempCSet)
			{
				SystemMode.f_Force = 0;		//操作温度,退出强力模式 lcx add 20240715
			}
			
			Tempr.u8_TempCSet = 32 - WiFi.Master.Byte5.MasterByte5.TempSet;
			if (Tempr.u8_TempCSet > 32)		Tempr.u8_TempCSet = 32;
			if (Tempr.u8_TempCSet < 13)		Tempr.u8_TempCSet = 13;
			
			if (SystemMode.f_Sleep)
			{
				Tempr.u8_TempCSetSleep = Tempr.u8_TempCSet;
			}
			
			//add code...//状态变化相关参数处理
			if (System.Mode == ENUM_SYSMODE_COLD)
			{
				Tempr.u8_ColdCSet = Tempr.u8_TempCSet;
			}
			
			if (System.Mode == ENUM_SYSMODE_HEAT)
			{
				Tempr.u8_HeatCSet = Tempr.u8_TempCSet;
			}
		
			System.u32_SleepCount = 0;			
//		}
//		
//		//第6字节
//		if (WiFi.MasterBak.Byte6.Byte != WiFi.Master.Byte6.Byte)
//		{
			temp = 0;
			
			switch (WiFi.Master.Byte6.MasterByte6.WindSpeed)
			{
				case	ENUM_WIFIWINDSPEED_AUTO:		//自动
				{
					if (Fan.Mode != ENUM_FANMODE_AUTO)
					{
						temp = 1;
					}
					
					Fan.Mode = ENUM_FANMODE_AUTO;
				}break;
				
				case	ENUM_WIFIWINDSPEED_LOW :		//低速
				{
					if (Fan.Mode != ENUM_FANMODE_LOW)
					{
						temp = 1;
					}
					
					Fan.Mode = ENUM_FANMODE_LOW;
				}break;
				
				case	ENUM_WIFIWINDSPEED_MED :		//中速
				{
					if (Fan.Mode != ENUM_FANMODE_MED)
					{
						temp = 1;
					}
					
					Fan.Mode = ENUM_FANMODE_MED;
				}break;
				
				case	ENUM_WIFIWINDSPEED_HIGH:		//高速
				{
					if (Fan.Mode != ENUM_FANMODE_HIGH)
					{
						temp = 1;
					}	

					Fan.Mode = ENUM_FANMODE_HIGH;
				}break;
				
				case	ENUM_WIFIWINDSPEED_SILENCE:		//静音	
				{
				
				}break;
				
				default: break;
			}
			
			if (temp)
			{
				SystemMode.f_TempCEC = 0;					//操作风速,达温标志清除
				SystemMode.f_Sleep = 0;						//操作风速,退出睡眠
				SystemMode.f_Force = 0;						//操作风速,退出强力模式 lcx add 20240715
				Fan.u2_AutoInitFdCount = 0;
			}
			
			if (WiFi.Master.Byte6.MasterByte6.UDSweep == ENUM_WIFIUDSWEEP_ENABLE)	Fan.f_SweepLR = 1;
			else																	Fan.f_SweepLR = 0;
			
//		}

//		//第15字节
//		if (WiFi.MasterBak.Byte15.Byte != WiFi.Master.Byte15.Byte)
//		{
			temp = 0;
			
			if (WiFi.Master.Byte15.MasterByte15.SleepMode == ENUM_SLEEPMODE_NULL)
			{
				if (SystemMode.f_Sleep)
				{
					temp = 1;
				}
				
				SystemMode.f_Sleep = 0;
			}
			else
			{
				if (SystemMode.f_Sleep == 0)
				{
					temp = 1;
				}
				
				SystemMode.f_Sleep = 1;
			}
			
			if (temp)
			{
				if (SystemMode.f_Sleep)	//开启睡眠			
				{								
			
					//睡眠模式下记录
					Tempr.u8_TempCSetSleep = CommDisp.Rx.Byte7.Byte;		//设定温度值
					Tempr.u8_TempFSetSleep = CommDisp.Rx.Byte10.Byte;		//设定温度华氏								
				}
				else					//关闭睡眠											
				{								
					
					//退出睡眠模式下记录退出
					Tempr.u8_TempCSet = Tempr.u8_TempCSetSleep;				
					Tempr.u8_TempFSet = Tempr.u8_TempFSetSleep;				
					Tempr.u8_TempCSetSleep = 0;
					Tempr.u8_TempFSetSleep = 0;				
				}
				
				//add code...//状态变化相关参数处理
				SystemMode.f_TempCEC = 0;				//操作睡眠,达温标志清除
				SystemMode.f_Force = 0;					//操作模式,退出强力模式 lcx add 20240715
				System.u32_SleepCount = 0;				//睡眠持续时间重新计时
				System.u32_SleepTimCount = 0;			//睡眠定时时间重新计时
				Fan.ModeBak = ENUM_FANMODE_INIT;		//风速重新判定	
			}
			else
			{
				Tempr.u8_TempFSet = App_TCLModule_CtoF(Tempr.u8_TempCSet, WiFi.Master.Byte7.MasterByte7.TempFSetAdd1);			
			}
//		}



			
//		//第7字节
//		if (WiFi.MasterBak.Byte7.Byte != WiFi.Master.Byte7.Byte)
//		{
//			Tempr.u8_TempFSet = App_TCLModule_CtoF(Tempr.u8_TempCSet, WiFi.Master.Byte7.MasterByte7.TempFSetAdd1);
			
			if (SystemMode.f_Sleep)
			{
				Tempr.u8_TempFSetSleep = Tempr.u8_TempFSet;
			}
			
			if (WiFi.Master.Byte7.MasterByte7.LRSweep)		Fan.f_SweepLR = 1;
			else											Fan.f_SweepLR = 0;
//		}
//		
//		//第8字节
//		if (WiFi.MasterBak.Byte8.Byte != WiFi.Master.Byte8.Byte)
//		{

			Tempr.f_TempUnit = WiFi.Master.Byte8.MasterByte8.TempUnit;
//		}
//		
//		//第9字节
//		if (WiFi.MasterBak.Byte9.Byte != WiFi.Master.Byte9.Byte)
//		{
//		
//		}
//		
//		//第10字节
//		if (WiFi.MasterBak.Byte10.Byte != WiFi.Master.Byte10.Byte)
//		{
//		
//		}
//		
//		//第11字节
//		if (WiFi.MasterBak.Byte11.Byte != WiFi.Master.Byte11.Byte)
//		{
//		
//		}
//		
//		//第12字节
//		if (WiFi.MasterBak.Byte12.Byte != WiFi.Master.Byte12.Byte)
//		{
//		
//		}
//		
//		//第13字节
//		if (WiFi.MasterBak.Byte13.Byte != WiFi.Master.Byte13.Byte)
//		{
//		
//		}
//		
//		//第14字节
//		if (WiFi.MasterBak.Byte14.Byte != WiFi.Master.Byte14.Byte)
//		{
//		
//		}
//		

//		
//		//第16字节
//		if (WiFi.MasterBak.Byte16.Byte != WiFi.Master.Byte16.Byte)
//		{
//			Tempr.u8_TempFSet = App_TCLModule_CtoF(Tempr.u8_TempCSet, WiFi.Master.Byte16.MasterByte16.TempFSetAdd1);
//		}
//		
//		//第17字节
//		if (WiFi.MasterBak.Byte17.Byte != WiFi.Master.Byte17.Byte)
//		{
//		
//		}
//		
//		//第18字节
//		if (WiFi.MasterBak.Byte18.Byte != WiFi.Master.Byte18.Byte)
//		{
//		
//		}
//		
//		//第19字节
//		if (WiFi.MasterBak.Byte19.Byte != WiFi.Master.Byte19.Byte)
//		{
//		
//		}
//		
//		//第20字节
//		if (WiFi.MasterBak.Byte20.Byte != WiFi.Master.Byte20.Byte)
//		{
//		
//		}
//		
//		//第21字节
//		if (WiFi.MasterBak.Byte21.Byte != WiFi.Master.Byte21.Byte)
//		{
//		
//		}
//		
//		//第22字节
//		if (WiFi.MasterBak.Byte22.Byte != WiFi.Master.Byte22.Byte)
//		{
//		
//		}
//		
//		//第23字节
//		if (WiFi.MasterBak.Byte23.Byte != WiFi.Master.Byte23.Byte)
//		{
//		
//		}
//		
//		//第24字节
//		if (WiFi.MasterBak.Byte24.Byte != WiFi.Master.Byte24.Byte)
//		{
//		
//		}
//		
//		//第25字节
//		if (WiFi.MasterBak.Byte25.Byte != WiFi.Master.Byte25.Byte)
//		{
//		
//		}
//		
//		//第26字节
//		if (WiFi.MasterBak.Byte26.Byte != WiFi.Master.Byte26.Byte)
//		{
//		
//		}
//		
//		//第27字节
//		if (WiFi.MasterBak.Byte27.Byte != WiFi.Master.Byte27.Byte)
//		{
//		
//		}

		
		WiFi.Master.Byte3.MasterByte3.Buzzer = 0;
		CommDisp.f_CmdInBakSync = 0;						//重新同步显示板标志备份
	}
	
	//-------------------------------------------------------------------//
	
	//同步备份
//	WiFi.MasterBak.Byte1.Byte = WiFi.Master.Byte1.Byte;
//	WiFi.MasterBak.Byte2.Byte = WiFi.Master.Byte2.Byte;
//	WiFi.MasterBak.Byte3.Byte = WiFi.Master.Byte3.Byte;
//	WiFi.MasterBak.Byte4.Byte = WiFi.Master.Byte4.Byte;
//	WiFi.MasterBak.Byte5.Byte = WiFi.Master.Byte5.Byte;
//	WiFi.MasterBak.Byte6.Byte = WiFi.Master.Byte6.Byte;
//	WiFi.MasterBak.Byte7.Byte = WiFi.Master.Byte7.Byte;
//	WiFi.MasterBak.Byte8.Byte = WiFi.Master.Byte8.Byte;
//	WiFi.MasterBak.Byte9.Byte = WiFi.Master.Byte9.Byte;
//	WiFi.MasterBak.Byte10.Byte = WiFi.Master.Byte10.Byte;
//	WiFi.MasterBak.Byte11.Byte = WiFi.Master.Byte11.Byte;
//	WiFi.MasterBak.Byte12.Byte = WiFi.Master.Byte12.Byte;
//	WiFi.MasterBak.Byte13.Byte = WiFi.Master.Byte13.Byte;
//	WiFi.MasterBak.Byte14.Byte = WiFi.Master.Byte14.Byte;
//	WiFi.MasterBak.Byte15.Byte = WiFi.Master.Byte15.Byte;
//	WiFi.MasterBak.Byte16.Byte = WiFi.Master.Byte16.Byte;
//	WiFi.MasterBak.Byte17.Byte = WiFi.Master.Byte17.Byte;
//	WiFi.MasterBak.Byte18.Byte = WiFi.Master.Byte18.Byte;
//	WiFi.MasterBak.Byte19.Byte = WiFi.Master.Byte19.Byte;
//	WiFi.MasterBak.Byte20.Byte = WiFi.Master.Byte20.Byte;
//	WiFi.MasterBak.Byte21.Byte = WiFi.Master.Byte21.Byte;
//	WiFi.MasterBak.Byte22.Byte = WiFi.Master.Byte22.Byte;
//	WiFi.MasterBak.Byte23.Byte = WiFi.Master.Byte23.Byte;
//	WiFi.MasterBak.Byte24.Byte = WiFi.Master.Byte24.Byte;
//	WiFi.MasterBak.Byte25.Byte = WiFi.Master.Byte25.Byte;
//	WiFi.MasterBak.Byte26.Byte = WiFi.Master.Byte26.Byte;
//	WiFi.MasterBak.Byte27.Byte = WiFi.Master.Byte27.Byte;

}
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
U8	App_TCLModule_CtoF(U8 tempcset, U8 Fadd1)
{
	U8 tempfset;
	
	if (tempcset < 13)	tempcset = 13;	//min
	if (tempcset > 32)	tempcset = 32;	//max
	
	switch (tempcset)
	{
		case	13:		tempfset = 55; break;
		case	14:		tempfset = 57; break;		
		case	15:		tempfset = 59; break;
		case	16:		tempfset = 61; break;		
		case	17:		tempfset = 63; break;
		case	18:		tempfset = 64; break;		
		case	19:		tempfset = 66; break;
		case	20:		tempfset = 68; break;
		case	21:		tempfset = 70; break;
		case	22:		tempfset = 72; break;		
		case	23:		tempfset = 73; break;
		case	24:		tempfset = 75; break;		
		case	25:		tempfset = 77; break;
		case	26:		tempfset = 79; break;		
		case	27:		tempfset = 81; break;
		case	28:		tempfset = 82; break;		
		case	29:		tempfset = 84; break;
		case	30:		tempfset = 86; break;
		case	31:		tempfset = 88; break;
		case	32:		tempfset = 89; break;
		
		default: tempfset = 72; break;
	}
	
	if (Fadd1)
	{
		tempfset += 1;
	}
	
	if (System.Mode == ENUM_SYSMODE_HEAT)		//制热:55F~81F
	{
		if (tempfset < 55)	tempfset = 55;
		if (tempfset > 81)	tempfset = 81;
	}
	else										//制冷:64F~90F	
	{
		if (tempfset < 64)	tempfset = 64;
		if (tempfset > 90)	tempfset = 90;
	}
	
	return tempfset;
}
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
U8	App_TCLModule_Fadd1(U8 tempfset)
{
	U8 Add1 = 0;
	
	if ((tempfset == 56) || (tempfset == 58) || (tempfset == 60) ||
		(tempfset == 62) || (tempfset == 65) || (tempfset == 67) ||
		(tempfset == 69) || (tempfset == 71) || (tempfset == 74) ||
		(tempfset == 76) || (tempfset == 78) || (tempfset == 80) ||
		(tempfset == 83) || (tempfset == 85) || (tempfset == 87) || (tempfset == 90))
	{
		Add1 = 1;
	}
	
	return Add1;
}
