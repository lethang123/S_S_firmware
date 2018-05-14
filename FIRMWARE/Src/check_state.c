/** @file
  * 
  * @brief CHECK STATE BUTTON INTERRUPT
  *
  */
	
/*********************************************************************************
 * INCLUDE
 */
#include "check_state.h"
#include "usart.h"
#include "relay.h"

/*********************************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************************
 * FLAG
 */
 
/* toggle state button flag */
bool flag_button_toggle_state = false;

/*********************************************************************************
 * LOCAL VARIABLES
 */
 
/* byte of state button */
uint16_t s_byte_check_state_button = 0x0000U;

/**
 *  @brief      CHECK state of button in interrupt and toggle relay
 *  
 *  @param[in]   GPIO_Pin       GPIO pins button 
 */
void CHECK_button_it(uint16_t GPIO_Pin)
{
	/* if button 1 */
	if(GPIO_Pin == BUTTON_1)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x1000);
		printf("a");
	}
	
	/* if button 2 */
	if(GPIO_Pin == BUTTON_2)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x0100);
		printf("b");
	}
	
	/* if button 3 */
	if(GPIO_Pin == BUTTON_3)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x0010);
		printf("c");
	}
	
	/* toggle relay pin */
	RELAY_action(s_byte_check_state_button);
	
	/* flag state toggle*/
	flag_button_toggle_state = true;
}

/**
 *  @brief      update state button
 *  
 *  @param[in]   GPIO_Pin       GPIO pins button 
 */
void CHECK_button_update(uint16_t data_control)
{
	/* update byte state button */
	s_byte_check_state_button = data_control;
}
