#include "fontset.h"


#if FONT_STRUCT==1

SetFont* CreatSetFont()
{
    SetFont* setFont = (SetFont*)malloc(sizeof(SetFont));
    if (NULL == setFont) {
        perror("malloc SetFont error");
        // exit(EXIT_FAILURE);
        return NULL;
    }
    setFont->setFontLocd = FONTLOAD;
    setFont->setFontSize = FONTSIZE;
    setFont->setFontColor = FONTCOLOR;

    return setFont;
}

int FontPrint(SetFont* setFont, int x, int y, char* text, LcdDevice* lcd) 
{
    printf("工程测试\n");
    //创建设备
    // LcdDevice* lcd = createLcd();
    //1.导入字库（字库文件）
    font *f = fontLoad(setFont->setFontLocd);
    // printf("字库导入成功\n");
    //2.设置字体大小（字库指针， 字体大小）
    fontSetSize(f, setFont->setFontSize);
    // printf("字体大小设置成功\n");
    //3.创建一个存储文字区域（宽， 高， 一个像素占用字节数）
    bitmap *bmp = createBitmap(800, 480, 4); //在上显示”我是中国人“
    // printf("创建存储文字区域\n");

    //4.把文字输入到文字域中
    //参数 f-字库, screen-绘制文字区域, x, y位置, text要绘制的文字, c文字颜色(RGBA), maxwidth文字最大宽度默认0自动识别字大小
    // printf("输入文字到文字域中\n");
    fontPrint(f, bmp, x, y, text, setFont->setFontColor, 0);

    //5.把存储文字的区域，拷贝到lcd上显示
    memcpy(lcd->mptr, bmp->map, 800*480*4);
    // printf("拷贝到lcd上显示\n");
    return 0;
}
#endif

#if FONT_STRUCT==0
// 下边是没有字体设置结构体的版本
int FontSet(LcdDevice* lcd)
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
    printf("输入文字到文字域中\n");
    char text[3][100];
    sprintf(text[0],"获取设备分辨率: %d*%d\n", lcd->w, lcd->h);
    sprintf(text[1],"获取设备虚拟分辨率: %d*%d\n", lcd->w_virtual, lcd->h_virtual);
    sprintf(text[2],"获取设备字节像素: %d\n", lcd->bytepix);

    fontPrint(f, bmp, 100, 100, text[0], 0x00ff00ff, 0);
    fontPrint(f, bmp, 100, 150, text[1], 0x00ff00ff, 0);
    fontPrint(f, bmp, 100, 200, text[2], 0x00ff00ff, 0);
    //5.把存储文字的区域，拷贝到lcd上显示
    memcpy(lcd->mptr, bmp->map, 800*480*4);
    printf("拷贝到lcd上显示\n");
    //销毁设备
    // destroyLcd(lcd);
    return 0;
} 
#endif