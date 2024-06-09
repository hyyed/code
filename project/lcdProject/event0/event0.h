#ifndef _EVENT0_H_
#define _EVENT0_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h> //usr/include/linux/fb.h

#define EVENT0_PATH "/dev/input/event0"


// 因为只需要获取文件描述符的坐标，所有将其和文件描述符结构体分开
// 这样返回值更加清晰, 
// 给这个结构体赋值，共其他函数使用（故不需要在这考虑控制）
typedef struct Point{
    int x;
    int y;
} Point;

// 设备结构体
typedef struct Event0Dev{
    int fd;
}Event0Dev;

// 创建销毁
Event0Dev* CreatEvent0Dev(const char* filename);
bool CloseEvent0Dev(Event0Dev* dev);

// 获取坐标
Point GetPoint(Event0Dev* dev);


#endif /* _EVENT0_H_ */