#include "main.h"
#include "adc.h"
#include "stm32f10x.h"

void adc_init(void)
{
		ADC_InitTypeDef ADC_InitStructure; 
		GPIO_InitTypeDef GPIO_InitStructure;

        
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
        //ADC1 CH8 PB0 VVCAP
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
		GPIO_Init(GPIOB, &GPIO_InitStructure);
    
        //ADC1 CH6 PA6 VVIN
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);

	 /*   //ADC1 CH3 PA3  VVOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
*/
	    //ADC1 CH7 PA3  VILIM1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			//ADC1 CH9 PA3  VILIM2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
		ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
		ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���  
	
		ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
		ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
		while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
		ADC_StartCalibration(ADC1);	 //����ADУ׼
 
		while(ADC_GetCalibrationStatus(ADC1));
		
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  
		ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  
		ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  
		ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	 
		ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	 		

        //ADC2 PA3 CH3 VVOUT
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_ADC2, ENABLE );	  //ʹ��ADC2ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14
				
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		ADC_DeInit(ADC2);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
		ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
		ADC_Init(ADC2, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���  
	
		ADC_Cmd(ADC2, ENABLE);	//ʹ��ָ����ADC1
	
		ADC_ResetCalibration(ADC2);	//ʹ�ܸ�λУ׼  
	 
		while(ADC_GetResetCalibrationStatus(ADC2));	//�ȴ���λУ׼����
	
		ADC_StartCalibration(ADC2);	 //����ADУ׼
 
		while(ADC_GetCalibrationStatus(ADC2));
		
		ADC_RegularChannelConfig(ADC2, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5 );	//ADC2,ADCͨ��,����ʱ��Ϊ239.5����

}

fp32 get_i_in(void)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_239Cycles5 );
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    return (ADC_GetConversionValue(ADC1) * adc_to_v * rss1 / rilim1 /rsns1) ;
}

fp32 get_i_out(void)
{
    ADC_RegularChannelConfig(ADC2, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5 );
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);
    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));
    
    return (ADC_GetConversionValue(ADC1) * adc_to_v * rss2 / rilim2 /rsns2 ) ;
}

fp32 get_v_out(void)
{
    ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 1, ADC_SampleTime_239Cycles5 );
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);
    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADC1) * adc_to_v * 11;
}

fp32 get_v_in(void)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_239Cycles5 );
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADC1) * adc_to_v * 11;
}
fp32 get_v_cap(void)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_239Cycles5 );
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADC1) * adc_to_v * 11;
}
