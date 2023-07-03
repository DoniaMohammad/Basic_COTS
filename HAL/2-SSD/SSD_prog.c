#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STD_TYPES.h"
#include "Err_Type.h"
#include "DIO_interface.h"

#include "SSD_interface.h"

uint8 SSD_u8SetNumber(const SSD_config_t* copy_SSD_object,uint8 copy_u8Number)
{
	uint8 Local_u8ErrorState = OK , Local_u8Iterrator;

	static uint8 SSD_ARRAY[10] = {
			0b00111111, /*0*/
			0b00000110, /*1*/
			0b01011011, /*2*/
			0b01001111, /*3*/
			0b01100110, /*4*/
			0b01101101, /*5*/
			0b01111101, /*6*/
			0b00000111, /*7*/
			0b01111111, /*8*/
			0b01100111  /*9*/
	};

	if (copy_SSD_object != NULL)
	{
		/*In case of common cathode or ETA kit*/
		if ((copy_SSD_object->SSD_TYPE == CATHODE)||(copy_SSD_object->SSD_TYPE == ETA_KIT))
		{
			/*If led A pin is pin 0*/
			if (copy_SSD_object->SSD_LED_A_PIN==DIO_PIN0)
			{
				for (Local_u8Iterrator=DIO_PIN0 ; Local_u8Iterrator<=DIO_PIN6 ; Local_u8Iterrator++)
				{
					DIO_u8SetPinValue(copy_SSD_object->SSD_PORT,Local_u8Iterrator,GET_BIT(copy_u8Number,Local_u8Iterrator));
				}
			}

			else if (copy_SSD_object->SSD_LED_A_PIN==DIO_PIN1)
			{
				for (Local_u8Iterrator=DIO_PIN1 ; Local_u8Iterrator<=DIO_PIN7 ; Local_u8Iterrator++)
				{
					DIO_u8SetPinValue(copy_SSD_object->SSD_PORT,Local_u8Iterrator,GET_BIT(copy_u8Number,Local_u8Iterrator-1));
				}
			}
		}

		/*In case of common anode*/
		else if (copy_SSD_object->SSD_TYPE == ANODE)
		{
			/*If LED A pin is pin 0*/
			if (copy_SSD_object->SSD_LED_A_PIN==DIO_PIN0)
			{
				for (Local_u8Iterrator=DIO_PIN0 ; Local_u8Iterrator<=DIO_PIN6 ; Local_u8Iterrator++)
				{
					DIO_u8SetPinValue(copy_SSD_object->SSD_PORT,Local_u8Iterrator,~GET_BIT(copy_u8Number,Local_u8Iterrator));
				}
			}

			/*if LED A is pin 1*/
			else if (copy_SSD_object->SSD_LED_A_PIN==DIO_PIN1)
			{
				for (Local_u8Iterrator=DIO_PIN1 ; Local_u8Iterrator<=DIO_PIN7 ; Local_u8Iterrator++)
				{
					DIO_u8SetPinValue(copy_SSD_object->SSD_PORT,Local_u8Iterrator,~GET_BIT(copy_u8Number,Local_u8Iterrator-1));
				}
			}

			else
			{
				Local_u8ErrorState = NOK;
			}
		}

		else
		{
			Local_u8ErrorState = NOK;
		}
	}

	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;
}


uint8 SSD_u8Enable (const SSD_config_t* copy_SSD_object)
{
	uint8 Local_u8ErrorState = OK;

	/*check if the pointer is null*/
	if (copy_SSD_object != NULL)
	{
		/*in case of common anode or ETA kit -> put high on enable pin*/
		if ((copy_SSD_object->SSD_TYPE == ANODE)||(copy_SSD_object->SSD_TYPE == ETA_KIT))
		{
			DIO_u8SetPinValue(copy_SSD_object->SSD_ENABLE_PORT,copy_SSD_object->SSD_ENABLE_PIN,DIO_PIN_HIGH);
		}

		/*in case of common cathode -> put low on enable pin*/
		else if (copy_SSD_object->SSD_TYPE == CATHODE)
		{
			DIO_u8SetPinValue(copy_SSD_object->SSD_ENABLE_PORT,copy_SSD_object->SSD_ENABLE_PIN,DIO_PIN_LOW);
		}

		else
		{
			Local_u8ErrorState = NOK;
		}
	}

	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;
}


uint8 SSD_u8Disable(const SSD_config_t* copy_SSD_object)
{
	uint8 Local_u8ErrorState = OK;

		/*check if the pointer is null*/
		if (copy_SSD_object != NULL)
		{
			/*in case of common anode or ETA kit -> put low on enable pin*/
			if ((copy_SSD_object->SSD_TYPE == ANODE)||(copy_SSD_object->SSD_TYPE == ETA_KIT))
			{
				DIO_u8SetPinValue(copy_SSD_object->SSD_ENABLE_PORT,copy_SSD_object->SSD_ENABLE_PIN,DIO_PIN_LOW);
			}

			/*in case of common cathode -> put high on enable pin*/
			else if (copy_SSD_object->SSD_TYPE == CATHODE)
			{
				DIO_u8SetPinValue(copy_SSD_object->SSD_ENABLE_PORT,copy_SSD_object->SSD_ENABLE_PIN,DIO_PIN_HIGH);
			}

			else
			{
				Local_u8ErrorState = NOK;
			}
		}

		else
		{
			Local_u8ErrorState = NULL_PTR;
		}

		return Local_u8ErrorState;
}
