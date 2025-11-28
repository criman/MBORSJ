/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Uart.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/04/28
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/

#ifndef    _UART_H_

#define    _UART_H_

#include    "Uart_app.h"

//===================================================================================================//
//选择UART0控制端口
//---------------------------------------------------------------------------------------------------//
#define    UART0_ENABLE                       //选择打开定义,否不使用则请屏蔽
//---------------------------------------------------------------------------------------------------//
#define    P_Uart0_Rx_Hi()                    DEFINE_PB0_HI
#define    P_Uart0_Rx_Low()                   DEFINE_PB0_LOW
#define    P_Uart0_Rx_Output()                DEFINE_PB0_OUTPUT
#define    P_Uart0_Rx_Input()                 DEFINE_PB0_INPUT
#define    P_Uart0_Rx_Enpull()                DEFINE_PB0_ENPULLUP
#define    P_Uart0_Rx_Dispull()               DEFINE_PB0_DISPULLUP
//---------------------------------------------------------------------------------------------------//
#define    P_Uart0_Tx_Hi()                    DEFINE_PB1_HI
#define    P_Uart0_Tx_Low()                   DEFINE_PB1_LOW
#define    P_Uart0_Tx_Output()                DEFINE_PB1_OUTPUT
#define    P_Uart0_Tx_Input()                 DEFINE_PB1_INPUT
#define    P_Uart0_Tx_Enpull()                DEFINE_PB1_ENPULLUP
#define    P_Uart0_Tx_Dispull()               DEFINE_PB1_DISPULLUP

//---------------------------------------------------------------------------------------------------//
#define    P_Uart0_En_Hi()                    DEFINE_PB2_HI
#define    P_Uart0_En_Low()                   DEFINE_PB2_LOW
#define    P_Uart0_En_Output()                DEFINE_PB2_OUTPUT
#define    P_Uart0_En_Input()                 DEFINE_PB2_INPUT
#define    P_Uart0_En_Enpull()                DEFINE_PB2_ENPULLUP
#define    P_Uart0_En_Dispull()               DEFINE_PB2_DISPULLUP

//===================================================================================================//
//选择UART1控制端口
//---------------------------------------------------------------------------------------------------//
//#define    UART1_ENABLE                       //选择打开定义,否不使用则请屏蔽
//---------------------------------------------------------------------------------------------------//
#define    P_Uart1_Rx_Hi()                    DEFINE_PB2_HI
#define    P_Uart1_Rx_Low()                   DEFINE_PB2_LOW
#define    P_Uart1_Rx_Output()                DEFINE_PB2_OUTPUT
#define    P_Uart1_Rx_Input()                 DEFINE_PB2_INPUT
#define    P_Uart1_Rx_Enpull()                DEFINE_PB2_ENPULLUP
#define    P_Uart1_Rx_Dispull()               DEFINE_PB2_DISPULLUP
//---------------------------------------------------------------------------------------------------//
#define    P_Uart1_Tx_Hi()                    DEFINE_PB3_HI
#define    P_Uart1_Tx_Low()                   DEFINE_PB3_LOW
#define    P_Uart1_Tx_Output()                DEFINE_PB3_OUTPUT
#define    P_Uart1_Tx_Input()                 DEFINE_PB3_INPUT
#define    P_Uart1_Tx_Enpull()                DEFINE_PB3_ENPULLUP
#define    P_Uart1_Tx_Dispull()               DEFINE_PB3_DISPULLUP

#define    P_Uart1_En_Hi()                    DEFINE_PB7_HI
#define    P_Uart1_En_Low()                   DEFINE_PB7_LOW
#define    P_Uart1_En_Output()                DEFINE_PB7_OUTPUT
#define    P_Uart1_En_Input()                 DEFINE_PB7_INPUT
#define    P_Uart1_En_Enpull()                DEFINE_PB7_ENPULLUP
#define    P_Uart1_En_Dispull()               DEFINE_PB7_DISPULLUP

