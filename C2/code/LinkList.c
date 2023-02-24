//请采用GBK编码
//测试用例写在程序里，直接运行即可

#include <stdio.h>
#include <stdlib.h>

typedef struct CELLTYPE
{
    int element;
    struct CELLTYPE* next;
}celltype;

typedef celltype* LIST;
typedef celltype* position;

//在p前插入一个结点，值为val
void Insert(position p,int val)
{
    //必须给q分配一块内存空间
    position q=(position)malloc(sizeof(struct CELLTYPE));
    q->element=val;
    q->next=p->next;
    p->next=q;
}

int Empty(LIST L)
{
    if(L->next==NULL)    return 1;
    return 0;
}

//删除p
void Delete(position p)
{
    if(p->next!=NULL)
    {
        position temp=p->next;
        p->next=p->next->next;
        free(temp);         
    }
}

//寻找值的位置
position Locate(int val,LIST L)
{
    position q=L;
    while(q->next!=NULL)
    {
        if(q->next->element==val)   return q;
        q=q->next;
    }
    return NULL;
}

//创建空表
LIST MakeNull()
{
    LIST L=(LIST)malloc(sizeof(struct CELLTYPE));
    L->next=NULL;
    return L;
}

//打印整个线性表
void output(LIST L)
{
    position tmp;
    for(tmp=L;tmp->next!=NULL;tmp=tmp->next)
    {
        printf("%-5d",tmp->next->element);
    }
    puts("");
}

//删除相同元素
void DeleteSame(LIST L)
{
    position tmp=L;
    while(tmp->next->next!=NULL)
    {
        if(tmp->next->element==tmp->next->next->element)
        {
            Delete(tmp->next);
        }
        else tmp=tmp->next;
    }
}

//逆置
void Reversal(LIST L)
{
    LIST tmp=MakeNull();
    while(!Empty(L))
    {
        Insert(tmp,L->next->element);
        Delete(L);
    }
    L->next=tmp->next;
    free(tmp);
}

//左移
void LMove(LIST L,int k)
{
    position end=L,tmp=L;
    while(end->next!=NULL)
    {
        end=end->next;
    }
    end->next=L->next;
    for(int i=1;i<=k;i++)
    {
        tmp=tmp->next;
    }
    L->next=tmp->next;
    tmp->next=NULL;
}

//右移
void RMove(LIST L,int k)
{
    int LL=0;
    position end=L,tmp=L;
    while(end->next!=NULL)
    {
        end=end->next;
        LL++;
    }
    end->next=L->next;
    for(int i=1;i<=LL-k;i++)
    {
        tmp=tmp->next;
    }
    L->next=tmp->next;
    tmp->next=NULL;
}

//传入一个数组和数组长度，串成一个链表(倒序)
LIST MakeList(int list[],int l)
{
    LIST tmp=MakeNull();
    for(int i=1;i<=l;i++)
    {
        Insert(tmp,list[i-1]);
    }
    return tmp;
}

//合并
LIST Merge(LIST L1,LIST L2)
{
    position end=L1;
    while(end->next!=NULL)
    {
        end=end->next;
    }
    end->next=L2->next;
}
int main()
{

    int testlist[]={15,13,11,9,7,7,7,3,1,1};
    int testlist2[]={9,7,5,3,1};
    LIST L1=MakeList(testlist,10),L2=MakeList(testlist2,5);

    printf("测试用例:\n");
    output(L1);

    printf("删除13:\n");
    Delete(Locate(13,L1));
    output(L1);
    
    printf("删除重复元素:\n");
    DeleteSame(L1);
    output(L1);

    printf("逆置\n");
    Reversal(L1);
    output(L1);

    printf("左移\n");
    LMove(L1,2);
    output(L1);

    printf("右移\n");
    RMove(L1,2);
    output(L1);

    printf("将L1和L2合并(L2=[1,3,5,7,9]\n");
    Merge(L1,L2);
    output(L1);

    return 0;
}