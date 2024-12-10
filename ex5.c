#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef char TElemType;

// 线索二叉树节点定义
typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    int ltag, rtag; // ltag=1表示前驱，rtag=1表示后继
} BiThrNode, *BiThrTree;

Status InitBiThrTree(BiThrTree *T) {
    *T = NULL;
    return OK;
}

// 创建二叉树
Status CreateBiThrTree(BiThrTree *T) {
    char ch;
    printf("请输入节点值，#表示没有节点：\n");
    scanf(" %c", &ch); // 注意前面的空格以跳过换行符
    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if (*T == NULL) {
            return OVERFLOW;
        }
        (*T)->data = ch;
        (*T)->ltag = 0;
        (*T)->rtag = 0;

        printf("请输入%c的左子节点：\n", ch);
        CreateBiThrTree(&(*T)->lchild);

        printf("请输入%c的右子节点：\n", ch);
        CreateBiThrTree(&(*T)->rchild);
    }
    return OK;
}

BiThrTree pre = NULL;

// 中序线索化
void InThreading(BiThrTree T) {
    if (T) {
        InThreading(T->lchild);

        if (!T->lchild) {
            T->ltag = 1;
            T->lchild = pre;
        }
        if (pre && !pre->rchild) {
            pre->rtag = 1;
            pre->rchild = T;
        }
        pre = T;

        InThreading(T->rchild);
    }
}

// 中序遍历线索二叉树
void InOrderTraverse(BiThrTree T) {
    BiThrTree p = T;
    while (p) {
        // 找到最左节点
        while (p->ltag == 0) {
            p = p->lchild;
        }
        printf("%c ", p->data);

        // 按后继线索遍历
        while (p->rtag == 1 && p->rchild) {
            p = p->rchild;
            printf("%c ", p->data);
        }

        p = p->rchild;
    }
}

int main() {
    SetConsoleOutputCP(65001);
    BiThrTree T;
    InitBiThrTree(&T);

    printf("开始创建二叉树...\n");
    CreateBiThrTree(&T);

    printf("开始中序线索化...\n");
    pre = NULL; // 初始化前驱节点
    InThreading(T);

    printf("中序遍历线索二叉树：\n");
    InOrderTraverse(T);
    getchar();
    return 0;
}
