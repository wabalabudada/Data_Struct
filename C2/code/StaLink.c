//�����GBK����
//��������д�ڳ����ֱ�����м���
//�þ�̬����Ĵ����SPACE��д���ģ�������maxsize���Ĵ�С
//Ϊ��̷��㣬��һ���ձ�ͷ���

#include <stdio.h>
#include <stdlib.h>
#define maxsize 100
typedef struct SPACRSTR
{
    int data;
    int next;
}spacestr;
typedef int position,Cursor;
spacestr SPACE[maxsize];    //�����
int avail=0;

//���ÿռ��ʼ��
void Initialize()
{
    for(int j=0;j<maxsize-1;j++)
    {
        SPACE[j].next=j+1;
    }
    SPACE[maxsize-1].next=-1;
    avail=0;
}


//����һ�����ÿռ�
Cursor GetNode()
{
    Cursor p;
    if(SPACE[avail].next==-1)
        p=-1;
    else
    {
        p=SPACE[avail].next;
        SPACE[avail].next=SPACE[p].next;
    }
    return p;
}

//����һ����̬��������Ҫ������ͷ��ֵ
Cursor MakeNull()
{
    Cursor p=GetNode();
    SPACE[p].next=-1;
    return p;
}

//���ÿռ�Ļ���
void FreeNode(Cursor p)
{
    SPACE[p].next=SPACE[avail].next;
    SPACE[avail].next=p;
}

//����
void Insert(int x,position p)
{
    position q;
    q=GetNode();
    SPACE[q].data=x;
    SPACE[q].next=SPACE[p].next;
    SPACE[p].next=q;
}

//ɾ��
void Delete(position p)
{
    position q;
    if(SPACE[p].next!=-1)
    {
        q=SPACE[p].next;
        SPACE[p].next=SPACE[q].next;
        FreeNode(q);
    }
}

//����
position Locate(int x)
{
    position q=SPACE->next;
    while(SPACE[q].next!=-1)
    {
        if(SPACE[q].data==x)    return q;
        q=SPACE[q].next;
    }
    return -1;
}

//�������
void Output(Cursor p)
{
    p=SPACE[p].next;
    while(p!=-1)
    {
        printf("%-5d",SPACE[p].data);
        p=SPACE[p].next;
    }
    puts("");
}

//����
void Reversal(Cursor p)
{
    Cursor tmp=MakeNull();
    while(SPACE[p].next!=-1)
    {
        Insert(SPACE[SPACE[p].next].data,tmp);
        Delete(p);
    }
    SPACE[p].next=SPACE[tmp].next;
}

int main()
{
    Initialize();
    Cursor p=MakeNull();
    int testlist[]={5,4,3,2,1};
    for(int i=1;i<=5;i++)
    {
        Insert(testlist[i-1],p);
    }

    printf("��������\n");
    Output(p);

    printf("���ú�\n");
    Reversal(p);
    Output(p);
}   