#include "main.h"
#include "stm32f10x.h"
#include "led.h"

void led_init(int a)
{
	if(a){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 5000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 7200-1;		
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  
	
  TIM_CtrlPWMOutputs(TIM4,ENABLE);	//MOE 主输出使能	
  TIM_CtrlPWMOutputs(TIM3,ENABLE);
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能	
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
		
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM3, ENABLE);	
	led_all_off();
	
	
}else{
    GPIO_InitTypeDef GPIO_InitStructure;
    
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=LED_RED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(LED_RED_GPIO_PART,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=LED_GREEN_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(LED_GREEN_GPIO_PART,&GPIO_InitStructure);
    
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=LED_ARED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(LED_ARED_GPIO_PART,&GPIO_InitStructure);
   
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=LED_AGREEN_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(LED_AGREEN_GPIO_PART,&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=LED_ABLUE_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(LED_ABLUE_GPIO_PART,&GPIO_InitStructure);
		
		led_all_off();
		
}
		
}
void led_all_on(void){
	GPIO_ResetBits(LED_RED_GPIO_PART,LED_RED_GPIO_PIN);
	GPIO_ResetBits(LED_GREEN_GPIO_PART,LED_GREEN_GPIO_PIN);
	GPIO_ResetBits(LED_ARED_GPIO_PART,LED_ARED_GPIO_PIN);
	GPIO_ResetBits(LED_AGREEN_GPIO_PART,LED_AGREEN_GPIO_PIN);
	GPIO_ResetBits(LED_ABLUE_GPIO_PART,LED_ABLUE_GPIO_PIN);
	
	TIM_SetCompare3(TIM4,2);
	TIM_SetCompare4(TIM4,2);
	TIM_SetCompare2(TIM3,2);
	TIM_SetCompare1(TIM4,2);
	TIM_SetCompare2(TIM4,2);

}
void led_all_off(void){
	GPIO_SetBits(LED_RED_GPIO_PART,LED_RED_GPIO_PIN);
	GPIO_SetBits(LED_GREEN_GPIO_PART,LED_GREEN_GPIO_PIN);
	GPIO_SetBits(LED_ARED_GPIO_PART,LED_ARED_GPIO_PIN);
	GPIO_SetBits(LED_AGREEN_GPIO_PART,LED_AGREEN_GPIO_PIN);
	GPIO_SetBits(LED_ABLUE_GPIO_PART,LED_ABLUE_GPIO_PIN);

	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,0);

}

void led_red_on(void){	TIM_SetCompare3(TIM4,2);GPIO_ResetBits(LED_RED_GPIO_PART,LED_RED_GPIO_PIN);}
void led_red_off(void){	TIM_SetCompare3(TIM4,0);GPIO_SetBits(LED_RED_GPIO_PART,LED_RED_GPIO_PIN);}
void led_green_on(void){	TIM_SetCompare4(TIM4,2);GPIO_ResetBits(LED_GREEN_GPIO_PART,LED_GREEN_GPIO_PIN);}
void led_green_off(void){	TIM_SetCompare4(TIM4,0);GPIO_SetBits(LED_GREEN_GPIO_PART,LED_GREEN_GPIO_PIN);}
void led_ared_on(void){	TIM_SetCompare2(TIM3,2);GPIO_ResetBits(LED_ARED_GPIO_PART,LED_ARED_GPIO_PIN);}
void led_ared_off(void){	TIM_SetCompare2(TIM3,0);GPIO_SetBits(LED_ARED_GPIO_PART,LED_ARED_GPIO_PIN);}
void led_agreen_on(void){	TIM_SetCompare1(TIM4,2);GPIO_ResetBits(LED_AGREEN_GPIO_PART,LED_AGREEN_GPIO_PIN);}
void led_agreen_off(void){	TIM_SetCompare1(TIM4,0);GPIO_SetBits(LED_AGREEN_GPIO_PART,LED_AGREEN_GPIO_PIN);}
void led_ablue_on(void){	TIM_SetCompare2(TIM4,2);GPIO_ResetBits(LED_ABLUE_GPIO_PART,LED_ABLUE_GPIO_PIN);}
void led_ablue_off(void){	TIM_SetCompare2(TIM4,0);GPIO_SetBits(LED_ABLUE_GPIO_PART,LED_ABLUE_GPIO_PIN);}

void led_red_blink(int a){	switch (a) {case 1:TIM_SetCompare3(TIM4,1); case 2:TIM_SetCompare3(TIM4,3); default:TIM_SetCompare3(TIM4,1); } }
void led_green_blink(void){TIM_SetCompare4(TIM4,1);}
void led_ared_blink(void){TIM_SetCompare2(TIM3,1);}
void led_agreen_blink(void){TIM_SetCompare1(TIM4,1);}
void led_ablue_blink(void){TIM_SetCompare2(TIM4,1);}
