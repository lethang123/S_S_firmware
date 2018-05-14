/** @file
  * 
  * @brief RELAY TOGGLE STATE
  *
  */
	
/*********************************************************************************
 * INCLUDE
 */
 
#include "relay.h"

/*********************************************************************************
 * TYPEDEFS
 */
 
/* Result check bit */
typedef enum
{
	BIT_SAME = 0, // if two bit same
	BIT_NOT_SAME
}check_bit_t;

/* Define bit point */
typedef enum
{
	bit_one = 12, // bit one
	bit_two = 8,
	bit_three = 4,
	bit_four = 0
}bit_point;

/*********************************************************************************
 * GLOBAL VARIABLES
 */

/* byte state of relay last */
uint16_t byte_state_relay_last = 0x0000;

/**
 *  @brief      check byte same of 
 *  
 *  @param[in]   RELAY_Pin      pin relay toogle state
 */
static check_bit_t check_bit_same(uint16_t data_one, uint16_t data_two, uint8_t piont)
{
	if((data_one & (0x0001 << piont )) !=
		 (data_two & (0x0001 << piont )) )
	{
		return BIT_NOT_SAME;
	}
	return BIT_SAME;
}

/**
 *  @brief      relay toogle state pin
 *  
 *  @param[in]   RELAY_Pin      pin relay toogle state
 */
 void relay_toggle_state_pin(uint16_t RELAY_Pin)
{
	/* check pin relay */
	if( RELAY_Pin == RELAY_1 ||
		  RELAY_Pin == RELAY_2 ||
	    RELAY_Pin == RELAY_3  )
	{
		/* toogle state relay */
		HAL_GPIO_TogglePin(GPIOB,RELAY_Pin);
	}
}

/**
 *  @brief      led toogle state pin
 *  
 *  @param[in]   LED_Pin      pin led toogle state
 */
 void led_toggle_state_pin(uint16_t LED_Pin)
{
	/* check pin led */
	if( LED_Pin == LED_1 ||
		  LED_Pin == LED_2 ||
	    LED_Pin == LED_3  )
	{
		/* toogle state led */
		HAL_GPIO_TogglePin(GPIOA,LED_Pin);
	}
}
/**
 *  @brief       RELAY toogle state by byte control
 *  
 *  @param[in]   byte_state_control      byte for control state relay
 */
void RELAY_action(uint16_t byte_state_control)
{
	/* if byte control state relay different state relay */
	if(byte_state_relay_last != byte_state_control)
	{
		/* if control relay 1 */
		if(check_bit_same(byte_state_relay_last , byte_state_control , bit_one))
		{
			relay_toggle_state_pin(RELAY_1);
			led_toggle_state_pin(LED_1);
		}
		
		/* if control relay 2 */
		if(check_bit_same(byte_state_relay_last , byte_state_control , bit_two))
		{
			relay_toggle_state_pin(RELAY_2);
			led_toggle_state_pin(LED_2);
		}
		
		/* if control relay 3 */
		if(check_bit_same(byte_state_relay_last , byte_state_control , bit_three))
		{
			relay_toggle_state_pin(RELAY_3);
			led_toggle_state_pin(LED_3);
		}
		
		/* update state relay */
		byte_state_relay_last = byte_state_control;
		
  }
}

void RELAY_action_one(uint8_t relay, uint8_t state)
{
	/* if state is off*/
	if(state == 0x00)
	{
		if(relay == 0x01)
		{
			HAL_GPIO_WritePin(GPIOB,RELAY_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,LED_1,GPIO_PIN_SET);
			byte_state_relay_last = byte_state_relay_last & 0x0111;
		}
				if(relay == 0x02) 
		{
			HAL_GPIO_WritePin(GPIOB,RELAY_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,LED_2,GPIO_PIN_SET);
			byte_state_relay_last = byte_state_relay_last & 0x1011;
		}
		
				if(relay == 0x03)
		{
			HAL_GPIO_WritePin(GPIOB,RELAY_3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,LED_3,GPIO_PIN_SET);
			byte_state_relay_last = byte_state_relay_last & 0x1101;
		}
	}
	
	/* if state is on*/
	if(state == 0x01)
	{
		if(relay == 0x01)
		{
			HAL_GPIO_WritePin(GPIOB,RELAY_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,LED_1,GPIO_PIN_RESET);
			byte_state_relay_last = byte_state_relay_last | 0x1000;
		}
				if(relay == 0x02)
		{
			HAL_GPIO_WritePin(GPIOB,RELAY_2,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,LED_2,GPIO_PIN_RESET);
			byte_state_relay_last = byte_state_relay_last | 0x0100;
		}
		
				if(relay == 0x03)
		{
			HAL_GPIO_WritePin(GPIOB,RELAY_3,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,LED_3,GPIO_PIN_RESET);
			byte_state_relay_last = byte_state_relay_last | 0x0010;
		}
	}
}
