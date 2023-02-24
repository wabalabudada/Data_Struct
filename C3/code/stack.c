#include "g.h"

//创建空栈
stack MakeNullStack()
{
    stack S=(stack)malloc(sizeof(struct STACK));
    S->next=NULL;
    return S;
}

//检查栈是否为空（空返回1，否则返回0）
int Empty_Stack(stack S)
{
    return !S->next;
}

//入栈
void push(stack S,Btree nd)
{
    stack new=(stack)malloc(sizeof(struct STACK));
    new->nd=nd;
    new->next=S->next;
    S->next=new;
}

//出栈（无返回值）
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

//返回栈顶元素的值
Btree top(stack S)
{
    if(!Empty_Stack(S))    return S->next->nd;
    else 
    {
        printf("The stack is empty!");
        exit(1);
    }
}