//===================================================================================================//
//选择UART2控制端口
//---------------------------------------------------------------------------------------------------//
//#define    UART2_ENABLE                       //选择打开定义,否不使用则请屏蔽
//---------------------------------------------------------------------------------------------------//
#define    P_Uart2_Rx_Hi()                    DEFINE_PB4_HI
#define    P_Uart2_Rx_Low()                   DEFINE_PB4_LOW
#define    P_Uart2_Rx_Output()                DEFINE_PB4_OUTPUT
#define    P_Uart2_Rx_Input()                 DEFINE_PB4_INPUT
#define    P_Uart2_Rx_Enpull()                DEFINE_PB4_ENPULLUP
#define    P_Uart2_Rx_Dispull()               DEFINE_PB4_DISPULLUP
//---------------------------------------------------------------------------------------------------//
#define    P_Uart2_Tx_Hi()                    DEFINE_PB5_HI
#define    P_Uart2_Tx_Low()                   DEFINE_PB5_LOW
#define    P_Uart2_Tx_Output()                DEFINE_PB5_OUTPUT
#define    P_Uart2_Tx_Input()                 DEFINE_PB5_INPUT
#define    P_Uart2_Tx_Enpull()                DEFINE_PB5_ENPULLUP
#define    P_Uart2_Tx_Dispull()               DEFINE_PB5_DISPULLUP
//---------------------------------------------------------------------------------------------------//
#define    P_Uart2_En_Hi()                    DEFINE_PB8_HI
#define    P_Uart2_En_Low()                   DEFINE_PB8_LOW
#define    P_Uart2_En_Output()                DEFINE_PB8_OUTPUT
#define    P_Uart2_En_Input()                 DEFINE_PB8_INPUT
#define    P_Uart2_En_Enpull()                DEFINE_PB8_ENPULLUP
#define    P_Uart2_En_Dispull()               DEFINE_PB8_DISPULLUP

//===================================================================================================//
//选择UART3控制端口
//---------------------------------------------------------------------------------------------------//
//#define    UART3_ENABLE                       //选择打开定义,否不使用则请屏蔽

