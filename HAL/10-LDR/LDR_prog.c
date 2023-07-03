#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LDR_cfg.h"
#include "LDR_interface.h"


uint8 LDR_u8GetLightLevel(uint8 copy_u8ChannelReading)
{
	uint8 Local_u8LightLevel;

	Local_u8LightLevel = (copy_u8ChannelReading* MAXVOLT) / LDR_RESOLUTION;

	return Local_u8LightLevel;
}
