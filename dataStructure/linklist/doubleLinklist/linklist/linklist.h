#ifndef _LINKLISK_
#define _LINKLISK_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 链表结构体 （想一想在语言上怎么 分离数据与关系链）
typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode* next;
    struct LNode* prev;
}LNode, *LinkList;


// 创建
LinkList CreatLinkList();
// 销毁
bool DestroyLinkList(LinkList head);

// 增
bool InsertNode(LinkList head, ElemType data, \
             ElemType (*pAssignData)(ElemType, ElemType));
// 删(指定数据)
bool DeleteLNode(LinkList head, ElemType data, \
             bool (*pEqualData)(ElemType, ElemType));
             
// 改
LNode SetLNode(LinkList head, ElemType targData, ElemType sourceData, \
             ElemType (*pAssignData)(ElemType, ElemType));

// 查
LNode IndexLNode(LinkList head, ElemType targData, \
             bool (*pEqualData)(ElemType, ElemType));


// 遍历
bool DisplayLinkList(LinkList head, bool (*pShowData)(ElemType));


#endif