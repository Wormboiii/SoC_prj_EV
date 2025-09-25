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
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xiic.h"
#include "sleep.h"

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

    // XIic_Initialize(&iic_instance, IIC_ADDR);



    XGpio_Initialize(&bled_instance, BLED_ADDR);
    XGpio_SetDataDirection(&bled_instance, BLED_CHANNEL, 0x00);

    btn_instance[0] = 0;
    photo_INT_instance[0] = 1;


    while(1) {
        led_instance[0] = 2;

        // fnd_instance[0] = 1;
        // int i;
        // for(i=0; i<10; i++) {
        //     fnd_instance[1] = i;
        //     sleep(1);
        // }


        // if(btn_instance[1] == 0b00001) {
        //     XGpio_DiscreteWrite(&bled_instance, BLED_CHANNEL, 0x0f);
        // }
        // else if(btn_instance[1] == 0b00000) {
        //     XGpio_DiscreteWrite(&bled_instance, BLED_CHANNEL, 0xf0);
        // }

        if(photo_INT_instance[1] == 0b010) {
            XGpio_DiscreteWrite(&bled_instance, BLED_CHANNEL, 0xf0);
        }
        else if(photo_INT_instance[1] == 0b000) {
            XGpio_DiscreteWrite(&bled_instance, BLED_CHANNEL, 0x00);
        }
        
        step_instance[0] = 1;
        servo_instance[0] = 200000;
        servo_instance[1] = 2000000;

        buzzer_instance[0] = 113637;
        buzzer_instance[1] = 227273;
        // XGpio_DiscreteWrite(&bled_instance, BLED_CHANNEL, 0x0f);

        


    }

    cleanup_platform();
    return 0;
}
