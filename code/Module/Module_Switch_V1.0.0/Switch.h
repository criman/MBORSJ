/*===================================================================================================
                		Copyright(C) 2011-2099.  SunRam. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Switch.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2022/03/22
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 


#ifndef			_SWITCH_H

#define			_SWITCH_H

//===================================================================================================//
//选择SWITCH1控制端口
//---------------------------------------------------------------------------------------------------//
#define		SWITCH1_ENABLE						//使用打开/不使用屏蔽
//---------------------------------------------------------------------------------------------------//
#define		Switch1SigValid						1//SWITCH1开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_switch1							PortPin_Read(GPIOA, GPIO_Pin_9)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_Switch1_Hi()						DEFINE_PA9_HI					//例子:DEFINE_P00_HI
#define		P_Switch1_Low()						DEFINE_PA9_LOW					//例子:DEFINE_P00_LOW
#define		P_Switch1_Output()					DEFINE_PA9_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Switch1_Input()					DEFINE_PA9_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Switch1_Enpull()					DEFINE_PA9_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_Switch1_Dispull()					DEFINE_PA9_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//选择SWITCH2控制端口
//---------------------------------------------------------------------------------------------------//
#define		SWITCH2_ENABLE						//使用打开/不使用屏蔽
//---------------------------------------------------------------------------------------------------//
#define		Switch2SigValid						1//SWITCH2开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_switch2							PortPin_Read(GPIOA, GPIO_Pin_10)//SWITCH2 IO端口选择			例子:P00/P0_0										
#define		P_Switch2_Hi()						DEFINE_PA10_HI					//例子:DEFINE_P00_HI
#define		P_Switch2_Low()						DEFINE_PA10_LOW					//例子:DEFINE_P00_LOW
#define		P_Switch2_Output()					DEFINE_PA10_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Switch2_Input()					DEFINE_PA10_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Switch2_Enpull()					DEFINE_PA10_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_Switch2_Dispull()					DEFINE_PA10_DISPULLUP		    //例子:DEFINE_P00_DISPULL
//===================================================================================================//
//选择SWITCH3控制端口
//---------------------------------------------------------------------------------------------------//
#define		SWITCH3_ENABLE						//使用打开/不使用屏蔽
//---------------------------------------------------------------------------------------------------//
#define		Switch3SigValid						1//SWITCH3开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_switch3							PortPin_Read(GPIOA, GPIO_Pin_11)//SWITCH3 IO端口选择			例子:P00/P0_0										
#define		P_Switch3_Hi()						DEFINE_PA11_HI					//例子:DEFINE_P00_HI
#define		P_Switch3_Low()						DEFINE_PA11_LOW					//例子:DEFINE_P00_LOW
#define		P_Switch3_Output()					DEFINE_PA11_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Switch3_Input()					DEFINE_PA11_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Switch3_Enpull()					DEFINE_PA11_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_Switch3_Dispull()					DEFINE_PA11_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//选择SWITCH4控制端口
//---------------------------------------------------------------------------------------------------//
#define		SWITCH4_ENABLE						//使用打开/不使用屏蔽
//---------------------------------------------------------------------------------------------------//
#define		Switch4SigValid						1//SWITCH4开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_switch4							PortPin_Read(GPIOA, GPIO_Pin_12)//SWITCH4 IO端口选择			例子:P00/P0_0										
#define		P_Switch4_Hi()						DEFINE_PA12_HI					//例子:DEFINE_P00_HI
#define		P_Switch4_Low()						DEFINE_PA12_LOW					//例子:DEFINE_P00_LOW
#define		P_Switch4_Output()					DEFINE_PA12_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Switch4_Input()					DEFINE_PA12_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Switch4_Enpull()					DEFINE_PA12_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_Switch4_Dispull()					DEFINE_PA12_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//选择SWITCH5控制端口
//---------------------------------------------------------------------------------------------------//
#define		SWITCH5_ENABLE						//使用打开/不使用屏蔽
//---------------------------------------------------------------------------------------------------//
#define		Switch5SigValid						1//SWITCH5开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_switch5							PortPin_Read(GPIOA, GPIO_Pin_15)//SWITCH5 IO端口选择			例子:P00/P0_0										
#define		P_Switch5_Hi()						DEFINE_PA15_HI					//例子:DEFINE_P00_HI
#define		P_Switch5_Low()						DEFINE_PA15_LOW					//例子:DEFINE_P00_LOW
#define		P_Switch5_Output()					DEFINE_PA15_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Switch5_Input()					DEFINE_PA15_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Switch5_Enpull()					DEFINE_PA15_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_Switch5_Dispull()					DEFINE_PA15_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//选择SWITCH6控制端口
//---------------------------------------------------------------------------------------------------//
#define		SWITCH6_ENABLE						//使用打开/不使用屏蔽
//---------------------------------------------------------------------------------------------------//
#define		Switch6SigValid						1//SWITCH6开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_switch6							PortPin_Read(GPIOA, GPIO_Pin_16)//SWITCH6 IO端口选择			例子:P00/P0_0										
#define		P_Switch6_Hi()						DEFINE_PA16_HI					//例子:DEFINE_P00_HI
#define		P_Switch6_Low()						DEFINE_PA16_LOW					//例子:DEFINE_P00_LOW
#define		P_Switch6_Output()					DEFINE_PA16_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Switch6_Input()					DEFINE_PA16_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Switch6_Enpull()					DEFINE_PA16_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_Switch6_Dispull()					DEFINE_PA16_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//选择SWITCH7控制端口
//---------------------------------------------------------------------------------------------------//
//#define		SWITCH7_ENABLE						//使用打开/不使用屏蔽
//---------------------------------------------------------------------------------------------------//
#define		Switch7SigValid						0//SWITCH7开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_switch7							PortPin_Read(GPIOA, GPIO_Pin_0)//SWITCH7 IO端口选择			例子:P00/P0_0										
#define		P_Switch7_Hi()						DEFINE_PA0_HI					//例子:DEFINE_P00_HI
#define		P_Switch7_Low()						DEFINE_PA0_LOW					//例子:DEFINE_P00_LOW
#define		P_Switch7_Output()					DEFINE_PA0_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Switch7_Input()					DEFINE_PA0_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Switch7_Enpull()					DEFINE_PA0_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_Switch7_Dispull()					DEFINE_PA0_DISPULLUP			//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//选择SWITCH8控制端口
//---------------------------------------------------------------------------------------------------//
//#define		SWITCH8_ENABLE						//使用打开/不使用屏蔽
//---------------------------------------------------------------------------------------------------//
#define		Switch8SigValid						0//SWITCH8开关IO端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_switch8							PortPin_Read(GPIOA, GPIO_Pin_0)//SWITCH8 IO端口选择			例子:P00/P0_0										
#define		P_Switch8_Hi()						DEFINE_PA0_HI					//例子:DEFINE_P00_HI
#define		P_Switch8_Low()						DEFINE_PA0_LOW					//例子:DEFINE_P00_LOW
#define		P_Switch8_Output()					DEFINE_PA0_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_Switch8_Input()					DEFINE_PA0_INPUT				//例子:DEFINE_P00_INPUT
#define		P_Switch8_Enpull()					DEFINE_PA0_ENPULLUP				//例子:DEFINE_P00_ENPULL
#define		P_Switch8_Dispull()					DEFINE_PA0_DISPULLUP		    //例子:DEFINE_P00_DISPULL

//---------------------------------------------------------------------------------------------------//
#define		C_SWITCH_SCAN_NUM					6			//信号瞬间持续同一电平确认次数
#define		C_SWITCH_ENABLE_FD					10		    //有效信号防抖次数
#define		C_SWITCH_DISABLE_FD					10		    //无效信号防抖次数
//-------------------------------------------------------------------------------------------//
typedef struct 	   			/*定义字节、位寻址结构*/
{		
	unsigned char b0:1;
	unsigned char b1:1;
	unsigned char b2:1;
	unsigned char b3:1;
	unsigned char b4:1;
	unsigned char b5:1;
	unsigned char b6:1;
	unsigned char b7:1;
}STRUCT_SWITCHBYTE;

