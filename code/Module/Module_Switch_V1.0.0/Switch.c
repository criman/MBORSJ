/*===================================================================================================
                        Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name        : Switch.c
Description         : C
Author              : Wuhaiming
Start Date          : 2022-03-22
Version             : V1.0
Revision History   1:
                   2:
===================================================================================================*/

#include    "main.h"

//-------------------------------------------------------------------------------------------//
enum
{
    #if defined 	SWITCH1_ENABLE
    C_SWITCH_SW1_SEL,
    #endif

    #if defined 	SWITCH2_ENABLE 
    C_SWITCH_SW2_SEL,
    #endif

    #if defined 	SWITCH3_ENABLE 
    C_SWITCH_SW3_SEL,
    #endif

    #if defined 	SWITCH4_ENABLE
    C_SWITCH_SW4_SEL,
    #endif

    #if defined 	SWITCH5_ENABLE
    C_SWITCH_SW5_SEL,
    #endif

    #if defined 	SWITCH6_ENABLE 
    C_SWITCH_SW6_SEL,
    #endif

    #if defined 	SWITCH7_ENABLE 
    C_SWITCH_SW7_SEL,
    #endif

    #if defined 	SWITCH8_ENABLE
    C_SWITCH_SW8_SEL,
    #endif	

    C_SWITCH_NUM,
};
//-------------------------------------------------------------------------------------------//
typedef		struct
{
    unsigned char		u8_disablecount[C_SWITCH_NUM];
    unsigned char		u8_enablecount[C_SWITCH_NUM];
	
}STRUCT_SWITCH;

typedef		union
{
    unsigned char		variable[C_SWITCH_NUM<<1];
    STRUCT_SWITCH		var;
}UNION_SWITCH;
//-------------------------------------------------------------------------------------------//
UNION_SWITCH			Switch;
STRUCT_SWITCHBYTE		SwitchFlag0;
#define					F_switch_sw1_new				SwitchFlag0.b0		// bit0	 
#define     			F_switch_sw2_new				SwitchFlag0.b1		// bit1	 
#define					F_switch_sw3_new				SwitchFlag0.b2		// bit2	 
#define					F_switch_sw4_new				SwitchFlag0.b3		// bit3  
#define					F_switch_sw5_new				SwitchFlag0.b4		// bit4	 
#define					F_switch_sw6_new				SwitchFlag0.b5		// bit5	 
#define     			F_switch_sw7_new				SwitchFlag0.b6		// bit6	 
#define					F_switch_sw8_new				SwitchFlag0.b7		// bit7	

STRUCT_SWITCHBYTE		SwitchFlag1;
//-------------------------------------------------------------------------------------------//

