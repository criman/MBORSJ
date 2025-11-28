/***************************************************************
*Copyright (C), 2021, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名：  system_ES8H018x.c
*作  者：  AE Team
*版  本：  V1.00
*日  期：  2021/11/4
*描  述：  库函数配置文件
*备  注：
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
 * limitations under the License.
***************************************************************/
#include "system_ES8H018x.h"
#include "ES8H018x.h"
#include "lib_config.h"

uint32_t SystemCoreClock = 16000000;

/***************************************************************
函数名：SystemCoreClockUpdate
描  述：系统时钟配置为内部时钟HRC，同时设置SystemCoreClock
输入值：无
输出值：无
返回值：无
***************************************************************/
void SystemCoreClockUpdate(void)
{
    uint32_t Prot_Temp;
    uint16_t Count = 0;
    SystemClockSelect(CLK_SEL_HRC);        //选择系统时钟为HRC时钟
    PLLClock_Config(ENUM_DISABLE, SCU_PLL_HRC, SCU_PLL_48M, ENUM_ENABLE);   //PLL禁止
    Prot_Temp = SCU->PROT.PROT;

    if (Prot_Temp != 0)                                     //写保护了
    {
        SCU->PROT.Word = 0x55AA6996; //解锁
    }

    SCU->SCLKEN1.HRC_EN = 1;                                //使能内部HRC

    do
    {
        Count++;
    }
    while ((SCU->SCLKEN1.HRC_RDY == 0) && (Count != 0xFFF)); //等待时钟开启

    if (Count == 0xFFF)
    {
        return ;
    }

    SCU->SCLKEN0.SYSCLK_DIV = 0;                            //系统时钟后分频1:1

    switch (SCU->SCLKEN0.CLK_SEL)
    {
        case 0:
            if (SCU->SCLKEN1.HRC_SEL == SCU_HRC_2M)
                SystemCoreClock = 2000000;                      //HRC:2MHz
            else if (SCU->SCLKEN1.HRC_SEL == SCU_HRC_16M)
                SystemCoreClock = 16000000;                     //HRC:16MHz
            else if (SCU->SCLKEN1.HRC_SEL == SCU_HRC_32M)
                SystemCoreClock = 32000000;                     //HRC:32MHz
            else if (SCU->SCLKEN1.HRC_SEL == SCU_HRC_48M)
                SystemCoreClock = 48000000;                     //HRC:48MHz

            break;

        case 1:
            SystemCoreClock = 32000;                        //LRC
            break;

        default:
            break;
    }

    if (Prot_Temp != 0)                                     //写保护了
    {
        SCU->PROT.Word = 0x00000000; //打开写保护
    }
}

/***************************************************************
函数名：SystemInit
描  述：系统初始化，设置时钟
输入值：无
输出值：无
返回值：无
***************************************************************/
void SystemInit(void)
{
    SystemCoreClockUpdate();
}

/*************************END OF FILE**********************/
