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

typedef struct {
    int key;
    int info;
} ElemType;

typedef struct BSTNode {
    ElemType data;
    struct BSTNode *lchild, *rchild; 
} BSNode, *BSTree;

// 初始化单个节点并插入二叉搜索树
void InitBSTree(BSTree *T, ElemType e) {
    if (!(*T)) {
        BSTree S = (BSTree)malloc(sizeof(BSNode));
        S->data = e;
        S->lchild = NULL;
        S->rchild = NULL;
        *T = S;
    } else if (e.key < (*T)->data.key) {
        InitBSTree(&(*T)->lchild, e);
    } else if (e.key > (*T)->data.key) {
        InitBSTree(&(*T)->rchild, e);
    }
}

// 创建二叉搜索树
void CreateBSTree(BSTree *T) {
    *T = NULL;
    ElemType e;
    printf("请输入数据，以-1结束：\n");
    scanf("%d", &e.key);
    while (e.key != -1) {   
        InitBSTree(T, e);
        scanf("%d", &e.key);
    }
}

// 删除二叉搜索树的节点
void DeleteBSTree(BSTree *T, int key) {
    BSTree p = *T, f = NULL, q, s;
    while (p) {
        if (p->data.key == key) {
            break;
        }
        f = p;
        if (key < p->data.key) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    if (!p) {
        printf("未找到键值为 %d 的节点\n", key);
        return;
    }

    q = p;
    if (p->lchild && p->rchild) { // 左右子树均存在
        s = p->lchild;
        while (s->rchild) { // 找前驱
            q = s;
            s = s->rchild;
        }
        p->data = s->data; // 用前驱数据覆盖当前节点
        if (q != p) {
            q->rchild = s->lchild;
        } else {
            q->lchild = s->lchild;
        }
        free(s);
        return;
    } else if (!p->rchild) { // 只有左子树
        p = p->lchild;
    } else if (!p->lchild) { // 只有右子树
        p = p->rchild;
    }

    if (!f) { // 删除的是根节点
        *T = p;
    } else if (q == f->lchild) {
        f->lchild = p;
    } else {
        f->rchild = p;
    }
    free(q);
}

// 搜索二叉搜索树的节点
BSTree SearchBST(BSTree T, int key) {
    if ((!T) || key == T->data.key) {
        return T;
    } else if (key < T->data.key) {               
        return SearchBST(T->lchild, key);
    } else {
        return SearchBST(T->rchild, key);
    }
}

// 中序遍历二叉树
void InOrderTraverse(BSTree T) {
    if (T) {
        InOrderTraverse(T->lchild);
        printf("%d ", T->data.key);
        InOrderTraverse(T->rchild);
    }
}

// 主函数
int main() {
    SetConsoleOutputCP(CP_UTF8);
    BSTree T;
    CreateBSTree(&T);

    printf("二叉搜索树的中序遍历结果：\n");
    InOrderTraverse(T);
    printf("\n");

    int searchKey, deleteKey;
    printf("请输入要搜索的键值：");
    scanf("%d", &searchKey);
    BSTree result = SearchBST(T, searchKey);
    if (result) {
        printf("找到键值为 %d 的节点\n", searchKey);
    } else {
        printf("未找到键值为 %d 的节点\n", searchKey);
    }

    printf("请输入要搜索的键值：");
    scanf("%d", &searchKey);
    result = SearchBST(T, searchKey);
    if (result) {
        printf("找到键值为 %d 的节点\n", searchKey);
    } else {
        printf("未找到键值为 %d 的节点\n", searchKey);
    }

    printf("请输入要删除的键值：");
    scanf("%d", &deleteKey);
    DeleteBSTree(&T, deleteKey);

    printf("删除后的二叉搜索树中序遍历结果：\n");
    InOrderTraverse(T);
    printf("\n");

    return 0;
}
