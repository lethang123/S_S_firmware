#include "relay.h"

void relay_toggle_state_pin(uint16_t RELAY_Pin)
{
	if( RELAY_Pin == GPIO_PIN_3 ||
		  RELAY_Pin == GPIO_PIN_4 ||
	    RELAY_Pin == GPIO_PIN_5 ||
	    RELAY_Pin == GPIO_PIN_6  )
	{
		HAL_GPIO_TogglePin(GPIOB,RELAY_Pin);
	}
}

void relay_action(uint16_t byte_action)
{
	
}
