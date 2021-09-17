#ifndef SWITCH_H
#define SWITCH_H
#include "delay.h"
#include "usart.h"

extern uint8_t chargeon ;
void tim2_init(uint32_t psc,uint32_t arr);

void tim1_init(void);

void switch_init(void);
void battery_on(void);
void battery_off(void);
void capacitor_on(void);
void capacitor_off(void);
void charge_on(void);
void charge_off(void);
void DIODE_on(void);
void DIODE_off(void);


#endif
