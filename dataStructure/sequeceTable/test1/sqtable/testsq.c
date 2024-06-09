#include "sqtable.h"

int main(int argc, char* argv[]) {
    SqTable* sqTable = CreateSqTable(5);

    InsertSqTable(sqTable, 'A', 1);
    InsertSqTable(sqTable, 'B', 2);
    InsertSqTable(sqTable, 'C', 3);
    InsertSqTable(sqTable, 'E', 3);

    printf("初识数据: ");
    DisplaySq(sqTable);
    // getchar(); printf("\n");

    InsertSqTable(sqTable, 'J', 1);
    printf("1处插入j: ");
    DisplaySq(sqTable);
    getchar();
    
    printf("删除2:");
    printf("%d\n", DeleteSqTable(sqTable, 2));
    DisplaySq(sqTable);
    getchar();

    printf("j位置:%d\n", GetSqTable(sqTable, 'J'));
    printf("%d\n", DeleteSqTable(sqTable, 3));
    getchar();

    DestroySqTable(sqTable);
}