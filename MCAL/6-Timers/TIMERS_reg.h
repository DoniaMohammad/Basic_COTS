#ifndef TIMERS_REG_H
#define TIMERS_REG_H

#define OCR0			*((volatile uint8*)0x5C)	/*output compare match register*/

#define TIMSK			*((volatile uint8*)0x59)	/*Timer mask register*/
#define TIMSK_TOIE0		0u							/*Timer 0 overflow interrupt enable*/
#define TIMSK_OCIEO		1u							/*Timer 0 compare match interrupt enable*/

#define TCCR0			*((volatile uint8*)0x53) 	/*Timer counter control register 0*/
#define TCCR0_COM00		4u							/*Compare match output mode bit 0*/
#define TCCR0_COM01		5u							/*Compare match output mode bit 1*/
#define TCCR0_WGM00		6u							/*Waveform generation mode bit 0*/
#define TCCR0_WGM01		3u							/*Waveform generation mode bit 1*/

#define TCNT0			*((volatile uint8*)0x52) 	/*Timer counter 0 register*/

#define TCCR1A			*((volatile uint8*)0x4F) 	/*Timer 1 control register A*/
#define TCCR1A_COM1A0	6u							/*Channel 1A compare match output mode bit0*/
#define TCCR1A_COM1A1	7u							/*Channel 1A compare match output mode bit1*/
#define TCCR1A_WGM0		0u							/*Waveform generation mode bit 0*/
#define TCCR1A_WGM1		1u							/*Waveform generation mode bit 1*/

#define TCCR1B			*((volatile uint8*)0x4E) 	/*Timer 1 control register B*/
#define TCCR1B_WGM13	4u							/*Waveform generation mode bit 3*/
#define TCCR1B_WGM12	3u							/*Waveform generation mode bit 2*/
#define TCCR1B_CS12		2u							/*PRE-scaler bit 2*/
#define TCCR1B_CS11		1u							/*PRE-scaler bit 1*/
#define TCCR1B_CS10		0u							/*PRE-scaler bit 0*/

#endif
