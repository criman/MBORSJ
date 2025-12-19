#ifndef _ECBM_MODBUS_H_
#define _ECBM_MODBUS_H_
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2023 奈特

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

免责说明：
    本软件库以MIT开源协议免费向大众提供。作者只保证原始版本是由作者在维护修BUG，
其他通过网络传播的版本也许被二次修改过，由此出现的BUG与作者无关。而当您使用原始
版本出现BUG时，请联系作者解决。
                            **************************
                            * 联系方式：进群778916610 *
                            * 若1群满人：进群927297508*
                            **************************
------------------------------------------------------------------------------------*/
#define MainSoftWareVersion   0x023F		//内机版本
//-----------------以下是图形设置界面，可在Configuration Wizard界面设置-----------------
//<<< Use Configuration Wizard in Context Menu >>>
//<q>使能IO控制读写功能？
//<i>使能后需要自己定义实现接口函数，函数内部放控制IO的语句，IO电平由形参传入
//<i>当modbus需要控制IO的时候会调用这个接口函数
//<i>void ecbm_modbus_rtu_set_io(emu8 dat)
//<i>{
//<i>    gpio_out_fast(GPIO_P5, GPIO_PIN_5, dat);
//<i>    //gpio_out(RS485_ENA,dat);
//<i>}
#define ECBM_MODBUS_IO_EN 1
//<h>MODBUS_RTU
#define ECBM_MODBUS_VERSION "V1.0.4"
//<i>这是modbus协议的RTU模式。
//<o>本机地址/ID
//<1-247>
//<i>8位的地址，可使用的范围是1~247，0作为广播地址。
#define ECBM_MODBUS_RTU_ID_ADRESS 1
//<o>超时时间
//<i>单位为定时器中断次数。比如500就是定时器中断500次，若每次中断的间隔是1ms，那么就是500mS超时。
#define ECBM_MODBUS_RTU_TIME_MAX  5		//10ms
//<h>线圈读写功能设置
//<e>线圈缓存
//<i>勾选后会定义一个数组作为缓存，线圈指令操作都会指向这个数组，适合新项目的开始。可以使用读写函数获取数组内部的值。
//<i>不勾选的话，可以通过移植两个读写函数将读写线圈功能映射到任意的地方。适合为老项目增加modbus功能。
#define ECBM_MODBUS_RTU_BIT_BUF_EN 0
//<o>线圈起始地址
//<i>有时候为了适配别人的协议，地址不一定是从0开始的，在这里可以设置一个偏移。
#define ECBM_MODBUS_RTU_BIT_START_ADDR 0
//<o>线圈缓存总数
//<i>单位是字节（8位），请根据需求填写。比如设备要有10个线圈，因为至少需要两个字节才能存完10个，那么就应该填2。
#define ECBM_MODBUS_RTU_BIT_BUF_SIZE  3
//</e>
//<h>线圈指令使能
//<i>如果和线圈有关的指令都没有被使能，那么线圈读写相关的函数和缓存都将被优化掉。
//<q>[01]读线圈
#define ECBM_MODBUS_RTU_CMD01_EN 0
//<q>[05]写单个线圈
#define ECBM_MODBUS_RTU_CMD05_EN 0
//</h>
//</h>
//<h>寄存器读写功能设置
//<e>寄存器缓存
#define ECBM_MODBUS_RTU_REG_BUF_EN 1
//<o>寄存器起始地址
//<i>有时候为了适配别人的协议，地址不一定是从0开始的，在这里可以设置一个偏移。
#define ECBM_MODBUS_RTU_REG_START_ADDR 0
//<o>寄存器缓存总数
//<i>单位是字（16位），请根据需求填写。
#define ECBM_MODBUS_RTU_REG_BUF_SIZE  512
//</e>
//<h>寄存器指令使能
//<i>如果和寄存器有关的指令都没有被使能，那么线圈读写相关的函数和缓存都将被优化掉。
//<q>[03]读寄存器
#define ECBM_MODBUS_RTU_CMD03_EN 1
//<q>[06]写单个寄存器
#define ECBM_MODBUS_RTU_CMD06_EN 1
//<e>[10]写多个寄存器
#define ECBM_MODBUS_RTU_CMD10_EN 1
//<o>寄存器写入缓存总数
//<i>单位是字节（8位），由于CRC的存在，在多字节写入的时候，不能立刻把数据存入，需要用一个缓存存起来，待CRC验证完毕之后才能一起写入。
#define ECBM_MODBUS_RTU_BUF_SIZE  10
//</e>
//</h>
//</h>
//<h>IO系统指令使能
//<i>如果和IO系统有关的指令都没有被使能，那么IO相关的函数和缓存都将被优化掉。
//<q>[02]读离散量输入
#define ECBM_MODBUS_RTU_CMD02_EN 0
//<q>[04]读输入寄存器
#define ECBM_MODBUS_RTU_CMD04_EN 0
//</h>
#define ECBM_MODBUS_RTU_CMD_BIT_EN  (ECBM_MODBUS_RTU_CMD01_EN+ECBM_MODBUS_RTU_CMD05_EN)
#define ECBM_MODBUS_RTU_CMD_REG_EN  (ECBM_MODBUS_RTU_CMD03_EN+ECBM_MODBUS_RTU_CMD06_EN+ECBM_MODBUS_RTU_CMD10_EN)
#define ECBM_MODBUS_RTU_CMD_IO_EN   (ECBM_MODBUS_RTU_CMD02_EN+ECBM_MODBUS_RTU_CMD04_EN)
#define ECBM_MODBUS_RTU_CMD_ALL_EN  (ECBM_MODBUS_RTU_CMD_BIT_EN+ECBM_MODBUS_RTU_CMD_REG_EN+ECBM_MODBUS_RTU_CMD_IO_EN)
//<<< end of configuration section >>>
//-----------------以上是图形设置界面，可在Configuration Wizard界面设置-----------------
/*-----------------------------------数据类型宏定义--------------------------------*/
//#define fast_type      idata        //快速内存区。
//#define large_type     xdata        //大容量内存区。
typedef unsigned char  emu8;     //8位无符号型变量。
typedef unsigned short emu16;    //16位无符号型变量。
typedef unsigned long  emu32;    //32位无符号型变量。
/*------------------------------------状态机宏定义---------------------------------*/
#define ECBM_MODBUS_RTU_READY           0   //就绪态，此时可以接受一帧modbus数据。
#define ECBM_MODBUS_RTU_WAIT            1   //等待态，当发生错误之后，在此等待当前数据帧结束。
#define ECBM_MODBUS_RTU_ID_ERR          2   //ID错误，当接收到的ID不是本机也不是广播地址时会到这里。
#define ECBM_MODBUS_RTU_FUN_NUM         3   //读取功能码，在此读取功能码。
#define ECBM_MODBUS_RTU_FUN_NUM_ERR     4   //功能码错误，功能码原则上小于128，超过就会到这里。
#define ECBM_MODBUS_RTU_FUN_NUM_VOID    5   //功能码不存在，主要原因是本机不支持该功能码。
#define ECBM_MODBUS_RTU_ADDRH           6   //读取地址高8位。
#define ECBM_MODBUS_RTU_ADDRL           7   //读取地址低8位。
#define ECBM_MODBUS_RTU_DATA_COUNTH     8   //读取数据或者个数的高8位。
#define ECBM_MODBUS_RTU_DATA_COUNTL     9   //读取数据或者个数的低8位。
#define ECBM_MODBUS_RTU_COUNT_ERR       10  //读取个数错误。
#define ECBM_MODBUS_RTU_CRCH            11  //读取CRC的高8位。
#define ECBM_MODBUS_RTU_CRCL            12  //读取CRC的低8位。
#define ECBM_MODBUS_RTU_CRC_ERR         13  //CRC错误，当接收到的数据的CRC和传输的CRC不一致时会报错。
#define ECBM_MODBUS_RTU_DO              14  //处理态，在该状态下处理数据。
#define ECBM_MODBUS_RTU_DATAH           15  //读取地址高8位。
#define ECBM_MODBUS_RTU_DATAL           16  //读取地址低8位。
#define ECBM_MODBUS_RTU_BYTE_COUNT      17  //读取字节数量。
#define ECBM_MODBUS_RTU_BYTE_ERR        18  //读取字节数量对应不上。
/*-------------------------------------返回值定义----------------------------------*/
#define ECBM_MODBUS_RTU_OK              0   //正常。
#define ECBM_MODBUS_RTU_BIT_ADDR_ERR    1   //比特位地址错误。
#define ECBM_MODBUS_RTU_REG_ADDR_ERR    2   //寄存器地址错误。
#define ECBM_MODBUS_RTU_IO_ADDR_ERR     3   //IO地址错误。
/*-------------------------------220709增加使能脚控制功能----------------------------*/


