#ifndef EXTI_REG_H
#define EXTI_REG_H

#define MCUCR		 	*((volatile uint8*)0X55) /*MCU Ctrl register*/
#define MCUCR_ISC_00	0u						 /*Int. Sense Ctrl 0 bit 0*/
#define MCUCR_ISC_01	1u						 /*Int. sense Ctrl 1 bit 1*/
#define MCUCR_ISC_10	2u						 /*Int. Sense Ctrl 1 bit 0*/
#define MCUCR_ISC_11	3u						 /*Int. Sense Ctrl 1 bit 1*/

#define GICR		 	*((volatile uint8*)0X5B) /*General Int. Ctrl register*/
#define GICR_INT1		7u						 /*Int. 1*/
#define GICR_INT0		6u						 /*Int. 0*/
#define GICR_INT2		5u						 /*Int. 2*/

#define MCUCSR			*((volatile uint8*)0x54) /*MCU ctrl and status register*/
#define MCUCSR_ISC2		6u 						 /*Int. Sense Ctrl 2*/

#endif
