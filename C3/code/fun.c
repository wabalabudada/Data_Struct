#include "g.h"
#include "Queue.c"
#include "stack.c"

//��������һ���������ӽ��Ϊ����#��ʾ
Btree CreatBT()
{
    Btree T=(Btree)malloc(sizeof(node));
    elemtype ch;
    scanf("%c",&ch);
    if(ch=='#') T=NULL;
    else
    {
        T->data=ch;
        T->lchild=CreatBT();
        T->rchild=CreatBT();
    }
    return T;
}

//�������
void PreOrder(Btree T)
{
    if(T!=NULL)
    {
        printf("%c ",T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

//�������
void InOrder(Btree T)
{
    if(T!=NULL)
    {
        InOrder(T->lchild);
        printf("%c ",T->data);
        InOrder(T->rchild);
    }
}

//�������
void PostOrder(Btree T)
{
    if(T!=NULL)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c ",T->data);
    }
}

//�������
void LeverOrder(Btree T)
{
    if(T!=NULL)
    {
        queue Q=MakeNullQueue();
        EnQueue(T,&Q);
        while(!Empty(Q))
        {
            int t=(Q.front+1)%MaxSize;
            printf("%c ",Q.data[t]->data);
            EnQueue(Q.data[t]->lchild,&Q);
            EnQueue(Q.data[t]->rchild,&Q);
            DeQueue(&Q);
        }
    }
}

//�������ĳ�ֱ����Ľ��
void Output(char descr[],void Way(Btree T),Btree T)
{
    puts(descr);
    Way(T);
    puts("");
}

//����һ����
Btree Copy(Btree T)
{
    if(T!=NULL)
    {
        Btree newtree=(Btree)malloc(sizeof(node));
        newtree->data=T->data;
        newtree->lchild=Copy(T->lchild);
        newtree->rchild=Copy(T->rchild);
        return newtree;
    }
    return NULL;
}

//�ͷ�һ�ö��������ڴ�
void Destroy(Btree T)
{
    if(T!=NULL)
    {
        Destroy(T->lchild);
        Destroy(T->rchild);
        free(T);
    }
}

//����
int MaxWidth(Btree T)
{
    if(T!=NULL)
    {
        int deps[MaxSize]={0};
        int ans=1;
        Btree tmpT=Copy(T);
        queue Q=MakeNullQueue();
        tmpT->data=1;
        deps[1]++;
        EnQueue(tmpT,&Q);
        while(!Empty(Q))
        {
            int t=(Q.front+1)%MaxSize;
            if(EnQueue(Q.data[t]->lchild,&Q)==1)
            {
                Q.data[t]->lchild->data=Q.data[t]->data+1;
                deps[Q.data[t]->lchild->data]++;
            }      
            if(EnQueue(Q.data[t]->rchild,&Q)==1)
            {
                Q.data[t]->rchild->data=Q.data[t]->data+1;
                deps[Q.data[t]->rchild->data]++;
            }
            DeQueue(&Q);
        }
        for(int i=2;i<MaxSize-1;i++)
        {
            if(deps[i]>ans) ans=deps[i];
        }
        Destroy(tmpT);
        return ans;
    }
    return 0;
}

//�ж��Ƿ�Ϊ��ȫ������
int CompleteBTree(Btree T)
{
    if(T!=NULL)
    {
        int a[3*MaxSize];
        int a_p=0;
        queue Q=MakeNullQueue();
        a[a_p++]=EnQueue(T,&Q);
        while(!Empty(Q))
        {
            int t=(Q.front+1)%MaxSize;
            a[a_p++]=EnQueue(Q.data[t]->lchild,&Q);
            a[a_p++]=EnQueue(Q.data[t]->rchild,&Q);
            DeQueue(&Q);
        }
        for(int i=0;i<a_p-1;i++)
        {
            if(a[i]==0&&a[i+1]==1)  return 0;
        }
    }
    return 1;
} 

//����������ǵݹ飩
void PreOrder_Stack(Btree T)
{
    stack S=MakeNullStack();
    Btree tmp=T;
    while(tmp!=NULL||!Empty_Stack(S))
    {
        while(tmp!=NULL)
        {
            printf("%c ",tmp->data);
            push(S,tmp);
            tmp=tmp->lchild;
        }
        if(!Empty_Stack(S))
        {
            tmp=top(S);pop(S);
            tmp=tmp->rchild;
        }
    }
    free(tmp);
}

//����������ǵݹ飩
void InOrder_Stack(Btree T)
{
    stack S=MakeNullStack();
    Btree tmp=T;
    while(tmp!=NULL||!Empty_Stack(S))
    {
        while(tmp!=NULL)
        {
            push(S,tmp);
            tmp=tmp->lchild;
        }
        if(!Empty_Stack(S))
        {
            tmp=top(S);pop(S);
            printf("%c ",tmp->data);
            tmp=tmp->rchild;
        }
    }
    free(tmp);
}

//����������ǵݹ飩
void PostOrder_Stack(Btree T)
{
    stack S=MakeNullStack();
    Btree tmp=T;
    while(tmp!=NULL||!Empty_Stack(S))
    {
        while(tmp!=NULL)
        {
            push(S,tmp);
            S->next->flag=1;
            tmp=tmp->lchild;
        }
        while(!Empty_Stack(S)&&S->next->flag==2)
        {
            printf("%c ",top(S)->data);
            pop(S);
        }
        if(!Empty_Stack(S))
        {
            S->next->flag=2;
            tmp=top(S)->rchild;
        }
    }
}

//�����
void OutputTree(Btree T)
{
    int i=0;
    if(T!=NULL)
    {
        queue Q=MakeNullQueue();
        EnQueue(T,&Q);
        while(!Empty(Q))
        {
            int t=(Q.front+1)%MaxSize;
            printf("node%d: %c ,left child:%c ,right child:%c\n",++i,Q.data[t]->data,Q.data[t]->lchild==NULL?'-':Q.data[t]->lchild->data
                    ,Q.data[t]->rchild==NULL?'-':Q.data[t]->rchild->data);
            EnQueue(Q.data[t]->lchild,&Q);
            EnQueue(Q.data[t]->rchild,&Q);
            DeQueue(&Q);
        }
    }
}