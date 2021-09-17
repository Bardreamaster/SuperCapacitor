#include "gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


void GPIO_Initialize(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
	/*Configure GPIO pin Output Level */
  GPIO_WriteBit(LEDB1_GPIO_Port, LEDB1_Pin, Bit_RESET);
  GPIO_WriteBit(GPIOB, EN1_Pin|EN2_Pin, Bit_RESET);
  GPIO_WriteBit(POWEROUT1_CTRL_GPIO_Port, POWEROUT1_CTRL_Pin, Bit_RESET);

  /*Configure GPIO pin : LEDB1_Pin */
  GPIO_InitStructure.GPIO_Pin = LEDB1_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /*Configure GPIO pin : KEY1_Pin */
  GPIO_InitStructure.GPIO_Pin = KEY1_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /*Configure GPIO pins : PG1_Pin PG2_Pin */
  GPIO_InitStructure.GPIO_Pin = PG1_Pin|PG2_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /*Configure GPIO pins : EN1_Pin EN2_Pin */
  GPIO_InitStructure.GPIO_Pin = EN1_Pin|EN2_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(EN1_GPIO_Port,EN1_Pin|EN2_Pin); //enable
	
}

void EN1_Enable(void){GPIO_ResetBits(EN1_GPIO_Port,EN1_Pin);}
void EN1_Disable(void){GPIO_SetBits(EN1_GPIO_Port,EN1_Pin);}
void EN2_Enable(void){GPIO_ResetBits(EN2_GPIO_Port,EN1_Pin);}
void EN2_Disable(void){GPIO_SetBits(EN2_GPIO_Port,EN2_Pin);}
uint8_t get_PG1(void){
	if ((PG1_GPIO_Port->IDR & PG1_Pin) != (uint32_t)Bit_RESET){
		return Bit_SET;
  }
  else{
		return Bit_RESET;
  }
}
uint8_t get_PG2(void){
	if ((PG2_GPIO_Port->IDR & PG2_Pin) != (uint32_t)Bit_RESET){
		return Bit_SET;
  }
  else{
		return Bit_RESET;
  }
}
	
	
	