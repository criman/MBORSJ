/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Init_ES8H018X_EX8H0163.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/08/04
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

/****************************************************************************************************
Function Name       :U8    PortPin_Read(GPIO_TYPE Port, GPIO_TYPE_PIN Pin)
Description         :读取引脚电平
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    PortPin_Read(GPIO_TYPE Port, GPIO_TYPE_PIN Pin)
{
	return (GPIO_Read(Port) & (U32)1u << Pin)?1:0;
}
/****************************************************************************************************
Function Name       :void    ConfigIO_Output(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字输出
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_Output(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)						
{
    GPIO_InitStruType    x;
	
	x.GPIO_Signal = GPIO_Pin_Signal_Digital;	//数字信号引脚
	
	x.GPIO_Direction = GPIO_Dir_Out;			//输出
	
	GPIO_Init(GPIOx, PINx, &x);
}
/****************************************************************************************************
Function Name       :void    ConfigIO_Input(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字输入
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_Input(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)						
{
    GPIO_InitStruType    x;
	
	x.GPIO_Signal = GPIO_Pin_Signal_Digital;	//数字信号引脚
	
	x.GPIO_Direction = GPIO_Dir_In;				//输入
	
	GPIO_Init(GPIOx, PINx, &x);
}
/****************************************************************************************************
Function Name       :void    ConfigIO_PullUpEnable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字上拉有效
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_PullUpEnable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{
	GPIO_SetPUERegFromPin(GPIOx, PINx, GPIO_PUE_Input_Enable);	
}
/****************************************************************************************************
Function Name       :void    ConfigIO_PullUpDisable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字上拉禁止
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_PullUpDisable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{	
	GPIO_SetPUERegFromPin(GPIOx, PINx, GPIO_PUE_Input_Disable);
}
/****************************************************************************************************
Function Name       :void    ConfigIO_PullDownEnable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字下拉有效
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_PullDownEnable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{	
	GPIO_SetPDERegFromPin(GPIOx, PINx, GPIO_PDE_Input_Enable);	
}
/****************************************************************************************************
Function Name       :void    ConfigIO_PullDownDisable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字下拉禁止
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_PullDownDisable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{	
	GPIO_SetPDERegFromPin(GPIOx, PINx, GPIO_PDE_Input_Disable);	
}
/****************************************************************************************************
Function Name       :void    ConfigIO_OpenDrainEnable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字开漏有效
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_OpenDrainEnable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{	
	GPIO_SetODERegFromPin(GPIOx, PINx, GPIO_ODE_Output_Enable);
}
/****************************************************************************************************
Function Name       :void    ConfigIO_OpenDrainDisable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字开漏禁止
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_OpenDrainDisable(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{	
	GPIO_SetODERegFromPin(GPIOx, PINx, GPIO_ODE_Output_Disable);
}
/****************************************************************************************************
Function Name       :void    ConfigIO_OutputStrong(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字输出强电流
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_OutputStrong(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{	
	GPIO_SetDSRegFromPin(GPIOx, PINx, GPIO_DS_Output_Strong);
}
/****************************************************************************************************
Function Name       :void    ConfigIO_OutputNormal(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)	
Description         :配置IO端口数字输出普通电流
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    ConfigIO_OutputNormal(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{	
	GPIO_SetDSRegFromPin(GPIOx, PINx, GPIO_DS_Output_Normal);
}
/****************************************************************************************************
Function Name       :void    T16NxInit(void)
Description         :使用T16Nx定时
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void T16NxInit(void)
{
    TIM_BaseInitStruType x;

    x.TIM_ClkS = TIM_ClkS_PCLK;    	   //时钟源选择:PCLK
    x.TIM_SYNC = ENUM_DISABLE;		   //外部时钟同步-禁止
    x.TIM_EDGE = TIM_EDGE_Rise;	   	   //外部时钟计数边沿-上升沿
    x.TIM_Mode = TIM_Mode_TC0;	   	   //定时,计数模式

	#if (TIMER_T16N0_ENABLE == CF_ENABLE)
	
    T16Nx_BaseInit(T16N0, &x);	   								//配置初始化
	T16Nx_SetPREMAT(T16N0, 1);	   								//1分频
	T16Nx_SetMAT0(T16N0, 2000);    								//每125us中断一次
	NVIC_Init(NVIC_T16N0_IRQn, NVIC_Priority_1, ENUM_ENABLE);	//T16N0中断有效，优先级1
	T16Nx_MAT0ITConfig(T16N0, TIM_Clr_Int);						//中断自动清除计数值
	T16Nx_ITConfig(T16N0, TIM_IT_MAT0, ENUM_ENABLE);			//T16N0使用MAT0计数
	T16N0_Enable();												//T16N0使能工作
	
	#endif
	
	
	#if (TIMER_T16N1_ENABLE == CF_ENABLE)
	
	T16Nx_BaseInit(T16N1, &x);
	T16Nx_SetPREMAT(T16N1, 1);
	T16Nx_SetMAT0(T16N1, 32000);
	NVIC_Init(NVIC_T16N1_IRQn, NVIC_Priority_1, ENABLE);
	T16Nx_MAT0ITConfig(T16N1, TIM_Clr_Int);
	T16Nx_ITConfig(T16N1, TIM_IT_MAT0, ENABLE);
	T16N1_Enable();
	
	#endif
	
	
	#if (TIMER_T16N2_ENABLE == CF_ENABLE)
	
	T16Nx_BaseInit(T16N2, &x);
	T16Nx_SetPREMAT(T16N2, 1);
	T16Nx_SetMAT0(T16N2, 32000);
	NVIC_Init(NVIC_T16N2_IRQn, NVIC_Priority_1, ENABLE);
	T16Nx_MAT0ITConfig(T16N2, TIM_Clr_Int);
	T16Nx_ITConfig(T16N2, TIM_IT_MAT0, ENABLE);
	T16N2_Enable();
	
	#endif	

	
	#if (TIMER_T16N3_ENABLE == CF_ENABLE)
	
	T16Nx_BaseInit(T16N3, &x);
	T16Nx_SetPREMAT(T16N3, 1);
	T16Nx_SetMAT0(T16N3, 32000);
	NVIC_Init(NVIC_T16N3_IRQn, NVIC_Priority_1, ENABLE);
	T16Nx_MAT0ITConfig(T16N3, TIM_Clr_Int);
	T16Nx_ITConfig(T16N3, TIM_IT_MAT0, ENABLE);
	T16N3_Enable();
	
	#endif	
	
}
/****************************************************************************************************
Function Name       :void    LowVoltDetect_Init(void)
Description         :初始化低电压检测配置
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if (LVD_ENABLE == CF_ENABLE)
void    LowVoltDetect_Init(void)
{	
    SCU_RegUnLock();

    NVIC_Init(NVIC_CCM_LVD_PLK_IRQn, NVIC_Priority_0, ENUM_ENABLE);  //中断设置
    SCU_LVDVS_4V0();
    SCU_LVDIFS_Fall();
    SCU_LVDFLT_Enable();
    SCU_LVD_Enable();
    Delay100us(5);
    SCU_LVDIT_Enable();

    SCU_RegLock();
}
#endif
/****************************************************************************************************
Function Name       :void    Init_MCU_System(void)
Description         :初始化MCU系统配置
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_MCU_System(void)
{
    SystemHRCSelect(SCU_HRC_16M);       //HRC选择16MHz
    SystemClockConfig();                //配置时钟
    DeviceClockAllEnable();             //打开所有外设时钟

    SysTickInit();                      //初始化系统滴答定时器
	
	T16NxInit();						//初始化T16Nx定时器配置
	
	#if (LVD_ENABLE == CF_ENABLE)
	LowVoltDetect_Init();				//初始化低电压检测配置
	#endif	
}
