#include "main.h"
#include "stdlib.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "timer.h"
#include "powerlimit.h"
#include "gpio.h"



	
int main(void){
	
	int a = 1;
	int i = 0;
	peripheral_init();
	
	EN1_Disable();
	EN2_Disable();
	
	ledb1_on();
	/*
	for(a=1 ; a < 16; a++){
		//TIM_SetCompare4(TIM2,a*800/15);
		
		//delay_ms(100);
	}
	*/
	
	while(1){
		
	
		i = (i + 1) % 5000;
		delay_us(100);  //0.1ms
		
		if(i%10==0){    //1ms
			
		}
		if(i%20==0){    //2ms
			
		}
		if(i%200==0){    //20ms  50Hz
			
			//execute();
		}
		if(i%50000==0){    //500ms  2Hz
			ledb1_negation();
		}
		
	}
	
}

void peripheral_init(void){
	
	delay_init(72);
	GPIO_Initialize();
	usart_init();//115200
	tim2_init(2,1800);//frequency20kHz
	adc_init();
	
	//led_init();

}

