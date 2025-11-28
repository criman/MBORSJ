/*===================================================================================================
                		Copyright(C) 2011-2099.  SUMRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: swing.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/03/10
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef		_SWING_H_

#define		_SWING_H_

#define		C_SWING_OFFDELAY				400			//风门在风机关闭4s后关闭 (10ms一次)

typedef    struct
{
    U16 	u16_offdelay;		//风门延时风机关闭计时
    U16     u16_anglebak;       //记录摆叶角度
    U16     u16_angledew; 		//目标角度备份
	U16     u16_AntiDewCount;	//防凝露功能计时
	U8      f_PrefTestSetMaxAngle:1;	//进入性能测试时开到最大角
}STRUCT_SWING;

extern  STRUCT_SWING    Swing;

/****************************************************************************************************
Function Name       :void	Swing_Con(void)	
Description         :风门控制
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Swing_Con(void);
/****************************************************************************************************
Function Name       :void	Swing_Sweep(void)	
Description         :风门扫风逻辑处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Swing_Sweep(void);

//add code
/****************************************************************************************************
Function Name       :void    Swing_AntiDew(void)
Description         :防凝露功能
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Swing_AntiDew(void);

#endif
