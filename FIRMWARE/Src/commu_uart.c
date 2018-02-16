/** @file
  * 
  * @brief COMMUNICATION UART
  *
  */
	
/*********************************************************************************
 * INCLUDE
 */
#include "usart.h"
#include "commu_uart.h"
#include "relay.h"

/*********************************************************************************
 * TYPEDEFS
 */
 
typedef enum
{
	BYTE_HEAD_FALSE = 0,
	BYTE_HEAD_TRUE
}check_head_return_t;

/*********************************************************************************
 * DEFINE
 */
#define CBUF_SIZE_DATA     50
#define MAX_DATA_FRAME     8

#define HEAD_BYTE          0x55
#define DLEN_DATA          0x05
#define ACTION_CHECK       0x00
#define ACTION_TOGGLE      0x01
#define CRC_BUF            0x00
#define TAIL_BYTE          0xFF

/*********************************************************************************
 * EXTERN VARIABLES
 */

/* using for transmition state relay */
extern bool flag_button_toggle_state;
extern uint16_t byte_state_relay_last;

/*********************************************************************************
 * LOCAL VARIABLES
 */
 
/* buffer data for circular_buf_t */
static uint8_t volatile cbuf_array_uart1[CBUF_SIZE_DATA];
/* save data of frame */
static uint8_t check_head_byte_one;
static uint8_t check_head_byte_two;
static uint8_t dlength;
static uint8_t action_byte;
static uint8_t data_control_state_relay_uint8;
static uint16_t data_control_state_relay_uint16;
/* using for transmition state ralay */
static uint8_t data_state_relay_transmit[MAX_DATA_FRAME];

 /*********************************************************************************
 * GLOBAL VARIABLES
 */
 
/* uart for communication */
UART_HandleTypeDef* COMMU = &huart1;

/* buffer of receive data 1*/
volatile uint8_t commu_buf_rx;

/* circular buffer */
circular_buf_t cbuf1;

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

static void get_data_control_state_relay(void)
{
  circular_buf_get(&cbuf1,&data_control_state_relay_uint8);
	data_control_state_relay_uint16 = data_control_state_relay_uint8 << 8;
	circular_buf_get(&cbuf1,&data_control_state_relay_uint8);
	data_control_state_relay_uint16 |= data_control_state_relay_uint8;
}

void COMMU_init(void)
{
	/* circular buffer init function */
	circular_buf_init(&cbuf1,cbuf_array_uart1,CBUF_SIZE_DATA);
	
	/* uart receive interrupt init */
	HAL_UART_Receive_IT(COMMU,(uint8_t *)&commu_buf_rx,1);
}

void COMMU_get_data_control(void)
{ 
	/* check head byte */
	if(  check_head_byte()  )
	{
		/* get byte data length */
		circular_buf_get(&cbuf1,&dlength);
		/* get byte action */
		circular_buf_get(&cbuf1,&action_byte);
		
		/* if action is check */
		if(action_byte == ACTION_CHECK)
		{
			flag_button_toggle_state = true;
		}
		
		/* if action is toggle relay */ 
		if(action_byte == ACTION_TOGGLE)
		{
			/* get data control relay */
      get_data_control_state_relay();
			
			/* toggle state relay */
			RELAY_action(data_control_state_relay_uint16);
		}
	}
}

void COMMU_trans_state_relay(void)
{
	/* set data for transmition */
	data_state_relay_transmit[0] = HEAD_BYTE;
	data_state_relay_transmit[1] = HEAD_BYTE;
	data_state_relay_transmit[2] = DLEN_DATA;
	data_state_relay_transmit[3] = byte_state_relay_last;
	data_state_relay_transmit[4] = byte_state_relay_last >> 8;
	data_state_relay_transmit[5] = CRC_BUF;
	data_state_relay_transmit[6] = CRC_BUF;
	data_state_relay_transmit[7] = TAIL_BYTE;
	/* transmition frame data state relay */
	HAL_UART_Transmit(COMMU, (uint8_t*)data_state_relay_transmit,MAX_DATA_FRAME,100);
}