//#define UART3_lhh //lcx 20240427 
//---------------------------------------------------------------------------------------------------//
#define    P_Uart3_Rx_Hi()                    DEFINE_PB0_HI
#define    P_Uart3_Rx_Low()                   DEFINE_PB0_LOW
#define    P_Uart3_Rx_Output()                DEFINE_PB0_OUTPUT
#define    P_Uart3_Rx_Input()                 DEFINE_PB0_INPUT
#define    P_Uart3_Rx_Enpull()                DEFINE_PB0_ENPULLUP
#define    P_Uart3_Rx_Dispull()               DEFINE_PB0_DISPULLUP
//---------------------------------------------------------------------------------------------------//
#define    P_Uart3_Tx_Hi()                    DEFINE_PB1_HI
#define    P_Uart3_Tx_Low()                   DEFINE_PB1_LOW
#define    P_Uart3_Tx_Output()                DEFINE_PB1_OUTPUT
#define    P_Uart3_Tx_Input()                 DEFINE_PB1_INPUT
#define    P_Uart3_Tx_Enpull()                DEFINE_PB1_ENPULLUP
#define    P_Uart3_Tx_Dispull()               DEFINE_PB1_DISPULLUP
//===================================================================================================//
//===================================================================================================//
//选择UART4控制端口
//---------------------------------------------------------------------------------------------------//
//#define    UART4_ENABLE                       //选择打开定义,否不使用则请屏蔽
//---------------------------------------------------------------------------------------------------//
#define    P_Uart4_Rx_Hi()                    DEFINE_PB9_HI
#define    P_Uart4_Rx_Low()                   DEFINE_PB9_LOW
#define    P_Uart4_Rx_Output()                DEFINE_PB9_OUTPUT
#define    P_Uart4_Rx_Input()                 DEFINE_PB9_INPUT
#define    P_Uart4_Rx_Enpull()                DEFINE_PB9_ENPULLUP
#define    P_Uart4_Rx_Dispull()               DEFINE_PB9_DISPULLUP
//---------------------------------------------------------------------------------------------------//
#define    P_Uart4_Tx_Hi()                    DEFINE_PB10_HI
#define    P_Uart4_Tx_Low()                   DEFINE_PB10_LOW
#define    P_Uart4_Tx_Output()                DEFINE_PB10_OUTPUT
#define    P_Uart4_Tx_Input()                 DEFINE_PB10_INPUT
#define    P_Uart4_Tx_Enpull()                DEFINE_PB10_ENPULLUP
#define    P_Uart4_Tx_Dispull()               DEFINE_PB10_DISPULLUP
//===================================================================================================//
//选择UART5控制端口
//---------------------------------------------------------------------------------------------------//
//#define    UART5_ENABLE                       //选择打开定义,否不使用则请屏蔽
//---------------------------------------------------------------------------------------------------//
#define    P_Uart5_Rx_Hi()                    DEFINE_PA2_HI
#define    P_Uart5_Rx_Low()                   DEFINE_PA2_LOW
#define    P_Uart5_Rx_Output()                DEFINE_PA2_OUTPUT
#define    P_Uart5_Rx_Input()                 DEFINE_PA2_INPUT
#define    P_Uart5_Rx_Enpull()                DEFINE_PA2_ENPULLUP
#define    P_Uart5_Rx_Dispull()               DEFINE_PA2_DISPULLUP
//---------------------------------------------------------------------------------------------------//
#define    P_Uart5_Tx_Hi()                    DEFINE_PA1_HI
#define    P_Uart5_Tx_Low()                   DEFINE_PA1_LOW
#define    P_Uart5_Tx_Output()                DEFINE_PA1_OUTPUT
#define    P_Uart5_Tx_Input()                 DEFINE_PA1_INPUT
#define    P_Uart5_Tx_Enpull()                DEFINE_PA1_ENPULLUP
#define    P_Uart5_Tx_Dispull()               DEFINE_PA1_DISPULLUP
//===================================================================================================//
//---------------------------------------------------------------------------------------------------//
//串口0标志位
//---------------------------------------------------------------------------------------------------//
extern		TYPE_BYTE			    		  STRUCT_uart0_flag0;				  //串口0标志位
#define		U8_uart0_flag0					  STRUCT_uart0_flag0.byte
#define		F_uart0_TxReady 				  STRUCT_uart0_flag0.bits.b0          //串口0发送准备
#define		F_uart0_RxComplete				  STRUCT_uart0_flag0.bits.b1          //串口0接收完成
#define		F_uart0_Receiving				  STRUCT_uart0_flag0.bits.b2          //串口0接收中
#define		F_uart0_TimeOut					  STRUCT_uart0_flag0.bits.b3          //串口0通信超时
#define		F_uart0_CommErr					  STRUCT_uart0_flag0.bits.b4          //串口0通信故障标志
//---------------------------------------------------------------------------------------------------//
//串口1标志位
//---------------------------------------------------------------------------------------------------//
extern		TYPE_BYTE			    		  STRUCT_uart1_flag0;				  //串口1标志位
#define		U8_uart1_flag0					  STRUCT_uart1_flag0.byte
#define		F_uart1_TxReady 				  STRUCT_uart1_flag0.bits.b0          //串口1发送准备
#define		F_uart1_RxComplete				  STRUCT_uart1_flag0.bits.b1          //串口1接收完成
#define		F_uart1_Receiving				  STRUCT_uart1_flag0.bits.b2          //串口1接收中
#define		F_uart1_TimeOut					  STRUCT_uart1_flag0.bits.b3          //串口1通信超时
#define		F_uart1_CommErr					  STRUCT_uart1_flag0.bits.b4          //串口1通信故障标志
//---------------------------------------------------------------------------------------------------//
//串口2标志位
//---------------------------------------------------------------------------------------------------//
extern		TYPE_BYTE			    		  STRUCT_uart2_flag0;				  //串口2标志位
#define		U8_uart2_flag0					  STRUCT_uart2_flag0.byte
#define		F_uart2_TxReady 				  STRUCT_uart2_flag0.bits.b0          //串口2发送准备
#define		F_uart2_RxComplete				  STRUCT_uart2_flag0.bits.b1          //串口2接收完成
#define		F_uart2_Receiving				  STRUCT_uart2_flag0.bits.b2          //串口2接收中
#define		F_uart2_TimeOut					  STRUCT_uart2_flag0.bits.b3          //串口2通信超时
#define		F_uart2_CommErr					  STRUCT_uart2_flag0.bits.b4          //串口2通信故障标志
#define		F_uart2_CheckHand				  STRUCT_uart2_flag0.bits.b4          //检查头码

