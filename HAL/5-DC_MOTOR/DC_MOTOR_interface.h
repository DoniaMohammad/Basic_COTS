#ifndef DCMOTOR_INTERFACE_H
#define DCMOTOR_INTERFACE_H

#define DCMOTOR_PORT	DIO_PORTD
#define DCMOTOR_PIN1	DIO_PIN0
#define DCMOTOR_PIN2	DIO_PIN1

void DCMotor_voidRotateCW (DIO_Port_t copy_DCmotor_PORT, DIO_Pin_t copy_DCmotor_PIN1, DIO_Pin_t DCmotor_PIN2);
void DCMotor_voidRotateCCW (DIO_Port_t copy_DCmotor_PORT, DIO_Pin_t copy_DCmotor_PIN1, DIO_Pin_t DCmotor_PIN2);
void DCMotor_voidStop (DIO_Port_t copy_DCmotor_PORT, DIO_Pin_t copy_DCmotor_PIN1, DIO_Pin_t DCmotor_PIN2);

#endif
