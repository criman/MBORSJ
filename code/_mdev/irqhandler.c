/*************************************************************************
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 **************************************************************************/
#include "irqhandler.h"
#include "lib_wdt.h"
#include "systick.h"

void NMI_IRQHandler(void)
{

}

void HardFault_IRQHandler(void)
{
    while (1)
    {
    }
}

void SVC_IRQHandler(void)
{

}

void PendSV_IRQHandler(void)
{

}

void SysTick_IRQHandler(void)
{
    TimingDelay_Decrement();
}


/*********************************************************
函数名: void T16N0_IRQHandler(void)
描  述: T16N0定时中断函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if (TIMER_T16N0_ENABLE == CF_ENABLE)

void T16N0_IRQHandler(void)
{
    if (T16Nx_GetITStatus(T16N0, TIM_IT_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N0, TIM_IF_MAT0);
	
		//125us中断
		if (++Sys.u8_1ms_count >= 8)
		{
			Sys.u8_1ms_count = 0;
			Sys.f_1ms = 1;					                //1ms标志位
			EEP.f_1ms = 1;
			
			if (++Sys.u8_isr10ms_count >= 10)               //1ms*10=10ms
			{
				Sys.u8_isr10ms_count = 0;
				App_Event_10ms();
				
				if (++Sys.u8_isr100ms_count >= 10)          //10ms*10=100ms
				{
					Sys.u8_isr100ms_count = 0;
					App_Event_100ms();
				}
			}         
		}		
    }
}

#endif
/*********************************************************
函数名: void T16N1_IRQHandler(void)
描  述: T16N1定时中断函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if (TIMER_T16N1_ENABLE == CF_ENABLE)

void T16N1_IRQHandler(void)
{
    if (T16Nx_GetITStatus(T16N1, TIM_IT_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N1, TIM_IF_MAT0);

    }
}

#endif
/*********************************************************
函数名: void T16N2_IRQHandler(void)
描  述: T16N2定时中断函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if (TIMER_T16N2_ENABLE == CF_ENABLE)

void T16N2_IRQHandler(void)
{
    if (T16Nx_GetITStatus(T16N2, TIM_IT_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N2, TIM_IF_MAT0);

    }
}

#endif
/*********************************************************
函数名: void T16N3_IRQHandler(void)
描  述: T16N3定时中断函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if (TIMER_T16N3_ENABLE == CF_ENABLE)

void T16N3_IRQHandler(void)
{
    if (T16Nx_GetITStatus(T16N3, TIM_IT_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N3, TIM_IF_MAT0);

    }
}

#endif
/*********************************************************
函数名: void UART0_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if defined    UART0_ENABLE

void UART0_IRQHandler(void)
{
	
	Uart0_Interrupt();	

}

#endif
/*********************************************************
函数名: void UART1_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if defined    UART1_ENABLE

void UART1_IRQHandler(void)
{
	
	Uart1_Interrupt();	

}

#endif
/*********************************************************
函数名: void UART2_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if defined    UART2_ENABLE

void UART2_IRQHandler(void)
{
	
	Uart2_Interrupt();	

}

#endif
/*********************************************************
函数名: void UART3_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if defined    UART3_ENABLE

void UART3_IRQHandler(void)
{
	
	Uart3_Interrupt();	

}

#endif

#if defined    UART3_lhh
void UART3_IRQHandler(void)
{
	
	//Uart3_Interrupt();	
  	Uart3_Interrupt_lhh();	
}

#endif

/*********************************************************
函数名: void UART4_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if defined    UART4_ENABLE

void UART4_IRQHandler(void)
{
	
	Uart4_Interrupt();	

}

#endif
/*********************************************************
函数名: void UART5_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if defined    UART5_ENABLE

void UART5_IRQHandler(void)
{
	
	Uart5_Interrupt();	

}

#endif
/*********************************************************
函数名: void LVD_IRQHandler(void)
描  述: LVD中断程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
#if (LVD_ENABLE == CF_ENABLE)

void CCM_LVD_PLK_IRQHandler(void)
{
    if ((SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) == SET) && (SCU_GetLVDITStatus() == SET))
    {
        SCU_RegUnLock();
        SCU_LVDClearIFBit();
        SCU_RegLock();

		//teset

    }
}

#endif
