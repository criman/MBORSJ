/*===================================================================================================
                		Copyright(C) 2011-2099.  SONG RESEARCH. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Stepmotor_app.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2022/05/07
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include		"main.h"
void	EEV_TrgSuperHeatCalc(void)
{
	if ((T5.f_Error) || (Tp.f_Error))
	{
		StepMotor.var.s16_SuperHeatTrg = 10;
	}
	else if (Comp.u32_RunContCount <= 1800)
	{
		StepMotor.var.s16_SuperHeatTrg = 10;
	}
	else 
	{
		if (Tp.s16_ValueMul10 >= 100)
		{
			if (T5.s16_ValueMul10bc >= 550)
			{
				StepMotor.var.s16_SuperHeatTrg = 40;
			}
			else if (T5.s16_ValueMul10bc >= 450)
			{
				StepMotor.var.s16_SuperHeatTrg = 30;
			}
			else if (T5.s16_ValueMul10bc >= 350)
			{
				StepMotor.var.s16_SuperHeatTrg = 20;
			}
			else 
			{
				StepMotor.var.s16_SuperHeatTrg = 10;
			}
		}
		else if (Tp.s16_ValueMul10 >= 80)
		{
			if (T5.s16_ValueMul10bc >= 550)
			{
				StepMotor.var.s16_SuperHeatTrg = 40;
			}
			else if (T5.s16_ValueMul10bc >= 450)
			{
				StepMotor.var.s16_SuperHeatTrg = 30;
			}
			else if (T5.s16_ValueMul10bc >= 350)
			{
				StepMotor.var.s16_SuperHeatTrg = 20;
			}
			else 
			{
				StepMotor.var.s16_SuperHeatTrg = 10;
			}
		}
		else if (Tp.s16_ValueMul10 >= 60)
		{
			if (T5.s16_ValueMul10bc >= 550)
			{
				StepMotor.var.s16_SuperHeatTrg = 50;
			}
			else if (T5.s16_ValueMul10bc >= 450)
			{
				StepMotor.var.s16_SuperHeatTrg = 40;
			}
			else if (T5.s16_ValueMul10bc >= 350)
			{
				StepMotor.var.s16_SuperHeatTrg = 30;
			}
			else 
			{
				StepMotor.var.s16_SuperHeatTrg = 20;
			}
		}
		else //TP < 60
		{
			if (T5.s16_ValueMul10bc >= 550)
			{
				StepMotor.var.s16_SuperHeatTrg = 60;
			}
			else if (T5.s16_ValueMul10bc >= 450)
			{
				StepMotor.var.s16_SuperHeatTrg = 50;
			}
			else if (T5.s16_ValueMul10bc >= 350)
			{
				StepMotor.var.s16_SuperHeatTrg = 40;
			}
			else 
			{
				StepMotor.var.s16_SuperHeatTrg = 30;
			}
		}

		if (BPV.f_DrvOn)
		{
			StepMotor.var.s16_SuperHeatTrg -= TempValueMul10(FtyPara.s16P15);
		}
	}
}
void	EEV_InitOpenStep(void)
{
	if (T4.s16_ValueMul10 >= 450)
	{
		if (T5.s16_ValueMul10bc >= 550)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 450)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 350)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 250)
		{
			StepMotor.var.u16_OpenInitStep = 450;
		}
		else if (T5.s16_ValueMul10bc >= 150)
		{
			StepMotor.var.u16_OpenInitStep = 400;
		}
		else //if (T5.s16_ValueMul10bc >= 50)
		{
			StepMotor.var.u16_OpenInitStep = 350;
		}
	}
	else if (T4.s16_ValueMul10 >= 400)
	{
		if (T5.s16_ValueMul10bc >= 550)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 450)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 350)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 250)
		{
			StepMotor.var.u16_OpenInitStep = 400;
		}
		else if (T5.s16_ValueMul10bc >= 150)
		{
			StepMotor.var.u16_OpenInitStep = 350;
		}
		else //if (T5.s16_ValueMul10bc >= 50)
		{
			StepMotor.var.u16_OpenInitStep = 300;
		}
	}
	else if (T4.s16_ValueMul10 >= 350)
	{
		if (T5.s16_ValueMul10bc >= 550)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 450)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 350)
		{
			StepMotor.var.u16_OpenInitStep = 450;
		}
		else if (T5.s16_ValueMul10bc >= 250)
		{
			StepMotor.var.u16_OpenInitStep = 350;
		}
		else if (T5.s16_ValueMul10bc >= 150)
		{
			StepMotor.var.u16_OpenInitStep = 300;
		}
		else //if (T5.s16_ValueMul10bc >= 50)
		{
			StepMotor.var.u16_OpenInitStep = 250;
		}
	}
	else if (T4.s16_ValueMul10 >= 300)
	{
		if (T5.s16_ValueMul10bc >= 550)
		{
			StepMotor.var.u16_OpenInitStep = 480;
		}
		else if (T5.s16_ValueMul10bc >= 450)
		{
			StepMotor.var.u16_OpenInitStep = 450;
		}
		else if (T5.s16_ValueMul10bc >= 350)
		{
			StepMotor.var.u16_OpenInitStep = 350;
		}
		else if (T5.s16_ValueMul10bc >= 250)
		{
			StepMotor.var.u16_OpenInitStep = 300;
		}
		else if (T5.s16_ValueMul10bc >= 150)
		{
			StepMotor.var.u16_OpenInitStep = 250;
		}
		else //if (T5.s16_ValueMul10bc >= 50)
		{
			StepMotor.var.u16_OpenInitStep = 200;
		}
	}
	else if (T4.s16_ValueMul10 >= 200)
	{
		if (T5.s16_ValueMul10bc >= 550)
		{
			StepMotor.var.u16_OpenInitStep = 450;
		}
		else if (T5.s16_ValueMul10bc >= 450)
		{
			StepMotor.var.u16_OpenInitStep = 350;
		}
		else if (T5.s16_ValueMul10bc >= 350)
		{
			StepMotor.var.u16_OpenInitStep = 300;
		}
		else if (T5.s16_ValueMul10bc >= 250)
		{
			StepMotor.var.u16_OpenInitStep = 250;
		}
		else if (T5.s16_ValueMul10bc >= 150)
		{
			StepMotor.var.u16_OpenInitStep = 200;
		}
		else //if (T5.s16_ValueMul10bc >= 50)
		{
			StepMotor.var.u16_OpenInitStep = 150;
		}
	}
	else if (T4.s16_ValueMul10 >= 100)
	{
		if (T5.s16_ValueMul10bc >= 550)
		{
			StepMotor.var.u16_OpenInitStep = 400;
		}
		else if (T5.s16_ValueMul10bc >= 450)
		{
			StepMotor.var.u16_OpenInitStep = 300;
		}
		else if (T5.s16_ValueMul10bc >= 350)
		{
			StepMotor.var.u16_OpenInitStep = 250;
		}
		else if (T5.s16_ValueMul10bc >= 250)
		{
			StepMotor.var.u16_OpenInitStep = 200;
		}
		else if (T5.s16_ValueMul10bc >= 150)
		{
			StepMotor.var.u16_OpenInitStep = 150;
		}
		else //if (T5.s16_ValueMul10bc >= 50)
		{
			StepMotor.var.u16_OpenInitStep = 100;
		}
	}
	else //if (T4.s16_ValueMul10 >= 0)
	{
		if (T5.s16_ValueMul10bc >= 550)
		{
			StepMotor.var.u16_OpenInitStep = 300;
		}
		else if (T5.s16_ValueMul10bc >= 450)
		{
			StepMotor.var.u16_OpenInitStep = 250;
		}
		else if (T5.s16_ValueMul10bc >= 350)
		{
			StepMotor.var.u16_OpenInitStep = 200;
		}
		else if (T5.s16_ValueMul10bc >= 250)
		{
			StepMotor.var.u16_OpenInitStep = 150;
		}
		else if (T5.s16_ValueMul10bc >= 150)
		{
			StepMotor.var.u16_OpenInitStep = 100;
		}
		else //if (T5.s16_ValueMul10bc >= 50)
		{
			StepMotor.var.u16_OpenInitStep = 70;
		}
	}
}

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
U8	Case_StepMotor_StepTime(void)
{
    //add code if necessary....

    if ((StepMotor.var.u8_status == ENUM_STEPMOTOR_STATUS_RUN)	&& (StepMotor.var.u8_run > ENUM_STEPMOTOR_POSITION_OFFOK))
    {
        if (StepMotor.var.u8_run != ENUM_STEPMOTOR_POSITION_SWEEP)
        {
            return 0;	//速度较快
        }
        else
        {
            return 1;	//速度较慢-//正常工作
        }
    }
    else		
    {	
        return 0;	    //速度较快-//上电初始化或关机关风门
    }
	
}
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
U8	Case_StepMotor_Pause(void)
{
    //add code if necessary....

    if (F_stepmotor_pause || (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget))
    {		
        return	1;
    }
    else
    {
        return	0;
    }
	
}
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
void	App_StepMotor_Run(void)
{
	static int s16SuperHeatSum,s16KP;
	static unsigned char u8SuperHeatCnt;
    switch (StepMotor.var.u8_status)
    {
        case	ENUM_STEPMOTOR_STATUS_RESETON:		//先打开到250P
        {
            F_stepmotor_forceoff = CF_ENABLE;										//强制关风门(上电已有效不用重复)
            StepMotor.var.u16_agcurrent = 0;										//起点
            StepMotor.var.u16_agtarget  = C_STEPMOTOR_RESET_ON;			    		//上电校准风门先打开的角度
        
//            if ((PowEnPTCB.f_DrvOn == ON) && (PowEn12V.f_DrvOn == ON))				//add 20231218 等待12V光耦打开和PTCB打开后才进行复位动作
//			{
//				StepMotor.var.u8_status += 1;
//			}

			StepMotor.var.u8_status += 1;
        }break;

        case	ENUM_STEPMOTOR_STATUS_RESETOFF:		//再关550P
        {
        	if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
            {
		            StepMotor.var.u16_agcurrent = C_STEPMOTOR_RESET_OFF;										//起点
		            StepMotor.var.u16_agtarget  = 0;			    		//上电校准风门先打开的角度
					StepMotor.var.u8_status += 1;
			}
        }break;
        
        case	ENUM_STEPMOTOR_STATUS_WAITFORMIN:		//等待风门达到最小
        {
            if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
            {
//                StepMotor.var.u16_agcurrent = C_STEPMOTOR_MAX;		        //风门最大角度
//                StepMotor.var.u16_agtarget  = 0;							        //起点
				if (Comp.f_HavedDrvOn == 1)
				{
					StepMotor.var.u16_agcurrent = 0;
					StepMotor.var.u16_agtarget = C_STEPMOTOR_COMPOFF_STEP;
					if (Comp.u32_StopContCount >= 1800)
					{//停机复位到160P要等待到压机停满3min才回到初开度
						Comp.f_HavedDrvOn = 0;
					}
				}
				else 
				{
	                EEV_InitOpenStep();
	                StepMotor.var.u8_status += 1;
	            }
            }
        }break;
        
//        case	ENUM_STEPMOTOR_STATUS_WAITFOROFF:		//等待风门关闭闭合
//        {
//            if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
//            {
//                StepMotor.var.u16_agcurrent = 0;									//起点
//                StepMotor.var.u16_agtarget = 0;										//起点
//                StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_OFFINIT;			    //功能运行默认关闭等待命令
//            
//                StepMotor.var.u8_status += 1;
//            }
//        }break;

        case	ENUM_STEPMOTOR_STATUS_INITOPEN:		//等待达到初开度
        {
            if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
            {
                StepMotor.var.u16_agcurrent = 0;									//起点
                StepMotor.var.u16_agtarget = StepMotor.var.u16_OpenInitStep;										//起点
//                StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_OFFINIT;			    //功能运行默认关闭等待命令
            
                StepMotor.var.u8_status += 1;
            }
        }break;
        
        case	ENUM_STEPMOTOR_STATUS_RUN:		//正常运行		
        {
#if 1
			if ((T3.f_Error) || (TH.f_Error))
			{
				EEV_InitOpenStep();
				StepMotor.var.u16_agtarget = StepMotor.var.u16_OpenInitStep;
			}
			else 
			{
				if  (Comp.f_DrvOn == 0)
				{
					if (Comp.f_HavedDrvOn == 1)
					{
						StepMotor.var.u16_agtarget = FtyPara.u16P13;
						
					}
					else 	//上电后未开启过压缩机时不动作
					{

					}

					if (Comp.u32_StopContCount >= 1200)
					{//压缩机停机2min后，复位一次
						StepMotor.var.u8_status = ENUM_STEPMOTOR_STATUS_RESETON;
					}
				}
				else 
				{
					EEV_TrgSuperHeatCalc();		//计算过热度
					Comp.f_HavedDrvOn = 1;
		        	StepMotor.var.u16_CtrlPeriod ++;
		        	if ((StepMotor.var.u16_CtrlPeriod % 500) == 0)
		        	{
		        		u8SuperHeatCnt ++;
		        		
						s16SuperHeatSum = s16SuperHeatSum + TH.s16_ValueMul10 - T3.s16_ValueMul10;
						if (u8SuperHeatCnt >= (FtyPara.u16P14 / 5))
		        		{
							StepMotor.var.s16_SuperHeatAvg = s16SuperHeatSum /(FtyPara.u16P14 / 5);
							s16SuperHeatSum = 0;
							u8SuperHeatCnt = 0;
		        		}
		        	}
		        	
		        	if (StepMotor.var.u16_CtrlPeriod >= (FtyPara.u16P14 * 100))
		        	{
		        		
						StepMotor.var.u16_CtrlPeriod = 0;
						if (Tp.s16_ValueMul10 >= TempValueMul10(FtyPara.s16P16))
						{
							StepMotor.var.u16_agtarget = StepMotor.var.u16_agtarget + 5;
						}
						else if (Tp.s16_ValueMul10 <= (TempValueMul10(FtyPara.s16P16) - 50))
						{
							if (Comp.f_DrvOn)
							{
								if (StepMotor.var.s16_SuperHeatAvg > 0)
								{
									s16KP = 10;
								}
								else if (StepMotor.var.s16_SuperHeatAvg > -10)
								{
									s16KP = 15;
								}
								else 
								{
									s16KP = 20;
								}
								
								StepMotor.var.s16_EEVDeltaStep = s16KP * 
								  (StepMotor.var.s16_SuperHeatAvg -StepMotor.var.s16_SuperHeatTrg)/100;	// /10取温度个位数，/10为Kp取小数点

								if (StepMotor.var.s16_EEVDeltaStep >=0)
								{
									if (StepMotor.var.s16_EEVDeltaStep > 20)
									{
										StepMotor.var.s16_EEVDeltaStep = 20;
									}
									StepMotor.var.u16_agtarget += (uint16_t)StepMotor.var.s16_EEVDeltaStep;
								}
								else 
								{
									if (StepMotor.var.s16_EEVDeltaStep < -20)
									{
										StepMotor.var.s16_EEVDeltaStep = -20;
									}
									StepMotor.var.u16_agtarget += (uint16_t)StepMotor.var.s16_EEVDeltaStep;
								}
							}
						}
						else 		//维持原步数
						{

						}
		        	}
				}
			}
			
//			StepMotor.var.u16_agtarget = StepMotor.var.u16_matarget;
        	if (StepMotor.var.u16_agtarget >= C_STEPMOTOR_MAX)
			{
				StepMotor.var.u16_agtarget = C_STEPMOTOR_MAX;
			}
			
			if (StepMotor.var.u16_agtarget <= C_STEPMOTOR_MIN)
			{
				StepMotor.var.u16_agtarget = C_STEPMOTOR_MIN;
			}
#endif

//以下为扫风逻辑        	
//            switch (StepMotor.var.u8_run)
//            {
//                case	ENUM_STEPMOTOR_POSITION_OFFINIT:	//关风门
//                {
//                    if ((StepMotor.var.u16_agcurrent == 0) && (StepMotor.var.u16_agtarget == 0))
//                    {
//                        if (StepMotor.var.f_forceinit == 0)
//                        {
//                            StepMotor.var.f_forceinit = 1;
//                            StepMotor.var.u16_agcurrent = C_STEPMOTOR_ANGLE_FORCEINIT;		//强加角度确保关闭(上电)
//                        
//                        } 
//                        else
//                        {
//                            StepMotor.var.u16_agcurrent = C_STEPMOTOR_ANGLE_FORCEOFF;		//强加角度确保关闭(待机)
//                        }
//                        
//                        StepMotor.var.u8_run += 1;
//                    }
//                }break;
//                
//                case	ENUM_STEPMOTOR_POSITION_WAITOFFOK:	//等待强加角度完成								
//                {
//                    if ((StepMotor.var.u16_agcurrent == 0) && (StepMotor.var.u16_agtarget == 0))
//                    {
//                        StepMotor.var.u8_run += 1;
//                    }
//                }break;
//                
//                case	ENUM_STEPMOTOR_POSITION_OFFOK:		//关风门强加角度确保关紧
//                {
//                    ;
//                }break;
//                
//                case	ENUM_STEPMOTOR_POSITION_ON:			//开风门-某角度定住
//                {
//                    if (SystemMode.f_AntiDew == 0)                 
//                    {	
//						StepMotor.var.u16_agtarget = Swing.u16_anglebak;			        //风门默认角度 						
//					}
//					else	//防凝露摆最大角度
//					{
//						StepMotor.var.u16_agtarget = C_STEPMOTOR_ANGLE_MAX;
//						F_stepmotor_pause = CF_DISABLE;
//					}
//					                   
//                    
//                    if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
//                    {
//                        StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ONOK;
//                    }
//                }break;
//                
//                case	ENUM_STEPMOTOR_POSITION_ONOK:
//                {
//					if ((SystemMode.f_AntiDew == 0) && (Swing.u16_angledew != 0))
//					{
//						StepMotor.var.u16_agtarget = Swing.u16_angledew;
//						if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
//						{
//							Swing.u16_angledew = 0;
//						}
//						StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ANTIDEW;
//						F_stepmotor_pause = CF_DISABLE;											//摆风情况清除停止标志
//					} 
//                }break;
//                
//                case	ENUM_STEPMOTOR_POSITION_SWEEP:		//开风门-扫风
//                {
//                    Swing_Sweep();
//                }break;
//                
//				case	ENUM_STEPMOTOR_POSITION_ANTIDEW:
//				{
//                    if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
//                    {
//                        StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ONOK;
//						Swing.u16_angledew = 0;
//                    }				
//				}break;
//				
//                case	ENUM_STEPMOTOR_POSITION_SELFCHK:		//自检风门	
//                {
//                    StepMotor.var.u16_agtarget  = C_STEPMOTOR_ANGLE_SELCHK;							//风门自检角度
//                }break;
//
//                default: break;
//            }
                
        }break;
        
        default: break;
    }
    
    //add code...       //通过功能改变角度
//    Swing_Con();		//风门控制
		
}

//{
//	static int s16SuperHeatSum,s16KP;
//	static unsigned char u8SuperHeatCnt;
//    switch (StepMotor.var.u8_status)
//    {
//        case	ENUM_STEPMOTOR_STATUS_INITFORMAX:		//先把风门打开到最大
//        {
//            F_stepmotor_forceoff = CF_ENABLE;										//强制关风门(上电已有效不用重复)
//            StepMotor.var.u16_agcurrent = 0;										//起点
//            StepMotor.var.u16_agtarget  = C_STEPMOTOR_INITOPEN;			    		//上电校准风门先打开的角度
//        
////            if ((PowEnPTCB.f_DrvOn == ON) && (PowEn12V.f_DrvOn == ON))				//add 20231218 等待12V光耦打开和PTCB打开后才进行复位动作
////			{
////				StepMotor.var.u8_status += 1;
////			}
//
//			StepMotor.var.u8_status += 1;
//        }break;
//        
//        case	ENUM_STEPMOTOR_STATUS_WAITFORMAX:		//等待风门达到最大
//        {
//            if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
//            {
////                StepMotor.var.u16_agcurrent = C_STEPMOTOR_MAX;		        //风门最大角度
////                StepMotor.var.u16_agtarget  = 0;							        //起点
//                EEV_InitOpenStep();
//                StepMotor.var.u8_status += 1;
//            }
//        }break;
//        
////        case	ENUM_STEPMOTOR_STATUS_WAITFOROFF:		//等待风门关闭闭合
////        {
////            if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
////            {
////                StepMotor.var.u16_agcurrent = 0;									//起点
////                StepMotor.var.u16_agtarget = 0;										//起点
////                StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_OFFINIT;			    //功能运行默认关闭等待命令
////            
////                StepMotor.var.u8_status += 1;
////            }
////        }break;
//
//        case	ENUM_STEPMOTOR_STATUS_INITOPEN:		//等待达到初开度
//        {
//            if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
//            {
//                StepMotor.var.u16_agcurrent = C_STEPMOTOR_MAX;									//起点
//                StepMotor.var.u16_agtarget = StepMotor.var.u16_OpenInitStep;										//起点
//                StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_OFFINIT;			    //功能运行默认关闭等待命令
//            
//                StepMotor.var.u8_status += 1;
//            }
//        }break;
//        
//        case	ENUM_STEPMOTOR_STATUS_RUN:		//正常运行		//扫风功能运行
//        {
//#if 1
//        	StepMotor.var.u16_CtrlPeriod ++;
//        	if ((StepMotor.var.u16_CtrlPeriod % 500) == 0)
//        	{
//        		u8SuperHeatCnt ++;
//        		
//				s16SuperHeatSum = s16SuperHeatSum + TH.s16_ValueMul10 - T3.s16_ValueMul10;
//				if (u8SuperHeatCnt >= 6)
//        		{
//					StepMotor.var.s16_SuperHeatAvg = s16SuperHeatSum /6;
//					s16SuperHeatSum = 0;
//					u8SuperHeatCnt = 0;
//        		}
//        	}
//        	
//        	if (StepMotor.var.u16_CtrlPeriod >= 3000)
//        	{
//        		StepMotor.var.s16_SuperHeatTrg = FtyPara.s16P2;
//				StepMotor.var.u16_CtrlPeriod = 0;
//				if (Tp.s16_ValueMul10 >= FtyPara.s16P3)
//				{
//					StepMotor.var.u16_agtarget = StepMotor.var.u16_agtarget + 5;
//				}
//				else if (Tp.s16_ValueMul10 < FtyPara.s16P3 - 50)
//				{
//					if (Comp.f_DrvOn)
//					{
//						if (StepMotor.var.s16_SuperHeatAvg > 0)
//						{
//							s16KP = 1;
//						}
//						else 
//						{
//							s16KP = 2;
//						}
//						
//						StepMotor.var.s16_EEVDeltaStep = s16KP * 
//						  (StepMotor.var.s16_SuperHeatAvg -StepMotor.var.s16_SuperHeatTrg)/10;
//
//						if (StepMotor.var.s16_EEVDeltaStep >=0)
//						{
//							if (StepMotor.var.s16_EEVDeltaStep > 20)
//							{
//								StepMotor.var.s16_EEVDeltaStep = 20;
//							}
//							StepMotor.var.u16_agtarget += (uint16_t)StepMotor.var.s16_EEVDeltaStep;
//						}
//						else 
//						{
//							if (StepMotor.var.s16_EEVDeltaStep < -20)
//							{
//								StepMotor.var.s16_EEVDeltaStep = -20;
//							}
//							StepMotor.var.u16_agtarget += (uint16_t)StepMotor.var.s16_EEVDeltaStep;
//						}
//					}
//				}
//				else 		//维持原步数
//				{
//
//				}
//        	}
//
//
////			StepMotor.var.u16_agtarget = StepMotor.var.u16_matarget;
//        	if (StepMotor.var.u16_agtarget >= C_STEPMOTOR_MAX)
//			{
//				StepMotor.var.u16_agtarget = C_STEPMOTOR_MAX;
//			}
//			
//			if (StepMotor.var.u16_agtarget <= C_STEPMOTOR_MIN)
//			{
//				StepMotor.var.u16_agtarget = C_STEPMOTOR_MIN;
//			}
//#endif
//
////以下为扫风逻辑        	
////            switch (StepMotor.var.u8_run)
////            {
////                case	ENUM_STEPMOTOR_POSITION_OFFINIT:	//关风门
////                {
////                    if ((StepMotor.var.u16_agcurrent == 0) && (StepMotor.var.u16_agtarget == 0))
////                    {
////                        if (StepMotor.var.f_forceinit == 0)
////                        {
////                            StepMotor.var.f_forceinit = 1;
////                            StepMotor.var.u16_agcurrent = C_STEPMOTOR_ANGLE_FORCEINIT;		//强加角度确保关闭(上电)
////                        
////                        } 
////                        else
////                        {
////                            StepMotor.var.u16_agcurrent = C_STEPMOTOR_ANGLE_FORCEOFF;		//强加角度确保关闭(待机)
////                        }
////                        
////                        StepMotor.var.u8_run += 1;
////                    }
////                }break;
////                
////                case	ENUM_STEPMOTOR_POSITION_WAITOFFOK:	//等待强加角度完成								
////                {
////                    if ((StepMotor.var.u16_agcurrent == 0) && (StepMotor.var.u16_agtarget == 0))
////                    {
////                        StepMotor.var.u8_run += 1;
////                    }
////                }break;
////                
////                case	ENUM_STEPMOTOR_POSITION_OFFOK:		//关风门强加角度确保关紧
////                {
////                    ;
////                }break;
////                
////                case	ENUM_STEPMOTOR_POSITION_ON:			//开风门-某角度定住
////                {
////                    if (SystemMode.f_AntiDew == 0)                 
////                    {	
////						StepMotor.var.u16_agtarget = Swing.u16_anglebak;			        //风门默认角度 						
////					}
////					else	//防凝露摆最大角度
////					{
////						StepMotor.var.u16_agtarget = C_STEPMOTOR_ANGLE_MAX;
////						F_stepmotor_pause = CF_DISABLE;
////					}
////					                   
////                    
////                    if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
////                    {
////                        StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ONOK;
////                    }
////                }break;
////                
////                case	ENUM_STEPMOTOR_POSITION_ONOK:
////                {
////					if ((SystemMode.f_AntiDew == 0) && (Swing.u16_angledew != 0))
////					{
////						StepMotor.var.u16_agtarget = Swing.u16_angledew;
////						if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
////						{
////							Swing.u16_angledew = 0;
////						}
////						StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ANTIDEW;
////						F_stepmotor_pause = CF_DISABLE;											//摆风情况清除停止标志
////					} 
////                }break;
////                
////                case	ENUM_STEPMOTOR_POSITION_SWEEP:		//开风门-扫风
////                {
////                    Swing_Sweep();
////                }break;
////                
////				case	ENUM_STEPMOTOR_POSITION_ANTIDEW:
////				{
////                    if (StepMotor.var.u16_agcurrent == StepMotor.var.u16_agtarget)
////                    {
////                        StepMotor.var.u8_run = ENUM_STEPMOTOR_POSITION_ONOK;
////						Swing.u16_angledew = 0;
////                    }				
////				}break;
////				
////                case	ENUM_STEPMOTOR_POSITION_SELFCHK:		//自检风门	
////                {
////                    StepMotor.var.u16_agtarget  = C_STEPMOTOR_ANGLE_SELCHK;							//风门自检角度
////                }break;
////
////                default: break;
////            }
//                
//        }break;
//        
//        default: break;
//    }
//    
//    //add code...       //通过功能改变角度
////    Swing_Con();		//风门控制
//		
//}
