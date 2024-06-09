#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;
struct StackNode{
    struct StackNode *next;
    ElemType data;
};

//判断栈是否为NULL
bool isEmpty(struct StackNode* top)
{
    //判断top->next 是否为NULL
    if(top==NULL || top->next == NULL) return true;
    else return false;
}

//创建栈
struct StackNode* createStack(ElemType data){
    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode));
    if(node != NULL){
        node->data = data;
        node->next = NULL;
        return node;
    }
    return NULL;
}
//入栈
bool pushStack(struct StackNode *top,  ElemType data){
    //判断top是否NULL，创建新节点node初始数据为data, 把node插入top后面，返回
    if(top==NULL) return false;
    struct StackNode* node = createStack(data);
    if(node == NULL) return false;

    node->next = top->next;
    top->next = node;
    return true;
}
//出栈
bool popStack(struct StackNode* top, ElemType *data){
    //判断栈是否为空，定义一个指针p指向top的下一个节点， 把p->data数据保存到*data 
    //把p从链表中删除，释放p
    if(isEmpty(top)) return false;
    struct StackNode* p =  top->next;
    *data = p->data;
    top->next = p->next;
    free(p);
    return true;
}
//获取栈顶元素
bool  topStack(struct StackNode* top, ElemType *data){
    //判断栈是否为空，返回top->next->data
    if(!isEmpty(top))
    {
        *data = top->next->data;
        return true;
    }
    return  false;
}


int main(void)
{
    struct StackNode *top = createStack(0);
    //括号匹配
    char a[]="<234{sdfdsf}disf(sdfdsf)[sdfs{dfsdf}]sdfs.fsdfdsf>";
    char *p = a;
    while(*p != '\0')
    {
        if(*p == '{' || *p == '[' || *p == '(' || *p == '<')
        {
            pushStack(top, *p);
        }

        if(*p == '}')
        {
           //去栈顶符号
           char ch = 0;
           popStack(top, &ch);
           if(ch != '{') 
           {
                printf("{}括号匹配失败\n");
           }
        }

        if(*p == ']')
        {
           //去栈顶符号
           char ch = 0;
           popStack(top, &ch);
           if(ch != '[') 
           {
                printf("[]括号匹配失败\n");
           }
        }

        if(*p == ')')
        {
           //去栈顶符号
           char ch = 0;
           popStack(top, &ch);
           if(ch != '(') 
           {
                printf("()括号匹配失败\n");
           }
        }

        if(*p == '>')
        {
           //去栈顶符号
           char ch = 0;
           popStack(top, &ch);
           if(ch != '<') 
           {
                printf("<>括号匹配失败\n");
           }
        }
        p++;
    }

    if(isEmpty(top))
    {
        printf("括号匹配成功\n");
    }else{
         printf("括号匹配失败\n");
    }
}