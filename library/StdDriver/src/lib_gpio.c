/***************************************************************
 *文件名：lib_gpio.c
 *作 者： AE Team
 *版 本： V1.00
 *日 期： 2021/11/3
 *描 述： GPIO库函数
 *备 注：
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
#include "lib_gpio.h"
extern uint32_t SystemCoreClock;
/***************************************************************
  函数名：GPIO_Init
  描  述：GPIO初始化
  输入值：GPIOx：可以是GPIOA/GPIOB 、 PINx：根据芯片选择需要的引脚 、 GPIO_InitStruct：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_Init(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_InitStruType *GPIO_InitStruct)
{
    if (GPIO_InitStruct->GPIO_Signal == GPIO_Pin_Signal_Analog)
    {
        GPIO_SetSingalTypeFromPin(GPIOx, PINx, GPIO_Pin_Signal_Analog);
        GPIO_SetDirRegFromPin(GPIOx, PINx, GPIO_Dir_In);
        GPIO_SetFuncxRegFromPin(GPIOx, PINx, GPIO_Func_0);
        GPIO_SetPUERegFromPin(GPIOx, PINx, GPIO_PUE_Input_Disable);
        GPIO_SetPDERegFromPin(GPIOx, PINx, GPIO_PDE_Input_Disable);
    }
    else
    {
        GPIO_SetSingalTypeFromPin(GPIOx, PINx, GPIO_Pin_Signal_Digital);
        GPIO_SetDirRegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_Direction);
        GPIO_SetFuncxRegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_Func);

        if (GPIO_InitStruct->GPIO_Direction == GPIO_Dir_Out)
        {
            GPIO_SetODERegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_OD);
            GPIO_SetDSRegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_DS);
        }

        GPIO_SetPinType(GPIOx, PINx, GPIO_InitStruct->GPIO_TYP);
        GPIO_SetPinFLT(GPIOx, PINx, GPIO_InitStruct->GPIO_FLT);
        GPIO_SetPUERegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_PUEN);
        GPIO_SetPDERegFromPin(GPIOx, PINx, GPIO_InitStruct->GPIO_PDEN);
    }
}

/***************************************************************
  函数名：GPIO_SetFuncxRegFromPin
  描  述：设置GPIO引脚的功能复用
  输入值：PINx：目的引脚
          Func：功能复用编号
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetFuncxRegFromPin(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_TYPE_FUNC Func)
{
    uint32_t value;

    switch (Func)
    {
        case GPIO_Func_0:
            value = 0;
            break;

        case GPIO_Func_1:
            value = 1;
            break;

        case GPIO_Func_2:
            value = 2;
            break;

        case GPIO_Func_3:
            value = 3;
            break;

        case GPIO_Func_4:
            value = 4;
            break;

        case GPIO_Func_5:
            value = 5;
            break;

        case GPIO_Func_6:
            value = 6;
            break;

        case GPIO_Func_7:
            value = 7;
            break;

        default:
            value = 0;
            break;
    }

    /* 引脚功能设置 */
    if (GPIOx == GPIOB)
    {
        switch (PINx)
        {
            case GPIO_Pin_0:
                GPIO->PBFUNC0.PB0 = value;
                break;

            case GPIO_Pin_1:
                GPIO->PBFUNC0.PB1 = value;
                break;

            case GPIO_Pin_2:
                GPIO->PBFUNC0.PB2 = value;
                break;

            case GPIO_Pin_3:
                GPIO->PBFUNC0.PB3 = value;
                break;

            case GPIO_Pin_4:
                GPIO->PBFUNC0.PB4 = value;
                break;

            case GPIO_Pin_5:
                GPIO->PBFUNC0.PB5 = value;
                break;

            case GPIO_Pin_6:
                GPIO->PBFUNC0.PB6 = value;
                break;

            case GPIO_Pin_7:
                GPIO->PBFUNC0.PB7 = value;
                break;

            case GPIO_Pin_8:
                GPIO->PBFUNC1.PB8 = value;
                break;

            case GPIO_Pin_9:
                GPIO->PBFUNC1.PB9 = value;
                break;

            case GPIO_Pin_10:
                GPIO->PBFUNC1.PB10 = value;
                break;

            case GPIO_Pin_11:
                GPIO->PBFUNC1.PB11 = value;
                break;

            case GPIO_Pin_12:
                GPIO->PBFUNC1.PB12 = value;
                break;

            case GPIO_Pin_13:
                GPIO->PBFUNC1.PB13 = value;
                break;

            case GPIO_Pin_14:
                GPIO->PBFUNC1.PB14 = value;
                break;

            case GPIO_Pin_15:
                GPIO->PBFUNC1.PB15 = value;
                break;

            case GPIO_Pin_16:
                GPIO->PBFUNC2.PB16 = value;
                break;

            case GPIO_Pin_17:
                GPIO->PBFUNC2.PB17 = value;
                break;

            case GPIO_Pin_18:
                GPIO->PBFUNC2.PB18 = value;
                break;

            case GPIO_Pin_19:
                GPIO->PBFUNC2.PB19 = value;
                break;

            case GPIO_Pin_20:
                GPIO->PBFUNC2.PB20 = value;
                break;

            case GPIO_Pin_21:
                GPIO->PBFUNC2.PB21 = value;
                break;

            case GPIO_Pin_22:
                GPIO->PBFUNC2.PB22 = value;
                break;

            case GPIO_Pin_23:
                GPIO->PBFUNC2.PB23 = value;
                break;

            case GPIO_Pin_24:
                GPIO->PBFUNC3.PB24 = value;
                break;

            case GPIO_Pin_25:
                GPIO->PBFUNC3.PB25 = value;
                break;

            case GPIO_Pin_26:
                GPIO->PBFUNC3.PB26 = value;
                break;

            case GPIO_Pin_27:
                GPIO->PBFUNC3.PB27 = value;
                break;

            default:
                break;
        }
    }

    else
    {
        switch (PINx)
        {
            case GPIO_Pin_0:
                GPIO->PAFUNC0.PA0 = value;
                break;

            case GPIO_Pin_1:
                GPIO->PAFUNC0.PA1 = value;
                break;

            case GPIO_Pin_2:
                GPIO->PAFUNC0.PA2 = value;
                break;

            case GPIO_Pin_3:
                GPIO->PAFUNC0.PA3 = value;
                break;

            case GPIO_Pin_4:
                GPIO->PAFUNC0.PA4 = value;
                break;

            case GPIO_Pin_5:
                GPIO->PAFUNC0.PA5 = value;
                break;

            case GPIO_Pin_6:
                GPIO->PAFUNC0.PA6 = value;
                break;

            case GPIO_Pin_7:
                GPIO->PAFUNC0.PA7 = value;
                break;

            case GPIO_Pin_8:
                GPIO->PAFUNC1.PA8 = value;
                break;

            case GPIO_Pin_9:
                GPIO->PAFUNC1.PA9 = value;
                break;

            case GPIO_Pin_10:
                GPIO->PAFUNC1.PA10 = value;
                break;

            case GPIO_Pin_11:
                GPIO->PAFUNC1.PA11 = value;
                break;

            case GPIO_Pin_12:
                GPIO->PAFUNC1.PA12 = value;
                break;

            case GPIO_Pin_13:
                GPIO->PAFUNC1.PA13 = value;
                break;

            case GPIO_Pin_14:
                GPIO->PAFUNC1.PA14 = value;
                break;

            case GPIO_Pin_15:
                GPIO->PAFUNC1.PA15 = value;
                break;

            case GPIO_Pin_16:
                GPIO->PAFUNC2.PA16 = value;
                break;

            case GPIO_Pin_17:
                GPIO->PAFUNC2.PA17 = value;
                break;

            case GPIO_Pin_18:
                GPIO->PAFUNC2.PA18 = value;
                break;

            case GPIO_Pin_19:
                GPIO->PAFUNC2.PA19 = value;
                break;

            case GPIO_Pin_20:
                GPIO->PAFUNC2.PA20 = value;
                break;

            case GPIO_Pin_21:
                GPIO->PAFUNC2.PA21 = value;
                break;

            case GPIO_Pin_22:
                GPIO->PAFUNC2.PA22 = value;
                break;

            case GPIO_Pin_23:
                GPIO->PAFUNC2.PA23 = value;
                break;

            case GPIO_Pin_24:
                GPIO->PAFUNC3.PA24 = value;
                break;

            case GPIO_Pin_25:
                GPIO->PAFUNC3.PA25 = value;
                break;

            case GPIO_Pin_26:
                GPIO->PAFUNC3.PA26 = value;
                break;

            case GPIO_Pin_27:
                GPIO->PAFUNC3.PA27 = value;
                break;

            case GPIO_Pin_28:
                GPIO->PAFUNC3.PA28 = value;
                break;

            case GPIO_Pin_29:
                GPIO->PAFUNC3.PA29 = value;
                break;

            case GPIO_Pin_30:
                GPIO->PAFUNC3.PA30 = value;
                break;

            case GPIO_Pin_31:
                GPIO->PAFUNC3.PA31 = value;
                break;

            default:
                break;
        }
    }

    return;
}

