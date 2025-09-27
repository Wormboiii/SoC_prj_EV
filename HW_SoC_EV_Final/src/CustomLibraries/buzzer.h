#ifndef __buzzer_h__
#define __buzzer_h__

#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"



#endif

#define BUZZER_ADDR     XPAR_CUSTOMIP_PWM_1_BASEADDR

extern volatile unsigned int *buzzer_instance;

void buzzer_set_La();
void buzzer_on_La();
void buzzer_off_La();
