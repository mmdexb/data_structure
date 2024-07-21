#include <stdio.h>
#define LIST_INIT_SIZE 1000 //线性表存储空间的初始分配量
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef char ElemType;

typedef struct LNode 
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;  //LinkList为Node类型的指针

// 初始化
Status initList(LinkList L){
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    return OK;
}

//单链表的销毁
Status DestroyList(LinkList L){
    LinkList p;
    while((L)!=NULL){
        p=L;
        (L)=(L)->next;
        free(p);
    }
    return OK;
}

//单链表的清空
Status ClearList(LinkList L){
    LinkList p,q;
    p=L->next;
    while(p==NULL){
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
    return OK;
}

//单链表的表长
int ListLenth(LinkList L){
    LinkList p=L;
    int count=0;
    while(p!=NULL){
        p=p->next;
        count++;
    }
    return count;
}

//单链表的取第i个元素
Status GetElem(LinkList L,int i,ElemType *e){
    LinkList p=L->next;
    int j=1;
    while(p!=NULL&&j<i){
        p=p->next;
        j++;
    }
    if(p==NULL||j>i){
        return ERROR;
    }
    e=p->data;
    return OK;
}

//单链表按值查找
//返回数据的位置
LinkList LocalElem(LinkList L,ElemType e){
    LinkList p=L->next;
    while(p!=NULL&&p->data!=e){
        p=p->next;
    }
    return p;
}

//返回数据的位置序号
int LocalElem2(LinkList L,ElemType e){
    LinkList p=L->next;
    int j=1;
    while(p->data!=e&&p!=NULL){
        p=p->next;
        j++;
    }
    if(p==NULL){
        return 0;
    }else {
        return j;
    }
}

//在第i个节点前插入e
Status ListInsert(LinkList L,int i,ElemType e){
    LinkList p=L;
    int j=0;
    while (p!=NULL&&j<i-1)//寻找第i-1个节点，使得要插入节点与其链接
    {
        p=p->next;
        j++;
    }
    if(p==NULL||j>i-1){ //i不合法
        return ERROR;
    }
    LinkList s=(LinkList)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
    
}

//删除第i个节点
Status ListDelete(LinkList L,int i,ElemType *e){
    LinkList p=L;
    int j=0;
    while(p->next!=NULL&&j<i-1){ //到达要删除节点的前一个
        p=p->next;
        j++;
    }
    if(p->next==NULL||j>i-1){
        return ERROR;
    }
    LinkList q=p->next;
    p->next=p->next->next;
    e=q->data;
    free(q);
    return OK;
}

//头插法
void CreateList_H(LinkList L,int n){
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    for(int i=0;i<n;i++){
        LinkList p=(LinkList)malloc(sizeof(LNode));
        scanf(&p->data);
        p->next=L->next; //把头节点后面的一串接到p的next上
        L->next=p; //连接到头节点

    }

}

//尾插法
void CreateList_R(LinkList L,int n){
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    LinkList r=L;
    for(int i=0;i<n;i++){
        LinkList p=(LinkList)malloc(sizeof(LNode));
        p->next=NULL;
        scanf(&p->data);
        r->next=p; //插入到表尾
        r=p; //更新最新的表尾
    }
}

LinkList Connect(LinkList Ta,LinkList Tb){
    LinkList p=Ta->next; //p暂存为Ta的头节点
    Ta->next=Tb->next->next; //将Ta的的尾节点连接到Tb的第一个具有数值的节点（头节点的下一个）
    free(Tb->next);//释放Tb的头节点
    Tb->next=p;//将Tb的尾节点连接到Ta的头节点
    return Tb;
}

typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior,*next;
}DuLNode,*DuLinkList;

DuLinkList GetElem_DuL(DuLinkList L,int i){
    DuLinkList p=L;
    int j=0;
    while (p->next!=NULL&&j<i+1)
    {
        p=p->next;
        j++;
    }
    return p;
}

void ListInsert_DuL(DuLinkList L,int i,ElemType e){
    DuLinkList p=GetElem_DuL(L,i);
    if(p==NULL){
        return ERROR;
    }
    DuLinkList s=(DuLinkList)malloc(sizeof(DuLNode));
    s->data=e;
    s->prior=p->prior; //将要插入的节点的前驱节点改为原节点的前驱节点
    p->prior->next=s; //将原节点的前驱节点的后驱节点改为要插入的节点
    s->next=p; //要插入的节点后驱节点改为原节点
    p->prior=s; //原节点的前驱节点改为要插入的节点

    return OK;
}

void ListDelete_DuL(DuLinkList L,int i,ElemType *e){
    DuLinkList p=GetElem_DuL(L,i);
    if(p==NULL){
        return ERROR;
    }
    e=p->data;
    p->prior->next=p->next;
    p->next->prior=p->prior;
    free(p);
    return OK;
}