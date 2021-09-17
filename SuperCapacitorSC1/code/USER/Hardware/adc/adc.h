#ifndef ADC_H
#define ADC_H
#include "main.h"

#define adc_to_v 3.3f/4096.0f
#define v_to_i_k 0.055f
#define v_to_i_b 1.641f

void adc_init(void);
fp32 get_i_in(void);
fp32 get_i_load(void);
fp32 get_v_load(void);
fp32 get_v_in(void);
fp32 get_v_cap(void);

#endif
