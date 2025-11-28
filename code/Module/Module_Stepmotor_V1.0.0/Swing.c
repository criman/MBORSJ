/*===================================================================================================
                		Copyright(C) 2011-2099.  SUMRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: swing.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/03/10
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_SWING    Swing;

/****************************************************************************************************
Function Name       :void	Swing_Con(void)	
Description         :风门控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Swing_Con(void)
{   
    if (StepMotor.var.u8_status < ENUM_STEPMOTOR_STATUS_RUN) return;                    //初始化结束才能正常摆叶
    
	if ((PowEnPTCB.f_DrvOn == OFF) || (PowEn12V.f_DrvOn == OFF)) return;
	
    if ((System.Enum_Status == ENUM_STATUS_ON) || (System.Enum_Status == ENUM_STATUS_BUSSCHK))   //开机开风门
    {
        F_stepmotor_forceoff = CF_DISABLE;												//系统工作清风门强制关标志
        Swing.u16_offdelay = C_SWING_OFFDELAY;											//风门延时关闭计时
    
        if (StepMotor.var.u8_status < ENUM_STEPMOTOR_STATUS_RUN)                        
        {
            StepMotor.var.u8_status = ENUM_STEPMOTOR_STATUS_RUN;					    //刚上电风门初始化动作系统开机时立即风门按最大角度走
            StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ON;
        
            if (StepMotor.var.u16_agcurrent <= C_STEPMOTOR_ANGLE_FORCEOFF)		        //预判即将到达关闭风门或者正在强制关闭风门
            {
                StepMotor.var.u16_agcurrent = 0;										//当前角度清0(开机需走最大角度)
            }//不满足条件的在当前角度基础上走最大角度
        }									
    
        if (StepMotor.var.u8_run == ENUM_STEPMOTOR_POSITION_OFFOK)				        //从风门待机状态系统工作刹那
        {
            StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ON;
        }

        if ((StepMotor.var.u8_run == ENUM_STEPMOTOR_POSITION_ONOK) || (StepMotor.var.u8_run == ENUM_STEPMOTOR_POSITION_SWEEP))
        {											
            if (Fan.f_SweepLR == 1)									    //只有在风门达到最大角度后才能进行摆风动作
            {
                StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_SWEEP;	
                F_stepmotor_pause = CF_DISABLE;											//摆风情况清除停止标志
            }
            else
            {																			
                if (StepMotor.var.u16_agcurrent < C_STEPMOTOR_ANGLE_MIN)				//未到达最小角度之前不能停摆叶
                {                        
                    F_stepmotor_pause = CF_DISABLE;	    
                }   
                else    
                {   

					if (Swing.u16_angledew == 0)										//正常没有防凝露
					{
						Swing.u16_anglebak = StepMotor.var.u16_agcurrent;                   //记录摆叶角度
					}
					else	//记录防凝露动作前的角度
					{
						Swing.u16_anglebak = Swing.u16_angledew;
					}
					
					
					if (F_stepmotor_pause == CF_DISABLE)
					{
//						F_func_remember = CF_ENABLE;                                    //记忆信息
					}

					
					F_stepmotor_pause = CF_ENABLE;									    //风门达到最大角度后停止摇头时停止标志置1
                    
					//---------------------------------------------------------
					//lcx add //进入性能测试时开到最大角
					if (Swing.f_PrefTestSetMaxAngle == 1)
					{
						if (F_stepmotor_autodirect) 								//自动扫描时候步进电机方向 1：顺时针	
						{
							StepMotor.var.u16_agtarget = C_STEPMOTOR_ANGLE_MAX;
						
							if (StepMotor.var.u16_agcurrent >= C_STEPMOTOR_ANGLE_MAX)
							{
								Swing.f_PrefTestSetMaxAngle = 0;
							}
						}
						F_stepmotor_pause = CF_DISABLE;
					}
					//---------------------------------------------------------
                }                  
            }
        }
    }
    else
    {
        if (Swing.u16_offdelay == 0)
        {
            if (F_stepmotor_forceoff == CF_DISABLE)										//只做一次强制关风门动作(再走一些角度)
            {
                F_stepmotor_forceoff = CF_ENABLE;
                F_stepmotor_pause = CF_DISABLE;
                StepMotor.var.u16_agtarget = 0;											//关机关风门
                StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_OFFINIT;
            }
        }
        else
        {
            if (Fan.Indoor.f_DrvOn == OFF)                                        	//20230426上电机风机关闭才倒计时
            {
                Swing.u16_offdelay -= 1;
            }
        }
    }
}
/****************************************************************************************************
Function Name       :void	Swing_Sweep(void)	
Description         :风门扫风逻辑处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Swing_Sweep(void)
{
    if (Fan.Indoor.f_DrvOn == ON)   //电机运行才能扫风
    {
    	if(Fan.Indoor.u16_RealRPM > 0) //实际转速大于0才能扫风  //lcx add 20240617
    	{
			Log_StepMotor_SweepAuto(C_STEPMOTOR_ANGLE_MIN, C_STEPMOTOR_ANGLE_MAX);	//最小角度和最大角度之间扫风
    	}
    }
}

//add code
/****************************************************************************************************
Function Name       :void    Swing_AntiDew(void)
Description         :防凝露功能
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Swing_AntiDew(void)
{	
	if ((SystemMode.f_AntiDew == 0) && (SystemMode.f_AntiDewMark == 0))		//无故障或再开机情况未曾进入防凝露满足条件
	{
		//判断运行防凝露条件
		if ((SystemMode.f_Cold == 1) && ((Fan.Indoor.Level == ENUM_FANLEVEL_LOW) || (Fan.Indoor.Level == ENUM_FANLEVEL_LOW_S))
			&& ((T1.s16_ValueMul10 >= 240) && (T1.s16_ValueMul10 <= 300)) && (Comp.f_DrvOn == ON) && (Fan.f_SweepLR == 0))
		{
			if (Swing.u16_AntiDewCount >= 18000)	//30min
			{
				SystemMode.f_AntiDew = 1;
				SystemMode.f_AntiDewMark = 1;
				
				Swing.u16_angledew = StepMotor.var.u16_agcurrent;                   //防凝露生效时记录摆叶角度
				StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ON;					//摆叶需动作
			}
		}
		else
		{
			Swing.u16_AntiDewCount = 0;
			Swing.u16_angledew = 0;
		}
	}
	else
	{
		Swing.u16_AntiDewCount = 0;
		
		//判断退出防凝露条件
		
		if ((System.Enum_Status == ENUM_STATUS_OFF) || (Comp.f_DrvOn == OFF) || (SystemMode.f_Fan == 1) || (Fan.f_SweepLR == 1) ||
			(Fan.Indoor.Level == ENUM_FANLEVEL_MED) || (Fan.Indoor.Level == ENUM_FANLEVEL_HIGH) || (Fan.Indoor.Level == ENUM_FANLEVEL_HIGH_S) ||
			(T1.s16_ValueMul10 < 240) || (T1.s16_ValueMul10 > 300) || 
			(Protect.f_Enable == 1) || (SystemMode.f_Error == 1))
		{
			if (SystemMode.f_AntiDew == 1)
			{
				StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ONOK;
			}
			
			SystemMode.f_AntiDew = 0;
			
			if (SystemMode.f_Error == 1)	//故障发生时清除防凝露标志后可再次进入
			{
				SystemMode.f_AntiDewMark = 0;
			}
			
				
		}
	}
}
