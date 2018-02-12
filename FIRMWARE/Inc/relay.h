#ifndef _RELAY_H
#define _RELAY_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

void relay_toggle_state_pin(uint16_t RELAY_Pin);
void relay_action(uint16_t byte_action);

#endif /* _RELAY_H */
