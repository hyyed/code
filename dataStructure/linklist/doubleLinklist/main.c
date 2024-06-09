#include "linklist/linklist.h"
#include "callBackLinkList/callBackLinkList.h"

int main(int argc, char* argv[]) 
{
    // 创建链表
    LinkList head = CreatLinkList();
    // 回调，展示数据
    bool (*pShowData)(ElemType) = &ShowData;
    // 回调，数据赋值
    ElemType (*pAssignData)(ElemType, ElemType) = &AssignData;
    DisplayLinkList(head, pShowData);

    // 插入数据
    InsertNode(head, 10, pAssignData);
    InsertNode(head, 20, pAssignData);
    InsertNode(head, 30, pAssignData);
    InsertNode(head, 40, pAssignData);
    InsertNode(head, 50, pAssignData);
    printf("local-data: %d\n", head->next->data);
    DisplayLinkList(head, pShowData);

    // 回调，数据比较
    bool (*pEqualData)(ElemType, ElemType) = &CompareData;
    // 删除数据
    DeleteLNode(head, 20, pEqualData);
    DisplayLinkList(head, pShowData);

    // 销毁链表
    DestroyLinkList(head);

    exit(0);
    return 0;

}