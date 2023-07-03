#include "STD_TYPES.h"

#include "BIT_MATH.h"
#include "Err_Type.h"

#include "TIMERS_cfg.h"
#include "TIMERS_interface.h"
#include "TIMERS_prv.h"
#include "TIMERS_reg.h"

static void (*TIMER0_pvNotificationFunc)(void) = NULL;

void TIMER0_voidInit(void)
{
	/*Set waveform generation mode: CTC*/
	SET_BIT(TCCR0, TCCR0_WGM01);
	CLR_BIT(TCCR0, TCCR0_WGM00);

	/*output compare mode: OC0 disconnected*/
	CLR_BIT(TCCR0,TCCR0_COM00);
	CLR_BIT(TCCR0,TCCR0_COM01);

	/*output compare value: 250*/
	OCR0 = 250u;

	/*output compare interrupt enable*/
	SET_BIT(TIMSK,TIMSK_OCIEO);

	/*PRE-scaler: division by 64*/
	TCCR0 &= PRESCALER_MASK;
	TCCR0 |= DIVISION_BY_64;
}

uint8 TIMER0_u8SetCallBack(void(*copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK ;

	if(copy_pvNotificationFunc != NULL)
	{
		/*Make the notification function global so that it can be accessed by the ISR*/
		TIMER0_pvNotificationFunc = copy_pvNotificationFunc;
	}

	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;
}

/*Timer0 compare match ISR*/
void __vector_10(void)		__attribute__((signal));
void __vector_10(void)
{
	if (TIMER0_pvNotificationFunc != NULL)
	{
		TIMER0_pvNotificationFunc();
	}

	else
	{
		/*Do nothing*/
	}
}
