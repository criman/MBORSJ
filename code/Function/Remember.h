/*===================================================================================================
                		Copyright(C) 2011-2099.  SUNRAM. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Remember.h
Description   		: H
Author        		: Wuhaiming
Start Date    		: 2023/08/30
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#ifndef    _REMEMBER_H_

#define    _REMEMBER_H_

//===================================================================================================//
//选择EEP写保护控制端口
//---------------------------------------------------------------------------------------------------//
#define		EEPwren_SigValid						0//PowEnPTC工作端口电平		例子:高电平有效1/低电平有效0
//---------------------------------------------------------------------------------------------------//
#define		Pin_EEPwren							PortPin_Read(GPIOA, GPIO_Pin_10)//SWITCH1 IO端口选择			例子:P00/P0_0										
#define		P_EEPwren_Hi()						DEFINE_PA10_HI					//例子:DEFINE_P00_HI
#define		P_EEPwren_Low()						DEFINE_PA10_LOW					//例子:DEFINE_P00_LOW
#define		P_EEPwren_Output()					DEFINE_PA10_OUTPUT				//例子:DEFINE_P00_OUTPUT
#define		P_EEPwren_Input()					DEFINE_PA10_INPUT				//例子:DEFINE_P00_INPUT
#define		P_EEPwren_Enpull()					DEFINE_PA10_ENPULLUP			//例子:DEFINE_P00_ENPULL
#define		P_EEPwren_Dispull()					DEFINE_PA10_DISPULLUP			//例子:DEFINE_P00_DISPULL
//---------------------------------------------------------------------------------------------------//
#if (PowEn12V_SigValid == 1)
#define		P_EEPwren_On()						P_EEPwren_Hi()
#define		P_EEPwren_Off()						P_EEPwren_Low()
#else
#define		P_EEPwren_On()						P_EEPwren_Low()
#define		P_EEPwren_Off()						P_EEPwren_Hi()
#endif
//===================================================================================================//

//===================================================================================================//
//宏定义有效时，调整参数便于测试
//#define    C_REMEMBER_PARA_FOR_TEST
//===================================================================================================//

//EE数据头码
#ifndef    C_REMEMBER_PARA_FOR_TEST
#define    C_REMEMBER_HEAD							0xA4	
#else
#define    C_REMEMBER_HEAD							0xC9
#endif
//EE全零非法数据校验码
#define	   C_REMEMBER_INVALIDCHKSUM_H				((((U16)(C_REMEMBER_HEAD^0xFFFF))+1)>>8)
#define	   C_REMEMBER_INVALIDCHKSUM_L				((((U16)(C_REMEMBER_HEAD^0xFFFF))+1)&0xFF)

//功能类
#define    C_REMEMBER_MODEFUNC_ONOFF                ENUM_STATUS_OFF        	   //01.开关机	
#define    C_REMEMBER_MODEFUNC_WORKMODE             ENUM_SYSMODE_COLD	  	   //02.工作模式-默认制冷
#define    C_REMEMBER_MODEFUNC_SPEEDMODE            ENUM_FANMODE_AUTO          //03.风速-自动风
#define    C_REMEMBER_MODEFUNC_TEMPCSET_DFT         23	   					   //04.温度设定值(℃) - 23℃
#define    C_REMEMBER_MODEFUNC_COLDCSET_DFT         23	   					   //05.制冷温度设定值(℃) - 23℃
#define    C_REMEMBER_MODEFUNC_HEATCSET_DFT		    27						   //06.制热温度设定值(℃) - 27℃
#define    C_REMEMBER_MODEFUNC_TEMPFSET_DFT         73	   					   //07.温度设定值(℉) - 73℉
#define    C_REMEMBER_MODEFUNC_COLDFSET_DFT         73	   					   //08.制冷温度设定值(℉) - 73℉
#define    C_REMEMBER_MODEFUNC_HEATFSET_DFT		    81						   //09.制热温度设定值(℉) - 81℉
#define	   C_REMEMBER_MODEFUNC_TEMPUNIT			    1						   //10.温度单位-默认1：华氏度
#define	   C_REMEMBER_MODEFUNC_SWEEP			    0						   //10.摆风状态-默认0：关闭
#define	   C_REMEMBER_MODEFUNC_TIMER		  	    0						   //10.定时是否设定-默认无			
#define	   C_REMEMBER_MODEFUNC_SLEEP			    0						   //10.睡眠是否设定-默认无
#define	   C_REMEMBER_MODEFUNC_FLZ				    0						   //10.负离子是否设定-默认无
#define	   C_REMEMBER_MODEFUNC_WIFIPWRONOFF		    0						   //10.wifi电源开启标志-默认关			



#ifndef    C_REMEMBER_PARA_FOR_TEST  
//正常使用
//参数类	
//1.室内风速							   (rpm/10)	   13Byte
#define    C_REMEMBER_PARA01_00        125         //EEP.u8_rdBuf[17]//测试-商检
#define    C_REMEMBER_PARA01_01        150		   //EEP.u8_rdBuf[18]//测试-额定制冷
#define    C_REMEMBER_PARA01_02        150		   //EEP.u8_rdBuf[19]//测试-最小制冷
#define    C_REMEMBER_PARA01_03        150		   //EEP.u8_rdBuf[20]//测试-额定制热
#define    C_REMEMBER_PARA01_04        150		   //EEP.u8_rdBuf[21]//常规-制冷-强力风
#define    C_REMEMBER_PARA01_05        125		   //EEP.u8_rdBuf[22]//常规-制冷-高风
#define    C_REMEMBER_PARA01_06        105		   //EEP.u8_rdBuf[23]//常规-制冷-中风
#define    C_REMEMBER_PARA01_07        95		   //EEP.u8_rdBuf[24]//常规-制冷-低风
#define    C_REMEMBER_PARA01_08        80		   //EEP.u8_rdBuf[25]//常规-制冷-微风
#define    C_REMEMBER_PARA01_09        125		   //EEP.u8_rdBuf[26]//常规-制热-高风
#define    C_REMEMBER_PARA01_10        105		   //EEP.u8_rdBuf[27]//常规-制热-中风
#define    C_REMEMBER_PARA01_11        90		   //EEP.u8_rdBuf[28]//常规-制热-低风
#define    C_REMEMBER_PARA01_12        80		   //EEP.u8_rdBuf[29]//常规-制热-微风

//2.室外风速							   (rpm/10)	   12Byte
#define    C_REMEMBER_PARA02_00		   135	       //EEP.u8_rdBuf[30]//测试-额定制冷	
#define    C_REMEMBER_PARA02_01		   120	       //EEP.u8_rdBuf[31]//测试-最小制冷	
#define    C_REMEMBER_PARA02_02		   120	       //EEP.u8_rdBuf[32]//测试-额定制热	
#define    C_REMEMBER_PARA02_03		   120	       //EEP.u8_rdBuf[33]//常规-制冷-强力风	
#define    C_REMEMBER_PARA02_04		   120	       //EEP.u8_rdBuf[34]//常规-制冷-高风	
#define    C_REMEMBER_PARA02_05		   120	       //EEP.u8_rdBuf[35]//常规-制冷-中风	
#define    C_REMEMBER_PARA02_06		   95	       //EEP.u8_rdBuf[36]//常规-制冷-低风	
#define    C_REMEMBER_PARA02_07		   80	       //EEP.u8_rdBuf[37]//常规-制冷-微风	
#define    C_REMEMBER_PARA02_08		   120	       //EEP.u8_rdBuf[38]//常规-制热-高风	
#define    C_REMEMBER_PARA02_09		   120	       //EEP.u8_rdBuf[39]//常规-制热-中风	
#define    C_REMEMBER_PARA02_10		   100	       //EEP.u8_rdBuf[40]//常规-制热-低风	
#define    C_REMEMBER_PARA02_11		   80	       //EEP.u8_rdBuf[41]//常规-制热-微风	
                                       
//3.压缩机运行档位					   频率(Hz)	   32Byte
#define    C_REMEMBER_PARA03_00		   0		   //EEP.u8_rdBuf[42]//制冷档位FC0	
#define    C_REMEMBER_PARA03_01		   30	       //EEP.u8_rdBuf[43]//制冷档位FC1	
#define    C_REMEMBER_PARA03_02		   31	       //EEP.u8_rdBuf[44]//制冷档位FC2	
#define    C_REMEMBER_PARA03_03		   34	       //EEP.u8_rdBuf[45]//制冷档位FC3	
#define    C_REMEMBER_PARA03_04		   36	       //EEP.u8_rdBuf[46]//制冷档位FC4	
#define    C_REMEMBER_PARA03_05		   38	       //EEP.u8_rdBuf[47]//制冷档位FC5	
#define    C_REMEMBER_PARA03_06		   40	       //EEP.u8_rdBuf[48]//制冷档位FC6	
#define    C_REMEMBER_PARA03_07		   45	       //EEP.u8_rdBuf[49]//制冷档位FC7	
#define    C_REMEMBER_PARA03_08		   50	       //EEP.u8_rdBuf[50]//制冷档位FC8	
#define    C_REMEMBER_PARA03_09		   52	       //EEP.u8_rdBuf[51]//制冷档位FC9
#define    C_REMEMBER_PARA03_10		   55	       //EEP.u8_rdBuf[52]//制冷档位FC10--56->55 lcx	 
#define    C_REMEMBER_PARA03_11		   55	       //EEP.u8_rdBuf[53]//制冷档位FC11--56->55	
#define    C_REMEMBER_PARA03_12		   55	       //EEP.u8_rdBuf[54]//制冷档位FC12--56->55	
#define    C_REMEMBER_PARA03_13		   55	       //EEP.u8_rdBuf[55]//制冷档位FC13--56->55	
#define    C_REMEMBER_PARA03_14		   55	       //EEP.u8_rdBuf[56]//制冷档位FC14--56->55	
#define    C_REMEMBER_PARA03_15		   60	       //EEP.u8_rdBuf[57]//制冷档位FC15--56->55	FC15 55->60  改给董梅燕测试用 20240622
#define    C_REMEMBER_PARA03_16		   0		   //EEP.u8_rdBuf[58]//制热档位FH0	
#define    C_REMEMBER_PARA03_17		   30	       //EEP.u8_rdBuf[59]//制热档位FH1	
#define    C_REMEMBER_PARA03_18		   31	       //EEP.u8_rdBuf[60]//制热档位FH2	
#define    C_REMEMBER_PARA03_19		   34	       //EEP.u8_rdBuf[61]//制热档位FH3	
#define    C_REMEMBER_PARA03_20		   36	       //EEP.u8_rdBuf[62]//制热档位FH4	
#define    C_REMEMBER_PARA03_21		   38	       //EEP.u8_rdBuf[63]//制热档位FH5	
#define    C_REMEMBER_PARA03_22		   40	       //EEP.u8_rdBuf[64]//制热档位FH6	
#define    C_REMEMBER_PARA03_23		   45	       //EEP.u8_rdBuf[65]//制热档位FH7	
#define    C_REMEMBER_PARA03_24		   50	       //EEP.u8_rdBuf[66]//制热档位FH8	
#define    C_REMEMBER_PARA03_25		   52	       //EEP.u8_rdBuf[67]//制热档位FH9	
#define    C_REMEMBER_PARA03_26		   56	       //EEP.u8_rdBuf[68]//制热档位FH10	
#define    C_REMEMBER_PARA03_27		   56	       //EEP.u8_rdBuf[69]//制热档位FH11	
#define    C_REMEMBER_PARA03_28		   56	       //EEP.u8_rdBuf[70]//制热档位FH12	
#define    C_REMEMBER_PARA03_29		   56	       //EEP.u8_rdBuf[71]//制热档位FH13	
#define    C_REMEMBER_PARA03_30		   56	       //EEP.u8_rdBuf[72]//制热档位FH14	
#define    C_REMEMBER_PARA03_31		   56	       //EEP.u8_rdBuf[73]//制热档位FH15	
                                       
//4.制冷T4限频						   频率档位	   12Byte
#define    C_REMEMBER_PARA04_00		   2		   //EEP.u8_rdBuf[74]//T＜0℃		
#define    C_REMEMBER_PARA04_01		   2		   //EEP.u8_rdBuf[75]//0℃≤T＜10℃	
#define    C_REMEMBER_PARA04_02		   3		   //EEP.u8_rdBuf[76]//10℃≤T＜15℃	
#define    C_REMEMBER_PARA04_03		   4		   //EEP.u8_rdBuf[77]//10℃≤T＜20℃	
#define    C_REMEMBER_PARA04_04		   5		   //EEP.u8_rdBuf[78]//20℃≤T＜25℃	
#define    C_REMEMBER_PARA04_05		   15		   //EEP.u8_rdBuf[79]//25℃≤T＜30℃ FC10->FC15  改给董梅燕测试用 20240622	
#define    C_REMEMBER_PARA04_06		   15		   //EEP.u8_rdBuf[80]//30℃≤T＜33℃ FC10->FC15  改给董梅燕测试用 20240622	
#define    C_REMEMBER_PARA04_07		   15		   //EEP.u8_rdBuf[81]//33℃≤T＜40℃ FC10->FC15  改给董梅燕测试用 20240622	
#define    C_REMEMBER_PARA04_08		   8		   //EEP.u8_rdBuf[82]//40℃≤T＜45℃	
#define    C_REMEMBER_PARA04_09		   6		   //EEP.u8_rdBuf[83]//45℃≤T＜50℃	
#define    C_REMEMBER_PARA04_10		   2		   //EEP.u8_rdBuf[84]//50℃≤T＜55℃	
#define    C_REMEMBER_PARA04_11		   2		   //EEP.u8_rdBuf[85]//55℃≤T		
                                       
//5.制热T4限频						   频率档位	   14Byte
#define    C_REMEMBER_PARA05_00        10	       //EEP.u8_rdBuf[86]//T＜-10℃	    
#define    C_REMEMBER_PARA05_01        10	       //EEP.u8_rdBuf[87]//-10℃≤T＜-7℃	
#define    C_REMEMBER_PARA05_02        10	       //EEP.u8_rdBuf[88]//-7℃≤T＜-3℃	
#define    C_REMEMBER_PARA05_03        10	       //EEP.u8_rdBuf[89]//-3℃≤T＜-1℃	
#define    C_REMEMBER_PARA05_04        10	       //EEP.u8_rdBuf[90]//1℃≤T＜4℃	
#define    C_REMEMBER_PARA05_05        10	       //EEP.u8_rdBuf[91]//4℃≤T＜7℃	
#define    C_REMEMBER_PARA05_06        10	       //EEP.u8_rdBuf[92]//7℃≤T＜10℃	
#define    C_REMEMBER_PARA05_07        9	       //EEP.u8_rdBuf[93]//10℃≤T＜13℃	
#define    C_REMEMBER_PARA05_08        8	       //EEP.u8_rdBuf[94]//13℃≤T＜16℃	
#define    C_REMEMBER_PARA05_09        8	       //EEP.u8_rdBuf[95]//16℃≤T＜19℃	
#define    C_REMEMBER_PARA05_10        8	       //EEP.u8_rdBuf[96]//19℃≤T＜22℃	
#define    C_REMEMBER_PARA05_11        7	       //EEP.u8_rdBuf[97]//22℃≤T＜25℃	
#define    C_REMEMBER_PARA05_12        6	       //EEP.u8_rdBuf[98]//25℃≤T＜28℃	
#define    C_REMEMBER_PARA05_13        5	       //EEP.u8_rdBuf[99]//28℃≤T	    

//6.制冷运行室内风速对压缩机频率的控制	   最大档位	   5Byte
#define    C_REMEMBER_PARA06_00	       10	       //EEP.u8_rdBuf[100]//室内风机超高风时-E_
#define    C_REMEMBER_PARA06_01        10	       //EEP.u8_rdBuf[101]//室内风机高风时-E_	
#define    C_REMEMBER_PARA06_02        8	       //EEP.u8_rdBuf[102]//室内风机中风时-E_	
#define    C_REMEMBER_PARA06_03        8	       //EEP.u8_rdBuf[103]//室内风机低风时-E_	
#define    C_REMEMBER_PARA06_04        6	       //EEP.u8_rdBuf[104]//室内风机微风时-E_	

//7.制热运行室内风速对压缩机频率的控制	   最大档位	   4Byte
#define    C_REMEMBER_PARA07_00		   10	       //EEP.u8_rdBuf[105]//室内风机高风时-E_	
#define    C_REMEMBER_PARA07_01		   8	       //EEP.u8_rdBuf[106]//室内风机中风时-E_	
#define    C_REMEMBER_PARA07_02		   8	       //EEP.u8_rdBuf[107]//室内风机低风时-E_	
#define    C_REMEMBER_PARA07_03		   6	       //EEP.u8_rdBuf[108]//室内风机微风时-E_	

//8.制热模式-管温矫正功能				  ℃		   8Byte
#define    C_REMEMBER_PARA08_00		   -2	       //EEP.u8_rdBuf[109]//室内风速中风时温度矫正	
#define    C_REMEMBER_PARA08_01		   -3	       //EEP.u8_rdBuf[110]//室内风速低风时温度矫正	
#define    C_REMEMBER_PARA08_02		   -4	       //EEP.u8_rdBuf[111]//室内风速微风时温度矫正	
#define    C_REMEMBER_PARA08_03		   52	       //EEP.u8_rdBuf[112]//T2_HEAT0				
#define    C_REMEMBER_PARA08_04		   53	       //EEP.u8_rdBuf[113]//T2_HEAT1				
#define    C_REMEMBER_PARA08_05		   54	       //EEP.u8_rdBuf[114]//T2_HEAT2				
#define    C_REMEMBER_PARA08_06		   59	       //EEP.u8_rdBuf[115]//T2_HEAT3				
#define    C_REMEMBER_PARA08_07		   63	       //EEP.u8_rdBuf[116]//T2_HEAT4				

//9.化霜功能							   ℃(含小数点) 9Byte
#define	   C_REMEMBER_PARA09_00		   -10		   //EEP.u8_rdBuf[117]//TDFI1		
#define	   C_REMEMBER_PARA09_01		   4		   //EEP.u8_rdBuf[118]//DELTA_TDF1	
#define	   C_REMEMBER_PARA09_02		   -6		   //EEP.u8_rdBuf[119]//TDFI2		
#define	   C_REMEMBER_PARA09_03		   5		   //EEP.u8_rdBuf[120]//DELTA_TDF2	
#define	   C_REMEMBER_PARA09_04		   -30		   //EEP.u8_rdBuf[121]//TDFI3		
#define	   C_REMEMBER_PARA09_05		   -2		   //EEP.u8_rdBuf[122]//TDFI4		
#define	   C_REMEMBER_PARA09_06		   30		   //EEP.u8_rdBuf[123]//TDFE1		
#define	   C_REMEMBER_PARA09_07		   16		   //EEP.u8_rdBuf[124]//TDFE2		

//10.化霜时运行频率					   档位		   1Byte
#define	   C_REMEMBER_PARA10_00		   10		   //EEP.u8_rdBuf[125]//化霜过程最大运行频率档位

//11.压缩机保护-排气温度保护			   ℃		   5Byte
#define	   C_REMEMBER_PARA11_00		   90		   //EEP.u8_rdBuf[126]//TP0
#define	   C_REMEMBER_PARA11_01		   95		   //EEP.u8_rdBuf[127]//TP1
#define	   C_REMEMBER_PARA11_02		   100		   //EEP.u8_rdBuf[128]//TP2
#define	   C_REMEMBER_PARA11_03		   105		   //EEP.u8_rdBuf[129]//TP3
#define	   C_REMEMBER_PARA11_04		   110		   //EEP.u8_rdBuf[130]//TP4

//12.制冷室内换热器的防冻结	           ℃(含小数点) 5Byte
#define	   C_REMEMBER_PARA12_00		   0		   //EEP.u8_rdBuf[131]//T2_COLD0
#define	   C_REMEMBER_PARA12_01		   4		   //EEP.u8_rdBuf[132]//T2_COLD1
#define	   C_REMEMBER_PARA12_02		   8		   //EEP.u8_rdBuf[133]//T2_COLD2
#define	   C_REMEMBER_PARA12_03		   11		   //EEP.u8_rdBuf[134]//T2_COLD3
#define	   C_REMEMBER_PARA12_04		   14		   //EEP.u8_rdBuf[135]//T2_COLD4

//13.制冷室外换热器防过热	℃(含小数点)	5Byte
#define	   C_REMEMBER_PARA13_00		   104		   //EEP.u8_rdBuf[136]//T3_COOL0	
#define	   C_REMEMBER_PARA13_01		   116		   //EEP.u8_rdBuf[137]//T3_COOL1	
#define	   C_REMEMBER_PARA13_02		   120		   //EEP.u8_rdBuf[138]//T3_COOL2	
#define	   C_REMEMBER_PARA13_03		   124		   //EEP.u8_rdBuf[139]//T3_COOL3	
#define	   C_REMEMBER_PARA13_04		   128		   //EEP.u8_rdBuf[140]//T3_COOL4	

//14.压缩机延时启动保护	分钟(范围：0~20)	1Byte
#define	   C_REMEMBER_PARA14_00		   10		   //EEP.u8_rdBuf[141]//高负荷启停待机时间

//15.测试模式压缩机运行档位(范围：1~15)	3Byte
#define	   C_REMEMBER_PARA15_00		   10		   //EEP.u8_rdBuf[142]//额定制冷压机运行档位
#define	   C_REMEMBER_PARA15_01		   1		   //EEP.u8_rdBuf[143]//最小制冷压机运行档位
#define	   C_REMEMBER_PARA15_02		   10		   //EEP.u8_rdBuf[144]//额定制热压机运行档位

#else
//测试使用
//参数类	
//1.室内风速							   (rpm/10)	   13Byte
#define    C_REMEMBER_PARA01_00        125         //EEP.u8_rdBuf[17]//测试-商检
#define    C_REMEMBER_PARA01_01        115		   //EEP.u8_rdBuf[18]//测试-额定制冷
#define    C_REMEMBER_PARA01_02        80		   //EEP.u8_rdBuf[19]//测试-最小制冷
#define    C_REMEMBER_PARA01_03        120		   //EEP.u8_rdBuf[20]//测试-额定制热
#define    C_REMEMBER_PARA01_04        115		   //EEP.u8_rdBuf[21]//常规-制冷-强力风
#define    C_REMEMBER_PARA01_05        105		   //EEP.u8_rdBuf[22]//常规-制冷-高风
#define    C_REMEMBER_PARA01_06        90		   //EEP.u8_rdBuf[23]//常规-制冷-中风
#define    C_REMEMBER_PARA01_07        80		   //EEP.u8_rdBuf[24]//常规-制冷-低风
#define    C_REMEMBER_PARA01_08        70		   //EEP.u8_rdBuf[25]//常规-制冷-微风
#define    C_REMEMBER_PARA01_09        120		   //EEP.u8_rdBuf[26]//常规-制热-高风
#define    C_REMEMBER_PARA01_10        100		   //EEP.u8_rdBuf[27]//常规-制热-中风
#define    C_REMEMBER_PARA01_11        90		   //EEP.u8_rdBuf[28]//常规-制热-低风
#define    C_REMEMBER_PARA01_12        70		   //EEP.u8_rdBuf[29]//常规-制热-微风

//2.室外风速							   (rpm/10)	   12Byte
#define    C_REMEMBER_PARA02_00		   105	       //EEP.u8_rdBuf[30]//测试-额定制冷	
#define    C_REMEMBER_PARA02_01		   80	       //EEP.u8_rdBuf[31]//测试-最小制冷	
#define    C_REMEMBER_PARA02_02		   100	       //EEP.u8_rdBuf[32]//测试-额定制热	
#define    C_REMEMBER_PARA02_03		   105	       //EEP.u8_rdBuf[33]//常规-制冷-强力风	
#define    C_REMEMBER_PARA02_04		   105	       //EEP.u8_rdBuf[34]//常规-制冷-高风	
#define    C_REMEMBER_PARA02_05		   105	       //EEP.u8_rdBuf[35]//常规-制冷-中风	
#define    C_REMEMBER_PARA02_06		   105	       //EEP.u8_rdBuf[36]//常规-制冷-低风	
#define    C_REMEMBER_PARA02_07		   70	       //EEP.u8_rdBuf[37]//常规-制冷-微风	
#define    C_REMEMBER_PARA02_08		   100	       //EEP.u8_rdBuf[38]//常规-制热-高风	
#define    C_REMEMBER_PARA02_09		   100	       //EEP.u8_rdBuf[39]//常规-制热-中风	
#define    C_REMEMBER_PARA02_10		   100	       //EEP.u8_rdBuf[40]//常规-制热-低风	
#define    C_REMEMBER_PARA02_11		   70	       //EEP.u8_rdBuf[41]//常规-制热-微风	
                                       
//3.压缩机运行档位					   频率(Hz)	   32Byte
#define    C_REMEMBER_PARA03_00		   0		   //EEP.u8_rdBuf[42]//制冷档位FC0	
#define    C_REMEMBER_PARA03_01		   16	       //EEP.u8_rdBuf[43]//制冷档位FC1	
#define    C_REMEMBER_PARA03_02		   20	       //EEP.u8_rdBuf[44]//制冷档位FC2	
#define    C_REMEMBER_PARA03_03		   25	       //EEP.u8_rdBuf[45]//制冷档位FC3	
#define    C_REMEMBER_PARA03_04		   30	       //EEP.u8_rdBuf[46]//制冷档位FC4	
#define    C_REMEMBER_PARA03_05		   34	       //EEP.u8_rdBuf[47]//制冷档位FC5	
#define    C_REMEMBER_PARA03_06		   36	       //EEP.u8_rdBuf[48]//制冷档位FC6	
#define    C_REMEMBER_PARA03_07		   38	       //EEP.u8_rdBuf[49]//制冷档位FC7	
#define    C_REMEMBER_PARA03_08		   42	       //EEP.u8_rdBuf[50]//制冷档位FC8	
#define    C_REMEMBER_PARA03_09		   45	       //EEP.u8_rdBuf[51]//制冷档位FC9	
#define    C_REMEMBER_PARA03_10		   48//47	       //EEP.u8_rdBuf[52]//制冷档位FC10	
#define    C_REMEMBER_PARA03_11		   50	       //EEP.u8_rdBuf[53]//制冷档位FC11	
#define    C_REMEMBER_PARA03_12		   52//50	       //EEP.u8_rdBuf[54]//制冷档位FC12	
#define    C_REMEMBER_PARA03_13		   54//50	       //EEP.u8_rdBuf[55]//制冷档位FC13	
#define    C_REMEMBER_PARA03_14		   56//50	       //EEP.u8_rdBuf[56]//制冷档位FC14	
#define    C_REMEMBER_PARA03_15		   58//50	       //EEP.u8_rdBuf[57]//制冷档位FC15	
#define    C_REMEMBER_PARA03_16		   0		   //EEP.u8_rdBuf[58]//制热档位FH0	
#define    C_REMEMBER_PARA03_17		   16	       //EEP.u8_rdBuf[59]//制热档位FH1	
#define    C_REMEMBER_PARA03_18		   20	       //EEP.u8_rdBuf[60]//制热档位FH2	
#define    C_REMEMBER_PARA03_19		   25	       //EEP.u8_rdBuf[61]//制热档位FH3	
#define    C_REMEMBER_PARA03_20		   30	       //EEP.u8_rdBuf[62]//制热档位FH4	
#define    C_REMEMBER_PARA03_21		   34	       //EEP.u8_rdBuf[63]//制热档位FH5	
#define    C_REMEMBER_PARA03_22		   36	       //EEP.u8_rdBuf[64]//制热档位FH6	
#define    C_REMEMBER_PARA03_23		   38	       //EEP.u8_rdBuf[65]//制热档位FH7	
#define    C_REMEMBER_PARA03_24		   42	       //EEP.u8_rdBuf[66]//制热档位FH8	
#define    C_REMEMBER_PARA03_25		   45	       //EEP.u8_rdBuf[67]//制热档位FH9	
#define    C_REMEMBER_PARA03_26		   48//47	       //EEP.u8_rdBuf[68]//制热档位FH10	
#define    C_REMEMBER_PARA03_27		   50	       //EEP.u8_rdBuf[69]//制热档位FH11	
#define    C_REMEMBER_PARA03_28		   52//50	       //EEP.u8_rdBuf[70]//制热档位FH12	
#define    C_REMEMBER_PARA03_29		   54//50	       //EEP.u8_rdBuf[71]//制热档位FH13	
#define    C_REMEMBER_PARA03_30		   56//50	       //EEP.u8_rdBuf[72]//制热档位FH14	
#define    C_REMEMBER_PARA03_31		   58//50	       //EEP.u8_rdBuf[73]//制热档位FH15	
                                       
//4.制冷T4限频						   频率档位	   12Byte
#define    C_REMEMBER_PARA04_00		   3		   //EEP.u8_rdBuf[74]//T＜0℃		
#define    C_REMEMBER_PARA04_01		   4		   //EEP.u8_rdBuf[75]//0℃≤T＜10℃	
#define    C_REMEMBER_PARA04_02		   5//6		   //EEP.u8_rdBuf[76]//10℃≤T＜15℃	
#define    C_REMEMBER_PARA04_03		   6//8		   //EEP.u8_rdBuf[77]//10℃≤T＜20℃	
#define    C_REMEMBER_PARA04_04		   7//9		   //EEP.u8_rdBuf[78]//20℃≤T＜25℃	
#define    C_REMEMBER_PARA04_05		   8//10		   //EEP.u8_rdBuf[79]//25℃≤T＜30℃	
#define    C_REMEMBER_PARA04_06		   15//10		   //EEP.u8_rdBuf[80]//30℃≤T＜33℃	
#define    C_REMEMBER_PARA04_07		   10		   //EEP.u8_rdBuf[81]//33℃≤T＜40℃	
#define    C_REMEMBER_PARA04_08		   9//0		   //EEP.u8_rdBuf[82]//40℃≤T＜45℃	
#define    C_REMEMBER_PARA04_09		   8//0		   //EEP.u8_rdBuf[83]//45℃≤T＜50℃	
#define    C_REMEMBER_PARA04_10		   7//0		   //EEP.u8_rdBuf[84]//50℃≤T＜55℃	
#define    C_REMEMBER_PARA04_11		   0		   //EEP.u8_rdBuf[85]//55℃≤T		
                                       
//5.制热T4限频						   频率档位	   14Byte
#define    C_REMEMBER_PARA05_00        4//10	       //EEP.u8_rdBuf[86]//T＜-10℃	    
#define    C_REMEMBER_PARA05_01        5//10	       //EEP.u8_rdBuf[87]//-10℃≤T＜-7℃	
#define    C_REMEMBER_PARA05_02        6//10	       //EEP.u8_rdBuf[88]//-7℃≤T＜-3℃	
#define    C_REMEMBER_PARA05_03        7//10	       //EEP.u8_rdBuf[89]//-3℃≤T＜-1℃	
#define    C_REMEMBER_PARA05_04        8//10	       //EEP.u8_rdBuf[90]//1℃≤T＜4℃	
#define    C_REMEMBER_PARA05_05        9//10	       //EEP.u8_rdBuf[91]//4℃≤T＜7℃	
#define    C_REMEMBER_PARA05_06        10	       //EEP.u8_rdBuf[92]//7℃≤T＜10℃	
#define    C_REMEMBER_PARA05_07        15//10	       //EEP.u8_rdBuf[93]//10℃≤T＜13℃	
#define    C_REMEMBER_PARA05_08        6//10	       //EEP.u8_rdBuf[94]//13℃≤T＜16℃	
#define    C_REMEMBER_PARA05_09        5//10	       //EEP.u8_rdBuf[95]//16℃≤T＜19℃	
#define    C_REMEMBER_PARA05_10        4//10	       //EEP.u8_rdBuf[96]//19℃≤T＜22℃	
#define    C_REMEMBER_PARA05_11        3//2	       //EEP.u8_rdBuf[97]//22℃≤T＜25℃	
#define    C_REMEMBER_PARA05_12        2	       //EEP.u8_rdBuf[98]//25℃≤T＜28℃	
#define    C_REMEMBER_PARA05_13        1//2	       //EEP.u8_rdBuf[99]//28℃≤T	    

//6.制冷运行室内风速对压缩机频率的控制	   最大档位	   5Byte
#define    C_REMEMBER_PARA06_00	       15//10	       //EEP.u8_rdBuf[100]//室内风机超高风时-E_
#define    C_REMEMBER_PARA06_01        15//10	       //EEP.u8_rdBuf[101]//室内风机高风时-E_	
#define    C_REMEMBER_PARA06_02        8	       //EEP.u8_rdBuf[102]//室内风机中风时-E_	
#define    C_REMEMBER_PARA06_03        7//8	       //EEP.u8_rdBuf[103]//室内风机低风时-E_	
#define    C_REMEMBER_PARA06_04        6	       //EEP.u8_rdBuf[104]//室内风机微风时-E_	

//7.制热运行室内风速对压缩机频率的控制	   最大档位	   4Byte
#define    C_REMEMBER_PARA07_00		   15//10	       //EEP.u8_rdBuf[105]//室内风机高风时-E_	
#define    C_REMEMBER_PARA07_01		   9//8	       //EEP.u8_rdBuf[106]//室内风机中风时-E_	
#define    C_REMEMBER_PARA07_02		   8	       //EEP.u8_rdBuf[107]//室内风机低风时-E_	
#define    C_REMEMBER_PARA07_03		   6	       //EEP.u8_rdBuf[108]//室内风机微风时-E_	

//8.制热模式-管温矫正功能				  ℃		   8Byte
#define    C_REMEMBER_PARA08_00		   -2	       //EEP.u8_rdBuf[109]//室内风速中风时温度矫正	
#define    C_REMEMBER_PARA08_01		   -3	       //EEP.u8_rdBuf[110]//室内风速低风时温度矫正	
#define    C_REMEMBER_PARA08_02		   -4	       //EEP.u8_rdBuf[111]//室内风速微风时温度矫正	
#define    C_REMEMBER_PARA08_03		   52	       //EEP.u8_rdBuf[112]//T2_HEAT0				
#define    C_REMEMBER_PARA08_04		   53	       //EEP.u8_rdBuf[113]//T2_HEAT1				
#define    C_REMEMBER_PARA08_05		   54	       //EEP.u8_rdBuf[114]//T2_HEAT2				
#define    C_REMEMBER_PARA08_06		   59	       //EEP.u8_rdBuf[115]//T2_HEAT3				
#define    C_REMEMBER_PARA08_07		   63	       //EEP.u8_rdBuf[116]//T2_HEAT4				

//9.化霜功能							   ℃(含小数点) 9Byte
#define	   C_REMEMBER_PARA09_00		   -10		   //EEP.u8_rdBuf[117]//TDFI1		
#define	   C_REMEMBER_PARA09_01		   4		   //EEP.u8_rdBuf[118]//DELTA_TDF1	
#define	   C_REMEMBER_PARA09_02		   -6		   //EEP.u8_rdBuf[119]//TDFI2		
#define	   C_REMEMBER_PARA09_03		   5		   //EEP.u8_rdBuf[120]//DELTA_TDF2	
#define	   C_REMEMBER_PARA09_04		   -30		   //EEP.u8_rdBuf[121]//TDFI3		
#define	   C_REMEMBER_PARA09_05		   -2		   //EEP.u8_rdBuf[122]//TDFI4		
#define	   C_REMEMBER_PARA09_06		   30		   //EEP.u8_rdBuf[123]//TDFE1		
#define	   C_REMEMBER_PARA09_07		   16		   //EEP.u8_rdBuf[124]//TDFE2		

//10.化霜时运行频率					   档位		   1Byte
#define	   C_REMEMBER_PARA10_00		   10		   //EEP.u8_rdBuf[125]//化霜过程最大运行频率档位

//11.压缩机保护-排气温度保护			   ℃		   5Byte
#define	   C_REMEMBER_PARA11_00		   90		   //EEP.u8_rdBuf[126]//TP0
#define	   C_REMEMBER_PARA11_01		   95		   //EEP.u8_rdBuf[127]//TP1
#define	   C_REMEMBER_PARA11_02		   100		   //EEP.u8_rdBuf[128]//TP2
#define	   C_REMEMBER_PARA11_03		   105		   //EEP.u8_rdBuf[129]//TP3
#define	   C_REMEMBER_PARA11_04		   110		   //EEP.u8_rdBuf[130]//TP4

//12.制冷室内换热器的防冻结	           ℃(含小数点) 5Byte
#define	   C_REMEMBER_PARA12_00		   0		   //EEP.u8_rdBuf[131]//T2_COLD0
#define	   C_REMEMBER_PARA12_01		   4		   //EEP.u8_rdBuf[132]//T2_COLD1
#define	   C_REMEMBER_PARA12_02		   8		   //EEP.u8_rdBuf[133]//T2_COLD2
#define	   C_REMEMBER_PARA12_03		   11		   //EEP.u8_rdBuf[134]//T2_COLD3
#define	   C_REMEMBER_PARA12_04		   14		   //EEP.u8_rdBuf[135]//T2_COLD4

//13.制冷室外换热器防过热	℃(含小数点)	5Byte
#define	   C_REMEMBER_PARA13_00		   104		   //EEP.u8_rdBuf[136]//T3_COOL0	
#define	   C_REMEMBER_PARA13_01		   116		   //EEP.u8_rdBuf[137]//T3_COOL1	
#define	   C_REMEMBER_PARA13_02		   124		   //EEP.u8_rdBuf[138]//T3_COOL2	
#define	   C_REMEMBER_PARA13_03		   128		   //EEP.u8_rdBuf[139]//T3_COOL3	
#define	   C_REMEMBER_PARA13_04		   132		   //EEP.u8_rdBuf[140]//T3_COOL4	

//14.压缩机延时启动保护	分钟(范围：0~20)	1Byte
#define	   C_REMEMBER_PARA14_00		   10		   //EEP.u8_rdBuf[141]//高负荷启停待机时间

//15.测试模式压缩机运行档位(范围：1~15)	3Byte
#define	   C_REMEMBER_PARA15_00		   10		   //EEP.u8_rdBuf[142]//额定制冷压机运行档位
#define	   C_REMEMBER_PARA15_01		   1		   //EEP.u8_rdBuf[143]//最小制冷压机运行档位
#define	   C_REMEMBER_PARA15_02		   9//10		   //EEP.u8_rdBuf[144]//额定制热压机运行档位

#endif



typedef    struct
{
	U8	f_LVD_En	 :1;	//低电压检测
	U8  u7_LVD_Count :7;	//低电压检测防抖计时
	U8	u8_WriteDelay;		//写入延时
	U8	f_DataChange :1;	//数据有变化
	U8	f_AllDatInit :1;	//强制初始化EE
	U16	u16_InitKey;		//强制初始化EE密钥
	U8  u8_InitCnt;			//接收强制初始化指令计数
	
	U8	u8_DB_TempCSet; 	//调试，上电时状态
	
}STRUCT_REMEMBER;

extern    STRUCT_REMEMBER    Remember;

/****************************************************************************************************
Function Name       :void    Init_Pin_WP_Enable(void)
Description         :EE读写允许引脚初始化
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Init_Pin_WP_Enable(void);
/****************************************************************************************************
Function Name       :void    Remember_ReadEEFunc(void)
Description         :掉电记忆-读取EE数据(功能部分)
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_ReadEEFunc(void);
/****************************************************************************************************
Function Name       :void    Remember_WriteEEFunc(void)
Description         :掉电记忆-写入EE数据(功能部分)
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_WriteEEFunc(U8 ParaType);
/****************************************************************************************************
Function Name       :void    Remember_ReadEEPara(void)
Description         :掉电记忆-读取EE数据(参数部分)
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_ReadEEPara(void);
/****************************************************************************************************
Function Name       :void    Remember_WritePara(void)
Description         :掉电记忆-写入EE数据(参数部分)
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    Remember_WriteEEPara(U8 ParaType);
/****************************************************************************************************
Function Name       :void    LowVoltDetect(void)
Description         :低电压检测
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void    LowVoltDetect(void);
void    SaveDatToEEP(void);
void    Remember_EE_Dat_Init(void);

#endif
