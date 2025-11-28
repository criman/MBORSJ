/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: WaterBox.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/12
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"


STRUCT_WATERBOX    WaterBox;

/****************************************************************************************************
Function Name       :void	Func_WaterBox(void)
Description         :水箱信号处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_WaterBox(void)
{

}
//{
////	WaterBox.f_SW1_Full = !F_switch_sw1_old;	//0:代表断开 1:代表短接	
////	WaterBox.f_SW2_Full = !F_switch_sw2_old;	//0:代表断开 1:代表短接
//
//	if (WaterBox.f_SW1_Full == 0)
//	{
//		if (F_switch_sw1_old == 0)
//		{
//			if (++WaterBox.u16_SW1FullCount >= 500)	//持续5s
//			{
//				WaterBox.u16_SW1FullCount = 0;
//				WaterBox.f_SW1_Full = 1;
//			}
//		}
//		else
//		{
//			WaterBox.u16_SW1FullCount = 0;
//		}
//		
//		WaterBox.u16_SW1NormalCount = 0;
//	}
//	else
//	{
//		if (F_switch_sw1_old == 1)
//		{
//			if (++WaterBox.u16_SW1NormalCount >= 500)	//持续5s
//			{
//				WaterBox.u16_SW1NormalCount = 0;
//				WaterBox.f_SW1_Full = 0;
//			}
//		}
//		else
//		{
//			WaterBox.u16_SW1NormalCount = 0;
//		}
//		
//		WaterBox.u16_SW1FullCount = 0;
//	}
//
//	//-----
//	
//	if (WaterBox.f_SW2_Full == 0)
//	{
//		if (F_switch_sw2_old == 0)
//		{
//			if (++WaterBox.u16_SW2FullCount >= 500)	//持续5s
//			{
//				WaterBox.u16_SW2FullCount = 0;
//				//WaterBox.f_SW2_Full = 1;
//			}
//		}
//		else
//		{
//			WaterBox.u16_SW2FullCount = 0;
//		}
//		
//		WaterBox.u16_SW2NormalCount = 0;
//	}
//	else
//	{
//		if (F_switch_sw2_old == 1)
//		{
//			if (++WaterBox.u16_SW2NormalCount >= 500)	//持续5s
//			{
//				WaterBox.u16_SW2NormalCount = 0;
//				WaterBox.f_SW2_Full = 0;
//			}
//		}
//		else
//		{
//			WaterBox.u16_SW2NormalCount = 0;
//		}
//		
//		WaterBox.u16_SW2FullCount = 0;
//	}	
//
//	//-----
//	/*
//	//N款水位保护逻辑 lcx 2024029
//	if (WaterBox.f_SW1_Full && WaterBox.f_SW2_Full)
//	{
//		WaterBox.f_Full = 1;
//		WaterBox.f_WatLow = 0;
//	}
//	else if (WaterBox.f_SW1_Full || WaterBox.f_SW2_Full)
//	{
//		WaterBox.f_Full = 0;
//		WaterBox.f_WatLow = 1;	
//	}
//	else
//	{
//		WaterBox.f_Full = 0;
//		WaterBox.f_WatLow = 0;	
//	}
//	*/
//
//	//M款水位保护逻辑 lcx 2024029
//	if (WaterBox.f_SW1_Full)
//	{
//		WaterBox.f_Full = 1;
//		WaterBox.f_WatLow = 0;
//	}
//	else
//	{
//		WaterBox.f_Full = 0;
//		WaterBox.f_WatLow = 0;	
//	}
//
//	
//}
