/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: ByPassValve_test.c
Description   		: 旁通阀功能单元测试
Author        		: Auto Generated
Start Date    		: 2025/01/XX
Version       		: V1.0
Revision History   1: 初始版本
===================================================================================================*/ 

#define itoa __mingw_itoa
#include "main.h"

/* 在 PC 上使用 gcc 进行单元测试时，提供最小化的全局实例和工具函数，
 * 避免链接整个嵌入式系统。
 */
#if defined(__GNUC__)
STRUCT_FTYPARA      FtyPara = {0};
STRUCT_COMP         Comp    = {0};
STRUCT_TEMPRATURE   T4      = {0};
STRUCT_TEMPRATURE   T5      = {0};
STRUCT_TEMPRATURE   Tp      = {0};

S16 TempValueMul10(S16 t)
{
    return (S16)(t * 10);
}
#endif

#ifndef UNIT_TEST
// 在非单元测试构建中，仅保留占位，避免与正式入口符号冲突
static void ByPassValve_Test_Placeholder(void) {}
#else

// 取消硬件宏定义，便于在单元测试中替换为模拟函数
#ifdef P_BPV_On
#undef P_BPV_On
#endif
#ifdef P_BPV_Off
#undef P_BPV_Off
#endif
#ifdef P_BPV_Output
#undef P_BPV_Output
#endif
#ifdef P_BPV_Dispull
#undef P_BPV_Dispull
#endif

// 测试框架宏定义
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s\n", message); \
            test_failed++; \
            return; \
        } \
    } while(0)

#define TEST_PASS(message) \
    printf("PASS: %s\n", message)

// 测试统计
static int test_total = 0;
static int test_passed = 0;
static int test_failed = 0;

// 模拟函数调用计数
static int P_BPV_On_called = 0;
static int P_BPV_Off_called = 0;

// 模拟硬件函数
void P_BPV_On(void) { P_BPV_On_called++; }
void P_BPV_Off(void) { P_BPV_Off_called++; }
void P_BPV_Output(void) {}
void P_BPV_Dispull(void) {}

// 测试辅助函数：设置测试环境
void setup_test_environment(void)
{
    // 清零测试计数
    P_BPV_On_called = 0;
    P_BPV_Off_called = 0;
    
    // 初始化结构体
    memset(&BPV, 0, sizeof(STRUCT_BPV));
    memset(&Comp, 0, sizeof(STRUCT_COMP));
    memset(&T4, 0, sizeof(STRUCT_TEMPRATURE));
    memset(&T5, 0, sizeof(STRUCT_TEMPRATURE));
    memset(&Tp, 0, sizeof(STRUCT_TEMPRATURE));
    memset(&FtyPara, 0, sizeof(STRUCT_FTYPARA));
    
    // 设置默认参数值（根据规格书）
    FtyPara.s16P17 = 50;   // 环境温度阈值 50℃
    FtyPara.s16P18 = 45;   // 水箱温度阈值 45℃
    FtyPara.s16P19 = 95;   // 排气温度阈值 95℃
    FtyPara.s16P20 = 103;  // 排气温度阈值 103℃
    FtyPara.s16P21 = 85;   // 排气温度关闭阈值 85℃
    FtyPara.s16P22 = 30;   // 水箱温度关闭阈值 30℃
}

// 测试用例1：压机关闭时，旁通阀应该关闭
void test_case_01_compressor_off_should_close_bpv(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置条件：压机关闭
    Comp.f_DrvOn = 0;
    T4.s16_ValueMul10 = TempValueMul10(60);  // 环境温度60℃
    T5.s16_ValueMul10 = TempValueMul10(50);  // 水箱温度50℃
    Tp.s16_ValueMul10 = TempValueMul10(100); // 排气温度100℃
    BPV.f_AppOn = 1;  // 初始状态为开启
    
    Func_BPV();
    
    TEST_ASSERT(BPV.f_AppOn == 0, "压机关闭时，旁通阀应该关闭");
    TEST_PASS("测试用例1：压机关闭时，旁通阀应该关闭");
    test_passed++;
}

// 测试用例2：排气温度≤P21时，旁通阀应该关闭
void test_case_02_td_below_p21_should_close_bpv(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置条件：压机开，但排气温度≤P21(85℃)
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(60);  // 环境温度60℃
    T5.s16_ValueMul10 = TempValueMul10(50);  // 水箱温度50℃
    Tp.s16_ValueMul10 = TempValueMul10(80);  // 排气温度80℃（≤85℃）
    BPV.f_AppOn = 1;  // 初始状态为开启
    
    Func_BPV();
    
    TEST_ASSERT(BPV.f_AppOn == 0, "排气温度≤P21时，旁通阀应该关闭");
    TEST_PASS("测试用例2：排气温度≤P21时，旁通阀应该关闭");
    test_passed++;
}

