 /**
  ******************************************************************************
  * File Name          : filenum.h
  * Description        : 
  ******************************************************************************
  */
  
#ifndef FILE_NUMBER_H
#define FILE_NUMBER_H

#include <stdbool.h>
#include <stdint.h>

#define FILENUM(num)     \
enum { F_NUM = num};     \
void _dummy##num(void){};


#define ASSERT(expr)      \
if (expr)                 \
{                         \
}                         \
else                      \
{                         \
 aFailed(F_NUM, __LINE__);\
}

void aFailed (uint8_t file, uint32_t line);

	
#endif /* File_NUMBER_H*/
