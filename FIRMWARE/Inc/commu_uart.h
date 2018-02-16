/** @file
  * 
  * @brief RELAY TOGGLE STATE
  *
  */
#ifndef _COMMU_UART_H
#define _COMMU_UART_H

/*********************************************************************************
 * INCLUDE
 */
 
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>
/* USER INCLUDE */
#include "circular_buffer.h"

/**
 *  @brief      COMMU initialize
 */
void COMMU_init(void);

/**
 *  @brief      COMMU transmition state relay 
 */
void COMMU_trans_state_relay(void);

/**
 *  @brief      COMMU 
 */
void COMMU_get_data_control(void);


#endif /* _COMMU_UART_H */
