#ifndef _LED_H_
#define _LED_H_

#include <stdbool.h>

#define TEST_MAGIC 'x'                    //定义幻数
#define LED1 _IO(TEST_MAGIC, 0)              
#define LED2 _IO(TEST_MAGIC, 1)
#define LED3 _IO(TEST_MAGIC, 2)
#define LED4 _IO(TEST_MAGIC, 3) 
 
#define LED_ON  	0	//灯亮
#define LED_OFF		1   //灯灭

#define LEDPATH "/dev/Led"

typedef struct LedTypeDef{
    int fd;
    void (*LedOff)(int num);
    void (*LedOn)(int num);
    void (*LedBlink)(int num);
    bool (*DestroyLed)(void);
} LedTypeDef;

// 创建销毁 led 设备
LedTypeDef* CreateLed(const char* filename);
bool DestroyLed(void);


// led 闪烁
void LedOff(int num);
void LedOn(int num);
void LedBlink(int num);




#endif /* _LED_H_ */