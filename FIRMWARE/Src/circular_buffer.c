/** @file
  * 
  * @brief CIRCULAR BUFFER
  *
  */
	
/*********************************************************************************
 * INCLUDE
 */
 
#include "circular_buffer.h"

/**
 * @brief        CIRCULAR BUFFER initialize circular buffer
 * 
 * @param[in]    *cbuf     address of circular buffer
 * @param[in]    *array    address array save data    
 * @param[in]    size      size of buffer
 */
void circular_buf_init(circular_buf_t *cbuf, volatile uint8_t *array, uint16_t size)
{
	cbuf->buff = array;
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->size = size;
	cbuf->data_los = false;
}

/**
 * @brief        CIRCULAR BUFFER reset circular buffer
 * 
 * @param[in]    *cbuf     address of circular buffer
 */
void circular_buf_reset(circular_buf_t *cbuf)
{
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->data_los = false;
}

/**
 * @brief        check circular buffer full
 * 
 * @param[in]   *cbuf      address of circular buffer
 * 
 * @return 1    if circular buffer full
 */
bool circular_buf_full(circular_buf_t *cbuf)
{
	return (( cbuf->head + 1 ) % cbuf->size ) == cbuf->tail;
}

/**
 * @brief        check circular buffer empty
 * 
 * @param[in]   *cbuf      address of circular buffer
 * 
 * @return 1    if circular buffer empty
 */
bool circular_buf_empty(circular_buf_t *cbuf)
{
	return (cbuf->head == cbuf->tail);
}

/**
 * @brief       CIRCULAR BUFFER put data into circular buffer
 * 
 * @param[in]   *cbuf      address of circular buffer
 * @param[in]   data       data to put
 */
void circular_buf_put(circular_buf_t *cbuf, uint8_t data)
{
	// if not full buffer
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

/**
 * @brief       CIRCULAR BUFFER get data of circular buffer
 * 
 * @param[in]   *cbuf      address of circular buffer
 * @param[in]   *data      address data to get
 */
void circular_buf_get(circular_buf_t *cbuf, uint8_t *data)
{
	/* if not empty and not loss data */
	if(!circular_buf_empty(cbuf) && (cbuf->data_los  == false ))
  {
    *data = cbuf->buff[cbuf->tail];
     cbuf->tail = (cbuf->tail + 1) % cbuf->size;
  }
}

uint8_t circular_buf_check(circular_buf_t *cbuf)
{
	return cbuf->buff[cbuf->tail];
}