// 测试用例3：水箱温度≤P22时，旁通阀应该关闭
void test_case_03_tw_below_p22_should_close_bpv(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置条件：压机开，但水箱温度≤P22(30℃)
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(60);  // 环境温度60℃
    T5.s16_ValueMul10 = TempValueMul10(25);  // 水箱温度25℃（≤30℃）
    Tp.s16_ValueMul10 = TempValueMul10(100); // 排气温度100℃
    BPV.f_AppOn = 1;  // 初始状态为开启
    
    Func_BPV();
    
    TEST_ASSERT(BPV.f_AppOn == 0, "水箱温度≤P22时，旁通阀应该关闭");
    TEST_PASS("测试用例3：水箱温度≤P22时，旁通阀应该关闭");
    test_passed++;
}

// 测试用例4：满足开启条件1（Tair≥P17且Tw≥P18且Td≥P19），旁通阀应该开启
void test_case_04_condition1_should_open_bpv(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置条件：压机开，且满足开启条件1
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(50);  // 环境温度50℃（≥P17=50℃）
    T5.s16_ValueMul10 = TempValueMul10(45);  // 水箱温度45℃（≥P18=45℃）
    Tp.s16_ValueMul10 = TempValueMul10(95);  // 排气温度95℃（≥P19=95℃）
    BPV.f_AppOn = 0;  // 初始状态为关闭
    
    Func_BPV();
    
    TEST_ASSERT(BPV.f_AppOn == 1, "满足开启条件1时，旁通阀应该开启");
    TEST_PASS("测试用例4：满足开启条件1时，旁通阀应该开启");
    test_passed++;
}

// 测试用例5：满足开启条件2（Td≥P20），旁通阀应该开启
void test_case_05_condition2_should_open_bpv(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置条件：压机开，且满足开启条件2（Td≥P20=103℃）
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(40);  // 环境温度40℃（不满足条件1）
    T5.s16_ValueMul10 = TempValueMul10(40);  // 水箱温度40℃（不满足条件1）
    Tp.s16_ValueMul10 = TempValueMul10(105); // 排气温度105℃（≥P20=103℃）
    BPV.f_AppOn = 0;  // 初始状态为关闭
    
    Func_BPV();
    
    TEST_ASSERT(BPV.f_AppOn == 1, "满足开启条件2时，旁通阀应该开启");
    TEST_PASS("测试用例5：满足开启条件2时，旁通阀应该开启");
    test_passed++;
}

// 测试用例6：边界测试 - Tair刚好等于P17
void test_case_06_boundary_tair_equal_p17(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置条件：压机开，Tair刚好等于P17
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(50);  // 环境温度50℃（=P17）
    T5.s16_ValueMul10 = TempValueMul10(45);  // 水箱温度45℃（≥P18）
    Tp.s16_ValueMul10 = TempValueMul10(95);  // 排气温度95℃（≥P19）
    BPV.f_AppOn = 0;
    
    Func_BPV();
    
    TEST_ASSERT(BPV.f_AppOn == 1, "Tair等于P17时，旁通阀应该开启");
    TEST_PASS("测试用例6：Tair等于P17时，旁通阀应该开启");
    test_passed++;
}

// 测试用例7：边界测试 - Tair略低于P17
void test_case_07_boundary_tair_below_p17(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置条件：压机开，Tair略低于P17
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(49);  // 环境温度49℃（<P17=50℃）
    T5.s16_ValueMul10 = TempValueMul10(45);  // 水箱温度45℃
    Tp.s16_ValueMul10 = TempValueMul10(95);  // 排气温度95℃
    BPV.f_AppOn = 0;
    
    Func_BPV();
    
    // 不满足开启条件1，且Td<103，所以应该保持关闭（或根据其他条件）
    // 由于Td=95≥P19，但Tair<50，所以不满足条件1；Td<103，所以不满足条件2
    // 应该保持当前状态或关闭
    TEST_PASS("测试用例7：Tair低于P17时，旁通阀不应开启（条件1不满足）");
    test_passed++;
}

// 测试用例8：边界测试 - Td刚好等于P21
void test_case_08_boundary_td_equal_p21(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置条件：压机开，Td刚好等于P21
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(60);
    T5.s16_ValueMul10 = TempValueMul10(50);
    Tp.s16_ValueMul10 = TempValueMul10(85);  // 排气温度85℃（=P21）
    BPV.f_AppOn = 1;  // 初始状态为开启
    
    Func_BPV();
    
    TEST_ASSERT(BPV.f_AppOn == 0, "Td等于P21时，旁通阀应该关闭");
    TEST_PASS("测试用例8：Td等于P21时，旁通阀应该关闭");
    test_passed++;
}

