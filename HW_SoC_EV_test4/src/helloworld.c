/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xiic.h"
#include "sleep.h"

#include "lcd.h"

#define BLED_ADDR       XPAR_AXI_GPIO_0_BASEADDR
#define BTN_ADDR        XPAR_CUSTOMIP_EXTERNAL_BTN_CNTR_0_BASEADDR
#define PHOTO_INT_ADDR  XPAR_CUSTOMIP_PHOTO_INT_CNTR_0_BASEADDR
#define LED_ADDR        XPAR_CUSTOMIP_EXTERNAL_LED_CNTR_0_BASEADDR
#define FND_ADDR        XPAR_CUSTOMIP_EXTERNAL_FND_CNTR_0_BASEADDR
#define STEP_ADDR       XPAR_CUSTOMIP_STEPPER_0_BASEADDR
#define SERVO_ADDR      XPAR_CUSTOMIP_PWM_0_BASEADDR
#define BUZZER_ADDR     XPAR_CUSTOMIP_PWM_1_BASEADDR

#define IIC_ADDR        XPAR_AXI_IIC_0_BASEADDR

#define BLED_CHANNEL                1

XIic    iic_instance;
XGpio   bled_instance;

volatile unsigned int *btn_instance = (volatile unsigned int*)BTN_ADDR;
volatile unsigned int *photo_INT_instance = (volatile unsigned int*)PHOTO_INT_ADDR;
volatile unsigned int *led_instance = (volatile unsigned int*)LED_ADDR;
volatile unsigned int *fnd_instance = (volatile unsigned int*)FND_ADDR;
volatile unsigned int *step_instance = (volatile unsigned int*)STEP_ADDR;
volatile unsigned int *servo_instance = (volatile unsigned int*)SERVO_ADDR;
volatile unsigned int *buzzer_instance = (volatile unsigned int*)BUZZER_ADDR;


