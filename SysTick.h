#ifndef SysTick_H_
#define  SysTick_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "tm4c123gh6pm.h"



void SYSTICK_init(void);

void SYSTICK_delay_m_callback(u32 delayNms , void (*callback)(void));

void SYSTICK_delay_m (u32 delayNms );

#endif