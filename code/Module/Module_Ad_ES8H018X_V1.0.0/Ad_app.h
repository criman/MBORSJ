/*===================================================================================================
                		Copyright(C) 2011-2099.  SunRam. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Ad_app.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2022/04/25
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 
#ifndef			_AD_APP_H_

#define			_AD_APP_H_

//--------------------------温度AD异常恢复相关参数----------------------------//
#define			C_FUNC_ADAPP_MIN					10					//AD采样电压小于0.05V-开路
#define			C_FUNC_ADAPP_MAX					4055				//AD采样电压大于4.95V-短路
#define			C_FUNC_ADAPP_RECOVER_DELTA		    20					//故障恢复需要AD间隔值
#define			C_FUNC_ADAPP_OPEN_DLY				1					//开路防抖1次
#define			C_FUNC_ADAPP_SHORT_DLY				1					//开路防抖1次
#define			C_FUNC_ADAPP_GOOD_DLY				5					//故障恢复防抖5次
//----------------------------------------------------------------------------//

//--------------------------排气温度AD值表信息参数--------------------------------//
#define			C_ADAPP_TABLEFIRST_TEMP				-40												//表头AD值对应温度值
#define			C_ADAPP_TABLEINDEX_NUM				191												//温度表AD值成员个数
#define			C_ADAPP_TABLEINDEX_HALF				(C_ADAPP_TABLEINDEX_NUM>>1)						//温度表中间(查表二分法)	
#define			C_ADAPP_TABLEINDEX_MAX				(C_ADAPP_TABLEINDEX_NUM-1)						//温度表AD值成员个数
#define			C_ADAPP_TABLEADVALUE_HALF			U16_adc_temp_table[C_ADAPP_TABLEINDEX_HALF]		//温度表中间处的AD值

//--------------------------盘管温度AD值表信息参数--------------------------------//
#define			C_ADAPP_TABLEFIRST_TEMPC			-30													//表头AD值对应温度值
#define			C_ADAPP_TABLEINDEX_NUMC				136													//温度表AD值成员个数
#define			C_ADAPP_TABLEINDEX_HALFC			(C_ADAPP_TABLEINDEX_NUMC>>1)						//温度表中间(查表二分法)	
#define			C_ADAPP_TABLEINDEX_MAXC				(C_ADAPP_TABLEINDEX_NUMC-1)							//温度表AD值成员个数
#define			C_ADAPP_TABLEADVALUE_HALFC			U16_adc_temp_table[C_ADAPP_TABLEINDEX_HALFC]		//温度表中间处的AD值

//--------------------------环境温度AD值表信息参数--------------------------------//
#define			C_ADAPP_TABLEFIRST_TEMPR			-50													//表头AD值对应温度值
#define			C_ADAPP_TABLEINDEX_NUMR				201													//温度表AD值成员个数
#define			C_ADAPP_TABLEINDEX_HALFR			(C_ADAPP_TABLEINDEX_NUMR>>1)						//温度表中间(查表二分法)	
#define			C_ADAPP_TABLEINDEX_MAXR				(C_ADAPP_TABLEINDEX_NUMR-1)							//温度表AD值成员个数
#define			C_ADAPP_TABLEADVALUE_HALFR			U16_adc_temp_table[C_ADAPP_TABLEINDEX_HALFR]		//温度表中间处的AD值

//--------------------------电流AD值表信息参数--------------------------------//
#define			C_ADAPP_TABLEFIRST_TEMPCUR			1													//表头AD值对应电流值
#define			C_ADAPP_TABLEINDEX_NUMCUR			22												//电流表AD值成员个数
#define			C_ADAPP_TABLEINDEX_HALFCUR			(C_ADAPP_TABLEINDEX_NUMCUR>>1)						//电流表中间(查表二分法)	
#define			C_ADAPP_TABLEINDEX_MAXCUR			(C_ADAPP_TABLEINDEX_NUMCUR-1)						//电流表AD值成员个数
#define			C_ADAPP_TABLEADVALUE_HALFCUR		U16_adc_temp_table[C_ADAPP_TABLEINDEX_HALFCUR]		//电流表中间处的AD值
//----------------------------------------------------------------------------//
//室内温度
//				宏定义					AD				温度
#define		C_AD_TEMPR_M50			76 			//-50℃对应AD值
#define		C_AD_TEMPR_M49			81 			//-49℃对应AD值
#define		C_AD_TEMPR_M48			86 			//-48℃对应AD值
#define		C_AD_TEMPR_M47			92 			//-47℃对应AD值
#define		C_AD_TEMPR_M46			98 			//-46℃对应AD值
#define		C_AD_TEMPR_M45			104 		//-45℃对应AD值
#define		C_AD_TEMPR_M44			111 		//-44℃对应AD值
#define		C_AD_TEMPR_M43			118 		//-43℃对应AD值
#define		C_AD_TEMPR_M42			125 		//-42℃对应AD值
#define		C_AD_TEMPR_M41			133 		//-41℃对应AD值
#define		C_AD_TEMPR_M40			141 		//-40℃对应AD值
#define		C_AD_TEMPR_M39			150 		//-39℃对应AD值
#define		C_AD_TEMPR_M38			159 		//-38℃对应AD值
#define		C_AD_TEMPR_M37			169 		//-37℃对应AD值
#define		C_AD_TEMPR_M36			179 		//-36℃对应AD值
#define		C_AD_TEMPR_M35			189 		//-35℃对应AD值
#define		C_AD_TEMPR_M34			201 		//-34℃对应AD值
#define		C_AD_TEMPR_M33			212 		//-33℃对应AD值
#define		C_AD_TEMPR_M32			224 		//-32℃对应AD值
#define		C_AD_TEMPR_M31			237 		//-31℃对应AD值
#define		C_AD_TEMPR_M30			251 		//-30℃对应AD值
#define		C_AD_TEMPR_M29			265 		//-29℃对应AD值
#define		C_AD_TEMPR_M28			279 		//-28℃对应AD值
#define		C_AD_TEMPR_M27			294 		//-27℃对应AD值
#define		C_AD_TEMPR_M26			310 		//-26℃对应AD值
#define		C_AD_TEMPR_M25			327 		//-25℃对应AD值
#define		C_AD_TEMPR_M24			344 		//-24℃对应AD值
#define		C_AD_TEMPR_M23			362 		//-23℃对应AD值
#define		C_AD_TEMPR_M22			381 		//-22℃对应AD值
#define		C_AD_TEMPR_M21			400 		//-21℃对应AD值
#define		C_AD_TEMPR_M20			421 		//-20℃对应AD值
#define		C_AD_TEMPR_M19			440 		//-19℃对应AD值
#define		C_AD_TEMPR_M18			461 		//-18℃对应AD值
#define		C_AD_TEMPR_M17			483 		//-17℃对应AD值
#define		C_AD_TEMPR_M16			505 		//-16℃对应AD值
#define		C_AD_TEMPR_M15			528 		//-15℃对应AD值
#define		C_AD_TEMPR_M14			552 		//-14℃对应AD值
#define		C_AD_TEMPR_M13			577 		//-13℃对应AD值
#define		C_AD_TEMPR_M12			603 		//-12℃对应AD值
#define		C_AD_TEMPR_M11			629 		//-11℃对应AD值
#define		C_AD_TEMPR_M10			657 		//-10℃对应AD值
#define		C_AD_TEMPR_M09			685 		//-9℃对应AD值
#define		C_AD_TEMPR_M08			714 		//-8℃对应AD值
#define		C_AD_TEMPR_M07			744 		//-7℃对应AD值
#define		C_AD_TEMPR_M06			775 		//-6℃对应AD值
#define		C_AD_TEMPR_M05			807 		//-5℃对应AD值
#define		C_AD_TEMPR_M04			839 		//-4℃对应AD值
#define		C_AD_TEMPR_M03			873 		//-3℃对应AD值
#define		C_AD_TEMPR_M02			907 		//-2℃对应AD值
#define		C_AD_TEMPR_M01			942 		//-1℃对应AD值
#define		C_AD_TEMPR_P00			978 		//0℃对应AD值
#define		C_AD_TEMPR_P01			1015 		//1℃对应AD值
#define		C_AD_TEMPR_P02			1053 		//2℃对应AD值
#define		C_AD_TEMPR_P03			1091 		//3℃对应AD值
#define		C_AD_TEMPR_P04			1130 		//4℃对应AD值
#define		C_AD_TEMPR_P05			1170 		//5℃对应AD值
#define		C_AD_TEMPR_P06			1210 		//6℃对应AD值
#define		C_AD_TEMPR_P07			1251 		//7℃对应AD值
#define		C_AD_TEMPR_P08			1293 		//8℃对应AD值
#define		C_AD_TEMPR_P09			1335 		//9℃对应AD值
#define		C_AD_TEMPR_P10			1377 		//10℃对应AD值
#define		C_AD_TEMPR_P11			1421 		//11℃对应AD值
#define		C_AD_TEMPR_P12			1464 		//12℃对应AD值
#define		C_AD_TEMPR_P13			1508 		//13℃对应AD值
#define		C_AD_TEMPR_P14			1552 		//14℃对应AD值
#define		C_AD_TEMPR_P15			1597 		//15℃对应AD值
#define		C_AD_TEMPR_P16			1642 		//16℃对应AD值
#define		C_AD_TEMPR_P17			1687 		//17℃对应AD值
#define		C_AD_TEMPR_P18			1732 		//18℃对应AD值
#define		C_AD_TEMPR_P19			1777 		//19℃对应AD值
#define		C_AD_TEMPR_P20			1822 		//20℃对应AD值
#define		C_AD_TEMPR_P21			1868 		//21℃对应AD值
#define		C_AD_TEMPR_P22			1913 		//22℃对应AD值
#define		C_AD_TEMPR_P23			1958 		//23℃对应AD值
#define		C_AD_TEMPR_P24			2003 		//24℃对应AD值
#define		C_AD_TEMPR_P25			2048 		//25℃对应AD值
#define		C_AD_TEMPR_P26			2093 		//26℃对应AD值
#define		C_AD_TEMPR_P27			2137 		//27℃对应AD值
#define		C_AD_TEMPR_P28			2181 		//28℃对应AD值
#define		C_AD_TEMPR_P29			2225 		//29℃对应AD值
#define		C_AD_TEMPR_P30			2268 		//30℃对应AD值
#define		C_AD_TEMPR_P31			2311 		//31℃对应AD值
#define		C_AD_TEMPR_P32			2353 		//32℃对应AD值
#define		C_AD_TEMPR_P33			2396 		//33℃对应AD值
#define		C_AD_TEMPR_P34			2437 		//34℃对应AD值
#define		C_AD_TEMPR_P35			2478 		//35℃对应AD值
#define		C_AD_TEMPR_P36			2518 		//36℃对应AD值
#define		C_AD_TEMPR_P37			2558 		//37℃对应AD值
#define		C_AD_TEMPR_P38			2597 		//38℃对应AD值
#define		C_AD_TEMPR_P39			2636 		//39℃对应AD值
#define		C_AD_TEMPR_P40			2674 		//40℃对应AD值
#define		C_AD_TEMPR_P41			2711 		//41℃对应AD值
#define		C_AD_TEMPR_P42			2747 		//42℃对应AD值
#define		C_AD_TEMPR_P43			2783 		//43℃对应AD值
#define		C_AD_TEMPR_P44			2818 		//44℃对应AD值
#define		C_AD_TEMPR_P45			2853 		//45℃对应AD值
#define		C_AD_TEMPR_P46			2887 		//46℃对应AD值
#define		C_AD_TEMPR_P47			2920 		//47℃对应AD值
#define		C_AD_TEMPR_P48			2952 		//48℃对应AD值
#define		C_AD_TEMPR_P49			2984 		//49℃对应AD值
#define		C_AD_TEMPR_P50			3014 		//50℃对应AD值
#define		C_AD_TEMPR_P51			3045 		//51℃对应AD值
#define		C_AD_TEMPR_P52			3074 		//52℃对应AD值
#define		C_AD_TEMPR_P53			3103 		//53℃对应AD值
#define		C_AD_TEMPR_P54			3131 		//54℃对应AD值
#define		C_AD_TEMPR_P55			3158 		//55℃对应AD值
#define		C_AD_TEMPR_P56			3185 		//56℃对应AD值
#define		C_AD_TEMPR_P57			3211 		//57℃对应AD值
#define		C_AD_TEMPR_P58			3236 		//58℃对应AD值
#define		C_AD_TEMPR_P59			3261 		//59℃对应AD值
#define		C_AD_TEMPR_P60			3285 		//60℃对应AD值
#define		C_AD_TEMPR_P61			3308 		//61℃对应AD值
#define		C_AD_TEMPR_P62			3331 		//62℃对应AD值
#define		C_AD_TEMPR_P63			3353 		//63℃对应AD值
#define		C_AD_TEMPR_P64			3375 		//64℃对应AD值
#define		C_AD_TEMPR_P65			3396 		//65℃对应AD值
#define		C_AD_TEMPR_P66			3416 		//66℃对应AD值
#define		C_AD_TEMPR_P67			3436 		//67℃对应AD值
#define		C_AD_TEMPR_P68			3455 		//68℃对应AD值
#define		C_AD_TEMPR_P69			3474 		//69℃对应AD值
#define		C_AD_TEMPR_P70			3492 		//70℃对应AD值
#define		C_AD_TEMPR_P71			3509 		//71℃对应AD值
#define		C_AD_TEMPR_P72			3526 		//72℃对应AD值
#define		C_AD_TEMPR_P73			3543 		//73℃对应AD值
#define		C_AD_TEMPR_P74			3559 		//74℃对应AD值
#define		C_AD_TEMPR_P75			3575 		//75℃对应AD值
#define		C_AD_TEMPR_P76			3590 		//76℃对应AD值
#define		C_AD_TEMPR_P77			3605 		//77℃对应AD值
#define		C_AD_TEMPR_P78			3619 		//78℃对应AD值
#define		C_AD_TEMPR_P79			3633 		//79℃对应AD值
#define		C_AD_TEMPR_P80			3647 		//80℃对应AD值
#define		C_AD_TEMPR_P81			3660 		//81℃对应AD值
#define		C_AD_TEMPR_P82			3672 		//82℃对应AD值
#define		C_AD_TEMPR_P83			3685 		//83℃对应AD值
#define		C_AD_TEMPR_P84			3697 		//84℃对应AD值
#define		C_AD_TEMPR_P85			3708 		//85℃对应AD值
#define		C_AD_TEMPR_P86			3719 		//86℃对应AD值
#define		C_AD_TEMPR_P87			3730 		//87℃对应AD值
#define		C_AD_TEMPR_P88			3740 		//88℃对应AD值
#define		C_AD_TEMPR_P89			3751 		//89℃对应AD值
#define		C_AD_TEMPR_P90			3761 		//90℃对应AD值
#define		C_AD_TEMPR_P91			3770 		//91℃对应AD值
#define		C_AD_TEMPR_P92			3779 		//92℃对应AD值
#define		C_AD_TEMPR_P93			3788 		//93℃对应AD值
#define		C_AD_TEMPR_P94			3797 		//94℃对应AD值
#define		C_AD_TEMPR_P95			3805 		//95℃对应AD值
#define		C_AD_TEMPR_P96			3814 		//96℃对应AD值
#define		C_AD_TEMPR_P97			3821 		//97℃对应AD值
#define		C_AD_TEMPR_P98			3829 		//98℃对应AD值
#define		C_AD_TEMPR_P99			3836 		//99℃对应AD值
#define		C_AD_TEMPR_P100			3844 		//100℃对应AD值
#define		C_AD_TEMPR_P101			3851 		//101℃对应AD值
#define		C_AD_TEMPR_P102			3858 		//102℃对应AD值
#define		C_AD_TEMPR_P103			3864 		//103℃对应AD值
#define		C_AD_TEMPR_P104			3870 		//104℃对应AD值
#define		C_AD_TEMPR_P105			3877 		//105℃对应AD值
#define		C_AD_TEMPR_P106			3883 		//106℃对应AD值
#define		C_AD_TEMPR_P107			3888 		//107℃对应AD值
#define		C_AD_TEMPR_P108			3894 		//108℃对应AD值
#define		C_AD_TEMPR_P109			3899 		//109℃对应AD值
#define		C_AD_TEMPR_P110			3905 		//110℃对应AD值
#define		C_AD_TEMPR_P111			3910 		//111℃对应AD值
#define		C_AD_TEMPR_P112			3915 		//112℃对应AD值
#define		C_AD_TEMPR_P113			3919 		//113℃对应AD值
#define		C_AD_TEMPR_P114			3924 		//114℃对应AD值
#define		C_AD_TEMPR_P115			3929 		//115℃对应AD值
#define		C_AD_TEMPR_P116			3933 		//116℃对应AD值
#define		C_AD_TEMPR_P117			3937 		//117℃对应AD值
#define		C_AD_TEMPR_P118			3941 		//118℃对应AD值
#define		C_AD_TEMPR_P119			3945 		//119℃对应AD值
#define		C_AD_TEMPR_P120			3949 		//120℃对应AD值
#define		C_AD_TEMPR_P121			3953 		//121℃对应AD值
#define		C_AD_TEMPR_P122			3957 		//122℃对应AD值
#define		C_AD_TEMPR_P123			3960 		//123℃对应AD值
#define		C_AD_TEMPR_P124			3964 		//124℃对应AD值
#define		C_AD_TEMPR_P125			3967 		//125℃对应AD值
#define		C_AD_TEMPR_P126			3970 		//126℃对应AD值
#define		C_AD_TEMPR_P127			3974 		//127℃对应AD值
#define		C_AD_TEMPR_P128			3977 		//128℃对应AD值
#define		C_AD_TEMPR_P129			3980 		//129℃对应AD值
#define		C_AD_TEMPR_P130			3983 		//130℃对应AD值
#define		C_AD_TEMPR_P131			3985 		//131℃对应AD值
#define		C_AD_TEMPR_P132			3988 		//132℃对应AD值
#define		C_AD_TEMPR_P133			3991 		//133℃对应AD值
#define		C_AD_TEMPR_P134			3993 		//134℃对应AD值
#define		C_AD_TEMPR_P135			3996 		//135℃对应AD值
#define		C_AD_TEMPR_P136			3998 		//136℃对应AD值
#define		C_AD_TEMPR_P137			4001 		//137℃对应AD值
#define		C_AD_TEMPR_P138			4003 		//138℃对应AD值
#define		C_AD_TEMPR_P139			4005 		//139℃对应AD值
#define		C_AD_TEMPR_P140			4007 		//140℃对应AD值
#define		C_AD_TEMPR_P141			4009 		//141℃对应AD值
#define		C_AD_TEMPR_P142			4011 		//142℃对应AD值
#define		C_AD_TEMPR_P143			4014 		//143℃对应AD值
#define		C_AD_TEMPR_P144			4015 		//144℃对应AD值
#define		C_AD_TEMPR_P145			4018 		//145℃对应AD值
#define		C_AD_TEMPR_P146			4019 		//146℃对应AD值
#define		C_AD_TEMPR_P147			4021 		//147℃对应AD值
#define		C_AD_TEMPR_P148			4023 		//148℃对应AD值
#define		C_AD_TEMPR_P149			4025 		//149℃对应AD值
#define		C_AD_TEMPR_P150			4026 		//150℃对应AD值

//----------------------------------------------------------------------------//
//盘管温度
//			宏定义						AD			温度
#define		C_AD_TEMPC_M30			237 		//-30℃对应AD值
#define		C_AD_TEMPC_M29			250 		//-29℃对应AD值
#define		C_AD_TEMPC_M28			264 		//-28℃对应AD值
#define		C_AD_TEMPC_M27			279 		//-27℃对应AD值
#define		C_AD_TEMPC_M26			294 		//-26℃对应AD值
#define		C_AD_TEMPC_M25			310 		//-25℃对应AD值
#define		C_AD_TEMPC_M24			327 		//-24℃对应AD值
#define		C_AD_TEMPC_M23			344 		//-23℃对应AD值
#define		C_AD_TEMPC_M22			362 		//-22℃对应AD值
#define		C_AD_TEMPC_M21			381 		//-21℃对应AD值
#define		C_AD_TEMPC_M20			401 		//-20℃对应AD值
#define		C_AD_TEMPC_M19			421 		//-19℃对应AD值
#define		C_AD_TEMPC_M18			442 		//-18℃对应AD值
#define		C_AD_TEMPC_M17			464 		//-17℃对应AD值
#define		C_AD_TEMPC_M16			487 		//-16℃对应AD值
#define		C_AD_TEMPC_M15			511 		//-15℃对应AD值
#define		C_AD_TEMPC_M14			535 		//-14℃对应AD值
#define		C_AD_TEMPC_M13			561 		//-13℃对应AD值
#define		C_AD_TEMPC_M12			587 		//-12℃对应AD值
#define		C_AD_TEMPC_M11			614 		//-11℃对应AD值
#define		C_AD_TEMPC_M10			642 		//-10℃对应AD值
#define		C_AD_TEMPC_M09			671 		//-9℃对应AD值
#define		C_AD_TEMPC_M08			701 		//-8℃对应AD值
#define		C_AD_TEMPC_M07			731 		//-7℃对应AD值
#define		C_AD_TEMPC_M06			763 		//-6℃对应AD值
#define		C_AD_TEMPC_M05			795 		//-5℃对应AD值
#define		C_AD_TEMPC_M04			829 		//-4℃对应AD值
#define		C_AD_TEMPC_M03			863 		//-3℃对应AD值
#define		C_AD_TEMPC_M02			898 		//-2℃对应AD值
#define		C_AD_TEMPC_M01			933 		//-1℃对应AD值
#define		C_AD_TEMPC_P00			970 		//0℃对应AD值
#define		C_AD_TEMPC_P01			1007 		//1℃对应AD值
#define		C_AD_TEMPC_P02			1045 		//2℃对应AD值
#define		C_AD_TEMPC_P03			1084 		//3℃对应AD值
#define		C_AD_TEMPC_P04			1124 		//4℃对应AD值
#define		C_AD_TEMPC_P05			1164 		//5℃对应AD值
#define		C_AD_TEMPC_P06			1205 		//6℃对应AD值
#define		C_AD_TEMPC_P07			1246 		//7℃对应AD值
#define		C_AD_TEMPC_P08			1288 		//8℃对应AD值
#define		C_AD_TEMPC_P09			1331 		//9℃对应AD值
#define		C_AD_TEMPC_P10			1374 		//10℃对应AD值
#define		C_AD_TEMPC_P11			1418 		//11℃对应AD值
#define		C_AD_TEMPC_P12			1461 		//12℃对应AD值
#define		C_AD_TEMPC_P13			1506 		//13℃对应AD值
#define		C_AD_TEMPC_P14			1550 		//14℃对应AD值
#define		C_AD_TEMPC_P15			1595 		//15℃对应AD值
#define		C_AD_TEMPC_P16			1640 		//16℃对应AD值
#define		C_AD_TEMPC_P17			1685 		//17℃对应AD值
#define		C_AD_TEMPC_P18			1731 		//18℃对应AD值
#define		C_AD_TEMPC_P19			1776 		//19℃对应AD值
#define		C_AD_TEMPC_P20			1822 		//20℃对应AD值
#define		C_AD_TEMPC_P21			1867 		//21℃对应AD值
#define		C_AD_TEMPC_P22			1913 		//22℃对应AD值
#define		C_AD_TEMPC_P23			1958 		//23℃对应AD值
#define		C_AD_TEMPC_P24			2003 		//24℃对应AD值
#define		C_AD_TEMPC_P25			2048 		//25℃对应AD值
#define		C_AD_TEMPC_P26			2092 		//26℃对应AD值
#define		C_AD_TEMPC_P27			2137 		//27℃对应AD值
#define		C_AD_TEMPC_P28			2181 		//28℃对应AD值
#define		C_AD_TEMPC_P29			2225 		//29℃对应AD值
#define		C_AD_TEMPC_P30			2269 		//30℃对应AD值
#define		C_AD_TEMPC_P31			2312 		//31℃对应AD值
#define		C_AD_TEMPC_P32			2354 		//32℃对应AD值
#define		C_AD_TEMPC_P33			2396 		//33℃对应AD值
#define		C_AD_TEMPC_P34			2437 		//34℃对应AD值
#define		C_AD_TEMPC_P35			2478 		//35℃对应AD值
#define		C_AD_TEMPC_P36			2518 		//36℃对应AD值
#define		C_AD_TEMPC_P37			2558 		//37℃对应AD值
#define		C_AD_TEMPC_P38			2597 		//38℃对应AD值
#define		C_AD_TEMPC_P39			2636 		//39℃对应AD值
#define		C_AD_TEMPC_P40			2674 		//40℃对应AD值
#define		C_AD_TEMPC_P41			2711 		//41℃对应AD值
#define		C_AD_TEMPC_P42			2747 		//42℃对应AD值
#define		C_AD_TEMPC_P43			2784 		//43℃对应AD值
#define		C_AD_TEMPC_P44			2818 		//44℃对应AD值
#define		C_AD_TEMPC_P45			2853 		//45℃对应AD值
#define		C_AD_TEMPC_P46			2887 		//46℃对应AD值
#define		C_AD_TEMPC_P47			2919 		//47℃对应AD值
#define		C_AD_TEMPC_P48			2952 		//48℃对应AD值
#define		C_AD_TEMPC_P49			2983 		//49℃对应AD值
#define		C_AD_TEMPC_P50			3014 		//50℃对应AD值
#define		C_AD_TEMPC_P51			3044 		//51℃对应AD值
#define		C_AD_TEMPC_P52			3074 		//52℃对应AD值
#define		C_AD_TEMPC_P53			3103 		//53℃对应AD值
#define		C_AD_TEMPC_P54			3130 		//54℃对应AD值
#define		C_AD_TEMPC_P55			3158 		//55℃对应AD值
#define		C_AD_TEMPC_P56			3185 		//56℃对应AD值
#define		C_AD_TEMPC_P57			3211 		//57℃对应AD值
#define		C_AD_TEMPC_P58			3237 		//58℃对应AD值
#define		C_AD_TEMPC_P59			3261 		//59℃对应AD值
#define		C_AD_TEMPC_P60			3285 		//60℃对应AD值
#define		C_AD_TEMPC_P61			3309 		//61℃对应AD值
#define		C_AD_TEMPC_P62			3330 		//62℃对应AD值
#define		C_AD_TEMPC_P63			3353 		//63℃对应AD值
#define		C_AD_TEMPC_P64			3374 		//64℃对应AD值
#define		C_AD_TEMPC_P65			3395 		//65℃对应AD值
#define		C_AD_TEMPC_P66			3416 		//66℃对应AD值
#define		C_AD_TEMPC_P67			3435 		//67℃对应AD值
#define		C_AD_TEMPC_P68			3455 		//68℃对应AD值
#define		C_AD_TEMPC_P69			3473 		//69℃对应AD值
#define		C_AD_TEMPC_P70			3490 		//70℃对应AD值
#define		C_AD_TEMPC_P71			3508 		//71℃对应AD值
#define		C_AD_TEMPC_P72			3526 		//72℃对应AD值
#define		C_AD_TEMPC_P73			3542 		//73℃对应AD值
#define		C_AD_TEMPC_P74			3559 		//74℃对应AD值
#define		C_AD_TEMPC_P75			3574 		//75℃对应AD值
#define		C_AD_TEMPC_P76			3590 		//76℃对应AD值
#define		C_AD_TEMPC_P77			3604 		//77℃对应AD值
#define		C_AD_TEMPC_P78			3618 		//78℃对应AD值
#define		C_AD_TEMPC_P79			3631 		//79℃对应AD值
#define		C_AD_TEMPC_P80			3646 		//80℃对应AD值
#define		C_AD_TEMPC_P81			3659 		//81℃对应AD值
#define		C_AD_TEMPC_P82			3670 		//82℃对应AD值
#define		C_AD_TEMPC_P83			3683 		//83℃对应AD值
#define		C_AD_TEMPC_P84			3695 		//84℃对应AD值
#define		C_AD_TEMPC_P85			3707 		//85℃对应AD值
#define		C_AD_TEMPC_P86			3717 		//86℃对应AD值
#define		C_AD_TEMPC_P87			3729 		//87℃对应AD值
#define		C_AD_TEMPC_P88			3739 		//88℃对应AD值
#define		C_AD_TEMPC_P89			3749 		//89℃对应AD值
#define		C_AD_TEMPC_P90			3760 		//90℃对应AD值
#define		C_AD_TEMPC_P91			3768 		//91℃对应AD值
#define		C_AD_TEMPC_P92			3779 		//92℃对应AD值
#define		C_AD_TEMPC_P93			3787 		//93℃对应AD值
#define		C_AD_TEMPC_P94			3796 		//94℃对应AD值
#define		C_AD_TEMPC_P95			3803 		//95℃对应AD值
#define		C_AD_TEMPC_P96			3812 		//96℃对应AD值
#define		C_AD_TEMPC_P97			3821 		//97℃对应AD值
#define		C_AD_TEMPC_P98			3828 		//98℃对应AD值
#define		C_AD_TEMPC_P99			3835 		//99℃对应AD值
#define		C_AD_TEMPC_P100			3842 		//100℃对应AD值
#define		C_AD_TEMPC_P101			3850 		//101℃对应AD值
#define		C_AD_TEMPC_P102			3857 		//102℃对应AD值
#define		C_AD_TEMPC_P103			3862 		//103℃对应AD值
#define		C_AD_TEMPC_P104			3870 		//104℃对应AD值
#define		C_AD_TEMPC_P105			3875 		//105℃对应AD值


//----------------------------------------------------------------------------//
//排气温度
//			宏定义						AD		温度
#define		C_AD_TEMPE_M40			11 		//-40℃对应AD值
#define		C_AD_TEMPE_M39			12 		//-39℃对应AD值
#define		C_AD_TEMPE_M38			13 		//-38℃对应AD值
#define		C_AD_TEMPE_M37			14 		//-37℃对应AD值
#define		C_AD_TEMPE_M36			15 		//-36℃对应AD值
#define		C_AD_TEMPE_M35			16 		//-35℃对应AD值
#define		C_AD_TEMPE_M34			17 		//-34℃对应AD值
#define		C_AD_TEMPE_M33			18 		//-33℃对应AD值
#define		C_AD_TEMPE_M32			19 		//-32℃对应AD值
#define		C_AD_TEMPE_M31			21 		//-31℃对应AD值
#define		C_AD_TEMPE_M30			22 		//-30℃对应AD值
#define		C_AD_TEMPE_M29			23 		//-29℃对应AD值
#define		C_AD_TEMPE_M28			25 		//-28℃对应AD值
#define		C_AD_TEMPE_M27			26 		//-27℃对应AD值
#define		C_AD_TEMPE_M26			28 		//-26℃对应AD值
#define		C_AD_TEMPE_M25			30 		//-25℃对应AD值
#define		C_AD_TEMPE_M24			31 		//-24℃对应AD值
#define		C_AD_TEMPE_M23			33 		//-23℃对应AD值
#define		C_AD_TEMPE_M22			35 		//-22℃对应AD值
#define		C_AD_TEMPE_M21			37 		//-21℃对应AD值
#define		C_AD_TEMPE_M20			39 		//-20℃对应AD值
#define		C_AD_TEMPE_M19			42 		//-19℃对应AD值
#define		C_AD_TEMPE_M18			44 		//-18℃对应AD值
#define		C_AD_TEMPE_M17			47 		//-17℃对应AD值
#define		C_AD_TEMPE_M16			49 		//-16℃对应AD值
#define		C_AD_TEMPE_M15			52 		//-15℃对应AD值
#define		C_AD_TEMPE_M14			55 		//-14℃对应AD值
#define		C_AD_TEMPE_M13			58 		//-13℃对应AD值
#define		C_AD_TEMPE_M12			62 		//-12℃对应AD值
#define		C_AD_TEMPE_M11			65 		//-11℃对应AD值
#define		C_AD_TEMPE_M10			69 		//-10℃对应AD值
#define		C_AD_TEMPE_M09			72 		//-9℃对应AD值
#define		C_AD_TEMPE_M08			76 		//-8℃对应AD值
#define		C_AD_TEMPE_M07			80 		//-7℃对应AD值
#define		C_AD_TEMPE_M06			85 		//-6℃对应AD值
#define		C_AD_TEMPE_M05			89 		//-5℃对应AD值
#define		C_AD_TEMPE_M04			94 		//-4℃对应AD值
#define		C_AD_TEMPE_M03			99 		//-3℃对应AD值
#define		C_AD_TEMPE_M02			104 		//-2℃对应AD值
#define		C_AD_TEMPE_M01			109 		//-1℃对应AD值
#define		C_AD_TEMPE_P00			115 		//0℃对应AD值
#define		C_AD_TEMPE_P01			120 		//1℃对应AD值
#define		C_AD_TEMPE_P02			126 		//2℃对应AD值
#define		C_AD_TEMPE_P03			133 		//3℃对应AD值
#define		C_AD_TEMPE_P04			139 		//4℃对应AD值
#define		C_AD_TEMPE_P05			146 		//5℃对应AD值
#define		C_AD_TEMPE_P06			153 		//6℃对应AD值
#define		C_AD_TEMPE_P07			160 		//7℃对应AD值
#define		C_AD_TEMPE_P08			168 		//8℃对应AD值
#define		C_AD_TEMPE_P09			176 		//9℃对应AD值
#define		C_AD_TEMPE_P10			184 		//10℃对应AD值
#define		C_AD_TEMPE_P11			193 		//11℃对应AD值
#define		C_AD_TEMPE_P12			202 		//12℃对应AD值
#define		C_AD_TEMPE_P13			211 		//13℃对应AD值
#define		C_AD_TEMPE_P14			221 		//14℃对应AD值
#define		C_AD_TEMPE_P15			231 		//15℃对应AD值
#define		C_AD_TEMPE_P16			241 		//16℃对应AD值
#define		C_AD_TEMPE_P17			252 		//17℃对应AD值
#define		C_AD_TEMPE_P18			263 		//18℃对应AD值
#define		C_AD_TEMPE_P19			275 		//19℃对应AD值
#define		C_AD_TEMPE_P20			286 		//20℃对应AD值
#define		C_AD_TEMPE_P21			299 		//21℃对应AD值
#define		C_AD_TEMPE_P22			311 		//22℃对应AD值
#define		C_AD_TEMPE_P23			324 		//23℃对应AD值
#define		C_AD_TEMPE_P24			338 		//24℃对应AD值
#define		C_AD_TEMPE_P25			352 		//25℃对应AD值
#define		C_AD_TEMPE_P26			366 		//26℃对应AD值
#define		C_AD_TEMPE_P27			381 		//27℃对应AD值
#define		C_AD_TEMPE_P28			396 		//28℃对应AD值
#define		C_AD_TEMPE_P29			412 		//29℃对应AD值
#define		C_AD_TEMPE_P30			428 		//30℃对应AD值
#define		C_AD_TEMPE_P31			445 		//31℃对应AD值
#define		C_AD_TEMPE_P32			462 		//32℃对应AD值
#define		C_AD_TEMPE_P33			480 		//33℃对应AD值
#define		C_AD_TEMPE_P34			498 		//34℃对应AD值
#define		C_AD_TEMPE_P35			516 		//35℃对应AD值
#define		C_AD_TEMPE_P36			535 		//36℃对应AD值
#define		C_AD_TEMPE_P37			555 		//37℃对应AD值
#define		C_AD_TEMPE_P38			574 		//38℃对应AD值
#define		C_AD_TEMPE_P39			595 		//39℃对应AD值
#define		C_AD_TEMPE_P40			616 		//40℃对应AD值
#define		C_AD_TEMPE_P41			637 		//41℃对应AD值
#define		C_AD_TEMPE_P42			659 		//42℃对应AD值
#define		C_AD_TEMPE_P43			681 		//43℃对应AD值
#define		C_AD_TEMPE_P44			704 		//44℃对应AD值
#define		C_AD_TEMPE_P45			727 		//45℃对应AD值
#define		C_AD_TEMPE_P46			751 		//46℃对应AD值
#define		C_AD_TEMPE_P47			775 		//47℃对应AD值
#define		C_AD_TEMPE_P48			800 		//48℃对应AD值
#define		C_AD_TEMPE_P49			825 		//49℃对应AD值
#define		C_AD_TEMPE_P50			850 		//50℃对应AD值
#define		C_AD_TEMPE_P51			876 		//51℃对应AD值
#define		C_AD_TEMPE_P52			903 		//52℃对应AD值
#define		C_AD_TEMPE_P53			929 		//53℃对应AD值
#define		C_AD_TEMPE_P54			957 		//54℃对应AD值
#define		C_AD_TEMPE_P55			984 		//55℃对应AD值
#define		C_AD_TEMPE_P56			1012 		//56℃对应AD值
#define		C_AD_TEMPE_P57			1040 		//57℃对应AD值
#define		C_AD_TEMPE_P58			1069 		//58℃对应AD值
#define		C_AD_TEMPE_P59			1098 		//59℃对应AD值
#define		C_AD_TEMPE_P60			1128 		//60℃对应AD值
#define		C_AD_TEMPE_P61			1157 		//61℃对应AD值
#define		C_AD_TEMPE_P62			1188 		//62℃对应AD值
#define		C_AD_TEMPE_P63			1218 		//63℃对应AD值
#define		C_AD_TEMPE_P64			1249 		//64℃对应AD值
#define		C_AD_TEMPE_P65			1279 		//65℃对应AD值
#define		C_AD_TEMPE_P66			1311 		//66℃对应AD值
#define		C_AD_TEMPE_P67			1342 		//67℃对应AD值
#define		C_AD_TEMPE_P68			1374 		//68℃对应AD值
#define		C_AD_TEMPE_P69			1406 		//69℃对应AD值
#define		C_AD_TEMPE_P70			1438 		//70℃对应AD值
#define		C_AD_TEMPE_P71			1470 		//71℃对应AD值
#define		C_AD_TEMPE_P72			1502 		//72℃对应AD值
#define		C_AD_TEMPE_P73			1535 		//73℃对应AD值
#define		C_AD_TEMPE_P74			1568 		//74℃对应AD值
#define		C_AD_TEMPE_P75			1600 		//75℃对应AD值
#define		C_AD_TEMPE_P76			1633 		//76℃对应AD值
#define		C_AD_TEMPE_P77			1666 		//77℃对应AD值
#define		C_AD_TEMPE_P78			1699 		//78℃对应AD值
#define		C_AD_TEMPE_P79			1732 		//79℃对应AD值
#define		C_AD_TEMPE_P80			1765 		//80℃对应AD值
#define		C_AD_TEMPE_P81			1798 		//81℃对应AD值
#define		C_AD_TEMPE_P82			1831 		//82℃对应AD值
#define		C_AD_TEMPE_P83			1864 		//83℃对应AD值
#define		C_AD_TEMPE_P84			1897 		//84℃对应AD值
#define		C_AD_TEMPE_P85			1930 		//85℃对应AD值
#define		C_AD_TEMPE_P86			1962 		//86℃对应AD值
#define		C_AD_TEMPE_P87			1995 		//87℃对应AD值
#define		C_AD_TEMPE_P88			2027 		//88℃对应AD值
#define		C_AD_TEMPE_P89			2059 		//89℃对应AD值
#define		C_AD_TEMPE_P90			2092 		//90℃对应AD值
#define		C_AD_TEMPE_P91			2123 		//91℃对应AD值
#define		C_AD_TEMPE_P92			2155 		//92℃对应AD值
#define		C_AD_TEMPE_P93			2187 		//93℃对应AD值
#define		C_AD_TEMPE_P94			2218 		//94℃对应AD值
#define		C_AD_TEMPE_P95			2249 		//95℃对应AD值
#define		C_AD_TEMPE_P96			2280 		//96℃对应AD值
#define		C_AD_TEMPE_P97			2310 		//97℃对应AD值
#define		C_AD_TEMPE_P98			2340 		//98℃对应AD值
#define		C_AD_TEMPE_P99			2370 		//99℃对应AD值
#define		C_AD_TEMPE_P100			2400 		//100℃对应AD值
#define		C_AD_TEMPE_P101			2429 		//101℃对应AD值
#define		C_AD_TEMPE_P102			2458 		//102℃对应AD值
#define		C_AD_TEMPE_P103			2487 		//103℃对应AD值
#define		C_AD_TEMPE_P104			2515 		//104℃对应AD值
#define		C_AD_TEMPE_P105			2542 		//105℃对应AD值
#define		C_AD_TEMPE_P106			2570 		//106℃对应AD值
#define		C_AD_TEMPE_P107			2597 		//107℃对应AD值
#define		C_AD_TEMPE_P108			2624 		//108℃对应AD值
#define		C_AD_TEMPE_P109			2650 		//109℃对应AD值
#define		C_AD_TEMPE_P110			2676 		//110℃对应AD值
#define		C_AD_TEMPE_P111			2702 		//111℃对应AD值
#define		C_AD_TEMPE_P112			2727 		//112℃对应AD值
#define		C_AD_TEMPE_P113			2752 		//113℃对应AD值
#define		C_AD_TEMPE_P114			2776 		//114℃对应AD值
#define		C_AD_TEMPE_P115			2800 		//115℃对应AD值
#define		C_AD_TEMPE_P116			2824 		//116℃对应AD值
#define		C_AD_TEMPE_P117			2847 		//117℃对应AD值
#define		C_AD_TEMPE_P118			2869 		//118℃对应AD值
#define		C_AD_TEMPE_P119			2892 		//119℃对应AD值
#define		C_AD_TEMPE_P120			2914 		//120℃对应AD值
#define		C_AD_TEMPE_P121			2936 		//121℃对应AD值
#define		C_AD_TEMPE_P122			2957 		//122℃对应AD值
#define		C_AD_TEMPE_P123			2977 		//123℃对应AD值
#define		C_AD_TEMPE_P124			2998 		//124℃对应AD值
#define		C_AD_TEMPE_P125			3018 		//125℃对应AD值
#define		C_AD_TEMPE_P126			3038 		//126℃对应AD值
#define		C_AD_TEMPE_P127			3057 		//127℃对应AD值
#define		C_AD_TEMPE_P128			3077 		//128℃对应AD值
#define		C_AD_TEMPE_P129			3096 		//129℃对应AD值
#define		C_AD_TEMPE_P130			3114 		//130℃对应AD值
#define		C_AD_TEMPE_P131			3132 		//131℃对应AD值
#define		C_AD_TEMPE_P132			3150 		//132℃对应AD值
#define		C_AD_TEMPE_P133			3168 		//133℃对应AD值
#define		C_AD_TEMPE_P134			3185 		//134℃对应AD值
#define		C_AD_TEMPE_P135			3202 		//135℃对应AD值
#define		C_AD_TEMPE_P136			3219 		//136℃对应AD值
#define		C_AD_TEMPE_P137			3236 		//137℃对应AD值
#define		C_AD_TEMPE_P138			3252 		//138℃对应AD值
#define		C_AD_TEMPE_P139			3269 		//139℃对应AD值
#define		C_AD_TEMPE_P140			3285 		//140℃对应AD值
#define		C_AD_TEMPE_P141			3302 		//141℃对应AD值
#define		C_AD_TEMPE_P142			3317 		//142℃对应AD值
#define		C_AD_TEMPE_P143			3334 		//143℃对应AD值
#define		C_AD_TEMPE_P144			3349 		//144℃对应AD值
#define		C_AD_TEMPE_P145			3365 		//145℃对应AD值
#define		C_AD_TEMPE_P146			3381 		//146℃对应AD值
#define		C_AD_TEMPE_P147			3396 		//147℃对应AD值
#define		C_AD_TEMPE_P148			3412 		//148℃对应AD值
#define		C_AD_TEMPE_P149			3428 		//149℃对应AD值
#define		C_AD_TEMPE_P150			3444 		//150℃对应AD值

//----------------------------------------------------------------------------//
//电流
//			宏定义						AD			温度
#define		C_AD_CUR_P01			47 			//	1	A对应AD值
#define		C_AD_CUR_P02			198 		//	2	A对应AD值
#define		C_AD_CUR_P03			349 		//	3	A对应AD值
#define		C_AD_CUR_P04			510 		//	4	A对应AD值
#define		C_AD_CUR_P05			637 		//	5	A对应AD值
#define		C_AD_CUR_P06			792 		//	6	A对应AD值
#define		C_AD_CUR_P07			949 		//	7	A对应AD值
#define		C_AD_CUR_P08			1136 		//	8	A对应AD值
#define		C_AD_CUR_P09			1297 		//	9	A对应AD值
#define		C_AD_CUR_P10			1445 		//	10	A对应AD值
#define		C_AD_CUR_P11			1614 		//	11	A对应AD值
#define		C_AD_CUR_P12			1775 		//	12	A对应AD值
#define		C_AD_CUR_P13			1906 		//	13	A对应AD值
#define		C_AD_CUR_P14			2068 		//	14	A对应AD值
#define		C_AD_CUR_P15			2194 		//	15	A对应AD值
#define		C_AD_CUR_P16			2336 		//	16	A对应AD值
#define		C_AD_CUR_P17			2457 		//	17	A对应AD值
#define		C_AD_CUR_P18			2598 		//	18	A对应AD值
#define		C_AD_CUR_P19			2750 		//	19	A对应AD值
#define		C_AD_CUR_P20			2980 		//	20	A对应AD值
#define		C_AD_CUR_P21			3168 		//	21	A对应AD值
#define		C_AD_CUR_P22			3236 		//	22	A对应AD值


extern	U16	U16_ad_value_12bit_resultOK[ENUM_AD_ID_NUM];	//已防抖12bit AD值		

/****************************************************************************************************
Function Name       :U8	App_NTC_Check(U8 channel)
Description         :NTC检测
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern	U8	App_NTC_Check(U8 channel);	
/****************************************************************************************************
Function Name       :void	App_ADCLookupTemperatureTable(U8 channel)
Description         :查表获取温度值
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern	void	App_ADCLookupTemperatureTable(U8 channel);

/****************************************************************************************************
Function Name       :void	App_LookUpTemperature(void)
Description         :汇总所有温度查表获取
Input               :
Return              :
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
extern	void	App_LookUpTemperature(void);

#endif
