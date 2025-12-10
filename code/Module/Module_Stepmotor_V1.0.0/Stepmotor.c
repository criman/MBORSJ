/*===================================================================================================
                		Copyright(C) 2011-2099.  SONG RESEARCH. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Stepmotor.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2022/05/06
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include		"main.h"

#if defined(UNIT_TEST)
    // 在测试环境中，全局变量在 test_compat.c 中定义
    extern STRUCT_STEPMOTORBYTE StepMotorFlag;
    extern UNION_STEPMOTOR StepMotor;
#else
    STRUCT_STEPMOTORBYTE		StepMotorFlag;
    UNION_STEPMOTOR				StepMotor;
#endif

//--------------------------------------------------------------------------------------------------//
//橙(bit3)-黄(bit2)-粉(bit1)-蓝(bit0)组成十六进制相序表
//当旋转方向与功能要求相反时更换相序表即可
//const    U8    U8_stepmotor_CW_table[8]__attribute__((at(0x00008000))) = {0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};	    //顺时针旋转相序表	
const    U8    U8_stepmotor_CCW_table[8]__attribute__((at(0x00008000)))  = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08};		//逆时针旋转相序表
//--------------------------------------------------------------------------------------------------//

/****************************************************************************************************
Function Name       :void Module_Init_StepMotor(void)
Description         :步进电机四相 IO初始化
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/ 
void	Module_Init_StepMotor(void)
{	
//--------------------------------------------------------------------------------------------------//
//步进电机橙色引线端
//--------------------------------------------------------------------------------------------------//	
    P_StepmotorA_Low();
    P_StepmotorA_Output();
    P_StepmotorA_Dispull();
//--------------------------------------------------------------------------------------------------//
//步进电机黄色引线端
//--------------------------------------------------------------------------------------------------//		
    P_StepmotorB_Low();
    P_StepmotorB_Output();
    P_StepmotorB_Dispull();
//--------------------------------------------------------------------------------------------------//
//步进电机粉色引线端	
//--------------------------------------------------------------------------------------------------//		
    P_StepmotorC_Low();
    P_StepmotorC_Output();
    P_StepmotorC_Dispull();
//--------------------------------------------------------------------------------------------------//
//步进电机蓝色引线端	
//--------------------------------------------------------------------------------------------------//
    P_StepmotorD_Low();
    P_StepmotorD_Output();	
    P_StepmotorD_Dispull();	
}
/****************************************************************************************************
Function Name       :void Drv_StepMotor(void)
Description         :步进电机四相 IO驱动
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/ 
void	Drv_StepMotor(void)
{
//    Pin_stepmotora = F_stepmotor_pina;
//    Pin_stepmotorb = F_stepmotor_pinb;
//    Pin_stepmotorc = F_stepmotor_pinc;
//    Pin_stepmotord = F_stepmotor_pind;	
	
	if (F_stepmotor_pina)	P_StepmotorA_Hi();
	else					P_StepmotorA_Low();
	
	if (F_stepmotor_pinb)	P_StepmotorB_Hi();
	else					P_StepmotorB_Low();	
	
	if (F_stepmotor_pinc)	P_StepmotorC_Hi();
	else					P_StepmotorC_Low();
	
	if (F_stepmotor_pind)	P_StepmotorD_Hi();
	else					P_StepmotorD_Low();		
}
/****************************************************************************************************
Function Name       :void Log_StepMotor(void)
Description         :步进电机逻辑处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/ 
void	Log_StepMotor(void)
{
    U8 steptemp;

//    if (Case_StepMotor_StepTime())						//工作速度选择
//    {
//        StepMotor.var.u8_steptime_base = 3;				//10ms更新相位(2ms*3 = 6ms) 32ms
//    }
//    else
//    {
//        StepMotor.var.u8_steptime_base = 1;				//2ms上电摆风复位或关风门时间快一些(2ms*1 = 2ms)
//    }
	StepMotor.var.u8_steptime_base = 16;				//32ms更新相位(2ms*16 = 32ms) 
//--------------------------------------------------------------------------------------------------//	
	
    if (++StepMotor.var.u8_steptime >= StepMotor.var.u8_steptime_base)		
    {
        StepMotor.var.u8_steptime = 0;

        if (Case_StepMotor_Pause())							                    //停止旋转条件																							
        {
            F_stepmotor_pina = 0;
            F_stepmotor_pinb = 0;
            F_stepmotor_pinc = 0;
            F_stepmotor_pind = 0;
        }
        else																																		//旋转进行中
        {
            if (StepMotor.var.u16_agcurrent < StepMotor.var.u16_agtarget)		//当前角度小于目标角度时顺时针选择
            {
                if (StepMotor.var.u8_stepcount > 0)	
                {
                    StepMotor.var.u8_stepcount -= 1;							//使用CCW表-顺时针是往后(减)
                }
                else
                {
                    StepMotor.var.u8_stepcount = 7;
                }
                
                StepMotor.var.u16_agcurrent += 1;
            }
            else if (StepMotor.var.u16_agcurrent > StepMotor.var.u16_agtarget)	//当前角度大于目标角度时逆时针选择
            {
                if (++StepMotor.var.u8_stepcount >= 8)
                {
                    StepMotor.var.u8_stepcount = 0;
                }		

                StepMotor.var.u16_agcurrent -= 1;
            }
            
            steptemp = U8_stepmotor_CCW_table[StepMotor.var.u8_stepcount];
            
            if (steptemp & 0x01)		F_stepmotor_pina = 1;					//橙色A-高电平
            else						F_stepmotor_pina = 0;					//橙色A-低电平
            
            if (steptemp & 0x02)		F_stepmotor_pinb = 1;					//黄色B-高电平
            else						F_stepmotor_pinb = 0;					//黄色B-低电平	

            if (steptemp & 0x04)		F_stepmotor_pinc = 1;					//粉色C-高电平
            else						F_stepmotor_pinc = 0;				    //粉色C-低电平

            if (steptemp & 0x08)		F_stepmotor_pind = 1;					//蓝色D-高电平
            else						F_stepmotor_pind = 0;					//蓝色D-低电平						
        }
    }
    
    Drv_StepMotor();
}
/****************************************************************************************************
Function Name       :void Log_StepMotor_SweepAuto(U16	u16_target1, U16	u16_target2)
Description         :自动扫风控制
Input               :U16	u16_target1, U16	u16_target2
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Log_StepMotor_SweepAuto(U16	u16_target1, U16	u16_target2)
{
    U16	temp;

    if (u16_target1 > u16_target2)								//必须满足u16_target1 < u16_target2
    {															
        temp = u16_target1;
        u16_target1 = u16_target2;
        u16_target2 = temp;	
    }

    if (F_stepmotor_autodirect)									//自动扫描时候步进电机方向 1：顺时针	
    {
        StepMotor.var.u16_agtarget = u16_target2;
    
        if (StepMotor.var.u16_agcurrent >= u16_target2)
        {
            if (F_stepmotor_autoadd == 0)
            {	
                F_stepmotor_autoadd = 1;
                StepMotor.var.u16_agcurrent -= C_STEPMOTOR_PULSE_OV;    //每次摆风克服自身重力多走C_STEPMOTOR_PULSE_OV个脉冲 20220527
            }	
            else
            {
            	//步进电机达到最大最小角度时停留时间
                if(++StepMotor.var.u8_remaintime > 200) //10ms*200=2s lcx add
                {
					F_stepmotor_autodirect = 0; 
					StepMotor.var.u8_remaintime = 0;
                }
                
            }
        }						
    }
    else														//自动扫描时候步进电机方向 0：逆时针
    {
        StepMotor.var.u16_agtarget = u16_target1;		
    
        if (StepMotor.var.u16_agcurrent <= u16_target1)
        {
			//步进电机达到最大最小角度时停留时间
			if(++StepMotor.var.u8_remaintime > 200) //10ms*200=2s lcx add
			{
				F_stepmotor_autodirect = 1; 
				F_stepmotor_autoadd = 0;
				StepMotor.var.u8_remaintime = 0;
			}      
        }
    }
}
