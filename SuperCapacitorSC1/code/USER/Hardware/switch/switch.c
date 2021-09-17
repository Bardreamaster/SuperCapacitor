#include "stm32f10x.h"
#include "switch.h"

uint8_t chargeon = 0;

void tim1_init(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
		TIM_BDTRInitTypeDef  TIM_BDTRInitStructure;

				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);  // 开启GPIO时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                                                 // 开启复用功能 
        // GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  因为这里不用重映射，所以不用写，有需要的必须写
        
        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    // 复用推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
        GPIO_Init(GPIOA, &GPIO_InitStructure);
       
        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    // 复用推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);        
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  /* 开启TIM1的时钟*/
  TIM_TimeBaseStructure.TIM_Prescaler = 71;
  /*  把系统工作频率分频后当做定时器的工作频率 ，比如72MHz，要得到1MHz定时器工作频率，*/
             
                                 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    
   /* TIM_CounterMode_Up                 TIM 向上计数模式
			TIM_CounterMode_Down               TIM 向下计数模式
			TIM_CounterMode_CenterAligned1     TIM 中央对齐模式 1 计数模式
			TIM_CounterMode_CenterAligned2     TIM 中央对齐模式 2 计数模式  */
          
  TIM_TimeBaseStructure.TIM_Period = (1000-1);  
   /* 这个参数和 TIM_Prescaler  构成 PWM的频率，即当TIM_Prescaler=71 时，TIM以1MHz的频率计数，当达到
      TIM_Period设定的个数时重新加载TIM_Period的值到寄存器，进行下一个循环，如果TIM_Period的值一直不变，
      PWM就已一个固定的周期输出，此处的PWM频率设置的是 1MHz/1000=1kHz。    */           
         
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;		
    /* 设置定时器时钟CK_INT频率与死区发生器以及数字滤波器采样时钟频率分频化，此处不用。   */
    						  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                         
   /* 对于某个占空比的PWM重复执行的次数，如果之前设置的占空比为50，那这个值设置为1的话，50%PWM会被执行
      两次，也就是连着上一次再执行一个周期   */

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);



	

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
   /*比较输出模式选择，共8种。value：
     TIM_OCMode_Timing                  TIM 输出比较时间模式
     TIM_OCMode_Active                  TIM 输出比较主动模式
     TIM_OCMode_Inactive                TIM 输出比较非主动模式
     TIM_OCMode_Toggle                  TIM 输出比较触发模式
     TIM_OCMode_PWM1                    TIM 脉冲宽度调制模式 1 
     TIM_OCMode_PWM2                    TIM 脉冲宽度调制模式 2  
     这PWM功能下，选TIM_OCMode_PWM1 或TIM_OCMode_PWM2 ，这里选后者 */

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;              
   /* 比较输出使能，决定信号是否通过外部引脚输出*/
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;            
   /* 互补使能，决定互补信号是否通过外部引脚输出*/
  TIM_OCInitStructure.TIM_Pulse = 0; 
   /* 初始化占空比                   */          
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
   /* 输出极性，决定定时器通道有效电平的极性*/
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
   /* 互补输出极性，可选高电平有效、低电平有效*/
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
   /* 空闲状态时通道输出电平设置，可选高电平、低电平*/
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
   /* 空闲状态时互补通道输出电平设置，可选高电平、低电平，设定值必须跟TIM_OCIdleState相反*/

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);


	

  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
   /* 运行模式下关闭状态选择*/
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
   /* 空闲模式下关闭状态选择*/
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
   /* 锁定配置
      00：锁定关闭，寄存器无写保护；
      01：锁定级别1，不能写入TIMx_BDTR寄存器的DTG、BKE、BKP、AOE位和     TIMx_CR2寄存器的OISx/OISxN位；
      10：锁定级别2，不能写入锁定级别1中的各位，也不能写入CC极性位(一旦相关通道通过CCxS位设为输出，CC极性位是TIMx_CCER寄存器的CCxP/CCNxP位)以及OSSR/OSSI位；
      11：锁定级别3，不能写入锁定级别2中的各位，也不能写入CC控制位(一旦相关通道通过CCxS位设为输出，CC控制位是TIMx_CCMRx寄存器的OCxM/OCxPE位)；
      注：在系统复位后，只能写一次LOCK位，一旦写入TIMx_BDTR寄存器，则其内容冻结直至复位。*/
  TIM_BDTRInitStructure.TIM_DeadTime = 20;
   /* 死区时间*/
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
   /* 刹车使能控制，如果需要刹车就需要另外配置一路GPIO*/
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
   /* 刹车输出极性*/
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
   /* 自动输出使能*/

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	TIM_SetCompare1(TIM1,500);
}

void tim2_init(uint32_t psc,uint32_t arr){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	//设置该引脚为复用输出功能,输出TIM2 CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

  //TIM_CtrlPWMOutputs(TIM2,ENABLE);	//MOE 主输出使能	

	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4预装载使能	
	
	//TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
	chargeon = 1;
	TIM_SetCompare4(TIM2,50);//FSW switch frequency 20kHz
}
void switch_init(void){ 
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
		
		//PA1 高电平电池供电路打开，低电平关断
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    
    //PA2 高电平超级电容供电路打开，低电平关断
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);
    
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    GPIO_ResetBits(GPIOA,GPIO_Pin_3);

		//PA15high->disable DIODE mode  , low enable DIODE mode.	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_15);

		DIODE_off();
		battery_on();
		capacitor_off();
	
}

void charge_on(void){
		chargeon = 1;
    tim2_init(1,7200); //FSW switch frequency 10kHz
}

void charge_off(void){
		chargeon = 0;
    GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}

void battery_on(void){
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
   
}
void battery_off(void){
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void capacitor_on(void){
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    GPIO_SetBits(GPIOA,GPIO_Pin_2);
    
}
void capacitor_off(void){
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void DIODE_off(void){
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
}
void DIODE_on(void){
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
}
