#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lcd/lcd.h"
#include "graph/graph.h"
#include "readPicture/readPicture.h"
#include "event0/event0.h"
#include "led/led.h"
#include "fontset/fontset.h"

// #include "draw/draw.h"

#define IMAGE
#define DRAW
#define FONTSET
#define EVENT0
// #define LED

#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff

int main()
{
    // 打开设备
    LcdDevice* lcd = CreateLcd(LCD_DEVNAME);

    LcdClear(lcd, 0xffffff);
    sleep(1);

// 字体设置
#ifdef FONTSET
fontset:
    printf("\n开始设置字体...\n");
    sleep(1);

    #if FONT_STRUCT==1
    SetFont* setFont = CreatSetFont();
    if (NULL == setFont) {
        printf("创建字体设置失败!\n");
        goto event0;
    }
    // 打印字体（可设置结构体）
    FontPrint(setFont, 200, 100, "hello word!", lcd);
    #endif

    #if FONT_STRUCT==0
    FontSet(lcd);
    #endif
#endif

// 读取显示图片
#if defined (IMAGE)
    ReadPicture* picture = ReadPict(PIC_NAME);
    if (NULL == picture) {
        printf("读取图片失败!\n");
        goto draw;
    }
    ImageShow(lcd, picture, 50, 200);
    FreePict(picture);
#endif

// 数学图像
#ifdef DRAW
draw:
    printf("\n开始显示数学图像...\n");
    GraphDriver* graphDriver = GetGraphDriver();
    if (NULL == graphDriver) {
        printf("创建图形驱动失败!\n");
        exit(1);
    }
    graphDriver->pdraw_circle(lcd, 200, 100, 50, RED);
    graphDriver->pdraw_rectangle(lcd, 400, 50, 100, 50, GREEN);
    graphDriver->pdraw_line(lcd, 100, 300, 300, 300,GREEN);
    graphDriver->pdraw_rotated_rectangle(lcd, 600, 300, 50, 50, 110, BLUE);
#endif


// 触摸屏事件处理
#ifdef EVENT0
event0:
    printf("\n开始触摸屏事件处理...\n");
    while (1) {
        // 注意：返回值的是否为空，影响下一步操作一般在 函数内部判断，主函数自调用。
        Event0Dev* event0Dev = CreatEvent0Dev(EVENT0_PATH);
        Point point = GetPoint(event0Dev);
        printf("触摸屏坐标:(%d,%d)\n", point.x, point.y);
    }
#endif

// LED控制
#ifdef LED
ledBlink:
    printf("\n开始LED闪烁...\n");
    LedTypeDef *led = CreateLed(LEDPATH);
    if (NULL == led) {
        printf("创建LED失败!\n");
        goto end;
    }
    led->LedBlink(1);
    led->DestroyLed();
#endif


end:
    //销毁lcd结构体
    if (!DestroyLcd(lcd)) {
        printf("销毁失败!\n");
    }

    // 退出程序
    exit(0);
    return 0;

}
