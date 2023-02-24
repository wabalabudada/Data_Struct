//请采用GBK编码
//测试用例写在程序里，直接运行即可

#include <stdio.h>
#define max 100
#include <stdlib.h>

//默认第一个元素在elements[1]处
typedef struct LIST
{
    int elements[max];
    int last;
}LIST;

//创建一个空表
LIST MakeNull()
{
    LIST L;
    L.last=0;
    return L;
}

//在位置p处插入值val
void Insert(LIST *L,int p,int val)
{
    if(p<1||p>(L->last+1))  return;
    else
    {
        for(int i=L->last;i>=p;i--)
        {
            L->elements[i+1]=L->elements[i];
        }
        L->elements[p]=val;
        L->last++;
    }
}

//打印整个线性表
void output(LIST *L)
{
    for(int i=1;i<=L->last;i++)
    {
        printf("%-5d",L->elements[i]);
    }
    puts("");
}

//删除位置p的值
void Delete(LIST *L,int p)
{
    if(p<1||p>(L->last+1))  return;
    else
    {
        for(int i=p;i<=L->last-1;i++)
        {
            L->elements[i]=L->elements[i+1];
        }
        L->last--;
    }

}

//排序(升序)
void Sort(LIST *L)
{
    for(int i=1;i<=L->last-1;i++)
    {
        for(int j=1;j<L->last-i+1;j++)
        {
            if(L->elements[j]>L->elements[j+1])
            {
                int temp=L->elements[j];
                L->elements[j]=L->elements[j+1];
                L->elements[j+1]=temp;
            }
        }
    }
}

//删除重复元素
void DeleteSame(LIST *L)
{
    for(int i=1;i<=L->last-1;)
    {
        if(L->elements[i]==L->elements[i+1])
        {
            Delete(L,i+1);
        }
        else i++;
    }
}

//翻转
void Reversal(LIST *L)
{
    LIST tmp=MakeNull();
    for(int i=1;i<=L->last;i++)
    {
        Insert(&tmp,1,L->elements[i]);
    }
    *L=tmp;
}

//左移
void LMove(LIST *L,int l)
{
    LIST tmp=MakeNull();
    for(int i=1,j=l;i<=L->last;i++,j++)
    {
        Insert(&tmp,i,L->elements[j%(L->last)+1]);
    }
    *L=tmp;
}

//右移
void Rmove(LIST *L,int r)
{
    LIST tmp=MakeNull();
    for(int i=1,j=L->last-r;i<=L->last;i++,j++)
    {
        Insert(&tmp,i,L->elements[j%(L->last)+1]);
    }
    *L=tmp;
}

//合并
LIST Merge(LIST *L1,LIST *L2)
{
    LIST tmp=MakeNull();
    int p1=1,p2=1,p3=1;
    while(p1<=L1->last||p2<=L2->last)
    {
        if(p1<=L1->last&&p2<=L2->last)
        {
            if(L1->elements[p1]<=L2->elements[p2])
            {
                Insert(&tmp,p3++,L1->elements[p1++]);
            }
            else
            {
                Insert(&tmp,p3++,L2->elements[p2++]);
            }
        }
        else if(p1<=L1->last)
        {
            Insert(&tmp,p3++,L1->elements[p1++]);

        }
        else if(p2<=L2->last)
        {
            Insert(&tmp,p3++,L2->elements[p2++]);
        }
    }
    return tmp;
}

//寻找给定元素（返回第一个下标）
int Locate(LIST L,int val)
{
    for(int i=1;i<=L.last;i++)
    {
        if(L.elements[i]==val)  return i;
    }
    return -1;
}

int main()
{
    LIST Test=MakeNull();
    int testlist[5]={0,1,1,1,1};
    for(int i=1;i<=4;i++)
    {
        Insert(&Test,i,testlist[i]);
    }
    printf("测试用例:\n");
    output(&Test);

    printf("排序后\n");
    Sort(&Test);
    output(&Test);

    printf("删除第一个1\n");
    Delete(&Test,Locate(Test,1));
    output(&Test);

    printf("删除重复元素\n");
    DeleteSame(&Test);
    output(&Test);

    printf("线性表逆置\n");
    Reversal(&Test);
    output(&Test);

    printf("左移两位\n");
    LMove(&Test,2);
    output(&Test);

    printf("右移一位\n");
    Rmove(&Test,1);
    output(&Test);

    printf("合并(这里直接将Test和Test合并)\n");
    Sort(&Test);
    Test=Merge(&Test,&Test);
    output(&Test);
}