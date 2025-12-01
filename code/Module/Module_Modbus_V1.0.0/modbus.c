#include "main.h"

/*--------------------------------------变量定义-----------------------------------*/
emu16  ecbm_modbus_rtu_crc           =0xFFFF;                    //初始化CRC变量各位为1。
emu8   ecbm_modbus_rtu_status        =ECBM_MODBUS_RTU_READY;     //状态机使用的变量。
emu8   ecbm_modbus_rtu_id            =ECBM_MODBUS_RTU_ID_ADRESS; //本机的设备ID。
emu8   ecbm_modbus_rtu_fun_code      =0;                         //功能码。
emu8   ecbm_modbus_rtu_fun_err_num   =0;                         //异常码。
emu16  ecbm_modbus_rtu_address       =0;                         //数据地址。
emu16  ecbm_modbus_rtu_data_count    =0;                         //数据/个数。
emu16  ecbm_modbus_rtu_crc_buf       =0;                         //CRC缓存。
emu16  ecbm_modbus_rtu_timeout       =0;                         //超时计算。
emu16  ecbm_modbus_rtu_uart_crc      =0xFFFF;                    //CRC计算缓存。
emu8   ecbm_modbus_rtu_cmd_count     =0;                         //指令缓存计数。
emu8   ecbm_modbus_rtu_broadcast_en  =0;                         //广播模式。
static uint16_t fg_MBText;

#if ECBM_MODBUS_RTU_BIT_BUF_EN
emu8   ecbm_modbus_rtu_bit_buf[ECBM_MODBUS_RTU_BIT_BUF_SIZE];        //比特线圈存放变量。
#endif
#if ECBM_MODBUS_RTU_REG_BUF_EN
emu16  ecbm_modbus_rtu_reg_buf[ECBM_MODBUS_RTU_REG_BUF_SIZE];        //寄存器存放变量。
#endif
#if ECBM_MODBUS_RTU_CMD10_EN
emu16  ecbm_modbus_rtu_cmd_buf[ECBM_MODBUS_RTU_BUF_SIZE];        //指令缓存。
#endif

void uart0_receive_callback(void){
    ecbm_modbus_rtu_receive();
}
void ecbm_modbus_rtu_set_data(U8 dat){
//    uart_char(1,dat);			//发送单字节
	U8_Uart0_TxBuf[Uart0.u8_TxNum++] = 	dat; 
}
U8   ecbm_modbus_rtu_get_data(void){
//    return SBUF;				//接收单字节
	return UART_RecByte(UART0);				//接收单字节	
}

/*-------------------------------------------------------
写比特数据函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_BIT_BUF_EN == 0
void ecbm_modbus_cmd_write_bit(emu16 addr,emu8 dat){
    addr=addr;
    dat=dat;
}
#endif
/*-------------------------------------------------------
读比特数据函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_BIT_BUF_EN == 0
void ecbm_modbus_cmd_read_bit(emu16 addr,emu8 * dat){
    addr=addr;
    *dat=1;
}
#endif
/*-------------------------------------------------------
写寄存器数据函数。
-------------------------------------------------------*/
//#if ECBM_MODBUS_RTU_REG_BUF_EN == 0
//void ecbm_modbus_cmd_write_reg(emu16 addr,emu16 dat){
//    addr=addr;
//    dat=dat;
//}
//#endif
/*-------------------------------------------------------
读寄存器函数。
-------------------------------------------------------*/
//#if ECBM_MODBUS_RTU_REG_BUF_EN == 0
//void ecbm_modbus_cmd_read_reg(emu16 addr,emu16 * dat){
//    addr=addr;
//    *dat=2;
//}
//#endif

