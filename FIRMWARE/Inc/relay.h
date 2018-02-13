/** @file
  * 
  * @brief RELAY TOGGLE STATE
  *
  */
#ifndef _RELAY_H
#define _RELAY_H

/*********************************************************************************
 * INCLUDE
 */
 
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

/*********************************************************************************
 * MACROS
 */
 
// Max relay control
#define MAX_RELAY      4

// Relay pin 
#define RELAY_1        GPIO_PIN_3
#define RELAY_2        GPIO_PIN_4
#define RELAY_3        GPIO_PIN_5
#define RELAY_4        GPIO_PIN_6

/**
 *  @brief      RELAY toogle state by byte control
 *  
 *  @param[in]   byte_state_control      byte for control state relay
 */
void RELAY_action(uint16_t byte_state_control);

#endif /* _RELAY_H */
