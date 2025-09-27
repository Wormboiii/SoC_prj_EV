#ifndef __servo_h__
#define __servo_h__

#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"



#endif


#define SERVO_ADDR      XPAR_CUSTOMIP_PWM_0_BASEADDR

extern volatile unsigned int *servo_instance;


void servo_init();
void servo_cw();
void servo_ccw();