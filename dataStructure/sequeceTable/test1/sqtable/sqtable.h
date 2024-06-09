#ifndef _SQTABLE_H_
#define _SQTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef char ElemType;

typedef struct {
    ElemType* data; //首地址
    int count; //当前元素个数
    int maxSize; //最大容量
} SqTable;

// 创建销毁
SqTable* CreateSqTable(int size);
bool DestroySqTable(SqTable* sqTable);

// 增删改查
bool InsertSqTable(SqTable* sqTable, ElemType data, int pos);
// 删
ElemType DeleteSqTable(SqTable* sqTable, int pos);
// 改
ElemType SetSqTable(SqTable* sqTable, int pos, ElemType data);
// 查
int GetSqTable(SqTable* sqTable, ElemType data);
// 遍历
bool DisplaySq(SqTable* sqTable);


#endif