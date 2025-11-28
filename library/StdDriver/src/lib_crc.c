/***************************************************************
 *文件名： lib_crc.c
 *作  者:  AE Team
 *版  本:  V1.00
 *日  期:  2021/11/8
 *描  述： CRC库函数
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
#include "lib_crc.h"

/***************************************************************
 函数名：CRC_Init
 描  述：CRC初始化
 输入值：*CRC_CONValueStrut: CRC初始化配置结构体地址
 返回值：无
***************************************************************/
void CRC_Init(CRC_CONValueStrutType *CRC_CONValueStrut)
{
    CRC_UNLOCK();

    CRC->CON.XOROUT = CRC_CONValueStrut->xorout;
    CRC->CON.REFOUT = CRC_CONValueStrut->refout;
    CRC->CON.REFIN = CRC_CONValueStrut->refin;
    CRC->CON.BYTE = CRC_CONValueStrut->byte;
    CRC->CON.MOD = CRC_CONValueStrut->mode;

    if (CRC_CONValueStrut->flash == ENUM_ENABLE)
    {
        CRC->CON.REQ = CRC_CONValueStrut->flash;
        CRC->ADDR.IFREN = CRC_CONValueStrut->ifren;
        CRC->ADDR.ADDR = CRC_CONValueStrut->addr;
        CRC->SIZE.CRC_SIZE = CRC_CONValueStrut->size - 1;
    }

    CRC->CON.DS = CRC_CONValueStrut->init_data_type;
    CRC->CON.HS = CRC_CONValueStrut->hs_type;

    CRC_LOCK();

    CRC_ENABLE();

    CRC_RESET();
}

/***************************************************************
 函数名：CRC_WriteData
 描  述：CRC用户模式输入数据
 输入值：data: 用户模式输入的数据
 返回值：无
***************************************************************/
void CRC_WriteData(uint32_t data)
{
    CRC_UNLOCK();

    CRC->DI.DI = data;

    CRC_LOCK();
}

/***************************************************************
 函数名：CRC_Trig
 描  述：CRC触发工作模式选择
 输入值：trig: 工作模式
         0x6E91: Flash校验
         0x6D92: Flash查空
         0x6C93: 用户校验
 返回值：无
***************************************************************/
void CRC_Trig(CRC_TRIG trig)
{
    CRC_UNLOCK();

    CRC->TRIG.TRIG = trig;

    CRC_LOCK();
}

/***************************************************************
 函数名：CRC_GetData
 描  述：CRC校验结果输出
 输入值：无
 返回值：CRC校验结果
***************************************************************/
uint32_t CRC_GetData(void)
{
    uint32_t data;

    CRC_UNLOCK();

    data = CRC->DO.DO;

    CRC_LOCK();

    return data;
}

/***************************************************************
  函数名：CRC_GetCRCStatus
  描  述：获取CRC状态
  输入值：CRC状态寄存器标志位
  返回值：RESET/SET
 ***************************************************************/
FlagStatus CRC_GetCRCStatus(CRC_STA sta)
{
    FlagStatus bitstatus = RESET;

    CRC_UNLOCK();

    if ((CRC->STA.Word & (uint32_t)sta) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    CRC_LOCK();

    return  bitstatus;
}

/***************************************************************
  函数名：CRC_ClearCRCStatus
  描  述：清除CRC状态
  输入值：CRC状态寄存器标志位
  返回值：无
 ***************************************************************/
void CRC_ClearCRCStatus(CRC_STA sta)
{
    CRC_UNLOCK();

    CRC->STA.Word |= (uint32_t)sta;

    CRC_LOCK();
}

/************************END OF FILE**************************/
