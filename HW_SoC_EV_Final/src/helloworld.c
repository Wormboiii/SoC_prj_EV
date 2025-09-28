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
#include "btn.h"
#include "photoINT.h"
#include "servo.h"
#include "step.h"
#include "buzzer.h"
#include "led.h"
#include "timer_sec.h"
#include "fnd.h"


#define IIC_ADDR        XPAR_AXI_IIC_0_BASEADDR
XIic    iic_instance;


int main() 
{
    init_platform();

    XIic_Initialize(&iic_instance, IIC_ADDR);

    i2cLcd_Init();
    btn_init_AL();
    photoINT_init_AH();
    fnd_init_CC();
    servo_init();
    buzzer_set_La();


    // 전원 인가했을 때 1,2,3층 사이에 있는거 방지하기 위해 일단 무조건 내림
    while(1) {
       step_cw();

       if((photo_INT_instance[1] & 0b001) == 0b1) {
        step_stop();
        fnd_display_num(1);
        moveCursor(0, 4);
        lcdString("Welcome");
        moveCursor(1, 3);
        lcdString("1st Floor");
        break;
       }

       else if(((photo_INT_instance[1] & 0b010) >> 1) == 0b1) {
        step_stop();
        fnd_display_num(2);
        moveCursor(0, 4);
        lcdString("Welcome");
        moveCursor(1, 3);
        lcdString("2nd Floor");
        break;
       }

       else if(((photo_INT_instance[1] & 0b100) >> 2) == 0b1) {
        step_stop();
        fnd_display_num(3);
        moveCursor(0, 4);
        lcdString("Welcome");
        moveCursor(1, 3);
        lcdString("3rd Floor");
        break;
       }
    }
    


    // 메인 루프문
    while(1) {

        btn_read();

        // -------------------------------------------------------1층일때--------------------------------------------------------------------
        if((photo_INT_instance[1] & 0b001) == 0b1) { 
            fnd_display_num(1);                             // FND에 1 표시

            if((btn_floor & 0b001) == 1) {                  // 포토인터럽트 1층 감지 시

                // LED 끄고 스텝모터 멈춤
                led_on();                  
                step_stop();

                // LCD에 1층 표시
                Display_clear();
                moveCursor(0, 4);
                lcdString("Welcome");
                moveCursor(1, 3);
                lcdString("1st Floor");

                // 0.5초동안 버저 킴(이때동안 다른 입력값 못받음)
                buzzer_on_La();
                msleep(500);
                buzzer_off_La();

                // 서보모터 시계방향으로 돌려서(0도) 문 엶
                servo_cw();
                
                // 문 열린 후 닫힐 때 까지 기다리는 부분
                timer_target_sec(3);                                            // 3초동안 열려 있을거임
                timer_on();                                                     // 이때부터 타이머 카운팅 시작

                while(timer_instance[2] == 0) {                                 // 타이머 플래그 세워지기 전까지 이 구문에 묶여있음
                    btn_read();                                                 // 문이 열려있을 때도 버튼은 감지하기

                    if(btn_door == 0b01) {                                      // 열림버튼 눌렸으면
                        while(btn_door == 1) {                                  // 버튼에서 손 땔 떼 까지 무한대기
                            btn_read();                                         // 다른 버튼값은 읽을거임
                        }
                    }
                    else if((btn_door >> 1) == 1) {                             // 닫힘버튼 눌렸으면
                        break;                                                  // 3초 안기다리고 while문 나감
                    }
                }
                timer_off();                                                    // 타이머 카운팅 종료
                
                // 서보모터 반시계방향으로 돌려서(180도) 문 닫음 
                servo_ccw();
                
                // 문 다 닫힐때까지 1초 대기하는 부분(문 다 안닫혔는데 출발하는거 방지)
                timer_target_sec(1);                                            // 닫힐때까지 1초동안 기다릴거임
                timer_on();                                                     // 타이머 카운팅 시작
                while(timer_instance[2] == 0) {                                 // 타이머 플래그 세워지기 전까지 이 구문에 묶여있음
                    btn_read();                                                 // 버튼 감지
                    
                    if(btn_door == 0b01) {                                      // 닫히는 도중 열림버튼 눌렸으면
                        while(btn_door == 1) {                                  // 버튼에서 손 땔떼까지 무한대기
                            servo_cw();                                         // 서보모터 시계방향으로 돌려서 다시 문 엶
                            btn_read();
                        }
                        timer_off();                                            // 열림버튼에서 손 떼면(혹은 열림버튼 안눌렀으면)
                        servo_ccw();                                            // 타이머 카운팅 종료 후 서보모터 돌려서 문 닫음
                        
                        timer_on();                                             // 문 한번 다시 열었으니까 닫힐 때 1초 대기 또 해야함
                        while(timer_instance[2] == 0);                          // 1초동안 기다림
                    }
                }
                timer_off();                                                    // while문 빠져나오면 타이머 카운팅 종료
            }

            btn_floor = btn_floor & 0b110;                                      // 1층 대기열 리셋해줌

            if(btn_floor == 0) {                                                // 모든 층 대기열이 0이면(갈곳이 없으면)
                step_stop();                                                    // 스텝모터 정지    
                led_on();                                                       // LED 다 킴

                if(btn_door == 0b01) {                                          // 열림버튼 눌렸으면 
                    servo_cw();                                                 // 문 열어줌

                    timer_target_sec(3);                                        // 닫히기 전까지 3초 대기
                    timer_on();                                                 // 타이머 카운팅 시작
                    while(timer_instance[2] == 0) {                             // 타이머 플래그 뜰 때까지 무한대기
                        btn_read();                                             // 버튼 값 읽으면서
                        if(btn_door == 0b10) {                                  
                            break;                                              // 닫힘버튼 누르면 3초 대기 안하고 바로 빠져나옴
                        }
                    }
                    timer_off();                                                // 카운팅 종료
                    servo_ccw();                                                // 문 닫기
                }           
            }
            else {                                                              // 2층이나 3층 대기열이 있으면
                step_ccw();                                                     // 스텝모터 감아올리기
                led_LS();                                                       // 올라가는 방향으로 LED 시프트

                // LCD에 올라간다고 표시
                moveCursor(0, 2);                               
                lcdString("Please Wait");
                moveCursor(1, 3);
                lcdString("Ascending");
            }
        }
        //---------------------------------------------------------1층 끝--------------------------------------------------------------------



        //---------------------------------------------------------2층일때--------------------------------------------------------------------
        else if(((photo_INT_instance[1] & 0b010) >> 1) == 0b1) { 
            fnd_display_num(2);

            if(((btn_floor & 0b010) >> 1) == 1) {
                led_on();
                step_stop();

                Display_clear();
                moveCursor(0, 4);
                lcdString("Welcome");
                moveCursor(1, 3);
                lcdString("2nd Floor");

                buzzer_on_La();
                msleep(500);
                buzzer_off_La();

                servo_cw();
                
                timer_target_sec(3);
                timer_on();
                while(timer_instance[2] == 0) {
                    btn_read();
                    
                    if(btn_door == 0b01) {
                        while(btn_door == 1) {
                            btn_read();
                        }
                    }
                    else if((btn_door >> 1) == 1) {
                        break;
                    }
                }
                timer_off();

                servo_ccw();
                
                timer_target_sec(1);
                timer_on();
                while(timer_instance[2] == 0) {
                    btn_read();
                    
                    if(btn_door == 0b01) {
                        while(btn_door == 1) {
                            servo_cw();
                            btn_read();
                        }
                        timer_off();
                        servo_ccw();
                        
                        timer_on();
                        while(timer_instance[2] == 0);
                    }
                }
                timer_off();
            }

            btn_floor = btn_floor & 0b101;

            if(btn_floor == 0) {
                step_stop();
                led_on();
                
                if(btn_door == 0b01) {                                          // 열림버튼 눌렸으면 
                    servo_cw();                                                 // 문 열어줌

                    timer_target_sec(3);                                        // 닫히기 전까지 3초 대기
                    timer_on();                                                 // 타이머 카운팅 시작
                    while(timer_instance[2] == 0) {                             // 타이머 플래그 뜰 때까지 무한대기
                        btn_read();                                             // 버튼 값 읽으면서
                        if(btn_door == 0b10) {                                  
                            break;                                              // 닫힘버튼 누르면 3초 대기 안하고 바로 빠져나옴
                        }
                    }
                    timer_off();                                                // 카운팅 종료
                    servo_ccw();                                                // 문 닫기
                }      
            }
            else if(btn_floor == 0b001) {                   // 1층 대기열이 있으면
                step_cw();                                  // 일단 밑으로 내려감
                led_RS();

                moveCursor(0, 2);
                lcdString("Please Wait");
                moveCursor(1, 3);
                lcdString("Descending");

                if(((btn_floor&0b100) >> 2) == 1) {         // 3층 대기열도 있으면
                    step_cw();                              // 그래도 일단 내려감
                    led_RS();                               // 1층 다 내려가면 1층 로직으로 인해 알아서 3층으로 올라갈거임
                }
            }
            else if(btn_floor == 0b100) {                   // 1층 대기열이 없고 3층 대기열이 있으면 
                step_ccw();                                 // 일단 위로 올라감
                led_LS();

                moveCursor(0, 2);
                lcdString("Please Wait");
                moveCursor(1, 3);
                lcdString("Ascending");

                if((btn_floor&0b001) == 1) {                // 1층 대기열이 추가되면
                    step_ccw();                             // 그래도 일단 올라감
                    led_LS();                               // 3층 다 올라가면 3층 로직으로 인해 알아서 1층으로 내려갈거임
                }
            }
            // else if(btn_floor == 0b101) {                   // 1층 3층 대기열 동시에 잡히면(while문 안에서 처리된 경우) 
            //     step_ccw();                                 // 일단 위로 올라감
            //     led_LS();

            //     moveCursor(0, 2);
            //     lcdString("Please Wait");
            //     moveCursor(1, 3);
            //     lcdString("Ascending");

            //     if((btn_floor&0b001) == 1) {                // 1층 대기열이 추가되면
            //         step_ccw();                             // 그래도 일단 올라감
            //         led_LS();                               // 3층 다 올라가면 3층 로직으로 인해 알아서 1층으로 내려갈거임
            //     }
            // }
        }
        //--------------------------------------------------------2층일때 끝------------------------------------------------------------------



        //--------------------------------------------------------3층일때--------------------------------------------------------------------
        else if(((photo_INT_instance[1] & 0b100) >> 2) == 0b1) {
            fnd_display_num(3);

            if(((btn_floor & 0b100) >> 2) == 1) {
                led_on();
                step_stop();

                Display_clear();
                moveCursor(0, 4);
                lcdString("Welcome");
                moveCursor(1, 3);
                lcdString("3rd Floor");

                buzzer_on_La();
                msleep(500);
                buzzer_off_La();

                servo_cw();
                
                timer_target_sec(3);
                timer_on();
                while(timer_instance[2] == 0) {
                    btn_read();
                    
                    if(btn_door == 0b01) {
                        while(btn_door == 1) {
                            btn_read();
                        }
                    }
                    else if((btn_door >> 1) == 1) {
                        break;
                    }
                }
                timer_off();
                
                servo_ccw();
                
                timer_target_sec(1);
                timer_on();
                while(timer_instance[2] == 0) {
                    btn_read();
                    
                    if(btn_door == 0b01) {
                        while(btn_door == 1) {
                            servo_cw();
                            btn_read();
                        }
                        timer_off();
                        servo_ccw();
                        
                        timer_on();
                        while(timer_instance[2] == 0);
                    }
                }
                timer_off();
            }
            btn_floor = btn_floor & 0b011;

            if(btn_floor == 0) {
                step_stop();
                led_on();

                if(btn_door == 0b01) {                                          // 열림버튼 눌렸으면 
                    servo_cw();                                                 // 문 열어줌

                    timer_target_sec(3);                                        // 닫히기 전까지 3초 대기
                    timer_on();                                                 // 타이머 카운팅 시작
                    while(timer_instance[2] == 0) {                             // 타이머 플래그 뜰 때까지 무한대기
                        btn_read();                                             // 버튼 값 읽으면서
                        if(btn_door == 0b10) {                                  
                            break;                                              // 닫힘버튼 누르면 3초 대기 안하고 바로 빠져나옴
                        }
                    }
                    timer_off();                                                // 카운팅 종료
                    servo_ccw();                                                // 문 닫기
                }              
            }
            else {
                step_cw();
                led_RS();

                moveCursor(0, 2);
                lcdString("Please Wait");
                moveCursor(1, 3);
                lcdString("Descending");
            }
            
        }
    }
    //-----------------------------------------------------3층일때 끝--------------------------------------------------------------
    
    cleanup_platform();
    return 0; 
}