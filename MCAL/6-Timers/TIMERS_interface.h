#ifndef TIMERS_INTERFACE_H
#define TIMERS_INTERFACE_H

void TIMER0_voidInit(void);
uint8 TIMER0_u8SetCallBack(void(*copy_pvNotificationFunc)(void));
uint8 TIMER1_u8SetCallBack(void(*copy_pvNotificationFunc)(void));

#endif
