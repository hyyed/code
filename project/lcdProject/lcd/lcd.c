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
 
    // 获取lcd设备信息 1、屏幕像素 2、屏幕虚拟像素 3、字节像素
    lcd->w = vinfo.xres;
    lcd->h = vinfo.yres;
    lcd->xvirtual = vinfo.xres_virtual;
    lcd->yvirtual = vinfo.yres_virtual;
    lcd->pixByte = vinfo.bits_per_pixel/8;
    // vinfo.xoffset = lcd->xoffset; // 偏移量 默认0
    // vinfo.yoffset = lcd->yoffset; // 偏移量 默认0
    printf("获取设备分辨率: %d*%d \n", lcd->w, lcd->h);
    printf("获取设备虚拟分辨率: %d*%d \n", lcd->xvirtual, lcd->yvirtual);
    printf("获取设备字节像素: %d \n", lcd->pixByte);

    // 映射堆空间
    // #ifndef DOUBLE_BUFFER
    // // 单缓冲区
    // lcd->mptr = mmap(NULL, lcd->w * lcd->h * lcd->pixByte, 
    //                  PROT_READ | PROT_WRITE, MAP_SHARED, lcd->fd, 0);
    // #else
    // // 双缓冲区
    lcd->mptr = mmap(NULL, 2 * lcd->w * lcd->h * lcd->pixByte, 
                     PROT_READ | PROT_WRITE, MAP_SHARED, lcd->fd, 0);
    // #endif
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

// 释放空间
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
    if (munmap(lcd->mptr, lcd->w * lcd->h * lcd->pixByte)) {
        perror("munmap error");
        exit(1);
    }

    close(lcd->fd); // 关闭lcd设备文件
    free(lcd); // 释放lcd结构体

    return true;
}


// 将RGB文件转ARGB
bool ImageShow(LcdDevice* lcd, ReadPicture* rgb, int x, int y, int range) {   
    // 判断指针和坐标是否超出范围
    if (NULL == lcd || NULL == rgb) {
        perror("Struct Point is NULL !");
        return false;
    }
    if (x < 0 || x > lcd->w || y < 0 || y > lcd->h) {
        printf("Coordinates Out of Range !\n");
        return false;
    }

    unsigned int* mptr = lcd->mptr + x + y * lcd->w ;// 显示指针移动到指定位置
    unsigned char* rgbp = rgb->rgbData + 
                         (rgb->width * (rgb->height - 1) * rgb->pixByte); // 图片数据指针(从最后一行开始扫描)

    // 设置偏移量为0
    struct fb_var_screeninfo vinfo;
    if (0 == range) {
        mptr = mptr; // 显示地址指针
        vinfo.xoffset = 0;
        vinfo.yoffset = 0;
    }
    // 设置偏移量为一个屏幕
    if (1 == range) {
        mptr =  mptr + lcd->w * lcd->h * lcd->pixByte; // 显示地址指针
        vinfo.xoffset = 0; 
        vinfo.yoffset = lcd->h;
    }
    // 设置缓存区的可见区域(发送设置信息给内核)
    ioctl(lcd->fd, FBIOPUT_VSCREENINFO, &vinfo); // 偏移量恢复默认值
    printf("sizeof(lcd->mptr): %ld\n", sizeof(lcd->mptr));
    char *ppp = (char*)lcd->mptr;
    printf("strlen(lcd->mptr): %ld\n", strlen(ppp));

    printf("开始RGB转ARGB!\n");
    for (int i=0; i<rgb->height; ++i) {
        printf("正在处理第%d/%d行!\n", i+1, rgb->height);
        for (int j=0; j<rgb->width; ++j) {
            printf("正在处理第%d/%d列!\n", j+1, rgb->width);
            mptr[j] = (0xFF << 24) | (rgbp[2+j*3] << 16) | (rgbp[1+j*3] << 8) | rgbp[j*3];
        }
        printf("已完成%d/%d行!\n", i+1, rgb->height);
        mptr += lcd->w; // 显示换行
        rgbp -= (rgb->width * rgb->pixByte); // 图片数据换行
    }
    printf("RGB转ARGB完成!\n");
    return true;
}

// 清屏函数（双缓冲可能需要清屏俩个）
void LcdClear(LcdDevice* lcd, unsigned int color) 
{
    for(int i=0; i<lcd->w*lcd->h-10; i++) {
        lcd->mptr[i] = color;
    }
}

