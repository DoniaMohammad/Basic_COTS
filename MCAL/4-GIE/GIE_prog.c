#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_reg.h"

void GIE_void_EnableGlobal (void)
{
	__asm volatile ("SEI");
	/*SET_BIT(SREG,SREG_I);*/
}

void GIE_void_DisableGlobal (void)
{
	__asm volatile ("CLI");
	/*CLR_BIT(SREG,SREG_I);*/
}