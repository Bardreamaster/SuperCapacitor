#ifndef LED_H
#define LED_H

#define LEDB1_Pin GPIO_Pin_14
#define LEDB1_GPIO_Port GPIOC

void led_init(void);

void ledb1_on(void);
void ledb1_off(void);

void ledb1_negation(void);

#endif
