#ifndef __timer_sec_h__
#define __timer_sec_h__

#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"



#endif

#define TIMER_ADDR      XPAR_CUSTOMIP_TIMER_SEC_0_BASEADDR

extern volatile unsigned int *timer_instance;

void timer_target_sec(uint8_t i);
void timer_on();
void timer_off();