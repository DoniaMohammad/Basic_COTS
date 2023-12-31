#ifndef EXTI_CFG_H
#define EXTI_CFG_H

#include "EXTI_interface.h"

/* configure INT0 trigger source, options: 1- LOW_LEVEL
 * 										   2- ON_CHANGE
 * 									 	   3- FALLING_EDGE
 * 									 	   4- RISING_EDGE
 * */
#define EXTI_INT0_TRIG_SRC			       FALLING_EDGE

/* configure INT1 trigger source, options: 1- LOW_LEVEL
 * 										   2- ON_CHANGE
 * 									 	   3- FALLING_EDGE
 * 									 	   4- RISING_EDGE
 * */
#define EXTI_INT1_TRIG_SRC				   FALLING_EDGE

/* configure INT2 trigger source, options: 1- FALLING_EDGE
 * 									 	   2- RISING_EDGE
 * */
#define EXTI_INT2_TRIG_SRC				   FALLING_EDGE


/*Configure INT0 initial state, options: 1- ENABLED
 * 									     2- DISABLED
 * */
#define EXTI_U8INT0_INIT_STATE		ENABLED

/*Configure INT1 initial state, options: 1- ENABLED
 * 									     2- DISABLED
 * */
#define EXTI_U8INT1_INIT_STATE		ENABLED

/*Configure INT2 initial state, options: 1- ENABLED
 * 									     2- DISABLED
 * */
#define EXTI_U8INT2_INIT_STATE		ENABLED



#endif
