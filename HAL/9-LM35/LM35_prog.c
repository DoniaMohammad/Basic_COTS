#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LM35_cfg.h"
#include "LM35_interface.h"


uint8 LM35_u8GetTemp(uint8 copy_u8ChannelReading)
{
	uint8 Local_u8Temp;

	Local_u8Temp = (copy_u8ChannelReading* (MAXVOLT/10)) / LM35_RESOLUTION;
	
	return Local_u8Temp;
}