#define ECBM_MODBUS_READ    0   //读使能
#define ECBM_MODBUS_WRITE   1   //写使能


/*--------------------------------------变量定义-----------------------------------*/
extern emu16  ecbm_modbus_rtu_crc;          //初始化CRC变量各位为1。
extern emu8   ecbm_modbus_rtu_status;       //状态机使用的变量。
extern emu8   ecbm_modbus_rtu_id;           //本机的设备ID。
extern emu8   ecbm_modbus_rtu_fun_code;     //功能码。
extern emu8   ecbm_modbus_rtu_fun_err_num;  //异常码。
extern emu16  ecbm_modbus_rtu_address;      //数据地址。
extern emu16  ecbm_modbus_rtu_data_count;   //数据/个数。
extern emu16  ecbm_modbus_rtu_crc_buf;      //CRC缓存。
extern emu16  ecbm_modbus_rtu_timeout;      //超时计算。
extern emu16  ecbm_modbus_rtu_uart_crc;     //CRC计算缓存。
extern emu8   ecbm_modbus_rtu_cmd_count;    //指令缓存计数。
extern emu8   ecbm_modbus_rtu_broadcast_en; //广播模式。

#if ECBM_MODBUS_RTU_BIT_BUF_EN
extern emu8   ecbm_modbus_rtu_bit_buf[ECBM_MODBUS_RTU_BIT_BUF_SIZE];//比特线圈存放变量。
#endif
#if ECBM_MODBUS_RTU_REG_BUF_EN
extern emu16  ecbm_modbus_rtu_reg_buf[ECBM_MODBUS_RTU_REG_BUF_SIZE];//寄存器存放变量。
#if 1
//0x00~0x64


