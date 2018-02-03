 /**
  ******************************************************************************
  * File Name          : filenum.c
  * Description        : 
  ******************************************************************************
  */
  
#include "circular_buffer.h"

#include "filenum.h"
FILENUM(0x0001U)

/*
 * @brief        initialize circular buffer
 * 
 * @param[in]    *cbuf     address of circular buffer
 * @param[in]    *p_buf    
 * @param[in]    size_     size of buffer
 */
void circular_buf_init(circular_buf_t *cbuf, uint8_t* p_buf, uint16_t size_)
{
	cbuf->buff = p_buf;
	cbuf->head   = 0;
	cbuf->tail   = 0;
	cbuf->size   = size_;  
}

void circular_buf_reset(circular_buf_t *cbuf)
{
	cbuf->head = 0;
	cbuf->tail = 0;
}

/*
 * @brief check circular buffer empty
 * 
 * @param[in]  cbuf
 * 
 * @return 1   if circular buffer empty
 */
bool circular_buf_empty(circular_buf_t *cbuf)
{
	return (cbuf->head == cbuf->tail);
}

/*
 * @brief check circular buffer full
 * 
 * @param[in]   cbuf
 * 
 * @return 1    if circular buffer full
 */
bool circular_buf_full(circular_buf_t *cbuf)
{
	return((cbuf->head + 1 ) % cbuf->size) == cbuf->tail;
}

/*
 * @brief put in value circular buffer
 */
void circular_buf_put(circular_buf_t *cbuf, uint8_t data)
{
    if(!circular_buf_full(cbuf))
	{
	    cbuf->buff[cbuf->head] = data;
	    cbuf->head = (cbuf->head + 1) % cbuf->size;
	}
	if(cbuf->head == cbuf->tail)
	{
		cbuf->tail = (cbuf->tail + 1) % cbuf->size;
	}
}

/*
 * @brief get out value circular buffer
 */
void circular_buf_get(circular_buf_t *cbuf, uint8_t *data)
{
	if(!circular_buf_empty(cbuf))
	{
		*data = cbuf->buff[cbuf->tail];
		cbuf->tail = (cbuf->tail + 1) % cbuf->size; 
	}
}
