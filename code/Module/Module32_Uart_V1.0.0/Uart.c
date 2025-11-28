/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Uart.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/04/28
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"


#if defined		UART3_lhh
unsigned char g_txbuf[0xFF];            //??????
unsigned char g_tx_length;            //??????
unsigned char g_tx_count;             //??????

unsigned char g_rxbuf[0xFF];            //??????
unsigned char g_rx_length;            //??????
unsigned char g_rx_count;             //??????
unsigned char g_rx_time;              //????
unsigned char g_rx_finish_flag;       //??????
unsigned char g_rx_start_flag;        //??????


unsigned char g_16rx_length;


unsigned char g_crcbuf[2];


#endif

#if defined		UART3_lhh

void    Uart3_Init(void)
{
      g_tx_length = 0;                                    //??????
    g_tx_count = 0;                                     //??????
    g_rx_length = 8;                                    //??????
    g_rx_count = 0;                                     //??????
    g_rx_time = 0;                                      //????
    g_rx_finish_flag = 0;                               //??????
    g_rx_start_flag = 0;                                //??????
	
		g_16rx_length = 29;

    Uart3_Config_lhh();
}

void Uart3_Interrupt_lhh(void) 
{
     if ((UART_GetITStatus(UART3, UART_IT_TB) != RESET)
            && (UART_GetFlagStatus(UART3, UART_FLAG_TB) != RESET))//??????
    {
        UART_SendByte(UART3, g_txbuf[g_tx_count]);
        g_tx_count++;

        if (g_tx_count >= g_tx_length)
        {
            g_tx_count = 0;
            UART_ITConfig(UART3, UART_IT_TB, ENUM_DISABLE);
        }
    }

    if ((UART_GetITStatus(UART3, UART_IT_RB) != RESET)
            && (UART_GetFlagStatus(UART3, UART_FLAG_RB) != RESET))//??????
    {
        g_rxbuf[g_rx_count] = UART_RecByte(UART3);
        if(g_rxbuf[0]!=0x01)
        {
          g_rx_count = 0;
        }
        else
		{
			g_rx_count++;
			if(g_rx_count >1)
			{
					if(g_rxbuf[1] == 0x03)
					{
							if (g_rx_count >= g_rx_length)            //?????,????8???
							{  //g_rx_start_flag = 1;        //???????
								g_rx_finish_flag = 1;
							}
					}
					else if (g_rxbuf[1] == 0x10)
						{
						if (g_rx_count >= g_16rx_length)            //?????,???????
							{  //g_rx_start_flag = 1;        //???????
								g_rx_finish_flag = 1;
							}
						}
					else g_rx_count = 0;
			}
					
		}
        //g_rx_time = 0;                  //??UART????,????????????
    }
}

#endif



//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
#if defined		UART0_ENABLE

TYPE_BYTE       STRUCT_uart0_flag0;					    //串口0标志位
STRUCT_UART     Uart0;                                  //串口0相关变量
U8              U8_Uart0_TxBuf[UART0_TX_LEN];           //串口0发送驱动层数据缓存
U8              U8_Uart0_AppTxBuf[UART0_TX_LEN];        //串口0发送应用层数据缓存
U8              U8_Uart0_DrvRxBuf[UART0_RX_LEN];        //串口0接收驱动层数据缓存
U8              U8_Uart0_RxBuf[UART0_RX_LEN];           //串口0接收应用层数据缓存    

#endif
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
#if defined		UART1_ENABLE

TYPE_BYTE       STRUCT_uart1_flag0;					    //串口1标志位
STRUCT_UART     Uart1;                                  //串口1相关变量
U8              U8_Uart1_TxBuf[UART1_TX_LEN];           //串口1发送驱动层数据缓存
U8              U8_Uart1_AppTxBuf[UART1_TX_LEN];        //串口1发送应用层数据缓存
U8              U8_Uart1_DrvRxBuf[UART1_RX_LEN];        //串口1接收驱动层数据缓存
U8              U8_Uart1_RxBuf[UART1_RX_LEN];           //串口1接收应用层数据缓存 

#endif
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
#if defined		UART2_ENABLE

TYPE_BYTE       STRUCT_uart2_flag0;					    //串口2标志位
STRUCT_UART     Uart2;                                  //串口2相关变量
U8              U8_Uart2_TxBuf[UART2_TX_LEN];           //串口2发送驱动层数据缓存
U8              U8_Uart2_AppTxBuf[UART2_TX_LEN];        //串口2发送应用层数据缓存
U8              U8_Uart2_DrvRxBuf[UART2_RX_LEN];        //串口2接收驱动层数据缓存
U8              U8_Uart2_RxBuf[UART2_RX_LEN];           //串口2接收应用层数据缓存 

