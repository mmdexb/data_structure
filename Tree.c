#include <stdio.h>
#include<Stack.c>
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXQSIZE 100
typedef int Status;
typedef char TElemType;
typedef struct {
    ElemType *base;
    ElemType *top;
    int stacksize;
}SqStack;

typedef struct{
    QElemType *base;//数组
    int front;
    int rear;

}SqQueue;

Status InitStack(SqStack *s){
    s->base=(ElemType *)malloc(sizeof(ElemType)*STACK_INIT_SIZE);
    if(s->base==NULL){
        return OVERFLOW;
    }
    s->base=s->top;
    s->stacksize=STACK_INIT_SIZE;
    return OK;
}

typedef TElemType SqBiTree[MAXQSIZE];
SqBiTree bt;

typedef struct BiNode{
    TElemType data;
    struct BiNode *lchild,*rchild;
}BiNode,*BiTree;
 
typedef struct TriTNode{
    TElemType data;
    struct TriTNode *lchild,*parent,*rchild;
}TriTNode,*TriTree;

Status EntryQueue(SqQueue *Q,ElemType e){
    if((Q->rear +1)%MAXQSIZE==Q->front){ //队列已满
        return ERROR;
    }
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXQSIZE;
    return OK;
}

Status OutQueue(SqQueue *Q,ElemType *e){
    if(Q->rear ==Q->front){ //队列为空
        return ERROR;
    }
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAXQSIZE;
    return OK;
}

Status InitQueue(SqQueue *Q){
    Q->base=(ElemType*)malloc(sizeof(ElemType)*MAXQSIZE);
    if(Q->base==NULL){
        return OVERFLOW;
    }
    Q->front=Q->rear=0;
    return OK;
}
void PreOrder(BiTree T){
    if(T!=NULL){
        printf("%d\t",T->data);
        Pre(T->lchild);
        Pre(T->rchild);
    }
}

void InOrder(BiTree t){
    if(t!=NULL){
        InOder(t->lchild);
        printf("%d\t",t->data);
        InOder(t->rchild);
    }
}

void PostOrder(BiTree t){
    if(t!=NULL){
        PostOrder(t->lchild);
        PostOrder(t->rchild);
        printf("%d\t",t->data);
    }
}

Status InOrder_A(BiTree t){
    BiTree p,q;
    SqStack s;
    InitStack(&s);
    p=t;
    while(p!=NULL||s.base!=s.top){
        if(p!=NULL){
            Push(&s,p);
            p=p->lchild;
        }else{
            Pop(&s,q);
            printf("%c",q->data);
            p=q->rchild;
        }
    }
    return OK;
}

void LevelOrder(BiNode *b){
    BiNode *p;
    SqQueue *qu;
    InitQueue(qu);
    EntryQueue(qu,b);
    while(qu->front!=qu->rear){
        OutQueue(qu,p);
        printf("%c",p->data);
        if(p->lchild!=NULL){
            EntryQueue(qu,p->lchild);
        }
        if(p->rchild!=NULL){
            EntryQueue(qu,p->rchild);
        }
    }
}

Status CreateBiiTree(BiTree *T){
    char ch =scanf(&ch);
    if(ch=='#'){
        *T=NULL;
    }else{
        if((T=(BiNode *)malloc(sizeof(BiNode)))!=NULL){
            return OVERFLOW;
        }
        (*T)->data=ch;
        CreateBiiTree(&(*T)->lchild);
        CreateBiiTree(&(*T)->rchild);
    }
    return OK;

}

void Copy(BiTree *Tnew, const BiTree T) {
    if (!T) {
        *Tnew = NULL;
        return;
    } else {
        *Tnew = (BiTree)malloc(sizeof(BiNode));
        (*Tnew)->data = T->data;
        Copy(&(*Tnew)->lchild, T->lchild);
        Copy(&(*Tnew)->rchild, T->rchild);
    }
}