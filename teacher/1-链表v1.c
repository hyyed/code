#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct  Node
{
      int data;
      struct Node *next;
};

//创建链表
struct Node* createNode(int data);
//插入数据
bool insertNode(struct Node* head, int data);
//显示数据
void displayNode(struct Node *head);

int main(void)
{
    //创建链表头
    struct Node *head = createNode(0);

    //插入数据
    for(int i=0; i<6; i++){
        int data = random()%100;
        insertNode(head, data);
    }

    //显示
    displayNode(head);

}
//创建链表
struct Node* createNode(int data){
/*
1.申请struct Node结构体空间（堆空间），赋值给node
2.初始化data， next指针
3.返回node
*/
}
//插入数据
bool insertNode(struct Node* head, int data){
/*
1.判断head是否为NULL，直接返回
2.调用createNode函数创建一个新节点p
3.把p->next指针指向head->next
4.把head->next指针指向p
5.返回
*/
}
//显示数据
void displayNode(struct Node *head){
/*
1.判断链表是否NULL， 判断head->next是否为NULL 直接返回
2.定义一个struct Node指针指向head的下一个节点 p = head->next
3.输出p->data
4.p往后偏移 p = p->next
5.循环3，4，直到p为NULL就退出循环
*/
}