#define  T4Temp	 				0x03	//环境温度 (0.1精度)
#define  u16MB_T4Temp	 		ecbm_modbus_rtu_reg_buf[T4Temp]	//内盘管温度 (0.1精度)
#define  TpTemp	 				0x04	//排气温度 (0.1精度)
#define  u16MB_TpTemp	 		ecbm_modbus_rtu_reg_buf[TpTemp]	//排气温度 (0.1精度)
#define  T3Temp	 				0x06	//排气温度 (0.1精度)
#define  u16MB_T3Temp	 		ecbm_modbus_rtu_reg_buf[T3Temp]	//外盘温度 (0.1精度)
#define  T5Temp	 				0x00	//水箱温度 (0.1精度)
#define  u16MB_T5Temp	 		ecbm_modbus_rtu_reg_buf[T5Temp]	//水箱温度 (0.1精度)
#define  T5ITemp	 			0x01	//进水温度 (0.1精度)
#define  u16MB_T5ITemp	 		ecbm_modbus_rtu_reg_buf[T5ITemp]	//进水温度 (0.1精度)
#define  T5OTemp	 			0x02	//出水温度 (0.1精度)
#define  u16MB_T5OTemp	 		ecbm_modbus_rtu_reg_buf[T5OTemp]	//出水温度 (0.1精度)
#define  THTemp	 				0x05	//回气温度 (0.1精度)
#define  u16MB_THTemp	 		ecbm_modbus_rtu_reg_buf[THTemp]	//出水温度 (0.1精度)
#define  CurEEVStep	 			0x07	//电子膨胀阀开度
#define  u16MB_CurEEVStep	 	ecbm_modbus_rtu_reg_buf[CurEEVStep]	//电子膨胀阀开度

#define  FlagWork				0x0C
#define  u16MB_FlagWork 		ecbm_modbus_rtu_reg_buf[FlagWork]	//工作标志
#define  FlagOutPut1 			0x0D//输出标志1
#define  u16MB_FlagOutPut1 		ecbm_modbus_rtu_reg_buf[FlagOutPut1] 	//输出标志1
#define  FlagOutPut2 			0x0E	//输出标志2
#define  u16MB_FlagOutPut2 		ecbm_modbus_rtu_reg_buf[u16MB_FlagOutPut2]	//输出标志2
#define  FlagOutPut3 			0x0F	//输出标志3
#define  u16MB_FlagOutPut3 		ecbm_modbus_rtu_reg_buf[FlagOutPut3]	//输出标志3
#define  FlagErr1 				0x10	//故障标志1
#define  u16MB_FlagErr1 		ecbm_modbus_rtu_reg_buf[u16MB_FlagErr1]	//故障标志1
#define  FlagErr2 				0x11	//故障标志2
#define  u16MB_FlagErr2 		ecbm_modbus_rtu_reg_buf[FlagErr2]	//故障标志2
#define  FlagErr3 				0x12	//故障标志3
#define  u16MB_FlagErr3 		ecbm_modbus_rtu_reg_buf[FlagErr3]	//故障标志3
#define  FlagErr4 				0x13	//故障标志4
#define  u16MB_FlagErr4 		ecbm_modbus_rtu_reg_buf[FlagErr4]	//故障标志4
#define  FlagErr5 				0x14	//故障标志5
#define  u16MB_FlagErr5 		ecbm_modbus_rtu_reg_buf[FlagErr5]	//故障标志5
#define  FlagErr6 				0x15	//故障标志6
#define  u16MB_FlagErr6 		ecbm_modbus_rtu_reg_buf[FlagErr6]	//故障标志6

