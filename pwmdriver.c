
/*******************************************************************************
TITLE:: initial_timer()
INPUT:: New frequency 
OUTPUT:: None
REFERENCES:: None
AUTHOR:: Jessica.H
DATE:: 05/05/16
REVISION:: -
REV HISTORY:: -
NOTE:: -
*******************************************************************************/
 void initial_timer()
 {
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

   /* TIM Configuration */
   TIM_Config();
  

  /* Time base configuration */  
  TIM_TimeBaseStructure.TIM_Period = 1000;//20;//1000;
  TIM_TimeBaseStructure.TIM_Prescaler = 59;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
   
  /* Output Compare Timing Mode configuration: Channel3 */  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  
  /* TIM Interrupts enable */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

/*******************************************************************************
TITLE:: pwm_set_frequency()
INPUT:: New frequency 
OUTPUT:: None
DESCRIPTION:: Sets the frequency of PWM on the fly. 
REFERENCES:: None
LIMITATIONS:: This function can be called after PWM outputs have been initialized.
REVISION:: -
REV HISTORY:: -
NOTE::-
*******************************************************************************/
void pwm_set_frequency(u8 pwm_channel, u16 pwm_frequency)
{
u16 temp_u16;

  switch(pwm_channel)
  {
   //TIM8
    case 0:
    case 1:
    case 2:
      pwm_period[0] = 1000;
      if(pwm_frequency)
        temp_u16 = (u16)(120000L / (u32)pwm_frequency);// Prescaler value for TIM8
      else
        temp_u16 = 60000;// Prescaler value for TIM8

      // Set the Autoreload value 
      TIM8->ARR = pwm_period[0];
      // Set the Prescaler value
      if(temp_u16)
        TIM8->PSC = temp_u16 - 1;
      else
        TIM8->PSC = 0;
    break;	    
		
   //TIM3
    case 3:
    case 4:
    case 5:
    case 6:
      pwm_period[1] = 1000;
      if(pwm_frequency)
        temp_u16 = (u16)(60000L / (u32)pwm_frequency);// Prescaler value for TIM3
      else
        temp_u16 = 30000;// Prescaler value for TIM3

      // Set the Autoreload value 
      TIM3->ARR = pwm_period[1];
      // Set the Prescaler value
      if(temp_u16)
        TIM3->PSC = temp_u16 - 1;
      else
        TIM3->PSC = 0;
    break;			
		
    //TIM9
    case 7:
    case 8:
      pwm_period[2] = 1000;
      if(pwm_frequency)
        temp_u16 = (u16)(120000L / (u32)pwm_frequency);// Prescaler value for TIM9
      else
        temp_u16 = 60000;// Prescaler value for TIM9

      // Set the Autoreload value 
      TIM9->ARR = pwm_period[2];
      // Set the Prescaler value
      if(temp_u16)
        TIM9->PSC = temp_u16 - 1;
      else
        TIM9->PSC = 0;
    break;	 		
		
    //TIM5
    case 9:
    case 10:
      pwm_period[3] = 1000;
      if(pwm_frequency)
        temp_u16 = (u16)(60000L / (u32)pwm_frequency);// Prescaler value for TIM5
      else
        temp_u16 = 30000;// Prescaler value for TIM5

      // Set the Autoreload value 
      TIM5->ARR = pwm_period[3];
      // Set the Prescaler value
      if(temp_u16)
        TIM5->PSC = temp_u16 - 1;
      else
        TIM5->PSC = 0;
    break;			
						
//TIM4
    case 11:  
      pwm_period[4] = 1000;
      if(pwm_frequency)
        temp_u16 = (u16)(60000L / (u32)pwm_frequency);// Prescaler value for TIM4
      else
        temp_u16 = 30000;// Prescaler value for TIM4

      // Set the Autoreload value 
      TIM4->ARR = pwm_period[4];
      // Set the Prescaler value
      if(temp_u16)
        TIM4->PSC = temp_u16 - 1;
      else
        TIM4->PSC = 0;
    break;
		
//TIM1
    case 12:
    case 13:
    case 14:
    case 15:			
      pwm_period[5] = 1000;
      if(pwm_frequency)
        temp_u16 = (u16)(120000L / (u32)pwm_frequency);// Prescaler value for TIM1
      else
        temp_u16 = 60000;// Prescaler value for TIM8

      // Set the Autoreload value 
      TIM1->ARR = pwm_period[5];
      // Set the Prescaler value
      if(temp_u16)
        TIM1->PSC = temp_u16 - 1;
      else
        TIM1->PSC = 0;
    break;		
    
    //TIM2
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
       pwm_period[6] = 1000;
      if(pwm_frequency)
        temp_u16 = (u16)(60000L / (u32)pwm_frequency);// Prescaler value for TIM1
      else
        temp_u16 = 60000;// Prescaler value for TIM8

      // Set the Autoreload value 
      TIM2->ARR = pwm_period[6];
      // Set the Prescaler value
      if(temp_u16)
        TIM2->PSC = temp_u16 - 1;
      else
        TIM2->PSC = 0;
      
      break;
  }   
}
