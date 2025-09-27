#ifndef __photoINT_h__
#define __photoINT_h__

#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"



#endif


#define PHOTO_INT_ADDR  XPAR_CUSTOMIP_PHOTO_INT_CNTR_0_BASEADDR

extern volatile unsigned int *photo_INT_instance;


void photoINT_init_AH();
void photoINT_init_AL();