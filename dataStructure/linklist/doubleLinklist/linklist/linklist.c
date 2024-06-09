# include "linklist.h"
/* 
    宝典：所有申请的临时节点全部执行链表的头结点，方便同一思考，避免思绪混乱。
 */

// 初始化
LinkList CreatLinkList() 
{
    LinkList head = (LinkList)malloc(sizeof(LNode));
    if (head == NULL) {
        perror("Malloc Error");
        return NULL;
    }

    head->next = head;
    head->prev = head;

    return head;
}

// 销毁
bool DestroyLinkList(LinkList head) 
{
    if (NULL == head) {
        perror("Head is NULL Error");
        return false;
    }

    LNode* p = head;
    LNode* q = head;
    int n =0;
    while (head != p->next) {
        q = p->next;
        free(p);
        p = q;
        ++n;
    }
    // free(head);
    printf("链表销毁完成，共%d个节点!\n", n);
    return true;
}


// 前后插
bool InsertNode(LinkList head, ElemType data, \
             ElemType (*pAssignData)(ElemType, ElemType)) 
{
    if (NULL == head) {
        perror("Head is NULL Error");
        return false;
    }

    LNode *p = (LNode*)malloc(sizeof(LNode));
    if (NULL == p) {
        perror("Malloc Error");
        return false;
    }
    
    // 要弄成回调函数
    // p->data=data;
    p->data = pAssignData(p->data, data); //这个回调函数必须要有返回值，不然赋值会失败（就算申请了堆空间，也需要有指针返回值）

    // 前插
    #if 1
    if (head->prev == head) { // 第一次插入检查
        head->prev = p;
    }
    p->next = head->next;
    p->prev = head;
    head->next->prev = p; // 必须要在前面插入，否则会导致链表单向断裂
    head->next = p;
    #endif

    #if 0
    // 后插
    if (head->next == head) { // 第一次插入检查
        head->next = p;
    }
    p->next = head;
    p->prev = head->prev;
    head->prev->next = p;
    head->prev = p;
    #endif

    return true;
}


// 删除指定数据
bool DeleteLNode(LinkList head, ElemType data, \
             bool (*pEqualData)(ElemType, ElemType)) 
{
    if (NULL == head) {
        perror("LinkList is NULL");
        return false;
    }

    LNode* p = head; // p指向要删除节点的上一个节点
                    //q指向要删除节点的下一个节点（只有找到指定数据才声明并并初始化）

    while (p->next != head)
    {   // 下回调函数u
        // if (p->next->data == data) { // p执行要删除节点的上一个节点
        if (pEqualData(p->next->data, data)) {  // p执行要删除节点的上一个节点
            LNode* q = p->next->next;          //q指向要删除节点的下一个节点
            free(p->next);
            p->next = q;      
            q->prev = p;
            printf("成功删除指定数据!\n");
            return true;
        }
        p = p->next;
    }
    printf("未找到指定数据!");
    return false;
}

/// @brief  
/// @param head 
/// @param pShowData 
/// @return 
// 遍历数据
bool DisplayLinkList(LinkList head, bool (*pShowData)(ElemType)) 
{
    LNode* p = head;
    if (head->next == head) {
        perror("LinkLisk is NULL Error");
        return false;
    }
    printf("下边遍历链表数据:\n");

    // 向前遍历
    #if 0
    while (p != head) {
        pShowData(p->next->data);
        p = p->next;
    }
    #endif

    #if 1
    //向后遍历
    while (p->prev != head) {
        pShowData(p->prev->data);
        p = p->prev;
    }
    #endif

    return true;
}