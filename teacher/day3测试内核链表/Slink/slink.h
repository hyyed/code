#ifndef _SLINK_H_
#define _SLINK_H_
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct SLink{
    struct SLink* prev;
    struct SLink* next;
    int data;
};

//创建节点
struct SLink* createNode(int data);
//插入节点
bool insertNode(struct SLink* head, struct SLink* node);
//显示链表
void displayNode(struct SLink* head);
//删除节点
bool deleteNode(struct SLink* node);
//销毁链表
bool destroyNode(struct SLink* head);
//查找函数
struct SLink* indexOf(struct SLink* head,  int data);
#endif