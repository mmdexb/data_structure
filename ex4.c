#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
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

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;


Status InitTree(BiTree* T){
    *T = NULL;
    return OK;
}

Status CreateTree(BiTree* T){
    TElemType ch;
    printf("请输入节点值，#表示没有节点：\n");
    scanf("%c",&ch);
    getchar();
    if (ch=='#')
    {
        *T=NULL;
    }else{
        *T=(BiTree)malloc(sizeof(BiTNode));
        if (*T==NULL)
        {
            return OVERFLOW;
        }
        (*T)->data=ch;
        printf("请输入%c的左子节点：\n",ch);
        CreateTree(&(*T)->lchild);
        printf("请输入%c的右子节点：\n",ch);
        CreateTree(&(*T)->rchild);
    }
    
}

void PreOrderTraverse(BiTree T){
    if (T){
        printf("%c ",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
    
}

void InOrderTraverse(BiTree T){
    if (T){
        InOrderTraverse(T->lchild);
        printf("%c ",T->data);
        InOrderTraverse(T->rchild);
    }
    
}

void PostOrderTraverse(BiTree T){
    if (T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c ",T->data);
    }
    
}

int TreeDepth(BiTree T){
    if (T==NULL)
    {
        return 0;
    }
    int left=TreeDepth(T->lchild);
    int right=TreeDepth(T->rchild);
    if(left>right){
        return left+1;
    }else{
        return right+1;
    }
    
}

int CountLeaves(BiTree T){
    if (T==NULL)
    {
        return 0;
    }
    if (T->lchild==NULL&&T->rchild==NULL)
    {
        return 1;
    }
    return CountLeaves(T->lchild)+CountLeaves(T->rchild);
}


int main(){
    SetConsoleOutputCP(65001);
    BiTree T;
    InitTree(&T);
    CreateTree(&T);
    printf("先序遍历：\n");
    PreOrderTraverse(T);
    printf("\n");
    printf("中序遍历：\n");
    InOrderTraverse(T);
    printf("\n");
    printf("后序遍历：\n");
    PostOrderTraverse(T);
    printf("\n");
    printf("树的深度为：%d\n",TreeDepth(T));
    printf("叶子节点的个数为：%d\n",CountLeaves(T));
    getchar();
    return 0;
}