/***************************************************************
  函数名：GPIO_SetSingalTypeFromPin
  描  述：设置引脚的信号类型
  输入值：PINx: 目的引脚
          Signal: 引脚的信号类型
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetSingalTypeFromPin(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_Pin_Signal GPIO_Signal)
{
    if (GPIOx == GPIOB)
    {
        if (GPIO_Signal == GPIO_Pin_Signal_Digital)
            GPIO->PBINEB.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PBINEB.Word |= (1uL << (uint32_t)PINx);
    }
    else
    {
        if (GPIO_Signal == GPIO_Pin_Signal_Digital)
            GPIO->PAINEB.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PAINEB.Word |= (1uL << (uint32_t)PINx);
    }

    return;
}

/***************************************************************
  函数名：GPIO_SetDirRegFromPin
  描  述：设置引脚的输入或输出方向
  输入值：PINx: 目的引脚
          Dir：引脚方向
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetDirRegFromPin(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_TYPE_DIR Dir)
{
    if (GPIOx == GPIOB)
    {
        if (Dir == GPIO_Dir_In)
            GPIO->PBDIRBSR.Word = (1uL << (uint32_t)PINx);
        else
            GPIO->PBDIRBCR.Word = (1uL << (uint32_t)PINx);
    }
    else
    {
        if (Dir == GPIO_Dir_In)
            GPIO->PADIRBSR.Word = (1uL << (uint32_t)PINx);
        else
            GPIO->PADIRBCR.Word = (1uL << (uint32_t)PINx);
    }

    return;
}

/***************************************************************
  函数名：GPIO_SetODERegFromPin
  描  述：设置引脚的输出开漏方式
  输入值：PINx: 目的引脚
          ODE: 输出开漏方式
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetODERegFromPin(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_ODE_Output ODE)
{
    if (GPIOx == GPIOB)
    {
        if (ODE == GPIO_ODE_Output_Disable)
            GPIO->PBODE.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PBODE.Word |= (1uL << (uint32_t)PINx);
    }
    else
    {
        if (ODE == GPIO_ODE_Output_Disable)
            GPIO->PAODE.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PAODE.Word |= (1uL << (uint32_t)PINx);
    }

    return;
}

/***************************************************************
  函数名：GPIO_SetDSRegFromPin
  描  述：设置引脚的输出驱动能力
  输入值：PINx: 目的引脚
          DS: 电流驱动方式
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetDSRegFromPin(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_TYPE_DS DS)
{
    if (GPIOx == GPIOB)
    {
        if (DS == GPIO_DS_Output_Normal)
            GPIO->PBDS.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PBDS.Word |= (1uL << (uint32_t)PINx);
    }
    else
    {
        if (DS == GPIO_DS_Output_Normal)
            GPIO->PADS.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PADS.Word |= (1uL << (uint32_t)PINx);
    }

    return;
}

/***************************************************************
  函数名：GPIO_SetPinType
  描  述：设置引脚端口类型
  输入值：PINx: 目的引脚
          TYP: 端口类型
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetPinType(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_TYPE_TYP TYP)
{
    if (GPIOx == GPIOB)
    {
        if (TYP == GPIO_TYP_CMOS)
            GPIO->PBTYP.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PBTYP.Word |= (1uL << (uint32_t)PINx);
    }
    else
    {
        if (TYP == GPIO_TYP_CMOS)
            GPIO->PATYP.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PATYP.Word |= (1uL << (uint32_t)PINx);
    }

    return;
}

/***************************************************************
  函数名：GPIO_SetPinFLT
  描  述：设置引脚端口滤波开关
  输入值：PINx: 目的引脚
          FLT: 端口滤波是否使能
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetPinFLT(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_TYPE_FLT FLT)
{
    if (GPIOx == GPIOB)
    {
        if (FLT == GPIO_TYP_FLT_DISABLE)
            GPIO->PBFLT.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PBFLT.Word |= (1uL << (uint32_t)PINx);
    }
    else
    {
        if (FLT == GPIO_TYP_FLT_DISABLE)
            GPIO->PAFLT.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PAFLT.Word |= (1uL << (uint32_t)PINx);
    }

    return;
}

/***************************************************************
  函数名：GPIO_SetPUERegFromPin
  描  述：设置引脚的弱上拉方式
  输入值：PINx: 目的引脚
          PUE: 弱上拉方式
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetPUERegFromPin(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_PUE_Input PUE)
{
    if (GPIOx == GPIOB)
    {
        if (PUE == GPIO_PUE_Input_Disable)
            GPIO->PBPUE.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PBPUE.Word |= (1uL << (uint32_t)PINx);
    }
    else
    {
        if (PUE == GPIO_PUE_Input_Disable)
            GPIO->PAPUE.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PAPUE.Word |= (1uL << (uint32_t)PINx);
    }
}

/***************************************************************
  函数名：GPIO_SetPDERegFromPin
  描  述：设置引脚的弱下拉方式
  输入值：PINx: 目的引脚
          PDE：弱下拉方式
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_SetPDERegFromPin(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx, GPIO_PDE_Input PDE)
{
    if (GPIOx == GPIOB)
    {
        if (PDE == GPIO_PDE_Input_Disable)
            GPIO->PBPDE.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PBPDE.Word |= (1uL << (uint32_t)PINx);
    }
    else
    {
        if (PDE == GPIO_PDE_Input_Disable)
            GPIO->PAPDE.Word &= (~(1uL << (uint32_t)PINx));
        else
            GPIO->PAPDE.Word |= (1uL << (uint32_t)PINx);
    }

    return;
}

/***************************************************************
  函数名：GPIO_Write
  描  述：GPIO端口写数据
  输入值：GPIOx：可以是GPIOA/GPIOB 、 Value要写的数据——注意：有些不存在的引脚，设置的值相对应的位是无作用的
  输出值：无
  返回值：无
 ***************************************************************/
