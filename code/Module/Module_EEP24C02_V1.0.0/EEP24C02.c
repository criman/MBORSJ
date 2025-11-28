/*===================================================================================================
                		Copyright(C) 2011-2099.  SUMRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: IICMIO.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023-01-10
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/

#include	"main.h"


STRUCT_EEP    EEP;

/****************************************************************************************************
Function Name       :void Module_Init_IICM(void)
Description         :模拟iic初始化IO
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Module_Init_IICM(void)
{
    //模拟I2C口
    P_IICM_SCL_H();  				//拉高
    P_IICM_SCL_OUT();
    P_IICM_SCL_DISPULL();

    P_IICM_SDA_H();					//拉高
    P_IICM_SDA_OUT();	
    P_IICM_SDA_DISPULL();	
	
	EEP.Step = ENUM_STEP_IDLE;
}
/****************************************************************************************************
Function Name       :void IICM_Delay(U8 us)
Description         :SCL,SDA信号延时
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
static void IICM_Delay(U8 us) //只允许在当前文件下使用
{
    U8 t = us; 

    while(t) 
    {
        t--;
    }
}
/****************************************************************************************************
Function Name       :void IICM_Start(void)
Description         :产生IIC起始信号 
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void IICM_Start(void)  
{  
    P_IICM_SDA_H();
	IICM_Delay(C_IICM_DELAY); 			//电平维持4.7us以上
	
    P_IICM_SCL_H(); 
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上

    P_IICM_SDA_L();						
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上

    P_IICM_SCL_L(); 					 
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上
} 
/****************************************************************************************************
Function Name       :void IICM_Stop(void)
Description         :产生IIC停止信号  
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void IICM_Stop(void)  
{  
    P_IICM_SDA_L();						
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上 
	   
    P_IICM_SCL_H();  
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上
    
    P_IICM_SDA_H();						 
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上                                
} 
/****************************************************************************************************
Function Name       :void    IIC_SetAck(void)
Description         :输出应答信号
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    IIC_SetAck(void)
{
    P_IICM_SDA_L();						
    IICM_Delay(C_IICM_DELAY); 			//电平维持4.7us以上

    P_IICM_SCL_H();  
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上	
	
    P_IICM_SCL_L();  
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上		
}
/****************************************************************************************************
Function Name       :void    IIC_SetAck(void)
Description         :输出不应答信号
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    IIC_SetNoAck(void)
{
    P_IICM_SDA_H();						
    IICM_Delay(C_IICM_DELAY); 			//电平维持4.7us以上

    P_IICM_SCL_H();  
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上	
	
    P_IICM_SCL_L();  
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上		
}
/****************************************************************************************************
Function Name       :void    IIC_TestAck(void)
Description         :获取应答信号
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    IIC_TestAck(void)
{
    U8    i;
	U8    chAck_data = 0;
	
	P_IICM_SDA_H();
	IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上	

    P_IICM_SCL_H();  
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上	

	P_IICM_SDA_IN();					//转输入
	
	for (i=0; i<100; i++)
	{
		//喂狗(若需要)
		if (Read_SDA() == 0)
		{
			chAck_data = 1;
			break;
		}
	}
	
	P_IICM_SDA_OUT();					//转输出
	
    P_IICM_SCL_L();  
    IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上	

	return    chAck_data;
}
/****************************************************************************************************
Function Name       :void IIC_Send_Byte(U8 byte)  
Description         :IIC发送一个字节 
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void IIC_Send_Byte(U8 byte)  
{                          
    U8 i;   
        
    for(i=0;i<8;i++)  
    {                
        if(byte & 0x80) 
        {
            P_IICM_SDA_H();
        }  
        else 
        { 
            P_IICM_SDA_L(); 
        }
        byte<<=1;  
        IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上
               
        P_IICM_SCL_H();  
        IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上  
		
        P_IICM_SCL_L();    
        IICM_Delay(C_IICM_DELAY);  			//电平维持4.7us以上 
    }      
}         
/****************************************************************************************************
Function Name       :U8    IIC_Read_Byte(void)   
Description         :IIC读取一个字节 
Input               :无
Return              :返回读取结果
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/    
U8    IIC_Read_Byte(void)  
{  
    U8 i,receive = 0;  
   
    P_IICM_SDA_IN();								//SDA设置为输入
    
    for(i=0;i<8;i++ )  
    {  
        P_IICM_SCL_H(); 
        IICM_Delay(C_IICM_DELAY);  					//电平维持4.7us以上
        
        receive<<=1;  
        if(Read_SDA())	
        {	
            receive++;     
        }     
		IICM_Delay(C_IICM_DELAY);  					//电平维持4.7us以上
		
        P_IICM_SCL_L();   							//离开for循环后SCL必须为保持低，否则可能会误触发stop信号； 
        IICM_Delay(C_IICM_DELAY);  					//电平维持4.7us以上      
    } 

	P_IICM_SDA_OUT();								//转输出 
    
    return receive;  
} 
/****************************************************************************************************
Function Name       :void    Write_24C02(U8 *addr_MCU, U8 Address, U8 DataCnt)
Description         :写入24C02数据
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Write_24C02(U8 *addr_MCU, U8 Address, U8 DataCnt)
{
	U8 i;
	
	IICM_Start();
	
	IIC_Send_Byte(SLAVE_ADDR);	
	if (!IIC_TestAck())
	{
		IICM_Stop();
		return;
	}
	
	IIC_Send_Byte(Address);
	if (!IIC_TestAck())
	{
		IICM_Stop();
		return;
	}

	do
	{
		IIC_Send_Byte(*addr_MCU);
		if (!IIC_TestAck())
		{
			IICM_Stop();
			return;
		}

		DataCnt--;
		addr_MCU++;
				
		
	}
	while (DataCnt > 0);
	
	IICM_Stop();
	

	i = 0;
	while (i<10)	//24c02 write time delay 10ms
	{
		if (EEP.f_1ms)
		{
			EEP.f_1ms = 0;
			i++;
		}
	}
}
/****************************************************************************************************
Function Name       :void    Read_24C02(U8 *addr_MCU, U8 Address, U8 DataCnt)
Description         :读取24C02数据
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Read_24C02(U8 *addr_MCU, U8 Address, U8 DataCnt)
{
	IICM_Start();

	IIC_Send_Byte(SLAVE_ADDR);		   //write
	if (!IIC_TestAck())
	{
		IICM_Stop();
		return;
	}

	IIC_Send_Byte(Address);
	if (!IIC_TestAck())
	{
		IICM_Stop();
		return;
	}

	IICM_Start();
	
	IIC_Send_Byte(SLAVE_ADDR|0x01);		//read
	if (!IIC_TestAck())
	{
		IICM_Stop();
		return;
	}

	do
	{
		*addr_MCU = IIC_Read_Byte();		
		
		DataCnt--;
		if (DataCnt > 0)
		{
			IIC_SetAck();
		}
		addr_MCU++;
	}
	while (DataCnt > 0);
	
	IIC_SetNoAck();
	
	IICM_Stop();
}
