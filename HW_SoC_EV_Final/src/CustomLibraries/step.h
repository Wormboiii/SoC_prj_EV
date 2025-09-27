#ifndef __step_h__
#define __step_h__

#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"



#endif


#define STEP_ADDR       XPAR_CUSTOMIP_STEPPER_0_BASEADDR


extern volatile unsigned int *step_instance;


void step_cw();
void step_ccw();
void step_stop();