void GPIO_Write(GPIO_TYPE GPIOx, uint32_t Value)
{
    if (GPIOx == GPIOA)
        GPIO->PADATA.Word = Value;
    else if (GPIOx == GPIOB)
        GPIO->PBDATA.Word = Value;
}

/***************************************************************
  函数名：GPIO_Read
  描  述：GPIO端口读数据
  输入值：GPIOx：可以是GPIOA/GPIOB
  输出值：无
  返回值：读出的数据——注意：有些不存在的引脚，读出的值相对应的位是无效的
 ***************************************************************/
uint32_t GPIO_Read(GPIO_TYPE GPIOx)
{
    if (GPIOx == GPIOA)
        return GPIO->PAPORT.Word;
    else if (GPIOx == GPIOB)
        return GPIO->PBPORT.Word;

    return 0;
}

/***************************************************************
  函数名：GPIO_ReadBit
  描  述：GPIO端口读某位数据
  输入值：GPIOx：可以是GPIOA/GPIOB 、 PINx:GPIO_Pin_0 —— GPIO_Pin_31
  输出值：无
  返回值：读出的数据——注意：有些不存在的引脚，读出的值是无效的
 ***************************************************************/
PinStatus GPIO_ReadBit(GPIO_TYPE GPIOx, GPIO_TYPE_PIN PINx)
{
    PinStatus bitstatus = RESET;

    if (GPIOx == GPIOA)
    {
        if ((GPIO->PAPORT.Word & (1uL << (uint32_t)PINx)) != RESET)
            bitstatus = SET;
        else
            bitstatus = RESET;
    }
    else if (GPIOx == GPIOB)
    {
        if ((GPIO->PBPORT.Word & (1uL << (uint32_t)PINx)) != RESET)
            bitstatus = SET;
        else
            bitstatus = RESET;
    }

    return bitstatus;
}

