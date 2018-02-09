#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct{
	volatile uint8_t *buff;
	uint16_t head;
	uint16_t tail;
	uint16_t size;
	bool data_los;
}	circular_buf_t;

void circular_buf_init(circular_buf_t *cbuf, volatile uint8_t *array, uint16_t size);
void circular_buf_reset(circular_buf_t *cbuf);

bool circular_buf_full(circular_buf_t *cbuf);
bool circular_buf_empty(circular_buf_t *cbuf);

void circular_buf_put(circular_buf_t *cbuf, uint8_t data);
void circular_buf_get(circular_buf_t *cbuf, uint8_t *data);

uint8_t circular_buf_check(circular_buf_t *cbuf);

#endif /* _CIRCULAR_BUFFER_H */
