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
#include "xintc.h"
#include "xil_exception.h"
#include "sleep.h"

#define BLED_ADDR       XPAR_AXI_GPIO_0_BASEADDR
#define BTN_ADDR        XPAR_CUSTOMIP_BUTTON_0_BASEADDR
#define PHOTO_INT_ADDR  XPAR_CUSTOMIP_PHOTOINT_0_BASEADDR
#define LED_ADDR        XPAR_CUSTOMIP_LED_0_BASEADDR
#define FND_ADDR        XPAR_CUSTOMIP_FND_0_BASEADDR
#define STEP_ADDR       XPAR_CUSTOMIP_STEPPER_0_BASEADDR
#define SERVO_ADDR      XPAR_CUSTOMIP_PWM_0_BASEADDR
#define BUZZER_ADDR     XPAR_CUSTOMIP_PWM_1_BASEADDR

#define IIC_ADDR        XPAR_AXI_IIC_0_BASEADDR
#define INTC_ADDR       XPAR_XINTC_0_BASEADDR

#define BTN_1F_CHANNEL              0
#define BTN_2F_CHANNEL              1
#define BTN_3F_CHANNEL              2
#define BTN_OPEN_PUSH_CHANNEL       3
#define BTN_OPEN_RELEASE_CHANNEL    4
#define BTN_CLOSE_PUSH_CHANNEL      5

#define PHOTO_INT_1_CHANNEL         6
#define PHOTO_INT_2_CHANNEL         7
#define PHOTO_INT_3_CHANNEL         8

#define BLED_CHANNEL                1

XIic    iic_instance;
XIntc   intc_instance;
XGpio   bled_instance;

volatile unsigned int *btn_instance = (volatile unsigned int*)BTN_ADDR;
volatile unsigned int *photo_INT_instance = (volatile unsigned int*)PHOTO_INT_ADDR;
volatile unsigned int *led_instance = (volatile unsigned int*)LED_ADDR;
volatile unsigned int *fnd_instance = (volatile unsigned int*)FND_ADDR;
volatile unsigned int *step_instance = (volatile unsigned int*)STEP_ADDR;
volatile unsigned int *servo_instance = (volatile unsigned int*)SERVO_ADDR;
volatile unsigned int *buzzer_instance = (volatile unsigned int*)BUZZER_ADDR;


void BTN_ISR(void *CallBackRef) {

}


int main() 
{
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");

    // XIic_Initialize(&iic_instance, IIC_ADDR);
    XIntc_Initialize(&intc_instance, INTC_ADDR);

    XIntc_Connect(&intc_instance, BTN_1F_CHANNEL, (XInterruptHandler)BTN_ISR, (void *)&btn_instance);
    XIntc_Connect(&intc_instance, BTN_2F_CHANNEL, (XInterruptHandler)BTN_ISR, (void *)&btn_instance);
    XIntc_Connect(&intc_instance, BTN_3F_CHANNEL, (XInterruptHandler)BTN_ISR, (void *)&btn_instance);
    
    XIntc_Enable(&intc_instance, BTN_1F_CHANNEL);
    XIntc_Enable(&intc_instance, BTN_2F_CHANNEL);
    XIntc_Enable(&intc_instance, BTN_3F_CHANNEL);
    XIntc_Start(&intc_instance, XIN_REAL_MODE);

    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, &intc_instance);
    Xil_ExceptionEnable();


    XGpio_Initialize(&bled_instance, BLED_ADDR);
    XGpio_SetDataDirection(&bled_instance, BLED_CHANNEL, 0x00);
    
    while(1) {
        // led_instance[0] = 3;
        // fnd_instance[0] = 5;
        // step_instance[0] = 0b100;
        servo_instance[0] = 200000;
        servo_instance[1] = 2000000;

        buzzer_instance[0] = 113637;
        buzzer_instance[1] = 227273;

    }

    cleanup_platform();
    return 0;
}