/***************************************************************
  函数名：GPIOA_SetBit
  描  述：GPIOA某引脚置1
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_31
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOA_SetBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PADATABSR.Word = 1uL << (uint32_t)PINx;
}

/***************************************************************
  函数名：GPIOA_ResetBit
  描  述：GPIOA某引脚清0
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_31
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOA_ResetBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PADATABCR.Word = 1uL << (uint32_t)PINx;
}

/***************************************************************
  函数名：GPIOA_ToggleBit
  描  述：GPIOA某引脚输出状态取反
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_31
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOA_ToggleBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PADATABRR.Word = 1uL << (uint32_t)PINx;
}

/***************************************************************
  函数名：GPIOB_SetBit
  描  述：GPIOB某引脚置1
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_27
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOB_SetBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PBDATABSR.Word = 1uL << (uint32_t)PINx;
}

/***************************************************************
  函数名：GPIOB_ResetBit
  描  述：GPIOB某引脚清0
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_27
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOB_ResetBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PBDATABCR.Word = 1uL << (uint32_t)PINx;
}

/***************************************************************
  函数名：GPIOB_ToggleBit
  描  述：GPIOB某引脚输出状态取反
  输入值：PINx：可以是GPIO_Pin_0 —— GPIO_Pin_27
  输出值：无
  返回值：无
 ***************************************************************/
