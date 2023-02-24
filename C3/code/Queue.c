#include "g.h"

//创建一个空队列
queue MakeNullQueue()
{
    queue Q;
    Q.front=MaxSize-1;
    Q.rear=MaxSize-1;
    return Q;
}

//检查队列是否为空
int Empty(queue Q)
{
    return Q.rear==Q.front;
}

//返回队首元素
Btree Front(queue Q)
{
    if(Empty(Q))    return NULL;
    return Q.data[(Q.front+1)%MaxSize];
}

//入队
int EnQueue(Btree x,queue *Q)
{
    if((Q->rear+1)%MaxSize==Q->front)
    {
        printf("The queue is full\n");
        exit(1);
    }    
    else
    {
        if(x==NULL) return 0;
        Q->rear=(Q->rear+1)%MaxSize;
        Q->data[Q->rear]=x;
        return 1;
    }
}

//出队
void DeQueue(queue *Q)
{
    if(Empty(*Q))
        printf("The queue is empty.\n");
    else
        Q->front=(Q->front+1)%MaxSize;
}

