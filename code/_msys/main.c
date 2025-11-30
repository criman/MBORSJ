/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: main.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2022/03/10
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"
//#include "SEGGER_RTT_Demo.h" //lcx add

/* 说明：
 * 1. 正常固件运行（Keil / 芯片环境）使用原有 main() 初始化 + 死循环。
 * 2. 在 PC 上用 gcc 做单元测试时，仅在 __GNUC__ + UNIT_TEST 下，
 *    main() 作为测试入口，根据 TEST_MODULE 宏选择不同的测试模块。
 */
#if defined(__GNUC__) && defined(UNIT_TEST)
extern int main_test_ByPassValve(void);
extern int main_test_WaterFeedValve(void);
extern int main_test_CirculationPump(void);
extern int main_test_Comp(void);
extern int main_test_Fan(void);
extern int main_test_Stepmotor(void);
#endif


STRUCT_SYS	Sys;

/****************************************************************************************************
Function Name       :void Sys_Run_Event_Per100ms(void)
Description         :系统每运行100ms间隔事件
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
#if defined(UNIT_TEST)
/* 单元测试时提供存根函数 */
void Sys_Run_Func1_Per100ms(void) {}
void Sys_Run_Func2_Per100ms(void) {}
void Sys_Run_Func3_Per100ms(void) {}
void Sys_Run_Func4_Per100ms(void) {}
void Sys_Run_Func5_Per100ms(void) {}
void Sys_Run_Func1_Per10ms(void) {}
void Sys_Run_Func2_Per10ms(void) {}
void Sys_Run_Func3_Per10ms(void) {}
void Sys_Run_Func4_Per10ms(void) {}
void PhaseSequenceCheck(void) {}
void Sys_Run_Per2ms(void) {}
#endif