void GPIOB_ToggleBit(GPIO_TYPE_PIN PINx)
{
    GPIO->PBDATABRR.Word = 1uL << (uint32_t)PINx;
}

/***************************************************************
  函数名：BUZC_Frequence
  描  述：BUZ使能后，配置BUZ信号频率
  输入值：Frequence : BUZ信号频率，sys_buz ：是否使能
  输出值：无
  返回值：无
 ***************************************************************/
void BUZC_Frequence(uint32_t Frequence, TYPE_FUNCEN sys_buz)
{
    float tmp;

    if (sys_buz == ENUM_DISABLE) //如果BUZC配置为禁止，则直接禁止BUZC，并返回
    {
        GPIO->BUZC.BUZEN = 0;
        return;
    }

    tmp = SystemCoreClock / (Frequence * 2) - 1;
    GPIO->BUZC.BUZ_LOAD = (uint32_t)tmp;
    GPIO->BUZC.BUZEN = 1;
}

/***************************************************************
  函数名：KINT_GetITFlag
  描  述：KINT读取中断标志
  输入值：KINT_IT_KINTx：KINT0-KINT11
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus KINT_GetITFlag(KINT_TYPE_IT KINT_Flag)
{
    FlagStatus bitstatus = RESET;

    if ((GPIO->KINTIF.Word & (uint32_t)KINT_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：KINT_GetITStatus
  描  述：KINT读取中断使能状态
  输入值：KINT_IE_PINTx：KINT0-PINT11
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus KINT_GetITStatus(KINT_TYPE_IE KINT_IE)
{
    FlagStatus bitstatus = RESET;

    if ((GPIO->KINTIE.Word & (uint32_t)KINT_IE) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：KINT_ClearITPendingBit
  描  述：KINT清除中断标志
  输入值：KINT中断类型
  输出值：无
  返回值：无
 ***************************************************************/
void KINT_ClearITPendingBit(KINT_TYPE_IT KINT_Flag)
{
    GPIO->KINTIF.Word = (uint32_t)KINT_Flag;
}

