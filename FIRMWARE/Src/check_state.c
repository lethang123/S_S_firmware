/*
 */
#include "check_state.h"

bool flag_toggle_state = false;

uint16_t byte_state_button;
static uint16_t s_byte_check_state_button = 0x0000U;

void check_state_button(uint16_t GPIO_Pin)
{
	/* if button 1 */
	if(GPIO_Pin == GPIO_PIN_10)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x1000);
	}
	
	/* if button 1 */
	if(GPIO_Pin == GPIO_PIN_11)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x0100);
	}
	
	/* if button 1 */
	if(GPIO_Pin == GPIO_PIN_12)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x0010);
	}
	
	/* if button 1 */
	if(GPIO_Pin == GPIO_PIN_13)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x0001);
	}
	
	/* update state buttton */
	byte_state_button = s_byte_check_state_button;
	
	/* flag state toggle*/
	flag_toggle_state = true;
}
