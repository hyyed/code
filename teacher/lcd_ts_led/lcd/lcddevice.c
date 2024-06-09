#include "lcddevice.h"
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

//创建lcd
struct LcdDevice* createLcd(){
    printf("lcd初始化\n");  
    struct LcdDevice *lcd = (struct LcdDevice*)malloc(sizeof(struct LcdDevice));
    if(NULL == lcd) return NULL;
    //打开设备文件
    lcd->lcdfd = open(DEVNAME, O_RDWR);
    if(lcd->lcdfd < 0){
        perror("lcd open");
        goto openerr;
    }
    //从驱动获取设备信息 --宽， 高， 色深
    struct fb_var_screeninfo  vinfo;
    int ret = ioctl(lcd->lcdfd, FBIOGET_VSCREENINFO, &vinfo);
    if(ret < 0)
    {
        perror("ioctl err");
        goto mmaperr;
    }
    lcd->w = vinfo.xres;
    lcd->h = vinfo.yres;
    lcd->bytepix = vinfo.bits_per_pixel/8;

    //映射
    lcd->mptr = mmap(NULL, lcd->w*lcd->h*lcd->bytepix,
                    PROT_READ|PROT_WRITE,MAP_SHARED,lcd->lcdfd, 0);
    if(lcd->mptr == MAP_FAILED)
    {
        perror("mmap err");
        goto  mmaperr;
    }
    return lcd;
mmaperr:
    close(lcd->lcdfd);
openerr:
    free(lcd);
    return NULL;
}
//销毁lcd
bool destroyLcd(struct LcdDevice* lcd){
    if(NULL == lcd)return false;
    printf("lcd销毁\n");
    //1.释放映射空间
    munmap(lcd->mptr, lcd->w*lcd->h*lcd->bytepix);
    //2.关闭设备
    close(lcd->lcdfd);
    //3.释放lcd设备
    free(lcd);
    return false;
}

//在lcd绘制图片
void drawBmp(struct LcdDevice *lcd, struct PicImage* image,int x, int y)
{
    //5.把数据显示在lcd上
    unsigned int *p = lcd->mptr;
    p = p+y*lcd->w+x;
    unsigned char *q = image->map;
    for(int i=0; i<image->h; ++i)
    {
        for(int j=0; j<image->w; ++j)
        {
            unsigned int argbdata = 0;
            argbdata = (0xFF << 24) | (q[2+j*3] << 16) | (q[1+j*3] << 8) | q[0+j*3];
            p[j] = argbdata;
        }
        q += image->w*image->bytepix;
        p += lcd->w;
    }
}

//绘制颜色
void drawColor(struct LcdDevice *lcd , unsigned int color){
    for(int i=0; i<lcd->w*lcd->h; ++i)
    {
        lcd->mptr[i] = color;
    }
}