//---------------------------------------------------------------------------------------------------//
//串口3标志位
//---------------------------------------------------------------------------------------------------//
extern		TYPE_BYTE			    		  STRUCT_uart3_flag0;				  //串口3标志位
#define		U8_uart3_flag0					  STRUCT_uart3_flag0.byte
#define		F_uart3_TxReady 				  STRUCT_uart3_flag0.bits.b0          //串口3发送准备
#define		F_uart3_RxComplete				  STRUCT_uart3_flag0.bits.b1          //串口3接收完成
#define		F_uart3_Receiving				  STRUCT_uart3_flag0.bits.b2          //串口3接收中
#define		F_uart3_TimeOut					  STRUCT_uart3_flag0.bits.b3          //串口3通信超时
#define		F_uart3_CommErr					  STRUCT_uart3_flag0.bits.b4          //串口3通信故障标志
//---------------------------------------------------------------------------------------------------//
//串口4标志位
//---------------------------------------------------------------------------------------------------//
extern		TYPE_BYTE			    		  STRUCT_uart4_flag0;				  //串口4标志位
#define		U8_uart4_flag0					  STRUCT_uart4_flag0.byte
#define		F_uart4_TxReady 				  STRUCT_uart4_flag0.bits.b0          //串口4发送准备
#define		F_uart4_RxComplete				  STRUCT_uart4_flag0.bits.b1          //串口4接收完成
#define		F_uart4_Receiving				  STRUCT_uart4_flag0.bits.b2          //串口4接收中
#define		F_uart4_TimeOut					  STRUCT_uart4_flag0.bits.b3          //串口4通信超时
#define		F_uart4_CommErr					  STRUCT_uart4_flag0.bits.b4          //串口4通信故障标志
//---------------------------------------------------------------------------------------------------//
//串口5标志位
//---------------------------------------------------------------------------------------------------//
extern		TYPE_BYTE			    		  STRUCT_uart5_flag0;				  //串口5标志位
#define		U8_uart5_flag0					  STRUCT_uart5_flag0.byte
#define		F_uart5_TxReady 				  STRUCT_uart5_flag0.bits.b0          //串口5发送准备
#define		F_uart5_RxComplete				  STRUCT_uart5_flag0.bits.b1          //串口5接收完成
#define		F_uart5_Receiving				  STRUCT_uart5_flag0.bits.b2          //串口5接收中
#define		F_uart5_TimeOut					  STRUCT_uart5_flag0.bits.b3          //串口5通信超时
#define		F_uart5_CommErr					  STRUCT_uart5_flag0.bits.b4          //串口5通信故障标志
//---------------------------------------------------------------------------------------------------//
//===================================================================================================//
//---------------------------------------------------------------------------------------------------//
//串口结构体
//---------------------------------------------------------------------------------------------------//
typedef    enum
{
    ENUM_TXSTATE_IDLE,		                  //没有接收到任何有效数据
    ENUM_TXSTATE_BUSY,		                  //接收正在进行中，忙
    ENUM_TXSTATE_OK,	                      //接收完成    
}ENUM_TXSTATE;

