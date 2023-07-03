#include "STD_TYPES.h"
#include "Err_Type.h"
#include "DIO_interface.h"
#include "STP_interface.h"
#include "STP_cfg.h"
#include <util/delay.h>

uint8 Stepper_u8Rotate (const STEPPER_cfg_t* stepper_object, uint16 copy_u16Angle, uint8 copy_u8Direction)
{
	uint8 Local_u8ErrorState = OK;
	uint16 Local_u16Step , Local_u16Iterrator;
	Local_u16Step = (uint16)(((uint32)copy_u16Angle*2048UL)/360UL);

	if (stepper_object != NULL)
	{
		if (copy_u8Direction == ClockWise)
		{
			for (Local_u16Iterrator=0 ; Local_u16Iterrator<Local_u16Step/4 ; Local_u16Iterrator++)
			{

				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->BLUE_PIN,DIO_PIN_LOW);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->PINK_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->YELLOW_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->ORANGE_PIN,DIO_PIN_HIGH);
				_delay_ms(2);

				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->BLUE_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->PINK_PIN,DIO_PIN_LOW);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->YELLOW_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->ORANGE_PIN,DIO_PIN_HIGH);
				_delay_ms(2);

				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->BLUE_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->PINK_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->YELLOW_PIN,DIO_PIN_LOW);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->ORANGE_PIN,DIO_PIN_HIGH);
				_delay_ms(2);

				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->BLUE_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->PINK_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->YELLOW_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->ORANGE_PIN,DIO_PIN_LOW);
				_delay_ms(2);
			}
		}

		else if (copy_u8Direction == CounterClockWise)
		{
			for (Local_u16Iterrator=0 ; Local_u16Iterrator<Local_u16Step/4 ; Local_u16Iterrator++)
			{

				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->ORANGE_PIN,DIO_PIN_LOW);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->YELLOW_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->PINK_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->BLUE_PIN,DIO_PIN_HIGH);
				_delay_ms(2);

				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->ORANGE_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->YELLOW_PIN,DIO_PIN_LOW);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->PINK_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->BLUE_PIN,DIO_PIN_HIGH);
				_delay_ms(2);


				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->ORANGE_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->YELLOW_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->PINK_PIN,DIO_PIN_LOW);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->BLUE_PIN,DIO_PIN_HIGH);
				_delay_ms(2);

				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->ORANGE_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->YELLOW_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->PINK_PIN,DIO_PIN_HIGH);
				DIO_u8SetPinValue(stepper_object->STEPPER_PORT,stepper_object->BLUE_PIN,DIO_PIN_LOW);
				_delay_ms(2);
			}
		}
	}

	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;
}