/***************************************************************
  函数名：PINT_Config
  描  述：PINT配置
  输入值：PINTx：可选PINT0 —— PINT11 、 SELx：输入选择SEL0--SEL5 、 TRIGx：触发选择
  输出值：无
  返回值：无
 ***************************************************************/
void PINT_Config(PINT_TYPE PINTx, PINT_TYPE_SEL SELx, PINT_TYPE_TRIG TRIGx)
{
	  uint32_t value;

    if (PINTx == PINT0 || PINTx <= PINT7)
    {
			  value = GPIO->PINTSEL0.Word;
			  value &= ~(7uL << ((uint32_t)PINTx * 4));
			  value |= ((uint32_t)SELx << ((uint32_t)PINTx * 4));  //sel选择
        GPIO->PINTSEL0.Word = value;

			  value = GPIO->PINTCFG0.Word;
			  value &= ~(7uL << ((uint32_t)PINTx * 4));
        value |= ((uint32_t)TRIGx << ((uint32_t)PINTx * 4)); //触发方式选择
			  GPIO->PINTCFG0.Word = value;
    }
    else
    {
        PINTx -= 8;

			  value = GPIO->PINTSEL1.Word;
        value &= ~(7uL << ((uint32_t)PINTx * 4));
        value |= ((uint32_t)SELx << ((uint32_t)PINTx * 4));  //sel选择
			  GPIO->PINTSEL1.Word = value;

			  value = GPIO->PINTCFG1.Word;
        value &= ~(7uL << ((uint32_t)PINTx * 4));
        value |= ((uint32_t)TRIGx << ((uint32_t)PINTx * 4)); //触发方式选择
			  GPIO->PINTCFG1.Word = value;
    }
}

/***************************************************************
  函数名：KINT_Config
  描  述：KINT配置
  输入值：KINTx：可选KINT0 —— KINT11 、 SELx：输入选择SEL0--SEL5 、 TRIGx：触发选择
  输出值：无
  返回值：无
 ***************************************************************/
void KINT_Config(KINT_TYPE KINTx, KINT_TYPE_SEL SELx, KINT_TYPE_TRIG TRIGx)
{
	  uint32_t value;

    if (KINTx == KINT0 || KINTx <= KINT7)
    {
			  value = GPIO->KINTSEL0.Word;
        value &= ~(7uL << ((uint32_t)KINTx * 4));
        value |= ((uint32_t)SELx << ((uint32_t)KINTx * 4));  //sel选择
			  GPIO->KINTSEL0.Word = value;

			  value = GPIO->KINTCFG0.Word;
        value &= ~(7uL << ((uint32_t)KINTx * 4));
        value |= ((uint32_t)TRIGx << ((uint32_t)KINTx * 4)); //触发方式选择
			  GPIO->KINTCFG0.Word = value;
    }
    else
    {
        KINTx -= 8;

			  value = GPIO->KINTSEL1.Word;
        value &= ~(7uL << ((uint32_t)KINTx * 4));
        value |= ((uint32_t)SELx << ((uint32_t)KINTx * 4));  //sel选择
			  GPIO->KINTSEL1.Word = value;

			  value = GPIO->KINTCFG1.Word;
        value &= ~(7uL << ((uint32_t)KINTx * 4));
        value |= ((uint32_t)TRIGx << ((uint32_t)KINTx * 4)); //触发方式选择
			  GPIO->KINTCFG1.Word = value;
    }
}

/***************************************************************
  函数名：PINT_GetITFlag
  描  述：PINT读取中断标志
  输入值：PINT_IT_PINTx：PINT0-PINT11
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus PINT_GetITFlag(PINT_TYPE_IT PINT_Flag)
{
    FlagStatus bitstatus = RESET;

    if ((GPIO->PINTIF.Word & (uint32_t)PINT_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：PINT_GetITStatus
  描  述：PINT读取中断使能状态
  输入值：PINT_IE_PINTx：PINT0-PINT11
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus PINT_GetITStatus(PINT_TYPE_IE PINT_IE)
{
    FlagStatus bitstatus = RESET;

    if ((GPIO->PINTIE.Word & (uint32_t)PINT_IE) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：PINT_ClearITPendingBit
  描  述：PINT清除中断标志
  输入值：PINT中断类型
  输出值：无
  返回值：无
 ***************************************************************/
