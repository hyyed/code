#include "lcd.h"


//初始化lcd设备
LcdDevice* CreateLcd(char* devname) 
{
    // 结构体堆空间，防止被释放
    LcdDevice* lcd = malloc(sizeof(LcdDevice));
    if (NULL == lcd) {
        perror("malloc error");
        return NULL;
    }

    // 打开lcd设备文件
    lcd->fd = open(devname ,O_RDWR);
    if (-1 == lcd->fd) {
        perror("open lcd error");
        goto openerr;
    }
    printf("lcd->fd: %d\n", lcd->fd);
    
    // 获取屏幕信息结构体
    struct fb_var_screeninfo vinfo;
    int ret = ioctl(lcd->fd, FBIOGET_VSCREENINFO, &vinfo);
    if (0 > ret) {
        perror("ioctl error");
        goto mmaperr;
    }
 
    // 初始化lcd设备信息，即结构体信息
    lcd->w = vinfo.xres;
    lcd->h = vinfo.yres;
    lcd->w_virtual = vinfo.xres_virtual;
    lcd->h_virtual = vinfo.yres_virtual;
    lcd->bytepix = vinfo.bits_per_pixel/8;
    printf("获取设备分辨率: %d*%d \n", lcd->w, lcd->h);
    printf("获取设备虚拟分辨率: %d*%d \n", lcd->w_virtual, lcd->h_virtual);
    printf("获取设备字节像素: %d \n", lcd->bytepix);

    // 映射堆空间
    #ifndef DOUBLE_BUFFER
    // 单缓冲区
    lcd->mptr = mmap(NULL, lcd->w*lcd->h*lcd->bytepix, 
                     PROT_READ | PROT_WRITE, MAP_SHARED, lcd->fd, 0);
    #else
    // 双缓冲区
    lcd->mptr = mmap(NULL, 2*lcd->w*lcd->h*lcd->bytepix, 
                     PROT_READ | PROT_WRITE, MAP_SHARED, lcd->fd, 0);
    #endif


    if (MAP_FAILED == lcd->mptr) {
        perror("mmap error");
        goto mmaperr;
    }
    printf("映射堆空间: %p\n", lcd->mptr);

    return lcd;

mmaperr:
    close(lcd->fd);

openerr:
    free(lcd);
    return NULL;
}

//释放空间
bool DestroyLcd(LcdDevice* lcd) 
{
    // 以页为单位释放映射地址
    long page_size = sysconf(_SC_PAGESIZE);
    printf("The system page size is: %ld bytes\n", page_size);
    // 空指针判断
    if (NULL == lcd) { 
        perror("lcd is NULL");
        return false;
    }
    // 释放映射空间
    if (munmap(lcd->mptr, lcd->w*lcd->h*lcd->bytepix)) {
        perror("munmap error");
        exit(1);
    }

    close(lcd->fd); // 关闭lcd设备文件
    free(lcd); // 释放lcd结构体

    return true;
}


// 将RGB文件转ARGB
bool ImageShow(LcdDevice* lcd, ReadPicture* rgb, int x, int y) {   
    unsigned int* mptr = lcd->mptr; // 显示地址指针
    unsigned char* rgbp = rgb->rgbData + (rgb->width * rgb->pixByte * (rgb->height - 1)); // 图片数据指针(上下颠倒)
    mptr = mptr + y * lcd->w + x; // 显示指针移动到指定位置

    printf("开始RGB转ARGB!\n");
    for (int i=0; i<rgb->height; ++i) {
        for (int j=0; j<rgb->width; ++j) {
            mptr[j] = (0xFF << 24) | (rgbp[2+j*3] << 16) | (rgbp[1+j*3] << 8) | rgbp[j*3];
        }

        mptr += lcd->w; // 显示换行
        rgbp -= (rgb->width * rgb->pixByte); // 图片数据换行
    }
    printf("RGB转ARGB完成!\n");
    return true;
}

// 清屏函数
void LcdClear(LcdDevice* lcd, unsigned int color) 
{
    for(int i=0; i<lcd->w*lcd->h-10; i++) {
        lcd->mptr[i] = color;
    }
}