/****************************************************************************************************
Function Name       :void Module_Init_Switch(void)
Description         :初始化开关检测IO配置
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Module_Init_Switch(void)
{
//---------------------------------------------------------------------------------------------------//
    #if defined 	SWITCH1_ENABLE
    #if (Switch1SigValid == 0)		    //低电平有效

    P_Switch1_Hi();  
    P_Switch1_Input();	
	P_Switch1_Enpull();
	
    #else							    //高电平有效

    P_Switch1_Low();	
    P_Switch1_Input();
    P_Switch1_Dispull();
	
    #endif
    #endif
//---------------------------------------------------------------------------------------------------//
    #if defined 	SWITCH2_ENABLE
    #if (Switch2SigValid == 0)		    //低电平有效

    P_Switch2_Hi();
    P_Switch2_Input();
    P_Switch2_Enpull();
	
    #else								//高电平有效

    P_Switch2_Low();
    P_Switch2_Input();	
    P_Switch2_Dispull();
	
    #endif
    #endif	
//---------------------------------------------------------------------------------------------------//	
    #if defined 	SWITCH3_ENABLE
    #if (Switch3SigValid == 0)		    //低电平有效

    P_Switch3_Hi();
    P_Switch3_Input();
    P_Switch3_Enpull();
	
    #else								//高电平有效

    P_Switch3_Low();
    P_Switch3_Input();	
    P_Switch3_Dispull();
	
    #endif
    #endif	
//---------------------------------------------------------------------------------------------------//	
    #if defined 	SWITCH4_ENABLE
    #if (Switch4SigValid == 0)		    //低电平有效

    P_Switch4_Hi();
    P_Switch4_Input();
    P_Switch4_Enpull();
	
    #else								//高电平有效

    P_Switch4_Low();	
    P_Switch4_Input();
    P_Switch4_Dispull();
	
    #endif
    #endif	
//---------------------------------------------------------------------------------------------------//	
    #if defined 	SWITCH5_ENABLE
    #if (Switch5SigValid == 0)		    //低电平有效

    P_Switch5_Hi();
    P_Switch5_Input();
    P_Switch5_Enpull();
	
    #else								//高电平有效

    P_Switch5_Low();
    P_Switch5_Input();	
    P_Switch5_Dispull();
	
    #endif
    #endif	
//---------------------------------------------------------------------------------------------------//	
    #if defined 	SWITCH6_ENABLE
    #if (Switch6SigValid == 0)		    //低电平有效

    P_Switch6_Hi();
    P_Switch6_Input();
    P_Switch6_Enpull();
	
    #else								//高电平有效

    P_Switch6_Low();	
    P_Switch6_Input();
    P_Switch6_Dispull();
	
    #endif
    #endif	
//---------------------------------------------------------------------------------------------------//	
    #if defined 	SWITCH7_ENABLE
    #if (Switch7SigValid == 0)		    //低电平有效

    P_Switch7_Hi();
    P_Switch7_Input();
    P_Switch7_Enpull();
	
    #else								//高电平有效

    P_Switch7_Low();	
    P_Switch7_Input();
    P_Switch7_Dispull();
	
    #endif
    #endif	
//---------------------------------------------------------------------------------------------------//	
    #if defined 	SWITCH8_ENABLE
    #if (Switch8SigValid == 0)		    //低电平有效

    P_Switch8_Hi();
    P_Switch8_Input();
    P_Switch8_Enpull();
	
    #else								//高电平有效

    P_Switch8_Low();	
    P_Switch8_Input();
    P_Switch8_Dispull();
	
    #endif
    #endif	
//---------------------------------------------------------------------------------------------------//	
}
/****************************************************************************************************
Function Name       :unsigned char	Switch_Scan(unsigned char IoSwitch, unsigned char SignalValid)
Description         :检测开关电平
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
unsigned char	Switch_Scan(unsigned char IoSwitch, unsigned char SignalValid)
{
	
    unsigned char Switchsig_count;
    unsigned int	SwitchValueOutput;

    Switchsig_count = 0;
    SwitchValueOutput = 0;

    while (IoSwitch == SignalValid)		//io电平是有效电平
    {
        if (++Switchsig_count >= C_SWITCH_SCAN_NUM)
        {
            Switchsig_count = 0;
            SwitchValueOutput = 1;
        
            break;
        }	
    }	
    
    return	SwitchValueOutput;
}
/****************************************************************************************************
Function Name       :void Drv_Switch_Scan(void)
Description         :开关信号检测
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Drv_Switch_Scan(void)
{
    #if defined 	SWITCH1_ENABLE
    F_switch_sw1_new = Switch_Scan(Pin_switch1, Switch1SigValid);
    #endif

    #if defined 	SWITCH2_ENABLE
    F_switch_sw2_new = Switch_Scan(Pin_switch2, Switch2SigValid);
    #endif	

    #if defined 	SWITCH3_ENABLE
    F_switch_sw3_new = Switch_Scan(Pin_switch3, Switch3SigValid);
    #endif		

    #if defined 	SWITCH4_ENABLE
    F_switch_sw4_new = Switch_Scan(Pin_switch4, Switch4SigValid);
    #endif		

    #if defined 	SWITCH5_ENABLE
    F_switch_sw5_new = Switch_Scan(Pin_switch5, Switch5SigValid);
    #endif		

    #if defined 	SWITCH6_ENABLE
    F_switch_sw6_new = Switch_Scan(Pin_switch6, Switch6SigValid);
    #endif		
    
    #if defined 	SWITCH7_ENABLE
    F_switch_sw7_new = Switch_Scan(Pin_switch7, Switch7SigValid);
    #endif

    #if defined 	SWITCH8_ENABLE
    F_switch_sw8_new = Switch_Scan(Pin_switch8, Switch8SigValid);
    #endif
}
/****************************************************************************************************
Function Name       :unsigned char		Log_Switch_Fd(unsigned char f_sw_old, unsigned char f_sw_new, unsigned char u8_sel)
Description         :开关检测防抖处理
Input               :f_sw_old:防抖处理的状态, f_sw_new:IO信号状态, u8_sel：开关ID号
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
unsigned char		Log_Switch_Fd(unsigned char f_sw_old, unsigned char f_sw_new, unsigned char u8_sel)
{
    unsigned char		f_result;	

    if (f_sw_old == CF_DISABLE)														//防抖后状态为无效电平
    {
        if (f_sw_new == CF_DISABLE)													//新的状态为无效电平
        {
            Switch.var.u8_enablecount[u8_sel] = 0;
        }
        else																		//新的状态为低电平(例如有水，闭合等)
        {
            if (++Switch.var.u8_enablecount[u8_sel] >= C_SWITCH_ENABLE_FD)			//防抖
            {
                Switch.var.u8_enablecount[u8_sel] = 0;
                f_sw_old = CF_ENABLE; 												//状态更改为低电平(例如有水，闭合等)
            }
        }
    }
    else																			//如果低电平(例如有水，闭合等)
    {
        if (f_sw_new == CF_DISABLE)												    //新的状态为高电平(例如缺水，断开等)
        {
            if (++Switch.var.u8_disablecount[u8_sel] >= C_SWITCH_DISABLE_FD)	    //防抖
            {
                Switch.var.u8_disablecount[u8_sel] = 0;
                f_sw_old = CF_DISABLE; 											    //状态更改为高电平(例如缺水，断开等)
            }
        }
        else																	    //新的状态为低电平(例如有水，闭合等)
        {
            Switch.var.u8_disablecount[u8_sel] = 0;
        }	
    }

    f_result = f_sw_old;	

    return	f_result;	
}
/****************************************************************************************************
Function Name       :void App_Switch(void)
Description         :开关检测
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	App_Switch(void)
{
    Drv_Switch_Scan();							//IO电平检测开关状态

    #if defined 	SWITCH1_ENABLE				//开关1状态防抖
    F_switch_sw1_old = Log_Switch_Fd(F_switch_sw1_old, F_switch_sw1_new, C_SWITCH_SW1_SEL);
    #endif

    #if defined 	SWITCH2_ENABLE				//开关2状态防抖
    F_switch_sw2_old = Log_Switch_Fd(F_switch_sw2_old, F_switch_sw2_new, C_SWITCH_SW2_SEL);
    #endif	

    #if defined 	SWITCH3_ENABLE				//开关3状态防抖
    F_switch_sw3_old = Log_Switch_Fd(F_switch_sw3_old, F_switch_sw3_new, C_SWITCH_SW3_SEL);
    #endif	

    #if defined 	SWITCH4_ENABLE				//开关4状态防抖
    F_switch_sw4_old = Log_Switch_Fd(F_switch_sw4_old, F_switch_sw4_new, C_SWITCH_SW4_SEL);
    #endif	

    #if defined 	SWITCH5_ENABLE				//开关5状态防抖
    F_switch_sw5_old = Log_Switch_Fd(F_switch_sw5_old, F_switch_sw5_new, C_SWITCH_SW5_SEL);
    #endif	

    #if defined 	SWITCH6_ENABLE				//开关6状态防抖
    F_switch_sw6_old = Log_Switch_Fd(F_switch_sw6_old, F_switch_sw6_new, C_SWITCH_SW6_SEL);
    #endif

    #if defined 	SWITCH7_ENABLE				//开关7状态防抖
    F_switch_sw7_old = Log_Switch_Fd(F_switch_sw7_old, F_switch_sw7_new, C_SWITCH_SW7_SEL);
    #endif

    #if defined 	SWITCH8_ENABLE				//开关8状态防抖
    F_switch_sw8_old = Log_Switch_Fd(F_switch_sw8_old, F_switch_sw8_new, C_SWITCH_SW8_SEL);
    #endif

	
	
}
