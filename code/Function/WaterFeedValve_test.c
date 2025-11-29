/*===================================================================================================
                        Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name        : WaterFeedValve_test.c
Description         : 补水阀功能单元测试（PC / gcc UNIT_TEST）
Author              : Auto Generated
Version             : V1.0
===================================================================================================*/

#include "main.h"
#include <stdio.h>
#include <string.h>

#if defined(UNIT_TEST)

/* 在 PC gcc 环境下，提供最小化的全局变量，避免链接整个系统 */
STRUCT_FTYPARA FtyPara = {0};

/* 覆盖 Switch.h 中的宏，高低水位在单元测试中用普通变量模拟 */
#undef HighWaterLevel
#undef LowWaterLevel
U8 HighWaterLevel = 0;
U8 LowWaterLevel  = 0;

/* WFV 由 WaterFeedValve.c 中定义，这里只用声明（通过头文件） */

/* 硬件函数模拟：统计调用次数，验证驱动状态 */
static int P_WFV_On_called    = 0;
static int P_WFV_Off_called   = 0;
static int P_WFV_Output_called   = 0;
static int P_WFV_Dispull_called  = 0;

/* 取消 WaterFeedValve.h 中的硬件宏，用函数实现以便统计调用 */
#ifdef P_WFV_On
#undef P_WFV_On
#endif
#ifdef P_WFV_Off
#undef P_WFV_Off
#endif
#ifdef P_WFV_Output
#undef P_WFV_Output
#endif
#ifdef P_WFV_Dispull
#undef P_WFV_Dispull
#endif

void P_WFV_On(void)      { P_WFV_On_called++; }
void P_WFV_Off(void)     { P_WFV_Off_called++; }
void P_WFV_Output(void)  { P_WFV_Output_called++; }
void P_WFV_Dispull(void) { P_WFV_Dispull_called++; }

/* 简单测试框架 */
static int test_total  = 0;
static int test_passed = 0;
static int test_failed = 0;

#define TEST_ASSERT(cond, msg)                  \
    do {                                        \
        if (!(cond)) {                          \
            printf("FAIL: %s\n", msg);          \
            test_failed++;                      \
            return;                             \
        }                                       \
    } while (0)

#define TEST_PASS(msg)                          \
    do {                                        \
        printf("PASS: %s\n", msg);              \
        test_passed++;                          \
    } while (0)

static void setup_env(void)
{
    memset(&WFV, 0, sizeof(WFV));
    memset(&FtyPara, 0, sizeof(FtyPara));

    HighWaterLevel = 0;
    LowWaterLevel  = 0;

    P_WFV_On_called    = 0;
    P_WFV_Off_called   = 0;
    P_WFV_Output_called   = 0;
    P_WFV_Dispull_called  = 0;

    /* 默认参数 */
    FtyPara.u16P9  = 3;   /* 定时补水延时（分钟） */
    FtyPara.u16P10 = 1;   /* 自动补水启动延时（分钟） */
    FtyPara.u16P11 = 3;   /* 自动补水停止延时（分钟） */
}

/********************************** 测试用例 **********************************/

/* 手动关：f_ManualOFF=1 时，强制关闭补水阀 */
static void test_WFV_manual_off(void)
{
    test_total++;
    setup_env();

    WFV.f_ManualOFF = 1;
    WFV.f_AppOn = 1;

    Func_WFV();

    TEST_ASSERT(WFV.f_AppOn == 0, "手动关：f_ManualOFF=1 时补水阀应关闭");
    TEST_PASS("用例1：手动关补水阀");
}

/* 手动开：f_ManualON=1 且高水位断开(HighWaterLevel=1) 时开启；高水位接通后关闭并清除 f_ManualON */
static void test_WFV_manual_on_high_level_logic(void)
{
    test_total++;
    setup_env();

    /* 高水位断开，允许补水 */
    WFV.f_ManualON   = 1;
    HighWaterLevel   = 1;

    Func_WFV();
    TEST_ASSERT(WFV.f_AppOn == 1, "手动开 + 高水位断开时应开启补水阀");

    /* 高水位接通，立即关闭补水阀并复位 f_ManualON */
    HighWaterLevel = 0;
    Func_WFV();
    TEST_ASSERT(WFV.f_AppOn == 0, "高水位接通后应关闭补水阀");
    TEST_ASSERT(WFV.f_ManualON == 0, "高水位接通后应清除手动开标志");

    TEST_PASS("用例2：手动开 + 高水位逻辑");
}

/* 定时补水：高水位断开后，延时 P9 分钟(6000*P9 次 10ms)才开启；高水位接通则立即关闭并清零计时 */
static void test_WFV_timing_mode_P9_delay(void)
{
    int i;
    U32 target = 0;

    test_total++;
    setup_env();

    WFV.f_Timing = 1;
    HighWaterLevel = 1;          /* 高水位断开 */
    FtyPara.u16P9 = 1;           /* 1 分钟，方便测试 */
    target = (U32)FtyPara.u16P9 * 6000U;

    /* 延时未到之前应保持关闭 */
    for (i = 0; i < (int)target - 1; i++)
    {
        Func_WFV();
        TEST_ASSERT(WFV.f_AppOn == 0, "定时补水：延时未到前应保持关闭");
    }

    /* 再执行一次，使计数达到阈值，补水阀应开启 */
    Func_WFV();
    TEST_ASSERT(WFV.f_AppOn == 1, "定时补水：延时到达后应开启补水阀");

    /* 高水位接通时应立即关闭并清零计时 */
    HighWaterLevel = 0;
    Func_WFV();
    TEST_ASSERT(WFV.f_AppOn == 0, "定时补水：高水位接通时应立即关闭");
    TEST_ASSERT(WFV.u16_TimingCnt == 0, "定时补水：高水位接通时计数应清零");

    TEST_PASS("用例3：定时补水 P9 延时逻辑");
}