typedef    struct
{
    ENUM_TXSTATE    Enum_TxState;             //发送状态
    U8              u8_TxCnt;                 //发送字节数目计数
    U8              u8_TxNum;                 //需要发送字节的个数
    U8              u8_RxCnt;                 //接收字节数目计数
    U8              u8_RxNum;                 //需要接收字节的个数
    U8              u8_RxTimerOut;            //接收超时计时
    U8              u8_RxBuff;                //串口本次接收数据
    U8              u8_RxBuffLast;            //串口上一次接收数据
    U16             u16_AbnormalCount;        //通信异常计时-复位
    U16             u16_ErrCount;             //通信异常计时-标志
	U8				u8_WaitCount;			  //发送间隔时间
	U8				f_txok;					  //接收信息后开始发送标志
}STRUCT_UART;
extern    STRUCT_UART    Uart0;
extern    STRUCT_UART    Uart1;
extern    STRUCT_UART    Uart2;
extern    STRUCT_UART    Uart3;
extern    STRUCT_UART    Uart4;
extern    STRUCT_UART    Uart5;
//---------------------------------------------------------------------------------------------------//
//===================================================================================================//
//---------------------------------------------------------------------------------------------------//
extern    U8             U8_Uart0_TxBuf[UART0_TX_LEN];           //串口0发送驱动层数据缓存
extern    U8             U8_Uart0_AppTxBuf[UART0_TX_LEN];        //串口0发送应用层数据缓存
extern    U8             U8_Uart0_DrvRxBuf[UART0_RX_LEN];        //串口0接收驱动层数据缓存
extern    U8             U8_Uart0_RxBuf[UART0_RX_LEN];           //串口0接收应用层数据缓存
//---------------------------------------------------------------------------------------------------//
extern    U8             U8_Uart1_TxBuf[UART1_TX_LEN];           //串口1发送驱动层数据缓存
extern    U8             U8_Uart1_AppTxBuf[UART1_TX_LEN];        //串口1发送应用层数据缓存
extern    U8             U8_Uart1_DrvRxBuf[UART1_RX_LEN];        //串口1接收驱动层数据缓存
extern    U8             U8_Uart1_RxBuf[UART1_RX_LEN];           //串口1接收应用层数据缓存 
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
extern    U8             U8_Uart2_TxBuf[UART2_TX_LEN];           //串口2发送驱动层数据缓存
extern    U8             U8_Uart2_AppTxBuf[UART2_TX_LEN];        //串口2发送应用层数据缓存
extern    U8             U8_Uart2_DrvRxBuf[UART2_RX_LEN];        //串口2接收驱动层数据缓存
extern    U8             U8_Uart2_RxBuf[UART2_RX_LEN];           //串口2接收应用层数据缓存 
//---------------------------------------------------------------------------------------------------//
extern    U8             U8_Uart3_TxBuf[UART3_TX_LEN];           //串口3发送驱动层数据缓存
extern    U8             U8_Uart3_AppTxBuf[UART3_TX_LEN];        //串口3发送应用层数据缓存
extern    U8             U8_Uart3_DrvRxBuf[UART3_RX_LEN];        //串口3接收驱动层数据缓存
extern    U8             U8_Uart3_RxBuf[UART3_RX_LEN];           //串口3接收应用层数据缓存 
//---------------------------------------------------------------------------------------------------//
extern    U8             U8_Uart4_TxBuf[UART4_TX_LEN];           //串口4发送驱动层数据缓存
extern    U8             U8_Uart4_AppTxBuf[UART4_TX_LEN];        //串口4发送应用层数据缓存
extern    U8             U8_Uart4_DrvRxBuf[UART4_RX_LEN];        //串口4接收驱动层数据缓存
extern    U8             U8_Uart4_RxBuf[UART4_RX_LEN];           //串口4接收应用层数据缓存 
//---------------------------------------------------------------------------------------------------//
extern    U8             U8_Uart5_TxBuf[UART5_TX_LEN];           //串口5发送驱动层数据缓存
extern    U8             U8_Uart5_AppTxBuf[UART5_TX_LEN];        //串口5发送应用层数据缓存
extern    U8             U8_Uart5_DrvRxBuf[UART5_RX_LEN];        //串口5接收驱动层数据缓存
extern    U8             U8_Uart5_RxBuf[UART5_RX_LEN];           //串口5接收应用层数据缓存 
//===================================================================================================//

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
void    Uart0_Interrupt(void);
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
void    Uart0_SendPackDeal(void);
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
void    Uart1_Interrupt(void);
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
void    Uart1_SendPackDeal(void);
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
void    Uart2_Interrupt(void);
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
void    Uart2_SendPackDeal(void);
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
void    Uart3_Interrupt(void);
/****************************************************************************************************
Function Name       :void    Uart3_SendPackDeal(void)
Description         :串口3发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart3_SendPackDeal(void);
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
void    Uart4_Interrupt(void);
/****************************************************************************************************
Function Name       :void    Uart4_SendPackDeal(void)
Description         :串口4发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart4_SendPackDeal(void);
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
void    Uart5_Interrupt(void);
/****************************************************************************************************
Function Name       :void    Uart5_SendPackDeal(void)
Description         :串口5发送数据包处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Uart5_SendPackDeal(void);
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
void    Module_Init_Uart(void);




//---------------------------------------------------------------------------------------------------//
//串口3,lhh
//---------------------------------------------------------------------------------------------------//

extern unsigned char g_txbuf[0xFF];            //??????
extern unsigned char g_tx_length;            //??????
extern unsigned char g_tx_count;             //??????

extern unsigned char g_rxbuf[0xFF];            //??????
extern unsigned char g_rx_length;            //??????
extern unsigned char g_rx_count;             //??????
extern unsigned char g_rx_time;              //????
extern unsigned char g_rx_finish_flag;       //??????
extern unsigned char g_rx_start_flag;        //??????


extern unsigned char g_16rx_length;

extern unsigned char g_crcbuf[2];

//lhh-------------------------------------------------
void    Uart3_Init(void);
void Uart3_Interrupt_lhh(void);

//----------------------------------------------------




#endif
