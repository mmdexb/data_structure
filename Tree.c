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
typedef char ElemType;

typedef struct PTNode{
    ElemType data;
    int parent;
}PTNode;

typedef struct PTree
{
    PTNode nodes[MAXQSIZE];
    int r,n //根节点的位置和个数
};

typedef struct CTNode
{
    int child;
    struct CTNode *next;
}*ChildPtr; //孩子节点

typedef struct{
    ElemType data;
    ChildPtr firstchild;
}CTbox; //双亲节点

typedef struct{
    CTbox nodes[MAXQSIZE];
    int n,r;//根节点数与根节点的位置
}CTree;

typedef struct CSNode{
    ElemType data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;