/* 自动补水：低水位断开持续 P10 分钟才开启；低水位接通后延时 P11 分钟关闭，或高水位接通时立刻关闭 */
static void test_WFV_auto_mode_P10_P11_logic(void)
{
    int i;
    U32 startCnt;
    U32 stopCnt;

    test_total++;
    setup_env();

    WFV.f_Auto = 1;
    LowWaterLevel  = 1;      /* 低水位断开 */
    HighWaterLevel = 1;      /* 高水位断开（不影响启动） */
    FtyPara.u16P10 = 1;
    FtyPara.u16P11 = 1;

    startCnt = (U32)FtyPara.u16P10 * 6000U;
    stopCnt  = (U32)FtyPara.u16P11 * 6000U;

    /* 启动延时：在 P10*6000 之前保持关闭 */
    for (i = 0; i < (int)startCnt - 1; i++)
    {
        Func_WFV();
        TEST_ASSERT(WFV.f_AppOn == 0, "自动补水：P10 延时未到前应保持关闭");
    }

    Func_WFV();  /* 到达启动阈值 */
    TEST_ASSERT(WFV.f_AppOn == 1, "自动补水：P10 延时到达后应开启补水阀");

    /* 模拟低水位再次接通，开始 P11 延时关阀（保持高水位未接通） */
    LowWaterLevel  = 0;      /* 低水位接通 */
    HighWaterLevel = 1;      /* 高水位仍断开 */

    for (i = 0; i < (int)stopCnt - 1; i++)
    {
        Func_WFV();
        TEST_ASSERT(WFV.f_AppOn == 1, "自动补水：P11 延时内应保持开启");
    }

    Func_WFV();  /* 到达停止阈值 */
    TEST_ASSERT(WFV.f_AppOn == 0, "自动补水：P11 延时到达后应关闭补水阀");

    /* 再测高水位接通立即关闭的路径 */
    setup_env();
    WFV.f_Auto = 1;
    LowWaterLevel  = 1;
    HighWaterLevel = 1;
    FtyPara.u16P10 = 0;
    FtyPara.u16P11 = 1;

    Func_WFV();      /* 立即达到启动条件并开启 */
    TEST_ASSERT(WFV.f_AppOn == 1, "自动补水：再次场景应能开启补水阀");

    LowWaterLevel  = 0;
    HighWaterLevel = 0;      /* 高水位接通 -> 立即关闭 */
    Func_WFV();
    TEST_ASSERT(WFV.f_AppOn == 0, "自动补水：高水位接通时应立即关闭补水阀");

    TEST_PASS("用例4：自动补水 P10/P11 及高水位立即关闭逻辑");
}

/* 驱动输出：根据 f_DrvOn / f_ForceDrvOn 调用硬件输出函数 */
static void test_WFV_drive_output_calls(void)
{
    test_total++;
    setup_env();

    /* 初始为关，f_AppOn=1 -> f_DrvOn 置 1 -> 调用 P_WFV_On */
    WFV.f_AppOn = 1;
    Func_WFV();
    TEST_ASSERT(WFV.f_DrvOn == 1, "驱动：f_AppOn=1 时应置 f_DrvOn=1");

    Func_WFV();
    TEST_ASSERT(P_WFV_On_called > 0, "驱动：f_DrvOn=1 时应调用 P_WFV_On");

    /* 关闭路径 */
    WFV.f_AppOn  = 0;
    WFV.u16_Delay = 0;
    Func_WFV();
    TEST_ASSERT(WFV.f_DrvOn == 0, "驱动：f_AppOn=0 且无延时应关闭 f_DrvOn");

    TEST_PASS("用例5：驱动输出函数调用");
}

/********************************** 测试入口 **********************************/

int main(void)
{
    printf("========================================\n");
    printf("补水阀功能单元测试\n");
    printf("========================================\n\n");

    test_WFV_manual_off();
    test_WFV_manual_on_high_level_logic();
    test_WFV_timing_mode_P9_delay();
    test_WFV_auto_mode_P10_P11_logic();
    test_WFV_drive_output_calls();

    printf("\n========================================\n");
    printf("测试结果统计\n");
    printf("========================================\n");
    printf("总测试用例数: %d\n", test_total);
    printf("通过: %d\n", test_passed);
    printf("失败: %d\n", test_failed);
    printf("通过率: %.1f%%\n", test_total > 0 ? (100.0 * test_passed / test_total) : 0.0);
    printf("========================================\n");

    return (test_failed == 0) ? 0 : 1;
}

#endif /* UNIT_TEST */


