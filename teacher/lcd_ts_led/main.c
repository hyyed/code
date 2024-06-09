#include <stdio.h>
#include <lcddevice.h>
#include <tsevent.h>
#include <led.h>

int main(void)
{
    struct TsDev* ts = createTs("/dev/input/event0");
    struct LcdDevice *lcd = createLcd("/dev/fb0");
    struct LedDev* led = createLed("/dev/Led");
    struct PicImage *onimage = createBmp("./on.bmp");
    struct PicImage *offimage = createBmp("./off.bmp");

    //初始化界面
    drawColor(lcd, 0xffffff);
    drawBmp(lcd, offimage, 200,120);
    drawBmp(lcd, offimage, 400,120);
    int ledflag[2] = {0,0};

    while(1){
        Point p = readXY(ts);
        if((p.x > 200 && p.x<400) && (p.y>120 && p.y<320) )
        {
            if(ledflag[0] == 0){
                ledflag[0] = 1;
                drawBmp(lcd, onimage, 200,120);
                openLed1(led);
            }else{
                ledflag[0] = 0;
                drawBmp(lcd, offimage, 200,120);
                closeLed1(led);
            }  
        }

    }

    destroyBmp(offimage);
    destroyBmp(onimage);
    destroyLcd(lcd);
    destroyTs(ts);
    destroyLed(led);
    return 0;
}