/*-------------------------------------------------------
CRC16计算函数。
-------------------------------------------------------*/
void ecbm_modbus_rtu_crc16(emu8 buf){
    emu8 j;
    ecbm_modbus_rtu_crc^=buf;                                   //当前数据异或CRC低字节，在C51里可以直接处理。
    for(j=0;j<8;j++){                                           //计算每个字节的每一位。
        if(ecbm_modbus_rtu_crc&0x01){                           //判断右移前最低位是否为1。
            ecbm_modbus_rtu_crc=(ecbm_modbus_rtu_crc>>1)^0xA001;//如果为1则右移并异或表达式。
        }else{
            ecbm_modbus_rtu_crc>>=1;                            //否则直接右移一位。
        }           
    }
}
/*-------------------------------------------------------
检测功能码函数。
-------------------------------------------------------*/
emu8 ecbm_modbus_rtu_check_fun_num(emu8 fun_num){
    switch(fun_num){
/*-------------------------------------------------
0x02|读离散量输入  |物理离散量输入      |            |
----+-------------+------------------|             |
0x01|读线圈        |                  |             |
----+--------------|                 |   比特访问   |
0x05|写单个线圈     |内部比特或物理线圈 |             |
----+--------------|                 |             |
0x0F|写多个线圈     |                 |             |
----+--------------+-----------------+-------------|
0x04|读输入寄存器   |输入寄存器        |             |
----+--------------+-----------------|             |
0x03|读多个寄存器   |                 |             |
----+--------------|                 |             |
0x06|写单个寄存器   |                 |             |
----+--------------|                 |             |
0x10|写多个寄存器   |内部储存器或物理  |  16比特访问  |
----+--------------|输出寄存器        |             |
0x17|读/写多个寄存器|                 |             |
----+--------------|                 |             |
0x16|屏蔽写寄存器   |                 |             |
----+--------------|                 |             |
0x18|读FIFO队列     |                |             |
-------------------------------------------------*/
#if ECBM_MODBUS_RTU_CMD01_EN
        case 0x01://读线圈
#endif
#if ECBM_MODBUS_RTU_CMD02_EN
        case 0x02://读离散量输入
#endif
#if ECBM_MODBUS_RTU_CMD05_EN
        case 0x05://写单个线圈
#endif
#if ECBM_MODBUS_RTU_CMD04_EN
        case 0x04://读输入寄存器
#endif
#if ECBM_MODBUS_RTU_CMD03_EN
        case 0x03://读多个寄存器
#endif
#if ECBM_MODBUS_RTU_CMD06_EN
        case 0x06://写单个寄存器
#endif
#if ECBM_MODBUS_RTU_CMD10_EN
        case 0x10://写多个寄存器
#endif
#if ECBM_MODBUS_RTU_CMD_ALL_EN
        {return fun_num;}break;//支持的功能码就返回本身。
#endif
        default:{return 0x80+fun_num;}break;//不支持的功能码就返回0x80+功能码。
    }
}
/*-------------------------------------------------------
写比特数据函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_BIT_BUF_EN
void ecbm_modbus_cmd_write_bit(emu16 addr,emu8 dat){
    emu8 temp;
    temp=addr%8;
    if(dat){
        ecbm_modbus_rtu_bit_buf[addr/8]|= (0x01<<temp);
    }else{
        ecbm_modbus_rtu_bit_buf[addr/8]&=~(0x01<<temp);
    }
}
#endif
/*-------------------------------------------------------
读比特数据函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_BIT_BUF_EN
void ecbm_modbus_cmd_read_bit(emu16 addr,emu8 * dat){
    emu8 temp;
    temp=addr%8;
    if((ecbm_modbus_rtu_bit_buf[addr/8])&(0x01<<temp)){
        *dat=0x01;
    }else{
        *dat=0x00;
    }
}
#endif
#if 1
/*-------------------------------------------------------
写寄存器数据函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_REG_BUF_EN
void ecbm_modbus_cmd_write_reg(emu16 addr,emu16 dat){
	
    ecbm_modbus_rtu_reg_buf[addr]=dat;
//    if ((addr == CoolSetTemp) || (addr == HeatSetTemp))	//制冷制热设定温度解析
    if (addr == CoolSetTemp)//制冷制热设定温度解析
    {
		Tempr.u8_TempCSet = ecbm_modbus_rtu_reg_buf[addr]/10;		// 为下发温度*10
		if (SystemMode.f_Sleep)
		{
			Tempr.u8_TempCSetSleep = Tempr.u8_TempCSet;
		}
		
		//add code...//状态变化相关参数处理
		
//		if (addr == HeatSetTemp)
//		{
//			Tempr.u8_HeatCSet = Tempr.u8_TempCSet;
//		}
//		else //if (SystemMode.f_Cold == 1)
//		{
			Tempr.u8_ColdCSet = Tempr.u8_TempCSet;
//		}
		
		System.u32_SleepCount = 0;
		SystemMode.f_Force = 0;//强力模式关闭
    }
    else if (addr == WFV_Set)			//补水阀工作状态设置
    {
		if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 0))
		{
			WFV.f_Timing = 1;
		}
		else 
		{
			WFV.f_Timing = 0;
		}

		if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 1))
		{
			WFV.f_Auto = 1;
		}
		else 
		{
			WFV.f_Auto = 0;
		}

		if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 2))
		{
			WFV.f_ManualON = 1;
		}
		else 
		{
			WFV.f_ManualON = 0;
		}

		if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 3))
		{
			WFV.f_ManualOFF = 1;
		}
		else 
		{
			WFV.f_ManualOFF = 0;
		}
    }
    else if (addr == WokeMode)			//模式
    {
//		if      (ecbm_modbus_rtu_reg_buf[addr] == 0)		System.Mode = ENUM_SYSMODE_HEAT;		//制热
////		else if (CommDisp.Rx.Byte5.var.Mode == ENUM_MODE_HUMI)     		System.Mode = ENUM_SYSMODE_HUM;			//除湿
//		else if (ecbm_modbus_rtu_reg_buf[addr] == 3)	    System.Mode = ENUM_SYSMODE_FAN;  		//送风
////		else if (CommDisp.Rx.Byte5.var.Mode == ENUM_MODE_INTE)      	System.Mode = ENUM_SYSMODE_INTE;        //智能 		
//		else if (ecbm_modbus_rtu_reg_buf[addr] == 1)        System.Mode = ENUM_SYSMODE_COLD;		//制冷(默认)	
		if (ecbm_modbus_rtu_reg_buf[addr] == 1)        System.Mode = ENUM_SYSMODE_COLD;
		//add code...//工作模式状态变化相关参数处理

		
		Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_INIT;		//操作模式,重新计算温差区域
		Tempr.T1TSDeltaZoneBak = ENUM_TEMPDELTAZONE_INIT;	//操作模式,重新计算温差区域
		
		//模式标志重新判定
		SystemMode.f_Cold = 0;		
		SystemMode.f_Heat = 0;
		SystemMode.f_Fan = 0;
		SystemMode.f_Auto = 0;
		
		SystemMode.f_TempCEC = 0;							//操作模式,达温标志清除			
		SystemMode.f_Sleep = 0;								//操作模式,退出睡眠
		SystemMode.f_Force = 0;//强力模式关闭

		SystemMode.f_ConTemp = 0; //lcx add 20240704 转换模式进去，要清除达温停机。重新计时进入条件。
		
		if (System.Mode == ENUM_SYSMODE_HUM)
		{
			//进入除湿模式计算设定温度:    ST = T1 - 2
			if (T1.s8_Value < 18)
			{				
				Tempr.u8_HumiCSet = 16;	//最低
			}
			else if (T1.s8_Value > 34)
			{
				Tempr.u8_HumiCSet = 32;	//最高
			}
			else
			{
				Tempr.u8_HumiCSet = T1.s8_Value - 2;
			}
		}
		else
		{
			Tempr.u8_HumiCSet = 24;	//默认
		}
	}
    else if (addr == FlagCtrl)			//控制标志
    {
		if (IFCB(ecbm_modbus_rtu_reg_buf[addr],0))
		{
			DisplayBoardTurnOn(); 				//开机处理
		}
		else													
		{
			DisplayBoardTurnOff();      		//关机处理
		}

		if (IFCB(ecbm_modbus_rtu_reg_buf[addr],11))
		{
			Fan.Indoor.f_EnableMASet = 1;
		}
		else 
		{
			Fan.Indoor.f_EnableMASet = 0;
		}

		if (IFCB(ecbm_modbus_rtu_reg_buf[addr],12))
		{
			Fan.Indoor.f_FanType = 1;
		}
		else 
		{
			Fan.Indoor.f_FanType = 0;
		}
    }
    else if (addr == EEVSet)				//手动设定电子膨胀阀开度			
    {
		StepMotor.var.u16_agtarget = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P1)					
    {
		FtyPara.u16P1 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P2)					
    {
		FtyPara.u16P2 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P3)					
    {
		FtyPara.u16P3 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P4)					
    {
		FtyPara.u16P4 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P5)					
    {
		FtyPara.u16P5 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P6)					
    {
		FtyPara.u16P6 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P7)					
    {
		FtyPara.u16P7 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P8)					
    {
		FtyPara.u16P8 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P9)					
    {
		FtyPara.u16P9 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P10)					
    {
		FtyPara.u16P10 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P11)					
    {
		FtyPara.u16P11 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P12)					
    {
		FtyPara.u16P12 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P13)					
    {
		FtyPara.u16P13 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P14)					
    {
		FtyPara.u16P14 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P15)					
    {
		FtyPara.s16P15 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P16)					
    {
		FtyPara.s16P16 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P17)					
    {
		FtyPara.s16P17 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P18)					
    {
		FtyPara.s16P18 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P19)					
    {
		FtyPara.s16P19 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P20)					
    {
		FtyPara.s16P20 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P21)					
    {
		FtyPara.s16P21 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P22)					
    {
		FtyPara.s16P22 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P23)					
    {
		FtyPara.s16P24 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P24)					
    {
		FtyPara.s16P24 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P25)					
    {
		FtyPara.s16P25 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P26)					
    {
		FtyPara.s16P26 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P27)					
    {
		FtyPara.s16P27 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P28)					
    {
		FtyPara.u16P28 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == P29)					
    {
		FtyPara.u16P29 = ecbm_modbus_rtu_reg_buf[addr];
    }
	else if (addr == F1)					
    {
		FtyPara.u16F1 = ecbm_modbus_rtu_reg_buf[addr];
    }
	else if (addr == F2)				
    {
		FtyPara.u16F2 = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == F3)					
    {
		FtyPara.u16F3 = ecbm_modbus_rtu_reg_buf[addr];
    }
	else if (addr == F4)				
    {
		FtyPara.s16F4 = ecbm_modbus_rtu_reg_buf[addr];
    }
    
	else if (addr == L1)					
    {
		FtyPara.u16L1 = ecbm_modbus_rtu_reg_buf[addr];
    }
	else if (addr == L2)				
    {
		FtyPara.u16L2 = ecbm_modbus_rtu_reg_buf[addr];
    }

    
//    0x100~
    else if (addr == Test_Enable)				//手动设定风速			
    {
		fg_MBText = ecbm_modbus_rtu_reg_buf[addr];
    }
    if (fg_MBText == 12345)
    {
	    if (addr == DefrostBits)				//手动设定风速			
	    {
			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 0))
			{
				Defrost.f_Enable = 1;
			}
			else 
			{
				Defrost.f_Enable = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 1))
			{
				Defrost.f_Quit = 1;
			}
			else 
			{
				Defrost.f_Quit = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 2))
			{
				Defrost.f_T30Found = 1;
			}
			else 
			{
				Defrost.f_T30Found = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 3))
			{
				Defrost.f_CompHasRun = 1;
			}
			else 
			{
				Defrost.f_CompHasRun = 0;
			}
	    }
	    if (addr == DF_s16_T30Mul10)
	    {
			Defrost.s16_T30Mul10 = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_DefCase3_Count)
	    {
			Defrost.u16_DefCase3_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_DefQCase2_Count)
	    {
			Defrost.u16_DefQCase2_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_Defrosting_Count)
	    {
			Defrost.u16_Defrosting_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_FindT30_Count)
	    {
			Defrost.u16_FindT30_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_HeatRun_Count)
	    {
			Defrost.u16_HeatRun_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u8_Step)
	    {
			Defrost.u8_Step = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_Step_Delay)
	    {
			Defrost.u16_Step_Delay = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == RLY_Ctrl)
	    {
			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 0))
			{
				Comp.f_ForceDrvOn = 1;
			}
			else 
			{
				Comp.f_ForceDrvOn = 0;
			}
			
			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 1))
			{
				CirculationPump.f_ForceDrvOn = 1;
			}
			else 
			{
				CirculationPump.f_ForceDrvOn = 0;
			}
			
			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 2))
			{
				Fan.Outdoor.f_ForceDrvOn = 1;
			}
			else 
			{
				Fan.Outdoor.f_ForceDrvOn = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 3))
			{
				FourWay.f_ForceDrvOn = 1;
			}
			else 
			{
				FourWay.f_ForceDrvOn = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 4))
			{
				Crank.f_ForceDrvOn = 1;
			}
			else 
			{
				Crank.f_ForceDrvOn = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 5))
			{
				WFV.f_ForceDrvOn = 1;
			}
			else 
			{
				WFV.f_ForceDrvOn = 0;
			}
	    }
    }
}
#endif
/*-------------------------------------------------------
读寄存器函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_REG_BUF_EN
void ecbm_modbus_cmd_read_reg(emu16 addr,emu16 * dat){
	ecbm_modbus_rtu_reg_buf[addr] = 0;
	if (addr == CoolSetTemp)	//制冷制热设定温度解析
	{
		ecbm_modbus_rtu_reg_buf[addr] = (U16)Tempr.u8_ColdCSet * 10;	//实际温度*10
		if (System.Mode == ENUM_SYSMODE_COLD)
		{
			Tempr.u8_TempCSet = Tempr.u8_ColdCSet;
		}
	}
//	else if (addr == HeatSetTemp)
//	{
//		ecbm_modbus_rtu_reg_buf[addr] = (U16)Tempr.u8_HeatCSet * 10;	//实际温度*10
//		if (System.Mode == ENUM_SYSMODE_HEAT)
//		{
//			Tempr.u8_TempCSet = Tempr.u8_HeatCSet;
//		}
//	}
	else if (addr == WFV_Set)			//补水阀工作状态设置
    {
		if (WFV.f_Timing)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}

		if (WFV.f_Auto)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}

		if (WFV.f_ManualON)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}

		if (WFV.f_ManualOFF)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}
    }
	else if (addr == WokeMode)			//模式  #test 新协议待改		
	{
		ecbm_modbus_rtu_reg_buf[addr] = 1;		//只有制冷模式
//		if (System.Mode == ENUM_SYSMODE_HEAT)
//		{
//			ecbm_modbus_rtu_reg_buf[addr] = 0;
//		}
//		else if (System.Mode == ENUM_SYSMODE_COLD)		
//		{
//			ecbm_modbus_rtu_reg_buf[addr] = 1;
//		}
//		else	//if (System.Mode == ENUM_SYSMODE_FAN)
//		{
//			ecbm_modbus_rtu_reg_buf[addr] = 3;
//		}	 
	}
	else if (addr == FlagCtrl)			//开关机
	{
		if (System.Enum_Status == ENUM_STATUS_ON)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
	}
	else if (addr == FlagWork)			//工作标志
	{
	
	}
	else if (addr == FlagOutPut1)			//输出标志1
	{
		if (Comp.f_DrvOn)					//压缩机
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}

		if (WFV.f_DrvOn)					//补水阀
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}

		if (CirculationPump.f_DrvOn)		//循环泵
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}

		if (SV.f_DrvOn)						//喷液阀
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}

		if (FourWay.f_DrvOn)						//四通阀
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);
		}
		
		if (Fan.Outdoor.f_DrvOn)			//外风机	
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
	}
	else if (addr == FlagOutPut2)			//输出标志2
	{
		if (HighPress)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}

		if (LowPress)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}

		if (WaterFlow)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}

		if (HighWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}

		if (MidWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);
		}

		if (LowWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}	
	}
	else if (addr == FlagOutPut3)			//输出标志3
	{

	}

	else if (addr == FlagErr1)			//故障标志1
	{
		if (T5I.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		
		if (T5O.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}
		if (T4.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}
		
		if (TH.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}
		
		if (Tp.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);
		}
		
		if (T3.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}

		if (T5.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 6);
		}

		
	}
	else if (addr == FlagErr2)			//故障标志2
	{
		if (Protect.f_HighPress)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);		//Bit0: 高压故障保护
		}
		
		if (Protect.f_LowPress)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);		//Bit1: 低压故障保护
		}
		
		if (Protect.f_HighWaterLevelErr)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);		//Bit2: 高水位开关故障
		}
		
		if (Protect.f_MidWaterLevelErr)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);		//Bit3: 中水位开关故障
		}
		
		if (Protect.f_LowWaterLevelErr)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);		//Bit4: 低水位开关故障
		}
		
		if (Protect.f_WaterFlow)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);		//Bit5: 水流开关故障
		}
		
		// Bit6: 预留
		// Bit7: 预留
	}
	else if (addr == FlagErr3)			//故障标志3
	{

	}
	else if (addr == FlagErr4)			//故障标志4
	{
		if (Protect.f_Tp)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}	
	}
	else if (addr == FlagErr5)			//故障标志5
	{
		
	}
	else if (addr == FlagErr6)			//故障标志6
	{
	
	}
	else if (addr == T4Temp)			//环境温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T4.s16_ValueMul10; 
	}
	else if (addr == TpTemp)			//排气温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = Tp.s16_ValueMul10; 
	}
	else if (addr == T3Temp)			//外盘管温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T3.s16_ValueMul10; 
	}
	else if (addr == T5Temp)			//水箱温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T5.s16_ValueMul10; 
	}
	else if (addr == T5ITemp)			//进水温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T5I.s16_ValueMul10; 
	}
	else if (addr == T5OTemp)			//出水温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T5O.s16_ValueMul10; 
	}
	else if (addr == THTemp)			//回气温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = TH.s16_ValueMul10; 
	}
	else if (addr == SoftwareVersion)
	{
		ecbm_modbus_rtu_reg_buf[addr] = MainSoftWareVersion;
	}
	else if (addr == EEVSet)				//手动设定电子膨胀阀开度			
    {
		ecbm_modbus_rtu_reg_buf[addr] = StepMotor.var.u16_agtarget;
    }
    else if (addr == P1)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P1;
    }
    else if (addr == P2)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P2;
    }
    else if (addr == P3)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P3;
    }
    else if (addr == P4)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P4;
    }
    else if (addr == P5)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P5;
    }
    else if (addr == P6)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P6;
    }
    else if (addr == P7)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P7;
    }
    else if (addr == P8)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P8;
    }
    else if (addr == P9)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P9;
    }
    else if (addr == P10)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P10;
    }
    else if (addr == P11)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P11;
    }
    else if (addr == P12)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P12;
    }
    else if (addr == P13)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P13;
    }
    else if (addr == P14)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P14;
    }
    else if (addr == P15)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P15;
    }
    else if (addr == P16)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P16;
    }
    else if (addr == P17)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P17;
    }
    else if (addr == P18)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P18;
    }
    else if (addr == P19)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P19;
    }
    else if (addr == P20)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P20;
    }
    else if (addr == P21)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P21;
    }
    else if (addr == P22)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P22;
    }
    else if (addr == P23)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P24;
    }
    else if (addr == P24)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P24;
    }
    else if (addr == P25)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P25;
    }
    else if (addr == P26)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P26;
    }
    else if (addr == P27)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16P27;
    }
    else if (addr == P28)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P28;
    }
    else if (addr == P29)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16P29;
    }
    
    else if (addr == F1)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16F1;
    }
	else if (addr == F2)				
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16F2;
    }
    else if (addr == F3)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16F3;
    }
	else if (addr == F4)				
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.s16F4;
    }

    else if (addr == L1)					
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16L1;
    }
	else if (addr == L2)				
    {
		ecbm_modbus_rtu_reg_buf[addr] = FtyPara.u16L2;
    }

	//0x100~0x1FF
	else if (addr == Test_Enable)
    {
		ecbm_modbus_rtu_reg_buf[addr] = fg_MBText;
    }
	else if (addr == DefrostBits)				//手动设定风速			
    {
		if (Defrost.f_Enable)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		if (Defrost.f_Quit)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}
		if (Defrost.f_T30Found)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}
		if (Defrost.f_CompHasRun)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}
    }
    else if (addr == DF_s16_T30Mul10)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.s16_T30Mul10;
    }
    else if (addr == DF_u16_DefCase3_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_DefCase3_Count;
    }
    else if (addr == DF_u16_DefQCase2_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_DefQCase2_Count;
    }
    else if (addr == DF_u16_Defrosting_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_Defrosting_Count;
    }
    else if (addr == DF_u16_FindT30_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_FindT30_Count;
    }
    else if (addr == DF_u16_HeatRun_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_HeatRun_Count;
    }
    else if (addr == DF_u8_Step)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u8_Step;
    }
    else if (addr == DF_u16_Step_Delay)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_Step_Delay;
    }
    else if (addr == HP_Err_Cnt)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Protect.u16_HpErrCnt;
    }
    else if (addr == LP_Err_Cnt)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Protect.u16_LpErrCnt;
    }
    else if (addr == RLY_Ctrl)
    {
		if (Comp.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		
		if (CirculationPump.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}

		if (Fan.Outdoor.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}

		if (FourWay.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}

		if (Crank.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);
		}

		if (WFV.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
    }
    else if (addr == Input_Sta)
    {
		if (LowPress)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		if (HighPress)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}
		if (WaterFlow)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}
		if (LowWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}
		if (MidWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);
		}
		if (HighWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
    }
	else if (addr == EEV_SuperHeatAvg)
    {
		ecbm_modbus_rtu_reg_buf[addr] = StepMotor.var.s16_SuperHeatAvg;
    } 
    else if (addr == EEV_DeltaStep)
    {
		ecbm_modbus_rtu_reg_buf[addr] = StepMotor.var.s16_EEVDeltaStep;
    } 
    
    *dat=ecbm_modbus_rtu_reg_buf[addr];
}
#endif
#else 
/*-------------------------------------------------------
写寄存器数据函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_REG_BUF_EN
void ecbm_modbus_cmd_write_reg(emu16 addr,emu16 dat){
	
    ecbm_modbus_rtu_reg_buf[addr]=dat;
    if ((addr == CoolSetTemp) || (addr == HeatSetTemp))	//制冷制热设定温度解析
    {
		Tempr.u8_TempCSet = ecbm_modbus_rtu_reg_buf[addr]/20;		// /5为下发温度*2
		if (SystemMode.f_Sleep)
		{
			Tempr.u8_TempCSetSleep = Tempr.u8_TempCSet;
		}
		
		//add code...//状态变化相关参数处理
		
		if (addr == HeatSetTemp)
		{
			Tempr.u8_HeatCSet = Tempr.u8_TempCSet;
		}
		else //if (SystemMode.f_Cold == 1)
		{
			Tempr.u8_ColdCSet = Tempr.u8_TempCSet;
		}
		
		System.u32_SleepCount = 0;
		SystemMode.f_Force = 0;//强力模式关闭
    }
    else if (addr == FanSet)			//风速
    {
		switch (ecbm_modbus_rtu_reg_buf[addr])
		{
			case	ENUM_FANSPEED_AUTO	 : Fan.Mode = ENUM_FANMODE_AUTO; break;			//自动风
			case	ENUM_FANSPEED_LOW    : Fan.Mode = ENUM_FANMODE_LOW;  break;			//低风
			case	ENUM_FANSPEED_MED    : Fan.Mode = ENUM_FANMODE_MED;  break;			//中风
			case	ENUM_FANSPEED_HIGH   : Fan.Mode = ENUM_FANMODE_HIGH; break;			//高风
			default: break;
		}	

		//add code...//风速模式变化相关参数处理
		SystemMode.f_TempCEC = 0;					//操作风速,达温标志清除
		SystemMode.f_Sleep = 0;						//操作风速,退出睡眠
		Fan.u2_AutoInitFdCount = 0;
		SystemMode.f_Force = 0;//强力模式关闭
    }
    else if (addr == WokeMode)			//模式
    {
		if      (ecbm_modbus_rtu_reg_buf[addr] == 0)		System.Mode = ENUM_SYSMODE_HEAT;		//制热
//		else if (CommDisp.Rx.Byte5.var.Mode == ENUM_MODE_HUMI)     		System.Mode = ENUM_SYSMODE_HUM;			//除湿
		else if (ecbm_modbus_rtu_reg_buf[addr] == 3)	    System.Mode = ENUM_SYSMODE_FAN;  		//送风
//		else if (CommDisp.Rx.Byte5.var.Mode == ENUM_MODE_INTE)      	System.Mode = ENUM_SYSMODE_INTE;        //智能 		
		else if (ecbm_modbus_rtu_reg_buf[addr] == 1)        System.Mode = ENUM_SYSMODE_COLD;		//制冷(默认)	
		
		//add code...//工作模式状态变化相关参数处理

		
		Tempr.T1TSDeltaZone = ENUM_TEMPDELTAZONE_INIT;		//操作模式,重新计算温差区域
		Tempr.T1TSDeltaZoneBak = ENUM_TEMPDELTAZONE_INIT;	//操作模式,重新计算温差区域
		
		//模式标志重新判定
		SystemMode.f_Cold = 0;		
		SystemMode.f_Heat = 0;
		SystemMode.f_Fan = 0;
		SystemMode.f_Auto = 0;
		
		SystemMode.f_TempCEC = 0;							//操作模式,达温标志清除			
		SystemMode.f_Sleep = 0;								//操作模式,退出睡眠
		SystemMode.f_Force = 0;//强力模式关闭

		SystemMode.f_ConTemp = 0; //lcx add 20240704 转换模式进去，要清除达温停机。重新计时进入条件。
		
		if (System.Mode == ENUM_SYSMODE_HUM)
		{
			//进入除湿模式计算设定温度:    ST = T1 - 2
			if (T1.s8_Value < 18)
			{				
				Tempr.u8_HumiCSet = 16;	//最低
			}
			else if (T1.s8_Value > 34)
			{
				Tempr.u8_HumiCSet = 32;	//最高
			}
			else
			{
				Tempr.u8_HumiCSet = T1.s8_Value - 2;
			}
		}
		else
		{
			Tempr.u8_HumiCSet = 24;	//默认
		}
	}
    else if (addr == FlagCtrl)			//控制标志
    {
		if (IFCB(ecbm_modbus_rtu_reg_buf[addr],0))
		{
			DisplayBoardTurnOn(); 				//开机处理
		}
		else													
		{
			DisplayBoardTurnOff();      		//关机处理
		}

		if (IFCB(ecbm_modbus_rtu_reg_buf[addr],11))
		{
			Fan.Indoor.f_EnableMASet = 1;
		}
		else 
		{
			Fan.Indoor.f_EnableMASet = 0;
		}

		if (IFCB(ecbm_modbus_rtu_reg_buf[addr],12))
		{
			Fan.Indoor.f_FanType = 1;
		}
		else 
		{
			Fan.Indoor.f_FanType = 0;
		}
    }
    else if (addr == DefrostDutySet)			//除霜周期设定			
    {

    }
    else if (addr == TimeDefrostMaxSet)			//最长除霜时间设定			
    {

    }
    else if (addr == TempDefrostOnSet)			//除霜进入温设定			
    {

    }
    else if (addr == TempDiffT3T4DefrostOn)		//可进入除霜环境温度与盘管温差			
    {

    }
    else if (addr == TimeHPProt)			//压机保护时间min			
    {

    }
    else if (addr == TimeFanDelayOFF)			//风机延时关闭时间s			
    {

    }
    else if (addr == TimeFanAheadON)			//风机提前打开时间s			
    {

    }
    else if (addr == TempSVON)					//喷液阀开温度			
    {
    	if ((ecbm_modbus_rtu_reg_buf[addr] >= 90)
    	|| (ecbm_modbus_rtu_reg_buf[addr] <= 100))
    	{
			SV.s16_OnTemp = ecbm_modbus_rtu_reg_buf[addr]*10;
    	}
    }
    else if (addr == TempSVOFF)					//喷液阀关温度			
    {
		if ((ecbm_modbus_rtu_reg_buf[addr] >= 80)
    	|| (ecbm_modbus_rtu_reg_buf[addr] <= 95))
    	{
			SV.s16_OffTemp = ecbm_modbus_rtu_reg_buf[addr]*10;
    	}
    }
    else if (addr == OverCurProt)				//电流报警设置值			
    {
		Protect.s16_ErrCur = ecbm_modbus_rtu_reg_buf[addr]*10;
    }
    else if (addr == Lock4G)					//4G锁机标志			
    {

    }
    else if (addr == FanSpMASet)				//手动设定风速			
    {
		Fan.Indoor.u16_MATargetRPM = ecbm_modbus_rtu_reg_buf[addr];
    }
    else if (addr == EEVSet)				//手动设定电子膨胀阀开度			
    {
		StepMotor.var.u16_agtarget = ecbm_modbus_rtu_reg_buf[addr];
    }
    
	

    else if (addr == Test_Enable)				//手动设定风速			
    {
		fg_MBText = ecbm_modbus_rtu_reg_buf[addr];
    }
    if (fg_MBText == 12345)
    {
	    if (addr == DefrostBits)				//手动设定风速			
	    {
			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 0))
			{
				Defrost.f_Enable = 1;
			}
			else 
			{
				Defrost.f_Enable = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 1))
			{
				Defrost.f_Quit = 1;
			}
			else 
			{
				Defrost.f_Quit = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 2))
			{
				Defrost.f_T30Found = 1;
			}
			else 
			{
				Defrost.f_T30Found = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 3))
			{
				Defrost.f_CompHasRun = 1;
			}
			else 
			{
				Defrost.f_CompHasRun = 0;
			}
	    }
	    if (addr == DF_s16_T30Mul10)
	    {
			Defrost.s16_T30Mul10 = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_DefCase3_Count)
	    {
			Defrost.u16_DefCase3_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_DefQCase2_Count)
	    {
			Defrost.u16_DefQCase2_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_Defrosting_Count)
	    {
			Defrost.u16_Defrosting_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_FindT30_Count)
	    {
			Defrost.u16_FindT30_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_HeatRun_Count)
	    {
			Defrost.u16_HeatRun_Count = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u8_Step)
	    {
			Defrost.u8_Step = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == DF_u16_Step_Delay)
	    {
			Defrost.u16_Step_Delay = ecbm_modbus_rtu_reg_buf[addr];
	    }
	    else if (addr == RLY_Ctrl)
	    {
			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 0))
			{
				Comp.f_ForceDrvOn = 1;
			}
			else 
			{
				Comp.f_ForceDrvOn = 0;
			}
			
			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 1))
			{
				CirculationPump.f_ForceDrvOn = 1;
			}
			else 
			{
				CirculationPump.f_ForceDrvOn = 0;
			}
			
			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 2))
			{
				Fan.Outdoor.f_ForceDrvOn = 1;
			}
			else 
			{
				Fan.Outdoor.f_ForceDrvOn = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 3))
			{
				FourWay.f_ForceDrvOn = 1;
			}
			else 
			{
				FourWay.f_ForceDrvOn = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 4))
			{
				Crank.f_ForceDrvOn = 1;
			}
			else 
			{
				Crank.f_ForceDrvOn = 0;
			}

			if (IFCB(ecbm_modbus_rtu_reg_buf[addr], 5))
			{
				WFV.f_ForceDrvOn = 1;
			}
			else 
			{
				WFV.f_ForceDrvOn = 0;
			}
	    }
    }
}
#endif
/*-------------------------------------------------------
读寄存器函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_REG_BUF_EN
void ecbm_modbus_cmd_read_reg(emu16 addr,emu16 * dat){
	ecbm_modbus_rtu_reg_buf[addr] = 0;
	if (addr == CoolSetTemp)	//制冷制热设定温度解析
	{
		ecbm_modbus_rtu_reg_buf[addr] = (U16)Tempr.u8_ColdCSet * 20;	//实际温度*2
		if (System.Mode == ENUM_SYSMODE_COLD)
		{
			Tempr.u8_TempCSet = Tempr.u8_ColdCSet;
		}
	}
	else if (addr == HeatSetTemp)
	{
		ecbm_modbus_rtu_reg_buf[addr] = (U16)Tempr.u8_HeatCSet * 20;	//实际温度*2
		if (System.Mode == ENUM_SYSMODE_HEAT)
		{
			Tempr.u8_TempCSet = Tempr.u8_HeatCSet;
		}
	}
	else if (addr == FanSet)			//风速
	{
		if (Fan.Mode == ENUM_FANMODE_AUTO)
		{
			ecbm_modbus_rtu_reg_buf[addr] = 0;
		}
		else if (Fan.Mode == ENUM_FANMODE_HIGH)
		{
			ecbm_modbus_rtu_reg_buf[addr] = 3;
		}
		else if (Fan.Mode == ENUM_FANMODE_MED)
		{
			ecbm_modbus_rtu_reg_buf[addr] = 2;
		}
		else 	//低风
		{
			ecbm_modbus_rtu_reg_buf[addr] = 1;
		}
		
	}
	else if (addr == WokeMode)			//模式  #test 新协议待改		
	{
		if (System.Mode == ENUM_SYSMODE_HEAT)
		{
			ecbm_modbus_rtu_reg_buf[addr] = 0;
		}
		else if (System.Mode == ENUM_SYSMODE_COLD)		
		{
			ecbm_modbus_rtu_reg_buf[addr] = 1;
		}
		else	//if (System.Mode == ENUM_SYSMODE_FAN)
		{
			ecbm_modbus_rtu_reg_buf[addr] = 3;
		}	 
	}
	else if (addr == FlagCtrl)			//开关机
	{
		if (System.Enum_Status == ENUM_STATUS_ON)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}

		//Bit11：0风机自动风速/1风机手动风速
		if (Fan.Indoor.f_EnableMASet)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 12);
		}
		//Bit12：0风机继电器输出/1风机板输出
		if (F_switch_sw5_old)	//(Fan.Indoor.f_FanType)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 12);
		}
	}
	else if (addr == FlagWork)			//工作标志
	{
		if (Defrost.f_Enable)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}		
	}
	else if (addr == FlagOutPut1)			//输出标志1
	{
		if (Comp.f_DrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		
		if (Fan.Outdoor.f_DrvOn)		
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
	}
	else if (addr == FlagOutPut3)			//输出标志3
	{
		if (SV.f_DrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
	}
#if 1 //#test 屏蔽故障
	else if (addr == FlagErr1)			//故障标志1
	{
		if (T3.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		
		if (T4.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}

		if (Protect.f_HighPress)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
		
		if (Protect.f_LowPress)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 6);
		}
	}
	else if (addr == FlagErr2)			//故障标志2
	{
		if (Protect.f_HighPress)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);		//Bit0: 高压故障保护
		}
		
		if (Protect.f_LowPress)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);		//Bit1: 低压故障保护
		}
		
		if (Protect.f_HighWaterLevelErr)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);		//Bit2: 高水位开关故障
		}
		
		if (Protect.f_MidWaterLevelErr)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);		//Bit3: 中水位开关故障
		}
		
		if (Protect.f_LowWaterLevelErr)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);		//Bit4: 低水位开关故障
		}
		
		if (Protect.f_WaterFlow)
		{	
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);		//Bit5: 水流开关故障
		}
		
		// Bit6: 预留
		// Bit7: 预留
	}
	else if (addr == FlagErr3)			//故障标志3
	{
#if defined		UART2_ENABLE
		if (F_uart2_CommErr)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
#endif 
		if (Fan.Indoor.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}
		
		if (Tp.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 6);
		}
	}
	else if (addr == FlagErr4)			//故障标志4
	{
		if (Protect.f_Tp)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}

		if (Protect.f_T2Cold)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
	}
	else if (addr == FlagErr5)			//故障标志5
	{
		if (Protect.PhaseSeqStatus != ENUM_PROSTATUS_NORMAL)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}
	}
	else if (addr == FlagErr6)			//故障标志6
	{
		if (T1.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}

		if (T2.f_Error)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}
	}
#endif
	else if (addr == FlagInFan)			//室内风机输出标志
	{
		ecbm_modbus_rtu_reg_buf[addr] = Fan.Indoor.u16_TargetRPM; 
	}
	else if (addr == T4Temp)			//环境温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T4.s16_ValueMul10; 
	}
	else if (addr == TpTemp)			//排气温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = Tp.s16_ValueMul10; 
	}
	else if (addr == T3Temp)			//外盘管温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T3.s16_ValueMul10; 
	}
	else if (addr == T1Temp)			//进风温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T5I.s16_ValueMul10; 
	}
	else if (addr == T2Temp)			//内盘管温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T5O.s16_ValueMul10; 
	}
	else if (addr == T5Temp)			//水箱温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T5.s16_ValueMul10; 
	}
	else if (addr == T5ITemp)			//进水温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T5I.s16_ValueMul10; 
	}
	else if (addr == T5OTemp)			//出水温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = T5O.s16_ValueMul10; 
	}
	else if (addr == THTemp)			//回气温度
	{
		ecbm_modbus_rtu_reg_buf[addr] = TH.s16_ValueMul10; 
	}
	else if (addr == Current)			//电流值
	{
		ecbm_modbus_rtu_reg_buf[addr] = Cur.s16_ValueMul10; 
	}
	else if (addr == SoftwareVersion)
	{
		ecbm_modbus_rtu_reg_buf[addr] = MainSoftWareVersion;
	}
	else if (addr == DefrostDutySet)			//除霜周期设定			
    {

    }
    else if (addr == TimeDefrostMaxSet)			//最长除霜时间设定			
    {

    }
    else if (addr == TempDefrostOnSet)			//除霜进入温设定			
    {

    }
    else if (addr == TempDiffT3T4DefrostOn)		//可进入除霜环境温度与盘管温差			
    {

    }
    else if (addr == TimeHPProt)				//压机保护时间min			
    {

    }
    else if (addr == TimeFanDelayOFF)			//风机延时关闭时间s			
    {

    }
    else if (addr == TimeFanAheadON)			//风机提前打开时间s			
    {

    }
    else if (addr == TempSVON)					//喷液阀开温度			
    {
		ecbm_modbus_rtu_reg_buf[addr] = SV.s16_OnTemp /10;
    }
    else if (addr == TempSVOFF)					//喷液阀关温度			
    {
		ecbm_modbus_rtu_reg_buf[addr] = SV.s16_OffTemp /10;
    }
    else if (addr == OverCurProt)				//电流报警设置值			
    {
		ecbm_modbus_rtu_reg_buf[addr] = Protect.s16_ErrCur /10;
    }
    else if (addr == Lock4G)					//4G锁机标志			
    {

    }
    else if (addr == FanSpMASet)				//手动设定风速			
    {
		ecbm_modbus_rtu_reg_buf[addr] = Fan.Indoor.u16_MATargetRPM;
    }
	else if (addr == EEVSet)				//手动设定电子膨胀阀开度			
    {
		ecbm_modbus_rtu_reg_buf[addr] = StepMotor.var.u16_agtarget;
    }


	//0x100~0x1FF
	else if (addr == Test_Enable)
    {
		ecbm_modbus_rtu_reg_buf[addr] = fg_MBText;
    }
	else if (addr == DefrostBits)				//手动设定风速			
    {
		if (Defrost.f_Enable)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		if (Defrost.f_Quit)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}
		if (Defrost.f_T30Found)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}
		if (Defrost.f_CompHasRun)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}
    }
    else if (addr == DF_s16_T30Mul10)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.s16_T30Mul10;
    }
    else if (addr == DF_u16_DefCase3_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_DefCase3_Count;
    }
    else if (addr == DF_u16_DefQCase2_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_DefQCase2_Count;
    }
    else if (addr == DF_u16_Defrosting_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_Defrosting_Count;
    }
    else if (addr == DF_u16_FindT30_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_FindT30_Count;
    }
    else if (addr == DF_u16_HeatRun_Count)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_HeatRun_Count;
    }
    else if (addr == DF_u8_Step)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u8_Step;
    }
    else if (addr == DF_u16_Step_Delay)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Defrost.u16_Step_Delay;
    }
    else if (addr == HP_Err_Cnt)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Protect.u16_HpErrCnt;
    }
    else if (addr == LP_Err_Cnt)
    {
		ecbm_modbus_rtu_reg_buf[addr] = Protect.u16_LpErrCnt;
    }
    else if (addr == RLY_Ctrl)
    {
		if (Comp.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		
		if (CirculationPump.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}

		if (Fan.Outdoor.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}

		if (FourWay.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}

		if (Crank.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);
		}

		if (WFV.f_ForceDrvOn)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
    }
    else if (addr == Input_Sta)
    {
		if (LowPress)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 0);
		}
		if (HighPress)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 1);
		}
		if (WaterFlow)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 2);
		}
		if (LowWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 3);
		}
		if (MidWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 4);
		}
		if (HighWaterLevel)
		{
			SETB(ecbm_modbus_rtu_reg_buf[addr], 5);
		}
    }
	else if (addr == EEV_SuperHeatAvg)
    {
		ecbm_modbus_rtu_reg_buf[addr] = StepMotor.var.s16_SuperHeatAvg;
    } 
    else if (addr == EEV_DeltaStep)
    {
		ecbm_modbus_rtu_reg_buf[addr] = StepMotor.var.s16_EEVDeltaStep;
    } 
    
    *dat=ecbm_modbus_rtu_reg_buf[addr];
}
#endif
#endif 	//旧点表结束

/*-------------------------------------------------------
1号功能码处理函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_CMD01_EN
void ecbm_modbus_rtu_cmd_0x01(void){
    emu8 temp8,t1,c1,i,j,qw;
    emu16 temp16;
    ecbm_modbus_rtu_crc= 0xFFFF;
    if((ecbm_modbus_rtu_data_count>=1)&&(ecbm_modbus_rtu_data_count<=0x07D0)){      //读取的个数要在1个以上，且不能大于2000。
        if(((emu32)ecbm_modbus_rtu_data_count+(emu32)ecbm_modbus_rtu_address)<=65536UL){   //判断地址+个数有没有超限。
            #if ECBM_MODBUS_RTU_BIT_BUF_EN
            if(                                                                        //遇到以下问题，说明写入肯定会失败。
                (ecbm_modbus_rtu_address<ECBM_MODBUS_RTU_BIT_START_ADDR)||             //输入地址比起始地址还小的，
                (ecbm_modbus_rtu_address+ecbm_modbus_rtu_data_count)>(ECBM_MODBUS_RTU_BIT_BUF_SIZE*8+ECBM_MODBUS_RTU_BIT_START_ADDR)//输入的地址+输入的数量超过本机定义的数量。
            ){
                ecbm_modbus_rtu_fun_err_num=0x04;                       //记录异常码04。
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);              //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x81);
                    ecbm_modbus_rtu_crc16(0x04);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);           //发送地址。
                    ecbm_modbus_rtu_set_data(0x81);                         //发送0x80+功能码回复。
                    ecbm_modbus_rtu_set_data(0x04);                         //异常码04。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));    //发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            #else
            if(0){  //如果是不用内置数组缓存的话，只要地址在范围内，无论是多少都是被允许的。
            #endif
            }else{
                if(ecbm_modbus_rtu_broadcast_en){
                    t1=(emu8)(ecbm_modbus_rtu_data_count/8);      //统计要读取的数据能凑够多少个字节。
                    if(ecbm_modbus_rtu_data_count%8)t1++;       //剩下的不足8位的数据也要一个字节来传输。
                    #if ECBM_MODBUS_RTU_BIT_BUF_EN
                    temp16=ecbm_modbus_rtu_address-ECBM_MODBUS_RTU_BIT_START_ADDR;             //获取数据起始地址。
                    #else
                    temp16=ecbm_modbus_rtu_address;             //获取数据起始地址。
                    #endif
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);  //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x01);
                    ecbm_modbus_rtu_crc16(t1);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);//发送地址。
                    ecbm_modbus_rtu_set_data(0x01);             //发送功能码回复。
                    ecbm_modbus_rtu_set_data(t1);               //发送数据长度。
                    for(i=0;i<t1;i++){                          //从起始位置开始组装数据。
                        temp8=0;                                //清零变量。
                        if(ecbm_modbus_rtu_data_count>=8){      //如果剩余要读的数据多于8个比特。
                            c1=8;                               //那么本轮循环先读8比特数据。
                        }else{                                  //否则，
                            c1=(emu8)ecbm_modbus_rtu_data_count;  //就有多少读多少。
                        }
                        for(j=0;j<c1;j++){      
                            ecbm_modbus_cmd_read_bit(temp16++,&qw);//将地址送到读取函数中，获取对应的比特值。
                            temp8|=(qw<<j);                     //组装数据。
                        }
                        ecbm_modbus_rtu_crc16(temp8);           //计算CRC。
                        ecbm_modbus_rtu_set_data(temp8);        //发送组装好的数据。
                        ecbm_modbus_rtu_data_count-=(emu16)c1;    //计算剩下要读的数据个数。
                    }
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            }
        }else{                                              //如果地址+个数超过2000。
            ecbm_modbus_rtu_fun_err_num=0x02;               //记录异常码02。
            if(ecbm_modbus_rtu_broadcast_en){
                ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);      //计算CRC，下同。
                ecbm_modbus_rtu_crc16(0x81);
                ecbm_modbus_rtu_crc16(0x02);
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);   //发送地址。
                ecbm_modbus_rtu_set_data(0x81);                 //发送0x80+功能码回复。
                ecbm_modbus_rtu_set_data(0x02);                 //异常码02。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
            }
        }
    }else{                                                  //如果个数本身就超过2000了。
        ecbm_modbus_rtu_fun_err_num=0x03;                   //记录异常码03。
        if(ecbm_modbus_rtu_broadcast_en){	
            ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);          //计算CRC，下同。
            ecbm_modbus_rtu_crc16(0x81);
            ecbm_modbus_rtu_crc16(0x03);
            ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);       //发送地址。
            ecbm_modbus_rtu_set_data(0x81);                     //发送0x80+功能码回复。
            ecbm_modbus_rtu_set_data(0x03);                     //异常码03
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
        }
    }
}
#endif
/*-------------------------------------------------------
2号功能码处理函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_CMD02_EN
void ecbm_modbus_rtu_cmd_0x02(void){
    emu8 temp8,t1,c1,i,j,qw;
    emu16 temp16;
    ecbm_modbus_rtu_crc= 0xFFFF;
    if((ecbm_modbus_rtu_data_count>=1)&&(ecbm_modbus_rtu_data_count<=0x07D0)){      //读取的个数要在1个以上，且地址不能大于2000。
        if(((emu32)ecbm_modbus_rtu_data_count+(emu32)ecbm_modbus_rtu_address)<=65536UL){   //判断地址+个数有没有超限。
//            if(0){//如果内部没有定义那么多的比特位。
//                ecbm_modbus_rtu_fun_err_num=0x04;                       //记录异常码04。
//                if(ecbm_modbus_rtu_broadcast_en){
//                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);              //计算CRC，下同。
//                    ecbm_modbus_rtu_crc16(0x82);
//                    ecbm_modbus_rtu_crc16(0x04);
//                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);           //发送地址。
//                    ecbm_modbus_rtu_set_data(0x82);                         //发送0x80+功能码回复。
//                    ecbm_modbus_rtu_set_data(0x04);                         //异常码04。
//                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));    //发送CRC。
//                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
//                }
//            }else{
                if(ecbm_modbus_rtu_broadcast_en){
                    t1=(emu8)(ecbm_modbus_rtu_data_count/8);      //统计要读取的数据能凑够多少个字节。
                    if(ecbm_modbus_rtu_data_count%8)t1++;       //剩下的不足8位的数据也要一个字节来传输。
                    temp16=ecbm_modbus_rtu_address;             //获取数据起始地址。
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);  //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x02);
                    ecbm_modbus_rtu_crc16(t1);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);//发送地址。
                    ecbm_modbus_rtu_set_data(0x02);             //发送功能码回复。
                    ecbm_modbus_rtu_set_data(t1);               //发送数据长度。
                    for(i=0;i<t1;i++){                          //从起始位置开始组装数据。
                        temp8=0;                                //清零变量。
                        if(ecbm_modbus_rtu_data_count>=8){      //如果剩余要读的数据多于8个比特。
                            c1=8;                               //那么本轮循环先读8比特数据。
                        }else{                                  //否则，
                            c1=(emu8)ecbm_modbus_rtu_data_count;  //就有多少读多少。
                        }
                        for(j=0;j<c1;j++){      
                            ecbm_modbus_cmd_read_io_bit(temp16++,&qw);//将地址送到读取函数中，获取对应的比特值。
                            temp8|=(qw<<j);                     //组装数据。
                        }
                        ecbm_modbus_rtu_crc16(temp8);           //计算CRC。
                        ecbm_modbus_rtu_set_data(temp8);        //发送组装好的数据。
                        ecbm_modbus_rtu_data_count-=(emu16)c1;    //计算剩下要读的数据个数。
                    }
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
//          }
        }else{                                              //如果地址+个数超过2000。
            ecbm_modbus_rtu_fun_err_num=0x02;               //记录异常码02。
            if(ecbm_modbus_rtu_broadcast_en){
                ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);      //计算CRC，下同。
                ecbm_modbus_rtu_crc16(0x82);
                ecbm_modbus_rtu_crc16(0x02);
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);   //发送地址。
                ecbm_modbus_rtu_set_data(0x82);                 //发送0x80+功能码回复。
                ecbm_modbus_rtu_set_data(0x02);                 //异常码02。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
            }
        }
    }else{                                                  //如果个数本身就超过2000了。
        ecbm_modbus_rtu_fun_err_num=0x03;                   //记录异常码03。
        if(ecbm_modbus_rtu_broadcast_en){	
            ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);          //计算CRC，下同。
            ecbm_modbus_rtu_crc16(0x82);
            ecbm_modbus_rtu_crc16(0x03);
            ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);       //发送地址。
            ecbm_modbus_rtu_set_data(0x82);                     //发送0x80+功能码回复。
            ecbm_modbus_rtu_set_data(0x03);                     //异常码03
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
        }
    }
}
#endif
/*-------------------------------------------------------
3号功能码处理函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_CMD03_EN
void ecbm_modbus_rtu_cmd_0x03(void){
    emu16 temp16,i;
    ecbm_modbus_rtu_crc=0xffff;
    if((ecbm_modbus_rtu_data_count>=1)&&(ecbm_modbus_rtu_data_count<=0x007D)){          //读取的个数要在1个以上，且地址不能大于125。
        if(((emu32)ecbm_modbus_rtu_data_count+(emu32)ecbm_modbus_rtu_address)<65536UL){     //判断地址+个数有没有超限。
            #if ECBM_MODBUS_RTU_REG_BUF_EN
            if(                                                                        //遇到以下问题，说明写入肯定会失败。
                (ecbm_modbus_rtu_address<ECBM_MODBUS_RTU_REG_START_ADDR)||             //输入地址比起始地址还小的，
                (ecbm_modbus_rtu_address+ecbm_modbus_rtu_data_count)>(ECBM_MODBUS_RTU_REG_BUF_SIZE+ECBM_MODBUS_RTU_REG_START_ADDR)//输入的地址+输入的数量超过本机定义的数量。
            ){
                ecbm_modbus_rtu_fun_err_num=0x04;           //记录异常码04。
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);  //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x83);
                    ecbm_modbus_rtu_crc16(0x04);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);//发送地址。
                    ecbm_modbus_rtu_set_data(0x83);             //发送0x80+功能码回复。
                    ecbm_modbus_rtu_set_data(0x04);             //异常码04。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            #else
            if(0){
            #endif
            }else{
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);  //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x03);
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_data_count*2);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);//发送地址。
                    ecbm_modbus_rtu_set_data(0x03);             //发送功能码回复。
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_data_count*2);//发送回复字节数。
                    #if ECBM_MODBUS_RTU_REG_BUF_EN
                    ecbm_modbus_rtu_address-=ECBM_MODBUS_RTU_REG_START_ADDR;
                    #endif
                    for(i=0;i<ecbm_modbus_rtu_data_count;i++){
                        ecbm_modbus_cmd_read_reg(ecbm_modbus_rtu_address+i,&temp16);//从寄存器变量里把数据取出来。
                        ecbm_modbus_rtu_crc16((emu8)(temp16>>8)); //计算CRC，下同。
                        ecbm_modbus_rtu_crc16((emu8)(temp16));
                        ecbm_modbus_rtu_set_data((emu8)(temp16>>8));//发送数据。
                        ecbm_modbus_rtu_set_data((emu8)(temp16));
                    }
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            }
        }else{
            ecbm_modbus_rtu_fun_err_num=0x02;           //记录异常码02。
            if(ecbm_modbus_rtu_broadcast_en){
                ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);  //计算CRC，下同。
                ecbm_modbus_rtu_crc16(0x83);
                ecbm_modbus_rtu_crc16(0x02);
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);//发送地址。
                ecbm_modbus_rtu_set_data(0x83);              //发送0x80+功能码回复。
                ecbm_modbus_rtu_set_data(0x02);              //异常码02。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
            }
        }
    }else{                                              //如果个数本身就超过125了。
        ecbm_modbus_rtu_fun_err_num=0x03;               //记录异常码03。	
        if(ecbm_modbus_rtu_broadcast_en){
            ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);      //计算CRC，下同。
            ecbm_modbus_rtu_crc16(0x83);
            ecbm_modbus_rtu_crc16(0x03);
            ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);   //发送地址。
            ecbm_modbus_rtu_set_data(0x83);                 //发送0x80+功能码回复。
            ecbm_modbus_rtu_set_data(0x03);                 //异常码03。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
        }
    }
}
#endif
/*-------------------------------------------------------
4号功能码处理函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_CMD04_EN
void ecbm_modbus_rtu_cmd_0x04(void){
    emu16 temp16,i;
    ecbm_modbus_rtu_crc=0xffff;
    if((ecbm_modbus_rtu_data_count>=1)&&(ecbm_modbus_rtu_data_count<=0x007D)){          //读取的个数要在1个以上，且地址不能大于125。
        if(((emu32)ecbm_modbus_rtu_data_count+(emu32)ecbm_modbus_rtu_address)<65536UL){     //判断地址+个数有没有超限。
//            if(0){//如果内部没有定义那么多的寄存器。
//                ecbm_modbus_rtu_fun_err_num=0x04;           //记录异常码04。
//                if(ecbm_modbus_rtu_broadcast_en){
//                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);  //计算CRC，下同。
//                    ecbm_modbus_rtu_crc16(0x84);
//                    ecbm_modbus_rtu_crc16(0x04);
//                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);//发送地址。
//                    ecbm_modbus_rtu_set_data(0x84);             //发送0x80+功能码回复。
//                    ecbm_modbus_rtu_set_data(0x04);             //异常码04。
//                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
//                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
//                }
//            }else{
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);  //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x04);
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_data_count*2);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);//发送地址。
                    ecbm_modbus_rtu_set_data(0x04);             //发送功能码回复。
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_data_count*2);//发送回复字节数。
                    for(i=0;i<ecbm_modbus_rtu_data_count;i++){
                        ecbm_modbus_cmd_read_io_reg(ecbm_modbus_rtu_address+i,&temp16);//从寄存器变量里把数据取出来。
                        ecbm_modbus_rtu_crc16((emu8)(temp16>>8)); //计算CRC，下同。
                        ecbm_modbus_rtu_crc16((emu8)(temp16));
                        ecbm_modbus_rtu_set_data((emu8)(temp16>>8));//发送数据。
                        ecbm_modbus_rtu_set_data((emu8)(temp16));
                    }
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
//            }
        }else{
            ecbm_modbus_rtu_fun_err_num=0x02;           //记录异常码02。
            if(ecbm_modbus_rtu_broadcast_en){
                ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);  //计算CRC，下同。
                ecbm_modbus_rtu_crc16(0x84);
                ecbm_modbus_rtu_crc16(0x02);
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);//发送地址。
                ecbm_modbus_rtu_set_data(0x84);              //发送0x80+功能码回复。
                ecbm_modbus_rtu_set_data(0x02);              //异常码02。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
            }
        }
    }else{                                              //如果个数本身就超过125了。
        ecbm_modbus_rtu_fun_err_num=0x03;               //记录异常码03。	
        if(ecbm_modbus_rtu_broadcast_en){
            ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);      //计算CRC，下同。
            ecbm_modbus_rtu_crc16(0x84);
            ecbm_modbus_rtu_crc16(0x03);
            ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);   //发送地址。
            ecbm_modbus_rtu_set_data(0x84);                 //发送0x80+功能码回复。
            ecbm_modbus_rtu_set_data(0x03);                 //异常码03。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
        }
    }
}
#endif
/*-------------------------------------------------------
5号功能码处理函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_CMD05_EN
void ecbm_modbus_rtu_cmd_0x05(void){
    ecbm_modbus_rtu_crc=0xffff;
    if((ecbm_modbus_rtu_data_count==0x0000)||(ecbm_modbus_rtu_data_count==0xFF00)){//判断输出值是否合法。
//      if((ecbm_modbus_rtu_address>=0)&&(ecbm_modbus_rtu_address<=65535)){//其实能传进来的地址都符合这个范围，所以在这里优化掉了。
            #if ECBM_MODBUS_RTU_BIT_BUF_EN
            if(                                                                        //遇到以下问题，说明写入肯定会失败。
                (ecbm_modbus_rtu_address<ECBM_MODBUS_RTU_BIT_START_ADDR)||             //输入地址比起始地址还小的，
                (ecbm_modbus_rtu_address>=(ECBM_MODBUS_RTU_BIT_BUF_SIZE*8+ECBM_MODBUS_RTU_BIT_START_ADDR))//输入地址比总的设计地址还大的，
            ){
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_fun_err_num=0x04;                           //记录异常码04。
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);                  //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x85);
                    ecbm_modbus_rtu_crc16(0x04);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);               //发送地址。
                    ecbm_modbus_rtu_set_data(0x85);                             //发送0x80+功能码回复。
                    ecbm_modbus_rtu_set_data(0x04);                             //异常码04。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));        //发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            #else
            if(0){  //如果是不用内置数组缓存的话，只要地址在范围内，无论是多少都是被允许的。
            #endif
            }else{
                #if ECBM_MODBUS_RTU_BIT_BUF_EN
                ecbm_modbus_cmd_write_bit(ecbm_modbus_rtu_address-ECBM_MODBUS_RTU_BIT_START_ADDR,(emu8)(ecbm_modbus_rtu_data_count>>8));
                #else
                ecbm_modbus_cmd_write_bit(ecbm_modbus_rtu_address,(emu8)(ecbm_modbus_rtu_data_count>>8));
                #endif
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);                  //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x05);
                    ecbm_modbus_rtu_crc16((emu8)(ecbm_modbus_rtu_address>>8));
                    ecbm_modbus_rtu_crc16((emu8)(ecbm_modbus_rtu_address));
                    ecbm_modbus_rtu_crc16((emu8)(ecbm_modbus_rtu_data_count>>8));
                    ecbm_modbus_rtu_crc16((emu8)(ecbm_modbus_rtu_data_count));
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);               //发送地址。
                    ecbm_modbus_rtu_set_data(0x05);                             //发送功能码回复。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_address>>8)); //发送地址回复。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_address));
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_data_count>>8));//发送计数回复。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_data_count));
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));        //发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            }
//      }else{
//          ecbm_modbus_rtu_fun_err_num=0x02;                   //异常码02。	
//          if(ecbm_modbus_rtu_broadcast_en){
//              ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);          //计算CRC，下同。
//              ecbm_modbus_rtu_crc16(0x85);
//              ecbm_modbus_rtu_crc16(0x02);
//              ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);       //发送地址。
//              ecbm_modbus_rtu_set_data(0x85);                     //发送0x80+功能码回复。
//              ecbm_modbus_rtu_set_data(0x02);                     //异常码02。
//              ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
//              ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
//          }
//      }
    }else{                                                  //如果不合法。
        ecbm_modbus_rtu_fun_err_num=0x03;                   //记录异常码03。	
        if(ecbm_modbus_rtu_broadcast_en){
            ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);          //计算CRC，下同。
            ecbm_modbus_rtu_crc16(0x85);
            ecbm_modbus_rtu_crc16(0x03);
            ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);       //发送地址。
            ecbm_modbus_rtu_set_data(0x85);                     //发送0x80+功能码回复。
            ecbm_modbus_rtu_set_data(0x03);                     //异常码03
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
        }
    }
}
#endif
/*-------------------------------------------------------
6号功能码处理函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_CMD06_EN
void ecbm_modbus_rtu_cmd_0x06(void){
    ecbm_modbus_rtu_crc=0xffff;
//  if((ecbm_modbus_rtu_data_count>=0x0000)&&(ecbm_modbus_rtu_data_count<=0xFFFF)){//其实能传进来的数据都符合这个范围，所以在这里优化掉了。
//      if((ecbm_modbus_rtu_address>=0)&&(ecbm_modbus_rtu_address<=65536UL)){//其实能传进来的地址都符合这个范围，所以在这里优化掉了。
            #if ECBM_MODBUS_RTU_REG_BUF_EN
            if(                                                                        //遇到以下问题，说明写入肯定会失败。
                (ecbm_modbus_rtu_address<ECBM_MODBUS_RTU_REG_START_ADDR)||             //输入地址比起始地址还小的，
                (ecbm_modbus_rtu_address)>=(ECBM_MODBUS_RTU_REG_BUF_SIZE+ECBM_MODBUS_RTU_REG_START_ADDR)//输入的地址+输入的数量超过本机定义的数量。
            ){
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_fun_err_num=0x04;               //记录异常码04。
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);      //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x86);
                    ecbm_modbus_rtu_crc16(0x04);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);   //发送地址。
                    ecbm_modbus_rtu_set_data(0x86);                 //发送0x80+功能码回复。
                    ecbm_modbus_rtu_set_data(0x04);                 //异常码04。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            #else
            if(0){    
            #endif
            }else{
                #if ECBM_MODBUS_RTU_REG_BUF_EN
                ecbm_modbus_cmd_write_reg(ecbm_modbus_rtu_address-ECBM_MODBUS_RTU_REG_START_ADDR,ecbm_modbus_rtu_data_count);//把数据写入寄存器。
                #else
                ecbm_modbus_cmd_write_reg(ecbm_modbus_rtu_address,ecbm_modbus_rtu_data_count);//把数据写入寄存器。
                #endif
                
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);          //计算CRC，下同。
                    ecbm_modbus_rtu_crc16(0x06);
                    ecbm_modbus_rtu_crc16((emu8)(ecbm_modbus_rtu_address>>8));
                    ecbm_modbus_rtu_crc16((emu8)(ecbm_modbus_rtu_address));
                    ecbm_modbus_rtu_crc16((emu8)(ecbm_modbus_rtu_data_count>>8));
                    ecbm_modbus_rtu_crc16((emu8)(ecbm_modbus_rtu_data_count));
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);       //发送地址。
                    ecbm_modbus_rtu_set_data(0x06);                     //发送功能码回复。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_address>>8));//发送地址。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_address));
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_data_count>>8));//发送个数。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_data_count));
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            }
//      }else{
//          ecbm_modbus_rtu_fun_err_num=0x02;               //记录异常码02。
//          if(ecbm_modbus_rtu_broadcast_en){	
//              ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);      //计算CRC，下同。
//              ecbm_modbus_rtu_crc16(0x86);
//              ecbm_modbus_rtu_crc16(0x02);
//              ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);   //发送地址。
//              ecbm_modbus_rtu_set_data(0x86);                 //发送0x80+功能码回复。
//              ecbm_modbus_rtu_set_data(0x02);                 //异常码02。
//              ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
//              ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
//          }
//      }
//  }else{                                                  //如果不合法。
//      ecbm_modbus_rtu_fun_err_num=0x03;                   //记录异常码03。	
//      if(ecbm_modbus_rtu_broadcast_en){
//          ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);          //计算CRC，下同。
//          ecbm_modbus_rtu_crc16(0x86);
//          ecbm_modbus_rtu_crc16(0x03);
//          ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);       //发送地址。
//          ecbm_modbus_rtu_set_data(0x86);                     //发送0x80+功能码回复。
//          ecbm_modbus_rtu_set_data(0x03);                     //异常码03。
//          ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
//          ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
//      }
//  }
}
#endif
/*-------------------------------------------------------
16号功能码处理函数。
-------------------------------------------------------*/
#if ECBM_MODBUS_RTU_CMD10_EN
void ecbm_modbus_rtu_cmd_0x10(void){
    emu8 i;
    ecbm_modbus_rtu_crc=0xffff;
    if((ecbm_modbus_rtu_data_count>=0x0001)&&(ecbm_modbus_rtu_data_count<=0x007B)){             //输入的数据个数得符合要求。
        if(((emu32)ecbm_modbus_rtu_address+(emu32)ecbm_modbus_rtu_data_count)<65536UL){             //地址不能超过65536。
            #if ECBM_MODBUS_RTU_REG_BUF_EN
            if(                                                                        //遇到以下问题，说明写入肯定会失败。
                (ecbm_modbus_rtu_address<ECBM_MODBUS_RTU_REG_START_ADDR)||             //输入地址比起始地址还小的，
                (ecbm_modbus_rtu_address+ecbm_modbus_rtu_data_count)>(ECBM_MODBUS_RTU_REG_BUF_SIZE+ECBM_MODBUS_RTU_REG_START_ADDR)//输入的地址+输入的数量超过本机定义的数量。
            ){
                if(ecbm_modbus_rtu_broadcast_en){
                    ecbm_modbus_rtu_fun_err_num=0x04;               //记录异常码04。
                    ecbm_modbus_rtu_crc16   (ecbm_modbus_rtu_id);   //计算CRC，下同。
                    ecbm_modbus_rtu_crc16   (0x90);
                    ecbm_modbus_rtu_crc16   (0x04);
                    ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);   //发送地址。
                    ecbm_modbus_rtu_set_data(0x90);                 //发送0x80+功能码回复。
                    ecbm_modbus_rtu_set_data(0x04);                 //异常码04。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                    ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            #else 
            if(0){    
            #endif
            }else{//12511
                #if ECBM_MODBUS_RTU_REG_BUF_EN
                ecbm_modbus_rtu_address-=ECBM_MODBUS_RTU_REG_START_ADDR;
                #endif
                for(i=0;i<ecbm_modbus_rtu_cmd_count;i++){   
                    ecbm_modbus_cmd_write_reg(ecbm_modbus_rtu_address+i,ecbm_modbus_rtu_cmd_buf[i]);  //把数据写入寄存器。
                }
                if(ecbm_modbus_rtu_broadcast_en){
                        ecbm_modbus_rtu_crc16   (ecbm_modbus_rtu_id);          //计算CRC，下同。
                        ecbm_modbus_rtu_crc16   (0x10);
                        ecbm_modbus_rtu_crc16   ((emu8)(ecbm_modbus_rtu_address>>8));
                        ecbm_modbus_rtu_crc16   ((emu8)(ecbm_modbus_rtu_address));
                        ecbm_modbus_rtu_crc16   ((emu8)(ecbm_modbus_rtu_data_count>>8));
                        ecbm_modbus_rtu_crc16   ((emu8)(ecbm_modbus_rtu_data_count));
                        ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);       //发送地址。
                        ecbm_modbus_rtu_set_data(0x10);                     //发送功能码回复。
                        ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_address>>8));//发送地址。
                        ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_address));
                        ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_data_count>>8));//发送个数。
                        ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_data_count));
                        ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                        ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
                }
            }
        }else{
            ecbm_modbus_rtu_fun_err_num=0x02;               //记录异常码02。
            if(ecbm_modbus_rtu_broadcast_en){	
                ecbm_modbus_rtu_crc16   (ecbm_modbus_rtu_id);   //计算CRC，下同。
                ecbm_modbus_rtu_crc16   (0x90);
                ecbm_modbus_rtu_crc16   (0x02);
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);   //发送地址。
                ecbm_modbus_rtu_set_data(0x90);                 //发送0x80+功能码回复。
                ecbm_modbus_rtu_set_data(0x02);                 //异常码02。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
            }
        }
    }else{                                                  //如果不合法。
        ecbm_modbus_rtu_fun_err_num=0x03;                   //记录异常码03。	
        if(ecbm_modbus_rtu_broadcast_en){
            ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);          //计算CRC，下同。
            ecbm_modbus_rtu_crc16(0x90);
            ecbm_modbus_rtu_crc16(0x03);
            ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);       //发送地址。
            ecbm_modbus_rtu_set_data(0x90);                     //发送0x80+功能码回复。
            ecbm_modbus_rtu_set_data(0x03);                     //异常码03。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));//发送CRC。
            ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
        }
    }
}
#endif
/*-------------------------------------------------------
modbus接收处理函数。
22-07-09：串口收到数据后回调用这里
-------------------------------------------------------*/
void ecbm_modbus_rtu_receive(void){
    emu8 dat;//11162
    ecbm_modbus_rtu_timeout=1;
    dat=ecbm_modbus_rtu_get_data();//220709:从串口BUFF寄存器中取数据
    switch(ecbm_modbus_rtu_status){
        case ECBM_MODBUS_RTU_READY:{            //就绪，等待接收数据。
            if((dat==ecbm_modbus_rtu_id)||(dat==0)||(dat==0xff)){      //如果收到的ID和本机的匹配。
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_FUN_NUM;//切换到功能码识别
                if((dat==0)||(dat==0xff)){
                    ecbm_modbus_rtu_broadcast_en=0;//写入通信模式，为了简化代码，采用直接赋值。
                }else{
                    ecbm_modbus_rtu_broadcast_en=1;
                }
                ecbm_modbus_rtu_fun_code=0;     //清零功能码缓存。
                ecbm_modbus_rtu_fun_err_num=0;  //清零异常码缓存。
                ecbm_modbus_rtu_uart_crc=0xffff;//重置CRC初值。
                ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;
                ecbm_modbus_rtu_crc16(dat);     //计算CRC。
                ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
            }else{                             //如果ID不匹配，进入相应的错误界面。
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_ID_ERR;
            }
        }break;
        case ECBM_MODBUS_RTU_FUN_NUM:{                                      //正在接收功能码。
            if(dat>127){                                                    //判断功能码是否合法，
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_FUN_NUM_ERR;         //不合法就跳到功能码错误。
                ecbm_modbus_rtu_fun_err_num=0x01;                           //异常码01。	
            }else{                                                          //如果合法，
                ecbm_modbus_rtu_fun_code=ecbm_modbus_rtu_check_fun_num(dat);//判断是不是本机支持的功能码。
                if(ecbm_modbus_rtu_fun_code>127){
                    ecbm_modbus_rtu_fun_code&=~0x80;
                    ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_FUN_NUM_VOID;    //不存在的功能码就跳到功能码空。
                    ecbm_modbus_rtu_fun_err_num=0x01;                       //异常码01。
                }else{
                    ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_ADDRH;           //如果是存在的功能码，就考虑开始接收数据了。
                    ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;
                    ecbm_modbus_rtu_crc16(dat);
                    ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
                }
            }
        }break;
        case ECBM_MODBUS_RTU_ADDRH:{                        //接收地址的高8位。
            ecbm_modbus_rtu_address=(emu16)dat<<8;            //组装地址。
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_ADDRL;   //到下一步。
            ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;   //计算CRC。
            ecbm_modbus_rtu_crc16(dat);
            ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
        }break;
        case ECBM_MODBUS_RTU_ADDRL:{                        //接收地址的低8位。
            ecbm_modbus_rtu_address+=(emu16)dat;              //组装地址。
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_DATA_COUNTH;//到下一步。
            ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;   //计算CRC。
            ecbm_modbus_rtu_crc16(dat);
            ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
        }break;
        case ECBM_MODBUS_RTU_DATA_COUNTH:{                  //接收数据/个数的高8位。
            ecbm_modbus_rtu_data_count=(emu16)dat<<8;         //组装数据/个数。
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_DATA_COUNTL;//到下一步。
            ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;   //计算CRC。
            ecbm_modbus_rtu_crc16(dat);
            ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
        }break;
        case ECBM_MODBUS_RTU_DATA_COUNTL:{                  //接收数据/个数的低8位。
            ecbm_modbus_rtu_data_count+=(emu16)dat;           //组装数据/个数。
            if(ecbm_modbus_rtu_fun_code==0x10){
                ecbm_modbus_rtu_cmd_count=0;
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_BYTE_COUNT;//到字节读取。
            }else{
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_CRCL;//到CRC。
            }
            ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;   //计算CRC。
            ecbm_modbus_rtu_crc16(dat);
            ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
        }break;
        case ECBM_MODBUS_RTU_CRCL:{                         //接收CRC的低8位。
            ecbm_modbus_rtu_crc_buf=(emu16)dat;               //组合CRC。
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_CRCH;    //到下一步。
        }break;
        case ECBM_MODBUS_RTU_CRCH:{                         //接收CRC的高8位。
            ecbm_modbus_rtu_crc_buf+=(emu16)dat<<8;           //组合CRC。
            if(ecbm_modbus_rtu_crc_buf==ecbm_modbus_rtu_uart_crc){//判断接收的CRC和计算的CRC是否相等。
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_DO;  //相等的话就到执行步骤。
            }else{                                          //否则，
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_CRC_ERR;//就跳到CRC错误界面。
            }
        }break;
        #if ECBM_MODBUS_RTU_CMD10_EN
        case ECBM_MODBUS_RTU_BYTE_COUNT:{                   //接收数据字节数。
            ecbm_modbus_rtu_cmd_count=dat;
            if((ecbm_modbus_rtu_cmd_count==0)||(ecbm_modbus_rtu_cmd_count!=(emu8)(ecbm_modbus_rtu_data_count*2))){//如果数量不合。
                ecbm_modbus_rtu_fun_err_num=0x03;           //字节数对不上，异常码03。
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_BYTE_ERR;//调到对应的处理界面。
            }else{
                ecbm_modbus_rtu_cmd_count=0;                    //复用该变量。
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_DATAH;//调到对应的处理界面。
                ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;   //计算CRC。
                ecbm_modbus_rtu_crc16(dat);
                ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
            }
        }break;
        case ECBM_MODBUS_RTU_DATAH:{
            ecbm_modbus_rtu_cmd_buf[ecbm_modbus_rtu_cmd_count]=((emu16)dat)<<8;
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_DATAL;   //到低8位。
            ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;   //计算CRC。
            ecbm_modbus_rtu_crc16(dat);
            ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
        }break;
        case ECBM_MODBUS_RTU_DATAL:{
            ecbm_modbus_rtu_cmd_buf[ecbm_modbus_rtu_cmd_count]+=((emu16)dat);
            ecbm_modbus_rtu_cmd_count++;
            if(ecbm_modbus_rtu_cmd_count==(emu8)ecbm_modbus_rtu_data_count){
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_CRCL;//到CRC。
            }else{
                ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_DATAH;//到下一个数据的高8位。
            }
            ecbm_modbus_rtu_crc=ecbm_modbus_rtu_uart_crc;   //计算CRC。
            ecbm_modbus_rtu_crc16(dat);
            ecbm_modbus_rtu_uart_crc=ecbm_modbus_rtu_crc;
        }break;
        #endif
    }
}
/*-------------------------------------------------------
modbus主循环处理函数。
-------------------------------------------------------*/
void ecbm_modbus_rtu_run(void){
    switch(ecbm_modbus_rtu_status){
        case ECBM_MODBUS_RTU_FUN_NUM_VOID://	debug("不支持该功能码\r\n");
        case ECBM_MODBUS_RTU_FUN_NUM_ERR:{//	debug("功能码错误\r\n");
            if(ecbm_modbus_rtu_broadcast_en){
                ecbm_modbus_rtu_crc=0xFFFF;
                ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);              //计算CRC，下同。
                ecbm_modbus_rtu_crc16(0x80+ecbm_modbus_rtu_fun_code); 
                ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_fun_err_num);
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);           //发送地址。
                ecbm_modbus_rtu_set_data(0x80+ecbm_modbus_rtu_fun_code);//发送0x80+功能码回复。
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_fun_err_num);  //异常码。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));    //发送CRC。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
            }
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_WAIT;
        }break;
        case ECBM_MODBUS_RTU_ID_ERR:{//ID错误。
            //这里可以做些处理，但默认留空。
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_WAIT;
        }break;
        case ECBM_MODBUS_RTU_CRC_ERR:{//CRC错误。
            //这里可以做些处理，比如发送个重发信号，但默认留空。
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_WAIT;
        }break;
        case ECBM_MODBUS_RTU_DO:{//动作执行。
            #if ECBM_MODBUS_RTU_CMD_ALL_EN
                #if ECBM_MODBUS_IO_EN
//                ecbm_modbus_rtu_set_io(ECBM_MODBUS_WRITE);//220709:控制使能脚写  #test
//                P_Uart2_En_Hi();
//                P_Uart1_En_Hi();
                #endif
                switch(ecbm_modbus_rtu_fun_code){//根据功能码来选择对应的动作。
                #if ECBM_MODBUS_RTU_CMD01_EN
                    case 0x01:ecbm_modbus_rtu_cmd_0x01();break;
                #endif
                #if ECBM_MODBUS_RTU_CMD02_EN
                    case 0x02:ecbm_modbus_rtu_cmd_0x02();break;
                #endif
                #if ECBM_MODBUS_RTU_CMD03_EN
                    case 0x03:ecbm_modbus_rtu_cmd_0x03();break;
                #endif
                #if ECBM_MODBUS_RTU_CMD04_EN
                    case 0x04:ecbm_modbus_rtu_cmd_0x04();break;
                #endif
                #if ECBM_MODBUS_RTU_CMD05_EN
                    case 0x05:ecbm_modbus_rtu_cmd_0x05();break;
                #endif
                #if ECBM_MODBUS_RTU_CMD06_EN
                    case 0x06:ecbm_modbus_rtu_cmd_0x06();break;
                #endif
                #if ECBM_MODBUS_RTU_CMD10_EN
                    case 0x10:ecbm_modbus_rtu_cmd_0x10();break;
                #endif
                }
            #endif
//            #if ECBM_MODBUS_IO_EN
////            ecbm_modbus_rtu_set_io(ECBM_MODBUS_READ);//220709:控制使能脚
//            P_Uart2_En_Low();
//            P_Uart1_En_Low();
//            #endif
			
            F_uart0_TxReady = ENUM_ENABLE;
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_READY;
        }break;
        case ECBM_MODBUS_RTU_BYTE_ERR:{
            if(ecbm_modbus_rtu_broadcast_en){
                ecbm_modbus_rtu_crc=0xFFFF;
                ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_id);              //计算CRC，下同。
                ecbm_modbus_rtu_crc16(0x80+ecbm_modbus_rtu_fun_code); 
                ecbm_modbus_rtu_crc16(ecbm_modbus_rtu_fun_err_num);
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_id);           //发送地址。
                ecbm_modbus_rtu_set_data(0x80+ecbm_modbus_rtu_fun_code);//发送0x80+功能码回复。
                ecbm_modbus_rtu_set_data(ecbm_modbus_rtu_fun_err_num);  //异常码。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc));    //发送CRC。
                ecbm_modbus_rtu_set_data((emu8)(ecbm_modbus_rtu_crc>>8));
            }
            ecbm_modbus_rtu_status=ECBM_MODBUS_RTU_WAIT;
        }break;
    }
	
    
} 
