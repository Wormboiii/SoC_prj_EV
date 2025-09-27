#include "servo.h"


volatile unsigned int *servo_instance = (volatile unsigned int*)SERVO_ADDR;


void servo_init() {
    servo_instance[1] = 2000000;
}

void servo_cw() {
    servo_instance[0] = 30000;
}

void servo_ccw() {
    servo_instance[0] = 240000;
}