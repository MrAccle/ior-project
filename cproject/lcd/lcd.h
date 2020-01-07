#ifndef __LCD_H__
#define __LCD_H__
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "lcd_var.h"

#define LCD_WIDTH 800
#define LCD_HEIGH 480
#define LCD_SHOW_BUFFER (LCD_WIDTH*LCD_HEIGH*4)
#define A_LEFT_TOP_Y 50 //A值的左上角Y坐标 以下类推
#define B_LEFT_TOP_Y 200
#define V1_LEFT_TOP_X 350*50*4
#define V2_LEFT_TOP_X 375
#define V3_LEFT_TOP_X 400
#define V4_LEFT_TOP_X 425
#define V5_LEFT_TOP_X 450

void initLcd();
void changeValueA(char* val);
void changeValueB(char* val);

#endif