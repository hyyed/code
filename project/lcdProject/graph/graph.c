
#include "graph.h"





GraphDriver *GetGraphDriver() {
    static GraphDriver graphDriver;
    graphDriver.pdraw_circle = draw_circle;
    graphDriver.pdraw_rectangle = draw_rectangle;
    graphDriver.pdraw_line = draw_line;
    graphDriver.pdraw_rotated_rectangle = draw_rotated_rectangle;
    return &graphDriver;
}



// 在LCD上绘制圆形
void draw_circle(LcdDevice *lcd, int x0, int y0, int radius, unsigned int color) {
    int x = radius;
    int y = 0;
    int err = 0;
    printf("圆形\n");
    int i=0;
    while (x >= y) {
        lcd->mptr[(y0 + y) * lcd->w + (x0 + x)] = color;
        lcd->mptr[(y0 + y) * lcd->w + (x0 - x)] = color;
        lcd->mptr[(y0 - y) * lcd->w + (x0 + x)] = color;
        lcd->mptr[(y0 - y) * lcd->w + (x0 - x)] = color;
        lcd->mptr[(y0 + x) * lcd->w + (x0 + y)] = color;
        lcd->mptr[(y0 + x) * lcd->w + (x0 - y)] = color;
        lcd->mptr[(y0 - x) * lcd->w + (x0 + y)] = color;
        lcd->mptr[(y0 - x) * lcd->w + (x0 - y)] = color;
        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}
 
// 在LCD上绘制矩形
void draw_rectangle(LcdDevice *lcd, int x0, int y0, int width, int height, unsigned int color) {
    for (int y = y0; y < y0 + height; y++) {
        for (int x = x0; x < x0 + width; x++) {
            lcd->mptr[y * lcd->w + x] = color;
        }
    }
}
 
// 在LCD上绘制直线 (Bresenham's line algorithm)
void draw_line(LcdDevice *lcd, int x0, int y0, int x1, int y1, unsigned int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
 
    while (1) {
        lcd->mptr[y0 * lcd->w + x0] = color;
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
 
 
// 在LCD上绘制带旋转角度的矩形
void draw_rotated_rectangle(LcdDevice *lcd, int x0, int y0, int width, int height, float angle, unsigned int color) {
    // 角度转换为弧度
    float rad = angle * M_PI / 180.0;
 
    // 矩形的四个顶点
    int x1 = x0 - width / 2;
    int y1 = y0 - height / 2;
    int x2 = x0 + width / 2;
    int y2 = y0 - height / 2;
    int x3 = x0 + width / 2;
    int y3 = y0 + height / 2;
    int x4 = x0 - width / 2;
    int y4 = y0 + height / 2;
 
    // 旋转后的顶点
    int xr1 = x0 + (x1 - x0) * cos(rad) - (y1 - y0) * sin(rad);
    int yr1 = y0 + (x1 - x0) * sin(rad) + (y1 - y0) * cos(rad);
    int xr2 = x0 + (x2 - x0) * cos(rad) - (y2 - y0) * sin(rad);
    int yr2 = y0 + (x2 - x0) * sin(rad) + (y2 - y0) * cos(rad);
    int xr3 = x0 + (x3 - x0) * cos(rad) - (y3 - y0) * sin(rad);
    int yr3 = y0 + (x3 - x0) * sin(rad) + (y3 - y0) * cos(rad);
    int xr4 = x0 + (x4 - x0) * cos(rad) - (y4 - y0) * sin(rad);
    int yr4 = y0 + (x4 - x0) * sin(rad) + (y4 - y0) * cos(rad);
 
    // 绘制四条边
    draw_line(lcd, xr1, yr1, xr2, yr2, color);
    draw_line(lcd, xr2, yr2, xr3, yr3, color);
    draw_line(lcd, xr3, yr3, xr4, yr4, color);
    draw_line(lcd, xr4, yr4, xr1, yr1, color);
}