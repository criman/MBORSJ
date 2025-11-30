/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Comp_test.c
Description   		: 压缩机功能单元测试（PC / gcc UNIT_TEST）
Author        		: Auto Generated
Version       		: V1.0
===================================================================================================*/

#include "main.h"
#include <stdio.h>
#include <string.h>

#if defined(UNIT_TEST)

/* 函数声明 */
void Log_Comp(void);
void Drv_Comp(void);

/* 在 PC gcc 环境下，提供最小化的全局变量，避免链接整个系统 */
STRUCT_FTYPARA          FtyPara = {0};
/* Comp 已在 Comp.c 中定义，这里不重复定义 */
STRUCT_FAN              Fan     = {0};
STRUCT_SYSTEM           System  = {0};
STRUCT_SYSTEMMODE       SystemMode = {0};
STRUCT_PROTECT          Protect = {0};
STRUCT_WATERBOX         WaterBox = {0};
STRUCT_DEFROST          Defrost = {0};
STRUCT_FOURWAY          FourWay = {0};
STRUCT_TEMPRATURE       T1 = {0}, T2 = {0}, T3 = {0}, T4 = {0}, Tp = {0};
STRUCT_TEMPR            Tempr = {0};
/* 提供缺失的全局变量存根 */
STRUCT_COMPDCFAN        DCFan = {0};
STRUCT_WPMOTOR          WPMotor = {0};
STRUCT_EEP              EEP = {0};

/* 工具函数 */
S16 TempValueMul10(S16 t)
{
    return (S16)(t * 10);
}

/* 取消 Comp.h 中的硬件宏，用函数实现以便统计调用 */
#ifdef P_Comp_On
#undef P_Comp_On
#endif
#ifdef P_Comp_Off
#undef P_Comp_Off
#endif
#ifdef P_Comp_Output
#undef P_Comp_Output
#endif
#ifdef P_Comp_Dispull
#undef P_Comp_Dispull
#endif

/* 硬件模拟 */
static int P_Comp_On_called     = 0;
static int P_Comp_Off_called    = 0;

void P_Comp_On(void)      { P_Comp_On_called++; }
void P_Comp_Off(void)     { P_Comp_Off_called++; }
void P_Comp_Output(void)  {}
void P_Comp_Dispull(void) {}

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
    memset(&Comp, 0, sizeof(Comp));
    memset(&FtyPara, 0, sizeof(FtyPara));
    memset(&Fan, 0, sizeof(Fan));
    memset(&System, 0, sizeof(System));
    memset(&SystemMode, 0, sizeof(SystemMode));
    memset(&Protect, 0, sizeof(Protect));
    memset(&WaterBox, 0, sizeof(WaterBox));
    memset(&Defrost, 0, sizeof(Defrost));
    memset(&FourWay, 0, sizeof(FourWay));
    memset(&T1, 0, sizeof(T1));
    memset(&T2, 0, sizeof(T2));
    memset(&T3, 0, sizeof(T3));
    memset(&T4, 0, sizeof(T4));
    memset(&Tp, 0, sizeof(Tp));
    memset(&Tempr, 0, sizeof(Tempr));

    P_Comp_On_called  = 0;
    P_Comp_Off_called = 0;

    /* 设置默认参数值（根据规格书） */
    FtyPara.u16P1 = 6;    /* 压缩机最小运行时间 6min */
    FtyPara.u16P2 = 15;   /* 风机运行后延时开启压缩机的时间 15s */
    FtyPara.u16P3 = 15;   /* 压缩机关闭后延时关闭风机的时间 15s */
    
    /* 初始化系统状态 */
    System.Enum_Status = ENUM_STATUS_ON;
    SystemMode.f_Cold = 1;
}

/********************************** 测试用例 **********************************/

/* 测试1：压缩机启动条件 - 外风机运行15s后允许启动 */
static void test_comp_start_after_fan_delay(void)
{
    setup_env();
    
    /* 设置外风机已运行15s（P2 * 10 = 150 ticks） */
    Fan.Outdoor.f_AppOn = ON;
    Fan.Outdoor.f_DrvOn = ON;
    Fan.Outdoor.u16_Count = FtyPara.u16P2 * 10;
    
    /* 设置压缩机应用标志为ON */
    Comp.f_AppOn = ON;
    Comp.u16_RestartDelay = 0;
    Comp.u8_SelTestDelay = 0;
    Comp.u8_PowerOnDelay = 0;
    WaterBox.f_Full = 0;
    
    /* 调用逻辑层 */
    Log_Comp();
    
    /* 验证：压缩机应该启动 */
    TEST_ASSERT(Comp.f_DrvOn == ON, "压缩机在外风机运行15s后应启动");
    TEST_ASSERT(Comp.u16_RunMinDelay == FtyPara.u16P1 * 600, "压缩机最小运行时间应设置为P1*600");
}

