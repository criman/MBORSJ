/*===================================================================================================
                		Copyright(C) 2011-2099.  SONG RESEARCH. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Stepmotor.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2022/05/07
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef			_STEPMOTOR_APP_H_

#define			_STEPMOTOR_APP_H_

//角度计算
#define			StepMotorAngle(angle)			((unsigned int)(angle*64/5.625))

#define			C_STEPMOTOR_ANGLE_SELCHK		StepMotorAngle(45)		//自检角度
#define			C_STEPMOTOR_ANGLE_FORCEINIT		StepMotorAngle(30)	    //上电强加角度20°确保关闭或角度最大
#define			C_STEPMOTOR_ANGLE_FORCEOFF		StepMotorAngle(30)	    //待机强加角度20°确保关闭或角度最大
#define         C_STEPMOTOR_ANGLE_INITOPEN      StepMotorAngle(0)       //上电自动校准-若忽略张口过程填0
#define         C_STEPMOTOR_ANGLE_DEFAULT       StepMotorAngle(203)      //风门角度默认值203
#define			C_STEPMOTOR_ANGLE_MIN			StepMotorAngle(120)	    //风门最小角度	120
#define			C_STEPMOTOR_ANGLE_MAX			StepMotorAngle(203)	    //风门最大角度	203

#define			C_STEPMOTOR_SELCHK				550//自检角度
#define			C_STEPMOTOR_FORCEINIT			500//上电强加角度20°确保关闭或角度最大
#define			C_STEPMOTOR_FORCEOFF			500//待机强加角度20°确保关闭或角度最大
#define         C_STEPMOTOR_INITOPEN            550//上电自动校准-若忽略张口过程填0
#define         C_STEPMOTOR_DEFAULT             0//风门角度默认值203
#define			C_STEPMOTOR_MIN				    20//风门最小角度	120
#define			C_STEPMOTOR_MAX					480//风门最大角度	203
#define			C_STEPMOTOR_RESET_ON			250//EEV复位先开250P
#define			C_STEPMOTOR_RESET_OFF			550//EEV复位先关550P
#define			C_STEPMOTOR_COMPOFF_STEP		160//压缩机停机EEV固定开度

#define			C_STEPMOTOR_PULSE_OV            0                       //每次摆风克服自身重力多走x个脉冲 若无需要填0

enum
{
//    ENUM_STEPMOTOR_STATUS_INITFORMAX,		//先把风门打开到最大
//    ENUM_STEPMOTOR_STATUS_WAITFORMAX,		//等待风门达到最大
//    ENUM_STEPMOTOR_STATUS_WAITFOROFF,		//等待风门关闭闭合
	ENUM_STEPMOTOR_STATUS_RESETON,			//先开250P
	ENUM_STEPMOTOR_STATUS_RESETOFF,			//再关550P
	ENUM_STEPMOTOR_STATUS_WAITFORMIN,		//等待关到最小
	ENUM_STEPMOTOR_STATUS_INITOPEN,			//等待达到初开度
    ENUM_STEPMOTOR_STATUS_RUN,				//正常功能运行
};

enum
{
    ENUM_STEPMOTOR_POSITION_OFFINIT,	    //关风门
    ENUM_STEPMOTOR_POSITION_WAITOFFOK,	    //等待强加角度完成
    ENUM_STEPMOTOR_POSITION_OFFOK,			//关风门强加角度确保关紧
    ENUM_STEPMOTOR_POSITION_ON,				//开风门-默认角度定住
    ENUM_STEPMOTOR_POSITION_ONOK,			//开风门-已完成最大角度
    ENUM_STEPMOTOR_POSITION_SWEEP,			//开风门-扫风
	ENUM_STEPMOTOR_POSITION_ANTIDEW,		//防凝露
    ENUM_STEPMOTOR_POSITION_SELFCHK,		//自检风门
};
/****************************************************************************************************
Function Name       :U8	Case_StepMotor_StepTime(void)
Description         :步进电机选择速度选择
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/ 
extern	U8	Case_StepMotor_StepTime(void);
/****************************************************************************************************
Function Name       :U8	Case_StepMotor_Pause(void)
Description         :步进电机停止旋转条件
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/ 
extern	U8	Case_StepMotor_Pause(void);
/****************************************************************************************************
Function Name       :void App_StepMotor_Run(void)
Description         :系统状态处理步进电机
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern	void	App_StepMotor_Run(void);
/****************************************************************************************************
Function Name       :void EEV_InitOpenStep(void)
Description         :初始开度计算
Input               :
Return              :
Author              :冯锐辉
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern	void	EEV_InitOpenStep(void);

#endif
