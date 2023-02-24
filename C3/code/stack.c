#include "g.h"

//������ջ
stack MakeNullStack()
{
    stack S=(stack)malloc(sizeof(struct STACK));
    S->next=NULL;
    return S;
}

//���ջ�Ƿ�Ϊ�գ��շ���1�����򷵻�0��
int Empty_Stack(stack S)
{
    return !S->next;
}

//��ջ
void push(stack S,Btree nd)
{
    stack new=(stack)malloc(sizeof(struct STACK));
    new->nd=nd;
    new->next=S->next;
    S->next=new;
}

//��ջ���޷���ֵ��
void pop(stack S)
{
    if(Empty_Stack(S))   
    {
        return ;
    }
    stack tmp=S->next;
    S->next=tmp->next;
    free(tmp);
}

//����ջ��Ԫ�ص�ֵ
Btree top(stack S)
{
    if(!Empty_Stack(S))    return S->next->nd;
    else 
    {
        printf("The stack is empty!");
        exit(1);
    }
}
