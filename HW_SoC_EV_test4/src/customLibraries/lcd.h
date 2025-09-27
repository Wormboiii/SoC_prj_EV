#ifndef __lcd_h__
#define __lcd_h__

#include <stdio.h>
#include <stdint.h>
#include "xiic.h"
#include "sleep.h"

#endif


extern XIic    iic_instance;

void lcdCommand(uint8_t command);
void lcdData(uint8_t data);
void i2cLcd_Init();
void lcdString(char *str);
void moveCursor(uint8_t row, uint8_t col);
void Display_clear();