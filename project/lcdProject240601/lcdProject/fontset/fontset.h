#ifndef _FONTSET_H_
#define _FONTSET_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "fontlib/font.h"
#include "../lcd/lcd.h"

#define FONTLOAD "./simfang.ttf"
// #define FONTLOAD "./fontlib/simfang.ttf"
#define FONTSIZE 32
#define FONTCOLOR 0x0000FF
#define FONT_STRUCT 0

/* typedef struct SetFond
{
    //1.导入字库（字库文件）
    font* (*fontLoad)(char *fontPath);
    //2.设置字体大小（字库指针， 字体大小）
    void (*fontSetSize)(font *f, s32 pixels);
     //3.创建一个存储文字区域（宽， 高， 一个像素占用字节数）
    bitmap* (*createBitmap)(u32 width, u32 height, u32 byteperpixel);
    //4.把文字输入到文字域中
    //参数 f-字库, screen-绘制文字区域, x, y位置, text要绘制的文字, c文字颜色(RGBA), maxwidth文字最大宽度默认0自动识别字大小
    void (*fontPrint)(font *f, bitmap *screen, s32 x, s32 y, char *text, color c, s32 maxWidth);
    //5.把存储文字的区域，拷贝到lcd上显示
    // memcpy(lcd->mptr, bmp->map, 800*480*4);
}SetFond;
 */

#if FONT_STRUCT == 1
typedef struct
{
    char* setFontLocd; // 字库文件路径
    int setFontSize; // 字体大小
    int setFontColor; // 字体颜色
    // int setx; // 文字起始位置x
    // int sety; // 文字起始位置y
    // char* setText; // 要打印的文字
    // int setMaxwidth = 0; // 文字最大宽度默认0自动识别字大小
}SetFont;

SetFont* CreatSetFont();
int FontPrint(SetFont* setFont, int x, int y, char* text, LcdDevice* lcd); // 打印文字
#endif

#if FONT_STRUCT == 0
int FontSet(LcdDevice* lcd);
#endif


#endif /* _FONTSET_H_ */