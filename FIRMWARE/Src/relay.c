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
	bit_one = 0, // bit one
	bit_two = 4,
	bit_three = 8,
	bit_four = 12
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
static void relay_toggle_state_pin(uint16_t RELAY_Pin)
{
	/* check pin relay */
	if( RELAY_Pin == RELAY_1 ||
		  RELAY_Pin == RELAY_2 ||
	    RELAY_Pin == RELAY_3 ||
	    RELAY_Pin == RELAY_4  )
	{
		/* toogle state relay */
		HAL_GPIO_TogglePin(GPIOB,RELAY_Pin);
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
		}
		
		/* if control relay 2 */
		if(check_bit_same(byte_state_relay_last , byte_state_control , bit_two))
		{
			relay_toggle_state_pin(RELAY_2);
		}
		
		/* if control relay 3 */
		if(check_bit_same(byte_state_relay_last , byte_state_control , bit_three))
		{
			relay_toggle_state_pin(RELAY_3);
		}
		
		/* if control relay 4 */
		if(check_bit_same(byte_state_relay_last , byte_state_control , bit_four))
		{
			relay_toggle_state_pin(RELAY_4);
		}
  }
}
