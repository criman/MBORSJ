/***************************************************************
 *文件名： lib_iap.h
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
#ifndef __LIB_IAP_H
#define __LIB_IAP_H

#include "ES8H018x.h"
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IAP_Code_PageProgram_addr   0x10000000
#define IAP_Code_PageErase_addr     0x10000004
#define IAP_Code_WordProgram_addr   0x10000008
#define IAP_Data_PageProgram_addr   0x10000010
#define IAP_Data_PageErase_addr     0x10000014
#define IAP_Data_WordProgram_addr   0x10000018

/* 回调函数定义 */
typedef ErrorStatus(*IAP_PE)(uint32_t address, uint32_t addressInv, uint32_t sector);
typedef ErrorStatus(*IAP_WP)(uint32_t address, uint32_t addressInv, uint32_t data);
typedef ErrorStatus(*IAP_PP)(uint32_t address, uint32_t addressInv, uint8_t data[], uint32_t length, uint32_t erase);

/* 函数声明 */
ErrorStatus IAP_Code_PageErase(uint32_t address, uint32_t addressInv);
ErrorStatus IAP_Code_WordProgram(uint32_t address, uint32_t addressInv, uint32_t data);
ErrorStatus IAP_Code_PageProgram(uint32_t address, uint32_t addressInv, uint8_t data[], uint32_t length, uint32_t erase);
ErrorStatus IAP_Data_PageErase(uint32_t address, uint32_t addressInv);
ErrorStatus IAP_Data_WordProgram(uint32_t address, uint32_t addressInv, uint32_t data);
ErrorStatus IAP_Data_PageProgram(uint32_t address, uint32_t addressInv, uint8_t data[], uint32_t length, uint32_t erase);
ErrorStatus IAPRead(uint32_t *Ram_Addr, uint32_t Flash_Addr, uint8_t Len);
void IAP_FLASH_Unlock(void);
void IAP_FLASH_Lock(void);

#define PageEraseEnable             0x00000001
#define PageEraseDisable            0x00000000

#ifdef __cplusplus
}
#endif

#endif
/*************************END OF FILE**********************/
