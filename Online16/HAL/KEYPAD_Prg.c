#define KEYPAD_PRG 1
#include "StdTypes.h"
#include "DIO_Int.h"
#include "KEYPAD_Int.h"
#include "KEYPAD_Cfg.h"

					
void KEYPAD_Init(void)
{
	u8 r;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,High);
	}
}
u8 KEYPAD_GetKey(void)
{
	u8 r,c,Key=NO_KEY;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for(c=0;c<COLS;c++)
		{
			if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{
				Key=KeysArr[r][c];
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,High);
	}
	return Key;
}