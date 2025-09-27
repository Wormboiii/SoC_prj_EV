#ifndef __fnd_h__
#define __fnd_h__

#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"



#endif


#define FND_ADDR        XPAR_CUSTOMIP_EXTERNAL_FND_CNTR_0_BASEADDR

extern volatile unsigned int *fnd_instance;


void fnd_init_CC();
void fnd_init_CA();
void fnd_display_num(int i);