#endif
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
#if defined		UART3_ENABLE

TYPE_BYTE       STRUCT_uart3_flag0;					    //串口3标志位
STRUCT_UART     Uart3;                                  //串口3相关变量
U8              U8_Uart3_TxBuf[UART3_TX_LEN];           //串口3发送驱动层数据缓存
U8              U8_Uart3_AppTxBuf[UART3_TX_LEN];        //串口3发送应用层数据缓存
U8              U8_Uart3_DrvRxBuf[UART3_RX_LEN];        //串口3接收驱动层数据缓存
U8              U8_Uart3_RxBuf[UART3_RX_LEN];           //串口3接收应用层数据缓存 

#endif
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
#if defined		UART4_ENABLE

TYPE_BYTE       STRUCT_uart4_flag0;					    //串口4标志位
STRUCT_UART     Uart4;                                  //串口4相关变量
U8              U8_Uart4_TxBuf[UART4_TX_LEN];           //串口4发送驱动层数据缓存
U8              U8_Uart4_AppTxBuf[UART4_TX_LEN];        //串口4发送应用层数据缓存
U8              U8_Uart4_DrvRxBuf[UART4_RX_LEN];        //串口4接收驱动层数据缓存
U8              U8_Uart4_RxBuf[UART4_RX_LEN];           //串口4接收应用层数据缓存 

#endif
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
#if defined		UART5_ENABLE

TYPE_BYTE       STRUCT_uart5_flag0;					    //串口5标志位
STRUCT_UART     Uart5;                                  //串口5相关变量
U8              U8_Uart5_TxBuf[UART5_TX_LEN];           //串口5发送驱动层数据缓存
U8              U8_Uart5_AppTxBuf[UART5_TX_LEN];        //串口5发送应用层数据缓存
U8              U8_Uart5_DrvRxBuf[UART5_RX_LEN];        //串口5接收驱动层数据缓存
U8              U8_Uart5_RxBuf[UART5_RX_LEN];           //串口5接收应用层数据缓存 

#endif
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//

