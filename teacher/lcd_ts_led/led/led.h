#ifndef _LED_H_
#define _LED_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#define TEST_MAGIC 'x'                    //定义幻数
#define LED1  _IO(TEST_MAGIC, 0)              
#define LED2  _IO(TEST_MAGIC, 1)
#define LED3  _IO(TEST_MAGIC, 2)
#define LED4  _IO(TEST_MAGIC, 3) 

#define LED_ON  	0	//灯亮
#define LED_OFF		1   //灯灭

struct LedDev{
    int fd;
};

//创建LED设备
struct LedDev* createLed(const char *ledname);
//销毁LED设备
bool destroyLed(struct LedDev *led);
//控制-开灯
void  openLed1(struct LedDev* led);
void  closeLed1(struct LedDev* led);



#endif//_LED_H_