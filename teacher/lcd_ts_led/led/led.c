#include "led.h"

//创建LED设备
struct LedDev* createLed(const char *ledname){
    static struct LedDev led;
    led.fd = open(ledname, O_RDWR);
    if(led.fd < 0){
        perror("open led ");
        return NULL;
    }
    return &led;
}
//销毁LED设备
bool destroyLed(struct LedDev *led)
{
    close(led->fd);
}
//控制-开灯
void  openLed1(struct LedDev* led){
    ioctl(led->fd,LED1,LED_ON);
}
void  closeLed1(struct LedDev* led){
    ioctl(led->fd,LED1, LED_OFF);
}