void PINT_ClearITPendingBit(PINT_TYPE_IT PINT_Flag)
{
    GPIO->PINTIF.Word = (uint32_t)PINT_Flag;
}

/***************************************************************
函数名：UART_TXxConfig
描  述：TXx脉宽调制输出配置
输入值：Plv：调制电平选择 ，Ps：调制PWM脉冲选择 ，TxSx: 调制波形输出管脚选择
输出值：无
返回值：无
***************************************************************/
void GPIO_TX0Config(UART_TYPE_TXPLV Plv, UART_TYPE_TX0PS Ps, UART_TYPE_TX0Sx TX0Sx)
{
    GPIO->TXPWM.TX0PS = Ps;
    GPIO->TXPWM.TX0PLV = Plv;

    if (Ps == UART_TX0PS_NO)
        return;

    switch (TX0Sx)
    {
        case UART_TYPE_TXD0:
            GPIO->TXPWM.TX0_S = 0x0;
            break;

        case UART_TYPE_TX0BUZ:
            GPIO->TXPWM.TX0_S = 0x1;
            break;

        case UART_TYPE_T16N0OUT0:
            GPIO->TXPWM.TX0_S = 0x2;
            break;

        case UART_TYPE_T16N0OUT1:
            GPIO->TXPWM.TX0_S = 0x3;
            break;
    }
}

void GPIO_TX1Config(UART_TYPE_TXPLV Plv, UART_TYPE_TX1PS Ps, UART_TYPE_TX1Sx TX1Sx)
{
    GPIO->TXPWM.TX1PLV = Plv;
    GPIO->TXPWM.TX1PS = Ps;

    if (Ps == UART_TX1PS_NO)
        return;

    switch (TX1Sx)
    {
        case UART_TYPE_TXD1:
            GPIO->TXPWM.TX1_S = 0x0;
            break;

        case UART_TYPE_TX1BUZ:
            GPIO->TXPWM.TX1_S = 0x1;
            break;

        case UART_TYPE_T16N1OUT0:
            GPIO->TXPWM.TX1_S = 0x2;
            break;

        case UART_TYPE_T16N1OUT1:
            GPIO->TXPWM.TX1_S = 0x3;
            break;
    }
}

void GPIO_TX2Config(UART_TYPE_TXPLV Plv, UART_TYPE_TX2PS Ps, UART_TYPE_TX2Sx TX2Sx)
{
    GPIO->TXPWM.TX2PLV = Plv;
    GPIO->TXPWM.TX2PS = Ps;

    if (Ps == UART_TX2PS_NO)
        return;

    switch (TX2Sx)
    {
        case UART_TYPE_TXD2:
            GPIO->TXPWM.TX2_S = 0x0;
            break;

        case UART_TYPE_TX2BUZ:
            GPIO->TXPWM.TX2_S = 0x1;
            break;

        case UART_TYPE_T16N2OUT0:
            GPIO->TXPWM.TX2_S = 0x2;
            break;

        case UART_TYPE_T16N2OUT1:
            GPIO->TXPWM.TX2_S = 0x3;
            break;
    }
}

void GPIO_TX3Config(UART_TYPE_TXPLV Plv, UART_TYPE_TX3PS Ps, UART_TYPE_TX3Sx TX3Sx)
{
    GPIO->TXPWM.TX3PLV = Plv;
    GPIO->TXPWM.TX3PS = Ps;

    if (Ps == UART_TX3PS_NO)
        return;

    switch (TX3Sx)
    {
        case UART_TYPE_TXD3:
            GPIO->TXPWM.TX3_S = 0x0;
            break;

        case UART_TYPE_TX3BUZ:
            GPIO->TXPWM.TX3_S = 0x1;
            break;

        case UART_TYPE_T16N3OUT0:
            GPIO->TXPWM.TX3_S = 0x2;
            break;

        case UART_TYPE_T16N3OUT1:
            GPIO->TXPWM.TX3_S = 0x3;
            break;
    }
}

/*************************END OF FILE**********************/



