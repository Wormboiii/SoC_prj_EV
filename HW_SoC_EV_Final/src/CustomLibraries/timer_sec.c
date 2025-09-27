#include "timer_sec.h"


volatile unsigned int *timer_instance = (volatile unsigned int *)TIMER_ADDR;


void timer_target_sec(uint8_t i) {      // IP상에서는 7비트까지만 받음, 8비트 이상 받으면 오버플로우나서 이상한 값 들어감  
    timer_instance[1] = i;              // 최대 100초까지 셀 수 있도록 IP 설계함, 7비트 최대값인 127초까지 셀 수 있음
}

void timer_on() {
    timer_instance[0] = 1;
}

void timer_off() {
    timer_instance[0] = 0;
}