#if defined		UART0_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart0(void) 
Description         :初始化串口0
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Module_Init_Uart0(void)
{
    //RX输出高内部上拉
    P_Uart0_Rx_Hi();
    P_Uart0_Rx_Output();
    P_Uart0_Rx_Enpull();
    
    //TX输出高内部上拉
    P_Uart0_Tx_Hi();
    P_Uart0_Tx_Output();
    P_Uart0_Tx_Enpull();

	//En输出高内部上拉
    P_Uart0_En_Low();
    P_Uart0_En_Output();
    P_Uart0_En_Enpull();
    //UART0配置  
    Uart0_Config();
}
/****************************************************************************************************
Function Name       :void Uart0_Interrupt(void)
Description         :串口中断函数
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void Uart0_Interrupt(void) 
{
    unsigned char i, temp;	

    if ((UART_GetITStatus(UART0, UART_IT_RB) != RESET) && (UART_GetFlagStatus(UART0, UART_FLAG_RB) != RESET))         //接收标志位判断
    {
		uart0_receive_callback();
    }
//    {
//		temp = UART_RecByte(UART0);
//   
//        Uart0.u8_RxBuffLast = Uart0.u8_RxBuff;
//        Uart0.u8_RxBuff = temp;
//
//        if (F_uart0_RxComplete == CF_DISABLE)
//        {			
//            if (Uart0.u8_RxCnt == 0)
//			{
//				if (Uart0.u8_RxBuff == C_UART0_RX_HEAD_FIRST)
//				{
//					for (i=0; i<UART0_RX_LEN; i++)
//					{
//						U8_Uart0_DrvRxBuf[i] = 0;
//					}
//				
//					U8_Uart0_DrvRxBuf[UART0_RX_HEAD_FIRST] = Uart0.u8_RxBuff;
//				
//					Uart0.u8_RxCnt = 1;
//					F_uart0_Receiving = CF_ENABLE;
//					Uart0.u8_RxTimerOut = 0;
//					
//				}
//			}
//            else if (Uart0.u8_RxCnt >= 1) 
//            {
//           
//                U8_Uart0_DrvRxBuf[Uart0.u8_RxCnt++] = Uart0.u8_RxBuff;									
//
//                if (Uart0.u8_RxCnt >= UART0_RX_LEN)                  //接收信息字节长度(根据功能需要接收多少个字节,可能是常数可能是变量)
//                {
//                    F_uart0_RxComplete = CF_ENABLE;
//                    F_uart0_Receiving = CF_DISABLE;
//                    Uart0.u8_RxTimerOut = 0;
//                }
//            }
//        }	
//    } 
    
    if ((UART_GetITStatus(UART0, UART_IT_TB) != RESET) && (UART_GetFlagStatus(UART0, UART_FLAG_TB) != RESET))		//发送标志位判断
    {
    	
    	if (Uart0.u8_TxCnt < Uart0.u8_TxNum)                          //发送电源板信息12个字节
        {			
            temp = U8_Uart0_TxBuf[Uart0.u8_TxCnt++];	
			UART_SendByte(UART0, temp);		
        }
        else if (UART_GetFlagStatus(UART0, UART_FLAG_TXIDLE) != RESET)
        {
            UART_ITConfig(UART0, UART_IT_TB, ENUM_DISABLE);
			Uart0.Enum_TxState = ENUM_TXSTATE_OK;
            Uart0.u8_TxCnt = 0;
            Uart0.u8_TxNum = 0;
            
        }	
    }
//    {       
////        if (Uart0.u8_TxCnt < UART0_TX_LEN)                          //发送电源板信息12个字节
////        {						
////            temp = U8_Uart0_TxBuf[Uart0.u8_TxCnt++];	
////			UART_SendByte(UART0, temp);			
////        }
////        else
////        {
////            UART_ITConfig(UART0, UART_IT_TB, ENUM_DISABLE);
////			Uart0.Enum_TxState = ENUM_TXSTATE_OK;
////            Uart0.u8_TxCnt = 0;
////        }	
//		UART_ITConfig(UART0, UART_IT_TB, ENUM_DISABLE);
//    }	
}
/****************************************************************************************************
Function Name       :void    Uart0_SendPackDeal(void)
Description         :串口0发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart0_SendPackDeal(void)
{
    if (F_uart0_TxReady)                            //串口发送空闲时
    {
        F_uart0_TxReady = CF_DISABLE;
        
        Uart0.u8_TxCnt = 1;                         //发送数据包首个字节
        Uart0.Enum_TxState = ENUM_TXSTATE_BUSY;     //发送状态忙
        UART_SendByte(UART0, U8_Uart0_TxBuf[0]);     //首个字节送入串口发送缓存
		UART_ITConfig(UART0, UART_IT_TB, ENUM_ENABLE);    //发送有效

    }

	if (Uart0.Enum_TxState >= ENUM_TXSTATE_OK)      //状态发送完毕后自动转为发送空闲
	{
		Uart0.Enum_TxState = ENUM_TXSTATE_IDLE;
	}

	if (Uart0.Enum_TxState == ENUM_TXSTATE_IDLE)
	{
		P_Uart0_En_Low();
	}
	else 
	{
		P_Uart0_En_Hi();
	}

    ECBM_MODBUS_RTU_TIMEOUT_RUN();			//modbus超时逻辑处理
}

//{
//    if (F_uart0_TxReady)                             //串口发送空闲时
//    {
//        F_uart0_TxReady = CF_DISABLE;
//        
//        Uart0.u8_TxCnt = 1;                          //发送数据包首个字节
//        Uart0.Enum_TxState = ENUM_TXSTATE_BUSY;      //发送状态忙
//		
//        UART_SendByte(UART0, U8_Uart0_TxBuf[0]);     //首个字节送入串口发送缓存
//		UART_ITConfig(UART0, UART_IT_TB, ENUM_ENABLE);    //发送有效
//    }
//    
//    
//    if (Uart0.Enum_TxState >= ENUM_TXSTATE_OK)       //状态发送完毕后自动转为发送空闲
//    {
//        Uart0.Enum_TxState = ENUM_TXSTATE_IDLE;
//    }
//}
#endif

#if defined		UART1_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart1(void) 
Description         :初始化串口1
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Module_Init_Uart1(void)
{
    //RX输出高内部上拉
    P_Uart1_Rx_Hi();
    P_Uart1_Rx_Output();
    P_Uart1_Rx_Enpull();
    
    //TX输出高内部上拉
    P_Uart1_Tx_Hi();
    P_Uart1_Tx_Output();
    P_Uart1_Tx_Enpull();

	//En输出高内部上拉
    P_Uart1_En_Low();
    P_Uart1_En_Output();
    P_Uart1_En_Enpull();

    //UART1配置  
    Uart1_Config();
}
/****************************************************************************************************
Function Name       :void Uart1_Interrupt(void)
Description         :串口中断函数
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void Uart1_Interrupt(void) 
{
	
    unsigned char i, temp;	

    if ((UART_GetITStatus(UART1, UART_IT_RB) != RESET) && (UART_GetFlagStatus(UART1, UART_FLAG_RB) != RESET))         //接收标志位判断
    {
//		uart1_receive_callback();
    }
//    {
//		temp = UART_RecByte(UART1);
//      
//        Uart1.u8_RxBuffLast = Uart1.u8_RxBuff;
//        Uart1.u8_RxBuff = temp;
//
//        if (F_uart1_RxComplete == CF_DISABLE)
//        {			
//            if ((Uart1.u8_RxBuffLast == C_UART1_RX_HEAD_FIRST) && (Uart1.u8_RxBuff == C_UART1_RX_HEAD_SECOND))
//            {
//                for (i=0; i<UART1_RX_LEN; i++)
//                {
//                    U8_Uart1_DrvRxBuf[i] = 0;
//                }
//            
//                U8_Uart1_DrvRxBuf[UART1_RX_HEAD_FIRST]  = Uart1.u8_RxBuffLast;
//                U8_Uart1_DrvRxBuf[UART1_RX_HEAD_SECOND] = Uart1.u8_RxBuff;
//            
//                Uart1.u8_RxCnt = 2;
//                F_uart1_Receiving = CF_ENABLE;
//                Uart1.u8_RxTimerOut = 0;
//                
//            }
//            else if (Uart1.u8_RxCnt >= 2) 
//            {
//           
//                U8_Uart1_DrvRxBuf[Uart1.u8_RxCnt++] = Uart1.u8_RxBuff;									
//
//                if (Uart1.u8_RxCnt >= UART1_RX_LEN)                  //接收信息字节长度(根据功能需要接收多少个字节,可能是常数可能是变量)
//                {
//                    F_uart1_RxComplete = CF_ENABLE;
//                    F_uart1_Receiving = CF_DISABLE;
//                    Uart1.u8_RxTimerOut = 0;
//                }
//            }
//        }	
//    } 
    
    if ((UART_GetITStatus(UART1, UART_IT_TB) != RESET) && (UART_GetFlagStatus(UART1, UART_FLAG_TB) != RESET))		//发送标志位判断
    {
    	
    	if (Uart1.u8_TxCnt < Uart1.u8_TxNum)                          //发送电源板信息12个字节
        {			
            temp = U8_Uart1_TxBuf[Uart1.u8_TxCnt++];	
			UART_SendByte(UART1, temp);		
        }
        else if (UART_GetFlagStatus(UART1, UART_FLAG_TXIDLE) != RESET)
        {
            UART_ITConfig(UART1, UART_IT_TB, ENUM_DISABLE);
			Uart1.Enum_TxState = ENUM_TXSTATE_OK;
            Uart1.u8_TxCnt = 0;
            Uart1.u8_TxNum = 0;
            
        }	
       
    }	
}
/****************************************************************************************************
Function Name       :void    Uart1_SendPackDeal(void)
Description         :串口1发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart1_SendPackDeal(void)
{
    if (F_uart1_TxReady)                            //串口发送空闲时
    {
        F_uart1_TxReady = CF_DISABLE;
        
        Uart1.u8_TxCnt = 1;                         //发送数据包首个字节
        Uart1.Enum_TxState = ENUM_TXSTATE_BUSY;     //发送状态忙
//        P_Uart1_En_Hi();
        UART_SendByte(UART1, U8_Uart1_TxBuf[0]);     //首个字节送入串口发送缓存
		UART_ITConfig(UART1, UART_IT_TB, ENUM_ENABLE);    //发送有效

    }

   
    
//    if (Uart1.Enum_TxState >= ENUM_TXSTATE_OK + 1)      //状态发送完毕后自动转为发送空闲
//    {
//        Uart1.Enum_TxState = ENUM_TXSTATE_IDLE;
//        P_Uart1_En_Low();
//    }
//
//    if (Uart1.Enum_TxState == ENUM_TXSTATE_OK)
//    {
//		Uart1.Enum_TxState ++;
//    }
	
	

	if (Uart1.Enum_TxState >= ENUM_TXSTATE_OK)      //状态发送完毕后自动转为发送空闲
	{
		Uart1.Enum_TxState = ENUM_TXSTATE_IDLE;
	}

	if (Uart1.Enum_TxState == ENUM_TXSTATE_IDLE)
	{
		P_Uart1_En_Low();
	}
	else 
	{
		P_Uart1_En_Hi();
	}

    ECBM_MODBUS_RTU_TIMEOUT_RUN();			//modbus超时逻辑处理
}
#endif

#if defined		UART2_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart2(void) 
Description         :初始化串口2
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Module_Init_Uart2(void)
{
    //RX输出高内部上拉
    P_Uart2_Rx_Hi();
    P_Uart2_Rx_Output();
    P_Uart2_Rx_Enpull();
    
    //TX输出高内部上拉
    P_Uart2_Tx_Hi();
    P_Uart2_Tx_Output();
    P_Uart2_Tx_Enpull();

	//En输出高内部上拉
    P_Uart2_En_Low();
    P_Uart2_En_Output();
    P_Uart2_En_Enpull();
    //Uart2配置  
    Uart2_Config();
}
/****************************************************************************************************
Function Name       :void Uart2_Interrupt(void)
Description         :串口中断函数
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void Uart2_Interrupt(void) 
{
	
    unsigned char i, temp;	

    if ((UART_GetITStatus(UART2, UART_IT_RB) != RESET) && (UART_GetFlagStatus(UART2, UART_FLAG_RB) != RESET)) //接收标志位判断
    {
		temp = UART_RecByte(UART2);
//		uart_receive_input(dat);
    
        Uart2.u8_RxBuffLast = Uart2.u8_RxBuff;
        Uart2.u8_RxBuff = temp;

        if (F_uart2_RxComplete == CF_DISABLE)
        {			
            if ((Uart2.u8_RxBuffLast == C_UART2_RX_HEAD_FIRST) 
            && ((Uart2.u8_RxBuff == C_UART2_RX_HEAD_SECOND03) || (Uart2.u8_RxBuff == C_UART2_RX_HEAD_SECOND06)|| (Uart2.u8_RxBuff == C_UART2_RX_HEAD_SECOND10))
            && (F_uart2_CheckHand == 0))  //避免buff2,3跟0,1一样的问题
            {
                for (i=0; i<UART2_RX_LEN; i++)
                {
                    U8_Uart2_DrvRxBuf[i] = 0;
                }
            
                U8_Uart2_DrvRxBuf[UART2_RX_HEAD_FIRST]  = Uart2.u8_RxBuffLast;
                U8_Uart2_DrvRxBuf[UART2_RX_HEAD_SECOND] = Uart2.u8_RxBuff;
            
                Uart2.u8_RxCnt = 2;
                F_uart2_Receiving = CF_ENABLE;
                Uart2.u8_RxTimerOut = 0;
                F_uart2_CheckHand = 1;
            }
            else if (Uart2.u8_RxCnt >= 2) 
            {
           		 
                U8_Uart2_DrvRxBuf[Uart2.u8_RxCnt++] = Uart2.u8_RxBuff;
                if (Uart2.u8_RxCnt ==3)
                {
	                if (U8_Uart2_DrvRxBuf[1] == 0x03)
	                {
						Uart2.u8_RxNum = U8_Uart2_DrvRxBuf[2] + 5;
	                }
	                else //if (U8_Uart2_DrvRxBuf[1] == 0x06)
	                {
						Uart2.u8_RxNum = 8;
	                }
				}
				
                if (Uart2.u8_RxCnt >= Uart2.u8_RxNum)//UART2_RX_LEN)                  //接收信息字节长度(根据功能需要接收多少个字节,可能是常数可能是变量)
                {
                    F_uart2_RxComplete = CF_ENABLE;
                    F_uart2_Receiving = CF_DISABLE;
                    Uart2.u8_RxTimerOut = 0;
                    F_uart2_CheckHand = 0;
                }
            }
        }	
    } 
    
    if ((UART_GetITStatus(UART2, UART_IT_TB) != RESET) && (UART_GetFlagStatus(UART2, UART_FLAG_TB) != RESET))		//发送标志位判断
    {
        if (Uart2.u8_TxCnt < Uart2.u8_TxNum/*UART2_TX_LEN*/)                          //发送电源板信息12个字节
        {			
            temp = U8_Uart2_TxBuf[Uart2.u8_TxCnt++];		
        }
        else
        {
            UART_ITConfig(UART2, UART_IT_TB, ENUM_DISABLE);
			Uart2.Enum_TxState = ENUM_TXSTATE_OK;
            Uart2.u8_TxCnt = 0;
			
//			if (WiFi.f_Reset && (Uart2.u8_TxNum == 17))
//			{
//				WiFi.f_Reset = 0;
//				CommDisp.Rx.Byte9.var.WifiReset = Enum_DISABLE;
//				CmdInBak.Byte9.var.WifiReset = Enum_DISABLE;
//			}
        }	
    }	
}
/****************************************************************************************************
Function Name       :void    Uart2_SendPackDeal(void)
Description         :串口2发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart2_SendPackDeal(void)
{
    if (F_uart2_TxReady)                            //串口发送空闲时
    {
        F_uart2_TxReady = CF_DISABLE;
        
        Uart2.u8_TxCnt = 1;                         //发送数据包首个字节
        Uart2.Enum_TxState = ENUM_TXSTATE_BUSY;     //发送状态忙
		P_Uart2_En_Hi();
        UART_SendByte(UART2, U8_Uart2_TxBuf[0]);     //首个字节送入串口发送缓存
		UART_ITConfig(UART2, UART_IT_TB, ENUM_ENABLE);    //发送有效

    }
    
    
    if (Uart2.Enum_TxState >= ENUM_TXSTATE_OK + 1)      //状态发送完毕后自动转为发送空闲
    {
        Uart2.Enum_TxState = ENUM_TXSTATE_IDLE;
        P_Uart2_En_Low();
    }
    
    if (Uart2.Enum_TxState == ENUM_TXSTATE_OK)
    {
		Uart2.Enum_TxState ++;
    }
}
#endif

#if defined		UART3_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart3(void) 
Description         :初始化串口3
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Module_Init_Uart3(void)
{
    //RX输出高内部上拉
    P_Uart3_Rx_Hi();
    P_Uart3_Rx_Output();
    P_Uart3_Rx_Enpull();
    
    //TX输出高内部上拉
    P_Uart3_Tx_Hi();
    P_Uart3_Tx_Output();
    P_Uart3_Tx_Enpull();

    //Uart3配置  
    Uart3_Config();
}
/****************************************************************************************************
Function Name       :void Uart3_Interrupt(void)
Description         :串口中断函数
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void Uart3_Interrupt(void) 
{
	
    unsigned char i, temp;	

    if ((UART_GetITStatus(UART3, UART_IT_RB) != RESET) && (UART_GetFlagStatus(UART3, UART_FLAG_RB) != RESET))         //接收标志位判断
    {
		temp = UART_RecByte(UART3);
    
        Uart3.u8_RxBuffLast = Uart3.u8_RxBuff;
        Uart3.u8_RxBuff = temp;

        if (F_uart3_RxComplete == CF_DISABLE)
        {			
            if ((Uart3.u8_RxBuffLast == C_UART3_RX_HEAD_FIRST) && (Uart3.u8_RxBuff == C_UART3_RX_HEAD_SECOND))
            {
                for (i=0; i<UART3_RX_LEN; i++)
                {
                    U8_Uart3_DrvRxBuf[i] = 0;
                }
            
                U8_Uart3_DrvRxBuf[UART3_RX_HEAD_FIRST]  = Uart3.u8_RxBuffLast;
                U8_Uart3_DrvRxBuf[UART3_RX_HEAD_SECOND] = Uart3.u8_RxBuff;
            
                Uart3.u8_RxCnt = 2;
                F_uart3_Receiving = CF_ENABLE;
                Uart3.u8_RxTimerOut = 0;
                
            }
            else if (Uart3.u8_RxCnt >= 2) 
            {
           
                U8_Uart3_DrvRxBuf[Uart3.u8_RxCnt++] = Uart3.u8_RxBuff;									

                if (Uart3.u8_RxCnt >= UART3_RX_LEN)                  //接收信息字节长度(根据功能需要接收多少个字节,可能是常数可能是变量)
                {
                    F_uart3_RxComplete = CF_ENABLE;
                    F_uart3_Receiving = CF_DISABLE;
                    Uart3.u8_RxTimerOut = 0;
                }
            }
        }	
    } 
    
    if ((UART_GetITStatus(UART3, UART_IT_TB) != RESET) && (UART_GetFlagStatus(UART3, UART_FLAG_TB) != RESET))		//发送标志位判断
    {

        if (Uart3.u8_TxCnt < UART3_TX_LEN)                          //发送电源板信息12个字节
        {			
            temp = U8_Uart3_TxBuf[Uart3.u8_TxCnt++];	
			UART_SendByte(UART3, temp);				
        }
        else
        {
            UART_ITConfig(UART3, UART_IT_TB, ENUM_DISABLE);
			Uart3.Enum_TxState = ENUM_TXSTATE_OK;
            Uart3.u8_TxCnt = 0;
        }	
    }	
}
/****************************************************************************************************
Function Name       :void    Uart3_SendPackDeal(void)
Description         :串口2发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart3_SendPackDeal(void)
{
    if (F_uart3_TxReady)                            //串口发送空闲时
    {
        F_uart3_TxReady = CF_DISABLE;
        
        Uart3.u8_TxCnt = 1;                         //发送数据包首个字节
        Uart3.Enum_TxState = ENUM_TXSTATE_BUSY;     //发送状态忙

        UART_SendByte(UART3, U8_Uart3_TxBuf[0]);     //首个字节送入串口发送缓存
		UART_ITConfig(UART3, UART_IT_TB, ENUM_ENABLE);    //发送有效

    }
    
    
    if (Uart3.Enum_TxState >= ENUM_TXSTATE_OK)      //状态发送完毕后自动转为发送空闲
    {
        Uart3.Enum_TxState = ENUM_TXSTATE_IDLE;
    }
}
#endif

#if defined		UART4_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart4(void) 
Description         :初始化串口4
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Module_Init_Uart4(void)
{
    //RX输出高内部上拉
    P_Uart4_Rx_Hi();
    P_Uart4_Rx_Output();
    P_Uart4_Rx_Enpull();
    
    //TX输出高内部上拉
    P_Uart4_Tx_Hi();
    P_Uart4_Tx_Output();
    P_Uart4_Tx_Enpull();

    //Uart4配置  
    Uart4_Config();
}
/****************************************************************************************************
Function Name       :void Uart4_Interrupt(void)
Description         :串口中断函数
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void Uart4_Interrupt(void) 
{
	
    unsigned char i, temp;	

    if ((UART_GetITStatus(UART4, UART_IT_RB) != RESET) && (UART_GetFlagStatus(UART4, UART_FLAG_RB) != RESET))         //接收标志位判断
    {
		temp = UART_RecByte(UART4);
    
        Uart4.u8_RxBuffLast = Uart4.u8_RxBuff;
        Uart4.u8_RxBuff = temp;

        if (F_uart4_RxComplete == CF_DISABLE)
        {			
            if ((Uart4.u8_RxBuffLast == C_UART4_RX_HEAD_FIRST) && (Uart4.u8_RxBuff == C_UART4_RX_HEAD_SECOND))
            {
                for (i=0; i<UART4_RX_LEN; i++)
                {
                    U8_Uart4_DrvRxBuf[i] = 0;
                }
            
                U8_Uart4_DrvRxBuf[UART4_RX_HEAD_FIRST]  = Uart4.u8_RxBuffLast;
                U8_Uart4_DrvRxBuf[UART4_RX_HEAD_SECOND] = Uart4.u8_RxBuff;
            
                Uart4.u8_RxCnt = 2;
                F_uart4_Receiving = CF_ENABLE;
                Uart4.u8_RxTimerOut = 0;
                
            }
            else if (Uart4.u8_RxCnt >= 2) 
            {
           
                U8_Uart4_DrvRxBuf[Uart4.u8_RxCnt++] = Uart4.u8_RxBuff;									

                if (Uart4.u8_RxCnt >= UART4_RX_LEN)                  //接收信息字节长度(根据功能需要接收多少个字节,可能是常数可能是变量)
                {
                    F_uart4_RxComplete = CF_ENABLE;
                    F_uart4_Receiving = CF_DISABLE;
                    Uart4.u8_RxTimerOut = 0;
                }
            }
        }	
    } 
    
    if ((UART_GetITStatus(UART4, UART_IT_TB) != RESET) && (UART_GetFlagStatus(UART4, UART_FLAG_TB) != RESET))		//发送标志位判断
    {

        if (Uart4.u8_TxCnt < UART4_TX_LEN)                          //发送电源板信息12个字节
        {			
            temp = U8_Uart4_TxBuf[Uart4.u8_TxCnt++];	
			UART_SendByte(UART4, temp);				
        }
        else
        {
            UART_ITConfig(UART4, UART_IT_TB, ENUM_DISABLE);
			Uart4.Enum_TxState = ENUM_TXSTATE_OK;
            Uart4.u8_TxCnt = 0;
        }	
    }	
}
/****************************************************************************************************
Function Name       :void    Uart4_SendPackDeal(void)
Description         :串口2发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart4_SendPackDeal(void)
{
    if (F_uart4_TxReady)                            //串口发送空闲时
    {
        F_uart4_TxReady = CF_DISABLE;
        
        Uart4.u8_TxCnt = 1;                         //发送数据包首个字节
        Uart4.Enum_TxState = ENUM_TXSTATE_BUSY;     //发送状态忙

        UART_SendByte(UART4, U8_Uart4_TxBuf[0]);     //首个字节送入串口发送缓存
		UART_ITConfig(UART4, UART_IT_TB, ENUM_ENABLE);    //发送有效

    }
    
    
    if (Uart4.Enum_TxState >= ENUM_TXSTATE_OK)      //状态发送完毕后自动转为发送空闲
    {
        Uart4.Enum_TxState = ENUM_TXSTATE_IDLE;
    }
}
#endif

#if defined		UART5_ENABLE
/****************************************************************************************************
Function Name       :void    Module_Init_Uart5(void) 
Description         :初始化串口5
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Module_Init_Uart5(void)
{
    //RX输出高内部上拉
    P_Uart5_Rx_Hi();
    P_Uart5_Rx_Output();
    P_Uart5_Rx_Enpull();
    
    //TX输出高内部上拉
    P_Uart5_Tx_Hi();
    P_Uart5_Tx_Output();
    P_Uart5_Tx_Enpull();

    //Uart5配置  
    Uart5_Config();
}
/****************************************************************************************************
Function Name       :void Uart5_Interrupt(void)
Description         :串口中断函数
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void Uart5_Interrupt(void) 
{
	
    unsigned char i, temp;	

    if ((UART_GetITStatus(UART5, UART_IT_RB) != RESET) && (UART_GetFlagStatus(UART5, UART_FLAG_RB) != RESET))         //接收标志位判断
    {
		temp = UART_RecByte(UART5);
    
        Uart5.u8_RxBuffLast = Uart5.u8_RxBuff;
        Uart5.u8_RxBuff = temp;

        if (F_uart5_RxComplete == CF_DISABLE)
        {			
            if ((Uart5.u8_RxBuffLast == C_UART5_RX_HEAD_FIRST) && (Uart5.u8_RxBuff == C_UART5_RX_HEAD_SECOND))
            {
                for (i=0; i<UART5_RX_LEN; i++)
                {
                    U8_Uart5_DrvRxBuf[i] = 0;
                }
            
                U8_Uart5_DrvRxBuf[UART5_RX_HEAD_FIRST]  = Uart5.u8_RxBuffLast;
                U8_Uart5_DrvRxBuf[UART5_RX_HEAD_SECOND] = Uart5.u8_RxBuff;
            
                Uart5.u8_RxCnt = 2;
                F_uart5_Receiving = CF_ENABLE;
                Uart5.u8_RxTimerOut = 0;
                
            }
            else if (Uart5.u8_RxCnt >= 2) 
            {
           
                U8_Uart5_DrvRxBuf[Uart5.u8_RxCnt++] = Uart5.u8_RxBuff;									

                if (Uart5.u8_RxCnt >= UART5_RX_LEN)                  //接收信息字节长度(根据功能需要接收多少个字节,可能是常数可能是变量)
                {
                    F_uart5_RxComplete = CF_ENABLE;
                    F_uart5_Receiving = CF_DISABLE;
                    Uart5.u8_RxTimerOut = 0;
                }
            }
        }	
    } 
    
    if ((UART_GetITStatus(UART5, UART_IT_TB) != RESET) && (UART_GetFlagStatus(UART5, UART_FLAG_TB) != RESET))		//发送标志位判断
    {

        if (Uart5.u8_TxCnt < UART5_TX_LEN)                          //发送电源板信息12个字节
        {			
            temp = U8_Uart5_TxBuf[Uart5.u8_TxCnt++];	
			UART_SendByte(UART5, temp);				
        }
        else
        {
            UART_ITConfig(UART5, UART_IT_TB, DISABLE);
			Uart5.Enum_TxState = ENUM_TXSTATE_OK;
            Uart5.u8_TxCnt = 0;
        }	
    }	
}
/****************************************************************************************************
Function Name       :void    Uart5_SendPackDeal(void)
Description         :串口2发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart5_SendPackDeal(void)
{
    if (F_uart5_TxReady)                            //串口发送空闲时
    {
        F_uart5_TxReady = CF_DISABLE;
        
        Uart5.u8_TxCnt = 1;                         //发送数据包首个字节
        Uart5.Enum_TxState = ENUM_TXSTATE_BUSY;     //发送状态忙

        UART_SendByte(UART5, U8_Uart5_TxBuf[0]);     //首个字节送入串口发送缓存
		UART_ITConfig(UART5, UART_IT_TB, ENABLE);    //发送有效

    }
    
    
    if (Uart5.Enum_TxState >= ENUM_TXSTATE_OK)      //状态发送完毕后自动转为发送空闲
    {
        Uart5.Enum_TxState = ENUM_TXSTATE_IDLE;
    }
}
#endif
/****************************************************************************************************
Function Name       :void    Module_Init_Uart(void) 
Description         :初始化串口
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Module_Init_Uart(void)
{
    #if defined		UART0_ENABLE
    Module_Init_Uart0();
    #endif
    
    #if defined		UART1_ENABLE
    Module_Init_Uart1();
    #endif
    
    #if defined		UART2_ENABLE
    Module_Init_Uart2();
    #endif
    
    #if defined		UART3_ENABLE
    Module_Init_Uart3();
    #endif
	
    #if defined		UART4_ENABLE
    Module_Init_Uart4();
    #endif	
	
    #if defined		UART5_ENABLE
    Module_Init_Uart5();
    #endif		
}
