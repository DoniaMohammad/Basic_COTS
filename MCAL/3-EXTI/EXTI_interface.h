#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


#define		LOW_LEVEL		1u
#define		ON_CHANGE		2u
#define 	FALLING_EDGE	3u
#define 	RISING_EDGE		4u


typedef enum
{
	INT0,
	INT1,
	INT2
}EXTI_IntNum_t;

void EXTI_voidInit (void);

uint8 EXTI_u8SetSenseCtrl (EXTI_IntNum_t copy_IntNum, uint8 copy_u8SenseCtrl);
uint8 EXTI_u8IntEnable (EXTI_IntNum_t copy_IntNum);
uint8 EXTI_u8IntDisable (EXTI_IntNum_t copy_IntNum);

#endif
