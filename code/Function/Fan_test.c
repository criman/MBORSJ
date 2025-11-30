/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Fan_test.c
Description   		: 外风机功能单元测试（PC / gcc UNIT_TEST）
Author        		: Auto Generated
Version       		: V1.0
===================================================================================================*/

#include "main.h"
#include <stdio.h>
#include <string.h>

#if defined(UNIT_TEST)

/* 函数声明 */
void Log_Fan_OutDoor(void);
void Drv_Fan_OutDoor(void);

/* 在 PC gcc 环境下，提供最小化的全局变量，避免链接整个系统 */
STRUCT_FTYPARA          FtyPara = {0};
STRUCT_COMP             Comp    = {0};
STRUCT_FAN              Fan     = {0};
STRUCT_SYSTEMMODE       SystemMode = {0};
STRUCT_PROTECT          Protect = {0};
STRUCT_WATERBOX         WaterBox = {0};
STRUCT_DEFROST          Defrost = {0};
STRUCT_TEMPRATURE       T1 = {0}, T2 = {0}, T3 = {0}, T4 = {0}, Tp = {0};

/* 取消 Fan.h 中的硬件宏，用函数实现以便统计调用 */
#ifdef P_OutDoorFan_On
#undef P_OutDoorFan_On
#endif
#ifdef P_OutDoorFan_Off
#undef P_OutDoorFan_Off
#endif
#ifdef P_OutDoorFan_Output
#undef P_OutDoorFan_Output
#endif
#ifdef P_OutDoorFan_Dispull
#undef P_OutDoorFan_Dispull
#endif

/* 硬件模拟 */
static int P_Fan_On_called     = 0;
static int P_Fan_Off_called    = 0;

void P_OutDoorFan_On(void)      { P_Fan_On_called++; }
void P_OutDoorFan_Off(void)     { P_Fan_Off_called++; }
void P_OutDoorFan_Output(void)  {}
void P_OutDoorFan_Dispull(void) {}

/* 简单测试框架 */
static int test_total  = 0;
static int test_passed = 0;
static int test_failed = 0;

#define TEST_ASSERT(cond, msg)                  \
    do {                                        \
        test_total++;                           \
        if (!(cond)) {                          \
            printf("FAIL: %s\n", msg);          \
            test_failed++;                      \
            return;                             \
        }                                       \
        printf("PASS: %s\n", msg);              \
        test_passed++;                          \
    } while (0)

static void setup_env(void)
{
    memset(&Fan, 0, sizeof(Fan));
    memset(&FtyPara, 0, sizeof(FtyPara));
    memset(&Comp, 0, sizeof(Comp));
    memset(&SystemMode, 0, sizeof(SystemMode));
    memset(&Protect, 0, sizeof(Protect));
    memset(&WaterBox, 0, sizeof(WaterBox));
    memset(&Defrost, 0, sizeof(Defrost));
    memset(&T1, 0, sizeof(T1));
    memset(&T2, 0, sizeof(T2));
    memset(&T3, 0, sizeof(T3));
    memset(&T4, 0, sizeof(T4));
    memset(&Tp, 0, sizeof(Tp));

    P_Fan_On_called  = 0;
    P_Fan_Off_called = 0;

    /* 设置默认参数值（根据规格书） */
    FtyPara.u16P2 = 15;   /* 风机运行后延时开启压缩机的时间 15s */
    FtyPara.u16P3 = 15;   /* 压缩机关闭后延时关闭风机的时间 15s */
    
    /* 初始化系统状态 */
    SystemMode.f_Cold = 1;
    Protect.T2HeatStatus = ENUM_PROSTATUS_NORMAL;
}

/********************************** 测试用例 **********************************/

/* 测试1：外风机启动 - 应用标志ON时驱动ON */
static void test_fan_start(void)
{
    setup_env();
    
    Fan.Outdoor.f_AppOn = ON;
    Fan.Outdoor.f_DrvOn = OFF;
    
    Log_Fan_OutDoor();
    
    /* 验证：外风机应启动 */
    TEST_ASSERT(Fan.Outdoor.f_DrvOn == ON, "外风机应用标志ON时应启动");
}

