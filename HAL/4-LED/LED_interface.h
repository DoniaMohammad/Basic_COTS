#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H


typedef enum
{
	ACTIVE_LOW,
	ACTIVE_HIGH
}LED_activity_t;

typedef struct
{
	DIO_Port_t LED_PORT;
	DIO_Pin_t LED_PIN;
	LED_activity_t ACTIVITY_TYPE;
}LED_config_t;

void LED_voidSetON (const LED_config_t* copy_LEDObject);
void LED_voidSetOFF (const LED_config_t* copy_LEDObject);
void LED_voidToggle (const LED_config_t* copy_LEDObject);



#endif
