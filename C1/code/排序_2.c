//为使代码简略写成两个.c文件，除排序函数实现其他不分均与排序_1相同。
#include <stdio.h>
int swap(int *a,int *b);
void Bubble_Sort(int a[],int n);
void Select_Sort(int a[],int fir,int n);
void Insert_Sort(int a[],int last,int n);
void mprintf(int a[],int n,char s[]);

void Bubble_Sort(int a[],int n)
{
    if(n==0)    return;
    for(int j=0;j<n-1;j++)
    {
        if(a[j]>a[j+1]) swap(&a[j],&a[j+1]);
    }
    Bubble_Sort(a,n-1);
    
}

void Select_Sort(int a[],int fir,int n)
{
    int min_index=fir;
    if(fir==n)    return;
    for(int j=fir+1;j<n;j++)
    {
        if(a[j]<a[min_index])
            min_index=j;
    }
    if(min_index!=fir)    swap(&a[fir],&a[min_index]);
    Select_Sort(a,++fir,n);
}

void Insert_Sort(int a[],int last,int n)
{
    if(last==n) return;
    for(int j=0;j<last;j++)
    {
        if(a[j]>a[last])
        {
            int tmp=a[last];
            for(int k=last;k>=j+1;k--)
                a[k]=a[k-1];
            a[j]=tmp;
        }
    }
    Insert_Sort(a,++last,n);
}

//用于交换两个值的通用函数
int swap(int *a,int *b)
{
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}

//用于打印数组
void mprintf(int a[],int n,char s[])
{
    printf("%s: ",s);
    for(int i=0;i<n;i++)    printf("%d  ",a[i]);
    printf("\n");
}

int main()
{
    int exap[10]={1,9,2,7,4,9,6,3,8,10};
    mprintf(exap,10,"Before Sort");
    Bubble_Sort(exap,10);
    Select_Sort(exap,0,10);
    Insert_Sort(exap,1,10);
    mprintf(exap,10,"After Sort");
    return 0;
}