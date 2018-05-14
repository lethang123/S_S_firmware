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
#define RELAY_1        GPIO_PIN_5
#define RELAY_2        GPIO_PIN_4
#define RELAY_3        GPIO_PIN_3


// Led pin
#define LED_1          GPIO_PIN_4
#define LED_2          GPIO_PIN_6
#define LED_3          GPIO_PIN_5

#define LED_ON         0x01
#define LED_OFF        0x00

/**
 *  @brief      RELAY toogle state by byte control
 *  
 *  @param[in]   byte_state_control      byte for control state relay
 */
void RELAY_action(uint16_t byte_state_control);

/**
 *  @brief      ONE RELAY toogle state by byte control
 *  
 *  @param[in]   relay      NO. relay control
 *  @param[in]   state      state of relay control
 */
void RELAY_action_one(uint8_t relay, uint8_t state);



#endif /* _RELAY_H */
