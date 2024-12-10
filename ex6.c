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
#define MAXVEX 100
typedef int Status;
int visited[MAXVEX];

typedef struct ArcNode // 边表结点
{
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode // 顶点表结点
{
    int data;
    ArcNode *firstarc;
} VNode, AdjList[MAXVEX];

typedef struct // 图的邻接表结构
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

int LocateVex(ALGraph G, int v)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data == v)
        {
            return i;
        }
    }
    return -1;
}

Status CreateUDG(ALGraph *G)
{
    printf("请输入顶点数和边数：");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int i = 0; i < G->vexnum; ++i)
    {
        printf("请输入顶点%d的数据：", i);
        scanf("%d", &G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
    }
    for (int i = 0; i < G->arcnum; ++i)
    {
        printf("请输入边%d的两个顶点：", i);
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        int k = LocateVex(*G, v1);
        int j = LocateVex(*G, v2);
        // 头插法 将新节点p1插入到顶点k的边表头部
        ArcNode *p1 = (ArcNode *)malloc(sizeof(ArcNode));
        p1->adjvex = j;
        p1->nextarc = G->vertices[k].firstarc;
        G->vertices[k].firstarc = p1;
        // 对称插入
        ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));
        p2->adjvex = k;
        p2->nextarc = G->vertices[j].firstarc;
        G->vertices[j].firstarc = p2;
    }
    return OK;
}

void DFS(ALGraph G, int v)
{
    printf("%d ", G.vertices[v].data);
    visited[v] = 1;
    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL)
    {
        int w = p->adjvex;
        if (!visited[w])
        {
            DFS(G, w);
        }
        p = p->nextarc;
    }
}

void BFS(ALGraph G, int v)
{
    int queue[MAXVEX];
    int front = 0, rear = 0;
    printf("%d ", G.vertices[v].data);
    //重置标记数组
    for (int i = 0; i < G.vexnum; i++)
    {
        visited[i] = 0;
    }
    visited[v] = 1;
    queue[rear++] = v; //入队
    while (front != rear)
    {
        int u = queue[front++]; //出队
        ArcNode *p = G.vertices[u].firstarc;
        while (p != NULL)
        {
            int w = p->adjvex;
            if (!visited[w])
            {
                printf("%d ", G.vertices[w].data);
                visited[w] = 1;
               queue[rear++] = w; //入队
            }
            p = p->nextarc;
        }
    }
}


int main()
{
    SetConsoleOutputCP(65001);
    ALGraph G;
    CreateUDG(&G);
    printf("深度优先遍历：");
    DFS(G, 0);
    printf("\n");
    printf("广度优先遍历：");
    BFS(G, 0);
    getchar();
    return 0;
}