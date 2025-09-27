#include "fnd.h"


volatile unsigned int *fnd_instance = (volatile unsigned int*)FND_ADDR;


void fnd_init_CC() {        // 하드웨어 캐소드 공통이면 이거 사용
    fnd_instance[0] = 1;
}

void fnd_init_CA() {        // 하드웨어 애노드 공통이면 이거 사용
    fnd_instance[0] = 0;
}

void fnd_display_num(int i) {
    fnd_instance[1] = i;
}