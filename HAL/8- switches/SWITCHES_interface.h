#ifndef SWITCHES_INTERFACE_H
#define SWITCHES_INTERFACE_H

typedef enum
{
	PULL_UP=1,
	PULL_DOWN
}PULL_TYPE;

typedef enum
{
	PRESSED=0,
	RELEASED
}Switch_State_t;

typedef struct 
{
	DIO_Port_t	SwitchPort;
	DIO_Pin_t	SwitchPin;
	PULL_TYPE	switchPullType;
}Switch_cfg_t;


uint8 Switch_u8GetState (const Switch_cfg_t* copy_pu8Switch, uint8* copy_pu8State);
#endif
