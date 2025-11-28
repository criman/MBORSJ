/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: WaterBox.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/13
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _WATERBOX_H_

#define    _WATERBOX_H_

typedef    struct
{
    U8    f_SW1_Full    :1;		//信号
	U8    f_SW2_Full    :1;		//信号
	U8    f_WatLow		:1;		//低水位
	U8    f_Full        :1;		//水满
//	U8    f_WatLowPro	:1;		//低水位报警
//	U8    f_FullPro		:1;		//水满报警
	U8    Reserved      :2;
	
	U16   u16_SW1FullCount;
	U16   u16_SW2FullCount;
	U16   u16_SW1NormalCount;
	U16   u16_SW2NormalCount;	
}STRUCT_WATERBOX;

extern    STRUCT_WATERBOX    WaterBox;

/****************************************************************************************************
Function Name       :void	Func_WaterBox(void)
Description         :水箱信号处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Func_WaterBox(void);
	
#endif
