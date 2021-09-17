#include "stm32f10x.h"
#include "switch.h"

uint8_t chargeon = 0;

void tim1_init(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
		TIM_BDTRInitTypeDef  TIM_BDTRInitStructure;

				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);  // ����GPIOʱ��
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                                                 // �������ù��� 
        // GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  ��Ϊ���ﲻ����ӳ�䣬���Բ���д������Ҫ�ı���д
        
        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    // �����������
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
        GPIO_Init(GPIOA, &GPIO_InitStructure);
       
        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    // �����������
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);        
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  /* ����TIM1��ʱ��*/
  TIM_TimeBaseStructure.TIM_Prescaler = 71;
  /*  ��ϵͳ����Ƶ�ʷ�Ƶ������ʱ���Ĺ���Ƶ�� ������72MHz��Ҫ�õ�1MHz��ʱ������Ƶ�ʣ�*/
             
                                 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    
   /* TIM_CounterMode_Up                 TIM ���ϼ���ģʽ
			TIM_CounterMode_Down               TIM ���¼���ģʽ
			TIM_CounterMode_CenterAligned1     TIM �������ģʽ 1 ����ģʽ
			TIM_CounterMode_CenterAligned2     TIM �������ģʽ 2 ����ģʽ  */
          
  TIM_TimeBaseStructure.TIM_Period = (1000-1);  
   /* ��������� TIM_Prescaler  ���� PWM��Ƶ�ʣ�����TIM_Prescaler=71 ʱ��TIM��1MHz��Ƶ�ʼ��������ﵽ
      TIM_Period�趨�ĸ���ʱ���¼���TIM_Period��ֵ���Ĵ�����������һ��ѭ�������TIM_Period��ֵһֱ���䣬
      PWM����һ���̶�������������˴���PWMƵ�����õ��� 1MHz/1000=1kHz��    */           
         
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;		
    /* ���ö�ʱ��ʱ��CK_INTƵ���������������Լ������˲�������ʱ��Ƶ�ʷ�Ƶ�����˴����á�   */
    						  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                         
   /* ����ĳ��ռ�ձȵ�PWM�ظ�ִ�еĴ��������֮ǰ���õ�ռ�ձ�Ϊ50�������ֵ����Ϊ1�Ļ���50%PWM�ᱻִ��
      ���Σ�Ҳ����������һ����ִ��һ������   */

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);



	

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
   /*�Ƚ����ģʽѡ�񣬹�8�֡�value��
     TIM_OCMode_Timing                  TIM ����Ƚ�ʱ��ģʽ
     TIM_OCMode_Active                  TIM ����Ƚ�����ģʽ
     TIM_OCMode_Inactive                TIM ����ȽϷ�����ģʽ
     TIM_OCMode_Toggle                  TIM ����Ƚϴ���ģʽ
     TIM_OCMode_PWM1                    TIM �����ȵ���ģʽ 1 
     TIM_OCMode_PWM2                    TIM �����ȵ���ģʽ 2  
     ��PWM�����£�ѡTIM_OCMode_PWM1 ��TIM_OCMode_PWM2 ������ѡ���� */

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;              
   /* �Ƚ����ʹ�ܣ������ź��Ƿ�ͨ���ⲿ�������*/
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;            
   /* ����ʹ�ܣ����������ź��Ƿ�ͨ���ⲿ�������*/
  TIM_OCInitStructure.TIM_Pulse = 0; 
   /* ��ʼ��ռ�ձ�                   */          
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
   /* ������ԣ�������ʱ��ͨ����Ч��ƽ�ļ���*/
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
   /* ����������ԣ���ѡ�ߵ�ƽ��Ч���͵�ƽ��Ч*/
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
   /* ����״̬ʱͨ�������ƽ���ã���ѡ�ߵ�ƽ���͵�ƽ*/
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
   /* ����״̬ʱ����ͨ�������ƽ���ã���ѡ�ߵ�ƽ���͵�ƽ���趨ֵ�����TIM_OCIdleState�෴*/

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);


	

  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
   /* ����ģʽ�¹ر�״̬ѡ��*/
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
   /* ����ģʽ�¹ر�״̬ѡ��*/
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
   /* ��������
      00�������رգ��Ĵ�����д������
      01����������1������д��TIMx_BDTR�Ĵ�����DTG��BKE��BKP��AOEλ��     TIMx_CR2�Ĵ�����OISx/OISxNλ��
      10����������2������д����������1�еĸ�λ��Ҳ����д��CC����λ(һ�����ͨ��ͨ��CCxSλ��Ϊ�����CC����λ��TIMx_CCER�Ĵ�����CCxP/CCNxPλ)�Լ�OSSR/OSSIλ��
      11����������3������д����������2�еĸ�λ��Ҳ����д��CC����λ(һ�����ͨ��ͨ��CCxSλ��Ϊ�����CC����λ��TIMx_CCMRx�Ĵ�����OCxM/OCxPEλ)��
      ע����ϵͳ��λ��ֻ��дһ��LOCKλ��һ��д��TIMx_BDTR�Ĵ������������ݶ���ֱ����λ��*/
  TIM_BDTRInitStructure.TIM_DeadTime = 20;
   /* ����ʱ��*/
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
   /* ɲ��ʹ�ܿ��ƣ������Ҫɲ������Ҫ��������һ·GPIO*/
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
   /* ɲ���������*/
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
   /* �Զ����ʹ��*/

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	TIM_SetCompare1(TIM1,500);
}

void tim2_init(uint32_t psc,uint32_t arr){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	//���ø�����Ϊ�����������,���TIM2 CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

  //TIM_CtrlPWMOutputs(TIM2,ENABLE);	//MOE �����ʹ��	

	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	
	
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
		
		//PA1 �ߵ�ƽ��ع���·�򿪣��͵�ƽ�ض�
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    
    //PA2 �ߵ�ƽ�������ݹ���·�򿪣��͵�ƽ�ض�
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
