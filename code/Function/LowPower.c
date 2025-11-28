/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: LowPower.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/18
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

ENUM_LOWPOWER      Enum_LowPower;

STRUCT_LOWPOWER    PowEn12V;
STRUCT_LOWPOWER    PowEnPTC;
STRUCT_LOWPOWER    PowEnPTCB;

U8    U8_LowPower_Step;
/****************************************************************************************************
Function Name       :void    Init_LowPower(void)
Description         :低功耗控制初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_LowPower(void)
{
    //PowEn12V
	P_PowEn12V_Off();  
    P_PowEn12V_Output();	
	P_PowEn12V_Dispull();
	
	//PowEnPTC(小)
	P_PowEnPTC_Off();  
    P_PowEnPTC_Output();	
	P_PowEnPTC_Dispull();	
	
	//PowEnPTCB(大)
	P_PowEnPTCB_Off();  
    P_PowEnPTCB_Output();	
	P_PowEnPTCB_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Func_LowPower(void)
Description         :低功耗控制功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_LowPower(void)
{
	if (Enum_LowPower == ENUM_LOWPOWER_INIT)//(System.Enum_Status == ENUM_STATUS_INIT)
	{
		PowEn12V.f_AppOn = ON;
		PowEnPTC.f_AppOn = ON;	
		PowEnPTCB.f_AppOn = ON;
		
		if (PowEn12V.f_InitOk == 0)
		{	
			PowEn12V.f_InitOk = 1;
			PowEn12V.u16_Delay = 50;	//500ms
		}
		
		if (PowEnPTC.f_InitOk == 0)
		{
			PowEnPTC.f_InitOk = 1;
			PowEnPTC.u16_Delay = 500;	
		}
		
		if (PowEnPTCB.f_InitOk == 0)
		{
			PowEnPTCB.f_InitOk = 1;
			PowEnPTCB.u16_Delay = 500;	
		}		
		
		System.u16_OffCount = 0;
		
		if ((PowEn12V.f_DrvOn == ON) && (PowEnPTCB.f_DrvOn == ON) && (PowEnPTC.f_DrvOn == OFF))
		{
			Enum_LowPower = ENUM_LOWPOWER_GO;
		}
	}
	else if (System.Enum_Status == ENUM_STATUS_OFF)
	{
		if ((Comp.f_DrvOn == OFF) && (Fan.Indoor.f_DrvOn == OFF) && (Fan.Outdoor.f_DrvOn == OFF) &&
			(FourWay.f_DrvOn == OFF) && (WPMotor.f_DrvOn == OFF) && (UVC.f_DrvOn == OFF) && (EAHeater.f_DrvOn == OFF) && (DCFan.f_DrvOn == OFF))
		{
			if ((PowEn12V.f_FirstOk == 0) || (PowEnPTCB.f_FirstOk == 0))
			{
				if (System.u16_OffCount >= 350)	//35s
				{
//					PowEn12V.f_AppOn = OFF;
//					PowEnPTC.f_AppOn = OFF;	
//					PowEnPTCB.f_AppOn = OFF;	
				}	
			}
			else
			{
				if (System.u16_OffCount >= 3000)	//5min
				{
//					PowEn12V.f_AppOn = OFF;
//					PowEnPTC.f_AppOn = OFF;
//					PowEnPTCB.f_AppOn = OFF;	
				}
			}			
		}
		else
		{
			System.u16_OffCount = 0;
		}
	}
	else 
	{
		PowEn12V.f_AppOn = ON;
		PowEnPTCB.f_AppOn = ON;	
		PowEnPTC.f_AppOn = ON;	

		System.u16_OffCount = 0;		

	}	
	
	//---------------

/*	
	if ((PowEn12V.f_DrvOn == OFF) && (PowEnPTC.f_DrvOn == OFF))
	{
		if (PowEn12V.f_AppOn == ON)
		{
			if (PowEn12V.u16_Delay == 0)
			{
				PowEn12V.f_DrvOn = ON;
				PowEnPTC.u16_Delay = 50;
				PowEn12V.u16_Delay = 50;
			}
			else
			{
				PowEn12V.u16_Delay -= 1;
			}
		}
	}
	else if (PowEnPTC.f_DrvOn == OFF)
	{
		if (PowEnPTC.f_AppOn == ON)
		{
			if (PowEnPTC.u16_Delay == 0)
			{
				PowEnPTC.f_DrvOn = ON;
				PowEnPTC.u16_Delay = 50;
				PowEn12V.u16_Delay = 50;
			}
			else 
			{
				PowEnPTC.u16_Delay -= 1;
			}
		}
	}
	else if ((PowEn12V.f_DrvOn == ON) && (PowEnPTC.f_DrvOn == ON))
	{
		if (PowEnPTC.f_AppOn == OFF)
		{
			if (PowEnPTC.u16_Delay == 0)
			{
				PowEnPTC.f_FirstOk = 1;
				PowEnPTC.f_DrvOn = OFF;
				PowEnPTC.u16_Delay = 50;
				PowEn12V.u16_Delay = 50;
			}
			else
			{
				PowEnPTC.u16_Delay -= 1;
			}
		}
	}
	else if (PowEn12V.f_DrvOn == ON)
	{
		if (PowEn12V.f_AppOn == OFF)
		{
			if (PowEn12V.u16_Delay == 0)
			{
				PowEn12V.f_FirstOk = 1;
				PowEn12V.f_DrvOn = OFF;
				PowEnPTC.u16_Delay = 50;
				PowEn12V.u16_Delay = 50;				
			}
			else
			{
				PowEn12V.u16_Delay -= 1;
			}
		}
	}
*/	
	
	if ((Enum_LowPower == ENUM_LOWPOWER_INIT) || (System.Enum_Status != ENUM_STATUS_OFF) || (U8_LowPower_Step < 4))
	{
		if ((PowEn12V.f_DrvOn == OFF) && (PowEnPTC.f_DrvOn == OFF) && (PowEnPTCB.f_DrvOn == OFF))
		{
			if (PowEn12V.f_AppOn == ON)
			{
				if (PowEn12V.u16_Delay == 0)
				{
					PowEn12V.f_DrvOn = ON;
					PowEnPTCB.u16_Delay = 500;
					PowEnPTC.u16_Delay = 50;
					PowEn12V.u16_Delay = 50;

					U8_LowPower_Step = 1;
				}
				else
				{
					PowEn12V.u16_Delay -= 1;
				}
			}
			
			
			//驱动断电通信异常变量全清0
			Uart0.u16_AbnormalCount = 0;                  //收到完整数据，清零通讯超时计数
			F_uart0_TimeOut = CF_DISABLE;                //通讯正常
			F_uart0_CommErr = CF_DISABLE;
			Uart0.u16_ErrCount = 0;  			
		}
		else if ((PowEn12V.f_DrvOn == ON) && (PowEnPTC.f_DrvOn == OFF) && (PowEnPTCB.f_DrvOn == OFF))
		{
			if (PowEnPTC.f_AppOn == ON)
			{
				if (PowEnPTC.u16_Delay == 0)
				{
					PowEnPTC.f_DrvOn = ON;
					PowEnPTCB.u16_Delay = 500;
					PowEnPTC.u16_Delay = 50;
					PowEn12V.u16_Delay = 50;	

					U8_LowPower_Step = 2;
				}
				else
				{
					PowEnPTC.u16_Delay -= 1;
				}
			}
		}
		else if ((PowEn12V.f_DrvOn == ON) && (PowEnPTC.f_DrvOn == ON) && (PowEnPTCB.f_DrvOn == OFF))
		{
			if (PowEnPTCB.f_AppOn == ON)
			{
				if (PowEnPTCB.u16_Delay == 0)
				{
					PowEnPTCB.f_DrvOn = ON;
					PowEnPTCB.u16_Delay = 500;
					PowEnPTC.u16_Delay = 200;
					PowEn12V.u16_Delay = 50;

					U8_LowPower_Step = 3;
				}
				else
				{
					PowEnPTCB.u16_Delay -= 1;
				}
			}		
		}
		else if ((PowEn12V.f_DrvOn == ON) && (PowEnPTC.f_DrvOn == ON) && (PowEnPTCB.f_DrvOn == ON))
		{
			PowEnPTC.f_AppOn = OFF;
			
			if (PowEnPTC.f_AppOn == OFF)
			{
				if (PowEnPTC.u16_Delay == 0)
				{
					PowEnPTC.f_DrvOn = OFF;
					PowEnPTCB.u16_Delay = 500;
					PowEnPTC.u16_Delay = 50;
					PowEn12V.u16_Delay = 50;	

					U8_LowPower_Step = 4;
				}
				else
				{
					PowEnPTC.u16_Delay -= 1;
				}
			}		
		}
	}
	else if ((U8_LowPower_Step >= 4) && (System.Enum_Status == ENUM_STATUS_OFF))
	{
		if ((PowEn12V.f_DrvOn == ON) && (PowEnPTCB.f_DrvOn == ON))
		{
			if (PowEnPTCB.f_AppOn == OFF)
			{
				if (PowEnPTCB.u16_Delay == 0)
				{
					PowEnPTCB.f_FirstOk = 1;
					PowEnPTCB.f_DrvOn = OFF;
					PowEnPTC.f_DrvOn = OFF;
					PowEnPTCB.u16_Delay = 500;
					PowEnPTC.u16_Delay = 50;
					PowEn12V.u16_Delay = 50;
				}
				else
				{
					PowEnPTCB.u16_Delay -= 1;
				}
			}
			
		}
		else if (PowEn12V.f_DrvOn == ON)
		{
			if (PowEn12V.f_AppOn == OFF)
			{
				if (PowEn12V.u16_Delay == 0)
				{
					PowEn12V.f_FirstOk = 1;
					PowEn12V.f_DrvOn = OFF;
					PowEnPTCB.u16_Delay = 500;
					PowEnPTC.u16_Delay = 50;
					PowEn12V.u16_Delay = 50;				
				}
				else
				{
					PowEn12V.u16_Delay -= 1;
				}			
			}
		}
		else
		{
			U8_LowPower_Step = 0;
			
		}
	}
	


	//---------------
	P_PowEn12V_On();
//	if (PowEn12V.f_DrvOn)	P_PowEn12V_On();
//	else					P_PowEn12V_Off();
	
	if (PowEnPTC.f_DrvOn)	P_PowEnPTC_On();
	else					P_PowEnPTC_Off();	
	
	if (PowEnPTCB.f_DrvOn)	P_PowEnPTCB_On();
	else					P_PowEnPTCB_Off();	
}
