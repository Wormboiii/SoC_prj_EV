#ifndef __btn_h__
#define __btn_h__

#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"



#endif


#define BTN_ADDR        XPAR_CUSTOMIP_EXTERNAL_BTN_CNTR_0_BASEADDR


extern volatile unsigned int *btn_instance;
extern int btn_floor;
extern int btn_door;



void btn_init_AH();
void btn_init_AL();
void btn_read();