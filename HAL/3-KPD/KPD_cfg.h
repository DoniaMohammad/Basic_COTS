#ifndef KPD_CFG_H
#define KPD_CFG_H

#define KPD_u8ROW_PORT				DIO_PORTB
#define KPD_u8R0_PIN				DIO_PIN4
#define KPD_u8R1_PIN				DIO_PIN5
#define KPD_u8R2_PIN				DIO_PIN6
#define KPD_u8R3_PIN				DIO_PIN7


#define KPD_u8COL_PORT				DIO_PORTD
#define KPD_u8C0_PIN				DIO_PIN2
#define KPD_u8C1_PIN				DIO_PIN3
#define KPD_u8C2_PIN				DIO_PIN4
#define KPD_u8C3_PIN				DIO_PIN5


#define KPD_u8Button_ARR			{{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'#','0','=','+'}}

#define KPD_u8NOPRESSED_KEY_VAL		0xff

#endif
