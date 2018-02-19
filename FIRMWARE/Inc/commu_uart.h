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

/*********************************************************************************
 * DEFINE
 */
 
#define HEAD_BYTE                0x44
#define DLEN_DATA_TRANS          0x05
#define DIR_CHECK                0x00
#define DIR_ACTION               0x01
#define CRC_BUF                  0x00
#define TAIL_BYTE                0xFF


/**
 *  @brief      COMMU initialize
 */
void COMMU_init(void);

/**
 *  @brief      COMMU transmition state relay 
 */
void COMMU_trans_state_relay(uint8_t dir_data);

/**
 *  @brief      COMMU get data control 
 */
void COMMU_get_data_control(void);

#endif /* _COMMU_UART_H */
