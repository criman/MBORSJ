/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Func.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2022/03/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

/****************************************************************************************************
Function Name       :void Data_Init(void)
Description         :数据初始化
Input               :无
Return              :无
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Data_Init(void)
{
	Protect.s16_ErrCur = 130;
	SV.s16_OnTemp = 950;
	SV.s16_OffTemp = 850;

//	UserPara.s16L2 = 60;
	StepMotor.var.s16_SuperHeatTrg = 10;
	
	FtyPara.u16P1	=	6;
	FtyPara.u16P2	=	15;
	FtyPara.u16P3	=	15;
	FtyPara.u16P4	=	40;
	FtyPara.u16P5	=	15;
	FtyPara.u16P6	=	20;
	FtyPara.u16P7	=	15;
	FtyPara.u16P8	=	5;
	FtyPara.u16P9	=	3;
	FtyPara.u16P10  =	1;
	FtyPara.u16P11  =	3;
	FtyPara.u16P12  =	5;
	FtyPara.u16P13  =	160;
	FtyPara.u16P14  =	30;
	FtyPara.s16P15  =	5;
	FtyPara.s16P16  =	100;
	FtyPara.s16P17  =	50;
	FtyPara.s16P18  =	45;
	FtyPara.s16P19  =	95;
	FtyPara.s16P20  =	103;
	FtyPara.s16P21  =	85;
	FtyPara.s16P22  =	30;
	FtyPara.u16P23  =	5;
	FtyPara.s16P24  =	110;
	FtyPara.s16P25  =	85;
	FtyPara.s16P26  =	3;
	FtyPara.s16P27  =	7;
	FtyPara.u16P28  =	30;
	FtyPara.u16P29  =	60;
	FtyPara.u16F1	=	15;
	FtyPara.u16F2	=	35;
	FtyPara.u16F3	=	0;
	FtyPara.s16F4	=	0;
	FtyPara.u16L1	=	24;
	FtyPara.u16L2	=	5;
}


/****************************************************************************************************
Function Name       :void Init_MCU_Gpio(void)
Description         :初始化MCU端口
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Init_MCU_Gpio(void)
{
    GPIO_InitStruType    x;
	
    memset(&x, 0, sizeof(x));

	//add code..
//	Init_Pin_WP_Enable();
//	Module_Init_IICM();
	
	Module_Init_Ad();
	Module_Init_Switch();
	Module_Init_StepMotor();
	Module_Init_Uart();
	
//	Init_WPMotor();
	Init_FourWay();
//	Init_UVC();
//	Init_LowPower();
	Init_EAHeater();
	Init_Comp();
//	Init_DCFan();
//	Init_WiFiPowEn();
	
//	wifi_protocol_init();			//WIFI协议初始化	

//--------美博新增初始化----------
//	Init_InDoorFan();
	Init_OutDoorFan();
//	Init_SyncFan();
//	Init_SV();
//	InitPhaseSequence();
//--------美博新增初始化----------


//---------美博热水机--------------//
	Init_WFV();
	Init_Crank();
	Init_CirculationPump();
//---------美博热水机--------------//

}
/****************************************************************************************************
Function Name       :void Sys_Run_Per2ms(void)
Description         :系统2ms运行一次事件
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT_PER2MS
void	Sys_Run_Per2ms(void)
{
	#if (LVD_ENABLE == CF_ENABLE)
	LowVoltDetect();
	#endif	
	
	Log_Ad();
	App_Switch();
	Log_StepMotor();
	

}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func1_Per10ms(void)
Description         :系统10ms运行一次事件一
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT01_PER10MS
void	Sys_Run_Func1_Per10ms(void)
{
	#if defined		UART0_ENABLE
	Uart0_SendPackDeal();
	#endif

	#if defined		UART1_ENABLE
	Uart1_SendPackDeal();
	#endif
	
	#if defined		UART2_ENABLE		
	Uart2_SendPackDeal();		
	#endif	
	
	#if defined		UART3_ENABLE	
	Uart3_SendPackDeal();	
	#endif
	
	#if defined		UART4_ENABLE
	Uart4_SendPackDeal();
	#endif
}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func2_Per10ms(void)
Description         :系统10ms运行一次事件二
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT02_PER10MS
void	Sys_Run_Func2_Per10ms(void)
{		


//	DisplayBoardCommandCheck();    	//判定显示板有命令送达
//	
//	DisplayBoardCommandUpdate();    //更新信息发送给显示板
//	
//	App_TCLModule_Master_Info();	//模组发送数据给底板	
//
//	App_TCLModule_Slave_Info();		//底板发送数据给模组
}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func3_Per10ms(void)
Description         :系统10ms运行一次事件三
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT03_PER10MS
void	Sys_Run_Func3_Per10ms(void)
{
	App_LookUpTemperature();
	App_StepMotor_Run();
}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func4_Per10ms(void)
Description         :系统10ms运行一次事件四
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT04_PER10MS
void	Sys_Run_Func4_Per10ms(void)
{
	App_Function();

}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func1_Per100ms(void)
Description         :系统100ms运行一次事件一
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT01_PER100MS
void	Sys_Run_Func1_Per100ms(void)
{
	#if defined		UART0_ENABLE
	static U8 Uart0TXCount;
	if (++Uart0TXCount >= 10)
	{		
		Uart0TXCount = 0;
//		App_Uart0_Write_Frame();
		P_Uart0_En_Hi();
		
//		UART_SendByte(UART0, 0x55);     //首个字节送入串口发送缓存
//		UART_ITConfig(UART0, UART_IT_TB, ENUM_ENABLE);    //发送有效
	}
	
//	App_Uart0_Read_Frame();
	
	#endif
}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func2_Per100ms(void)
Description         :系统100ms运行一次事件二
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT02_PER100MS
void	Sys_Run_Func2_Per100ms(void)
{
	#if defined		UART4_ENABLE
	
	static U8 Uart4TXCount;
	
	if (++Uart4TXCount >= 2)
	{		
		Uart4TXCount = 0;
		App_Uart4_Write_Frame();
	}
	
	App_Uart4_Read_Frame();
	
	#endif
}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func3_Per100ms(void)
Description         :系统100ms运行一次事件三
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT03_PER100MS
void	Sys_Run_Func3_Per100ms(void)
{
	CommMotDrv_InfoCon();	//主控芯片与电机驱动芯片通信

}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func4_Per100ms(void)
Description         :系统100ms运行一次事件四
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT04_PER100MS
void	Sys_Run_Func4_Per100ms(void)
{
	#if defined		UART3_ENABLE
	
	static U8 Uart3TXCount;
	//上位机通信
	if (++Uart3TXCount >= 5)
	{
		Uart3TXCount = 0;
		App_Uart3_Write_Frame();
		
	}
	
	App_Uart3_Read_Frame();
	
	#endif
}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func5_Per100ms(void)
Description         :系统100ms运行一次事件五
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT05_PER100MS
void	Sys_Run_Func5_Per100ms(void)
{
//	App_UartAPI();												//底板上报信息
//	wifi_uart_service();
//	
//	WiFi.u8_Status = mcu_get_wifi_work_state();

#if defined		UART2_ENABLE
	if (F_switch_sw5_old)
	{
		App_Uart2_Read_Frame();	
		App_Uart2_Write_Frame();
	}
#endif 

	SaveDatToEEP(); //lcx add 20240510
	Remember_EE_Dat_Init();

}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func6_Per100ms(void)
Description         :系统100ms运行一次事件六
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT06_PER100MS
void	Sys_Run_Func6_Per100ms(void)
{

}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func7_Per100ms(void)
Description         :系统100ms运行一次事件七
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT07_PER100MS
void	Sys_Run_Func7_Per100ms(void)
{

}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func8_Per100ms(void)
Description         :系统100ms运行一次事件八
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT08_PER100MS
void	Sys_Run_Func8_Per100ms(void)
{

}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func9_Per100ms(void)
Description         :系统100ms运行一次事件九
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT09_PER100MS
void	Sys_Run_Func9_Per100ms(void)
{

}
#endif
/****************************************************************************************************
Function Name       :void Sys_Run_Func10_Per100ms(void)
Description         :系统100ms运行一次事件十
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if		defined		SYS_RUN_EVENT10_PER100MS
void	Sys_Run_Func10_Per100ms(void)
{

}
#endif
