#include <stdio.h>   //从系统头文件路径找stdio.h
#include "calc.h"   //从当前目录下找calc.h文件如果没有找到去系统路径找
#include "utils.h"

int main(void){
    int a=10,b=20;
    int c = add(a,b);
    printf("%d\n", c);

    func();
}