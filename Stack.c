#include <stdio.h>
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef char ElemType;

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量
typedef struct {
    ElemType *base;
    ElemType *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack *s){
    s->base=(ElemType *)malloc(sizeof(ElemType)*STACK_INIT_SIZE);
    if(s->base==NULL){
        return OVERFLOW;
    }
    s->base=s->top;
    s->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *s,ElemType e){
    if(s->top-s->base==s->stacksize){ //栈满
        return ERROR;
    }
    *(s->top++)=e;
    return OK;

}

Status Pop(SqStack *s,ElemType *e){
    if(s->base==s->top){
        return ERROR; //栈空
    }
    e=*(--s->top);
    return OK;
}

Status GetTop(SqStack S, ElemType e){ 
    //若栈不空，则用e返回S的栈顶元素，并返回OK
    if (S.top == S.base){ // 空栈
        return ERROR;
    }
    e = *(S.top-1); //返回非空栈中栈顶元素
    return OK;
} //GetTop


typedef struct StackNode{
    ElemType data;
    struct StackNode *next;
}StackNode, *LinkStack;

Status push_L(LinkStack *S,ElemType e){
    LinkStack p;
    p=(LinkStack *)malloc(sizeof(StackNode));
    p->data=e;
    p->next=*S;
    *S=p; //修改栈顶元素

}

Status pop_l(LinkStack *S,ElemType *e){
    LinkStack p=*S;
    *e=(*S)->data;
    *S=(*S)->next;
    free(p);
    return OK;
}