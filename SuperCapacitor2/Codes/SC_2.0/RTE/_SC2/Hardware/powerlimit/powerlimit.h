#ifndef POWERLIMIT_H
#define POWERLIMIT_H
#include "main.h"

typedef struct
{
  fp32 i_in;
	fp32 v_in;
	fp32 p_in;
  fp32 v_cap;
  fp32 p_cap;     // p.load - p.in
	fp32 i_load;
  fp32 v_load;
  fp32 p_load;
}PowerInformation;

void powerlimit_init(void);
void setpMAX(fp32 pmax);
fp32 getpMAX(void);
void getInfo(PowerInformation *Info);
void execute(void);
void charge(void);
uint16_t pid_calc(fp32 p_cap);

#endif
