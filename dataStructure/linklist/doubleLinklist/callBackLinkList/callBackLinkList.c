// #include "callBackLinkList.h"
#include "linklist.h" 

// 展示节点数据
bool ShowData(ElemType data) {
    printf("data:%d\n", data);
    return true;
}

// 比较数据
bool CompareData(ElemType targData, ElemType sourceData) {
    return targData == sourceData;
}

// 赋值数据
ElemType AssignData(ElemType targData, ElemType sourceData) {
    targData = sourceData;
    return targData;
}