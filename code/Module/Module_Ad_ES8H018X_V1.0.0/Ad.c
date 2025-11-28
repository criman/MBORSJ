/*===================================================================================================
                		Copyright(C) 2011-2099.  SunRam. Co., Ltd.
-----------------------------------------------------------------------------------------------------
Project Name  		: Ad.c
Description   		: C
Author        		: Wuhaiming
Start Date    		: 2022/03/30
Version       		: V1.0
Revision History   1:
                   2:
===================================================================================================*/ 

#include	"main.h"


const    unsigned char    U8_ad_channel_table[ENUM_AD_ID_NUM]__attribute__((at(0x00007000))) =
{
    #ifdef		AD_AN0_ENABLE
    ADC_CH_0,
    #endif

    #ifdef		AD_AN1_ENABLE
    ADC_CH_1,
    #endif	

    #ifdef		AD_AN2_ENABLE
    ADC_CH_2,
    #endif

    #ifdef		AD_AN3_ENABLE
    ADC_CH_3,
    #endif

    #ifdef		AD_AN4_ENABLE
    ADC_CH_4,
    #endif

    #ifdef		AD_AN5_ENABLE
    ADC_CH_5,
    #endif

    #ifdef		AD_AN6_ENABLE
    ADC_CH_6,
    #endif

    #ifdef		AD_AN7_ENABLE
    ADC_CH_7,
    #endif

    #ifdef		AD_AN8_ENABLE
    ADC_CH_8,
    #endif

    #ifdef		AD_AN9_ENABLE
    ADC_CH_9,
    #endif

    #ifdef		AD_AN10_ENABLE
    ADC_CH_10,
    #endif

    #ifdef		AD_AN11_ENABLE
    ADC_CH_11,
    #endif	

    #ifdef		AD_AN12_ENABLE
    ADC_CH_12,
    #endif

    #ifdef		AD_AN13_ENABLE
    ADC_CH_13,
    #endif

    #ifdef		AD_AN14_ENABLE
    ADC_CH_14,
    #endif

    #ifdef		AD_AN15_ENABLE
    ADC_CH_15,
    #endif

    #ifdef		AD_AN16_ENABLE
    ADC_CH_16,
    #endif

    #ifdef		AD_AN17_ENABLE
    ADC_CH_17,
    #endif

    #ifdef		AD_AN18_ENABLE
    ADC_CH_18,
    #endif

    #ifdef		AD_AN19_ENABLE
    ADC_CH_19,
    #endif

    #ifdef		AD_AN20_ENABLE
    ADC_CH_20,
    #endif

    #ifdef		AD_AN21_ENABLE
    ADC_CH_21,
    #endif	

    #ifdef		AD_AN22_ENABLE
    ADC_CH_22,
    #endif

    #ifdef		AD_AN23_ENABLE
    ADC_CH_23,
    #endif

    #ifdef		AD_AN24_ENABLE
    ADC_CH_24,
    #endif

    #ifdef		AD_AN25_ENABLE
    ADC_CH_25,
    #endif

    #ifdef		AD_AN26_ENABLE
    ADC_CH_26,
    #endif

    #ifdef		AD_AN27_ENABLE
    ADC_CH_27,
    #endif

};

typedef		struct
{
    unsigned	char	u8_sample;			    //ad采样次数
    unsigned	char	u8_scan;				//ad通道切换
    unsigned	int		u16_valuemax;
    unsigned	int		u16_valuemin;
    unsigned	int		u16_valuesum;
    unsigned	int		u16_value_new[ENUM_AD_ID_NUM];
    unsigned	int		u16_value_old[ENUM_AD_ID_NUM];
}STRUCT_AD;

typedef		union
{
    unsigned char	    variable[(ENUM_AD_ID_NUM<<2)+8];
    STRUCT_AD			var;
}UNION_AD;

