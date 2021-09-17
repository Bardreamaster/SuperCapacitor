#ifndef GPIO_H
#define GPIO_H
#include "main.h"

#define LEDB1_Pin GPIO_Pin_14
#define LEDB1_GPIO_Port GPIOC
#define KEY1_Pin GPIO_Pin_15
#define KEY1_GPIO_Port GPIOC
#define VPWM1_Pin GPIO_Pin_0
#define VPWM1_GPIO_Port GPIOA
#define IPWM1_Pin GPIO_Pin_1
#define IPWM1_GPIO_Port GPIOA
#define VVOUT_Pin GPIO_Pin_3
#define VVOUT_GPIO_Port GPIOA
#define VVIN_Pin GPIO_Pin_6
#define VVIN_GPIO_Port GPIOA
#define VILIM1_Pin GPIO_Pin_7
#define VILIM1_GPIO_Port GPIOA
#define VVCAP_Pin GPIO_Pin_0
#define VVCAP_GPIO_Port GPIOB
#define VILIM2_Pin GPIO_P_1
#define VILIM2_GPIO_Port GPIOB
#define IPWM2_Pin GPIO_Pin_10
#define IPWM2_GPIO_Port GPIOB
#define VPWM2_Pin GPIO_Pin_11
#define VPWM2_GPIO_Port GPIOB
#define PG1_Pin GPIO_Pin_12
#define PG1_GPIO_Port GPIOB
#define EN1_Pin GPIO_Pin_13
#define EN1_GPIO_Port GPIOB
#define PG2_Pin GPIO_Pin_14
#define PG2_GPIO_Port GPIOB
#define EN2_Pin GPIO_Pin_15
#define EN2_GPIO_Port GPIOB
#define POWEROUT1_CTRL_Pin GPIO_Pin_8
#define POWEROUT1_CTRL_GPIO_Port GPIOA

void GPIO_Initialize(void);
void EN1_Enable(void);
void EN1_Disable(void);
void EN2_Enable(void);
void EN2_Disable(void);
uint8_t get_PG1(void);
uint8_t get_PG2(void);

#endif