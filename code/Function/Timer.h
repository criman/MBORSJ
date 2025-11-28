/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Timer.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _TIMER_H_

#define    _TIMER_H_


typedef    struct
{
	U8     f_OffEn      :1;		      //定时关标志
    U8     f_OnEn       :1;           //定时开标志
	U8     f_Enable		:1;			  //定时有效总标志
	U8     Reserve    	:5;		      //预留
	U16    u16_Minute;				  //分钟:   0-1440 		
	U16    u16_SecDiv10Remain;        //秒计时: 0-599 (单位:100ms)
	
}STRUCT_TIMER;

extern    STRUCT_TIMER    Timer;

/****************************************************************************************************
Function Name       :void    TimerPara_Init(void)
Description         :定时相关变量清除
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    TimerPara_Init(void);
/****************************************************************************************************
Function Name       :void Timer_Run(void)
Description         :常规定时计时
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Timer_Run(void);

#endif
