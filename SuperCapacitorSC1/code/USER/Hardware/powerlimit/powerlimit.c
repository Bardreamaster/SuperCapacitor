#include "main.h"
#include "powerlimit.h"
#include "stm32f10x.h"
#include "adc.h"
#include "led.h"
#include "switch.h"

PowerInformation PInfo;

fp32 i_MAX = 1.5;
fp32 v_MAX = 24;
fp32 p_MAX=40.0f;

fp32 pid_MAX = 0.0;



//************************************
uint16_t pwmval=0;//(50,7199)      //**
fp32 PID_outMax=7150;             //**
fp32 PID_outMin=50;               //** 
//************************************
fp32 kp=0.8;
fp32 ki=0.8;
fp32 kd=-1;
fp32 Pout=0;
fp32 Iout=0;
fp32 Dout=0;
fp32 PID_output=0;
fp32 Dbuf[3]={0,0,0};  //微分项 0最新 1上一次 2上上次
fp32 error[3]={0,0,0}; //误差项 0最新 1上一次 2上上次


void setpMAX(fp32 pmax){
	p_MAX = pmax;
}
fp32 getpMAX(void){
	return p_MAX;
}
void setiMAX(fp32 imax){
	p_MAX = imax;
}
fp32 getiMAX(void){
	return i_MAX;
}
void setvMAX(fp32 vmax){
	p_MAX = vmax;
}
fp32 getvMAX(void){
	return v_MAX;
}
void getInfo(PowerInformation *Info){
	
		Info->i_in=get_i_in();
    Info->i_load=get_i_load();
    Info->v_load=get_v_load();
    Info->v_in=get_v_in();
    Info->v_cap=get_v_cap();
    Info->p_in=Info->i_in * Info->v_in;
    Info->p_load=Info->i_load * Info->v_load;
    Info->p_cap=Info->p_load - Info->p_in;
        
}

void getMode(CurrentMode *Mode){
	getInfo(&PInfo);
	
	if(PInfo.v_in <= 27 && PInfo.v_in > 25.5){Mode->BATMode = Vhigh;}
	else if(PInfo.v_in <= 25.5 && PInfo.v_in > 22){Mode->BATMode = Vnormal;}
	else if(PInfo.v_in <= 22 && PInfo.v_in > 13.5){Mode->BATMode = Vlow;}
	else if(PInfo.v_in <= 13.5 && PInfo.v_in > -0.5){Mode->BATMode = offline;}
	else {Mode->BATMode = unknownerror;}
	
	if(PInfo.v_cap < 13.5 && PInfo.v_cap > 1.6){Mode->CAPMode = Vlow;}
	else if(PInfo.v_cap >= 13.5 && PInfo.p_cap < 27){Mode->CAPMode = Vnormal;}
	else if(PInfo.v_cap >= 27 && PInfo.v_cap <= 30){Mode->CAPMode = Vhigh;}
	else if(PInfo.v_cap <= 1.6 && PInfo.v_cap > -0.5){Mode->CAPMode = offline;}  //****************************!!!!!!
	else {Mode->CAPMode = unknownerror;}
	
	if(PInfo.p_load < 0){Mode->LoadMode = Pnegative;}
	else if(PInfo.p_load >= 0 && PInfo.p_load <= p_MAX){Mode->LoadMode = Pnormal;}
	else if(PInfo.p_load > p_MAX){Mode->LoadMode = Pbeyond;}
	else{Mode->LoadMode = unknownerror;}
	
	if(Mode->BATMode <= 0){Mode->BoardMode = VDDonly;}
	else if(Mode->BATMode > 0){Mode->BoardMode = BATonly;}
	else{Mode->LoadMode = unknownerror;}



}

void setLed(CurrentMode Mode){
	
	led_all_off();
	switch(Mode.BoardMode){
		case unknownerror :led_ared_on();break;
	//	case 0 :;break;
		case VDDonly :led_ablue_on();break;
		case BATonly :led_agreen_on();break;
	//	case 3 :break;
		default:led_ared_on();break;

	}
	switch(Mode.BATMode){
		case unknownerror :led_red_on();break;
		case offline :break;	
		case Vlow :break;
		case Vnormal :break;
		case Vhigh :break;
		default:break;
	}
	switch(Mode.CAPMode){
		case unknownerror :break;
		case offline :led_green_off();break;
		case Vnormal :led_green_on();break;
		case Vlow :led_green_off();break;
		case Vhigh :led_green_on();break;
		default:break;
	}
	switch(Mode.LoadMode){
		case unknownerror :break;
		case offline :break;
		case Pnegative :break;
		case Pnormal :break;
		case Pbeyond :break;
		default:break;
	}
}
void execute(CurrentMode Mode){

	if(Mode.BATMode>0){                                        //battery is online
		if(Mode.LoadMode <= offline ){													 		//load is offline
			if(Mode.CAPMode > offline){                               		//CAP is online
				charge('p');
				battery_off();
				capacitor_off();
			}else if(Mode.CAPMode <= offline){														//CAP is offline
				charge_off();
				battery_off();
				capacitor_off();
			}else{																									  		//CAP unknown
				charge_off();
				battery_off();
				capacitor_off();
			}
		}else if(Mode.LoadMode > offline){													//load is online
			if(Mode.CAPMode > Vlow){																			//CAP is OK
				if(Mode.LoadMode > 0 && Mode.LoadMode < Pbeyond){
					charge('p');
					battery_on();
				}else if(Mode.LoadMode == Pbeyond){
					//charge('p');																												// !!!important!!!
					charge_off();
					capacitor_on();
					battery_off();
				}else{
					charge_off();
					battery_on();
					capacitor_off();
				}
			}else if(Mode.CAPMode <= Vlow){																//CAP is low	
				charge('i');
				battery_on();
				capacitor_off();
			}else{																													//CAP is offline
				charge_off();
				battery_on();
				capacitor_off();
			}
		}else{																											//LOAD unknown
			charge_off();
			battery_off();
			capacitor_off();
		}

	}else{																									 //unknown
			charge_off();
			battery_off();
			capacitor_off();
	}

}

void charge(char mode){      	// there may be something more
		switch(mode){
		case 'p':
				kp=0.9;ki=1;
				pid_MAX = p_MAX;
				pwmval = pid_calc(PInfo.p_in); 
				break;
		case 'i':
				kp=0.1;ki=0.5;
				pid_MAX = i_MAX;
				pwmval = pid_calc(PInfo.i_in); 
				break;
		case 'v':
				pid_MAX = v_MAX;
				pwmval = pid_calc(PInfo.v_cap); 
				break;
		default:
				kp=0.5;ki=0.8;
				pid_MAX = p_MAX;
				pwmval = pid_calc(PInfo.p_in); 
	}
	
	if(chargeon == 0){charge_on();}
	TIM_SetCompare4(TIM2,pwmval);
	
}

uint16_t pid_calc(fp32 pid){

    error[2]=error[1];
    error[1]=error[0];
    error[0]=(pid_MAX - pid);
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

