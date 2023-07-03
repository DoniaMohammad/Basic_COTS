#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LED_interface.h"


void LED_voidSetON (const LED_config_t* copy_LEDObject)
{
	if (copy_LEDObject->ACTIVITY_TYPE == ACTIVE_HIGH)
	{
		DIO_u8SetPinValue(copy_LEDObject->LED_PORT , copy_LEDObject->LED_PIN , DIO_PIN_HIGH);
	}

	else if (copy_LEDObject->ACTIVITY_TYPE == ACTIVE_LOW)
	{
		DIO_u8SetPinValue(copy_LEDObject->LED_PORT , copy_LEDObject->LED_PIN , DIO_PIN_LOW);
	}
}


void LED_voidSetOFF (const LED_config_t* copy_LEDObject)
{
	if (copy_LEDObject->ACTIVITY_TYPE == ACTIVE_HIGH)
	{
		DIO_u8SetPinValue(copy_LEDObject->LED_PORT , copy_LEDObject->LED_PIN , DIO_PIN_LOW);
	}

	else if (copy_LEDObject->ACTIVITY_TYPE == ACTIVE_LOW)
	{
		DIO_u8SetPinValue(copy_LEDObject->LED_PORT , copy_LEDObject->LED_PIN , DIO_PIN_HIGH);
	}
}

void LED_voidToggle (const LED_config_t* copy_LEDObject)
{
	DIO_u8TogglePinValue(copy_LEDObject->LED_PORT , copy_LEDObject->LED_PIN);
}
