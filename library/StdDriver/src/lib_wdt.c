/***************************************************************
 *文件名：  lib_wdt.c
 *作  者：  AE Team
 *版  本：  V1.00
 *日  期：  2021/11/3
 *描  述：  看门狗模块库函数
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
#include "lib_wdt.h"

/*************************************
  函数名：IWDT_Init
  描  述：IWDT初始化
  输入值：初始化结构体
  返回值：无
 **************************************/
void IWDT_Init(IWDT_InitStruType *WDT_InitStruct)
{
    uint32_t tmp;

    if (WDT_InitStruct->WDT_Clock != WDT_CLOCK_PCLK)
        tmp = (uint32_t)(32 * WDT_InitStruct->WDT_Tms);
    else
        tmp = SystemCoreClock / 1000 * WDT_InitStruct->WDT_Tms;

    IWDT->LOAD.LOAD = tmp;
    IWDT->CON.CLKS = WDT_InitStruct->WDT_Clock;
    IWDT->CON.IE = WDT_InitStruct->WDT_IE;
    IWDT->CON.RSTEN = WDT_InitStruct->WDT_Rst;

    return;
}


/*************************************
  函数名：IWDT_SetReloadValue
  描  述：设置WDT重载的初值
  输入值：初始值，32-bit无符号整数
  返回值：无
 **************************************/
void IWDT_SetReloadValue(uint32_t Value)
{
    IWDT->LOAD.LOAD = Value;
    return;
}

/*************************************
  函数名：IWDT_GetValue
  描  述：获取WDT当前值
  输入值：无
  返回值：当前值
 **************************************/
uint32_t IWDT_GetValue(void)
{
    return (uint32_t)IWDT->VALUE.VALUE;
}

/*************************************
  函数名：IWDT_GetFlagStatus
  描  述：获取WDT中断状态
  输入值：无
  返回值：SET/RESET
 **************************************/
FlagStatus IWDT_GetFlagStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (IWDT->RIS.IWDTIF != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************************
  函数名：IWDT_GetITStatus
  描  述：获取WDT使能中断状态
  输入值：无
  返回值：SET/RESET
 **************************************/
FlagStatus IWDT_GetITStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (IWDT->CON.IE != RESET)
        bitstatus = SET;

    return  bitstatus;
}


/*************************************
  函数名：WWDT_Init
  描  述：WWDT初始化
  输入值：初始化结构体
  返回值：无
 **************************************/
void WWDT_Init(WWDT_InitStruType *WDT_InitStruct)
{
    uint32_t tmp;

    if (WDT_InitStruct->WDT_Clock != WDT_CLOCK_PCLK)
        tmp = (uint32_t)(32 * WDT_InitStruct->WDT_Tms);
    else
        tmp = SystemCoreClock / 1000 * WDT_InitStruct->WDT_Tms;

    WWDT->LOAD.LOAD = tmp;
    WWDT->CON.CLKS = WDT_InitStruct->WDT_Clock;
    WWDT->CON.IE = WDT_InitStruct->WDT_IE;
    WWDT->CON.RSTEN = WDT_InitStruct->WDT_Rst;
    WWDT->CON.WWDTWIN = WDT_InitStruct->WDT_Win;

    return;
}

/*************************************
  函数名：WWDT_SetReloadValue
  描  述：设置WDT重载的初值
  输入值：初始值，32-bit无符号整数
  返回值：无
 **************************************/
void WWDT_SetReloadValue(uint32_t Value)
{
    WWDT->LOAD.LOAD = Value;
    return;
}

/*************************************
  函数名：WWDT_GetValue
  描  述：获取WDT当前值
  输入值：无
  返回值：当前值
 **************************************/
uint32_t WWDT_GetValue(void)
{
    return (uint32_t)WWDT->VALUE.VALUE;
}

/*************************************
  函数名：WWDT_GetFlagStatus
  描  述：获取WDT中断状态
  输入值：无
  返回值：SET/RESET
 **************************************/
FlagStatus WWDT_GetFlagStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (WWDT->RIS.WWDTIF != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************************
  函数名：WWDT_GetIEStatus
  描  述：获取WDT中断使能状态
  输入值：无
  返回值：SET/RESET
 **************************************/
FlagStatus WWDT_GetITStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (WWDT->CON.IE != RESET)
        bitstatus = SET;

    return  bitstatus;
}


/*************************END OF FILE**********************/


