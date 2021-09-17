#include "main.h"
#include "stdlib.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "switch.h"
#include "powerlimit.h"


CurrentMode AllMode;

uint8_t batteryOn=0;
uint8_t chargeOn=1;
uint16_t xx = 135;

int main(void){
	int a = 1;
	int i = 0;
	peripheral_init();
	//getMode(&AllMode);
	//setLed(AllMode);
		
	for(i=0;i<150000;i++){
		getMode(&AllMode);
		charge('i');
		delay_us(100);
	}
	
	
		
	while(1){
		getMode(&AllMode);
	
		i = (i + 1) % 5000;
		delay_us(100);  //0.1ms
		
	

		if(i%10==0){    //1ms
			execute(AllMode);
		}
		if(i%20==0){    //2ms
			
		}
		if(i%100==0){    //10ms  100Hz
			
		}
		if(i%5000==0){    //500ms  2Hz
			setLed(AllMode);
		}
		
	}
	
}

void peripheral_init(void){
    switch_init();
		charge_off();
		usart_init();//115200
    led_init(0);
		delay_init(72);
		adc_init();
	
		//tim1_init();

}
