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
#define MAXSIZE 4000
typedef int Status;

typedef struct {
    int key;
    int info;
} ElemType;

typedef struct {
    ElemType r[MAXSIZE+1]; // 数组
    int length; // 长度
} SqList;

// 冒泡排序
void BubbleSort(SqList *L) {
    int i, j;
    ElemType temp;
    for (i = 1; i <= L->length; i++) {
        for (j = L->length; j >= i; j--) {
            if (L->r[j].key < L->r[j-1].key) {
                temp = L->r[j];
                L->r[j] = L->r[j-1];
                L->r[j-1] = temp;
            }
        }
    }
}
void ImprovedBubbleSort(SqList *L) {
    int m =L->length-1;
    int flag =1;
    while(m>0 && flag==1){
        flag = 0;
        for (int j =1;j<=m;j++){
            if (L->r[j].key > L->r[j+1].key) {
                flag = 1;
                ElemType t =L->r[j];
                L->r[j] = L->r[j+1];
                L->r[j+1] = t;
            }
        }
        m--;
    }
}

// 快速排序第一趟
int Partition(SqList *L, int low, int high) {
    L->r[0] = L->r[low];
    int pivotkey = L->r[low].key;
    while (low<high)
    {
        while (low<high && L->r[high].key >= pivotkey)
        {
            --high;
        }
        L->r[low] = L->r[high];
        while (low<high && L->r[low].key <= pivotkey)
        {
            ++low;
        }
        L->r[high] = L->r[low];
    } 
    L->r[low] = L->r[0];
    return low;
}
// 快速排序
void QSort(SqList *L, int low, int high) {
    int pivot;
    if (low<high)
    {
        pivot = Partition(L, low, high);
        QSort(L, low, pivot-1);
        QSort(L, pivot+1, high);
    }
}

// 堆调整
void HeapAdjust(SqList *L, int s, int m) {
    ElemType rc = L->r[s];
    for (int j = 2*s; j <=m; j*=2)
    {
        if (j<m && L->r[j].key < L->r[j+1].key)
        {
            ++j;
        }
        if (rc.key >= L->r[j].key)
        {
            break;
        }
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = rc;
}
// 创建堆
void CreateHeap(SqList *L) {
    int n = L->length;
    for (int i = n/2; i >= 1; i--)
    {
        HeapAdjust(L, i, n);
    }

}

// 堆排序
void HeapSort(SqList *L) {
    int n = L->length;
    CreateHeap(L);
    for (int i = n; i >= 2; i--)
    {
        ElemType temp = L->r[1];
        L->r[1] = L->r[i];
        L->r[i] = temp;
        HeapAdjust(L, 1, i-1);
    }
}

#include <time.h>

// 生成升序数据
void GenerateAscendingData(SqList *L, int N) {
    L->length = N;
    for (int i = 1; i <= N; i++) {
        L->r[i].key = i;
    }
}

// 生成降序数据
void GenerateDescendingData(SqList *L, int N) {
    L->length = N;
    for (int i = 1; i <= N; i++) {
        L->r[i].key = N - i + 1;
    }
}

// 生成随机数据
void GenerateRandomData(SqList *L, int N) {
    L->length = N;
    srand((unsigned)time(NULL)); // 设置随机种子
    for (int i = 1; i <= N; i++) {
        L->r[i].key = rand() % 10000; // 控制随机数范围
    }
}



void PrintArray(SqList *L) {
    for (int i = 1; i <= 10; i++) {
        printf("%d ", L->r[i].key);
    }
    printf("\n");
}

int main() {
    SetConsoleOutputCP(65001); // 设置控制台为 UTF-8
    SqList list;
    int N = 3000;
    clock_t start, end;

    printf("冒泡排序性能测试\n");

    // 升序数据
    printf("生成升序数据\n");
    GenerateAscendingData(&list, N);
    printf("开始升序数据冒泡排序\n");
    start = clock();
    BubbleSort(&list);
    end = clock();
    printf("升序数据冒泡排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    // 降序数据
    printf("生成降序数据\n");
    GenerateDescendingData(&list, N);
    printf("开始降序数据冒泡排序\n");
    start = clock();
    BubbleSort(&list);
    end = clock();
    printf("降序数据冒泡排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    // 随机数据
    printf("生成随机数据\n");
    GenerateRandomData(&list, N);
    printf("开始随机数据冒泡排序\n");
    start = clock();
    BubbleSort(&list);
    end = clock();
    printf("随机数据冒泡排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);
    printf("------------------------------------------------------------\n");
    printf("改进冒泡排序性能测试\n");

    // 升序数据
    printf("生成升序数据\n");
    GenerateAscendingData(&list, N);
    printf("开始升序数据改进冒泡排序\n");
    start = clock();
    ImprovedBubbleSort(&list);
    end = clock();
    printf("升序数据改进冒泡排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    // 降序数据
    printf("生成降序数据\n");
    GenerateDescendingData(&list, N);
    printf("开始降序数据改进冒泡排序\n");
    start = clock();
    ImprovedBubbleSort(&list);
    end = clock();
    printf("降序数据改进冒泡排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    // 随机数据
    printf("生成随机数据\n");
    GenerateRandomData(&list, N);
    printf("开始随机数据改进冒泡排序\n");
    start = clock();
    ImprovedBubbleSort(&list);
    end = clock();
    printf("随机数据改进冒泡排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);
    printf("------------------------------------------------------------\n");
    printf("快速排序性能测试\n");

    // 升序数据
    printf("生成升序数据\n");
    GenerateAscendingData(&list, N);
    printf("开始升序数据快速排序\n");
    start = clock();
    QSort(&list, 1, N);
    end = clock();
    printf("升序数据快速排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    // 降序数据
    printf("生成降序数据\n");
    GenerateDescendingData(&list, N);
    printf("开始降序数据快速排序\n");
    start = clock();
    QSort(&list, 1, N);
    end = clock();
    printf("降序数据快速排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    // 随机数据
    printf("生成随机数据\n");
    GenerateRandomData(&list, N);
    printf("开始随机数据快速排序\n");
    start = clock();
    QSort(&list, 1, N);
    end = clock();
    printf("随机数据快速排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);
    printf("------------------------------------------------------------\n");
    printf("堆排序性能测试\n");

    // 升序数据
    printf("生成升序数据\n");
    GenerateAscendingData(&list, N);
    printf("开始升序数据堆排序\n");
    start = clock();
    HeapSort(&list);
    end = clock();
    printf("升序数据堆排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    // 降序数据
    printf("生成降序数据\n");
    GenerateDescendingData(&list, N);
    printf("开始降序数据堆排序\n");
    start = clock();
    HeapSort(&list);
    end = clock();
    printf("降序数据堆排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    // 随机数据
    printf("生成随机数据\n");
    GenerateRandomData(&list, N);
    printf("开始随机数据堆排序\n");
    start = clock();
    HeapSort(&list);
    end = clock();
    printf("随机数据堆排序用时: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("排序后前10个元素: ");
    PrintArray(&list);

    getchar();
    return 0;
}