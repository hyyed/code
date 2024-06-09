#ifndef _CALLBACK_LINKLINST_
#define _CALLBACK_LINKLINST_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* 
    双向链表的 回调函数
 */

#include "../linklist/linklist.h"
// 如果不指明明确数据，在cmake中必须要指定头文件所在路径
// 可是为什么在这个文件的实现中，在linklist.h中定义的类型显示灰色
// #include "linklist.h" 

// 展示节点数据
bool ShowData(ElemType data);
// 比较数据
bool CompareData(ElemType targData, ElemType sourceData);
// 赋值数据
ElemType AssignData(ElemType targData, ElemType sourceData);

#endif