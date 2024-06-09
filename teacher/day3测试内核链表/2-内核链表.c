#include <stdio.h>
#include <stdlib.h>
//链表结构体
struct list_head{
    struct list_head *prev, *next;
};

//初始化节点
void  list_head_init(struct list_head *list)
{
    list->prev = list;
    list->next = list;
}
//插入-头
void list_add(struct list_head *head,  struct list_head *new)
{
    new->next = head->next;
    new->prev = head;
    head->next->prev = new;
    head->next = new;
}
//插入-尾
void list_add_tail(struct list_head *head,  struct list_head *new)
{
    list_add(head->prev, new);
}
//删除
void  list_del(struct list_head *node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = node;
    node->prev = node;
}


//数据结构体
struct Data{
    struct list_head list;
    int data;
};

int main(void)
{
    struct Data d1; //d1里面的list就是链表的头
    //初始化链表头
    list_head_init(&d1.list);

    for(int i=0; i<5; i++)
    {
        struct Data *d = malloc(sizeof(struct Data));
        d->data = i+10;
        //初始化链表节点
        list_head_init(&d->list);
        //把链接节点插入到链表头后面
        list_add(&d1.list,  &d->list);
    }

    //遍历
    //定义一个链表指针头
    struct list_head * head= &d1.list;
    struct list_head *p = head->next;
    while(p != head){
        //计算链表结构体到数据结构体链接的偏移量
        unsigned long s = (unsigned long)(&((struct Data*)0)->list);
        //通过链表结构体与偏移量计算数结构体地址
        struct Data* d = (struct Data*) ((char*)p-s);
        printf("%d ", d->data);
        p = p->next;
    }printf("\n");

}