#define  HP_Err_Cnt				0x16	//高压保护累计计数
#define  u16MB_HP_Err_Cnt		ecbm_modbus_rtu_reg_buf[HP_Err_Cnt]
#define  LP_Err_Cnt				0x17	//低压保护累计计数
#define  u16MB_LP_Err_Cnt		ecbm_modbus_rtu_reg_buf[LP_Err_Cnt]
#define  TPHigh_Err_Cnt			0x18	//排气过高保护累计计数
#define  u16MB_TPHigh_Err_Cnt	ecbm_modbus_rtu_reg_buf[TPHigh_Err_Cnt]

#define  TPHigh_Err_Cnt			0x18	//排气过高保护累计计数
#define  u16MB_TPHigh_Err_Cnt	ecbm_modbus_rtu_reg_buf[TPHigh_Err_Cnt]

#define  MachType		 		0x1A	//机型
#define  u16MB_MachType		 	ecbm_modbus_rtu_reg_buf[MachType]	
#define  SoftwareVersion		0x1B	//主控版本
#define  u16MB_SoftwareVersion  ecbm_modbus_rtu_reg_buf[SoftwareVersion]	
#define  FlagCtrl		 		0x1C	//控制标志
#define  u16MB_FlagCtrl		 	ecbm_modbus_rtu_reg_buf[u16MB_FlagCtrl]	//控制标志
#define  WokeMode				0x1D	//模式
#define  u16MB_WokeMode			ecbm_modbus_rtu_reg_buf[WokeMode]	//模式
#define  EEVSet					0x1E	//主膨胀阀手动步数
#define  u16MB_EEVSet			ecbm_modbus_rtu_reg_buf[EEVSet]	
#define  EEVMinSet				0x1F	//主膨胀阀最小开度设定
#define  u16MB_EEVMinSet		ecbm_modbus_rtu_reg_buf[EEVMinSet]	
#define  ColdSuperHeat			0x20	//制冷过热度
#define  u16MB_ColdSuperHeat	ecbm_modbus_rtu_reg_buf[ColdSuperHeat]	

#define  CoolSetTemp			0x21	//制冷设定温度
#define  u16MB_CoolSetTemp		ecbm_modbus_rtu_reg_buf[CoolSetTemp]	//制冷设定温度

#define  WFV_Set				0x23	//补水阀工作状态设置	0~4	0：未设置 1：定时补水 2：自动补水 3：手动补水 4：手动关闭补水
#define  u16MB_WFV_Set			ecbm_modbus_rtu_reg_buf[WFV_Set]

#define  	P1	0x27	//	压缩机启动后最小运行时间
#define  	P2	0x28	//	风机运行后延时开启压缩机的时间
#define  	P3	0x29	//	压缩机关闭后延时关闭风机的时间
#define  	P4	0x2A	//	水泵启动后延时开启风机的时间
#define  	P5	0x2B	//	风机关闭后延时关闭循环水泵的时间
#define  	P6	0x2C	//	水泵启动后开始检测水流开关的时间
#define  	P7	0x2D	//	水流开关信号断开持续时间
#define  	P8	0x2E	//	循环水泵防生锈卡死的运行时间
#define  	P9	0x2F	//	定时补水延时开启补水阀时间
#define  	P10	0x30	//	自动补水延时开启补水阀时间
#define  	P11	0x31	//	自动补水延时关闭补水阀时间
#define  	P12	0x32	//	手动开启或者手动关闭补水的按键时间
#define  	P13	0x33	//	压缩机停机时电子膨胀阀开度
#define  	P14	0x34	//	电子膨胀阀动作周期
#define  	P15	0x35	//	目标过热度补偿设定
#define  	P16	0x36	//	膨胀阀调节时允许排气温度
#define  	P17	0x37	//	旁通阀开启条件之一的环境温度值
#define  	P18	0x38	//	旁通阀开启条件之二的水箱温度值
#define  	P19	0x39	//	旁通阀开启条件之三的排气温度值
#define  	P20	0x3A	//	旁通阀开启条件之四的排气温度值
#define  	P21	0x3B	//	旁通阀关闭条件之一的排气温度值
#define  	P22	0x3C	//	旁通阀关闭条件之二的水箱温度值
#define  	P23	0x3D	//	压缩机启动后屏蔽低压保护的时间
#define  	P24	0x3E	//	排气温度过高保护的限定值
#define  	P25	0x3F	//	排气温度过高保护的退出值
#define  	P26	0x40	//	防冻保护条件之一的环境温度值
#define  	P27	0x41	//	防冻保护条件之二的水箱温度值
#define  	P28	0x42	//	防冻保护条件之三的时间持续值
#define  	P29	0x43	//	定时补水期间补水阀持续补水时长

