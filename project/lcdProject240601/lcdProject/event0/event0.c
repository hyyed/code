#include "event0.h"

//创建触摸屏结构体
Event0Dev* CreatEvent0Dev(const char* filename) {
    Event0Dev* dev = (Event0Dev*)malloc(sizeof(Event0Dev));
    dev->fd = open(filename, O_RDWR);
    if (dev->fd < 0) {
        perror("open event0 error");
        free(dev);
        return NULL;
    }

    return dev;

    /* // 禁止缓冲区
    if (ioctl(fd, FIONBIO, 1) < 0) {
        perror("set nonblock error");
        exit(1);
    } */
}

//关闭触摸屏
bool CloseEvent0Dev(Event0Dev* dev) {
    if (NULL == dev) return false;
    close(dev->fd);
    free(dev);  
    return true;
}


Point GetPoint(Event0Dev* dev)
{
    //// ****************************************************************
    /// 注意逻辑的严谨性，需要考虑到可能的异常情况
    /// 不要偷懒
    Point point = {0, 0};
    if (NULL == dev || 0 > dev->fd) {
        return point;
    } 

    
    struct input_event ev; // 定义输入事件结构体 // 按压，左右箭头按压，坐标
    // struct input_absinfo absinfo;

    while(1) {
        int ret = read(dev->fd, &ev, sizeof(ev));
        if (ret < 0) {
            perror("read event0 error");
            exit(1);
        }

        // 检测触摸
        if (EV_KEY == ev.type && BTN_TOUCH == ev.code && ev.value > 0) {
            // printf("touch event0\n");
        } 
        if (EV_KEY == ev.type && BTN_TOUCH == ev.code && ev.value == 0) {
            // printf("release event0\n");
            break;
        }

        // 收集坐标数据
        if (EV_ABS == ev.type) {
            if (ABS_X == ev.code) {
                point.x = ev.value*800/1024;
                // printf("X:%d\n; ", ev.value*800/1024);
            } else if (ABS_Y == ev.code) {
                point.y = ev.value*480/600;
                printf("Y:%d\n", ev.value*480/600);
            }
        }
    }
    return point;
}