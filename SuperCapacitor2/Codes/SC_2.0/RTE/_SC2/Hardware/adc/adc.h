#ifndef ADC_H
#define ADC_H
#include "main.h"

#define adc_to_v 3.3f/4096.0f
#define rilim1 10000.0f
#define rilim2 6040.0f
#define rss1 1000.0f
#define rss2 1000.0f
#define rsns1 0.01f
#define rsns2 0.01f
#define vref 1.21f

void adc_init(void);
fp32 get_i_in(void);
fp32 get_i_out(void);
fp32 get_v_out(void);
fp32 get_v_in(void);
fp32 get_v_cap(void);

#endif
