#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXVEX 100

typedef int Status;

typedef struct {
    int key;
    int info;
} ElemType;

typedef struct {
    ElemType *R; 
    int length;  
} SSTable;

// 初始化顺序表
Status InitTable(SSTable *ST, int size) {
    ST->R = (ElemType *)malloc((size + 1) * sizeof(ElemType)); // 多分配一个空间，索引从 1 开始
    if (!ST->R) {
        printf("存储分配失败！\n");
        return OVERFLOW;
    }
    ST->length = size;
    return OK;
}

// 创建顺序表（按升序初始化键值）
void CreateTable(SSTable *ST) {
    for (int i = 1; i <= ST->length; i++) {
        printf("请输入第 %d 个元素的键值和信息：", i);
        scanf("%d %d", &ST->R[i].key, &ST->R[i].info);
        getchar();
    }
}

// 二分查找
int Search_Bin(SSTable ST, int key) {
    int low, high, mid;
    low = 1;
    high = ST.length;
    while (low <= high) {
        mid = (low + high) / 2;
        if (key == ST.R[mid].key)
            return mid;
        else if (key < ST.R[mid].key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0; // 查找失败返回 0
}

int main() {
    SetConsoleOutputCP(65001);
    SSTable ST;
    int size, key, result;

    printf("请输入表的大小：");
    scanf("%d", &size);
    getchar();
    if (InitTable(&ST, size) != OK) {
        return ERROR;
    }
    CreateTable(&ST);
    printf("请输入要查找的键值：");
    scanf("%d", &key);

    result = Search_Bin(ST, key);
    if (result != 0) {
        printf("查找成功！键值 %d 在表中的位置是 %d，信息是 %d。\n", key, result, ST.R[result].info);
    } else {
        printf("查找失败！表中没有键值 %d。\n", key);
    }
    free(ST.R);
    getchar();
    return 0;
}
