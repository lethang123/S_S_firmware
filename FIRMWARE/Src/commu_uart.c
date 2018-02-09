#include "usart.h"
#include "commu_uart.h"


/* */
#define CBUF_SIZE_DATA     50

extern bool flag_toggle_state;

/* buffer of receive uart 1*/
volatile uint8_t commu_buf_rx;

/* static vair*/
circular_buf_t cbuf1;
static uint8_t volatile cbuf_array_uart1[CBUF_SIZE_DATA];

static uint8_t point_start;
static uint8_t check_head_byte_one;
static uint8_t check_head_byte_two;


void COMMU_init(void)
{
	circular_buf_init(&cbuf1,cbuf_array_uart1,CBUF_SIZE_DATA);
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&commu_buf_rx,1);
}

void COMMU_check_data_receive()
{ 
	circular_buf_get(&cbuf1,&check_head_byte_one);
	circular_buf_get(&cbuf1,&check_head_byte_two);
	if(check_head_byte_one
}
	