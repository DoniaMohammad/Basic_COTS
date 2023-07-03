#include "STD_TYPES.h"
#include "Err_Type.h"
#include "DIO_interface.h"
#include "SWITCHES_interface.h"

uint8 Switch_u8GetState (const Switch_cfg_t* copy_pu8Switch, uint8* copy_pu8State)
{
	uint8 Local_u8ErrorState = OK, Local_u8PinValue;

	if (copy_pu8Switch != NULL)
	{
		DIO_u8GetPinValue(copy_pu8Switch->SwitchPort, copy_pu8Switch->SwitchPin, &Local_u8PinValue);
		if (Local_u8PinValue == DIO_PIN_LOW)
		{
			if (copy_pu8Switch->switchPullType == PULL_UP)
			{
				*copy_pu8State = PRESSED;
			}

			else if (copy_pu8Switch->switchPullType == PULL_DOWN)
			{
				*copy_pu8State = RELEASED;
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
		}

		else if (Local_u8PinValue == DIO_PIN_HIGH)
		{
			if (copy_pu8Switch->switchPullType == PULL_UP)
			{
				*copy_pu8State = RELEASED;
			}

			else if (copy_pu8Switch->switchPullType == PULL_DOWN)
			{
				*copy_pu8State = PRESSED;
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
