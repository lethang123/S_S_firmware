#ifndef _COMMU_UART_H
#define _COMMU_UART_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

/* user include */
#include "circular_buffer.h"

void COMMU_init(void);
void COMMU_check_data_receive();

#endif /* _COMMU_UART_H */
