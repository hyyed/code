#ifndef _LCDDEVICE_H_
#define _LCDDEVICE_H_


#include <stdio.h>
#include <stdbool.h>
#include "pictrue.h"

//打开设备open，/dev/fb0,  映射mmap
//把lcd设计的到特征属性封装在一个结构体里面
struct LcdDevice{
    int w; //lcd的宽
    int h; //lcd的高
    int bytepix; //一个像素占用自己（色深）  1字节8位， 1m-1024k字节
    int lcdfd;//设备文件描述符
    unsigned  int *mptr ;//保存映射空间首地址
};

#define DEVNAME  "/dev/fb0"

//创建lcd
struct LcdDevice* createLcd();
//销毁lcd
bool destroyLcd(struct LcdDevice* lcd);
//在lcd绘制图片
void drawBmp(struct LcdDevice *lcd, struct PicImage* image,int x, int y);
//清屏函数
void drawColor(struct LcdDevice *lcd , unsigned int color);


#endif//_LCDDEVICE_H_