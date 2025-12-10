# Keil C51 单元测试完整指南

本文档总结了在Keil C51嵌入式项目中创建可在PC上运行的单元测试的完整过程和解决方案。

## 目录

1. [概述](#概述)
2. [环境准备](#环境准备)
3. [项目结构](#项目结构)
4. [兼容层实现](#兼容层实现)
5. [测试框架搭建](#测试框架搭建)
6. [常见问题与解决方案](#常见问题与解决方案)
7. [快速开始模板](#快速开始模板)
8. [示例代码](#示例代码)

---

## 概述

### 目标
在Windows环境下使用GCC编译器，为Keil C51项目创建可在PC上运行的单元测试，实现90%+代码覆盖率。

### 核心挑战
1. **编译器差异**: Keil C51 vs GCC
2. **硬件依赖**: 嵌入式代码依赖硬件寄存器
3. **数据类型**: C51特有的存储类型（xdata, idata, bit等）
4. **标准库差异**: absacc.h, intrins.h等C51特有头文件

### 解决方案
- 创建兼容层（Compatibility Layer）
- 使用Mock函数替代硬件依赖
- 自定义轻量级测试框架
- PowerShell构建脚本（无需make工具）

---

## 环境准备

### 必需工具
1. **MinGW-w64 GCC** (推荐版本 14.2.0+)
   - 下载: https://www.mingw-w64.org/
   - 或使用winget: `winget install mingw-w64`
   
2. **PowerShell** (Windows 10+自带)

3. **文本编辑器/IDE** (VS Code推荐)

### 验证安装
```powershell
gcc --version
```

---

## 项目结构

```
项目根目录/
├── User/                          # 源代码目录
│   ├── main.c
│   ├── Project.c
│   ├── MyPort.c
│   ├── MyPort.h
│   ├── App/                       # 应用层代码
│   ├── Driver/                    # 驱动层代码
│   └── Test/                      # 测试目录
│       ├── unittest.h             # 测试框架头文件
│       ├── unittest.c             # 测试框架实现
│       ├── test_compat.h          # 兼容层头文件
│       ├── test_compat.c          # 兼容层实现
│       ├── MyPort_test_wrapper.h  # 类型定义包装器
│       ├── MyPort_test.c          # 测试源文件（测试版MyPort.c）
│       ├── test_MyPort.c          # MyPort模块测试
│       ├── test_main.c            # main.c模块测试
│       ├── test_Project.c         # Project.c模块测试
│       ├── test_runner.c          # 测试运行器
│       ├── build.ps1              # PowerShell构建脚本
│       └── TestConfig.h           # 测试配置（可选）
└── H/                             # 头文件目录
```

---

## 兼容层实现

### 1. test_compat.h - 兼容层头文件

```c
#ifndef __TEST_COMPAT_H__
#define __TEST_COMPAT_H__

/*
 * 测试环境兼容层
 * 用于在PC环境（GCC）中编译和测试嵌入式C51代码
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// 定义TEST_ENV
#ifndef TEST_ENV
#define TEST_ENV 1
#endif

// ========== Keil C51 存储类型兼容 ==========
// 在测试环境中，xdata和idata都是普通变量
#define xdata
#define idata
#define code
#define bdata
#define sbit

// ========== Keil C51 位类型兼容 ==========
// 在测试环境中，bit类型用uint8_t模拟
typedef uint8_t bit;

// ========== absacc.h 兼容 ==========
// 绝对地址访问宏（测试环境中不需要）
#define CBYTE(addr) (*(uint8_t volatile *)(addr))
#define DBYTE(addr) (*(uint8_t volatile *)(addr))
#define PBYTE(addr) (*(uint8_t volatile *)(addr))
#define XBYTE(addr) (*(uint8_t volatile *)(addr))
#define CWORD(addr) (*(uint16_t volatile *)(addr))
#define DWORD(addr) (*(uint16_t volatile *)(addr))
#define PWORD(addr) (*(uint16_t volatile *)(addr))
#define XWORD(addr) (*(uint16_t volatile *)(addr))

// ========== intrins.h 兼容 ==========
static inline void _nop_(void) {
    volatile int dummy = 0;
    (void)dummy;
}

static inline uint8_t _crol_(uint8_t value, uint8_t count) {
    count &= 7;
    return (value << count) | (value >> (8 - count));
}

static inline uint8_t _cror_(uint8_t value, uint8_t count) {
    count &= 7;
    return (value >> count) | (value << (8 - count));
}

// ========== 硬件寄存器模拟 ==========
extern uint8_t mock_WDTCON;
#define WDTCON mock_WDTCON

// 添加其他硬件寄存器（根据需要）
// extern uint8_t mock_P0CON;
// #define P0CON mock_P0CON

// ========== 硬件相关函数的Mock声明 ==========
// 使用宏将硬件函数调用重定向到Mock函数
#define IO_Init() mock_IO_Init()
#define Key_GpioInit() mock_Key_GpioInit()
#define Timer_Init() mock_Timer_Init()
// ... 添加其他需要Mock的函数

// Mock函数声明
void mock_IO_Init(void);
void mock_Key_GpioInit(void);
void mock_Timer_Init(void);
// ... 添加其他Mock函数声明

#endif // __TEST_COMPAT_H__
```

### 2. test_compat.c - 兼容层实现

```c
#include "test_compat.h"

// ========== Mock硬件寄存器 ==========
uint8_t mock_WDTCON = 0;
// 添加其他Mock寄存器
// uint8_t mock_P0CON = 0;

// ========== 全局变量定义 ==========
// Project.c等文件中使用的全局变量
bit GbTimer_250us = 0;
bit GbTimer_100ms = 0;
uint8_t GbTimer_1ms = 0;
uint8_t Gu8Timer_2ms = 0;
uint8_t Gu8Timer_10ms = 0;
uint8_t Gu8Timer_50ms = 0;
uint8_t Gu8Timer_100ms = 0;

// ========== Mock函数实现 ==========
void mock_IO_Init(void) {
    // Mock实现（可以添加调用计数等）
}

void mock_Key_GpioInit(void) {
    // Mock实现
}

void mock_Timer_Init(void) {
    // Mock实现
}
```

### 3. 类型定义冲突处理

**问题**: MyPort.h中定义的int32_t等类型与stdint.h冲突

**解决方案**: 创建包装器头文件

```c
// MyPort_test_wrapper.h
#ifndef __MYPORT_TEST_WRAPPER_H__
#define __MYPORT_TEST_WRAPPER_H__

// 定义标志，让MyPort.h知道这是测试环境，跳过类型定义
#define __TEST_ENV_STDINT__ 1

// 先包含系统的stdint.h（定义标准类型）
#include <stdint.h>

// 定义标志，防止MyPort.h重新定义类型
#define __TYPEDEF_ALREADY_DEFINED__

// 现在包含MyPort.h（它会看到__TYPEDEF_ALREADY_DEFINED__，跳过类型定义）
#include "../MyPort.h"

#endif // __MYPORT_TEST_WRAPPER_H__
```

**修改MyPort.h**:
```c
// MyPort.h
#if 1  // defined TYPEDEF_DATATYPE
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

/*!< Signed integer types  */
// 在测试环境中，如果类型已定义（通过stdint.h），则不重新定义
#ifdef __TYPEDEF_ALREADY_DEFINED__
// 测试环境：类型已在stdint.h中定义，跳过
#else
// 真实环境：定义C51类型
typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;
/*!< Unsigned integer types  */
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;
#endif
#endif
```

---

## 测试框架搭建

### 1. unittest.h - 轻量级测试框架

```c
#ifndef __UNITTEST_H__
#define __UNITTEST_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>

// 测试统计
extern uint32_t g_test_total;
extern uint32_t g_test_passed;
extern uint32_t g_test_failed;

// Setup和Teardown函数（使用弱符号避免多重定义）
void setup(void) __attribute__((weak));
void teardown(void) __attribute__((weak));

// 测试宏
#define TEST(test_name) \
    static void test_##test_name(void)

#define RUN_TEST(test_name) \
    do { \
        printf("Running test: %s\n", #test_name); \
        setup(); \
        test_##test_name(); \
        teardown(); \
        g_test_total++; \
    } while(0)

// 断言宏
#define TEST_ASSERT(condition) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s:%d: Assertion failed: %s\n", \
                   __FILE__, __LINE__, #condition); \
            g_test_failed++; \
            return; \
        } \
    } while(0)

#define TEST_ASSERT_EQUAL(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("FAIL: %s:%d: Expected %d, got %d\n", \
                   __FILE__, __LINE__, (expected), (actual)); \
            g_test_failed++; \
            return; \
        } \
    } while(0)

#define TEST_ASSERT_ARRAY_EQUAL(expected, actual, length) \
    do { \
        if (memcmp((expected), (actual), (length)) != 0) { \
            printf("FAIL: %s:%d: Array comparison failed\n", \
                   __FILE__, __LINE__); \
            g_test_failed++; \
            return; \
        } \
    } while(0)

// 空实现（默认）
void setup(void) {}
void teardown(void) {}

#endif // __UNITTEST_H__
```

### 2. unittest.c - 测试框架实现

```c
#include "unittest.h"

uint32_t g_test_total = 0;
uint32_t g_test_passed = 0;
uint32_t g_test_failed = 0;

// 默认实现（可以被测试文件中的定义覆盖）
__attribute__((weak)) void setup(void) {}
__attribute__((weak)) void teardown(void) {}
```

### 3. 测试文件示例

```c
// test_MyPort.c
#include "unittest.h"
#include "MyPort_test_wrapper.h"

// Setup和Teardown（使用弱符号）
__attribute__((weak)) void setup(void)
{
    // 初始化测试环境
}

__attribute__((weak)) void teardown(void)
{
    // 清理测试环境
}

// 测试用例
TEST(MyMemorySet_Normal)
{
    uint8_t buf[10] = {0};
    MyMemorySet(buf, 0xAA, 10);
    
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL(0xAA, buf[i]);
    }
}

TEST(MyMemorySet_ZeroLength)
{
    uint8_t buf[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    uint8_t original[5];
    memcpy(original, buf, 5);
    
    MyMemorySet(buf, 0xAA, 0);
    TEST_ASSERT_ARRAY_EQUAL(original, buf, 5);
}

// 测试运行函数
void run_MyPort_tests(void)
{
    printf("========================================\n");
    printf("Running MyPort Module Tests\n");
    printf("========================================\n\n");
    
    RUN_TEST(MyMemorySet_Normal);
    RUN_TEST(MyMemorySet_ZeroLength);
    // ... 添加更多测试
}
```

### 4. test_runner.c - 测试运行器

```c
#include "unittest.h"

// 声明各模块的测试运行函数
extern void run_MyPort_tests(void);
extern void run_main_tests(void);
extern void run_Project_tests(void);

int main(void)
{
    printf("========================================\n");
    printf("Unit Test Framework Initialized\n");
    printf("========================================\n\n");
    
    // 运行所有测试
    run_MyPort_tests();
    run_main_tests();
    run_Project_tests();
    
    // 打印测试结果
    printf("\n========================================\n");
    printf("Test Summary\n");
    printf("========================================\n");
    printf("Total Tests:  %lu\n", g_test_total);
    printf("Passed:       %lu\n", g_test_passed);
    printf("Failed:       %lu\n", g_test_failed);
    printf("Total Errors: %lu\n", g_test_failed);
    printf("========================================\n");
    
    if (g_test_failed == 0) {
        printf("ALL TESTS PASSED!\n");
        printf("========================================\n");
        return 0;
    } else {
        printf("SOME TESTS FAILED!\n");
        printf("========================================\n");
        return 1;
    }
}
```

---

## 构建脚本

### build.ps1 - PowerShell构建脚本

```powershell
# PowerShell构建脚本 - 用于编译和运行单元测试
# 无需安装make，直接在PowerShell中运行: .\build.ps1

param(
    [Parameter(Position=0)]
    [ValidateSet("clean", "run", "test", "all", "help")]
    [string]$Action = "all"
)

$ErrorActionPreference = "Stop"

# 编译器配置
$CC = "gcc"
$CFLAGS = "-Wall", "-Wextra", "-std=c99", "-g", "-O0", "-DTEST_ENV=1"
$INCLUDES = "-I.", "-I..", "-I../H", "-I../App", "-I../Driver", "-I../Periph"
$LDFLAGS = "-mconsole"  # Windows控制台应用链接选项

# 测试兼容层源文件
$TestCompatFiles = @(
    "test_compat.c"
)

# 测试源文件列表
$TestSources = @(
    "unittest.c",
    "test_MyPort.c",
    "test_main.c",
    "test_Project.c",
    "test_runner.c"
)

# 被测试的源文件（需要TEST_ENV定义）
# 注意：如果源文件有硬件依赖，需要创建测试版本（如MyPort_test.c）
$SourceFiles = @(
    "MyPort_test.c"  # 测试版本的MyPort.c
)

$Target = "test_runner.exe"

# 清理构建文件
function Clean-Build {
    Write-Host "清理构建文件..." -ForegroundColor Yellow
    Remove-Item -Path "*.o", "*.exe", "test_report.txt" -ErrorAction SilentlyContinue
    Write-Host "? 清理完成!" -ForegroundColor Green
    Write-Host ""
}

# 检查GCC
function Test-GCC {
    try {
        $null = & $CC --version 2>&1
        return $true
    } catch {
        return $false
    }
}

# 编译单个文件
function Compile-File {
    param(
        [string]$source,
        [string]$obj,
        [bool]$isTestEnv = $false
    )
    
    $flags = $CFLAGS
    if ($isTestEnv) {
        # 测试环境源文件需要TEST_ENV定义
    }
    
    Write-Host "  编译: $source" -ForegroundColor Cyan
    & $CC $flags $INCLUDES -c $source -o $obj
    if ($LASTEXITCODE -ne 0) {
        throw "编译失败: $source"
    }
}

# 构建项目
function Build-Project {
    if (-not (Test-GCC)) {
        throw "未找到GCC编译器，请先安装MinGW-w64"
    }
    
    Write-Host "开始构建..." -ForegroundColor Yellow
    Write-Host "编译器: $CC $(& $CC --version | Select-Object -First 1)" -ForegroundColor Cyan
    Write-Host ""
    
    # 使用 ArrayList 来构建对象列表，避免数组 += 的性能问题
    $objectList = New-Object System.Collections.ArrayList
    
    # 编译测试兼容层
    foreach ($file in $TestCompatFiles) {
        $obj = $file -replace '\.c$', '.o'
        Compile-File -source $file -obj $obj
        [void]$objectList.Add($obj)
    }
    
    # 编译测试源文件
    foreach ($file in $TestSources) {
        $obj = $file -replace '\.c$', '.o'
        Compile-File -source $file -obj $obj
        [void]$objectList.Add($obj)
    }
    
    # 编译被测试的源文件
    foreach ($file in $SourceFiles) {
        $obj = [System.IO.Path]::GetFileName($file) -replace '\.c$', '.o'
        Compile-File -source $file -obj $obj -isTestEnv $true
        [void]$objectList.Add($obj)
    }
    
    # 链接
    Write-Host "  链接: $Target" -ForegroundColor Cyan
    # 使用 ArrayList 构建参数数组，确保每个参数独立
    $linkArgs = New-Object System.Collections.ArrayList
    [void]$linkArgs.Add("-o")
    [void]$linkArgs.Add($Target)
    foreach ($obj in $objectList) {
        [void]$linkArgs.Add($obj)
    }
    foreach ($flag in $LDFLAGS) {
        [void]$linkArgs.Add($flag)
    }
    # 转换为数组并执行
    $argsArray = $linkArgs.ToArray()
    $linkOutput = & $CC $argsArray 2>&1
    $exitCode = $LASTEXITCODE
    if ($exitCode -ne 0) {
        Write-Host "  链接失败，退出代码: $exitCode" -ForegroundColor Red
        Write-Host "  链接错误详情:" -ForegroundColor Red
        $linkOutput | Where-Object { $_ -match "error|undefined|multiple definition" } | ForEach-Object {
            Write-Host "    $_" -ForegroundColor Red
        }
        throw "链接失败，退出代码: $exitCode"
    }
    
    Write-Host "? 构建成功!" -ForegroundColor Green
    Write-Host ""
}

# 运行测试
function Run-Tests {
    if (-not (Test-Path $Target)) {
        throw "测试可执行文件不存在，请先构建"
    }
    
    Write-Host "运行测试..." -ForegroundColor Yellow
    & ".\$Target"
    return $LASTEXITCODE
}

# 主逻辑
switch ($Action) {
    "clean" { Clean-Build }
    "run" { 
        $ec = Run-Tests
        exit $ec
    }
    "test" {
        $ec = Run-Tests
        & ".\$Target" | Tee-Object -FilePath "test_report.txt"
        Write-Host "测试报告: test_report.txt" -ForegroundColor Cyan
        exit $ec
    }
    "all" {
        Clean-Build
        Write-Host ""
        Build-Project
        Write-Host ""
        $ec = Run-Tests
        exit $ec
    }
    "help" {
        Write-Host "使用方法: .\build.ps1 [clean|run|test|all|help]" -ForegroundColor Cyan
        Write-Host "  all   - 清理、构建并运行测试（默认）" -ForegroundColor White
        Write-Host "  clean - 清理构建文件" -ForegroundColor White
        Write-Host "  run   - 运行测试" -ForegroundColor White
        Write-Host "  test  - 运行测试并生成报告" -ForegroundColor White
    }
}
```

---

## 常见问题与解决方案

### 问题1: 编译错误 - `absacc.h: No such file or directory`

**原因**: GCC不支持Keil C51的头文件

**解决方案**: 
- 在`test_compat.h`中定义相关宏（见兼容层实现）
- 使用`#ifdef TEST_ENV`条件编译排除硬件相关头文件

### 问题2: 类型冲突 - `conflicting types for 'int32_t'`

**原因**: MyPort.h中定义了int32_t等类型，与stdint.h冲突

**解决方案**: 
1. 创建包装器头文件（MyPort_test_wrapper.h）
2. 在MyPort.h中使用条件编译：
   ```c
   #ifdef __TYPEDEF_ALREADY_DEFINED__
   // 跳过类型定义
   #else
   // 定义类型
   #endif
   ```

### 问题3: 链接错误 - `undefined reference to 'WinMain'`

**原因**: GCC默认链接GUI应用，需要链接控制台应用

**解决方案**: 
在`build.ps1`中添加链接选项：
```powershell
$LDFLAGS = "-mconsole"
```

### 问题4: 多重定义错误 - `multiple definition of 'setup'`

**原因**: 多个测试文件都定义了setup/teardown函数

**解决方案**: 
使用弱符号（weak symbol）：
```c
__attribute__((weak)) void setup(void) { ... }
```

### 问题5: 全局变量未定义错误

**原因**: Project.c等文件中使用的全局变量在测试环境中未定义

**解决方案**: 
在`test_compat.c`中定义这些全局变量：
```c
uint8_t Gu8Timer_2ms = 0;
uint8_t Gu8Timer_10ms = 0;
// ...
```

### 问题6: 函数调用计数冲突

**原因**: test_Project.c和test_compat.c都定义了mock_Timer_Run等函数

**解决方案**: 
- test_compat.c中定义通用Mock函数（空实现）
- 测试文件中定义本地Mock函数（带计数），使用static避免冲突
- 或使用函数指针在运行时替换

---

## 快速开始模板

### 步骤1: 创建测试目录结构

```
User/Test/
├── unittest.h
├── unittest.c
├── test_compat.h
├── test_compat.c
├── test_runner.c
├── test_YourModule.c
├── YourModule_test.c  (如果需要，创建测试版本的源文件)
└── build.ps1
```

### 步骤2: 复制模板文件

1. 复制`test_compat.h`和`test_compat.c`（根据项目修改Mock函数）
2. 复制`unittest.h`和`unittest.c`
3. 复制`build.ps1`并根据项目修改源文件列表
4. 创建`test_YourModule.c`

### 步骤3: 创建测试用例

```c
// test_YourModule.c
#include "unittest.h"
#include "test_compat.h"
// 包含被测试模块的头文件（可能需要包装器）

__attribute__((weak)) void setup(void) {
    // 初始化
}

__attribute__((weak)) void teardown(void) {
    // 清理
}

TEST(YourFunction_NormalCase)
{
    // 测试代码
    TEST_ASSERT(1);  // 占位
}

void run_YourModule_tests(void)
{
    printf("Running YourModule Tests\n");
    RUN_TEST(YourFunction_NormalCase);
}
```

### 步骤4: 修改test_runner.c

添加测试函数声明和调用：
```c
extern void run_YourModule_tests(void);

int main(void) {
    // ...
    run_YourModule_tests();
    // ...
}
```

### 步骤5: 运行测试

```powershell
.\build.ps1
```

---

## 测试覆盖率建议

### 目标覆盖率: 90%+

### 测试用例类型

1. **正常路径测试** (Happy Path)
   - 正常输入和预期输出

2. **边界条件测试** (Boundary Conditions)
   - 最小值、最大值
   - 空值、零值
   - 数组边界

3. **错误处理测试** (Error Handling)
   - 无效输入
   - 异常情况

4. **分支覆盖** (Branch Coverage)
   - if/else所有分支
   - switch所有case
   - 循环边界

5. **组合场景测试** (Integration Scenarios)
   - 多个函数交互
   - 状态转换

### 示例测试矩阵

| 函数 | 正常输入 | 边界值 | 错误输入 | 分支覆盖 |
|------|---------|--------|---------|---------|
| MyMemorySet | ? | ? | ? | ? |
| MyMemoryCpy | ? | ? | ? | ? |
| Project | ? | ? | - | ? |

---

## 测试文件编写最佳实践

### 1. 测试文件结构

```c
// test_YourModule.c
#include "unittest.h"
#include "test_compat.h"

// 定义UNIT_TEST，让源文件知道这是测试环境
#define UNIT_TEST 1

// 注意：不包含原始头文件（如YourModule.h）
// 因为结构体定义已经在test_compat.h中
// 包含原始头文件会导致类型冲突和宏展开问题

// 声明被测试函数（在YourModule.c中定义）
extern void Func_YourModule(void);

// Mock硬件函数（这些函数会被YourModule.c中的extern声明引用）
static int P_YourModule_On_called = 0;
void P_YourModule_On(void) { P_YourModule_On_called++; }
void P_YourModule_Off(void) { P_YourModule_Off_called++; }

// Setup和Teardown
__attribute__((weak)) void setup(void)
{
    // 清零Mock函数调用计数
    P_YourModule_On_called = 0;
    
    // 初始化全局结构体
    memset(&YourModule, 0, sizeof(YourModule));
    // 设置默认参数值
    YourModule.u8_Param = 100;
}

__attribute__((weak)) void teardown(void)
{
    // 清理测试环境
}

// 测试用例
TEST(your_function_normal_case)
{
    // 测试代码
    Func_YourModule();
    TEST_ASSERT(YourModule.f_Status == 1);
}

// 测试运行函数
void run_YourModule_tests(void)
{
    printf("========================================\n");
    printf("Running YourModule Tests\n");
    printf("========================================\n\n");
    
    RUN_TEST(your_function_normal_case);
}
```

### 2. 关键要点

1. **不包含原始头文件**: 测试文件只包含`unittest.h`和`test_compat.h`，避免类型和宏冲突
2. **使用extern声明**: 只声明被测试的函数，不包含定义
3. **Mock函数定义**: 在测试文件中定义Mock函数，这些函数会被源文件中的`extern`声明引用
4. **条件编译**: 在源文件中使用`#if defined(UNIT_TEST)`来处理测试环境
5. **全局变量初始化**: 在`setup()`中初始化所有相关的全局变量

### 3. 源文件修改示例

```c
// YourModule.c
#include "main.h"

#if defined(UNIT_TEST)
    // 在测试环境中，全局变量在 test_compat.c 中定义
    extern STRUCT_YOURMODULE YourModule;
    
    // 取消硬件宏定义，声明为extern函数
    #undef P_YourModule_On
    #undef P_YourModule_Off
    extern void P_YourModule_On(void);
    extern void P_YourModule_Off(void);
#else
    STRUCT_YOURMODULE YourModule;  // 正常定义
#endif

void Func_YourModule(void)
{
    // 函数实现
    if (condition) {
        P_YourModule_On();  // 在测试环境中会调用Mock函数
    }
}
```

## 注意事项

1. **硬件依赖**: 所有硬件相关代码必须通过Mock函数处理
2. **全局变量**: 确保在test_compat.c中定义所有需要的全局变量，在源文件中使用条件编译
3. **条件编译**: 使用`#ifdef TEST_ENV`和`#if defined(UNIT_TEST)`区分测试环境和真实环境
4. **函数可见性**: 被测试函数必须是外部可见的（非static）
5. **内存管理**: 嵌入式代码通常不使用动态内存，测试中也要避免
6. **浮点数**: 避免在断言中直接比较浮点数，使用误差范围比较
7. **类型定义**: 所有结构体和枚举定义统一放在`test_compat.h`中，避免重复定义
8. **宏冲突**: 测试文件不包含原始头文件，避免宏展开冲突
9. **链接参数**: 使用`ArrayList`构建链接参数，确保PowerShell正确展开数组

---

## 参考资料

- [MinGW-w64 官网](https://www.mingw-w64.org/)
- [GCC 文档](https://gcc.gnu.org/onlinedocs/)
- [PowerShell 文档](https://docs.microsoft.com/powershell/)

---

## 更新日志

- **v1.0** (2024-01-XX): 初始版本
  - 兼容层实现
  - 测试框架搭建
  - 构建脚本
  - 常见问题解决方案

- **v1.1** (2025-01-XX): 实际项目应用经验总结
  - **关键修复**：PowerShell链接参数展开问题解决方案
    - 问题：所有目标文件名被连接成一个字符串
    - 原因：PowerShell数组展开机制不一致
    - 解决：使用`System.Collections.ArrayList`构建参数列表
  - 添加类型重定义冲突解决方案（统一在test_compat.h中定义）
  - 添加宏冲突解决方案（测试文件不包含原始头文件）
  - 添加全局变量多重定义解决方案（条件编译使用extern）
  - 添加未定义引用的解决方案
  - 改进错误日志输出（显示退出代码和详细错误信息）
  - 实际项目中的完整测试框架实现经验

- **v1.1** (2025-01-XX): 实际项目应用经验总结
  - 添加类型重定义冲突解决方案
  - 添加宏冲突解决方案（关键：测试文件不包含原始头文件）
  - 添加全局变量多重定义解决方案（条件编译使用extern）
  - **重点**：添加PowerShell链接参数展开问题的详细分析和解决方案
  - 添加未定义引用的解决方案
  - 改进错误日志输出方法
  - 实际项目中的完整测试框架实现经验

---

## 许可证

本文档适用于内部项目使用。

