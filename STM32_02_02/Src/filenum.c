 /**
  ******************************************************************************
  * File Name          : filenum.c
  * Description        : 
  ******************************************************************************
  */
  
#include <stdbool.h>
#include <stdint.h>

#include "filenum.h"
#include "usart.h"


void aFailed (uint8_t file, uint32_t line)
{
	printf(" Wrong parameters value: file %d on line %d \r\n", file , line);
}


//******************************************end****************************************//

