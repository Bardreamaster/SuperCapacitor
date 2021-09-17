#ifndef LED_H
#define LED_H

#define LED_RED_GPIO_PART  GPIOB
#define LED_RED_GPIO_PIN  GPIO_Pin_8

#define LED_GREEN_GPIO_PART  GPIOB
#define LED_GREEN_GPIO_PIN  GPIO_Pin_9

#define LED_ARED_GPIO_PART  GPIOB
#define LED_ARED_GPIO_PIN  GPIO_Pin_5
#define LED_AGREEN_GPIO_PART  GPIOB
#define LED_AGREEN_GPIO_PIN  GPIO_Pin_6
#define LED_ABLUE_GPIO_PART  GPIOB
#define LED_ABLUE_GPIO_PIN  GPIO_Pin_7

void led_init(int);

void led_all_on(void);
void led_all_off(void);

void led_red_on(void);
void led_red_off(void);
void led_green_on(void);
void led_green_off(void);

void led_ared_on(void);
void led_ared_off(void);
void led_agreen_on(void);
void led_agreen_off(void);
void led_ablue_on(void);
void led_ablue_off(void);

void led_red_blink(int);
void led_green_blink(void);
void led_ared_blink(void);
void led_agreen_blink(void);
void led_ablue_blink(void);

#endif
