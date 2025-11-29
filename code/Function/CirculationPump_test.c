/*===================================================================================================
Project Name        : CirculationPump_test.c
Description         : 循环泵功能单元测试（PC / gcc UNIT_TEST）
Author              : Auto Generated
Version             : V1.0
===================================================================================================*/

#include "main.h"
#include <stdio.h>
#include <string.h>

#if defined(UNIT_TEST)

/* 在 PC gcc 环境下，提供最小化的全局变量，避免链接整个系统 */
STRUCT_FTYPARA          FtyPara = {0};
STRUCT_COMP             Comp    = {0};
STRUCT_FAN              Fan     = {0};
STRUCT_DEFROST          Defrost = {0};

/* CirculationPump 由 CirculationPump.c 定义 */

/* 硬件模拟 */
static int P_Circ_On_called     = 0;
static int P_Circ_Off_called    = 0;

void P_CirculationPump_On(void)      { P_Circ_On_called++; }
void P_CirculationPump_Off(void)     { P_Circ_Off_called++; }
void P_CirculationPump_Output(void)  {}
void P_CirculationPump_Dispull(void) {}

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
    memset(&CirculationPump, 0, sizeof(CirculationPump));
    memset(&FtyPara, 0, sizeof(FtyPara));
    memset(&Comp, 0, sizeof(Comp));
    memset(&Fan, 0, sizeof(Fan));
    memset(&Defrost, 0, sizeof(Defrost));

    P_Circ_On_called  = 0;
    P_Circ_Off_called = 0;

    FtyPara.u16P3 = 15;    /* 关闭顺序参数 */
    FtyPara.u16P5 = 15;
}

/********************************** 测试用例 **********************************/

/* 正常工作保持：在延时和除霜等条件满足时，循环泵应保持开启 */
static void test_Circ_normal_keep_on(void)
{
    test_total++;
    setup_env();

    CirculationPump.f_AppOn = 1;
    Comp.f_DrvOn            = 1;
    Comp.u16_RestartDelay   = 0;
    Comp.u8_SelTestDelay    = 0;
    Comp.u8_PowerOnDelay    = 0;
    Defrost.f_Enable        = 0;

    Func_CirculationPump();

    TEST_ASSERT(CirculationPump.f_AppOn == 1, "正常工作：循环泵应保持开启");
    TEST_PASS("用例1：正常工作保持开启");
}

/* 关闭顺序：压机停机后，在 P3+P5 之前保持开，时间到且外风机关后才关闭 */
static void test_Circ_stop_sequence_P3_P5(void)
{
    U32 totalDelay;

    test_total++;
    setup_env();

    FtyPara.u16P3 = 1;   /* 为便于单元测试，取较小值 */
    FtyPara.u16P5 = 1;
    totalDelay = (U32)(FtyPara.u16P3 + FtyPara.u16P5) * 10U;

    /* 压机刚停止，计时未达到 totalDelay，循环泵应保持开启 */
    CirculationPump.f_AppOn    = 1;
    Comp.f_DrvOn               = 0;
    Comp.u32_StopContCount     = totalDelay - 1;
    Fan.Outdoor.f_DrvOn        = 1;

    Func_CirculationPump();
    TEST_ASSERT(CirculationPump.f_AppOn == 1, "关闭顺序：totalDelay 前循环泵应保持开启");

    /* 到达 totalDelay 但外风机仍开，不允许关闭 */
    Comp.u32_StopContCount = totalDelay;
    Fan.Outdoor.f_DrvOn    = 1;
    Func_CirculationPump();
    TEST_ASSERT(CirculationPump.f_AppOn == 1, "关闭顺序：外风机未关时循环泵仍应保持开启");

    /* 外风机关后，允许关闭 */
    Fan.Outdoor.f_DrvOn = 0;
    Func_CirculationPump();
    TEST_ASSERT(CirculationPump.f_AppOn == 0, "关闭顺序：外风机关后循环泵应关闭");

    TEST_PASS("用例2：P3/P5 关闭顺序逻辑");
}

/* 驱动输出：根据 f_AppOn / u16_Delay 控制 f_DrvOn 并调用硬件函数 */
static void test_Circ_drive_output(void)
{
    test_total++;
    setup_env();

    /* 开启路径 */
    CirculationPump.f_AppOn = 1;
    Func_CirculationPump();
    TEST_ASSERT(CirculationPump.f_DrvOn == 1, "驱动：f_AppOn=1 时应置 f_DrvOn=1");

    Func_CirculationPump();
    TEST_ASSERT(P_Circ_On_called > 0, "驱动：f_DrvOn=1 时应调用 P_CirculationPump_On");

    /* 关闭路径（无延时） */
    CirculationPump.f_AppOn  = 0;
    CirculationPump.u16_Delay = 0;
    Func_CirculationPump();
    TEST_ASSERT(CirculationPump.f_DrvOn == 0, "驱动：f_AppOn=0 且无延时应关闭 f_DrvOn");

    TEST_PASS("用例3：驱动输出开关");
}

/********************************** 测试入口 **********************************/

int main(void)
{
    printf("========================================\n");
    printf("循环泵功能单元测试\n");
    printf("========================================\n\n");

    test_Circ_normal_keep_on();
    test_Circ_stop_sequence_P3_P5();
    test_Circ_drive_output();

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


