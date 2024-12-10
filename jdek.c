
#include <stdio.h>

int main() {
    int N, i, j;
    int a[20][20] = {0};  // 初始化矩阵
    scanf("%d", &N);
    
    int num = 1;  // 计数器，从1开始
    
    for (i = 0; i < N; i++) {
        if (i % 2 == 0) {  // 偶数行，从左到右
            for (j = 0; j < N; j++) {
                a[i][j] = num++;
            }
        } else {  // 奇数行，从右到左
            for (j = N - 1; j >= 0; j--) {
                a[i][j] = num++;
            }
        }
    }
    
    // 输出蛇形矩阵
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%03d ", a[i][j]);  // 每个数字占3列，后跟空格
        }
        printf("\n");
    }

    return 0;
}
