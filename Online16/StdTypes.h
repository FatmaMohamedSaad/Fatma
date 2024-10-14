
#ifndef STDTYPES_H_
#define STDTYPES_H_
typedef signed char           s8;
typedef  char                 c8;
typedef signed short int      s16;
typedef signed long int       s32;
typedef signed long long int  s64;

typedef unsigned char           u8;
typedef unsigned short int      u16;
typedef unsigned long int       u32;
typedef unsigned long long int  u64;



typedef float                   f32; //4-Byte 6 Decimal Point
typedef double                  f64; //8-Byte 14 Decimal Point
typedef long double             f96; //12-Byte 19 decimal Point
#define MAX_U8    255
#define MIN_U8    0
#define MAX_S8    127
#define MIN_S8   -128
#define MAX_U16   65535
#define MAX_U32   16777215
typedef enum {
	FALSE=0X55,
	TRUE=0XAA
}bool_t;
typedef enum{
	OK,
	NOK,
	NULL_PTR,
	OUT_OUT_RANGE,
	IN_PROGRESS
}Error_t;
#define  F_CPU   8000000
#include <util/delay.h>
#define NULLPTR ((void*)0)
#define  GET_BIT(reg,bit)  ((reg>>bit)&1)
#define  SET_BIT(reg,bit)  (reg=reg|(1<<bit))
#define  CLR_BIT(reg,bit)  (reg=reg&~(1<<bit))
#define  TOG_BIT(reg,bit)  (reg=reg^(1<<bit))






#endif /* STDTYPES_H_ */