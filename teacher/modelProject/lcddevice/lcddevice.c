#include "lcddevice.h"
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/fb.h>  //vim /usr/include/linux/fb.h 

static struct LcdDevice* instance = NULL; 

static void clear(unsigned int color) //设置屏幕
{
    for(int i=0; i<instance->w* instance->h; i++)
    {
        instance->mptr[i] = color;
    }
}
static void drawPoint(int x,int y,unsigned int color) //绘制一个点
{
    //定义变量保存lcd首地址
    unsigned int *p = instance->mptr+x+y*instance->w;
    p[0] = color;
}
static void drawLine(int x0,int y0,int x1,int y1, unsigned int color)//绘制直线
{
    //定义变量保存lcd首地址
    unsigned int *p = instance->mptr;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        p[y0 * instance->w + x0] = color;
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
static void drawCircle(int x0,int y0,int radius,unsigned int color)//绘制圆
{
    //定义变量保存lcd首地址
    unsigned int *p = instance->mptr;
    int x = radius;
    int y = 0;
    int err = 0;
    while (x >= y) {
        p[(y0 + y) * instance->w + (x0 + x)] = color;
        p[(y0 + y) * instance->w + (x0 - x)] = color;
        p[(y0 - y) * instance->w + (x0 + x)] = color;
        p[(y0 - y) * instance->w + (x0 - x)] = color;
        p[(y0 + x) * instance->w + (x0 + y)] = color;
        p[(y0 + x) * instance->w + (x0 - y)] = color;
        p[(y0 - x) * instance->w + (x0 + y)] = color;
        p[(y0 - x) * instance->w + (x0 - y)] = color;
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


static void destroy()//销毁
{
    if(instance != NULL)
    {
        munmap(instance->mptr, instance->w*instance->h*instance->bytepix);
        close(instance->fd);
        free(instance);
        instance = NULL;
    }
}

struct LcdDevice *getLcd()
{
    if(instance != NULL)
    {
        return instance;
       
    }
    instance = malloc(sizeof(struct LcdDevice));
    //打开设备
    instance->fd = open("/dev/fb0", O_RDWR);
    if(instance->fd  < 0)
    {
        perror("open");
        goto openerr;
    }

    //获取lcd设备信息
    //从驱动获取设备信息 --宽， 高， 色深
    struct fb_var_screeninfo  vinfo;
    int ret = ioctl(instance->fd, FBIOGET_VSCREENINFO, &vinfo);
    if(ret < 0)
    {
        perror("ioctl err");
        goto mmaperr;
    }
    instance->w = vinfo.xres;
    instance->h = vinfo.yres;
    instance->bytepix = vinfo.bits_per_pixel/8;

    //映射
    instance->mptr = mmap(NULL, instance->w*instance->h*instance->bytepix,
                         PROT_READ|PROT_WRITE, MAP_SHARED, instance->fd, 0);
    if(instance->mptr == MAP_FAILED)
    {
        perror("mmap");
        goto mmaperr;
    }
    //初始化函数
    instance->clear = clear;
    instance->drawPoint = drawPoint;
    instance->drawLine = drawLine;
    instance->drawCircle  = drawCircle;
    instance->destroy = destroy;
    return instance;
mmaperr:
    close(instance->fd);
openerr:
    free(instance);
    instance = NULL;
    return instance;
}