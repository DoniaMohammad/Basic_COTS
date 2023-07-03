#include "STD_TYPES.h"
#include "DIO_interface.h"

void DCMotor_voidRotateCW (DIO_Port_t copy_DCmotor_PORT, DIO_Pin_t copy_DCmotor_PIN1, DIO_Pin_t copy_DCmotor_PIN2)
{
	DIO_u8SetPinValue(copy_DCmotor_PORT,copy_DCmotor_PIN1,DIO_PIN_LOW);
	DIO_u8SetPinValue(copy_DCmotor_PORT,copy_DCmotor_PIN2,DIO_PIN_HIGH);
}


void DCMotor_voidRotateCCW (DIO_Port_t copy_DCmotor_PORT, DIO_Pin_t copy_DCmotor_PIN1, DIO_Pin_t copy_DCmotor_PIN2)
{
	DIO_u8SetPinValue(copy_DCmotor_PORT,copy_DCmotor_PIN2,DIO_PIN_LOW);
	DIO_u8SetPinValue(copy_DCmotor_PORT,copy_DCmotor_PIN1,DIO_PIN_HIGH);
}


void DCMotor_voidStop (DIO_Port_t copy_DCmotor_PORT, DIO_Pin_t copy_DCmotor_PIN1, DIO_Pin_t copy_DCmotor_PIN2)
{
	DIO_u8SetPinValue(copy_DCmotor_PORT,copy_DCmotor_PIN2,DIO_PIN_LOW);
	DIO_u8SetPinValue(copy_DCmotor_PORT,copy_DCmotor_PIN1,DIO_PIN_LOW);
}
