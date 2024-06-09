#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "led.h"

static LedTypeDef* led;

LedTypeDef* CreateLed(const char* filename) {
	//1.在程序执行前必须确保你的驱动已经安装驱动
	//2.访问驱动设备
	led = malloc(sizeof(LedTypeDef));
	led->fd = open(filename, O_RDWR);
	if (0 > led->fd) {
		perror("open led device failed");
		return NULL;
	}
	// 初始化设备
	led->LedOff = LedOff;
	led->LedOn = LedOn;
	led->LedBlink = LedBlink;
	led->DestroyLed = DestroyLed;

	return led;
}

// 销毁
bool DestroyLed() {
	if (NULL != led) {
		close(led->fd);
		free(led);
	}
	return true;
}

void LedOff(int num) {
	ioctl(led->fd, LED1, LED_OFF);
}

void LedOn(int num) {
	ioctl(led->fd, LED1, LED_ON);
}

void LedBlink(int num) {
    printf("led blink on...\n");
	while(1) {
		led->LedOn(1);
		sleep(1);
		led->LedOff(1);
		sleep(1);
	}
}

