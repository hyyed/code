#include "tsevent.h"

//创建触摸屏
struct TsDev* createTs(const char *tsname){
    struct TsDev *ts = malloc(sizeof(struct TsDev));
    ts->fd = open(tsname, O_RDWR);
    if(ts->fd < 0)
    {
        perror("open");
        free(ts);
        return NULL;
    }
    return ts;
}
//销毁触摸屏
bool destroyTs(struct TsDev* ts){
    if(ts != NULL)
    {
        close(ts->fd);
        free(ts);
        return true;
    }
    return false;
}

//读取坐标值
Point readXY(struct TsDev* ts){
    Point p={0,0};
    if(ts== NULL || ts->fd < 0) return p;

    struct input_event evt;
    while(1){
        int size = read(ts->fd, &evt, sizeof(evt));
        if(EV_KEY == evt.type && BTN_TOUCH == evt.code && evt.value>0){

        }
        if(EV_KEY == evt.type && BTN_TOUCH == evt.code && evt.value==0){
            break;
        }
        //x坐标
        if(EV_ABS == evt.type)
        {
            if(evt.code == ABS_X){
                p.x = evt.value*800/1024;
            }
            if(evt.code == ABS_Y)
            {
                p.y = evt.value*480/600;
            }
        }
    }
    return p;
}