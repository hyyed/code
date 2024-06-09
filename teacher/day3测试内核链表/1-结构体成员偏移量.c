#include <stdio.h>

//链表结构体
struct list_head{
    struct list_head *prev, *next;
};

//数据结构体
struct Data{
    struct list_head list;
    int data;
};

int main(void)
{
    struct Data d1;
    //计算list成员到d1的偏移量s
    //unsigned long s = (char*)&d1.list - (char *)&d1;
    unsigned long s = (unsigned long)&(((struct Data*)0)->list);

    printf("%p, %p, %ld\n", &d1, &d1.list, s);


    struct Data d2; //假设d2.list已知

    //通过d2.list， 与偏移量s计算d2的地址
    unsigned long d2ptr = (char *)&d2.list - s;
    printf("%p, %lx\n", &d2,  d2ptr);




}


