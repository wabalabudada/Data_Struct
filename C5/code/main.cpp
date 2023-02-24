#include <stdio.h>
#include <stdlib.h>
#define MAX 3000
#define SIZE 1024
int sum;
typedef struct S_LIST
{
    int data[MAX];
    int last;
}*LIST;

typedef struct S_celltype
{
    int data;
    struct S_celltype *lchild,*rchild;
}celltype;
typedef celltype *BST;

//折半查找，没找到返回0，找到返回非0下标
int BSearch(LIST F,int k)
{  
    int low=1,up=F->last,mid;
    while(low<=up)
    {
        sum++;
        mid=(low+up)/2;
        if(F->data[mid]==k)
            return mid;
        else if(F->data[mid]<k)
            low=mid+1;
        else
            up=mid-1;
    }
    return 0;
}   

//BST上的查找
BST Search(BST F,int k)
{
    sum++;
    if(F==NULL)
        return NULL;
    else if(F->data==k)
        return F;
    else if(F->data<k)
        return Search(F->rchild,k);
    else
        return Search(F->lchild,k);
}

//如果数据集中存在关键字等于待插入条目的条目，返回0；如果插入成功，返回1
int Insert(BST &F,int k)
{
    if(F==NULL)
    {
        F=new celltype;
        F->data=k;
        F->lchild=NULL;
        F->rchild=NULL;
        return 1;
    }
    else if(k<F->data)
        return Insert(F->lchild,k);
    else if(k>F->data)
        return Insert(F->rchild,k);
    else
        return 0;
}

//删除继承结点,返回条目
int DeleteMin(BST &F)
{
    int tmp;
    BST P;
    if(F->lchild==NULL)
    {
        P=F;
        tmp=F->data;
        F=F->rchild;
        free(P);
        return tmp;
    }
    else
        return DeleteMin(F->lchild);
}

//删除指定关键字的结点，成功删除返回1，否则返回0
int Delete(BST &F,int k)
{
    if(F!=NULL)
    {
        if(k<F->data)
            Delete(F->lchild,k);
        else if(k>F->data)
            Delete(F->rchild,k);
        else
        {
            BST TMP=F;
            if(F->lchild==NULL&&F->rchild==NULL)
            {
                F=NULL;
                free(TMP);
            }
            else if(F->lchild==NULL)
            {
                F=F->rchild;
                free(TMP);
            }
            else if(F->rchild==NULL)
            {
                F=F->lchild;
                free(TMP);
            }
            else
            {
                F->data=DeleteMin(F);
            }
            return 1;
        }            
    }
    return 0;
}

void SortBST(LIST L,BST F)
{
    if(F!=NULL)
    {
        SortBST(L,F->lchild);
        L->data[++L->last]=F->data;
        SortBST(L,F->rchild);
    }

}

void MakeTestData1(LIST F,BST &T)
{
    int i;
    for(i=1;i<=SIZE;i++)
    {
        Insert(T,2*i-1);
    }
}

void MakeTestData2(LIST F,BST &T)
{
    int tmp[SIZE+1];
    int i,swap,j;
    for(i=1;i<=SIZE;i++)
    {
        tmp[i]=2*i-1;
    }
    for(i=1;i<=SIZE;i++)
    {
        j=rand()%SIZE+1;
        swap=tmp[j];
        tmp[j]=tmp[i];
        tmp[i]=swap;
    }
    for(i=1;i<=SIZE;i++)
    {
        Insert(T,tmp[i]);
    }
}

void Cal_ASL_BST(BST T)
{
    int i;
    sum=0;
    for(i=1;i<=SIZE;i++)
    {
        Search(T,2*i-1);
    }
    printf("BST上查找成功的平均查找长度:%f\n",(float)sum/SIZE);
    
    sum=0;
    for(i=1;i<=SIZE;i++)
    {
        Search(T,2*i);
    }
    printf("BST上查找失败的平均查找长度:%f\n",(float)sum/SIZE);
}

void Cal_ASL_ZB(LIST L)
{
    int i;
    sum=0;
    for(i=1;i<=SIZE;i++)
    {
        BSearch(L,2*i-1);
    }
    printf("折半查找查找成功的平均查找长度:%f\n",(float)sum/SIZE);

    sum=0;
    for(i=1;i<=SIZE;i++)
    {
        BSearch(L,2*i);
    }
    printf("折半查找查找失败的平均查找长度:%f\n",(float)sum/SIZE);

} 

int main()
{
    LIST F=(LIST)malloc(sizeof(struct S_LIST));
    BST T=NULL;
    printf("----------第一组-----------\n");
    MakeTestData1(F,T);
    F->last=0;
    SortBST(F,T);
    Cal_ASL_BST(T);
    Cal_ASL_ZB(F);

    LIST F2=(LIST)malloc(sizeof(struct S_LIST));
    BST T2=NULL;
    printf("\n----------第二组-----------\n");
    MakeTestData2(F2,T2);
    F->last=0;
    SortBST(F,T2);
    Cal_ASL_BST(T2);
    Cal_ASL_ZB(F);

    return 0;
}