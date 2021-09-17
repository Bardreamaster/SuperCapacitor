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
//	//设置该引脚为复用输出功能,输出TIM2 CH4的PWM脉冲波形
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	TIM_TimeBaseStructure.TIM_Period = arr-1;
//	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;
//	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

//  TIM_CtrlPWMOutputs(TIM2,ENABLE);	//MOE 主输出使能	

//	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4预装载使能	
//	
//	TIM_ARRPreloadConfig(TIM2, ENABLE);
//	
//	TIM_Cmd(TIM2, ENABLE);
//	
//			TIM_SetCompare4(TIM2,0);
//}
