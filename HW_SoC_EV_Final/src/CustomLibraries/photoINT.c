#include "photoINT.h"


volatile unsigned int *photo_INT_instance = (volatile unsigned int*)PHOTO_INT_ADDR;


void photoINT_init_AH() {           // 하드웨어 액티브 하이일때 이거 사용
    photo_INT_instance[0] = 1;      // 감지 시 1번 레지스터 set
}

void photoINT_init_AL() {           // 하드웨어 액티브 로우일때 이거 사용
    photo_INT_instance[0] = 1;      // 감자 시 1번 레지스터 set
}