int main() 
{
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");

    XIic_Initialize(&iic_instance, IIC_ADDR);
    XGpio_Initialize(&bled_instance, BLED_ADDR);
    XGpio_SetDataDirection(&bled_instance, BLED_CHANNEL, 0x00);

    i2cLcd_Init();

    btn_instance[0] = 0;
    photo_INT_instance[0] = 1;
    fnd_instance[0] = 1;
    servo_instance[1] = 2000000;
    buzzer_instance[1] = 227273;

    int btn_floor = 0b000;      // 리소스 점유 부분에서는 전역 변수랑 크게 다를거 없고 
                                // 대신 다른 함수 내에서 값 건드릴 수 없어서 값을 보호하는 데는 유용.


    // 전원 인가했을 때 1,2,3층 사이에 있는거 방지하기 위해 일단 무조건 내림
    while(1) {
       step_instance[0] = 2;
       if((photo_INT_instance[1] & 0b001) == 0b1) {
        step_instance[0] = 0;
        fnd_instance[1] = 1;
        moveCursor(0, 4);
        lcdString("Welcome");
        moveCursor(1, 3);
        lcdString("1st Floor");
        break;
       }
       else if(((photo_INT_instance[1] & 0b010) >> 1) == 0b1) {
        step_instance[0] = 0;
        fnd_instance[1] = 2;
        moveCursor(0, 4);
        lcdString("Welcome");
        moveCursor(1, 3);
        lcdString("2nd Floor");
        break;
       }
       else if(((photo_INT_instance[1] & 0b100) >> 2) == 0b1) {
        step_instance[0] = 0;
        fnd_instance[1] = 3;
        moveCursor(0, 4);
        lcdString("Welcome");
        moveCursor(1, 3);
        lcdString("3rd Floor");
        break;
       }


    }
    

    

    // 메인 루프문
    while(1) {

        // 버튼 누르면 몇층 버튼 눌렸는지 저장하는 부분
        if((btn_instance[1] & 0b00001) == 0b1) {
            btn_floor = btn_floor | 0b001;
        }
        else if(( (btn_instance[1] & 0b00010) >> 1 ) == 0b1) {
            btn_floor = btn_floor | 0b010;
        }
        else if(( (btn_instance[1] & 0b00100) >> 2 ) == 0b1) {
            btn_floor = btn_floor | 0b100;
        }

        // 층 감지하는 부분
        if((photo_INT_instance[1] & 0b001) == 0b1) {        // 1층일때
            fnd_instance[1] = 1;

            if((btn_floor & 0b001) == 1) {
                int i = 0;

                led_instance[0] = 3;
                step_instance[0] = 0;

                Display_clear();
                moveCursor(0, 4);
                lcdString("Welcome");
                moveCursor(1, 3);
                lcdString("1st Floor");

                buzzer_instance[0] = 113636;
                msleep(500);
                buzzer_instance[0] = 0;

                servo_instance[0] = 30000;
                // sleep(2);
                for(i=0; i<5000000; i++) {
                    msleep(50);
                    if(( (btn_instance[1] & 0b01000) >> 3 ) == 1) {
                        while(( (btn_instance[1] & 0b01000) >> 3 ) == 1){
                        }
                    }
                    else if(( (btn_instance[1] & 0b10000) >> 4 ) == 1) {
                        break;
                    }
                }
                servo_instance[0] = 240000;
                sleep(1);
            }
            btn_floor = btn_floor & 0b110;

            if(btn_floor == 0) {
                step_instance[0] = 0;
                led_instance[0] = 3;           
            }
            else {
                step_instance[0] = 1;
                led_instance[0] = 1;

                moveCursor(0, 2);
                lcdString("Please Wait");
                moveCursor(1, 3);
                lcdString("Ascending");
            }
        }

        else if(((photo_INT_instance[1] & 0b010) >> 1) == 0b1) {    // 2층일때
            fnd_instance[1] = 2;

            if(((btn_floor & 0b010) >> 1) == 1) {
                led_instance[0] = 3;
                step_instance[0] = 0;

                Display_clear();
                moveCursor(0, 4);
                lcdString("Welcome");
                moveCursor(1, 3);
                lcdString("2nd Floor");

                buzzer_instance[0] = 113636;
                msleep(500);
                buzzer_instance[0] = 0;

                servo_instance[0] = 30000;
                sleep(2);
                servo_instance[0] = 240000;
                sleep(1);
            }

            btn_floor = btn_floor & 0b101;

            if(btn_floor == 0) {
                step_instance[0] = 0;
                led_instance[0] = 3;    
            }
            else if(btn_floor == 0b001) {
                step_instance[0] = 2;
                led_instance[0] = 2;

                moveCursor(0, 2);
                lcdString("Please Wait");
                moveCursor(1, 3);
                lcdString("Descending");

                if(((btn_floor&0b100) >> 2) == 1) {
                    step_instance[0] = 2;
                    led_instance[0] = 2;
                }
            }
            else if(btn_floor == 0b100) {
                step_instance[0] = 1;
                led_instance[0] = 1;

                moveCursor(0, 2);
                lcdString("Please Wait");
                moveCursor(1, 3);
                lcdString("Ascending");

                if((btn_floor&0b001) == 1) {
                    step_instance[0] = 1;
                    led_instance[0] = 1;
                }
            }
        }

        else if(((photo_INT_instance[1] & 0b100) >> 2) == 0b1) {    // 3층일때
            fnd_instance[1] = 3;

            if(((btn_floor & 0b100) >> 2) == 1) {
                led_instance[0] = 3;
                step_instance[0] = 0;

                Display_clear();
                moveCursor(0, 4);
                lcdString("Welcome");
                moveCursor(1, 3);
                lcdString("3rd Floor");

                buzzer_instance[0] = 113636;
                msleep(500);
                buzzer_instance[0] = 0;

                servo_instance[0] = 30000;
                sleep(2);
                servo_instance[0] = 240000;
                sleep(1);
            }
            btn_floor = btn_floor & 0b011;

            if(btn_floor == 0) {
                step_instance[0] = 0;
                led_instance[0] = 3;           
            }
            else {
                step_instance[0] = 2;
                led_instance[0] = 2;

                moveCursor(0, 2);
                lcdString("Please Wait");
                moveCursor(1, 3);
                lcdString("Descending");
            }
            
        }
    }
    
    cleanup_platform();
    return 0; 
}
