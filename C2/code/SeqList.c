//�����GBK����
//��������д�ڳ����ֱ�����м���

#include <stdio.h>
#define max 100
#include <stdlib.h>

//Ĭ�ϵ�һ��Ԫ����elements[1]��
typedef struct LIST
{
    int elements[max];
    int last;
}LIST;

//����һ���ձ�
LIST MakeNull()
{
    LIST L;
    L.last=0;
    return L;
}

//��λ��p������ֵval
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

//��ӡ�������Ա�
void output(LIST *L)
{
    for(int i=1;i<=L->last;i++)
    {
        printf("%-5d",L->elements[i]);
    }
    puts("");
}

//ɾ��λ��p��ֵ
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

//����(����)
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

//ɾ���ظ�Ԫ��
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

//��ת
void Reversal(LIST *L)
{
    LIST tmp=MakeNull();
    for(int i=1;i<=L->last;i++)
    {
        Insert(&tmp,1,L->elements[i]);
    }
    *L=tmp;
}

//����
void LMove(LIST *L,int l)
{
    LIST tmp=MakeNull();
    for(int i=1,j=l;i<=L->last;i++,j++)
    {
        Insert(&tmp,i,L->elements[j%(L->last)+1]);
    }
    *L=tmp;
}

//����
void Rmove(LIST *L,int r)
{
    LIST tmp=MakeNull();
    for(int i=1,j=L->last-r;i<=L->last;i++,j++)
    {
        Insert(&tmp,i,L->elements[j%(L->last)+1]);
    }
    *L=tmp;
}

//�ϲ�
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

//Ѱ�Ҹ���Ԫ�أ����ص�һ���±꣩
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
    printf("��������:\n");
    output(&Test);

    printf("�����\n");
    Sort(&Test);
    output(&Test);

    printf("ɾ����һ��1\n");
    Delete(&Test,Locate(Test,1));
    output(&Test);

    printf("ɾ���ظ�Ԫ��\n");
    DeleteSame(&Test);
    output(&Test);

    printf("���Ա�����\n");
    Reversal(&Test);
    output(&Test);

    printf("������λ\n");
    LMove(&Test,2);
    output(&Test);

    printf("����һλ\n");
    Rmove(&Test,1);
    output(&Test);

    printf("�ϲ�(����ֱ�ӽ�Test��Test�ϲ�)\n");
    Sort(&Test);
    Test=Merge(&Test,&Test);
    output(&Test);
}