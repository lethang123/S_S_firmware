/*
 */
#ifndef _CHECK_STATE_H
#define _CHECK_STATE_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

/* program */
void check_state_button_it(uint16_t GPIO_Pin);
void transmit_state_relay(void);
#endif /* _CHECK_STATE_H */
