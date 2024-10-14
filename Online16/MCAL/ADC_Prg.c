#include "StdTypes.h"
#include "MemMap.h"
#include "ADC_Int.h"
#define  F_CPU   8000000
#include <util/delay.h>
static u8 ConversionFlag=0;
void ADC_Init(ADC_VREF_t vref,ADC_Prescaler_t scaler)
{
	/*vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_VCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	/*prescaler*/
	ADCSRA=ADCSRA&0xf8;
	ADCSRA=ADCSRA|scaler;
	/*pins*/
	/*enable*/
	SET_BIT(ADCSRA,ADEN);
}
u16 ADC_Read(ADC_Channel_t ch)
{
	/*select channel*/
	ADMUX=ADMUX&0xE0;
	ADMUX=ADMUX|ch;
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait until conversion end*/
	while(GET_BIT(ADCSRA,ADSC));//called busy wait Or Blocking
	//_delay_ms(1);
	/* get reading*/
	//ADC=ADCH<<8|ADCL;
	
	return ADC;
}


u16 ADC_ReadVolt(ADC_Channel_t ch)
{
	u16 adc=ADC_Read(ch);
	u16 volt;
	volt=((u32)5000*adc)/1024;
	return volt;
}
void ADC_StartConversion(ADC_Channel_t ch)
{
	if(ConversionFlag==0)
	{
		/*select channel*/
		ADMUX=ADMUX&0xE0;
		ADMUX=ADMUX|ch;
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		ConversionFlag=1;
	}
	
}
u16 ADC_GetRead(void)
{
	/*wait until conversion end*/
	while(GET_BIT(ADCSRA,ADSC)); 
	return ADC;
}
Error_t ADC_GetReadPerodic(u16*Pdata)
{
	if(!GET_BIT(ADCSRA,ADSC))//called pulling
	{
		*Pdata=ADC;
		ConversionFlag=1;
		return OK;
	}
	return IN_PROGRESS;
}
u16 ADC_GetReadNoBlock(void)
{
	/*wait until conversion end*/
	while(GET_BIT(ADCSRA,ADSC));
	return ADC;
}