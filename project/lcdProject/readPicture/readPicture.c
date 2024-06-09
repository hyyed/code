#include "readPicture.h"

// extern typedef struct BitFileHeader ;
// static ReadPicture* readPict;

// 读取bmp 图片
ReadPicture* ReadPict(const char* filename) 
{
    //1、申请读图片信息，结构体空间
    ReadPicture* readPict = malloc(sizeof(ReadPicture));
    if (NULL == readPict) {
        perror("malloc error");
        return NULL;
    }

    // 2、打开文件
    readPict->fd = open(filename, O_RDWR);
    if (-1 == readPict->fd) {
        perror("open error");
        goto erropen;
    }
    printf("readPict->fd: %d\n", readPict->fd);

    // 3、读取文件头
    printf("读图文件头\n");
    BitHeader bmpHeader;
    int ret = read(readPict->fd, &bmpHeader, 54);
    if (0 > ret) {
        perror("read header error");
        goto erropen;
    }

    printf("读图1\n");

    // 初始化图片结构体信息 1、宽 2、高 3、像素字节数
    readPict->width = bmpHeader.biWidth; printf("width:%d\n",readPict->width);
    readPict->height = bmpHeader.biHeight; printf("height:%d\n",readPict->height);
    readPict->pixByte = bmpHeader.biBitCount/8; printf("pixByte:%d\n",readPict->pixByte);
    // static ImageProcess process;
    // process.pRgbArgb = RgbArgb;

    // 打印图片信息
    printf("pic-width: %d\npic-height: %d\npix-byte: %d\n",
                readPict->width, readPict->height, readPict->pixByte);

    // 图片空间申请 1、字节对齐 2、行缓存，补齐四字节，记得本函数内释放 3、rgb图片空间
    int lseek = readPict->width % 4; //以四字节对齐，截断了余数
    int lineChar = (readPict->width) * (readPict->pixByte); //一行字节数
    unsigned char* lineBuffer = malloc(lineChar+lseek); //一行空间（需补齐4字节）
    readPict->rgbData = malloc(lineChar * readPict->height); //图片空间（字需要存放rgb信息）
    if (NULL == lineBuffer || NULL == readPict->rgbData) { //空间申请失败
        perror("malloc error");
        goto errRead;
    }
    // printf("lseek:%d;\nlinChar:%d;\n 图片空间%d\n",
    //              lseek,lineChar,(lineChar * readPict->height));

    // 读取图片 1、读取到行缓存 2、每一行拷贝一次到图片空间
    int readChar = 0;
    for (int i=0; i<readPict->height; ++i) {
        readChar = read(readPict->fd, lineBuffer, lineChar + lseek);
        memcpy(readPict->rgbData + i *lineChar, lineBuffer, lineChar);
        // memcmp(readPict->rgbData + i *lineChar, lineBuffer, lineChar);
        if (-1 > readChar) {
            perror("read line error");
            goto errRead;
        }
    }

    //释放图片行缓冲
    free(lineBuffer); 
    printf("图片读取完成!\n");
    return readPict;

errRead:
    free(lineBuffer);
    free(readPict->rgbData);

erropen:
    // 释放读图片信息结构体空间
    free(readPict);
}

// 释放内存 1、关闭文件描述符 2、释放图片空间 3、释放读图片信息结构体空间
bool FreePict(ReadPicture* readPict)
{
    if (NULL == readPict) {
        perror("readPict is NULL");
        return false;
    }
    if (0 != readPict->fd) {
        close(readPict->fd);
    }
    free(readPict->rgbData);
    free(readPict);
    return true;
}