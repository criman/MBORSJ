/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: FourWay.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/09/13
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_FOURWAY    FourWay;         //四通阀

/****************************************************************************************************
Function Name       :void    Init_FourWay(void)
Description         :四通阀控制初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_FourWay(void)
{
    P_FourWay_Off();  
    P_FourWay_Output();	
	P_FourWay_Dispull();	
}
/****************************************************************************************************
Function Name       :void    Log_FourWay(void)
Description         :四通阀逻辑处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Log_FourWay(void)
{
	if(l_contData.four_is !=0)
    {
            if(l_contData.four_is ==1)
            {
                FourWay.f_DrvOn = ON;
            }
            else
            {
                FourWay.f_DrvOn = OFF;
            }
    }
    else
    {
        if (FourWay.f_DrvOn == OFF)
        {
            if (FourWay.f_AppOn == ON) 
//            && (PowEn12V.f_DrvOn == ON) 		//无低功耗
//            && (PowEnPTCB.f_DrvOn == ON))		
            {
                if (Defrost.f_Enable 
                || ((Comp.u16_RestartDelay <= 50) 
                || ((Comp.u8_SelTestDelay > 0 ) &&(Comp.u8_SelTestDelay <= 50))))
                {
                    //四通阀开启瞬间
                    
                    if (Comp.f_DrvOn == ON)//还需判断压缩机是否运行，运行的需关停压缩机四通阀再动作
                    {
                        Comp.f_FourWayAbn = 1;	//四通阀开启逼停压缩机
                    }
                    else
                    {
                        if (Comp.u16_RestartDelay < 50)	//保证四通阀比压缩机提前5秒工作
                        {
                            Comp.u16_RestartDelay = 50;
                        }
                        
                        FourWay.f_DrvOn = ON;
                    }
                }
            }
            
        }
        else
        {
            if (FourWay.f_AppOn == OFF) 
            {
                if (Defrost.f_Enable || (FourWay.u16_Delay == 0))
                {
                    //四通阀关闭瞬间
                    
                    if (Comp.f_DrvOn == ON)	//还需判断压缩机是否运行，关闭时的需关停压缩机四通阀再动作
                    {
                        Comp.f_FourWayAbn = 1;	//四通阀开启逼停压缩机					
                    }
                    else
                    {
                        FourWay.f_DrvOn = OFF;
                    }				
                }
            }	
        }
    }
}
/****************************************************************************************************
Function Name       :void    Drv_FourWay(void)
Description         :四通阀驱动处理
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Drv_FourWay(void)
{
	if ((FourWay.f_DrvOn)  || (FourWay.f_ForceDrvOn))	
	{
		P_FourWay_On();
	}
	else					
	{
		P_FourWay_Off();
	}
}
/****************************************************************************************************
Function Name       :void    Func_FourWay(void)
Description         :四通阀功能
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_FourWay(void)
{
	Log_FourWay();
	Drv_FourWay();
}
