#include <stdio.h>
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXQSIZE 100
typedef int Status;
typedef char QElemType;

typedef struct{
    QElemType *base;//数组
    int front;
    int rear;

}SqQueue;

Status InitQueue(SqQueue *Q){
    Q->base=(QElemType*)malloc(sizeof(QElemType)*MAXQSIZE);
    if(Q->base==NULL){
        return OVERFLOW;
    }
    Q->front=Q->rear=0;
    return OK;
}

int QueueLenth(SqQueue *Q){
    return((Q->rear-Q->front+MAXQSIZE)%MAXQSIZE);
}

Status EntryQueue(SqQueue *Q,QElemType e){
    if((Q->rear +1)%MAXQSIZE==Q->front){ //队列已满
        return ERROR;
    }
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXQSIZE;
    return OK;
}

Status OutQueue(SqQueue *Q,QElemType *e){
    if(Q->rear ==Q->front){ //队列为空
        return ERROR;
    }
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAXQSIZE;
    return OK;
}

typedef struct QNode{
    QElemType data;
    QNode *next;
}QNode;

typedef struct LinkedQueue{
    QNode *front; //链表的头指针
    QNode *rear; //指向链表的最后一个节点
}LinkedQueue;

Status EntryQueue_L(LinkedQueue *Q,QElemType e){
    QNode *node=(QNode*)malloc(sizeof(QNode));
    if(node==NULL){
        return OVERFLOW;
    }
    node->data=e;
    node->next=NULL;
    Q->rear->next=node;
    Q->rear=node;
    return OK;
}

Status OutQueue_L(LinkedQueue *Q,QElemType *e){
    if(Q->front==Q->rear){
        return ERROR;
    }
    QNode *node=Q->front->next;
    *e=node->data;
    Q->front->next=node->next;
    if(Q->rear==node){ //队列中最后一个离开，则变为空队列
        Q->rear=Q->front;
    }
    free(node);
    return OK;
}