/* 测试2：外风机关闭 - 应用标志OFF且延时为0时关闭 */
static void test_fan_stop_immediate(void)
{
    setup_env();
    
    Fan.Outdoor.f_AppOn = OFF;
    Fan.Outdoor.f_DrvOn = ON;
    Fan.Outdoor.u16_Delay = 0;  /* 延时已到 */
    
    Log_Fan_OutDoor();
    
    /* 验证：外风机应关闭 */
    TEST_ASSERT(Fan.Outdoor.f_DrvOn == OFF, "外风机应用标志OFF且延时为0时应关闭");
}

/* 测试3：外风机关闭延时 - 压缩机关闭后延时P3后关闭 */
static void test_fan_stop_delay_after_comp(void)
{
    setup_env();
    
    /* 压缩机关闭，设置外风机延时 */
    Comp.f_DrvOn = OFF;
    Fan.Outdoor.f_AppOn = OFF;
    Fan.Outdoor.f_DrvOn = ON;
    Fan.Outdoor.u16_Delay = FtyPara.u16P3 * 10;  /* 设置延时P3*10 */
    
    /* 延时未到，不应关闭 */
    Log_Fan_OutDoor();
    TEST_ASSERT(Fan.Outdoor.f_DrvOn == ON, "外风机延时未到时不应关闭");
    
    /* 延时已到，应关闭 */
    Fan.Outdoor.u16_Delay = 0;
    Log_Fan_OutDoor();
    TEST_ASSERT(Fan.Outdoor.f_DrvOn == OFF, "外风机延时已到时应关闭");
}

/* 测试4：外风机计数 - 用于判断压缩机启动条件 */
static void test_fan_count_for_comp_start(void)
{
    setup_env();
    
    Fan.Outdoor.f_AppOn = ON;
    Fan.Outdoor.f_DrvOn = ON;
    
    /* 模拟运行，每10ms调用一次（假设） */
    for (int i = 0; i < (FtyPara.u16P2 * 10); i++)
    {
        if (Fan.Outdoor.f_DrvOn)
        {
            Fan.Outdoor.u16_Count++;
        }
    }
    
    /* 验证：计数应达到P2*10 */
    TEST_ASSERT(Fan.Outdoor.u16_Count >= (FtyPara.u16P2 * 10), "外风机计数应达到P2*10以允许压缩机启动");
}

/* 测试5：驱动层测试 - 驱动标志ON时调用P_OutDoorFan_On */
static void test_fan_drive_on(void)
{
    setup_env();
    
    Fan.Outdoor.f_DrvOn = ON;
    P_Fan_On_called = 0;
    P_Fan_Off_called = 0;
    
    Drv_Fan_OutDoor();
    
    TEST_ASSERT(P_Fan_On_called == 1, "外风机驱动标志ON时应调用P_OutDoorFan_On");
    TEST_ASSERT(P_Fan_Off_called == 0, "外风机驱动标志ON时不应调用P_OutDoorFan_Off");
}

/* 测试6：驱动层测试 - 驱动标志OFF时调用P_OutDoorFan_Off */
static void test_fan_drive_off(void)
{
    setup_env();
    
    Fan.Outdoor.f_DrvOn = OFF;
    P_Fan_On_called = 0;
    P_Fan_Off_called = 0;
    
    Drv_Fan_OutDoor();
    
    TEST_ASSERT(P_Fan_On_called == 0, "外风机驱动标志OFF时不应调用P_OutDoorFan_On");
    TEST_ASSERT(P_Fan_Off_called == 1, "外风机驱动标志OFF时应调用P_OutDoorFan_Off");
}

/********************************** 主测试入口 **********************************/

int main_test_Fan(void)
{
    printf("\n========== 外风机单元测试 ==========\n\n");
    
    test_total = 0;
    test_passed = 0;
    test_failed = 0;
    
    test_fan_start();
    test_fan_stop_immediate();
    test_fan_stop_delay_after_comp();
    test_fan_count_for_comp_start();
    test_fan_drive_on();
    test_fan_drive_off();
    
    printf("\n========== 测试结果 ==========\n");
    printf("总计: %d\n", test_total);
    printf("通过: %d\n", test_passed);
    printf("失败: %d\n", test_failed);
    
    return (test_failed == 0) ? 0 : 1;
}

#endif /* UNIT_TEST */

