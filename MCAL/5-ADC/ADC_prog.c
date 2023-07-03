#include "STD_TYPES.h"

#include "BIT_MATH.h"
#include "Err_Type.h"

#include "ADC_interface.h"
#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"

static uint16* ADC_pu16DigResult = NULL;
static void (*ADC_pvNotificationFunc)(void) = NULL;
static uint8 ADC_u8BusyFlag = IDLE;
static ADC_Chain_t* ADC_pChainData = NULL;
static uint8 ADC_u8ConversionIndex = 0u;
static uint8 ADC_u8ISRSource;

void ADC_voidInit(void)
{
	/*1- Reference selection*/
	CLR_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);

	/*2- ADC conversion result*/
#if ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error wrong ADC resolution configuration value
#endif

	/*3- check on PRE-scaler configuration setting*/
	ADCSRA &= PRESCALER_MASK;			/*clear the PRE-scaler bits*/
	ADCSRA |= ADC_u8PRESCALER;

	/*4- Enable ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}


uint8 ADC_u16StartSingleConversionSynch (ADC_Channel_t copy_u8Channel, uint16* copy_pu16DigResult)
{
	uint8 Local_u8ErrorState = OK;

	if(copy_pu16DigResult != NULL)
	{
		if (ADC_u8BusyFlag == IDLE)
		{
			uint32 Local_u32Counter = 0u;

			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*1- set the required channel*/
			ADMUX &= CHANNEL_SELECTION_MASK;			/*clear the channel selection bits*/
			ADMUX |= copy_u8Channel;

			/*2- start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*3- wait until conversion is completed or the timeout has not passed out*/
			while (((GET_BIT(ADCSRA, ADCSRA_ADIF))==0)&&(Local_u32Counter<ADC_u32TIMEOUT_COUNT))
			{
				Local_u32Counter++;
			}

			if(Local_u32Counter == ADC_u32TIMEOUT_COUNT)
			{
				/*Loop is broken because timeout has passed*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}

			else /*loop is broken because flag is raised*/
			{
				/*4- clear the conversion complete flag*/
				SET_BIT(ADCSRA, ADCSRA_ADIF);

				/*5- read the data*/
#if ADC_u8RESOLUTION == EIGHT_BITS
				*copy_pu16DigResult = (uint16)ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
				*copy_pu16DigResult = ADC;
#endif

				/*task is done, ADC is now idle*/
				ADC_u8BusyFlag = IDLE;
			}
		}

		else
		{
			Local_u8ErrorState = BUSY_ERR;
		}

	}

	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;
}

/**
 * @brief this function is used to start single channel conversion and get back with the result
 * @param copy_u8Channel: the required analogue channel to convert, choose from options @ADC_Channel_t
 * @param copy_pu16DigResult: out parameter for the digital result
 * @param copy_pvNotificationFunc
 * @return error state
 */
uint8 ADC_u16StartSingleConversionAsynch (ADC_Channel_t copy_u8Channel, uint16* copy_pu16DigResult, void(*copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if ((copy_pu16DigResult != NULL) && (copy_pvNotificationFunc != NULL))
	{
		if (ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now BUSY*/
			ADC_u8BusyFlag = BUSY;

			/*ISR source is chain conversion synchronous function*/
			ADC_u8ISRSource = SINGLE_CONV_ASYNCH;

			/*1- convert the digital result and the notification function local variables into global*/
			ADC_pu16DigResult = copy_pu16DigResult;

			ADC_pvNotificationFunc = copy_pvNotificationFunc;

			/*2- set the required channel*/
			ADMUX &= CHANNEL_SELECTION_MASK;			/*clear the channel selection bits*/
			ADMUX |= copy_u8Channel;

			/*3- start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*4- enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}

		else
		{
			Local_u8ErrorState = BUSY_ERR;
		}

	}

	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;
}

uint8 ADC_u8StartChainConversionAsynch (const ADC_Chain_t* copy_ChainData)
{
	uint8 Local_u8ErrorState = OK;

	if(copy_ChainData != NULL)
	{
		if (ADC_u8BusyFlag == IDLE)
		{
			/*task is done ADC is now BUSY*/
			ADC_u8BusyFlag = BUSY;

			/*ISR source is chain conversion asynchronous function*/
			ADC_u8ISRSource = CHAIN_CONV_ASYNCH;

			/*convert local chain data into global*/
			ADC_pChainData = copy_ChainData;

			ADC_u8ConversionIndex = 0u;

			/*Set the first channel*/
			ADMUX &= CHANNEL_SELECTION_MASK;			/*clear the channel selection bits*/
			ADMUX |= ADC_pChainData->ChannelArr[ADC_u8ConversionIndex];

			/*3- start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*4- enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}

		else
		{
			Local_u8ErrorState = NULL_PTR;
		}

		return Local_u8ErrorState;
	}
}

/*ADC conversion complete ISR*/
void __vector_16(void)		__attribute__((signal));
void __vector_16(void)
{
	if (ADC_u8ISRSource == SINGLE_CONV_ASYNCH)
	{
#if ADC_u8RESOLUTION == EIGHT_BITS
		*ADC_pu16DigResult = (uint16)ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
		*ADC_pu16DigResult = ADC;
#endif

		/*ADC interrupt disable*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);

		/*ADC is now IDLE*/
		ADC_u8BusyFlag = IDLE;

		/*Invoke the callback notification function*/
		if (ADC_pvNotificationFunc != NULL)
		{
			ADC_pvNotificationFunc();
		}
		else
		{
			/*do nothing*/
		}
	}

	else if (ADC_u8ISRSource == CHAIN_CONV_ASYNCH)
	{
#if ADC_u8RESOLUTION == EIGHT_BITS
		ADC_pChainData->ResultArr[ADC_u8ConversionIndex] = (uint16)ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
		ADC_pChainData->ResultArr[ADC_u8ConversionIndex] = ADC;
#endif

		/*increment the index*/
		ADC_u8ConversionIndex ++;

		if (ADC_u8ConversionIndex == ADC_pChainData -> ConversionsNum)
		{
			/*chain is finished*/
			/*ADC is now Idle*/
			ADC_u8BusyFlag = IDLE;

			/*Disable ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);

			/*Invoke the callback notification*/
			if (ADC_pChainData->NotificationFunc != NULL)
			{
				ADC_pChainData->NotificationFunc();
			}

			else
			{
				/*Do nothing*/
			}
		}

		else

		{
			/*chain is not finished yet*/
			/*Set the next channel*/
			ADMUX &= CHANNEL_SELECTION_MASK;			/*clear the channel selection bits*/
			ADMUX |= ADC_pChainData->ChannelArr[ADC_u8ConversionIndex];

			/*start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);
		}
	}

}
