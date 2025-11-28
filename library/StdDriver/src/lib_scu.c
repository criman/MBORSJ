/***************************************************************
 *文件名：  lib_scu.c
 *作  者：  AE Team
 *版  本：  V1.00
 *日  期：  2021/11/3
 *描  述：  系统控制模块库函数
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
#include "lib_scu.h"

/***************************************************************
  函数名：SCU_OpenXTAL
  描  述: 开启外部时钟
  输入值：无
  输出值：无
  返回值：系统时钟源
 ***************************************************************/
void SCU_OpenXTAL(void)
{
    SCU_RegUnLock();
    SCU->SCLKEN1.XTAL_EN = 1;

    while (SCU->SCLKEN1.XTAL_RDY == 0); //等待外部时钟稳定

    SCU_RegLock() ;
}

/***************************************************************
  函数名：SCU_NMISelect
  描  述：设置NMI不可屏蔽中断
  输入值：不可屏蔽中断
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_NMISelect(SCU_TYPE_NMICS NMI_Type)
{
    SCU_RegUnLock();
    SCU->NMICON.NMICS = NMI_Type;
    SCU_RegLock() ;
}

/***************************************************************
  函数名：SCU_GetPWRCFlagStatus
  描  述：获取PWRC复位状态寄存器标志位状态
  输入值：PWRC寄存器标志位
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
FlagStatus SCU_GetPWRCFlagStatus(SCU_TYPE_PWRC PWRC_Flag)
{
    FlagStatus bitstatus = RESET;

    if ((SCU->PWRC.Word & (uint32_t)PWRC_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：SCU_ClearPWRCFlagBit
  描  述：清除PWRC复位状态寄存器标志位
  输入值：PWRC寄存器标志位
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_ClearPWRCFlagBit(SCU_TYPE_PWRC PWRC_Flag)
{
    SCU_RegUnLock() ;
    SCU->PWRC.Word &= ~((uint32_t)PWRC_Flag);
    SCU_RegLock() ;
}

/***************************************************************
  函数名：SCU_GetLVDFlagStatus
  描  述：获取LVDD寄存器标志位状态
  输入值：LVD寄存器标志位
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
FlagStatus  SCU_GetLVDFlagStatus(SCU_TYPE_LVD0CON LVD_Flag)
{
    FlagStatus bitstatus = RESET;

    if ((SCU->LVDCON.Word & (uint32_t)LVD_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：SCU_GetLVDITStatus
  描  述：获取LVD中断使能状态
  输入值：无
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
FlagStatus  SCU_GetLVDITStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (SCU->LVDCON.IE == 1)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}


/***************************************************************
  函数名：SCU_SysClkSelect
  描  述：选择系统时钟
  输入值：时钟源
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_SysClkSelect(SCU_TYPE_CLK_SEL Sysclk)
{
    SCU_RegUnLock() ;
    SCU->SCLKEN0.CLK_SEL = Sysclk;
    SCU_RegLock() ;
}

/***************************************************************
  函数名：SCU_GetSysClk
  描  述：获取系统时钟源
  输入值：无
  输出值：无
  返回值：系统时钟源
 ***************************************************************/
SCU_TYPE_SYSCLK SCU_GetSysClk(void)
{
    return (SCU_TYPE_SYSCLK)(SCU->SCLKEN0.CLK_SEL);
}

/***************************************************************
  函数名：SCU_HRCReadyFlag
  描  述：获取HRC稳定标志位
  输入值：无
  输出值：无
  返回值：RESET（不稳定）/SET（稳定）
 ***************************************************************/
