#ifndef _GRAPH_H_
#define _GTAPH_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#include "../lcd/lcd.h"

typedef struct {
    void (*pdraw_circle)(LcdDevice *lcd, int x0, int y0, int radius, unsigned int color);
    void (*pdraw_rectangle)(LcdDevice *lcd, int x0, int y0, int width, int height, unsigned int color);
    void (*pdraw_line)(LcdDevice *lcd, int x0, int y0, int x1, int y1, unsigned int color);
    void (*pdraw_rotated_rectangle)(LcdDevice *lcd, int x0, int y0, int width, int height, float angle, unsigned int color);
} GraphDriver;


GraphDriver* GetGraphDriver();

// 在LCD上绘制圆形
static void draw_circle(LcdDevice *lcd, int x0, int y0, int radius, unsigned int color);

// 在LCD上绘制矩形
static void draw_rectangle(LcdDevice *lcd, int x0, int y0, int width, int height, unsigned int color);
 
// 在LCD上绘制直线 (Bresenham's line algorithm)
static void draw_line(LcdDevice *lcd, int x0, int y0, int x1, int y1, unsigned int color);
 
// 在LCD上绘制带旋转角度的矩形
static void draw_rotated_rectangle(LcdDevice *lcd, int x0, int y0, int width, int height, float angle, unsigned int color);
 


#endif