#include <stdio.h>
#include "lcddevice/lcddevice.h"

int main(void)
{
    struct LcdDevice* lcd = getLcd(); //创建lcd变量

    lcd->clear(0xffffff);//设置屏幕为白色
    lcd->drawPoint(10,10,0xff0000); //绘制一个点
    lcd->drawLine(10,10,200,200, 0xff);//绘制直线
    lcd->drawCircle(10,10, 50, 0xff0000);//绘制圆
    lcd->destroy();
    return 0;
}