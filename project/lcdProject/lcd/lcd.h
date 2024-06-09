#ifndef _LDC_H_
#define _LDC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h> 
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "../readPicture/readPicture.h"

// 双缓冲区
#define DOUBLE_BUFFER

#define LCD_DEVNAME "/dev/fb0"

// lcd设备结构体
typedef struct {
    int w; //lcd的宽
    int h; //lcd的高
    int xvirtual; //虚拟x坐标
    int yvirtual; //虚拟y坐标
    // int xoffset = 0; //偏移x坐标 默认0
    // int yoffset = 0; //偏移y坐标 默认0
    int pixByte; //字节像素

    int  fd; //文件描述符
    unsigned int* mptr ; //映射空间首地址
}LcdDevice;

// 获取屏幕信息（不需要写在lcd设备结构体中，因为他可以让其他文件描述符使用）

// 初始化显示屏
LcdDevice* CreateLcd(char* devname);
// 销毁结构体
bool DestroyLcd(LcdDevice* lcd);
// 清理屏幕
void LcdClear(LcdDevice* lcd, unsigned int color);

// 显示图片
bool ImageShow(LcdDevice* lcd, ReadPicture* rgb, int x, int y, int range);

#endif