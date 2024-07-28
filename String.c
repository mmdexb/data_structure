#include <stdio.h>
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXLEN 255
#define CHUNKSIZE 80
typedef int Status;
typedef char ElemType;

typedef struct{
    char ch[MAXLEN-1]; //存储串的一维数组
    int length;
}SString; //顺序存储字符串

typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk;

typedef struct{
    Chunk *head;
    Chunk *tail;
    int curlen;
}LString;

int Index_BF(SString S,SString T){
    int i=1;
    int j=1;
    while(i<=S.length&&j<=T.length){
        if(S.ch[i]==T.ch[j]){
            i++;
            j++;
        }else{ //被查找串与模式串指针游标回溯
            i=i-j+2;
            j=1;
        }
    }
    if(j>=T.length){
        return i-T.length; //返回匹配成功后的匹配的第一个字符的下标
    }else{
        return 0;
    }
}