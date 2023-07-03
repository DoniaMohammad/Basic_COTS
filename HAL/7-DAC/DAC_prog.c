#include "STD_TYPES.h"
#include "Err_Type.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "DAC_interface.h"
#include "DAC_cfg.h"
#include "DAC_prv.h"
#include <util/delay.h>

void DAC_voidSetAnalogVolt (uint16 copy_u16AnalogVolt)
{
	if (copy_u16AnalogVolt <= DAC_REFVOLT)
	{
		DIO_u8SetPortValue(DAC_PORT, copy_u16AnalogVolt/DAC_STEP);
	}

	else
	{
		/*Do nothing*/
	}

}
