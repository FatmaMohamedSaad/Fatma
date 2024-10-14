


#ifndef LCD_INT_H_
#define LCD_INT_H_
void LCD_Init(void);
void WriteInst(u8 ins);
void WriteData(u8 Data);
void LCD_WriteString(c8*str);
void LCD_WriteStringCursor(u8 line,u8 cell,c8*str);
void LCD_ClearCursor(u8 line,u8 cell,u8 NofCells);
u32 String_Length(u8*str);
void LCD_WriteCh(u8 ch);
void LCD_WriteNumber(s32 num);
void LCD_SetCursor(u8 line,u8 cell);
void LCD_CustomChar(u8 address,u8* Pattern);
void LCD_ReturnToDDRAM(void);
/*move on LCD*/
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
u8 LCD_WriteBinary_to_decimal(u8 *num);
u8 LCD_WriteHex_to_decimal(u8 *num,u8 cell);
void LCD_Clear(void);




#endif /* LCD_INT_H_ */