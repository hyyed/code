#ifndef _KERNEL_LINKLIST_H_
#define _KERNEL_LINKLIST_H_

#include <stdio.h>

typedef struct KernelLinklist 
{
    struct KernelLinklist* prev;
    struct KernelLinklist* next;
} KernelLinklist;


// 初始化
void InitKernelList(KernelLinklist head);

// 头插
void HeadKernelList(KernelLinklist head, KernelLinklist newl);

// 尾巴插
void TailKernelList(KernelLinklist taul, KernelLinklist newl);

// 删除()
void DeleKernelList(KernelLinklist head, KernelLinklist )

//删除
void  list_del(struct list_head *node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = node;
    node->prev = node;
}
