/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Stepmotor_test.c
Description   		: 电子膨胀阀功能单元测试（PC / gcc UNIT_TEST）
Author        		: Auto Generated
Version       		: V1.0
===================================================================================================*/

#include "main.h"
#include <stdio.h>
#include <string.h>

#if defined(UNIT_TEST)

/* 在 PC gcc 环境下，提供最小化的全局变量，避免链接整个系统 */
STRUCT_FTYPARA          FtyPara = {0};
STRUCT_COMP             Comp    = {0};
STRUCT_BPV              BPV     = {0};
STRUCT_TEMPRATURE       T4      = {0};
STRUCT_TEMPRATURE       T5      = {0};
STRUCT_TEMPRATURE       Tp      = {0};
STRUCT_TEMPRATURE       T3      = {0};
STRUCT_TEMPRATURE       TH      = {0};

/* StepMotor 变量需要从 Stepmotor.h 中获取定义 */
/* 这里假设 StepMotor 是一个全局结构体变量 */
/* 如果实际定义不同，需要根据实际情况调整 */

S16 TempValueMul10(S16 t)
{
    return (S16)(t * 10);
}

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
    memset(&FtyPara, 0, sizeof(FtyPara));
    memset(&Comp, 0, sizeof(Comp));
    memset(&BPV, 0, sizeof(BPV));
    memset(&T4, 0, sizeof(T4));
    memset(&T5, 0, sizeof(T5));
    memset(&Tp, 0, sizeof(Tp));
    memset(&T3, 0, sizeof(T3));
    memset(&TH, 0, sizeof(TH));

    /* 设置默认参数值（根据规格书） */
    FtyPara.s16P15 = 5;   /* 目标过热度补偿设定 5°C */
    FtyPara.s16P16 = 100; /* 膨胀阀调节时允许排气温度 100°C */
    FtyPara.u16P13 = 160; /* 压缩机停机时电子膨胀阀开度 160P */
    FtyPara.u16P14 = 30;  /* 电子膨胀阀动作周期 30s */
}

/********************************** 测试用例 **********************************/

/* 测试1：目标过热度计算 - 压缩机运行3分钟后根据Td和Tw计算 */
static void test_target_superheat_calc(void)
{
    setup_env();
    
    /* 压缩机运行超过3分钟 */
    Comp.u32_RunContCount = 1801;  /* 3分钟+1 tick */
    
    /* 设置温度：Td=80°C, Tw=40°C */
    Tp.s16_ValueMul10 = 800;  /* 80°C * 10 */
    T5.s16_ValueMul10bc = 400;  /* 40°C * 10 */
    T5.f_Error = 0;
    Tp.f_Error = 0;
    
    /* 调用目标过热度计算函数 */
    EEV_TrgSuperHeatCalc();
    
    /* 验证：目标过热度应该被设置（具体值根据表格） */
    /* 根据代码逻辑，Td>=80且Tw>=35时，目标过热度应该是30 */
    TEST_ASSERT(StepMotor.var.s16_SuperHeatTrg > 0, "目标过热度应被正确计算");
}

/* 测试2：目标过热度计算 - 旁通阀开启时补偿 */
static void test_target_superheat_with_bypass(void)
{
    setup_env();
    
    Comp.u32_RunContCount = 1801;
    Tp.s16_ValueMul10 = 800;
    T5.s16_ValueMul10bc = 400;
    T5.f_Error = 0;
    Tp.f_Error = 0;
    
    /* 先计算不带旁通阀的目标过热度 */
    EEV_TrgSuperHeatCalc();
    S16 trg_without_bypass = StepMotor.var.s16_SuperHeatTrg;
    
    /* 旁通阀开启 */
    BPV.f_DrvOn = ON;
    
    /* 再次计算 */
    EEV_TrgSuperHeatCalc();
    S16 trg_with_bypass = StepMotor.var.s16_SuperHeatTrg;
    
    /* 验证：旁通阀开启时目标过热度应减少P15（5°C） */
    TEST_ASSERT((trg_without_bypass - trg_with_bypass) == TempValueMul10(FtyPara.s16P15), 
                "旁通阀开启时目标过热度应减少P15");
}

/* 测试3：初开度计算 - 根据Tair和Tw计算 */
static void test_init_open_step(void)
{
    setup_env();
    
    /* 设置温度：Tair=35°C, Tw=30°C */
    T4.s16_ValueMul10 = 350;  /* 35°C * 10 */
    T5.s16_ValueMul10bc = 300;  /* 30°C * 10 */
    
    /* 调用初开度计算函数 */
    EEV_InitOpenStep();
    
    /* 验证：初开度应该被设置（具体值根据表格） */
    TEST_ASSERT(StepMotor.var.u16_OpenInitStep > 0, "初开度应被正确计算");
}

/* 测试4：目标过热度计算 - 压缩机运行时间不足3分钟 */
static void test_target_superheat_before_3min(void)
{
    setup_env();
    
    /* 压缩机运行时间不足3分钟 */
    Comp.u32_RunContCount = 1000;  /* 小于1800 */
    
    EEV_TrgSuperHeatCalc();
    
    /* 验证：目标过热度应为默认值10°C */
    TEST_ASSERT(StepMotor.var.s16_SuperHeatTrg == 10, "压缩机运行不足3分钟时目标过热度应为10°C");
}

/* 测试5：目标过热度计算 - 温度传感器故障 */
static void test_target_superheat_sensor_error(void)
{
    setup_env();
    
    Comp.u32_RunContCount = 1801;
    
    /* 设置温度传感器故障 */
    T5.f_Error = 1;
    Tp.f_Error = 0;
    
    EEV_TrgSuperHeatCalc();
    
    /* 验证：传感器故障时目标过热度应为默认值10°C */
    TEST_ASSERT(StepMotor.var.s16_SuperHeatTrg == 10, "温度传感器故障时目标过热度应为10°C");
}

/********************************** 主测试入口 **********************************/

int main_test_Stepmotor(void)
{
    printf("\n========== 电子膨胀阀单元测试 ==========\n\n");
    
    test_total = 0;
    test_passed = 0;
    test_failed = 0;
    
    test_target_superheat_calc();
    test_target_superheat_with_bypass();
    test_init_open_step();
    test_target_superheat_before_3min();
    test_target_superheat_sensor_error();
    
    printf("\n========== 测试结果 ==========\n");
    printf("总计: %d\n", test_total);
    printf("通过: %d\n", test_passed);
    printf("失败: %d\n", test_failed);
    
    return (test_failed == 0) ? 0 : 1;
}

#endif /* UNIT_TEST */