void	Sys_Run_Event_Per100ms(void)
{
    switch (Sys.u8_100ms_count)
    {
        #if		defined		SYS_RUN_EVENT01_PER100MS
        case	0:	SYS_RUN_EVENT01_PER100MS; break;	//系统100ms运行一次事件一
        #endif
    
        #if		defined		SYS_RUN_EVENT02_PER100MS
        case	1:	SYS_RUN_EVENT02_PER100MS; break;	//系统100ms运行一次事件二
        #endif
    
        #if		defined		SYS_RUN_EVENT03_PER100MS
        case	2:	SYS_RUN_EVENT03_PER100MS; break;	//系统100ms运行一次事件三
        #endif
    
        #if		defined		SYS_RUN_EVENT04_PER100MS
        case	3:	SYS_RUN_EVENT04_PER100MS; break;	//系统100ms运行一次事件四
        #endif
    
        #if		defined		SYS_RUN_EVENT05_PER100MS
        case	4:	SYS_RUN_EVENT05_PER100MS; break;	//系统100ms运行一次事件五
        #endif
    
        #if		defined		SYS_RUN_EVENT06_PER100MS
        case	5:	SYS_RUN_EVENT06_PER100MS; break;	//系统100ms运行一次事件六
        #endif
        
        #if		defined		SYS_RUN_EVENT07_PER100MS
        case	6:	SYS_RUN_EVENT07_PER100MS; break;	//系统100ms运行一次事件七
        #endif
        
        #if		defined		SYS_RUN_EVENT08_PER100MS
        case	7:	SYS_RUN_EVENT08_PER100MS; break;	//系统100ms运行一次事件八
        #endif
        
        #if		defined		SYS_RUN_EVENT09_PER100MS
        case	8:	SYS_RUN_EVENT09_PER100MS; break;	//系统100ms运行一次事件九
        #endif
    
        #if		defined		SYS_RUN_EVENT10_PER100MS
        case	9:	SYS_RUN_EVENT10_PER100MS; break;	//系统100ms运行一次事件十
        #endif
    
        default: break;
    }
                            
    if (++Sys.u8_100ms_count >= 10)
    {
        Sys.u8_100ms_count = 0;							
    }
}
/****************************************************************************************************
Function Name       :void Sys_Run_Event_Per10ms(void)
Description         :系统每运行10ms间隔事件
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Sys_Run_Event_Per10ms(void)
{
    switch (Sys.u8_10ms_count)
    {
        #if		defined		SYS_RUN_EVENT01_PER10MS
        case	0:	SYS_RUN_EVENT01_PER10MS; 	break;		//系统10ms运行一次事件一
        #endif
    
        #if		defined		SYS_RUN_EVENT02_PER10MS
        case	1:	SYS_RUN_EVENT02_PER10MS; 	break;		//系统10ms运行一次事件二
        #endif
    
        #if		defined		SYS_RUN_EVENT03_PER10MS
        case	2:	SYS_RUN_EVENT03_PER10MS; 	break;		//系统10ms运行一次事件三
        #endif
    
        #if		defined		SYS_RUN_EVENT04_PER10MS
        case	3:	SYS_RUN_EVENT04_PER10MS; 	break;		//系统10ms运行一次事件四			
        #endif
    
        case	4:	Sys_Run_Event_Per100ms();   break;		//系统每运行100ms间隔事件
    
        default: break;
    }

    if (++Sys.u8_10ms_count >= 5)
    {
        Sys.u8_10ms_count = 0;
    }
}
/****************************************************************************************************
Function Name       :void Sys_Run_Event_Per1ms(void)
Description         :系统每运行1ms间隔事件
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Sys_Run_Event_Per1ms(void)
{	
//	ECBM_MODBUS_RTU_TIMEOUT_RUN();		//modbus超时处理程序
	PhaseSequenceCheck();
    switch (Sys.u8_2ms_count)
    {
        #if		defined		SYS_RUN_EVENT_PER2MS
        case	0:	SYS_RUN_EVENT_PER2MS;			break;						//系统2ms运行一次事件
        #endif
    
        case	1:	Sys_Run_Event_Per10ms();	    break;
    
        default: break;
    }
    
    if (++Sys.u8_2ms_count >= 2)
    {
        Sys.u8_2ms_count = 0;					
    }
}
/****************************************************************************************************
Function Name       :void main(void)
Description         :主函数
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
int    main(void)
{	
#if defined(__GNUC__) && defined(UNIT_TEST)
/* PC / gcc 单元测试入口：根据 TEST_MODULE 选择测试模块 */
#ifdef TEST_MODULE
    #if TEST_MODULE == 1
        return main_test_ByPassValve();
    #elif TEST_MODULE == 2
        return main_test_WaterFeedValve();
    #elif TEST_MODULE == 3
        return main_test_CirculationPump();
    #elif TEST_MODULE == 4
        return main_test_Comp();
    #elif TEST_MODULE == 5
        return main_test_Fan();
    #elif TEST_MODULE == 6
        return main_test_Stepmotor();
    #else
        printf("错误: 未定义的测试模块编号 %d\n", TEST_MODULE);
        return 1;
    #endif
#else
    /* 默认运行旁通阀测试 */
    return main_test_ByPassValve();
#endif
#else
    /* 原有固件入口：芯片上运行正常程序 */
    Init_MCU_Gpio();					   //初始化MCU端口
	
    Init_MCU_System();					   //初始化MCU系统配置

    #if defined		UART3_lhh
	Uart3_Init();	
	#endif
//	RTT_Demo_Init();                       //lcx add
	Data_Init();
    while (1)
    {		
        if(Sys.f_1ms)
        {		
            Sys.f_1ms = 0;
               
            Sys_Run_Event_Per1ms();        //系统每运行1ms间隔事件
//            RTT_Demo_Run(); 			   //lcx add
        }				

		#if defined 	UART3_lhh
		if (1 == g_rx_finish_flag)
         {
           g_rx_finish_flag = 0;
            //g_rx_length = g_rx_count;
            g_rx_count = 0;
            app_Rec();
         }
		#endif
		ecbm_modbus_rtu_run();
    }
#endif           
}
