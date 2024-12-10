#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量

typedef struct {
    int *base;
    int *top;
    int stacksize;
}SqStack;

//初始化栈
Status InitStack(SqStack *S) {
    S->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if(!S->base) exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

//判断是否为空
int is_empety(SqStack S) {
    return S.base == S.top;
}

//出栈
Status Pop(SqStack *S, int *e){
    if (S->base==S->top){
        return ERROR;
    }
    S->top--;
    *e = *S->top;
}

//入栈
Status Push(SqStack *S,int e){
    if (S->top-S->base==S->stacksize){
        return ERROR;
    }
    *S->top = e;
    *S->top++;
}

//十进制N转r进制
void N2R(int n,int r){
    //初始化栈
    SqStack S;
    InitStack(&S);

    char ch[]= {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    if(r!=2&&r!=8&&r!=16){
        printf("r必须为2、8、16");
        return;
    }

    //辗转相除
    while(n){
        Push(&S,n%r);
        n=n/r;
    }
    printf("转换结果为：\n");
    while (!is_empety(S))
    {
        int e;
        Pop(&S,&e);
        printf("%c",ch[e]);

    }
    
}

int main(){
    SetConsoleOutputCP(65001);
    int n,r;
    printf("请输入要转换的十进制数：");
    scanf("%d",&n);
    printf("请输入要转换的进制：");
    scanf("%d",&r);
    N2R(n,r);
    system("pause");
    return 0;
}