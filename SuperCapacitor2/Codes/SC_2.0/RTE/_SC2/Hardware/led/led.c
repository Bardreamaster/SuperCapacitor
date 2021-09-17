#include "led.h"
#include "stm32f10x_gpio.h"


void led_init(void){}
	
void ledb1_on(void){
	GPIO_ResetBits(LEDB1_GPIO_Port,LEDB1_Pin);//set 0 to turn led on
}

void ledb1_off(void){
	GPIO_SetBits(LEDB1_GPIO_Port,LEDB1_Pin);
}
void ledb1_negation(void){
	if ((LEDB1_GPIO_Port->IDR & LEDB1_Pin) != (uint32_t)Bit_RESET){
		GPIO_ResetBits(LEDB1_GPIO_Port,LEDB1_Pin);
  }
  else{
		GPIO_SetBits(LEDB1_GPIO_Port,LEDB1_Pin);
  }
}