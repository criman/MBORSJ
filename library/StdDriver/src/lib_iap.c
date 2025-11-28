/***************************************************************
 *文件名： lib_iap.c
 *作  者:  AE Team
 *版  本:  V1.00
 *日  期:  2021/11/3
 *描  述：
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
#include "lib_iap.h"

/**
 * @brief  CODE区 IAP 页擦除编程.回调固化在ROM中的程序
 * @param  address: 页首地址
 * @retval None
 */
ErrorStatus IAP_Code_PageErase(uint32_t address, uint32_t addressInv)
{
    IAP_PE IAPPageErase = (IAP_PE)(*(uint32_t *)IAP_Code_PageErase_addr);
    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPPageErase)(address, addressInv, 0);
    __ASM("CPSIE i");
    return  result;
}

/**
 * @brief  DATA区 IAP 页擦除编程.回调固化在ROM中的程序
 * @param  address: 页首地址
 * @retval None
 */
ErrorStatus IAP_Data_PageErase(uint32_t address, uint32_t addressInv)
{
    IAP_PE IAPPageErase = (IAP_PE)(*(uint32_t *)IAP_Data_PageErase_addr);
    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPPageErase)(address, addressInv, 0);
    __ASM("CPSIE i");
    return  result;
}

/**
 * @brief  CODE区 IAP 单字自编程.回调固化在ROM中的程序
 * @param  address:
 * @retval None
 */
ErrorStatus IAP_Code_WordProgram(uint32_t address, uint32_t addressInv, uint32_t data)
{
    IAP_WP IAPWordProgram = (IAP_WP)(*(uint32_t *)IAP_Code_WordProgram_addr);
    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPWordProgram)(address, addressInv, data);
    __ASM("CPSIE i");
    return  result;
}

/**
 * @brief  DATA区 IAP 单字自编程.回调固化在ROM中的程序
 * @param  address: 页首地址
 * @retval None
 */
ErrorStatus IAP_Data_WordProgram(uint32_t address, uint32_t addressInv, uint32_t data)
{
    IAP_WP IAPWordProgram = (IAP_WP)(*(uint32_t *)IAP_Data_WordProgram_addr);
    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPWordProgram)(address, addressInv, data);
    __ASM("CPSIE i");
    return  result;
}

/**
 * @brief  CODE区 IAP 多字自编程.回调固化在ROM中的程序
 * @param  address:
 * @retval None
 */
ErrorStatus IAP_Code_PageProgram(uint32_t address, uint32_t addressInv, uint8_t data[], uint32_t length, uint32_t erase)
{
    IAP_PP IAPPageProgram = (IAP_PP)(*(uint32_t *)IAP_Code_PageProgram_addr);
    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPPageProgram)(address, addressInv, data, length, erase);
    __ASM("CPSIE i");
    return  result;
}

/**
 * @brief  DATA区 IAP 多字自编程.回调固化在ROM中的程序
 * @param  address: 页首地址
 * @retval None
 */
ErrorStatus IAP_Data_PageProgram(uint32_t address, uint32_t addressInv, uint8_t data[], uint32_t length, uint32_t erase)
{
    IAP_PP IAPPageProgram = (IAP_PP)(*(uint32_t *)IAP_Data_PageProgram_addr);
    ErrorStatus result;
    __ASM("CPSID i");
    result = (*IAPPageProgram)(address, addressInv, data, length, erase);
    __ASM("CPSIE i");
    return  result;
}

/**
 * @brief  读取特定地址上的数据
 * @param  Ram_Addr: 保存读取数据的地址
 *         Flash_Addr: FLASH上的地址(字对齐)
 *         Len: 读取的长度(以字(4字节)为单位)
 * @retval None
 */
ErrorStatus IAPRead(uint32_t *Ram_Addr, uint32_t Flash_Addr, uint8_t Len)
{
    uint8_t i;
    uint32_t *ram_addr;
    const uint32_t *flash_addr;

    if (Flash_Addr % 4 != 0)
        return ERROR;

    ram_addr = Ram_Addr;
    flash_addr = (const uint32_t *)Flash_Addr;

    for (i = 0; i < Len; ++i)
    {
        *ram_addr = *flash_addr;
        ++ram_addr;
        ++flash_addr;
    }

    return SUCCESS;
}

/**
 * @brief  解锁FLASH
 * @param  None
 * @retval None
 */
void IAP_FLASH_Unlock(void)
{
    IAP->FLASHKEY.Word = 0x8ACE0246;
    IAP->FLASHKEY.Word = 0x9BDF1357;
}

/**
 * @brief  解锁INFO
 * @param  None
 * @retval None
 */
void IAP_INFO_Unlock(void)
{
    IAP->INFOKEY.Word = 0x7153BFD9;
    IAP->INFOKEY.Word = 0x0642CEA8;
}

/**
 * @brief  锁定FLASH
 * @param  None
 * @retval None
 */
void IAP_FLASH_Lock(void)
{
    IAP->FLASHKEY.Word = 0x0;
}

/**
 * @brief  锁定FINFO
 * @param  None
 * @retval None
 */
void IAP_INFO_Lock(void)
{
    IAP->INFOKEY.Word = 0x0;
}

/************************END OF FILE**************************/

