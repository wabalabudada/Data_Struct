//请采用GBK编码
//测试用例写在程序里，直接运行即可
//该静态链表的储存池SPACE是写死的，可以在maxsize更改大小
//为编程方便，带一个空表头结点

#include <stdio.h>
#include <stdlib.h>
#define maxsize 100
typedef struct SPACRSTR
{
    int data;
    int next;
}spacestr;
typedef int position,Cursor;
spacestr SPACE[maxsize];    //储存池
int avail=0;

//可用空间初始化
void Initialize()
{
    for(int j=0;j<maxsize-1;j++)
    {
        SPACE[j].next=j+1;
    }
    SPACE[maxsize-1].next=-1;
    avail=0;
}


//分配一个可用空间
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

//生成一个静态链表，这里要给定表头的值
Cursor MakeNull()
{
    Cursor p=GetNode();
    SPACE[p].next=-1;
    return p;
}

//可用空间的回收
void FreeNode(Cursor p)
{
    SPACE[p].next=SPACE[avail].next;
    SPACE[avail].next=p;
}

//插入
void Insert(int x,position p)
{
    position q;
    q=GetNode();
    SPACE[q].data=x;
    SPACE[q].next=SPACE[p].next;
    SPACE[p].next=q;
}

//删除
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

//查找
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

//遍历输出
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

//逆置
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

    printf("测试用例\n");
    Output(p);

    printf("逆置后\n");
    Reversal(p);
    Output(p);
}   