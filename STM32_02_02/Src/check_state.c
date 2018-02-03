 /**
  ******************************************************************************
  * File Name          : check_state.c
  * Description        : 
  ******************************************************************************
  */

#include "check_state.h"

static uint8_t s_byte_state_last = 0x00U;

void check_state_button(uint16_t byte_state)
{
	if(byte_state !=  s_byte_state_last)
	{
		s_byte_state_last = byte_state;
		
	}
}

