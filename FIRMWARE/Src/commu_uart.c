#include "usart.h"
#include "commu_uart.h"
#include "relay.h"

/* */
#define CBUF_SIZE_DATA     50
#define MAX_DATA_FRAME     8

#define HEAD_BYTE          0x55
#define DLEN_DATA          0x05
#define ACTION_CHECK       0x00
#define ACTION_TOGGLE      0x01
#define CRC_BUF            0x00
#define TAIL_BYTE          0xFF

UART_HandleTypeDef* COMMU = &huart1;

extern bool flag_toggle_state;
extern uint16_t byte_state_relay_last;

/* buffer of receive uart 1*/
volatile uint8_t commu_buf_rx;

/* static vair*/
circular_buf_t cbuf1;
static uint8_t volatile cbuf_array_uart1[CBUF_SIZE_DATA];

static uint8_t check_head_byte_one;
static uint8_t check_head_byte_two;
static uint8_t dlength;
static uint8_t action_byte;
static uint8_t data_control_state_relay_uint8;
static uint16_t data_control_state_relay_uint16;
static uint8_t data_state_relay_transmit[MAX_DATA_FRAME];


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
  circular_buf_get(&cbuf1,&data_control_state_relay_uint8);
	data_control_state_relay_uint16 = data_control_state_relay_uint8 << 8;
	circular_buf_get(&cbuf1,&data_control_state_relay_uint8);
	data_control_state_relay_uint16 |= data_control_state_relay_uint8;
}

void COMMU_init(void)
{
	circular_buf_init(&cbuf1,cbuf_array_uart1,CBUF_SIZE_DATA);
	HAL_UART_Receive_IT(COMMU,(uint8_t *)&commu_buf_rx,1);
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
			
		}
		
		/* if action is toggle relay */
		if(action_byte == ACTION_TOGGLE)
		{
      get_data_state_relay();
			RELAY_action(data_control_state_relay_uint16);
		}
		
	}
}

void COMMI_trans_state_relay(void)
{
	data_state_relay_transmit[0] = HEAD_BYTE;
	data_state_relay_transmit[1] = HEAD_BYTE;
	data_state_relay_transmit[2] = DLEN_DATA;
	data_state_relay_transmit[3] = byte_state_relay_last;
	data_state_relay_transmit[4] = byte_state_relay_last >> 8;
	data_state_relay_transmit[5] = CRC_BUF;
	data_state_relay_transmit[6] = CRC_BUF;
	data_state_relay_transmit[7] = TAIL_BYTE;
	
	HAL_UART_Transmit(COMMU, (uint8_t*)data_state_relay_transmit,MAX_DATA_FRAME,100);
}