extern	STRUCT_SWITCHBYTE	SwitchFlag1;	
#define						F_switch_sw1_old				SwitchFlag1.b0		// bit0	
#define						F_switch_sw2_old				SwitchFlag1.b1		// bit1	
#define						F_switch_sw3_old				SwitchFlag1.b2		// bit2	
#define						F_switch_sw4_old				SwitchFlag1.b3		// bit3	
#define						F_switch_sw5_old				SwitchFlag1.b4		// bit4	
#define						F_switch_sw6_old				SwitchFlag1.b5		// bit5	
#define						F_switch_sw7_old				SwitchFlag1.b6		// bit6	
#define						F_switch_sw8_old				SwitchFlag1.b7		// bit7	

#define	LowPress			F_switch_sw1_old				
#define	HighPress			F_switch_sw2_old					
#define	WaterFlow			F_switch_sw3_old					
#define	LowWaterLevel		F_switch_sw4_old				
#define	MidWaterLevel		F_switch_sw5_old				
#define	HighWaterLevel		F_switch_sw6_old					
//#define						F_switch_sw7_old				
//#define						F_switch_sw8_old				

//-------------------------------------------------------------------------------------------//

/****************************************************************************************************
Function Name       :void Module_Init_Switch(void)
Description         :初始化开关检测IO配置
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern	void	Module_Init_Switch(void);
/****************************************************************************************************
Function Name       :void App_Switch(void)
Description         :开关检测
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern	void	App_Switch(void);

#endif
