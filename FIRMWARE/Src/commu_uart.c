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
#include "check_state.h"

/*********************************************************************************
 * TYPEDEFS
 */
 
/*********************************************************************************
 * DEFINE
 */
#define CBUF_SIZE_DATA     50
#define MAX_DATA_FRAME     8

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
/*
static uint8_t buf;
static uint8_t check_head_byte_one;
static uint8_t check_head_byte_two;
static uint8_t dlength;
static uint8_t action_byte;
static uint8_t data_control_state_relay_uint8_one;
static uint8_t data_control_state_relay_uint8_two;
static uint8_t crc_data;
static uint8_t tail_data;*/
static uint16_t data_control_state_relay_uint16;
static uint8_t check_head_byte_one;
static uint8_t dlength;
static uint8_t frame_data_get[10];
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


static void get_data_control_state_relay(void)
{
  
	data_control_state_relay_uint16 = frame_data_get[1];
	data_control_state_relay_uint16 = data_control_state_relay_uint16 << 8 | frame_data_get[2];
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
	if(!circular_buf_empty(&cbuf1))
	{
		if(circular_buf_check(&cbuf1) == HEAD_BYTE)
		{
			circular_buf_get(&cbuf1,&check_head_byte_one);
			printf("%d\n\r",check_head_byte_one);
			if( check_head_byte_one == HEAD_BYTE)
			{
				/* get byte data length */
				circular_buf_get(&cbuf1,&dlength);
				printf("%d\r\n",dlength);
				
				/* get all data of frame */
				circular_buf_get_array(&cbuf1,frame_data_get,dlength - 1);
			}
			
			/* if action is check */
			if(frame_data_get[0] == DIR_CHECK)
			{
				COMMU_trans_state_relay(DIR_CHECK);
			}
			
			/* if action is control relay */
			if(frame_data_get[0] == DIR_ACTION)
			{
				/* get data control relay */
				get_data_control_state_relay();
				
				/* toggle state relay */
				RELAY_action(data_control_state_relay_uint16);
				
				/* update state for button */
				CHECK_button_update(data_control_state_relay_uint16);
			}
		}
	}
}

void COMMU_trans_state_relay(uint8_t dir_data)
{
	/* set data for transmition */
	data_state_relay_transmit[0] = HEAD_BYTE;
	data_state_relay_transmit[1] = HEAD_BYTE;
	data_state_relay_transmit[2] = DLEN_DATA_TRANS;
	if(dir_data == DIR_CHECK)
	{
		data_state_relay_transmit[3] = DIR_CHECK;
	}
	else
	{
		data_state_relay_transmit[3] = DIR_ACTION;
	}
	data_state_relay_transmit[4] = byte_state_relay_last >> 8;
	data_state_relay_transmit[5] = byte_state_relay_last;
	data_state_relay_transmit[6] = CRC_BUF;
	data_state_relay_transmit[7] = TAIL_BYTE;
	
	/* transmition frame data state relay */
	HAL_UART_Transmit(COMMU, (uint8_t*)data_state_relay_transmit,MAX_DATA_FRAME,100);
}
