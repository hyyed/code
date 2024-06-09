#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Empty;

typedef struct StackNode {
    struct StackNode* next;
    Empty data;
}StackNode;

// 判断栈是否为NULL
static inline bool isEmpty(StackNode* top)
{
    //判断top->next 是否为NULL
    if (top == NULL || top->next == NULL) {
        perror("Cstack is NULL");
        return true;
    }
    return false;
}

// 创建栈
StackNode* createStack(Empty data) {
    StackNode* top = (StackNode*)malloc(sizeof(StackNode));
    if (NULL == top) return NULL; 
    top->next = NULL;
    top->data = data;
    return top;
}

// 入栈
static inline bool pushStack(StackNode *top,  Empty data){
    //判断top是否NULL，创建新节点node初始数据为data, 把node插入top后面，返回
    if (NULL == top) return false;
    StackNode* p = (StackNode*)malloc(sizeof(StackNode));
    if (NULL==p) return false;
    p->data = data;
    p->next = top->next;
    top->next = p;
    return true;
}
// 出栈
static inline bool popStack(StackNode* top, Empty *data){
    //判断栈是否为空，定义一个指针p指向top的下一个节点， 把p->data数据保存到*data 
    //把p从链表中删除，释放p
    if (isEmpty(top)) return false;
    StackNode* p=top->next;
    *data = p->data;
    top->next = p->next;
    free(p);
    p->next = p;
    return true;
}
// 获取栈顶元素
static inline bool topStack(StackNode* top, Empty data){
    //判断栈是否为空，返回top->next->data
    if (isEmpty(top)) return false;
    return top->next->data;
}


int main () {
    StackNode* top = createStack(10);
    pushStack(top, 20);
    pushStack(top, 30);
    pushStack(top, 40);
    pushStack(top, 50);

    Empty data = 0;

    while (top->next != NULL)
    {
        popStack(top, &data);
        printf("data: %d\n", data);
    }


    return 0;


}