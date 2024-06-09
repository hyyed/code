#include "slink.h"


//创建节点
struct SLink* createNode(int data){
    struct SLink* node = (struct SLink*)malloc(sizeof(struct SLink));
    if(node == NULL) return NULL;
    node->data = data;
    node->next = node;
    node->prev = node;
    return node;
}
//插入节点
bool insertNode(struct SLink* head, struct SLink* node){
    if(head == NULL || node == NULL) return false;
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
    return true;
}
//显示链表
void displayNode(struct SLink* head){
    if(head == NULL) return ;
    struct SLink* p = head->next;
    while(p != head)
    {
        printf("%d ", p->data);
        p = p->next;
    }

}
//删除节点
bool deleteNode(struct SLink* node){
    if(node != NULL){
        node->next->prev = node->prev;
        node->prev->next = node->next;
        free(node);
        return true;
    }else 
    return false;
}
//销毁链表
bool destroyNode(struct SLink* head){
    if(head == NULL) return false;
    while(head->next != head){
        struct SLink* p = head->next;
        deleteNode(p);
    }
    free(head);
    return true;
}
//查找函数
struct SLink* indexOf(struct SLink* head,  int data){
    if(head == NULL) return  NULL;
    struct SLink* p = head->next;
    while(p != head)
    {
        if(p->data == data) return p;
        p = p->next;
    }
    return NULL;
}