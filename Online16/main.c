#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "ADC_Int.h"
int main(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
	
	u8 k,flag=0,flag2=0;
	u8 count=0,num1=0,num2=0,binary[8]={0},y=0,count2=0;
	u32 num3=0,i=0;
	//LCD_SetCursor(1,0);
	//LCD_WriteCh('B');
	LCD_SetCursor(0,4);
	LCD_WriteString("Hello");
	_delay_ms(500);
	LCD_Clear();
	
	
	while (1)
	{
		k=KEYPAD_GetKey();
		if((flag==0)||k=='c'||(num1==0)||(num2==0))
		{
			if(k=='c')
			{
				flag=0;
				count=0;
				num1=0;
				num2=0;
				num3=0;
			}
			if(flag==0)
			{
				LCD_SetCursor(0,0);
				LCD_WriteString("Convert..to..");
				LCD_SetCursor(1,0);
				LCD_WriteString("1-H 2-B 3-D");
				flag=1;
			}
			
			if(count==0)
			{
				
				if(k=='1')
				{
					LCD_Clear();
					LCD_SetCursor(0,0);
					num1=k;
					count++;
					LCD_WriteString("H:");
				}else if(k=='2')
				{
					LCD_Clear();
					LCD_SetCursor(0,0);
					num1=k;
					count++;
					i=14;
					LCD_WriteString("B:");
				}else if (k=='3')
				{
					LCD_Clear();
					LCD_SetCursor(0,0);
					num1=k;
					count++;
					LCD_WriteString("D:");
				}else
				{
					;
				}
				
			}else
			{
				LCD_SetCursor(1,0);
				if(k=='1')
				{
					num2=k;
					count++;
					LCD_WriteString("H:");
				}else if(k=='2')
				{
					num2=k;
					count++;
					LCD_WriteString("B:");
				}else if (k=='3')
				{
					num2=k;
					count++;
					LCD_WriteString("D:");
				}else
				{
					;
				}
			}
		}
		else
		{
			if(k!=NO_KEY)
			{
				if((num1=='3')&&num2=='1')
				{
					if(k>='0'&&k<='9')
					{
						LCD_SetCursor(0,3);
						LCD_WriteString("               ");
						LCD_SetCursor(0,3);
						num3=(num3*10)+(k-'0');
						LCD_WriteNumber(num3);
					}
					else if (k=='=')
					{
						LCD_SetCursor(1,3);
						LCD_WriteString("      ");
						LCD_SetCursor(1,3);
						LCD_WriteHex(num3);
						num3=0;
					}
				}
				else if((num1=='3')&&num2=='2')
				{
					
					if(k>='0'&&k<='9')
					{
						LCD_SetCursor(0,3);
						LCD_WriteString("               ");
						LCD_SetCursor(0,3);
						num3=(num3*10)+(k-'0');
						LCD_WriteNumber(num3);
					}
					else if (k=='=')
					{
						LCD_SetCursor(1,3);
						LCD_WriteString("      ");
						LCD_SetCursor(1,3);
						LCD_WriteBinary(num3);
						num3=0;
					}
					
				}
				else if((num1=='2')&&num2=='3')
				{
					
					if(k>='0'&&k<='1')
					{
						if(flag2==1)
						{
							LCD_SetCursor(0,7);
							LCD_WriteString("                  ");
							flag2=0;
						}
						LCD_SetCursor(0,i);
						binary[y]=k-'0';
						i--;
						y++;
						LCD_WriteCh(k);
					}
					else if (k=='=')
					{
						i=14;
						binary[8]=0;
						y=0;
						LCD_SetCursor(1,3);
						LCD_WriteString("      ");
						LCD_SetCursor(1,3);
						LCD_WriteNumber(LCD_WriteBinary_to_decimal(binary));
						flag2=1;
					}
					
					
				}
				
				else if((num1=='2')&&num2=='1')
				{
					
					if(k>='0'&&k<='1')
					{
						if(flag2==1)
						{
							LCD_SetCursor(0,7);
							LCD_WriteString("                  ");
							flag2=0;
						}
						LCD_SetCursor(0,i);
						binary[y]=k-'0';
						i--;
						y++;
						LCD_WriteCh(k);
					}
					else if (k=='=')
					{
						i=14;
						binary[8]=0;
						y=0;
						LCD_SetCursor(1,3);
						LCD_WriteString("      ");
						LCD_SetCursor(1,3);
						LCD_WriteHex(LCD_WriteBinary_to_decimal(binary));
						flag2=1;
					}
					
					
				}
				else if((num1=='1')&&num2=='3')
				{
					if(flag2==0)
					{
						LCD_SetCursor(0,3);
						LCD_WriteString("               ");
						LCD_SetCursor(0,3);
						flag2=1;
					}else
					{
						;
					}
					
					if((k>='0'&&k<='9')||((k>='A')&&(k<='F')))
					{
						
						
						if(k>='D')
						{
							if(count2==0)
							{
								k='D';
							}else if(count2==1)
							{
								k='E';
							}else if(count2==2)
							{
								k='F';
							}
							count2++;
						}else
						{
							;
						}
						
						if((k>='0'&&k<='9'))
						{
							k=k-'0';
							LCD_WriteNumber(k);
						}else
						{
							LCD_WriteCh(k);
							k=k-'A'+10;
						}
						binary[y]=k;
						y++;
						
						
					}
					else if (k=='=')
					{
						y--;
						num3=LCD_WriteHex_to_decimal(binary,(y));
						count2=0;
						y=0;
						flag2=0;
						binary[8]=0;
						LCD_SetCursor(1,3);
						LCD_WriteString("      ");
						LCD_SetCursor(1,3);
						LCD_WriteNumber(num3);
						num3=0;
					}
					
				}
				else if((num1=='1')&&num2=='2')
				{
					if(flag2==0)
					{
						LCD_SetCursor(0,3);
						LCD_WriteString("               ");
						LCD_SetCursor(0,3);
						flag2=1;
					}else
					{
						;
					}
					
					if((k>='0'&&k<='9')||((k>='A')&&(k<='F')))
					{
						
						
						if(k>='D')
						{
							if(count2==0)
							{
								k='D';
							}else if(count2==1)
							{
								k='E';
							}else if(count2==2)
							{
								k='F';
							}
							count2++;
						}else
						{
							;
						}
						
						if((k>='0'&&k<='9'))
						{
							k=k-'0';
							LCD_WriteNumber(k);
						}else
						{
							LCD_WriteCh(k);
							k=k-'A'+10;
						}
						binary[y]=k;
						y++;
						
						
					}
					else if (k=='=')
					{
						y--;
						num3=LCD_WriteHex_to_decimal(binary,(y));
						count2=0;
						y=0;
						flag2=0;
						binary[8]=0;
						LCD_SetCursor(1,3);
						LCD_WriteString("      ");
						LCD_SetCursor(1,3);
						LCD_WriteBinary(num3);
						num3=0;
					}
					
				}
			}
		}
		
	}
}

