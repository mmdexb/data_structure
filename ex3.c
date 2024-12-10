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
#define MAXSIZE 100
typedef int Status;

typedef struct 
{
   char name[20];
   char sex;
}Person;

typedef struct{
    Person *base;//数组
    int front;
    int rear;

}SqQueue;

//队列初始化
Status InitQueue(SqQueue *Q)
{
    Q->base=(Person *)malloc(sizeof(Person)*MAXSIZE);
    if (Q->base==NULL)
    {
       return ERROR;
    }
    
    Q->front=Q->rear=0;
    return OK;
}

//获取队列长度
int GetLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}
//入队
Status EnQueue(SqQueue *Q,Person e){
    if ((Q->rear+1)%MAXSIZE==Q->front)
    {
        return ERROR;
    }
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXSIZE;
}

//出队
Status DeQueue(SqQueue *Q,Person *e){
    if (Q->front==Q->rear)
    {
        return ERROR;
    }
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAXSIZE;
}

//取队头
Status GetHead(SqQueue Q,Person *e){
    if (Q.front==Q.rear)
    {
        return ERROR;
    }
    *e=Q.base[Q.front];
    return OK;
}

int is_empty(SqQueue Q){
    return Q.front==Q.rear;
}

SqQueue Mdancers,Fdancers;

void DancerPartner(Person dancer[],int n)
{
    Person p;
    //初始化
    InitQueue(&Mdancers);
    InitQueue(&Fdancers);

    //将所有人分性别入队
    for (int i = 0; i < n; i++)
    {
        p=dancer[i];
        if (p.sex=='M')
        {
            EnQueue(&Mdancers,p);
        }
        else
        {
            EnQueue(&Fdancers,p);
        }

    }
    printf("配对如下:\n");
    while (!is_empty(Mdancers)&&!is_empty(Fdancers))
    {
        DeQueue(&Mdancers,&p);
        printf("%s ",p);
        DeQueue(&Fdancers,&p);
        printf("%s\n",p);
    }

    if (!is_empty(Mdancers))
    {
        GetHead(Mdancers,&p);
        printf("下一位第一个得到舞伴的男士为: %s\n",p.name);
        return;
    }

    if (!is_empty(Fdancers))
    {
        GetHead(Fdancers,&p);
        printf("下一位第一个得到舞伴的女士为: %s\n",p.name);
        return;
    }
    

    
}

int main()
{
    SetConsoleOutputCP(65001);
    Person dancer[5]={{"张三",'M'},{"李四",'F'},{"王五",'M'},{"赵六",'F'},{"钱七",'M'}};
    DancerPartner(dancer,5);
    return 0;
}