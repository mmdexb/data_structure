#include <stdio.h>

int main() {
    double a, b, c, x;
    int n;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &x);
    double total_weight = a + b + c;

    // 实现向上取整
    n = (int)(total_weight / x);
    if ((total_weight / x) > n) {
        n += 1;
    }
    printf("%d\n", n);

    return 0;
}
