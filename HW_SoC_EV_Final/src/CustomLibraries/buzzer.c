#include "buzzer.h"


volatile unsigned int *buzzer_instance = (volatile unsigned int*)BUZZER_ADDR;


void buzzer_set_La() {
    buzzer_instance[1] = 227273;
}

void buzzer_on_La() {
    buzzer_instance[0] = 113636;
}

void buzzer_off_La() {
    buzzer_instance[0] = 0;
}