/* 测试2：压缩机启动条件 - 外风机运行时间不足，不应启动 */
static void test_comp_not_start_before_fan_delay(void)
{
    setup_env();
    
    /* 设置外风机运行时间不足（只有10s） */
    Fan.Outdoor.f_AppOn = ON;
    Fan.Outdoor.f_DrvOn = ON;
    Fan.Outdoor.u16_Count = 100;  /* 10s，小于P2*10=150 */
    
    Comp.f_AppOn = ON;
    Comp.u16_RestartDelay = 0;
    Comp.u8_SelTestDelay = 0;
    Comp.u8_PowerOnDelay = 0;
    WaterBox.f_Full = 0;
    
    Log_Comp();
    
    /* 验证：压缩机不应启动 */
    TEST_ASSERT(Comp.f_DrvOn == OFF, "外风机运行时间不足时压缩机不应启动");
}

/* 测试3：压缩机最小运行时间 - 运行时间未到不应关闭 */
static void test_comp_min_run_time(void)
{
    setup_env();
    
    /* 压缩机已启动并运行 */
    Comp.f_DrvOn = ON;
    Comp.f_AppOn = ON;
    Comp.u16_RunMinDelay = 100;  /* 还有100 ticks未运行完 */
    
    /* 尝试关闭压缩机 */
    Comp.f_AppOn = OFF;
    
    Log_Comp();
    
    /* 验证：压缩机应继续运行（因为最小运行时间未到） */
    TEST_ASSERT(Comp.f_DrvOn == ON, "最小运行时间未到时压缩机应继续运行");
}

/* 测试4：压缩机关闭后设置外风机延时 */
static void test_comp_stop_sets_fan_delay(void)
{
    setup_env();
    
    /* 压缩机正在运行 */
    Comp.f_DrvOn = ON;
    Comp.f_AppOn = ON;
    Comp.u16_RunMinDelay = 0;  /* 最小运行时间已到 */
    
    /* 关闭压缩机 */
    Comp.f_AppOn = OFF;
    
    Log_Comp();
    
    /* 验证：外风机延时应设置为P3*10 */
    TEST_ASSERT(Fan.Outdoor.u16_Delay == (FtyPara.u16P3 * 10), "压缩机关闭后应设置外风机延时P3*10");
}

/* 测试5：驱动层测试 - 应用标志ON时驱动ON */
static void test_comp_drive_on(void)
{
    setup_env();
    
    Comp.f_DrvOn = ON;
    P_Comp_On_called = 0;
    P_Comp_Off_called = 0;
    
    Drv_Comp();
    
    TEST_ASSERT(P_Comp_On_called == 1, "压缩机驱动标志ON时应调用P_Comp_On");
    TEST_ASSERT(P_Comp_Off_called == 0, "压缩机驱动标志ON时不应调用P_Comp_Off");
}

/* 测试6：驱动层测试 - 应用标志OFF时驱动OFF */
static void test_comp_drive_off(void)
{
    setup_env();
    
    Comp.f_DrvOn = OFF;
    P_Comp_On_called = 0;
    P_Comp_Off_called = 0;
    
    Drv_Comp();
    
    TEST_ASSERT(P_Comp_On_called == 0, "压缩机驱动标志OFF时不应调用P_Comp_On");
    TEST_ASSERT(P_Comp_Off_called == 1, "压缩机驱动标志OFF时应调用P_Comp_Off");
}

/********************************** 主测试入口 **********************************/

int main_test_Comp(void)
{
    printf("\n========== 压缩机单元测试 ==========\n\n");
    
    test_total = 0;
    test_passed = 0;
    test_failed = 0;
    
    test_comp_start_after_fan_delay();
    test_comp_not_start_before_fan_delay();
    test_comp_min_run_time();
    test_comp_stop_sets_fan_delay();
    test_comp_drive_on();
    test_comp_drive_off();
    
    printf("\n========== 测试结果 ==========\n");
    printf("总计: %d\n", test_total);
    printf("通过: %d\n", test_passed);
    printf("失败: %d\n", test_failed);
    
    return (test_failed == 0) ? 0 : 1;
}

#endif /* UNIT_TEST */

