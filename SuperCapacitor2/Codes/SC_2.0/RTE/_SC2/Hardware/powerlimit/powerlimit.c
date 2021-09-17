#include "main.h"
#include "powerlimit.h"
#include "stm32f10x.h"
#include "adc.h"
#include "timer.h"

fp32 p_MAX=1.0f;
fp32 p_MAX2=75;
fp32 v_MIN=13.5;

PowerInformation PInfo;

//************************************
uint16_t pwmval = 0;//      //**
fp32 PID_outMax = 1800;             //**
fp32 PID_outMin = 0;               //** 
//************************************
fp32 kp=1;
fp32 ki=1;
fp32 kd=-1;
fp32 Pout=0;
fp32 Iout=0;
fp32 Dout=0;
fp32 PID_output=0;
fp32 Dbuf[3]={0,0,0};  //微分项 0最新 1上一次 2上上次
fp32 error[3]={0,0,0}; //误差项 0最新 1上一次 2上上次

void powerlimit_init(void){
	PID_outMax = get_arrmax();             
	PID_outMin = 0;  
	
}
void setpMAX(fp32 pmax){
	p_MAX = pmax;
	p_MAX2 = p_MAX - 5;
}
fp32 getpMAX(void){
	return p_MAX;
}
void getInfo(PowerInformation *Info){
	
		Info->i_in=get_i_in();
    Info->i_load=get_i_out();
    Info->v_load=get_v_out();
    Info->v_in=get_v_in();
    Info->v_cap=get_v_cap();
    Info->p_in=Info->i_in * Info->v_in;
    Info->p_load=Info->i_load * Info->v_load;
    Info->p_cap=Info->p_load - Info->p_in;
        
}




void execute(){
		
}

void charge(void){                	// there may be something more
	
	getInfo(&PInfo);
	if(chargeon == 0){
		
		pwmval = pid_calc(PInfo.p_in);
    TIM_SetCompare4(TIM2,pwmval);
	}else{
		pwmval = pid_calc(PInfo.p_in);
    TIM_SetCompare4(TIM2,pwmval);
	}

}

uint16_t pid_calc(fp32 p_in){
    error[2]=error[1];
    error[1]=error[0];
    error[0]=(p_MAX - p_in);
    Pout = kp * error[0];
    Iout += ki * error[0];
    Dbuf[2]=Dbuf[1];
    Dbuf[1]=Dbuf[0];
    Dbuf[0]=(error[0] - error[1]);
    Dout = kd * Dbuf[0];
    PID_output=Pout+Iout+Dout;
    if(PID_output>PID_outMax)
        PID_output=PID_outMax;
    else if(PID_output<PID_outMin)
        PID_output=PID_outMin;
    return  PID_output;
}

