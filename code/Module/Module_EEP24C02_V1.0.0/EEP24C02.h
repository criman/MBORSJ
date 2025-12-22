/*===================================================================================================
                		Copyright(C) 2011-2099.  SUMRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: IICMIO.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023-01-10
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/

#ifndef			_IICMIO_H_

#define			_IICMIO_H_


//===================================================================================================//
//模拟IIC控制SCL引脚IO配置
//---------------------------------------------------------------------------------------------------//
#define			Pin_IICM_SCL					PB8//SCL IO端口选择			例子:P00/P0_0
#define			P_IICM_SCL_H()					DEFINE_PB8_HI				//例子:DEFINE_P00_HI
#define			P_IICM_SCL_L()					DEFINE_PB8_LOW				//例子:DEFINE_P00_LOW
#define			P_IICM_SCL_OUT()				DEFINE_PB8_OUTPUT			//例子:DEFINE_P00_OUTPUT
#define			P_IICM_SCL_IN()					DEFINE_PB8_INPUT			//例子:DEFINE_P00_INPUT
#define         P_IICM_SCL_ENPULL()             DEFINE_PB8_ENPULLUP		//例子:DEFINE_P00_ENPULL
#define         P_IICM_SCL_DISPULL()            DEFINE_PB8_DISPULLUP		//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//模拟IIC控制SDA引脚IO配置
//---------------------------------------------------------------------------------------------------//
#define			Pin_IICM_SDA					PB9//SCL IO端口选择			例子:P00/P0_0
#define			P_IICM_SDA_H()					DEFINE_PB9_HI				//例子:DEFINE_P00_HI
#define			P_IICM_SDA_L()					DEFINE_PB9_LOW				//例子:DEFINE_P00_LOW
#define			P_IICM_SDA_OUT()				DEFINE_PB9_OUTPUT			//例子:DEFINE_P00_OUTPUT
#define			P_IICM_SDA_IN()					DEFINE_PB9_INPUT			//例子:DEFINE_P00_INPUT
#define			P_IICM_SDA_ENPULL()				DEFINE_PB9_ENPULLUP		//例子:DEFINE_P00_ENPULL
#define			P_IICM_SDA_DISPULL()            DEFINE_PB9_DISPULLUP		//例子:DEFINE_P00_DISPULL
//===================================================================================================//
//从机地址和ID命令
//---------------------------------------------------------------------------------------------------//
#define			SLAVE_ADDR						0xA0						//设备地址命令
//===================================================================================================//
//SCL,SDA电平维持时间需大于4.7us
#define 		C_IICM_DELAY 					5 						    //如果指令周期1us,那么电平维持时间10us  
//===================================================================================================//

//===================================================================================================//
//以下宏定义无需修改参数
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
#define			Read_SDA() 								(PortPin_Read(GPIOB, GPIO_Pin_9))
//---------------------------------------------------------------------------------------------------//
//===================================================================================================//

//---------------------------------------------------------------------------------------------------//

typedef    enum
{
	ENUM_STEP_IDLE,			//空闲
	ENUM_STEP_WR,			//写阶段
	ENUM_STEP_RD,			//读阶段
	ENUM_STEP_OK,			//读写相同退出
}ENUM_STEP;

//---------------------------------------------------------------------------------------------------//
#ifndef EEP_PARA_TOTAL_LEN
/* 如果上层未定义 EEP_PARA_TOTAL_LEN，则默认适配为 240 字节（包含头码与校验两字节）
 * 注意：EEPROM 24C02 总容量 256 字节，若参数区从地址 16 开始，最大可用长度为 240 字节（0x10..0xFF） */
#define EEP_PARA_TOTAL_LEN    240
#endif
typedef    struct
{
	ENUM_STEP    Step;
	U8  		 f_1ms		 		 :1;	//1ms中断标志
	U8			 u7_Count            :7;	//计时范围 0-127
	U8  		 u8_wrBuf[EEP_PARA_TOTAL_LEN + 16];				//写缓存
	U8			 u8_rdBuf[EEP_PARA_TOTAL_LEN + 16];				//读缓存
}STRUCT_EEP;

//---------------------------------------------------------------------------------------------------//

extern    STRUCT_EEP    EEP;

/****************************************************************************************************
Function Name       :void Module_Init_IICM(void)
Description         :模拟iic初始化IO
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Module_Init_IICM(void);
/****************************************************************************************************
Function Name       :void    Write_24C02(U8 *addr_MCU, U8 Address, U8 DataCnt)
Description         :写入24C02数据
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Write_24C02(U8 *addr_MCU, U8 Address, U8 DataCnt);
/****************************************************************************************************
Function Name       :void    Read_24C02(U8 *addr_MCU, U8 Address, U8 DataCnt)
Description         :读取24C02数据
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Read_24C02(U8 *addr_MCU, U8 Address, U8 DataCnt);

#endif
