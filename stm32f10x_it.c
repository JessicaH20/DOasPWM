//stm32f10x_it.c

u16 pwm_on_high_length;
u8 pwm_onoff[12];
u8 pwm_state;
  
void TIM2_IRQHandler(void)
{
  u8 i;
 
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    
   switch(pwm_state)
   {
     case ALL_LOW_STATE:

       if(pwm_new_duty_cycle_value_flag)
        {
          pwm_new_duty_cycle_value_flag = 0;
           for(i=0;i<12;i++)
          {
            pwm_buffered_high_value[i] = pwm_high_value[i];
            pwm_buffered_low_value[i] = 1000 - pwm_high_value[i];//pwm_low_value[i];
            pwm_buffered_high_value_sort[i] = (u16)pwm_high_value_sort[i];
          }
        }
				
        for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] < 1000)
	   pwm_onoff[i] = 0;
	  else
	   pwm_onoff[i] = 1;
        }
        
        pwm_on_high_length = (u16)(1000 - (u16)pwm_buffered_high_value_sort[0]);
        
          if(pwm_buffered_high_value_sort[11]==(int)1000)
           pwm_state = ALL_HIGH_STATE;
        
          else if(pwm_buffered_high_value_sort[0])
          { 
            if(pwm_on_high_length)
            {
             TIM2->ARR  = pwm_on_high_length;
             pwm_state = HIGH_1ST_STATE;
            }
            else
            {
              if(pwm_buffered_high_value_sort[1])
              {
               TIM2->ARR  = (u16)(pwm_buffered_high_value_sort[0] - pwm_buffered_high_value_sort[1]);
               pwm_state = HIGH_2ND_STATE; 
              }
              else
              {
               TIM2->ARR  = 1000;
               pwm_state = ALL_LOW_STATE; 
              }
            }
          }
	break;
      
      case HIGH_1ST_STATE:
	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
         if(pwm_buffered_high_value_sort[1])
         {
            pwm_on_high_length = pwm_buffered_high_value_sort[0] - pwm_buffered_high_value_sort[1];
            TIM2->ARR = pwm_on_high_length;
            pwm_state = HIGH_2ND_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
    	break;
      
    case HIGH_2ND_STATE:
       	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
       if(pwm_buffered_high_value_sort[2])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[1] - pwm_buffered_high_value_sort[2];
            pwm_state = HIGH_3RD_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
       case HIGH_3RD_STATE:
         for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
       if(pwm_buffered_high_value_sort[3])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[2] - pwm_buffered_high_value_sort[3];
            pwm_state = HIGH_4TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_4TH_STATE:
       	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
         
       if(pwm_buffered_high_value_sort[4])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[3] - pwm_buffered_high_value_sort[4];
            pwm_state = HIGH_5TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_5TH_STATE:
        for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
      if(pwm_buffered_high_value_sort[5])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[4] - pwm_buffered_high_value_sort[5];
            pwm_state = HIGH_6TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_6TH_STATE:
       	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
       if(pwm_buffered_high_value_sort[6])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[5] - pwm_buffered_high_value_sort[6];
            pwm_state = HIGH_7TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_7TH_STATE:
       	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
        
       if(pwm_buffered_high_value_sort[7])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[6] - pwm_buffered_high_value_sort[7];
            pwm_state = HIGH_8TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_8TH_STATE:
       	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
      if(pwm_buffered_high_value_sort[8])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[7] - pwm_buffered_high_value_sort[8];
            pwm_state = HIGH_9TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_9TH_STATE:
        for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
      if(pwm_buffered_high_value_sort[9])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[8] - pwm_buffered_high_value_sort[9];
            pwm_state = HIGH_10TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_10TH_STATE:
       	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
      if(pwm_buffered_high_value_sort[10])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[9] - pwm_buffered_high_value_sort[10];
            pwm_state = HIGH_11TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_11TH_STATE:
       	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
       if(pwm_buffered_high_value_sort[11])
         {
            TIM2->ARR = pwm_buffered_high_value_sort[10] - pwm_buffered_high_value_sort[11];
            pwm_state = HIGH_12TH_STATE;
         }
        else
         {
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
         }
	break;
      
      case HIGH_12TH_STATE:
       	 for(i=0;i<12;i++)
        {
          if(pwm_buffered_high_value[i] >= (u16)pwm_buffered_high_value_sort[pwm_state-1])
          {
             pwm_onoff[i] = 1;
          }
          else
             pwm_onoff[i] = 0;
        }
        
           TIM2->ARR = pwm_buffered_high_value_sort[pwm_state-1];
           pwm_state = ALL_LOW_STATE;
	break;
      

      case ALL_HIGH_STATE:
       
        for(i=0;i<12;i++)
        {
         if(pwm_new_duty_cycle_value_flag)
          {
            pwm_buffered_high_value[i] = pwm_high_value[i];
            pwm_buffered_low_value[i] = pwm_low_value[i];
            pwm_state = ALL_LOW_STATE;
          }
        }

	for(i=0;i<12;i++)
        {
          if(pwm_buffered_low_value[i])
	  pwm_onoff[i] = 0;
	 else
	  pwm_onoff[i] = 1;
        }
	break; 
	}
	
    for(i=0;i<12;i++)
    {
      switch(i)
      {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:    
          if(output_on_off_proportional_pattern & (0x0001 << (14 + i)))
          {
            if(pwm_onoff[i])
              set_digital_output(14 + i);
            else
              clear_digital_output(14 + i);  
          }
       break;
       
      case 7://CMD23
        if(output_on_off_proportional_pattern & (0x0001 << (15 + i)))
        {
         if(pwm_onoff[i])
            set_digital_output(15 + i);
         else
           clear_digital_output(15 + i); 
        }
      break;
      
     case 8://CMD25
        if(output_on_off_proportional_pattern & (0x0001 << (16 + i)))
        {
         if(pwm_onoff[i])
            set_digital_output(16 + i);
         else
           clear_digital_output(16 + i); 
        }
     break;
     
     case 9://CMD28
     case 10://CMD29
     case 11://CMD30
       if(output_on_off_proportional_pattern & (0x0001 << (18 + i)))
       {
         if(pwm_onoff[i])
            set_digital_output(18 + i);
         else
           clear_digital_output(18 + i); 
       }
     break;

      }
    }
  }
} 
