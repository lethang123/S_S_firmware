#ifndef _COMMU_UART_H
#define _COMMU_UART_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

/* user include */
#include "circular_buffer.h"

typedef enum
{
	BYTE_HEAD_TRUE = 0,
	BYTE_HEAD_FALSE
}check_head_return_t;

void COMMU_init(void);
void COMMI_trans_state_relay(void);
void COMMU_get_data(void);


#endif /* _COMMU_UART_H */