FlagStatus SCU_HRCReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if ((SCU->SCLKEN1.HRC_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：SCU_XTALReadyFlag
  描  述：获取XTAL稳定标志位
  输入值：无
  输出值：无
  返回值：RESET（不稳定）/SET（稳定）
 ***************************************************************/
FlagStatus SCU_XTALReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if ((SCU->SCLKEN1.XTAL_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：SCU_LOSCReadyFlag
  描  述：获取LOSC稳定标志位
  输入值：无
  输出值：无
  返回值：RESET（不稳定）/SET（稳定）
 ***************************************************************/
FlagStatus SCU_PLLReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if ((SCU->SCLKEN1.PLL_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
 函数名：SystemClockConfig
 描  述：系统时钟配置：内部时钟HRC，打开所有外设时钟
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void SystemClockConfig(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;

    if (Prot_Temp != 0)                     //写保护了
        SCU_RegUnLock();                    //解锁

    SCU_HRC_Enable();                       //使能内部HRC

    while (SCU_HRCReadyFlag() != SET);      //等待时钟开启

    SCU_SysClkSelect(CLK_SEL_HRC);       //选择内部HRC为系统时钟

    SCU_SysClk_Div1();                      //系统时钟后分频1:1

    if (SCU->SCLKEN1.HRC_SEL == SCU_HRC_2M)
        SystemCoreClock = 2000000;                      //HRC:2MHz
    else if (SCU->SCLKEN1.HRC_SEL == SCU_HRC_16M)
        SystemCoreClock = 16000000;                     //HRC:16MHz
    else if (SCU->SCLKEN1.HRC_SEL == SCU_HRC_32M)
        SystemCoreClock = 32000000;                     //HRC:32MHz
    else if (SCU->SCLKEN1.HRC_SEL == SCU_HRC_48M)
        SystemCoreClock = 48000000;                     //HRC:48MHz

    if (Prot_Temp != 0)                     //写保护了
        SCU_RegLock();                      //上锁
}

/***************************************************************
  函数名：DeviceClockAllEnable
  描  述：打开所有外设时钟
  输入值：无
  输出值：无
  返回值：无
 ***************************************************************/
void DeviceClockAllEnable(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;

    if (Prot_Temp != 0)                     //写保护了
        SCU_RegUnLock();                    //解锁

    SCU->PCLKEN0.Word = 0xFFFFFFFF;
    SCU->PCLKEN1.Word = 0xFFFFFFFF;         //打开所有外设时钟

    if (Prot_Temp != 0)                     //写保护了
        SCU_RegLock();                      //打开写保护
}

/***************************************************************
  函数名：DeviceClockAllDisable
  描  述：关闭所有外设时钟
  输入值：无
  输出值：无
  返回值：无
 ***************************************************************/
void DeviceClockAllDisable(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;

    if (Prot_Temp != 0)                     //写保护了
        SCU_RegUnLock();                    //解锁

    SCU->PCLKEN0.Word = 0x00000000;         //关闭所有外设时钟，scu无法关闭
    SCU->PCLKEN1.Word = 0x00000000;

    if (Prot_Temp != 0)                     //写保护了
        SCU_RegLock();                  //打开写保护
}

/***************************************************************
  函数名: DeviceClockAllEnableButIAP
  描  述: 打开除IAP模块以外所有外设时钟
  输入值: 无
  输出值: 无
  返回值: 无
 ***************************************************************/
void DeviceClockAllEnableButIAP(void)
{
    uint32_t prot_tmp;
    prot_tmp = SCU->PROT.PROT;

    if (prot_tmp != 0)                 //写保护已开
        SCU_RegUnLock();               //解锁写保护

    SCU->PCLKEN0.Word = 0xFFFFFFFB;
    SCU->PCLKEN1.Word = 0xFFFFFFFF;    //打开除IAP以外所有外设时钟

    if (prot_tmp != 0)                 //写保护已开
        SCU_RegLock();                 //打开写保护

    return;
}

/***************************************************************
  函数名：SystemClockSelect
  描  述：系统时钟选择
  输入值：CLKx 系统时钟源选择
  输出值：无
  返回值：无
 ***************************************************************/
void SystemClockSelect(SCU_TYPE_CLK_SEL CLK_SEL)
{
    SCU_RegUnLock();                        //解锁

    switch (CLK_SEL)
    {
        case CLK_SEL_HRC:
            SCU_HRC_Enable();

            while (SCU_HRCReadyFlag() != SET);

            break;

        case CLK_SEL_XTAL:
            SCU_XTAL_Enable();

            while (SCU_XTALReadyFlag() != SET);

            break;

        default:
            break;
    }

    SCU->SCLKEN0.CLKFLT_BY = 0; //系统时钟不为48M，不旁路时钟滤波
    SCU->SCLKEN0.SYSCLK_DIV = 0;
    SCU->SCLKEN0.CLK_SEL = CLK_SEL;

    SCU_RegLock();
}

void SystemHRCSelect(SCU_HRC_SEL hrc)
{
    SCU_RegUnLock();                        //解锁
    SCU->SCLKEN1.HRC_SEL = hrc;
    SCU_RegLock();
}

/***************************************************************
  函数名：PLLClock_Config
  描  述：PLL时钟配置,并设置PLL时钟为系统时钟
  输入值：pll_en:是否开启PLL，pll_origin：pll时钟源选择，pll_out：pll输出频率选择，sys_pll：系统时钟是否使用PLL时钟
  输出值：无
  返回值：无
 ***************************************************************/
void PLLClock_Config(TYPE_FUNCEN pll_en, SCU_PLL_Origin  pll_origin, SCU_PLL_Out pll_out, TYPE_FUNCEN sys_pll)
{
    uint32_t i_buf;
    uint32_t n_buf = 29000;

    SCU_RegUnLock();

    if (pll_en == ENUM_DISABLE) //如果PLL配置为禁止，则直接禁止PLL，并返回
    {
        SCU->SCLKEN0.PLL_MUX = 0;
        SCU->SCLKEN1.PLL_BYLOCK = 0;
        SCU->SCLKEN0.CLKFLT_BY = 0x00;
        SCU->SCLKEN1.PLL_EN = 0;
        return;
    }

    if ((pll_origin == SCU_PLL_HRC))        //如果使用内部高速时钟，需开启内部高速时钟
    {
        if (SCU->SCLKEN1.HRC_RDY == 0)
        {
            SCU->SCLKEN1.HRC_EN = 1;

            while (SCU->SCLKEN1.HRC_RDY == 0); //等待HRC开启
        }
    }

    if ((pll_origin == SCU_PLL_XTAL_32K)
            || (pll_origin == SCU_PLL_XTAL_4M)
            || (pll_origin == SCU_PLL_XTAL_8M)
            || (pll_origin == SCU_PLL_XTAL_16M)
            || (pll_origin == SCU_PLL_XTAL_20M))          //如果使用外部时钟，需开启外部时钟
    {
        if (SCU->SCLKEN1.XTAL_RDY == 0)
        {
            SCU->SCLKEN1.XTAL_EN = 1;

            while (SCU->SCLKEN1.XTAL_RDY == 0); //等待XTAL开启
        }
    }

    switch (pll_origin)
    {
        case SCU_PLL_HRC:
            SCU->SCLKEN1.PLL_REF_SEL = 0x00;
            break;

        case SCU_PLL_LRC:
            SCU->SCLKEN1.PLL_REF_SEL = 0x02;
            break;

        case SCU_PLL_XTAL_32K:
            SCU->SCLKEN1.PLL_REF_SEL = 0x03;
            break;

        case SCU_PLL_XTAL_4M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x04;
            break;

        case SCU_PLL_XTAL_8M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x05;
            break;

        case SCU_PLL_XTAL_16M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x06;
            break;

        case SCU_PLL_XTAL_20M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x07;
            break;

        default:
            break;
    }

    SCU->SCLKEN1.PLL_48M_SEL = pll_out;   //配置PLL输出为32或48Mhz

    SCU->SCLKEN1.PLL_EN = 1;

    for (i_buf = 0; i_buf < n_buf; i_buf++)    //标志位查询，超时等待时间20ms
    {
        if (SCU->SCLKEN1.PLL_RDY == SET)
            break;
    }

    if (sys_pll == ENUM_ENABLE)
    {

        if (pll_out == SCU_PLL_32M)
        {
            SCU->SCLKEN0.CLKFLT_BY = 0;
        }
        else
        {
            SCU->SCLKEN0.CLKFLT_BY = 0x55;  //48M 时钟滤波旁路
        }

        SCU->SCLKEN1.PLL_BYLOCK = 0;
        SCU->SCLKEN0.PLL_MUX = 1;
    }
    else
    {
        SCU->SCLKEN0.PLL_MUX = 0;
        SCU->SCLKEN1.PLL_BYLOCK = 0;
        SCU->SCLKEN0.CLKFLT_BY = 0x00;
    }

    SCU_RegLock();
}

/***************************************************************
  函数名：SCU_MultTimerEnable
  描  述：多个时钟同时开启(T16N0/1/2/3/4/5,T32N0)
  输入值：SCU_TimerMask：可以是T16N0/1/2/3/4/5和T32N0的任意组合
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_MultTimerEnable(SCU_TIMEREN_Typedef SCU_TimerMask)
{
    SCU_RegUnLock();
    SCU->TIMEREN.Word = SCU_TimerMask.Word;
    SCU_RegLock();
}

/***************************************************************
  函数名：SCU_MultTimerDisable
  描  述：多个时钟同时关闭(T16N0/1/2/3/4/5,T32N0)
  输入值：SCU_TimerMask：可以是T16N0/1/2/3/4/5和T32N0的任意组合
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_MultTimerDisable(SCU_TIMERDIS_Typedef SCU_TimerMask)
{
    SCU_RegUnLock();
    SCU->TIMERDIS.Word = SCU_TimerMask.Word;
    SCU_RegLock();
}

/*************************END OF FILE**********************/



