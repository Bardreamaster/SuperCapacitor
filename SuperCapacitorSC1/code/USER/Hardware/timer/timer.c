#include "main.h"
#include "timer.h"
#include "stm32f10x.h"

//void tim2_init(uint32_t psc,uint32_t arr)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
//	
//	//���ø�����Ϊ�����������,���TIM2 CH4��PWM���岨��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	TIM_TimeBaseStructure.TIM_Period = arr-1;
//	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;
//	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

//  TIM_CtrlPWMOutputs(TIM2,ENABLE);	//MOE �����ʹ��	

//	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	
//	
//	TIM_ARRPreloadConfig(TIM2, ENABLE);
//	
//	TIM_Cmd(TIM2, ENABLE);
//	
//			TIM_SetCompare4(TIM2,0);
//}
