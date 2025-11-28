/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Defrost.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/09/20
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _DEFROST_H_

#define    _DEFROST_H_


typedef     struct
{
	U8    f_Enable    :1;  //进入标志
	U8    f_Quit	  :1;  //退出标志		
	U8    f_T30Found  :1;  //1：已经找到T30 0：未找到T30
	U8    f_CompHasRun :1; //lcx add 进入制热后，记录压机运行过标志
	U8    Reserve	  :4;
	
	S16   s16_T30Mul10;				//T3最小值(*10)
	U16   u16_FindT30_Count;		//寻找T30时间计时(压缩机开启时重新计时)
	U16   u16_HeatRun_Count;		//制热运行时间计时
	U16   u16_DefCase3_Count;		//条件三满足持续计时
	U16   u16_DefQCase2_Count;		//退出条件二满足持续计时
	U16   u16_Defrosting_Count;		//化霜进行时计时
	U8    u8_Step;					//化霜阶段
	U16	  u16_Step_Delay;			//化霜阶段经历倒计时
}STRUCT_DEFROST;

extern    STRUCT_DEFROST    Defrost;

/****************************************************************************************************
Function Name       :void    Defrost_Init(void)
Description         :化霜功能初始化
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Defrost_Init(void);
/****************************************************************************************************
Function Name       :void    Defrost_Con(void)
Description         :化霜功能处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Defrost_Con(void);


#endif
