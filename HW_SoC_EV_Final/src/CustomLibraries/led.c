#include "led.h"


volatile unsigned int *led_instance = (volatile unsigned int*)LED_ADDR;


void led_on() {
    led_instance[0] = 3;
}

void led_off() {
    led_instance[0] = 0;
}

void led_LS() {
    led_instance[0] = 1;
}

void led_RS() {
    led_instance[0] = 2;
}