/*********************************************************

*文件名:  systick.h
*作  者:  AE Team
*版  本:  V1.00
*日  期:  2021/11/4
*描  述:  系统滴答定时器模块程序头文件
*备  注:
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
**********************************************************/
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "lib_config.h"

void SysTickInit(void);
void Delay100us(__IO uint32_t nTime);
void Delay1ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#endif
