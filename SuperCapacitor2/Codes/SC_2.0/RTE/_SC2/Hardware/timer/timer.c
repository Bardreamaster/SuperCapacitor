#include "main.h"
#include "timer.h"
#include "stm32f10x.h"

uint8_t chargeon = 0;
uint32_t arrmax = 100;
void tim2_init(uint32_t psc,uint32_t arr){
	arrmax = arr;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);
	
	//设置该引脚为复用输出功能,输出TIM2 CH1,2的PWM脉冲波形                  1,2,3,4  V1,I1,I2,V2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 

  TIM_CtrlPWMOutputs(TIM2,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH1预装载使能	
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
	
	chargeon = 1;
	
	TIM_SetCompare2(TIM2,0);
	TIM_SetCompare3(TIM2,0);
	//TIM_SetCompare4(TIM2,135);//FSW switch frequency20kHz   2,1800 V300-1800 I0-1800  
}


void buck1_on(void){
	TIM_SetCompare2(TIM2,arrmax);
}

void buck1_off(void){
	TIM_SetCompare2(TIM2,0);
}
void buck1_ctrl(uint16_t vpwm,uint16_t ipwm){
	TIM_SetCompare1(TIM2,vpwm);
	TIM_SetCompare2(TIM2,ipwm);
}
void buck2_on(void){
	TIM_SetCompare3(TIM2,arrmax);
}
void buck2_off(void){
  TIM_SetCompare3(TIM2,0);
}
void buck2_ctrl(uint16_t vpwm,uint16_t ipwm){
	TIM_SetCompare3(TIM2,ipwm);
	TIM_SetCompare4(TIM2,vpwm);
}
fp32 get_arrmax(void){
	return (fp32)arrmax;
}

