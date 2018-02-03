 /**
  ******************************************************************************
  * File Name          : filenum.h
  * Description        : 
  ******************************************************************************
  */
  
#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint8_t* buff;
  uint16_t head;
  uint16_t tail;
  uint16_t size;
}circular_buf_t;

void circular_buf_init(circular_buf_t *cbuf, uint8_t* array, uint16_t size_);
void circular_buf_reset(circular_buf_t *cbuf);
bool circular_buf_empty(circular_buf_t *cbuf);
bool circular_buf_full(circular_buf_t *cbuf);
void circular_buf_put(circular_buf_t *cbuf, uint8_t data);
void circular_buf_get(circular_buf_t *cbuf, uint8_t *data);

#endif /* _CIRCULAR_BUFFER_H */
