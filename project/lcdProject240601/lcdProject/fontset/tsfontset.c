#include "fontset.h"

int main(LcdDevice* lcd)
{
    printf("工程测试\n");
    //创建设备
    // LcdDevice* lcd = createLcd();
    //1.导入字库（字库文件）
    font *f = fontLoad("./simfang.ttf");
    printf("字库导入成功\n");
    //2.设置字体大小（字库指针， 字体大小）
    fontSetSize(f, 32);
    printf("字体大小设置成功\n");
    //3.创建一个存储文字区域（宽， 高， 一个像素占用字节数）
    bitmap *bmp = createBitmap(800, 480, 4); //在上显示”我是中国人“
    printf("创建存储文字区域\n");
    //4.把文字输入到文字域中
    //参数 f-字库, screen-绘制文字区域, x, y位置, text要绘制的文字, c文字颜色(RGBA), maxwidth文字最大宽度默认0自动识别字大小
    fontPrint(f, bmp, 300, 200, "我是中国人", 0x00ff00ff, 0);
    printf("输入文字到文字域中\n");
    //5.把存储文字的区域，拷贝到lcd上显示
    memcpy(lcd->mptr, bmp->map, 800*480*4);
    // printf("拷贝到lcd上显示\n");tt
    //销毁设备
    // destroyLcd(lcd);
    return 0;
}