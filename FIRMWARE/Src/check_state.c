/*
 */
#include "check_state.h"
#include "usart.h"
#include "relay.h"

#define MAX_DATA_FRAME   8
#define HEAD_BYTE        0x55
#define DLEN_DATA        0x05
#define CRC_BUF          0x00
#define TAIL_BYTE        0xFF

bool flag_toggle_state = false;

static uint16_t s_byte_check_state_button = 0x0000U;
static uint8_t data_state_relay_transmit[MAX_DATA_FRAME];

uint16_t byte_state_button;

void check_state_button_it(uint16_t GPIO_Pin)
{
	/* if button 1 */
	if(GPIO_Pin == GPIO_PIN_10)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x1000);
	}
	
	/* if button 1 */
	if(GPIO_Pin == GPIO_PIN_11)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x0100);
	}
	
	/* if button 1 */
	if(GPIO_Pin == GPIO_PIN_12)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x0010);
	}
	
	/* if button 1 */
	if(GPIO_Pin == GPIO_PIN_13)
	{
		s_byte_check_state_button = s_byte_check_state_button ^ (0x0001);
	}
	
	/* toggle relay pin */
	relay_toggle_state_pin(GPIO_Pin);                                             /***********************************/
	
	/* update state buttton */
	byte_state_button = s_byte_check_state_button;
	
	/* flag state toggle*/
	flag_toggle_state = true;
}

void transmit_state_relay(void)
{
	data_state_relay_transmit[0] = HEAD_BYTE;
	data_state_relay_transmit[1] = HEAD_BYTE;
	data_state_relay_transmit[2] = DLEN_DATA;
	data_state_relay_transmit[3] = 
	data_state_relay_transmit[4] = 
	data_state_relay_transmit[5] = CRC_BUF;
	data_state_relay_transmit[6] = CRC_BUF;
	data_state_relay_transmit[7] = TAIL_BYTE;
	
	HAL_UART_Transmit(&huart1, (uint8_t*)data_state_relay_transmit,MAX_DATA_FRAME,100);
}
