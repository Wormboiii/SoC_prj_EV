#include "step.h"


volatile unsigned int *step_instance = (volatile unsigned int*)STEP_ADDR;


void step_cw() {
    step_instance[0] = 2;
}

void step_ccw() {
    step_instance[0] = 1;
}

void step_stop() {
    step_instance[0] = 0;
}