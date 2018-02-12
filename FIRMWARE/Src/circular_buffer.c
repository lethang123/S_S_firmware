#include "circular_buffer.h"


void circular_buf_init(circular_buf_t *cbuf, volatile uint8_t *array, uint16_t size)
{
	cbuf->buff = array;
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->size = size;
	cbuf->data_los = false;
}

void circular_buf_reset(circular_buf_t *cbuf)
{
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->data_los = false;
}

bool circular_buf_full(circular_buf_t *cbuf)
{
	return (( cbuf->head + 1 ) % cbuf->size ) == cbuf->tail;
}

bool circular_buf_empty(circular_buf_t *cbuf)
{
	return (cbuf->head == cbuf->tail);
}

void circular_buf_put(circular_buf_t *cbuf, uint8_t data)
{
	if(!circular_buf_full(cbuf))
	{
		cbuf->buff[cbuf->head] = data;
		cbuf->head = (cbuf->head + 1 ) % cbuf->size;
	}
	
	if(cbuf->head == cbuf->tail)
  {
     cbuf->tail = (cbuf->tail + 1) % cbuf->size;
		 cbuf->data_los = true;
  }
}
void circular_buf_get(circular_buf_t *cbuf, uint8_t *data)
{
	if(!circular_buf_empty(cbuf))
  {
    *data = cbuf->buff[cbuf->tail];
     cbuf->tail = (cbuf->tail + 1) % cbuf->size;
  }
}

uint8_t circular_buf_check(circular_buf_t *cbuf)
{
	return cbuf->buff[cbuf->tail];
}
