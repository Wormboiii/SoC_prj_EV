#ifndef __led_h__
#define __led_h__

#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"



#endif

#define LED_ADDR        XPAR_CUSTOMIP_EXTERNAL_LED_CNTR_0_BASEADDR

extern volatile unsigned int *led_instance;

void led_on();
void led_off();
void led_LS();
void led_RS();