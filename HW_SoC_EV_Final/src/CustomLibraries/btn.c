#include "btn.h"


volatile unsigned int *btn_instance = (volatile unsigned int*)BTN_ADDR;
int btn_floor = 0b000;          // 리소스 점유 부분에서는 전역 변수랑 크게 다를거 없고 
                                // 대신 다른 함수 내에서 값 건드릴 수 없어서 값을 보호하는 데는 유용.
int btn_door = 0b00;


void btn_init_AH() {        // 하드웨어 액티브 하이일때 이거 사용
    btn_instance[0] = 1;    // 감지 시 1번 레지스터 set        
}

void btn_init_AL() {        // 하드웨어 액티브 로우일때 이거 사용
    btn_instance[0] = 0;    // 감지 시 1번 레지스터 set  
}

void btn_read() {
    if((btn_instance[1] & 0b00001) == 0b1) {
        btn_floor = btn_floor | 0b001;
    }
    if(( (btn_instance[1] & 0b00010) >> 1 ) == 0b1) {
        btn_floor = btn_floor | 0b010;
    }
    if(( (btn_instance[1] & 0b00100) >> 2 ) == 0b1) {
        btn_floor = btn_floor | 0b100;
    }

    if(( (btn_instance[1] & 0b01000) >> 3 ) == 0b1) {
        btn_door = btn_door | 0b01;
    }
    else if(( (btn_instance[1] & 0b01000) >> 3 ) == 0b0) {
        btn_door = btn_door & 0b10;
    }
    if(( (btn_instance[1] & 0b10000) >> 4 ) == 0b1) {
        btn_door = btn_door | 0b10;
    }
    else if(( (btn_instance[1] & 0b10000) >> 4 ) == 0b0) {
        btn_door = btn_door & 0b01;
    }
    
}