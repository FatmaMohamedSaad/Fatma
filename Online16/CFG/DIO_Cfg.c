#include "DIO_Int.h"
#include "StdTypes.h"
#include "DIO_Private.h"
#include "DIO_Cfg.h"
/*OUTPUT,INPULL,INFREE*/
const DIO_Status_t PinStatusArr[TOTAL_PINS]={
	INFREE,/*A0*/
	OUTPUT,/*A1*/
	OUTPUT,/*A2*/
	OUTPUT,/*A3*/
	OUTPUT,/*A4*/
	OUTPUT,/*A5*/
	OUTPUT,/*A6*/
	INFREE,/*A7*/
	OUTPUT,/*B0*/
	OUTPUT,/*B1*/
	OUTPUT,/*B2*/
	OUTPUT,/*B3*/
	OUTPUT,/*B4*/
	OUTPUT,/*B5*/
	OUTPUT,/*B6*/
	OUTPUT,/*B7*/
	OUTPUT,/*C0*/
	OUTPUT,/*C1*/
	OUTPUT,/*C2*/
	OUTPUT,/*C3*/
	OUTPUT,/*C4*/
	OUTPUT,/*C5*/
	OUTPUT,/*C6*/
	OUTPUT,/*C7*/
	OUTPUT,/*D0*/
	INPULL,/*D1*/
	INPULL,/*D2*/
	INPULL,/*D3*/
	INPULL,/*D4*/
	INPULL,/*D5*/
	OUTPUT,/*D6*/
	OUTPUT,/*D7*/
};
