#ifndef _RELAY_H
#define _RELAY_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

void relay_toggle_state(uint16_t RELAY_Pin);

#endif /* _RELAY_H */
