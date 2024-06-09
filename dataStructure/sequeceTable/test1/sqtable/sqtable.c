# include "sqtable.h"


SqTable* CreateSqTable(int size) {
    static SqTable* sqTable;
    sqTable = (SqTable*)malloc(sizeof(SqTable));
    sqTable->data = (ElemType*)malloc(size * sizeof(ElemType));
    // bzero(sqTable->data, NULL);
    memset(sqTable->data, 0, sizeof(size * sizeof(ElemType)));
    sqTable->count = 0;
    sqTable->maxSize = MAX_SIZE;
    return sqTable;
}

bool DestroySqTable(SqTable* sqTable) {
    if (NULL == sqTable) {
        perror("sqTable is NULL Error");
        return -1;
    }
    if (NULL == sqTable->data) {
        perror("sqTable->data is NULL Error");
        return -1;
    }
    free(sqTable->data);
    free(sqTable);
    
    return 0;
}

// 增删改查(如果ElemType为指针类型，data为空怎么办)
bool InsertSqTable(SqTable* sqTable, ElemType data, int pos) {
    if (NULL == sqTable) {
        perror("sqTable is NULL Error");
        return false;
    }
    if (pos <= 0 || pos > sqTable->count+1 || sqTable->count == sqTable->maxSize) {
        perror("The current size of the array is");
        return false;
    }
    // 注意i 的范围
    for (int i=sqTable->count; i>=pos; --i) {
        sqTable->data[i] = sqTable->data[i-1];
    }
    sqTable->data[pos-1] = data;
    sqTable->count++;

    return true;
}
// 删
ElemType DeleteSqTable(SqTable* sqTable, int pos) {
    if (NULL == sqTable) {
        perror("sqTable is NULL Error");
        return -1;
    }
    // 超过、小于0、结构体空
    if (pos > sqTable->count || pos <= 0 || sqTable->count == 0) {
        perror("The current size of the array is");
        return -1;
    }

    ElemType tmp = sqTable->data[pos-1];
    for (int i=pos; i<sqTable->count; i++) {
        sqTable->data[i-1] = sqTable->data[i];
        // printf("i=%d\n",i);
        // printf("cnt=%d\n",sqTable->count);
        // printf("%d\n",sqTable->data[i-1]);
        // getchar();
    }
    sqTable->count--;
    return tmp;
}

// 改
ElemType SetSqTable(SqTable* sqTable, int pos, ElemType data) {
    if (NULL == sqTable) {
        perror("sqTable is NULL Error");
        return false;
    }
    if (pos > sqTable->count) {
        perror("The current size of the array is");
        return false;
    }
    ElemType tmp = sqTable->data[pos-1];
    sqTable->data[pos-1] = data;
    return tmp;
}

// 查
int GetSqTable(SqTable* sqTable, ElemType data) {
    if (NULL == sqTable) {
        perror("sqTable is NULL Error");
        return false;
    }

    for (int i=0; i<sqTable->count; ++i) {
        if (sqTable->data[i] == data) {
            return i+1;
        }
    }
    return -1;
}
// 遍历
bool DisplaySq(SqTable* sqTable) {
    if (NULL == sqTable) {
        perror("sqTable is NULL Error");
        return false;
    }

    for (int i=0; i<sqTable->count; ++i) {
        printf("%d ", sqTable->data[i]);
    } 
    printf("\n");


    return true;
}