#define  	F1	0x48	//	制冷水箱设定温度下限值
#define  	F2	0x49	//	制冷水箱设定温度上限值
#define  	F3	0x4A	//	水流开关安装配置选择
#define  	F4	0x4B	//	水箱感温包温度补偿值

#define  	L1	0x50	//	水泵连续停机时间
#define  	L2	0x51	//	启动温差


#else 

//0x00~0x64
#define  FlagWork				0x0C
#define  u16MB_FlagWork 		ecbm_modbus_rtu_reg_buf[FlagWork]	//工作标志
#define  FlagOutPut1 			0x0D//输出标志1
#define  u16MB_FlagOutPut1 		ecbm_modbus_rtu_reg_buf[FlagOutPut1] 	//输出标志1
#define  FlagOutPut2 			0x0E	//输出标志2
#define  u16MB_FlagOutPut2 		ecbm_modbus_rtu_reg_buf[u16MB_FlagOutPut2]	//输出标志2
#define  FlagOutPut3 			0x0F	//输出标志3
#define  u16MB_FlagOutPut3 		ecbm_modbus_rtu_reg_buf[FlagOutPut3]	//输出标志3
#define  FlagErr1 				0x10	//故障标志1
#define  u16MB_FlagErr1 		ecbm_modbus_rtu_reg_buf[u16MB_FlagErr1]	//故障标志1
#define  FlagErr2 				0x11	//故障标志2
#define  u16MB_FlagErr2 		ecbm_modbus_rtu_reg_buf[FlagErr2]	//故障标志2
#define  FlagErr3 				0x12	//故障标志3
#define  u16MB_FlagErr3 		ecbm_modbus_rtu_reg_buf[FlagErr3]	//故障标志3
#define  FlagErr4 				0x13	//故障标志4
#define  u16MB_FlagErr4 		ecbm_modbus_rtu_reg_buf[FlagErr4]	//故障标志4
#define  FlagErr5 				0x14	//故障标志5
#define  u16MB_FlagErr5 		ecbm_modbus_rtu_reg_buf[FlagErr5]	//故障标志5
#define  FlagInFan 				0x16	//内风机输出标志
#define  u16MB_FlagInFan 		ecbm_modbus_rtu_reg_buf[FlagInFan]	//内风机输出标志
#define  T4Temp	 				0x18	//环境温度 (0.1精度)
#define  u16MB_T4Temp	 		ecbm_modbus_rtu_reg_buf[T4Temp]	//内盘管温度 (0.1精度)
#define  TpTemp	 				0x19	//排气温度 (0.1精度)
#define  u16MB_TpTemp	 		ecbm_modbus_rtu_reg_buf[TpTemp]	//排气温度 (0.1精度)
#define  T3Temp	 				0x1B	//排气温度 (0.1精度)
#define  u16MB_T3Temp	 		ecbm_modbus_rtu_reg_buf[T3Temp]	//外盘温度 (0.1精度)
#define  T1Temp	 				0x1E	//进风温度 (0.1精度)
#define  u16MB_T1Temp	 		ecbm_modbus_rtu_reg_buf[T1Temp]	//进风温度 (0.1精度)
#define  T2Temp	 				0x1F	//内盘管温度 (0.1精度)
#define  u16MB_T2Temp	 		ecbm_modbus_rtu_reg_buf[T2Temp]	//内盘管温度 (0.1精度)
#define  T5Temp	 				0x01	//水箱温度 (0.1精度)
#define  u16MB_T5Temp	 		ecbm_modbus_rtu_reg_buf[T5Temp]	//水箱温度 (0.1精度)
#define  T5ITemp	 			0x02	//进水温度 (0.1精度)
#define  u16MB_T5ITemp	 		ecbm_modbus_rtu_reg_buf[T5ITemp]	//进水温度 (0.1精度)
#define  T5OTemp	 			0x03	//出水温度 (0.1精度)
#define  u16MB_T5OTemp	 		ecbm_modbus_rtu_reg_buf[T5OTemp]	//出水温度 (0.1精度)
#define  THTemp	 				0x1A	//回气温度 (0.1精度)
#define  u16MB_THTemp	 		ecbm_modbus_rtu_reg_buf[THTemp]	//出水温度 (0.1精度)


