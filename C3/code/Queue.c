#include "g.h"

//����һ���ն���
queue MakeNullQueue()
{
    queue Q;
    Q.front=MaxSize-1;
    Q.rear=MaxSize-1;
    return Q;
}

//�������Ƿ�Ϊ��
int Empty(queue Q)
{
    return Q.rear==Q.front;
}

//���ض���Ԫ��
Btree Front(queue Q)
{
    if(Empty(Q))    return NULL;
    return Q.data[(Q.front+1)%MaxSize];
}

//���
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

//����
void DeQueue(queue *Q)
{
    if(Empty(*Q))
        printf("The queue is empty.\n");
    else
        Q->front=(Q->front+1)%MaxSize;
}

