#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

typedef enum
{
	ANODE,
	CATHODE,
	ETA_KIT
}SSD_type_t;


typedef struct
{
	SSD_type_t SSD_TYPE;
	DIO_Port_t SSD_PORT;
	DIO_Pin_t SSD_LED_A_PIN;
	DIO_Port_t SSD_ENABLE_PORT;
	DIO_Pin_t SSD_ENABLE_PIN;
}SSD_config_t;

uint8 SSD_u8SetNumber(const SSD_config_t *copy_SSD_object,uint8 copy_u8Number);
uint8 SSD_u8Enable (const SSD_config_t* copy_SSD_object);
uint8 SSD_u8Disable(const SSD_config_t* copy_SSD_object);

#endif