#define  FlagErr6 				0x20	//故障标志6
#define  u16MB_FlagErr6 		ecbm_modbus_rtu_reg_buf[FlagErr6]	//故障标志6
#define  Current		 		0x23	//当前电流值 (0.1精度)
#define  u16MB_Cur		 		ecbm_modbus_rtu_reg_buf[u16MB_Cur]	//当前电流值 (0.1精度)
#define  SoftwareVersion		0x27	//控制标志
#define  u16MB_SoftwareVersion  ecbm_modbus_rtu_reg_buf[SoftwareVersion]	//控制标志
#define  FlagCtrl		 		0x28	//控制标志
#define  u16MB_FlagCtrl		 	ecbm_modbus_rtu_reg_buf[u16MB_FlagCtrl]	//控制标志
#define  WokeMode				0x2A	//模式
#define  u16MB_WokeMode			ecbm_modbus_rtu_reg_buf[WokeMode]	//模式
#define  FanSet					0x2B	//风机模式选择
#define  u16MB_FanSet			ecbm_modbus_rtu_reg_buf[FanSet]	//风机模式选择
#define  EEVSet					0x2E	//风机模式选择 主膨胀阀最小开度设定
#define  u16MB_EEVSet			ecbm_modbus_rtu_reg_buf[EEVSet]	//风机模式选择

//TBD
#define  DefrostDutySet			0x3C	//除霜周期设定
#define  u16MB_DefrostDutySet	ecbm_modbus_rtu_reg_buf[DefrostDutySet]	//除霜周期设定
#define  TimeDefrostMaxSet		0x3D	//最长除霜时间设定
#define  u16MB_TimeDefrostMaxSet	ecbm_modbus_rtu_reg_buf[TimeDefrostMaxSet]	//最长除霜时间设定
#define  TempDefrostOnSet		0x3E	//除霜进入温设定
#define  u16MB_TempDefrostOnSet	ecbm_modbus_rtu_reg_buf[TempDefrostOnSet]	//除霜进入温设定
#define  TempDiffT3T4DefrostOn	0x3F	//可进入除霜环境温度与盘管温差
#define  u16MB_TempDiffT3T4DefrostOn	ecbm_modbus_rtu_reg_buf[TempDiffT3T4DefrostOn]	//可进入除霜环境温度与盘管温差
//TBD
#define  CoolSetTemp			0x40	//制冷设定温度
#define  u16MB_CoolSetTemp		ecbm_modbus_rtu_reg_buf[CoolSetTemp]	//制冷设定温度
#define  CoolHE					0x41	//制冷回差温度
#define  u16MB_CoolHE			ecbm_modbus_rtu_reg_buf[CoolHE]	//制冷回差温度
#define  HeatSetTemp			0x42	//制热设定温度
#define  u16MB_HeatSetTemp		ecbm_modbus_rtu_reg_buf[HeatSetTemp]	//制热设定温度
#define  HeatHE					0x43	//制热回差温度
#define  u16MB_HeatHE			ecbm_modbus_rtu_reg_buf[HeatHE]	//制热回差温度
#define  TimeHPProt				0x5D	//压机保护时间min
#define  u16MB_TimeHPProt		ecbm_modbus_rtu_reg_buf[TimeHPProt]	//压机保护时间min
#define  TimeFanDelayOFF		0x5E	//风机延时关闭时间s
#define  u16MB_TimeFanDelayOFF	ecbm_modbus_rtu_reg_buf[TimeFanDelayOFF]	//风机延时关闭时间s
#define  TimeFanAheadON			0x5F	//风机提前打开时间s
#define  u16MB_TimeFanAheadON	ecbm_modbus_rtu_reg_buf[TimeFanAheadON]	//风机提前打开时间s
#define  TempSVON				0x60	//喷液阀开温度
#define  u16MB_TimeSVON			ecbm_modbus_rtu_reg_buf[TempSVON]	//喷液阀开温度
#define  TempSVOFF				0x61	//喷液阀关温度
#define  u16MB_TimeSVOFF		ecbm_modbus_rtu_reg_buf[TempSVOFF]	//喷液阀关温度
#define  OverCurProt			0x62	//电流报警设置值A
#define  u16MB_OverCurProt		ecbm_modbus_rtu_reg_buf[OverCurProt]	//电流报警设置值A
#define  Lock4G					0x63	//4G锁机标志
#define  u16MB_4GLock			ecbm_modbus_rtu_reg_buf[Lock4G]	//4G锁机标志
#define  FanSpMASet				0x64	//手动设定风速
#define  u16MB_FanSpMASet		ecbm_modbus_rtu_reg_buf[FanSpMASet]	//手动设定风速
#endif

