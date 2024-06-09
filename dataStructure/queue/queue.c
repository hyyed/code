#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 20

typedef char ElemType;

typedef struct  Squeue{
    ElemType  *data ;//存储数据空间（申请堆空间）
    int front;//头
    int tail; //尾
    int size; //对列长度    
}Squeue ;


//创建队列
struct Squeue* createsq(int size);
//检查队列是否为空间
bool isEmpty(struct Squeue* sq);
//检查队列是否满
bool isFull(struct Squeue* sq);
//入队列
bool  interSq(struct Squeue* sq,  ElemType data);
//出队列
bool leaveSq(struct Squeue *sq, ElemType* data);
//获取队头元素
bool frontsq(struct Squeue *sq, ElemType* data);

//销毁队列
void destroySq(struct Squeue* sq);

int main() 
{
    Squeue* sq = createsq(MAX_SIZE);

    for (char i='A'; i<'Z'; i++) {
        if (! interSq(sq, i)) break;
        printf("%c", i);
    }

    ElemType data;
    int i=0;
    while (!isEmpty(sq))
    {   
        leaveSq(sq, &data);
        printf("%d:%c\n", ++i,data);
    }
    printf("\n");

    destroySq(sq);

}



//创建队列
struct Squeue* createsq(int size) 
{
    struct Squeue* sq = (struct Squeue*)malloc(sizeof(struct Squeue));
    if (NULL == sq) {
        perror("Malloc Error");
        return NULL;
    }
    sq->data = (ElemType*)malloc(size * sizeof(ElemType));
    if (NULL == sq->data) {
        perror("Malloc Error");
        free(sq);
        return NULL;
    }

    sq->front = 0;
    sq->tail = 0;
    sq->size = size;
    return sq;
}

//检查队列是否为空
bool isEmpty(struct Squeue* sq) 
{
    if (sq->front == sq->tail) {
        printf("Queue is Empty\n");
        return true;
    }
    return false;
}
//检查队列是否满
bool isFull(struct Squeue* sq) {
    if ((sq->tail + 1) % sq->size == sq->front) {
        printf("Queue is Full!\n");
        return true;
    }
    return false;
}

//入队列
bool  interSq(struct Squeue* sq,  ElemType data) 
{
    if (isFull(sq)) return false;
    sq->data[sq->tail] = data;  
    sq->tail = (sq->tail + 1) % sq->size; //取余在逻辑上就是环状的
    return true;
}
//出队列
bool leaveSq(struct Squeue *sq, ElemType* data) 
{
    if (isEmpty(sq)) return false;
    *data = sq->data[sq->front];
    sq->front = (sq->front + 1) % MAX_SIZE; //取余在逻辑上就是环状的
    return true;
}
//获取队头元素
bool frontsq(struct Squeue *sq, ElemType* data) 
{
    if (isEmpty(sq)) return false;
    *data = sq->data[sq->front];
    return true;
}

//销毁队列
void destroySq(struct Squeue* sq) {
    if (NULL == sq) return;
    if (NULL == sq->data) free(sq);
    free(sq->data);
    free(sq);
    printf("Squeue Destroy succes!\n");
}