	void scheduler(void)
{
#ifdef LCD_DISPLAY_ENABLE
unsigned char delta_rows[8] = {0x04, 0x04, 0x0A, 0x0A, 0x11, 0x1F, 0x00, 0x00};// Thay are located in Data Flash
#endif
u8 i= 0;
u8 temp_can_msg_data[8];

	interrupt_flag = 0;
	interrupt_phase++;
        	
   if((interrupt_phase & MASK_4MS) == PHASE_4MS)
	{

		for(i=0; i<30; i++)
			joystick_input_value[i] = analog_input_to_joystick_input_map(i);			
		
		joystick_input_to_pwm_output_phase++;
		if(joystick_input_to_pwm_output_phase > 1)
			joystick_input_to_pwm_output_phase = 0;
    
    for(i=0; i<15; i++)
		  joystick_input_to_pwm_output_map(joystick_input_to_pwm_output_phase + 2 * i);
		
  }
  if((interrupt_phase & MASK_32MS) == PHASE_32MS)
	{
    
    	pwm_scan_phase++;
		if(pwm_scan_phase > 1)
			pwm_scan_phase = 0;    
    pwm_generator(pwm_scan_phase);
    pwm_generator(pwm_scan_phase + 2);
    pwm_generator(pwm_scan_phase + 4);
    pwm_generator(pwm_scan_phase + 6);		
    pwm_generator(pwm_scan_phase + 8);		
    pwm_generator(pwm_scan_phase + 10);			
    pwm_generator(pwm_scan_phase + 12);	
     
    pwm_generator_simulation(pwm_scan_phase + 14);
    pwm_generator_simulation(pwm_scan_phase + 16);
    pwm_generator_simulation(pwm_scan_phase + 18);
    pwm_generator_simulation(pwm_scan_phase + 28);
    
    if(!pwm_scan_phase)
    {
      pwm_generator_simulation(pwm_scan_phase + 20);
      pwm_generator_simulation(pwm_scan_phase + 22);
      pwm_generator_simulation(pwm_scan_phase + 24);
      pwm_generator(pwm_scan_phase + 26);
    }
    else
    {
      pwm_generator(pwm_scan_phase + 20);
      pwm_generator(pwm_scan_phase + 22);
      pwm_generator(pwm_scan_phase + 24);
      pwm_generator_simulation(pwm_scan_phase + 26);
    }
    }

}