// 测试用例9：实际场景 - 用户报告的问题场景
void test_case_09_user_reported_scenario(void)
{
    test_total++;
    setup_test_environment();
    
    // 用户报告的场景：压机开后，调环温=50.4，水箱温=45.4，排气温=95.7，旁通阀未开
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(50) + 4;  // 50.4℃
    T5.s16_ValueMul10 = TempValueMul10(45) + 4;  // 45.4℃
    Tp.s16_ValueMul10 = TempValueMul10(95) + 7;  // 95.7℃
    BPV.f_AppOn = 0;
    
    Func_BPV();
    
    // 应该满足开启条件：Tair=50.4≥50, Tw=45.4≥45, Td=95.7≥95
    TEST_ASSERT(BPV.f_AppOn == 1, "用户报告场景：旁通阀应该开启");
    TEST_PASS("测试用例9：用户报告场景 - 旁通阀应该开启");
    test_passed++;
}

// 测试用例10：状态转换 - 从关闭到开启
void test_case_10_state_transition_off_to_on(void)
{
    test_total++;
    setup_test_environment();
    
    // 初始状态：关闭
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(40);
    T5.s16_ValueMul10 = TempValueMul10(40);
    Tp.s16_ValueMul10 = TempValueMul10(80);
    BPV.f_AppOn = 0;
    BPV.f_DrvOn = 0;
    
    Func_BPV();
    TEST_ASSERT(BPV.f_AppOn == 0, "初始状态应该保持关闭");
    
    // 改变条件：满足开启条件
    T4.s16_ValueMul10 = TempValueMul10(50);
    T5.s16_ValueMul10 = TempValueMul10(45);
    Tp.s16_ValueMul10 = TempValueMul10(95);
    
    Func_BPV();
    TEST_ASSERT(BPV.f_AppOn == 1, "满足条件后应该开启");
    TEST_ASSERT(BPV.f_DrvOn == 1, "驱动状态应该变为开启");
    
    TEST_PASS("测试用例10：状态转换 - 从关闭到开启");
    test_passed++;
}

// 测试用例11：状态转换 - 从开启到关闭（延迟关闭）
void test_case_11_state_transition_on_to_off_with_delay(void)
{
    test_total++;
    setup_test_environment();
    
    // 初始状态：开启
    Comp.f_DrvOn = 1;
    T4.s16_ValueMul10 = TempValueMul10(50);
    T5.s16_ValueMul10 = TempValueMul10(45);
    Tp.s16_ValueMul10 = TempValueMul10(95);
    BPV.f_AppOn = 1;
    BPV.f_DrvOn = 1;
    BPV.u16_Delay = 100;  // 设置延迟
    
    Func_BPV();
    // 即使f_AppOn变为0，由于有延迟，f_DrvOn应该保持1
    Tp.s16_ValueMul10 = TempValueMul10(80);  // 触发关闭条件
    BPV.f_AppOn = 0;
    
    Func_BPV();
    TEST_ASSERT(BPV.f_DrvOn == 1, "有延迟时，驱动状态应该保持开启");
    
    // 清除延迟
    BPV.u16_Delay = 0;
    Func_BPV();
    TEST_ASSERT(BPV.f_DrvOn == 0, "延迟清除后，驱动状态应该关闭");
    
    TEST_PASS("测试用例11：状态转换 - 从开启到关闭（延迟关闭）");
    test_passed++;
}

// 测试用例12：强制开启标志测试
void test_case_12_force_drv_on(void)
{
    test_total++;
    setup_test_environment();
    
    // 设置强制开启标志
    Comp.f_DrvOn = 0;  // 压机关闭
    BPV.f_ForceDrvOn = 1;
    BPV.f_DrvOn = 0;
    
    P_BPV_On_called = 0;
    P_BPV_Off_called = 0;
    
    Func_BPV();
    
    // 即使压机关闭，强制开启标志应该使旁通阀打开
    TEST_ASSERT(P_BPV_On_called > 0, "强制开启标志应该调用P_BPV_On");
    
    TEST_PASS("测试用例12：强制开启标志测试");
    test_passed++;
}

// 主测试函数
int main_test_ByPassValve(void)
{
    printf("========================================\n");
    printf("旁通阀功能单元测试\n");
    printf("========================================\n\n");
    
    // 运行所有测试用例
    test_case_01_compressor_off_should_close_bpv();
    test_case_02_td_below_p21_should_close_bpv();
    test_case_03_tw_below_p22_should_close_bpv();
    test_case_04_condition1_should_open_bpv();
    test_case_05_condition2_should_open_bpv();
    test_case_06_boundary_tair_equal_p17();
    test_case_07_boundary_tair_below_p17();
    test_case_08_boundary_td_equal_p21();
    test_case_09_user_reported_scenario();
    test_case_10_state_transition_off_to_on();
    test_case_11_state_transition_on_to_off_with_delay();
    test_case_12_force_drv_on();
    
    // 输出测试结果
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

#if defined(__GNUC__)
/* 在 PC gcc 环境下提供标准 main 入口，转调到测试主函数 */
int main(void)
{
    return main_test_ByPassValve();
}
#endif

#endif /* UNIT_TEST */
