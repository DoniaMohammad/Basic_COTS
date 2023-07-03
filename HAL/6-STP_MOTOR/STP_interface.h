#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

#define ClockWise				0
#define CounterClockWise		1

typedef struct
{
	DIO_Port_t STEPPER_PORT;
	DIO_Pin_t BLUE_PIN;
	DIO_Pin_t PINK_PIN;
	DIO_Pin_t YELLOW_PIN;
	DIO_Pin_t ORANGE_PIN;
}STEPPER_cfg_t;

uint8 Stepper_u8Rotate (const STEPPER_cfg_t* stepper_object, uint16 copy_u16Angle, uint8 copy_u8Direction);

#endif
