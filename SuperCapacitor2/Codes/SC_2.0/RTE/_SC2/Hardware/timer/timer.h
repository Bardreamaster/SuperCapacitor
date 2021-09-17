#ifndef TIMER_H
#define TIMER_H
#include "main.h"

extern uint8_t chargeon ;
void tim2_init(uint32_t psc,uint32_t arr);



void buck1_on(void);
void buck1_off(void);
void buck2_ctrl(uint16_t vpwm,uint16_t ipwm);
void buck2_on(void);
void buck2_off(void);
void buck2_ctrl(uint16_t vpwm,uint16_t ipwm);
fp32 get_arrmax(void);


#endif
