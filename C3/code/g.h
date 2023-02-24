#ifndef g_h
#define g_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 100   //队列的最大长度

//树中元素的型
typedef char elemtype;

//树的结点的存储结构
typedef struct NODE
{
    struct NODE *lchild;
    struct NODE *rchild;
    elemtype data;
}node,*Btree;

//队列的存储结构
typedef struct QUEUE
{
    Btree data[MaxSize];
    int front;
    int rear;
}queue;

//栈的存储结构
struct STACK
{
    Btree nd;
    struct STACK * next;
    int flag;
};
typedef struct STACK* stack;

Btree CreatBT();
void PreOrder(Btree T);
void InOrder(Btree T);
void PostOrder(Btree T);
void LeverOrder(Btree T);
void Output(char descr[],void Way(Btree T),Btree T);
Btree Copy(Btree T);
int MaxWidth(Btree T);
int CompleteBTree(Btree T);
void Destroy(Btree T);
void PreOrder_Stack(Btree T);
void InOrder_Stack(Btree T);
void PostOrder_Stack(Btree T);

#endif