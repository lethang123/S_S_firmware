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
#define CBUF_SIZE_DATA           50
#define MAX_DATA_FRAME_TRANS     9

/*********************************************************************************
 * EXTERN VARIABLES
 */

/* using for transmition state relay */
extern uint16_t byte_state_relay_last;

/*********************************************************************************
 * LOCAL VARIABLES
 */

/* buffer data for circular_buf_t */
static uint8_t volatile cbuf_array_uart1[CBUF_SIZE_DATA];

/* check head byte of frame */
 uint8_t check_head_byte_one;
 uint8_t check_head_byte_two;

/* length of data frame */
 uint8_t dlength;

/* data control get in frame */
static uint16_t data_control_state_relay_uint16;

 /* save data of frame */
 uint8_t frame_data_get[10];

/* using for transmition state ralay */
static uint8_t data_state_relay_transmit[MAX_DATA_FRAME_TRANS];

 /*********************************************************************************
 * GLOBAL VARIABLES
 */
 
/* uart for communication */
UART_HandleTypeDef* COMMU = &huart3;

/* buffer of receive data 1*/
volatile uint8_t commu_buf_rx;

/* circular buffer */
circular_buf_t cbuf1;



static void get_data_control_state_relay(void)
{
  
	data_control_state_relay_uint16 = frame_data_get[1];
	data_control_state_relay_uint16 = data_control_state_relay_uint16 << 8 | frame_data_get[2];
}

/**
 *  @brief      COMMU initialize
 */
void COMMU_init(void)
{
	/* circular buffer init function */
	circular_buf_init(&cbuf1,cbuf_array_uart1,CBUF_SIZE_DATA);
	
	/* uart receive interrupt init */
	HAL_UART_Receive_IT(COMMU,(uint8_t *)&commu_buf_rx,1);
}

/**
 *  @brief      COMMU get data control 
 */
void COMMU_get_data_control(void)
{
	if(!circular_buf_empty(&cbuf1))
	{
		/* check head byte frist */
		circular_buf_get(&cbuf1,&check_head_byte_one);
		
		if(check_head_byte_one == HEAD_BYTE)
		{
			printf("head one is %d\n\r",check_head_byte_one);
			
			/* check head byte second */
			circular_buf_get(&cbuf1,&check_head_byte_two);
			
			if(check_head_byte_two == HEAD_BYTE)
			{
				printf("head two is %d\n\r",check_head_byte_two);
				/* get dleng byte */
        circular_buf_get(&cbuf1,&dlength);
				printf("dlength is %d\n\r",dlength);
				
				/* get all data of frame */
				circular_buf_get_array(&cbuf1,frame_data_get,dlength);
				
				printf("data 1 is %d\n\r",frame_data_get[0]);
				printf("data 2 is %d\n\r",frame_data_get[1]);
				printf("data 3 is %d\n\r",frame_data_get[2]);
				printf("data 4 is %d\n\r",frame_data_get[3]);
				
				/* if action control is check state of relay */
				if(frame_data_get[0] == DIR_CHECK)
				{
					/* transmition state of relay */
					COMMU_trans_state_relay(DIR_CHECK);
				}
				
				/* if action control is toggle state of relay */
				if(frame_data_get[0] == DIR_ACTION)
				{
					/* get data control relay */
					get_data_control_state_relay();
					
					/* toggle state relay */
					RELAY_action(data_control_state_relay_uint16);
					
					/* update state for button */
					CHECK_button_update(data_control_state_relay_uint16);
				}
				
				if(frame_data_get[0] == DIR_ACTION_ONE)
				{ 
					/* control one relay */
					RELAY_action_one(frame_data_get[1],frame_data_get[2]);
				}
			}
		}
  }
}
/**
 *  @brief      COMMU transmition state relay 
 */
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
	data_state_relay_transmit[8] = 'x';
	
	/* transmition frame data state relay */
	HAL_UART_Transmit(COMMU, (uint8_t*)data_state_relay_transmit,MAX_DATA_FRAME_TRANS,100);
}