UNION_AD	Ad;
/****************************************************************************************************
Function Name       :void	Module_Init_Ad(void)
Description         :AD使用的IO初始化程序
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Module_Init_Ad(void)
{
    //设置ADC的运行模式
    GPIO_InitStruType x;
    ADC_InitStruType y;
    memset(&x, 0, sizeof(x));
    memset(&y, 0, sizeof(y));
    x.GPIO_Signal = GPIO_Pin_Signal_Analog;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;

    #if defined		AD_AN0_ENABLE
    //AN0
	GPIO_Init(GPIOB, GPIO_Pin_5, &x);    //PB5
    y.ADC_ChS = ADC_CHS_AIN0;            //通道:AIN0		
    #endif

    #if defined		AD_AN1_ENABLE	
	//AN1
	GPIO_Init(GPIOB, GPIO_Pin_6, &x);    //PB6
    y.ADC_ChS = ADC_CHS_AIN1;            //通道:AIN1	
    #endif

    #if defined		AD_AN2_ENABLE
	//AN2
	GPIO_Init(GPIOB, GPIO_Pin_7, &x);    //PB7
    y.ADC_ChS = ADC_CHS_AIN2;            //通道:AIN2
    #endif

    #if defined		AD_AN3_ENABLE		
	//AN3
	GPIO_Init(GPIOA, GPIO_Pin_2, &x);    //PA2
    y.ADC_ChS = ADC_CHS_AIN3;            //通道:AIN3
    #endif

    #if defined		AD_AN4_ENABLE				
	//AN4
	GPIO_Init(GPIOA, GPIO_Pin_3, &x);    //PA3
    y.ADC_ChS = ADC_CHS_AIN4;            //通道:AIN4
    #endif

    #if defined		AD_AN5_ENABLE	
	//AN5
	GPIO_Init(GPIOA, GPIO_Pin_4, &x);    //PA4
    y.ADC_ChS = ADC_CHS_AIN5;            //通道:AIN5
    #endif

    #if defined		AD_AN6_ENABLE	
	//AN6
	GPIO_Init(GPIOA, GPIO_Pin_5, &x);    //PA5
    y.ADC_ChS = ADC_CHS_AIN6;            //通道:AIN6
    #endif

    #if defined		AD_AN7_ENABLE		
	//AN7
	GPIO_Init(GPIOA, GPIO_Pin_6, &x);    //PA6
    y.ADC_ChS = ADC_CHS_AIN7;            //通道:AIN7										
    #endif

    #if defined		AD_AN8_ENABLE		
	//AN8
	GPIO_Init(GPIOA, GPIO_Pin_7, &x);    //PA7
    y.ADC_ChS = ADC_CHS_AIN8;            //通道:AIN8
    #endif		

    #if defined		AD_AN9_ENABLE		
	//AN9
	GPIO_Init(GPIOA, GPIO_Pin_8, &x);    //PA8
    y.ADC_ChS = ADC_CHS_AIN9;            //通道:AIN9	
    #endif

    #if defined		AD_AN10_ENABLE
	//AN10
	GPIO_Init(GPIOA, GPIO_Pin_9, &x);    //PA9
    y.ADC_ChS = ADC_CHS_AIN10;           //通道:AIN10
    #endif

    #if defined		AD_AN11_ENABLE
	//AN11
	GPIO_Init(GPIOA, GPIO_Pin_10, &x);    //PA10
    y.ADC_ChS = ADC_CHS_AIN11;            //通道:AIN11
    #endif

    #if defined		AD_AN12_ENABLE
	//AN12
	GPIO_Init(GPIOA, GPIO_Pin_11, &x);    //PA11
    y.ADC_ChS = ADC_CHS_AIN12;            //通道:AIN12
    #endif

    #if defined		AD_AN13_ENABLE
	//AN13
	GPIO_Init(GPIOA, GPIO_Pin_12, &x);    //PA12
    y.ADC_ChS = ADC_CHS_AIN13;            //通道:AIN13
    #endif

    #if defined		AD_AN14_ENABLE
	//AN14
	GPIO_Init(GPIOA, GPIO_Pin_15, &x);    //PA15
    y.ADC_ChS = ADC_CHS_AIN14;            //通道:AIN14
    #endif

    #if defined		AD_AN15_ENABLE
	;//空
    #endif
    
    #if defined		AD_AN16_ENABLE
	//AN16
	GPIO_Init(GPIOB, GPIO_Pin_20, &x);    //PB20
    y.ADC_ChS = ADC_CHS_AIN16;            //通道:AIN16
    #endif		

    #if defined		AD_AN17_ENABLE
	//AN17
	GPIO_Init(GPIOB, GPIO_Pin_21, &x);    //PB21
    y.ADC_ChS = ADC_CHS_AIN17;            //通道:AIN17	
    #endif

    #if defined		AD_AN18_ENABLE
	;//空
    #endif

    #if defined		AD_AN19_ENABLE
	//AN19
	GPIO_Init(GPIOB, GPIO_Pin_25, &x);    //PB25
    y.ADC_ChS = ADC_CHS_AIN19;            //通道:AIN19	
    #endif

    #if defined		AD_AN20_ENABLE
	//AN20
	GPIO_Init(GPIOA, GPIO_Pin_20, &x);    //PA20
    y.ADC_ChS = ADC_CHS_AIN20;            //通道:AIN20	
    #endif

    #if defined		AD_AN21_ENABLE
	//AN21
	GPIO_Init(GPIOA, GPIO_Pin_24, &x);    //PA24
    y.ADC_ChS = ADC_CHS_AIN21;            //通道:AIN21	
    #endif

    #if defined		AD_AN22_ENABLE
	//AN22
	GPIO_Init(GPIOA, GPIO_Pin_19, &x);    //PA19
    y.ADC_ChS = ADC_CHS_AIN22;            //通道:AIN22	
    #endif

    #if defined		AD_AN23_ENABLE
	//AN23
	GPIO_Init(GPIOA, GPIO_Pin_22, &x);    //PA22
    y.ADC_ChS = ADC_CHS_AIN23;            //通道:AIN23		
    #endif

    #if defined		AD_AN24_ENABLE
	//AN24
	GPIO_Init(GPIOA, GPIO_Pin_23, &x);    //PA23
    y.ADC_ChS = ADC_CHS_AIN24;            //通道:AIN24			
    #endif    

    #if defined		AD_AN25_ENABLE
	//AN25
	GPIO_Init(GPIOA, GPIO_Pin_30, &x);    //PA30
    y.ADC_ChS = ADC_CHS_AIN25;            //通道:AIN25		
    #endif    

    #if defined		AD_AN26_ENABLE
	//AN26
	GPIO_Init(GPIOB, GPIO_Pin_14, &x);    //PB14
    y.ADC_ChS = ADC_CHS_AIN26;            //通道:AIN26			
    #endif  

    #if defined		AD_AN27_ENABLE
	//AN27
	GPIO_Init(GPIOB, GPIO_Pin_15, &x);    //PB15
    y.ADC_ChS = ADC_CHS_AIN27;            //通道:AIN27			
    #endif 
	
    y.ADC_ClkS = ADC_ClkS_PCLK;          //时钟:PCLK
    y.ADC_ClkDiv = ADC_ClkDiv_32;        //预分频:1:32  ADC转换时钟源一定要符合数据手册中ADC转换时钟源选择表
    y.ADC_BITSEL = ADC_BITSEL_12;        //分辨率:12位
    y.ADC_VrefP = ADC_VREFP_VDD;         //参考电压:VDD
    y.ADC_SampS = ADC_SMPS_HARD;         //AD采样模式选择:硬件
    y.ST = 7;
    y.ADC_VREFN = ADC_VREFN_SEL_VSS;
    ADC_Init(&y);                        //按照结构体的参数配置ADC

//    ADC_IE_Enable();                     //使能中断
//    NVIC_Init(NVIC_ADC_IRQn, NVIC_Priority_0, ENABLE);
    ADC_Enable();                        //使能ADC	
	
}
/****************************************************************************************************
Function Name       :void	Log_Ad(void)
Description         :AD采样
Input               :无
Return              :无
Author              :wuhaiming
Version             :V1.0
Revision History   1:
                   2:
****************************************************************************************************/
void	Log_Ad(void)
{
    unsigned int		adc_result;

	ADC->CHS.CHS = (ADC_TYPE_CHS)U8_ad_channel_table[Ad.var.u8_scan];	//打开当前AD通道

	ADC_Start();													//开始AD采样
	
	while (ADC_GetConvStatus() == SET);								//等待AD采样完毕

	ADC_ClearIFStatus(ADC_IF);										//清标志位

	adc_result = ADC_GetConvValue();								//读取AD值
	
    Ad.var.u16_valuesum += adc_result;

    if (Ad.var.u8_sample == 0)
    {
        Ad.var.u16_valuemax = adc_result;
        Ad.var.u16_valuemin = adc_result;
    }	
    else
    {
        if (adc_result > Ad.var.u16_valuemax)		Ad.var.u16_valuemax = adc_result;
        if (adc_result < Ad.var.u16_valuemin)		Ad.var.u16_valuemin = adc_result;		
    }			
            
    if (++Ad.var.u8_sample >= 10)
    {
        Ad.var.u8_sample = 0;

        Ad.var.u16_valuesum -= Ad.var.u16_valuemax;
        Ad.var.u16_valuesum -= Ad.var.u16_valuemin;
        Ad.var.u16_valuesum >>= 3;
        Ad.var.u16_value_new[Ad.var.u8_scan] = Ad.var.u16_valuesum;
        Ad.var.u16_valuesum = 0;
    
        if ((Ad.var.u16_value_new[Ad.var.u8_scan] <= ADC_VALUE_MIN) || (Ad.var.u16_value_new[Ad.var.u8_scan] >= ADC_VALUE_MAX))	//开路短路
        {
            Ad.var.u16_value_old[Ad.var.u8_scan] = Ad.var.u16_value_new[Ad.var.u8_scan];
        }
        else
        {
            if (Ad.var.u16_value_old[Ad.var.u8_scan] > Ad.var.u16_value_new[Ad.var.u8_scan])
            {
                if ((Ad.var.u16_value_old[Ad.var.u8_scan] - Ad.var.u16_value_new[Ad.var.u8_scan]) > ADC_VALUE_FD)
                {
                    Ad.var.u16_value_old[Ad.var.u8_scan] = Ad.var.u16_value_new[Ad.var.u8_scan];
                }
            }

            if (Ad.var.u16_value_old[Ad.var.u8_scan] < Ad.var.u16_value_new[Ad.var.u8_scan])
            {
                if ((Ad.var.u16_value_new[Ad.var.u8_scan] - Ad.var.u16_value_old[Ad.var.u8_scan]) > ADC_VALUE_FD)
                {
                    Ad.var.u16_value_old[Ad.var.u8_scan] = Ad.var.u16_value_new[Ad.var.u8_scan];
                }
            }						
        }
        
        U16_ad_value_12bit_resultOK[Ad.var.u8_scan] = Ad.var.u16_value_old[Ad.var.u8_scan];		//12位AD
        
        if (++Ad.var.u8_scan >= ENUM_AD_ID_NUM)
        {
            Ad.var.u8_scan = 0;
        
//            F_humi_turn = 1;		//如果有湿度检测的切换到湿度检测,没有湿度检测请屏蔽
        }
    }
		
}
