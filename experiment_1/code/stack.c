#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g.h"


//������ջ
stack MakeNull()
{
    stack S=(stack)malloc(sizeof(struct STACK));
    S->next=NULL;
    return S;
}

//���ջ�Ƿ�Ϊ�գ��շ���1�����򷵻�0��
int Empty(stack S)
{
    if(S->next==NULL) return 1;
    return 0;
}

//��ջ
void push(stack S,char item[])
{
    stack new=(stack)malloc(sizeof(struct STACK));
    strcpy(new->item,item);
    new->next=S->next;
    S->next=new;
}

//��ջ���޷���ֵ��
void pop(stack S)
{
    if(Empty(S))    ERR();
    stack tmp=S->next;
    S->next=tmp->next;
    free(tmp);
}

//����ջ�����(��ջ����ջβ)
void output(stack S)
{
    while(S->next!=NULL)
    {
        printf("%s ",S->next->item);
        S=S->next;
    }
    puts("");
}

//����ջ��Ԫ�ص�ֵ
char *top(stack S)
{
    if(!Empty(S))
        return S->next->item;
    else ERR();
}

//����
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

