#define  F_CPU   8000000
#include <util/delay.h>
#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "LCD_Cfg.h"
#if LCD_MODE==_8_BIT
void WriteInst(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,High);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void WriteData(u8 Data)
{
	DIO_WritePin(RS,High);
	DIO_WritePort(LCD_PORT,Data);
	DIO_WritePin(EN,High);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteInst(0x38);
	WriteInst(0x0c);
	WriteInst(0x01);//Clear Screen
	_delay_ms(1);
	WriteInst(0x06);
}
#elif LCD_MODE==_4_BIT
void WriteInst(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,GET_BIT(ins,7));
	DIO_WritePin(D6,GET_BIT(ins,6));
	DIO_WritePin(D5,GET_BIT(ins,5));
	DIO_WritePin(D4,GET_BIT(ins,4));
	DIO_WritePin(EN,High);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,GET_BIT(ins,3));
	DIO_WritePin(D6,GET_BIT(ins,2));
	DIO_WritePin(D5, GET_BIT(ins,1));
	DIO_WritePin(D4,GET_BIT(ins,0));
	DIO_WritePin(EN,High);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void WriteData(u8 Data)
{
	DIO_WritePin(RS,High);
	DIO_WritePin(D7,GET_BIT(Data,7));
	DIO_WritePin(D6,GET_BIT(Data,6));
	DIO_WritePin(D5,GET_BIT(Data,5));
	DIO_WritePin(D4,GET_BIT(Data,4));
	DIO_WritePin(EN,High);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,GET_BIT(Data,3));
	DIO_WritePin(D6,GET_BIT(Data,2));
	DIO_WritePin(D5, GET_BIT(Data,1));
	DIO_WritePin(D4,GET_BIT(Data,0));
	DIO_WritePin(EN,High);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteInst(0x02);
	WriteInst(0x28);
	WriteInst(0x0c);
	WriteInst(0x01);//Clear Screen
	_delay_ms(1);
	WriteInst(0x06);
}
#endif
void LCD_WriteString(c8*str)
{
	u8 i;
		for(i=0; str[i]; i++)
		{
			WriteData(str[i]);
		}

}
void LCD_WriteCh(u8 ch)
{
	WriteData(ch);
}
void LCD_WriteNumber(s32 num)
{
	s32 num1=num;
	s8 i=0,arr[10]={0};
		if (num==0)
		{
			arr[i]='0';
			return;
		}else
		{
			if(num1<0)
			{
				LCD_WriteCh('-');
				num=num*-1;
			}else
			{
				;
			}
		}
		
	for(i;num>0;i++)
	{
		arr[i]=(num%10)+'0';
		//WriteData(k+48);
		num=num/10;
	}
	/*if(num1<0)
	{
		arr[i]='-';
		i++;
	}else
	{
		;
	}*/
	arr[i]=0;
	for(i=i-1;i>=0;i--)
	{
		
		WriteData((arr[i]));
		
	}
}
void LCD_SetCursor(u8 line,u8 cell)
{
	if (line==0)
	{
		WriteInst(cell+0x80);//0x80 from datasheet to set DDRAM Address
	}else
	{
		WriteInst(cell+0x40+0x80);
	}	
}
/*move on LCD*/
void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		LCD_WriteCh(GET_BIT(num,i)+'0');
	}
	
}
void LCD_WriteHex(u8 num)
{
	u8 HN=num>>4;
	u8 LN=num&0x0F;
	 if(HN<10)
	 {
		 LCD_WriteCh(HN+'0');
	 }
	 else
	 {
		 LCD_WriteCh(HN+'A'-10);
	 }
	 if(LN<10)
	 {
		 LCD_WriteCh(LN+'0');
	 }
	 else
	 {
		 LCD_WriteCh(LN+'A'-10);
	 }
}
u8 LCD_WriteBinary_to_decimal(u8 *num)
{
	s8 i,u=1;
	u8 r=0;
	for(i=0;i<8;i++)
	{
		r=(num[i]*u)+r;
		u=u*2;
	}
	return r;
}
u8 LCD_WriteHex_to_decimal(u8 *num,u8 cell)
{
	s8 i,u=1;
	u8 r=0;
	for(i=cell;i>=0;i--)
	{
		r=(num[i]*u)+r;
		u=u*16;
	}
	return r;
}
void LCD_Clear(void)
{
	WriteInst(0x01);//Clear Screen
	_delay_ms(1);
}
void LCD_ClearCursor(u8 line,u8 cell,u8 NofCells)
{
	LCD_SetCursor(line,cell);
	for(u8 i=0;i<NofCells;i++)
	{
		LCD_WriteString("   ");
	}
}
void LCD_WriteStringCursor(u8 line,u8 cell,c8*str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
}
void LCD_CustomChar(u8 address,u8* Pattern)
{
	WriteInst((0x40)|(address*8));
	u8 i;
	for(i=0;i<8;i++)
	{
		WriteData(Pattern[i]);
	}
	
	//WriteInst((0x80));
}
void LCD_ReturnToDDRAM(void)
{
	WriteInst((0x80));
	LCD_SetCursor(0,1);
}
