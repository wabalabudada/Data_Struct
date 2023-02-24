#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g.h"


//创建空栈
stack MakeNull()
{
    stack S=(stack)malloc(sizeof(struct STACK));
    S->next=NULL;
    return S;
}

//检查栈是否为空（空返回1，否则返回0）
int Empty(stack S)
{
    if(S->next==NULL) return 1;
    return 0;
}

//入栈
void push(stack S,char item[])
{
    stack new=(stack)malloc(sizeof(struct STACK));
    strcpy(new->item,item);
    new->next=S->next;
    S->next=new;
}

//出栈（无返回值）
void pop(stack S)
{
    if(Empty(S))    ERR();
    stack tmp=S->next;
    S->next=tmp->next;
    free(tmp);
}

//遍历栈，输出(从栈顶到栈尾)
void output(stack S)
{
    while(S->next!=NULL)
    {
        printf("%s ",S->next->item);
        S=S->next;
    }
    puts("");
}

//返回栈顶元素的值
char *top(stack S)
{
    if(!Empty(S))
        return S->next->item;
    else ERR();
}

//逆置
void Reversal(stack S)
{
    stack tmp=MakeNull();
    while(!Empty(S))
    {
        push(tmp,S->next->item);
        pop(S);
    }
    S->next=tmp->next;
}