//0x100~0x1FF
#define  Test_Enable				0xFF	//测试状态
#define  u16MB_Test_Enable			ecbm_modbus_rtu_reg_buf[Test_Enable]
#define  DefrostBits				0x100	//化霜状态位
#define  u16MB_DefrostBits			ecbm_modbus_rtu_reg_buf[DefrostBits]	
#define  DF_s16_T30Mul10			0x101	//T3最小值(*10)
#define  u16MB_s16_T30Mul10			ecbm_modbus_rtu_reg_buf[DF_s16_T30Mul10]	
#define  DF_u16_FindT30_Count		0x102	//寻找T30时间计时(压缩机开启时重新计时)
#define  u16MB_u16_FindT30_Count	ecbm_modbus_rtu_reg_buf[DF_u16_FindT30_Count]	
#define  DF_u16_HeatRun_Count		0x103	//制热运行时间计时
#define  u16MB_u16_HeatRun_Count	ecbm_modbus_rtu_reg_buf[DF_u16_HeatRun_Count]
#define  DF_u16_DefCase3_Count		0x104	//条件三满足持续计时
#define  u16MB_u16_DefCase3_Count	ecbm_modbus_rtu_reg_buf[DF_u16_DefCase3_Count]	
#define  DF_u16_DefQCase2_Count		0x105	//退出条件二满足持续计时
#define  u16MB_u16_DefQCase2_Count	ecbm_modbus_rtu_reg_buf[DF_u16_DefQCase2_Count]	
#define  DF_u16_Defrosting_Count	0x106	//化霜进行时计时
#define  u16MB_u16_Defrosting_Count	ecbm_modbus_rtu_reg_buf[DF_u16_Defrosting_Count]	
#define  DF_u8_Step					0x107	//化霜阶段
#define  u16MB_u8_Step				ecbm_modbus_rtu_reg_buf[DF_u8_Step]
#define  DF_u16_Step_Delay			0x108	//化霜阶段经历倒计时
#define  u16MB_u16_Step_Delay		ecbm_modbus_rtu_reg_buf[DF_u16_Step_Delay]
//#define  HP_Err_Cnt					0x109	//高压保护计时
//#define  u16MB_HP_Err_Cnt			ecbm_modbus_rtu_reg_buf[HP_Err_Cnt]
//#define  LP_Err_Cnt					0x10A	//低压保护计时
//#define  u16MB_LP_Err_Cnt			ecbm_modbus_rtu_reg_buf[LP_Err_Cnt]
#define  RLY_Ctrl					0x10B	//继电器强控
#define  u16MB_RLY_Ctrl				ecbm_modbus_rtu_reg_buf[RLY_Ctrl]
#define  Input_Sta					0x10C	//输入端口状态
#define  u16MB_Input_Sta			ecbm_modbus_rtu_reg_buf[Input_Sta]
#define  EEV_SuperHeatAvg			0x10D	//平均过热度
#define  u16MB_EEV_SuperHeatAvg		ecbm_modbus_rtu_reg_buf[EEV_SuperHeatAvg]
#define  EEV_DeltaStep				0x10E	//开度变化值
#define  u16MB_EEV_DeltaStep		ecbm_modbus_rtu_reg_buf[EEV_DeltaStep]


#endif
#if ECBM_MODBUS_RTU_CMD10_EN
extern emu16  ecbm_modbus_rtu_cmd_buf[ECBM_MODBUS_RTU_BUF_SIZE];//指令缓存。
#endif
/*--------------------------------------函数定义-----------------------------------*/
/**
 * @brief 设置485芯片的读写IO脚,220709
 * 
 * @param dat 电平状态
 */
extern void ecbm_modbus_rtu_set_io(emu8 dat);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_set_data
描  述：发送数据函数。需要用户移植。
输  入：
    dat     要发送的数据
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_set_data(emu8 dat);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_get_data
描  述：数据接收函数。需要用户移植。
输  入：无
输  出：无
返回值：接收到的数据。
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
-------------------------------------------------------*/
extern emu8 ecbm_modbus_rtu_get_data(void);
/*-------------------------------------------------------
函数名：ECBM_MODBUS_RTU_TIMEOUT_RUN
描  述：走时宏定义，为了加快运行速度，所以做成了宏定义。需要用户移植。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-10
修改记录：
-------------------------------------------------------*/
#define ECBM_MODBUS_RTU_TIMEOUT_RUN()   \
do{\
    if(ecbm_modbus_rtu_timeout>0)/*不为0的时候才增加。*/\
        ecbm_modbus_rtu_timeout++;/*时间往上加。*/\
    if(ecbm_modbus_rtu_timeout>ECBM_MODBUS_RTU_TIME_MAX){/*超时的时候，*/\
        ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_READY;/*回到就绪态。*/\
        ecbm_modbus_rtu_timeout=0;/*同时关闭时间累积。*/\
    }\
}while(0)
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_crc16
描  述：CRC16计算函数。
输  入：
    buf     需要计算CRC的数据
