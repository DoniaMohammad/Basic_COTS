#ifndef DIO_REG_H_
#define DIO_REG_H_


#define PORTA		 *((volatile uint8*)0X3B)
#define DDRA		 *((volatile uint8*)0X3A)
#define PINA		 *((volatile uint8*)0X39)

#define PORTB		 *((volatile uint8*)0X38)
#define DDRB		 *((volatile uint8*)0X37)
#define PINB		 *((volatile uint8*)0X36)

#define PORTC		 *((volatile uint8*)0X35)
#define DDRC		 *((volatile uint8*)0X34)
#define PINC		 *((volatile uint8*)0X33)

#define PORTD		 *((volatile uint8*)0X32)
#define DDRD		 *((volatile uint8*)0X31)
#define PIND		 *((volatile uint8*)0X30)


#endif