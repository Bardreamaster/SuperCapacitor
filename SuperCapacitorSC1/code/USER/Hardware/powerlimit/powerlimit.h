#ifndef POWERLIMIT_H
#define POWERLIMIT_H
#include "main.h"

extern fp32 i_MAX;
extern fp32 v_MAx;
extern fp32 p_MAX;
extern fp32 pid_MAX;



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

enum{offline = 0, unknownerror = -1};
typedef enum {  VDDonly = 1,   BATonly = 2,      }BoardMode_TypeDef;
typedef enum {  Vlow = 1,      Vnormal = 2,   Vhigh = 3,    }BATMode_TypeDef;
typedef enum {  chargein = 1,  discharge = 2, stable = 3,   }CAPMode_TypeDef;
typedef enum {  Pnegative = 1, Pnormal = 2,   Pbeyond = 3,  }LoadMode_TypeDef;
    //     |offline|          online           |ERROR
	  //Board|       |VDDonly  |BATonly  |       |error
	  //BAT  |null   |low      |normal   |high   |error
	  //CAP  |null   |low      |normal   |high   |error
	  //Load |null   |negative |normal   |beyond |error
	  //     | 0     | 1       | 2       | 3     |  -1
typedef struct
{                 
	int BoardMode;  
	int BATMode;    
	int CAPMode;    
	int LoadMode;   
	int CANMode;
	                
}CurrentMode;     


void setpMAX(fp32 pmax);
fp32 getpMAX(void);
void setiMAX(fp32 imax);
fp32 geipMAX(void);
void setvMAX(fp32 vmax);
fp32 getvMAX(void);
void getInfo(PowerInformation *Info);
void getMode(CurrentMode *Mode);
void setLed(CurrentMode Mode);
void execute(CurrentMode Mode);
void charge(char mode);
uint16_t pid_calc(fp32 pid);

#endif
