/** @file
  * 
  * @brief CHECK STATE BUTTON INTERRUPT
  *
  */
#ifndef _CHECK_STATE_H
#define _CHECK_STATE_H

/*********************************************************************************
 * INCLUDE
 */
 
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

/*********************************************************************************
 * MACROS
 */
 
/* Button pin define */
#define BUTTON_1       GPIO_PIN_10
#define BUTTON_2       GPIO_PIN_11
#define BUTTON_3       GPIO_PIN_12
#define BUTTON_4       GPIO_PIN_13

/**
 *  @brief      CHECK state of button in interrupt
 *  
 *  @param[in]   GPIO_Pin       GPIO pins button 
 */
void CHECK_button_it(uint16_t GPIO_Pin);

#endif /* _CHECK_STATE_H */
