#ifndef _LCDDEVICE_H
#define _LCDDEVICE_H

struct LcdDevice{
    int w, h, bytepix; //宽，高， 色深
    int fd;//文件描述符
    unsigned int *mptr;//存储映射的指针
    //封装操作函数
    void (*clear)(unsigned int color); //设置屏幕
    void (*drawPoint)(int x,int y,unsigned int color); //绘制一个点
    void (*drawLine)(int x0,int y0,int x1,int y1, unsigned int color);//绘制直线
    void (*drawCircle)(int x,int y,int radius,unsigned int color);//绘制圆
    //销毁
    void (*destroy)();
};
//创建设备
struct LcdDevice* getLcd(); 
#endif