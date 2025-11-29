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

#ifdef UNIT_TEST
extern int main_test_ByPassValve(void);
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
#ifdef UNIT_TEST
    return main_test_ByPassValve();
#else
    // TODO: restore firmware runtime loop when not running module tests
    return 0;
#endif
}
// {	
//     Init_MCU_Gpio();					   //初始化MCU端口
	
//     Init_MCU_System();					   //初始化MCU系统配置

//     #if defined		UART3_lhh
// 	Uart3_Init();	
// 	#endif
// //	RTT_Demo_Init();                       //lcx add
// 	Data_Init();
//     while (1)
//     {		
//         if(Sys.f_1ms)
//         {		
//             Sys.f_1ms = 0;
               
//             Sys_Run_Event_Per1ms();        //系统每运行1ms间隔事件
// //            RTT_Demo_Run(); 			   //lcx add
//         }				

// 		#if defined 	UART3_lhh
// 		if (1 == g_rx_finish_flag)
//          {
//            g_rx_finish_flag = 0;
//             //g_rx_length = g_rx_count;
//             g_rx_count = 0;
//             app_Rec();
//          }
// 		#endif
// 		ecbm_modbus_rtu_run();
//     }
// }
