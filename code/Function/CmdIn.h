/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: CmdIn.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/08/14
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _CMDIN_H_

#define	   _CMDIN_H_

//--------------------------------------------------------------------------------------------------//
//接收命令相关参数宏定义


//--------------------------------------------------------------------------------------------------//
extern    STRUCT_RX    CmdInBak;

/****************************************************************************************************
Function Name       :void	DisplayBoardCommandCheck(void)
Description         :判定显示板有命令送达
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    DisplayBoardCommandCheck(void);
/****************************************************************************************************
Function Name       :void	DisplayBoardTurnOff(void)
Description         :关机处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern void    DisplayBoardTurnOff(void);
/****************************************************************************************************
Function Name       :void	DisplayBoardTurnOn(void)
Description         :开机处理
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern void    DisplayBoardTurnOn(void);

#endif