输  出：
    ecbm_modbus_rtu_crc     计算的结果
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-10 
修改记录：
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_crc16(emu8 buf);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_check_fun_num
描  述：检测功能码函数。
输  入：
    fun_num     功能码
输  出：无
返回值：功能码存在返回本身，不存在返回0x80+功能码。
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
-------------------------------------------------------*/
extern emu8 ecbm_modbus_rtu_check_fun_num(emu8 fun_num);
/*-------------------------------------------------------
函数名：ecbm_modbus_cmd_read_io_bit
描  述：读输入离散量函数。
输  入：
    addr    离散量地址
输  出：
    dat     比特值
返回值：读取结果
创建者：奈特
调用例程：无
创建日期：2021-03-15
修改记录：
-------------------------------------------------------*/
extern emu8 ecbm_modbus_cmd_read_io_bit(emu16 addr,emu8 * dat);
/*-------------------------------------------------------
函数名：ecbm_modbus_cmd_read_io_reg
描  述：读输入寄存器函数。
输  入：
    addr    寄存器地址
输  出：
    dat     寄存器值
返回值：读取结果
创建者：奈特
调用例程：无
创建日期：2021-03-15
修改记录：
-------------------------------------------------------*/
extern emu8 ecbm_modbus_cmd_read_io_reg(emu16 addr,emu16 * dat);
/*-------------------------------------------------------
函数名：ecbm_modbus_cmd_write_bit
描  述：写比特数据函数。
输  入：
    addr    比特位地址
    dat     比特值
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-16：取消返回值，优化运行速度。
-------------------------------------------------------*/
extern void ecbm_modbus_cmd_write_bit(emu16 addr,emu8 dat);
/*-------------------------------------------------------
函数名：ecbm_modbus_cmd_read_bit
描  述：读比特数据函数。
输  入：
    addr    比特位地址
输  出：
    dat     比特值
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-16：取消返回值，优化运行速度。
-------------------------------------------------------*/
extern void ecbm_modbus_cmd_read_bit(emu16 addr,emu8 * dat);
/*-------------------------------------------------------
函数名：ecbm_modbus_cmd_write_reg
描  述：写寄存器数据函数。
输  入：
    addr    寄存器地址
    dat     寄存器值
输  出：无
返回值：读取结果
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-16：取消返回值，优化运行速度。
-------------------------------------------------------*/
extern void ecbm_modbus_cmd_write_reg(emu16 addr,emu16 dat);
/*-------------------------------------------------------
函数名：ecbm_modbus_cmd_read_reg
描  述：读寄存器函数。
输  入：
    addr    寄存器地址
输  出：
    dat     寄存器值
返回值：读取结果
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-16：取消返回值，优化运行速度。
-------------------------------------------------------*/
extern void ecbm_modbus_cmd_read_reg(emu16 addr,emu16 * dat);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_cmd_0x01
描  述：1号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-09：新增CRC校验。
2021-03-15：修改了异常码02的触发条件。
2021-03-16：新增异常码04的触发条件。
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_cmd_0x01(void);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_cmd_0x02
描  述：2号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-15
修改记录：
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_cmd_0x02(void);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_cmd_0x03
描  述：3号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-09：新增CRC校验。
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_cmd_0x03(void);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_cmd_0x05
描  述：5号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-09：新增CRC校验。
2021-03-16：新增异常码04的触发条件，优化了部分执行代码。
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_cmd_0x05(void);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_cmd_0x06
描  述：6号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-09：新增CRC校验。
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_cmd_0x06(void);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_cmd_0x10
描  述：16号功能码处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-12
修改记录：
-------------------------------------------------------*/
void ecbm_modbus_rtu_cmd_0x10(void);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_receive
描  述：modbus接收处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-09：新增CRC校验。
2021-03-12：新增0x10指令相关处理,新增0xff广播地址。
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_receive(void);
/*-------------------------------------------------------
函数名：ecbm_modbus_rtu_run
描  述：modbus主循环处理函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2021-03-05
修改记录：
2021-03-09：新增CRC校验相关代码。
2021-03-12：新增0x10指令相关处理。
-------------------------------------------------------*/
extern void ecbm_modbus_rtu_run(void);

/*-------------------------------------------------------
函数名：uart2_receive_callback
描  述：串口接收回调函数。
输  入：无
输  出：无
返回值：无
创建者：冯锐辉
调用例程：无
创建日期：2025年7月24日17:47:17
修改记录：

-------------------------------------------------------*/
extern void uart0_receive_callback(void);

#endif 
