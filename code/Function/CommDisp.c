/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: CommDisp.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2023/08/09
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"

STRUCT_COMMDISP    CommDisp;

/****************************************************************************************************
Function Name       :U8    CommDisp_Check8(U8 *p, U8 counter)
Description         :校验函数
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
U8    CommDisp_Check8(U8 *p, U8 counter)
{
	U8    crc8 = 0;
	U8    index = 0;
	
	for (; counter > 0; counter--)
	{
		if (index >= 2)	//头码两个字节不纳入计算校验码
		{
			crc8 ^= *p;
		}
		
		p++;
		index++;
	}
	
	return crc8;
}
