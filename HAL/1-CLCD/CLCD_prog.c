#include "STD_TYPES.h"
#include <util/delay.h>
#include "BIT_MATH.h"
#include "CLCD_cfg.h"
#include "Err_Type.h"

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_priv.h"

/*private function for the 4 bits mode*/
static void voidSetHalfDataPort (uint8 copy_u8FourBitData)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4_PIN,GET_BIT(copy_u8FourBitData,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5_PIN,GET_BIT(copy_u8FourBitData,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6_PIN,GET_BIT(copy_u8FourBitData,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7_PIN,GET_BIT(copy_u8FourBitData,3));
}


/*private function to send enable pulse*/
static void voidSendEnablePulse (void)
{
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_PIN_LOW);
}

void CLCD_voidSendCommand (uint8 copy_u8Command)
{
	/*1- Set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_LOW);

	/*2- Set RW pin to low for write*/
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif

	/*3- Send the command*/
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,copy_u8Command);

	/*4- Send Enable pulse*/
	voidSendEnablePulse();

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
	/*send the four most significant bits*/
	voidSetHalfDataPort(copy_u8Command >> 4u);

	/*send enable pulse*/
	voidSendEnablePulse();

	/*send the four least significant bits*/
	voidSetHalfDataPort(copy_u8Command);

	/*send enable pulse*/
	voidSendEnablePulse();
#endif
}

void CLCD_voidSendData (uint8 copy_u8data)
{
	/*1- Set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_HIGH);

	/*2- Set RW pin to low for write*/
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif

	/*3- Send the command*/
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,copy_u8data);

	/*4- Send Enable pulse*/
	voidSendEnablePulse();

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
	/*send the four most significant bits*/
	voidSetHalfDataPort(copy_u8data >> 4u);

	/*send enable pulse*/
	voidSendEnablePulse();

	/*send the four least significant bits*/
	voidSetHalfDataPort(copy_u8data);

	/*send enable pulse*/
	voidSendEnablePulse();
#endif
}

void CLCD_voidInit (void)
{
	/*1- wait for more than 30ms after power on*/
	_delay_ms(40);

	/*2- function set command: 2 lines, font size: 5x7*/
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	CLCD_voidSendCommand(0b00111000);

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b1000);
	voidSendEnablePulse();
#endif

	/*3-  Display ON/OFF control command: Display on, cursor off, blink cursor off*/
	CLCD_voidSendCommand(0b00001100);

	/*4- Display clear command*/
	CLCD_voidSendCommand(0b00000001);
}

void CLCD_voidSendString(uint8* copy_u8string)
{
	uint8 Local_u8StringCounter;
	while (copy_u8string[Local_u8StringCounter]!='\0')
	{
		CLCD_voidSendData(copy_u8string[Local_u8StringCounter]);
		Local_u8StringCounter++;
	}
}

void CLCD_voidSendNumber(sint32 copy_s32number)
{
	uint8 Local_u8Digit , Local_u8NumArray[10] , Local_u8Iterrator=0;
	sint8  Local_s8Counter;

	/*Zero*/
	if (copy_s32number == 0)
	{
		CLCD_voidSendData('0');
	}

	/*negative number*/
	else if (copy_s32number<0)
	{
		/*1- Display negative sign*/
		CLCD_voidSendData('-');

		/*2- change number to positive*/
		copy_s32number = copy_s32number * -1;
	}

	/*Positive number*/
	while (copy_s32number != 0)
	{
		/*get each digit*/
		Local_u8Digit = copy_s32number%10;

		/*remove the last digit*/
		copy_s32number = copy_s32number/10;

		/*save the digit in the array*/
		Local_u8NumArray[Local_u8Iterrator] = Local_u8Digit;

		/*increment the iterator*/
		Local_u8Iterrator++;
	}

	/*send the array in a reversed order to the CLCD*/
	for (Local_s8Counter = Local_u8Iterrator-1 ; Local_s8Counter>=0 ; Local_s8Counter--)
	{
		CLCD_voidSendData('0'+Local_u8NumArray[Local_s8Counter]);
	}
}

void CLCD_voidGoToXY(uint8 copy_u8XPos, uint8 copy_u8YPos)
{
	uint8 Local_u8DDRamAdd = (copy_u8YPos*0x40)+copy_u8XPos;

	/*
	 * if (copy_u8YPos == 0u)
	 * {
	 * 	Local_u8DDRamAdd = copy_u8XPos;
	 * }
	 *
	 * else
	 * {
	 * 	Local_u8DDRamAdd = 0x40 + copy_u8XPos ;
	 * 	}
	 *
	 * 	*/

	/*Set bit 7 for setting DDRAM address command*/
	SET_BIT(Local_u8DDRamAdd,7u);

	/*send the setting DDRAM address command*/
	CLCD_voidSendCommand(Local_u8DDRamAdd);
}

uint8 CLCD_u8WriteSpecialCharacter(uint8 copy_PatternNumber, uint8 copy_pu8PatternArray[], uint8 copy_u8XPos, uint8 copy_u8YPos)
{
	uint8 Local_u8ErrorStatus = OK;

	if (copy_pu8PatternArray != NULL)
	{
		/*1- calculate CGRAM address*/
		uint8 Local_u8CGRAMAdd = copy_PatternNumber * 8u;
		uint8 Local_u8Iterator;

		/*2- set bit 6 for setting CGRAM address command*/
		SET_BIT(Local_u8CGRAMAdd,6u);

		/*3- set CGRAM address*/
		CLCD_voidSendCommand(Local_u8CGRAMAdd);

		/*4- write the pattern inside CGRAM*/
		for (Local_u8Iterator=0 ; Local_u8Iterator<8 ; Local_u8Iterator++)
		{
			CLCD_voidSendData(copy_pu8PatternArray[Local_u8Iterator]);
		}

		/*5- Display the pattern on LCD
		 * return control to DDRAM -> SET DDRAM ADDRESS*/
		CLCD_voidGoToXY(copy_u8XPos,copy_u8YPos);

		/*6- write in DDRAM the corresponding value of CGRAM address -> pattern nnumber*/
		CLCD_voidSendData(copy_PatternNumber);
	}

	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}
