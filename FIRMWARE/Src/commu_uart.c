#include "usart.h"
#include "commu_uart.h"
#include "check_state.h"
#include "relay.h"

/* */
#define CBUF_SIZE_DATA     50
#define HEAD_BYTE          0x55
#define ACTION_CHECK       0x00
#define ACTION_TOGGLE      0x01

extern bool flag_toggle_state;

/* buffer of receive uart 1*/
volatile uint8_t commu_buf_rx;

/* static vair*/
circular_buf_t cbuf1;
static uint8_t volatile cbuf_array_uart1[CBUF_SIZE_DATA];


static uint8_t check_head_byte_one;
static uint8_t check_head_byte_two;
static uint8_t dlength;
static uint8_t action_byte;
static uint8_t data_state_relay_uint8;
static uint16_t data_state_relay_uint16;
	
static bool check_head_byte(void)
{
	if(circular_buf_check(&cbuf1) == HEAD_BYTE)
	{
		/* get byte head to check */
		circular_buf_get(&cbuf1,&check_head_byte_one);
		circular_buf_get(&cbuf1,&check_head_byte_two);
		
		/* if is head byte */
		if(check_head_byte_one == HEAD_BYTE && 
			 check_head_byte_two == HEAD_BYTE)
		{
			return BYTE_HEAD_TRUE;
		}
	}
	
	return  BYTE_HEAD_FALSE;
}

static void get_data_state_relay(void)
{
  circular_buf_get(&cbuf1,&data_state_relay_uint8);
	data_state_relay_uint16 = data_state_relay_uint8 << 8;
	circular_buf_get(&cbuf1,&data_state_relay_uint8);
	data_state_relay_uint16 |= data_state_relay_uint8;
}

void COMMU_init(void)
{
	circular_buf_init(&cbuf1,cbuf_array_uart1,CBUF_SIZE_DATA);
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&commu_buf_rx,1);
}

void COMMU_get_data(void)
{ 
	/* check head byte */
	if(check_head_byte() == BYTE_HEAD_TRUE)
	{
		
		/* get byte data length */
		circular_buf_get(&cbuf1,&dlength);
		/* get byte action */
		circular_buf_get(&cbuf1,&action_byte);
		
		/* if action is check */
		if(action_byte == ACTION_CHECK)
		{
			transmit_state_relay();
		}
		
		/* if action is toggle relay */
		if(action_byte == ACTION_TOGGLE)
		{
      get_data_state_relay();
			flag_toggle_state = true;
		}
		
	}
}
