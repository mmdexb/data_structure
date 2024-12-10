#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 1000
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef struct PNode
{
    float coef;         // 系数
    int expn;           // 指数
    struct PNode *next; // 指针域
} PNode, *Polynomial;

// 创建多项式
Status CreatePolyn(Polynomial *P, int n)
{
    *P = (Polynomial)malloc(sizeof(PNode));
    if (!(*P))
    {
        return OVERFLOW;
    }
    (*P)->next = NULL;

    for (int i = 0; i < n; i++)
    {
        PNode *s = (PNode *)malloc(sizeof(PNode));
        if (!s)
        {
            return OVERFLOW;
        }
        s->next = NULL;

        // 清除输入缓冲区
        while (getchar() != '\n');

        printf("请输入多项式的系数: ");
        scanf("%f", &s->coef);

        printf("请输入多项式的指数: ");
        scanf("%d", &s->expn);

        PNode *pre = *P;      // 初始化为 q 的前驱
        PNode *q = (*P)->next; // q 初始化，指向首元结点

        // 查找插入位置
        while (q != NULL && q->expn > s->expn)
        {
            pre = q;
            q = q->next;
        }

        // 插入节点
        s->next = q;
        pre->next = s;
    }
    return OK;
}

void PrintPoly(PNode *P)
{
    PNode *p = P->next;
    while (p != NULL)
    {
        printf("%.1fx^%d", p->coef, p->expn);
        p = p->next;
        if (p != NULL)
        {
            printf(" + ");
        }
    }
    printf("\n");
}

Status PolyAdd(PNode *Pa, PNode *Pb)
{
    PNode *P1 = Pa->next; // Pa链表第一有效结点
    PNode *P2 = Pb->next; // Pb链表第一有效结点
    PNode *P3 = Pa;       // Pa链表作为结果链表，插入结点位置

    while (P1 != NULL && P2 != NULL)
    {
        if (P1->expn == P2->expn)
        {
            float sum = P1->coef + P2->coef;
            if (sum != 0.0)
            {
                P1->coef = sum;
                P3->next = P1;
                P3 = P1;
                P1 = P1->next;
                PNode *temp = P2;
                P2 = P2->next;
                free(temp);
            }
            else
            {
                PNode *temp1 = P1;
                PNode *temp2 = P2;
                P1 = P1->next;
                P2 = P2->next;
                free(temp1);
                free(temp2);
            }
        }
        else if (P1->expn > P2->expn) // Pa当前节点的指数大于Pb
        {
            P3->next = P1;
            P3 = P1;
            P1 = P1->next;
        }
        else
        {
            P3->next = P2;
            P3 = P2;
            P2 = P2->next;
        }
    }
    P3->next = P1 ? P1 : P2;

    // 释放Pb的头节点
    free(Pb);
    return OK;
}

int main()
{
    int n1;
    printf("请输入多项式1的项数: ");
    scanf("%d", &n1);

    Polynomial P1;
    CreatePolyn(&P1, n1);

    // 输出多项式1
    printf("多项式1为: ");
    PrintPoly(P1);

    int n2;
    printf("请输入多项式2的项数: ");
    scanf("%d", &n2);
    Polynomial P2;
    CreatePolyn(&P2, n2);

    // 输出多项式2
    printf("多项式2为: ");
    PrintPoly(P2);

    // 相加结果
    PolyAdd(P1, P2);
    printf("多项式1和多项式2相加的结果为: ");
    PrintPoly(P1);

    return 0;
}
